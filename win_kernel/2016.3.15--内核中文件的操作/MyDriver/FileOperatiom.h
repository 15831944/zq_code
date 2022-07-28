#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include <Ntifs.h>


#define RN_MAX_PATH 2048
#define SFLT_POOL_TAG 'fuck'
#define MAX_PATH2 4096
#define kmalloc(_s)	ExAllocatePoolWithTag(NonPagedPool, _s, 'SYSQ')
#define kfree(_p)	ExFreePool(_p)


//�����ļ�
BOOLEAN ZwCopyFile(IN PWSTR ustrDestFile, IN PWSTR ustrSrcFile)
{
	HANDLE hSrcFile = NULL;
	HANDLE hDestFile = NULL;
	PVOID buffer = NULL;
	ULONG length = 0;
	LARGE_INTEGER offset = { 0 };
	IO_STATUS_BLOCK Io_Status_Block = { 0 };
	OBJECT_ATTRIBUTES obj_attrib;
	NTSTATUS status;
	BOOLEAN bRet = FALSE;
	UNICODE_STRING unSrcFile;
	UNICODE_STRING unDestFile;
	WCHAR SrcBuf[256] = { 0 };
	WCHAR DestBuf[256] = { 0 };
	wcscpy(SrcBuf, L"\\??\\");
	wcscat(SrcBuf, ustrSrcFile);
	wcscpy(DestBuf, L"\\??\\");
	wcscat(DestBuf, ustrDestFile);
	RtlInitUnicodeString(&unSrcFile, SrcBuf);
	RtlInitUnicodeString(&unDestFile, DestBuf);
	do
	{
		//���ں��У������Ǵ��ļ���ע������豸�������ȵ���
		//���������ʼ��һ��OBJECT_ATTRIBUTES�Ľṹ��
		InitializeObjectAttributes(&obj_attrib,
			&unSrcFile,
			OBJ_CASE_INSENSITIVE |//���ֲ����ִ�Сд
			OBJ_KERNEL_HANDLE,//�ں˾�������ù˼�Ȩ������
			NULL,
			NULL);

		//��һ���ļ�
			status = ZwCreateFile(&hSrcFile,//���ָ��
				GENERIC_READ,//��Ȩ��
				&obj_attrib,//�����ʼ���Ľṹ�壬����������ļ�·��
				&Io_Status_Block,//��ʾ�����Ľ��
				NULL,//�����ļ���ʼ�������С������ϵ�������ļ�����д�ļ�
				FILE_ATTRIBUTE_NORMAL,//�½������ļ����ԣ�һ��Ϊ0����FILE_ATTRIBUTE_NORMAL
				FILE_SHARE_READ,//�������Ȩ��
				FILE_OPEN,//������ļ�
				FILE_NON_DIRECTORY_FILE |
				FILE_SYNCHRONOUS_IO_NONALERT,//��ʾͬ����һ���ļ�������Ŀ¼
				NULL,
				0);
		if (!NT_SUCCESS(status))
		{
			bRet = FALSE;
			break;
		}

		// ��Ŀ���ļ�
		InitializeObjectAttributes(&obj_attrib,
			&unDestFile,
			OBJ_CASE_INSENSITIVE |
			OBJ_KERNEL_HANDLE,
			NULL,
			NULL);
		status = ZwCreateFile(&hDestFile,
			GENERIC_WRITE,
			&obj_attrib,
			&Io_Status_Block,
			NULL,
			FILE_ATTRIBUTE_NORMAL,
			FILE_SHARE_READ,
			FILE_OPEN_IF,
			FILE_NON_DIRECTORY_FILE |
			FILE_SYNCHRONOUS_IO_NONALERT,
			NULL,
			0);
		if (!NT_SUCCESS(status))
		{
			bRet = FALSE;
			break;
		}

		//Ϊbuffer����4KB�ռ�
		buffer = ExAllocatePool(NonPagedPool, 1024 * 4);
		if (buffer == NULL)
		{
			bRet = FALSE;
			break;
		}

		// �����ļ�
		while (1)
		{
			length = 4 * 1024;
			// ��ȡԴ�ļ�
			status = ZwReadFile(hSrcFile,//�ļ����
				NULL,//һ���¼��������첽��ȡ
				NULL,//�ص����̣������첽
				NULL,//��NULL����
				&Io_Status_Block,//����״̬�����ͬ����ʱ��ͬ������
				buffer,//�ļ����ݶ������������
				length,//����������
				&offset,//�ļ�ƫ����
				NULL);//������Ϣ����NULL����
			if (!NT_SUCCESS(status))
			{
				// ���״̬Ϊ STATUS_END_OF_FILE��˵���ļ��Ѿ���ȡ��ĩβ
				if (status == STATUS_END_OF_FILE)
				{
					bRet = TRUE;
					break;
				}
			}

			// ���ʵ�ʶ�ȡ�ĳ���
			length = (ULONG)Io_Status_Block.Information;

			// д�뵽Ŀ���ļ�
			status = ZwWriteFile(hDestFile,
				NULL,
				NULL,
				NULL,
				&Io_Status_Block,
				buffer,
				length,
				&offset,
				NULL);
			if (!NT_SUCCESS(status))
			{
				bRet = FALSE;
				break;
			}

			// �ƶ��ļ�ָ��
			offset.QuadPart += length;
		}
	} while (0);

	if (hSrcFile)
	{
		ZwClose(hSrcFile);
	}
	if (hDestFile)
	{
		ZwClose(hDestFile);
	}
	if (buffer != NULL)
	{
		ExFreePool(buffer);
	}

	return bRet;
}

