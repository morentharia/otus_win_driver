// �������� ���� WDK
#include <ntddk.h>

// ���������� ������� �������� ��������
VOID DriverUnload(PDRIVER_OBJECT driverObject);

// ����� ����� � ������� (������ ������� main)
NTSTATUS DriverEntry(IN PDRIVER_OBJECT driverObject, IN PUNICODE_STRING registryPath)
{
	// ������� ��������� ��������������
	UNREFERENCED_PARAMETER(registryPath);

	// ������ ����������� ���������
	DbgPrint("Hello from Windows kernel mode!!");
	DbgPrint("LOOOOOOVE fuck fuckfuckcuk");
	DbgPrint("LOOOOOOVE fuck fuckfuckcuk");
	DbgPrint("LOOOOOOVE fuck fuckfuckcuk");
	DbgPrint("LOOOOOOVE fuck fuckfuckcuk");
	DbgPrint("LOOOOOOVE fuck fuckfuckcuk");
	DbgPrint("LOOOOOOVE fuck fuckfuckcuk");

	// ����������� ������� �������� ��������
	driverObject->DriverUnload = DriverUnload;

	return STATUS_SUCCESS;
}

// ������� �������� ��������
VOID DriverUnload(IN PDRIVER_OBJECT driverObject)
{
	// ������� ��������� ��������������
	UNREFERENCED_PARAMETER(driverObject);
	// ����� ����������� ���������
	DbgPrint("Goodbye!");
}
