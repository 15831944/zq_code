#include <ntddk.h>

// �ṩһ��Unload����ֻ��Ϊ��
VOID DriverUnload(PDRIVER_OBJECT driver)
{
	UNREFERENCED_PARAMETER(driver);
	// ����ʵ��������ʲô��������ֻ��ӡһ�仰:
	DbgPrint("DriverUnload: hello world");
}

// DriverEntry����ں������൱��main��
NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING reg_path)
{
	UNREFERENCED_PARAMETER(reg_path);

	DbgBreakPoint();
	DbgPrint("DriverEntry: hello world!\n");

	// ����һ��ж�غ�����������������˳���
	driver->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}
