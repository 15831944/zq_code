#ifndef COM_CAP_H
#define COM_CAP_H

#include <ntddk.h>
#include <ntstrsafe.h>


#define CCP_MAX_COM_ID 32
#define DELAY_ONE_MICROSECOND  (-10)
#define DELAY_ONE_MILLISECOND (DELAY_ONE_MICROSECOND*1000)
#define DELAY_ONE_SECOND (DELAY_ONE_MILLISECOND*1000)


// �����豸����ʵ�豸
static PDEVICE_OBJECT s_fltobj[CCP_MAX_COM_ID] = { 0 };
static PDEVICE_OBJECT s_nextobj[CCP_MAX_COM_ID] = { 0 };

// ͨ���豸���ֻ��һ���˿��豸
PDEVICE_OBJECT ccpOpenCom(ULONG id)
{
	UNICODE_STRING name_str;
	static WCHAR name[32] = { 0 };
	PFILE_OBJECT fileobj = NULL;
	PDEVICE_OBJECT devobj = NULL;
	NTSTATUS status;

	// �����ַ���
	memset(name, 0, sizeof(WCHAR) * 32);
	RtlStringCchPrintfW(name, 32, L"\\Device\\Serial%d", id);
	RtlInitUnicodeString(&name_str, name);

	// ���������ֵõ��豸����
	status = IoGetDeviceObjectPointer(&name_str, FILE_ALL_ACCESS, &fileobj, &devobj);

	//����ɹ�����Ҫ������ļ����������ã�����������ڴ�й©
	if (status == STATUS_SUCCESS)
		ObDereferenceObject(fileobj);

	return devobj;
}

// ���ɹ����豸����
NTSTATUS ccpAttachDevice(PDRIVER_OBJECT pDriverObj, PDEVICE_OBJECT pOldObj, PDEVICE_OBJECT* pFltObj, PDEVICE_OBJECT* pNext)
{
	NTSTATUS status;
	PDEVICE_OBJECT topdev;

	//�����豸
	status = IoCreateDevice(pDriverObj,//����������
		0,//�豸��չ�����ﴫ0����
		NULL,//�����豸���֣�һ�㲻��Ҫ����
		pOldObj->DeviceType,//�豸���ͣ����ֺͱ��󶨵��豸����һ�¼���
		0,//�豸����
		FALSE,
		pFltObj//�����豸
		);
	if (status != STATUS_SUCCESS)
		return status;

	//���豸֮ǰ����Ҫ������豸����Ķ���������óɺ�Ҫ��
	//��Ŀ�����һ�£����������ͱ�־
	//������Ҫ��־λ
	if (pOldObj->Flags & DO_BUFFERED_IO)
		(*pFltObj)->Flags |= DO_BUFFERED_IO;
	if (pOldObj->Flags & DO_DIRECT_IO)
		(*pFltObj)->Flags |= DO_DIRECT_IO;
	if (pOldObj->Characteristics & FILE_DEVICE_SECURE_OPEN)
		(*pFltObj)->Characteristics |= FILE_DEVICE_SECURE_OPEN;
	(*pFltObj)->Flags |= DO_POWER_PAGABLE;

	//��һ���豸�󶨵���һ���豸��
	status = IoAttachDeviceToDeviceStackSafe(*pFltObj,//�����豸
		pOldObj,//Ҫ���󶨵��豸ջ�е��豸
		&topdev);//�������ձ��󶨵��豸
	if (status != STATUS_SUCCESS)
	{
		IoDeleteDevice(*pFltObj);
		*pFltObj = NULL;
		return status;
	}
	*pNext = topdev;

	//��������豸�Ѿ�����
	(*pFltObj)->Flags = (*pFltObj)->Flags & ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}

// ���������DriverEntry�е��ã����԰����еĴ��ڡ�
void ccpAttachAllComs(PDRIVER_OBJECT driver)
{
	ULONG i;
	PDEVICE_OBJECT com_ob;
	for (i = 0; i < CCP_MAX_COM_ID; i++)
	{
		// ���object����
		com_ob = ccpOpenCom(i);
		if (com_ob == NULL)
			continue;

		// �������
		ccpAttachDevice(driver, com_ob, &s_fltobj[i], &s_nextobj[i]);
	}
}


#endif
