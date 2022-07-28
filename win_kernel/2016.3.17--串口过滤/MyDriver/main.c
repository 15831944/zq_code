#include "ComCap.h"


#define	DEVICE_NAME			L"\\Device\\MyDriver"
#define LINK_NAME			L"\\DosDevices\\MyDriver"
#define LINK_GLOBAL_NAME	L"\\DosDevices\\Global\\MyDriver"


VOID DriverUnload(PDRIVER_OBJECT pDriverObj)
{
	ULONG i;
	LARGE_INTEGER interval;

	//���Ƚ����
	for (i = 0; i < CCP_MAX_COM_ID; ++i)
	{
		if (s_nextobj[i] != NULL)
			IoDeleteDevice(s_nextobj[i]);
	}

	//˯��5�룬�ȴ����е�IRP�������
	interval.QuadPart = (5 * 1000 * DELAY_ONE_MILLISECOND);
	KeDelayExecutionThread(KernelMode, FALSE, &interval);

	//ɾ�������豸
	for (i = 0; i < CCP_MAX_COM_ID; ++i)
	{
		if (s_fltobj[i] != NULL)
			IoDeleteDevice(s_fltobj[i]);
	}

	//ɾ���������Ӻ��豸
	UNICODE_STRING strLink;
	RtlInitUnicodeString(&strLink, LINK_NAME);
	IoDeleteSymbolicLink(&strLink);
	IoDeleteDevice(pDriverObj->DeviceObject);
	DbgPrint("DriverUnload Succed!\n");
}

NTSTATUS ccpDispatch(PDEVICE_OBJECT device, PIRP irp)
{
	PIO_STACK_LOCATION irpsp = IoGetCurrentIrpStackLocation(irp);
	NTSTATUS status;
	ULONG i, j;

	//���������豸
	for (i = 0; i < CCP_MAX_COM_ID; ++i)
	{
		if (s_fltobj[i] == device)
		{
			//���еĵ�Դ����ȫ��ͨ��
			if (irpsp->MajorFunction == IRP_MJ_POWER)
			{
				//ֱ�ӷ��ͣ�Ȼ�󷵻�˵һ�䱻������
				PoStartNextPowerIrp(irp);
				IoSkipCurrentIrpStackLocation(irp);
				return PoCallDriver(device, irp);
			}

			//Ȼ�����д����
			if (irpsp->MajorFunction == IRP_MJ_WRITE)
			{
				//�Ȼ�ó���
				ULONG len = irpsp->Parameters.Write.Length;

				//Ȼ���û�����
				PUCHAR buf = NULL;
				if (irp->MdlAddress != NULL)
					buf = (PUCHAR)MmGetSystemAddressForMdlSafe(irp->MdlAddress, NormalPagePriority);
				else
					buf = (PUCHAR)irp->UserBuffer;

				if (buf == NULL)
					buf = (PUCHAR)irp->AssociatedIrp.SystemBuffer;

				//��ӡ����
				for (j = 0; j < len; ++j)
				{
					DbgPrint("comcap: Send Data: %2x\n", buf[j]);
				}
			}

			//��Щ����ֱ���·�ִ�м��ɣ�û�н�ֹ�����߸ı���
			IoSkipCurrentIrpStackLocation(irp);
			return IoCallDriver(s_nextobj[i], irp);
		}
	}

	//���û�ڰ󶨵��豸�У�����������ģ�ֱ�ӷ��ز�������
	irp->IoStatus.Information = 0;
	irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING pRegistryString)
{
	UNICODE_STRING ustrLinkName;
	UNICODE_STRING ustrDevName;
	PDEVICE_OBJECT pDevObj;
	NTSTATUS status = STATUS_SUCCESS;

	//���÷ַ�������ж������
	size_t i;
	for (i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; ++i)
	{
		pDriverObj->MajorFunction[i] = ccpDispatch;
	}
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

	// �����еĴ��ڡ�
	ccpAttachAllComs(pDriverObj);

	DbgPrint("DriverEntry Succeed!\n");
	
	//���ؼ���������״̬���������ʧ�ܣ���������������ں˿ռ�
	return STATUS_SUCCESS;
}