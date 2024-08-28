// Основной файл WDK
#include <ntddk.h>

// Объявление функции выгрузки драйвера
VOID DriverUnload(PDRIVER_OBJECT driverObject);

// Точка входа в драйвер (аналог функции main)
NTSTATUS DriverEntry(IN PDRIVER_OBJECT driverObject, IN PUNICODE_STRING registryPath)
{
	// Отметка параметра неиспользуемым
	UNREFERENCED_PARAMETER(registryPath);

	// Печать отладочного сообщения
	DbgPrint("Hello from Windows kernel mode!!");
	DbgPrint("LOOOOOOVE fuck fuckfuckcuk");
	DbgPrint("LOOOOOOVE fuck fuckfuckcuk");
	DbgPrint("LOOOOOOVE fuck fuckfuckcuk");
	DbgPrint("LOOOOOOVE fuck fuckfuckcuk");
	DbgPrint("LOOOOOOVE fuck fuckfuckcuk");
	DbgPrint("LOOOOOOVE fuck fuckfuckcuk");

	// Регистрация функции выгрузки драйвера
	driverObject->DriverUnload = DriverUnload;

	return STATUS_SUCCESS;
}

// Функция выгрузки драйвера
VOID DriverUnload(IN PDRIVER_OBJECT driverObject)
{
	// Отметка параметра неиспользуемым
	UNREFERENCED_PARAMETER(driverObject);
	// Вывод отладочного сообщения
	DbgPrint("Goodbye!");
}