//ɾ���ļ����ļ���
NTSTATUS ZwDeleteFileFolder(IN PWSTR wsFileName)
{
	NTSTATUS st;
	OBJECT_ATTRIBUTES ObjectAttributes;
	UNICODE_STRING UniFileName;
	WCHAR Buf[256] = { 0 };
	wcscpy(Buf, L"\\??\\");
	wcscat(Buf, wsFileName);

	//�� WCHAR*ת��Ϊ UNICODE_STRING
	RtlInitUnicodeString(&UniFileName, Buf);

	//����OBJECT����ʹ��ZwDeleteFileɾ��
	InitializeObjectAttributes(&ObjectAttributes,
		&UniFileName,
		OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
		NULL,
		NULL);

	return ZwDeleteFile(&ObjectAttributes); 
}

//�������ļ����ļ���
NTSTATUS ZwRenameFile(IN PWSTR DstFileName, IN PWSTR SrcFileName)
{
	UNICODE_STRING ObjectName;
	WCHAR SrcBuf[256] = { 0 };
	WCHAR DestBuf[256] = { 0 };
	wcscpy(SrcBuf, L"\\??\\");
	wcscat(SrcBuf, SrcFileName);
	wcscpy(DestBuf, L"\\??\\");
	wcscat(DestBuf, DstFileName);
	HANDLE FileHandle = NULL;
	OBJECT_ATTRIBUTES ObjectAttributes;
	IO_STATUS_BLOCK IoStatus;
	NTSTATUS Status;
	PFILE_RENAME_INFORMATION RenameInfo = NULL;

	//��������������Ϣ
	RenameInfo = (PFILE_RENAME_INFORMATION)ExAllocatePoolWithTag(NonPagedPool,
		sizeof(FILE_RENAME_INFORMATION) + RN_MAX_PATH * sizeof(WCHAR), SFLT_POOL_TAG);
	if (RenameInfo == NULL)
	{
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	//�����ڴ�
	RtlZeroMemory(RenameInfo, sizeof(FILE_RENAME_INFORMATION) + RN_MAX_PATH *
		sizeof(WCHAR));
	RenameInfo->FileNameLength = wcslen(DestBuf) * sizeof(WCHAR);
	wcscpy(RenameInfo->FileName, DestBuf);
	RenameInfo->ReplaceIfExists = 0;
	RenameInfo->RootDirectory = NULL;

	//����Դ�ļ���Ϣ����þ��
	RtlInitUnicodeString(&ObjectName, SrcBuf);
	InitializeObjectAttributes(&ObjectAttributes,
		&ObjectName,
		OBJ_CASE_INSENSITIVE,
		NULL,
		NULL);

	//�ļ�������
	Status = ZwCreateFile(&FileHandle,
		SYNCHRONIZE | DELETE,
		&ObjectAttributes,
		&IoStatus,
		NULL,
		0,
		FILE_SHARE_READ,
		FILE_OPEN,
		FILE_SYNCHRONOUS_IO_NONALERT |
		FILE_NO_INTERMEDIATE_BUFFERING,
		NULL,
		0);
	if (!NT_SUCCESS(Status))
	{
		ExFreePoolWithTag(RenameInfo, SFLT_POOL_TAG);
		return Status;
	}

	//�����ļ���Ϣ
	Status = ZwSetInformationFile(FileHandle,
		&IoStatus,
		RenameInfo,
		sizeof(FILE_RENAME_INFORMATION) +
		RN_MAX_PATH * sizeof(WCHAR),
		FileRenameInformation);
	if (!NT_SUCCESS(Status))
	{
		ExFreePoolWithTag(RenameInfo, SFLT_POOL_TAG);
		ZwClose(FileHandle);
		return Status;
	}

	ExFreePoolWithTag(RenameInfo, SFLT_POOL_TAG);
	ZwClose(FileHandle);

	return Status;
}

//��ȡ�ļ���С
ULONG64 GetFileSize(PWSTR wsFileName)
{
	IO_STATUS_BLOCK iostatus = { 0 };
	NTSTATUS ntStatus = 0;
	FILE_STANDARD_INFORMATION fsi = { 0 };
	IO_STATUS_BLOCK Io_Status_Block = { 0 };
	HANDLE hFile = NULL;
	OBJECT_ATTRIBUTES obj_attrib;
	UNICODE_STRING UniFileName;
	WCHAR Buf[256] = { 0 };
	wcscpy(Buf, L"\\??\\");
	wcscat(Buf, wsFileName);
	RtlInitUnicodeString(&UniFileName, Buf);
	InitializeObjectAttributes(&obj_attrib,
		&UniFileName,
		OBJ_CASE_INSENSITIVE |//���ֲ����ִ�Сд
		OBJ_KERNEL_HANDLE,//�ں˾�������ù˼�Ȩ������
		NULL,
		NULL);

	//��һ���ļ�
	ntStatus = ZwCreateFile(&hFile,//���ָ��
		GENERIC_READ,//��Ȩ��
		&obj_attrib,//�����ʼ���Ľṹ�壬����������ļ�·��
		&Io_Status_Block,//��ʾ�����Ľ��
		NULL,//�����ļ���ʼ�������С������ϵ�������ļ�����д�ļ�
		FILE_ATTRIBUTE_NORMAL,//�½������ļ����ԣ�һ��Ϊ0����FILE_ATTRIBUTE_NORMAL
		FILE_SHARE_READ,//�������Ȩ��
		FILE_OPEN,//������ļ�
		FILE_NON_DIRECTORY_FILE |
		FILE_SYNCHRONOUS_IO_NONALERT,//��ʾͬ����һ���ļ�������Ŀ¼
		NULL,
		0);
	if (!NT_SUCCESS(ntStatus))
	{
		if (hFile)
			ZwClose(hFile);
		return 0;
	}

	ntStatus = ZwQueryInformationFile(hFile,
		&iostatus,
		&fsi,
		sizeof(FILE_STANDARD_INFORMATION),
		FileStandardInformation);
	if (!NT_SUCCESS(ntStatus))
	{
		ZwClose(hFile);
		return 0;
	}

	if (hFile)
	{
		ZwClose(hFile);
	}

	return fsi.EndOfFile.QuadPart;
}

//ö���ļ�
HANDLE MyFindFirstFile(LPSTR lpDirectory, PFILE_BOTH_DIR_INFORMATION pDir, ULONG uLength)
{
	char strFolder[MAX_PATH2] = { 0 };
	STRING astrFolder;
	UNICODE_STRING ustrFolder;
	OBJECT_ATTRIBUTES oa;
	IO_STATUS_BLOCK ioStatus;
	NTSTATUS ntStatus;
	HANDLE hFind = NULL;
	memset(strFolder, 0, MAX_PATH2);
	strcpy(strFolder, "\\??\\");
	strcat(strFolder, lpDirectory);
	RtlInitString(&astrFolder, strFolder);
	if (RtlAnsiStringToUnicodeString(&ustrFolder, &astrFolder, TRUE) == 0)
	{
		InitializeObjectAttributes(&oa, &ustrFolder, OBJ_CASE_INSENSITIVE, NULL, NULL);
		ntStatus = IoCreateFile(
			&hFind,
			FILE_LIST_DIRECTORY | SYNCHRONIZE | FILE_ANY_ACCESS,
			&oa,
			&ioStatus,
			NULL,
			FILE_ATTRIBUTE_NORMAL,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			FILE_OPEN,	//FILE_OPEN
			FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT | FILE_OPEN_FOR_BACKUP_INTENT,
			NULL,
			0,
			CreateFileTypeNone,
			NULL,
			IO_NO_PARAMETER_CHECKING);
		RtlFreeUnicodeString(&ustrFolder);
		if (ntStatus == 0 && hFind)
		{
			ntStatus = ZwQueryDirectoryFile(
				hFind, // File Handle
				NULL, // Event
				NULL, // Apc routine
				NULL, // Apc context
				&ioStatus, // IoStatusBlock
				pDir, // FileInformation
				uLength, // Length
				FileBothDirectoryInformation, // FileInformationClass
				TRUE, // ReturnSingleEntry
				NULL, // FileName
				FALSE //RestartScan
				);
			if (ntStatus != 0)
			{
				ZwClose(hFind);
				hFind = NULL;
			}
		}
	}

	return hFind;
}

BOOLEAN MyFindNextFile(HANDLE hFind, PFILE_BOTH_DIR_INFORMATION pDir, ULONG uLength)
{
	IO_STATUS_BLOCK ioStatus;
	NTSTATUS ntStatus;
	ntStatus = ZwQueryDirectoryFile(
		hFind, // File Handle
		NULL, // Event
		NULL, // Apc routine
		NULL, // Apc context
		&ioStatus, // IoStatusBlock
		pDir, // FileInformation
		uLength, // Length
		FileBothDirectoryInformation, // FileInformationClass
		FALSE, // ReturnSingleEntry
		NULL, // FileName
		FALSE //RestartScan
		);
	if (ntStatus == 0)
		return TRUE;
	else
		return FALSE;
}

ULONG SearchDirectory(LPSTR lpPath)
{
	ULONG muFileCount = 0;
	HANDLE hFind = NULL;
	PFILE_BOTH_DIR_INFORMATION pDir;
	char* strBuffer = NULL;
	char strFileName[255 * 2];
	ULONG uLength = MAX_PATH2 * 2 + sizeof(FILE_BOTH_DIR_INFORMATION);
	strBuffer = (PCHAR)kmalloc(uLength);
	pDir = (PFILE_BOTH_DIR_INFORMATION)strBuffer;
	hFind = MyFindFirstFile(lpPath, pDir, uLength);
	if (hFind)
	{
		kfree(strBuffer);
		uLength = (MAX_PATH2 * 2 + sizeof(FILE_BOTH_DIR_INFORMATION)) * 0x2000;
		strBuffer = (PCHAR)kmalloc(uLength);
		pDir = (PFILE_BOTH_DIR_INFORMATION)strBuffer;
		if (MyFindNextFile(hFind, pDir, uLength))
		{
			while (TRUE)
			{
				memset(strFileName, 0, 255 * 2);
				memcpy(strFileName, pDir->FileName, pDir->FileNameLength);
				if (strcmp(strFileName, "..") != 0 && strcmp(strFileName, ".") != 0)
				{
					if (pDir->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						DbgPrint("[Ŀ¼]%S\n", strFileName);
					}
					else
					{
						DbgPrint("[�ļ�]%S\n", strFileName);
					}
					muFileCount++;
				}
				if (pDir->NextEntryOffset == 0) 
					break;
				pDir = (PFILE_BOTH_DIR_INFORMATION)((char *)pDir + pDir->NextEntryOffset);
			}
			kfree(strBuffer);
		}
		ZwClose(hFind);
	}

	return muFileCount;
}

#endif
