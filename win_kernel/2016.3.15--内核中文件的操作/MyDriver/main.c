#include "FileOperatiom.h"


#define	DEVICE_NAME			L"\\Device\\MyDriver"
#define LINK_NAME			L"\\DosDevices\\MyDriver"
#define LINK_GLOBAL_NAME	L"\\DosDevices\\Global\\MyDriver"


VOID DriverUnload(PDRIVER_OBJECT pDriverObj)
{
	DbgPrint("DriverUnload!\n");

	//ɾ���������Ӻ��豸
	UNICODE_STRING strLink;
	RtlInitUnicodeString(&strLink, LINK_NAME);
	IoDeleteSymbolicLink(&strLink);
	IoDeleteDevice(pDriverObj->DeviceObject);
}

//IRP_MJ_CREATE��Ӧ�Ĵ������̣�һ�㲻�ù���
NTSTATUS DispatchCreate(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

//IRP_MJ_CLOSE��Ӧ�Ĵ������̣�һ�㲻�ù���
NTSTATUS DispatchClose(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

//IRP_MJ_DEVICE_CONTROL��Ӧ�Ĵ������̣���������Ҫ�ĺ���֮һ��һ��������;�������������ܵĳ��򣬶��ᾭ���������
NTSTATUS DispatchIoctl(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	NTSTATUS status = STATUS_INVALID_DEVICE_REQUEST;
	PIO_STACK_LOCATION pIrpStack;
	ULONG uIoControlCode;
	PVOID pIoBuffer;
	ULONG uInSize;
	ULONG uOutSize;

	//���IRP��Ĺؼ�����
	pIrpStack = IoGetCurrentIrpStackLocation(pIrp);

	//������Ǵ�˵�еĿ�����
	uIoControlCode = pIrpStack->Parameters.DeviceIoControl.IoControlCode;

	//���������Ļ�������DeviceIoControl��InBuffer��OutBuffer��������
	pIoBuffer = pIrp->AssociatedIrp.SystemBuffer;

	//EXE���ʹ������ݵ�BUFFER���ȣ�DeviceIoControl��nInBufferSize��
	uInSize = pIrpStack->Parameters.DeviceIoControl.InputBufferLength;

	//EXE���մ������ݵ�BUFFER���ȣ�DeviceIoControl��nOutBufferSize��
	uOutSize = pIrpStack->Parameters.DeviceIoControl.OutputBufferLength;
	switch (uIoControlCode)
	{
	default:
		break;
	}

	//�����趨DeviceIoControl��*lpBytesReturned��ֵ�����ͨ��ʧ���򷵻�0���ȣ�
	if (status == STATUS_SUCCESS)
	{
		pIrp->IoStatus.Information = uOutSize;
	}
	else
	{
		pIrp->IoStatus.Information = 0;
	}

	//�����趨DeviceIoControl�ķ���ֵ�ǳɹ�����ʧ��
	pIrp->IoStatus.Status = status;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return status;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING pRegistryString)
{
	DbgPrint("DriverEntry!\n");
	UNICODE_STRING ustrLinkName;
	UNICODE_STRING ustrDevName;
	PDEVICE_OBJECT pDevObj;
	NTSTATUS status = STATUS_SUCCESS;

	//���÷ַ�������ж������
	pDriverObj->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
	pDriverObj->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
	pDriverObj->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchIoctl;
	pDriverObj->DriverUnload = DriverUnload;

	//����һ���豸����
	RtlInitUnicodeString(&ustrDevName, DEVICE_NAME);
	status = IoCreateDevice(pDriverObj, 0, &ustrDevName, FILE_DEVICE_UNKNOWN, 0, FALSE, &pDevObj);
	if (!NT_SUCCESS(status))
	{
		return status;
	}
	else
	{
		RtlInitUnicodeString(&ustrLinkName, LINK_NAME);
	}

	//������������
	status = IoCreateSymbolicLink(&ustrLinkName, &ustrDevName);
	if (!NT_SUCCESS(status))
	{
		IoDeleteDevice(pDevObj);
		return status;
	}

	if (FALSE == ZwCopyFile(L"C:\\3.txt", L"D:\\1.txt"))
		DbgPrint("ZwCopyFile Faild!\n");
	NTSTATUS st;
	st = ZwDeleteFileFolder(L"D:\\1.txt");
	if (st != STATUS_SUCCESS)
	{
		DbgPrint("ZwDeleteFileFolder Faild:%08x\n", st);
	}
	if (STATUS_SUCCESS != ZwRenameFile(L"D:\\4.txt", L"D:\\3.txt"))
		DbgPrint("ZwRenameFile Faild!\n");
	DbgPrint("FileSize=%ld\n", GetFileSize(L"D:\\1.txt"));
	DbgPrint("Count=%ld\n", SearchDirectory("C:\\2"));
	
	//���ؼ���������״̬���������ʧ�ܣ���������������ں˿ռ�
	return STATUS_SUCCESS;
}