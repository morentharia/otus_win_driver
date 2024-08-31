#include <windows.h>
#include <iostream>
#include <stdio.h>

#define IOCTL_TERMINATE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)

struct DeviceRequest
{
	USHORT a;
	USHORT b;
};

struct DeviceResponse
{
	USHORT result;
};
// ===========================

int main()
{
	//HANDLE hDevice = CreateFileW(L"\\\\.\\Terminator",
	//	FILE_ANY_ACCESS,
	//	FILE_SHARE_READ,
	//	NULL,
	//	OPEN_EXISTING,
	//	FILE_ATTRIBUTE_NORMAL,
	//	NULL);

	HANDLE hDevice = CreateFileW(L"\\\\.\\Terminator", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hDevice == INVALID_HANDLE_VALUE) {
		printf("failed to open mydriver\n");
		return -1;
	}

	DWORD request = 10100;
	

	LPVOID input = (LPVOID)&request;

	DeviceResponse response = { 0 };
	LPVOID answer = (LPVOID)&response;
	DWORD bytes = 0;

	bool res = DeviceIoControl(hDevice, IOCTL_TERMINATE, input, sizeof(DWORD), NULL, 0, NULL, NULL);
	
	std::cout << "deviceio res" << res;

	response = *((DeviceResponse*)answer);
	std::cout << "Sum : " << response.result << std::endl;
	//char ch;
	//std::cin >> ch;

	CloseHandle(hDevice);
}
