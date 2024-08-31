#include <ntifs.h>
#include <string.h>
#include <Ntstrsafe.h>

#define deviceName      L"\\Device\\Terminator"
#define symbolicName    L"\\DosDevices\\Terminator"

#define IOCTL_TERMINATE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)

PDEVICE_OBJECT deviceObject;
UNICODE_STRING  SymbolicLinkName;

void Unload(PDRIVER_OBJECT pDriverObject)
{
    DbgPrint("Unload!\n");
    UNREFERENCED_PARAMETER(pDriverObject);
}

void Terminate(DWORD pid) {
    HANDLE hProcess = NULL;
    OBJECT_ATTRIBUTES oa = { 0 };
    CLIENT_ID clientId;
    NTSTATUS status;

    DbgPrint("kill pid: %d", pid);
    //clientId.UniqueProcess = (HANDLE)pid;
    //status = ZwOpenProcess(&hProcess, PROCESS_ALL_ACCESS, &oa, &clientId);

    //if (status == STATUS_SUCCESS) {
    //    ZwTerminateProcess(hProcess, 0);
    //    ZwClose(hProcess);
    //}

    DbgPrint("kill again and again");
    //again
    PEPROCESS eProcess = NULL;
    NTSTATUS NtStatus = STATUS_SUCCESS;
    NtStatus = PsLookupProcessByProcessId((HANDLE)pid, &eProcess);
    if (NT_SUCCESS(NtStatus)) {
        __try {
            HANDLE proc = NULL;
            NtStatus = ObOpenObjectByPointer(eProcess, OBJ_KERNEL_HANDLE, NULL, KEY_ALL_ACCESS, NULL, KernelMode, &proc);
            if (NT_SUCCESS(NtStatus)) {
                NtStatus = ZwTerminateProcess(proc, STATUS_FAIL_FAST_EXCEPTION);
                ZwClose(proc);
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            NtStatus = STATUS_INTERNAL_ERROR;
        }
    }
  
}

NTSTATUS CtlPass(IN PDEVICE_OBJECT pDeviceObject, IN PIRP Irp)
{
    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return STATUS_SUCCESS;
}

NTSTATUS CtlDriverDispatch(IN PDEVICE_OBJECT pDeviceObject, IN PIRP Irp)
{
    PIO_STACK_LOCATION pIrpStack;
    DWORD inSize, ioctl, pid;

    pIrpStack = IoGetCurrentIrpStackLocation(Irp);
    ioctl = pIrpStack->Parameters.DeviceIoControl.IoControlCode;
    // inSize = pIrpStack->Parameters.DeviceIoControl.InputBufferLength;

    if (ioctl == IOCTL_TERMINATE)
    {
        if (pIrpStack->Parameters.DeviceIoControl.InputBufferLength == sizeof(DWORD)) {
            RtlCopyMemory(&pid, Irp->AssociatedIrp.SystemBuffer, sizeof(pid));
            pid = *(DWORD*)Irp->AssociatedIrp.SystemBuffer;
            Terminate(pid);
        }
    }

    Irp->IoStatus.Information = 0;
    Irp->IoStatus.Status = STATUS_SUCCESS;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return STATUS_SUCCESS;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
    int i;
    NTSTATUS status;
    UNICODE_STRING DeviceName;

    PDRIVER_DISPATCH* pDispacher;
    pDispacher = pDriverObject->MajorFunction;

    RtlInitUnicodeString(&DeviceName, deviceName);
    RtlInitUnicodeString(&SymbolicLinkName, symbolicName);

    status = IoCreateDevice(pDriverObject, 0, &DeviceName, FILE_DEVICE_NULL, 0, FALSE, &deviceObject);
    if (status == STATUS_SUCCESS)
    {
        status = IoCreateSymbolicLink(&SymbolicLinkName, &DeviceName);

        for (i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
            pDriverObject->MajorFunction[i] = CtlPass;

        pDispacher[IRP_MJ_DEVICE_CONTROL] = CtlDriverDispatch;
        pDriverObject->DriverUnload = Unload;
    }

    return STATUS_SUCCESS;
}
