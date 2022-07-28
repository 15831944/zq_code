#include <ntddk.h>

//1.�ַ�����ʼ��
VOID StringInitTest()
{
	//�ַ�����ʼ��(1)
	UNICODE_STRING str;
	str.Buffer = L"hello world0!";
	str.Length = str.MaximumLength = wcslen(L"hello world0") * sizeof(WCHAR);
	DbgPrint("%wZ", &str);

	//�ַ�����ʼ��(2)
	RtlInitUnicodeString(&str, L"hello");
	DbgPrint("%wZ", &str);

	//��ʼ��һ�������ַ������õ��ĺ�
	UNICODE_STRING str1 = RTL_CONSTANT_STRING(L"hello world2!");
	DbgPrint("%wZ", &str1);
}

//2.�ַ�������
VOID StringCopyTest()
{
	//�ַ����Ŀ���
	UNICODE_STRING des;
	WCHAR buf[32];
	UNICODE_STRING src = RTL_CONSTANT_STRING(L"hello world3!");
	RtlInitEmptyUnicodeString(&des, buf, sizeof(buf));
	RtlCopyUnicodeString(&des, &src);
	DbgPrint("%wZ", &des);
}

//3.�ַ�������
VOID StringCatTest()
{
	NTSTATUS status;
	WCHAR buf[32];
	UNICODE_STRING des;
	UNICODE_STRING src = RTL_CONSTANT_STRING(L"hello world4!");
	RtlInitEmptyUnicodeString(&des, buf, sizeof(buf));
	status = RtlAppendUnicodeStringToString(&des, &src);
	if (status == STATUS_BUFFER_TOO_SMALL)
	{
		DbgPrint(L"StringCatTest: STATUS_BUFFER_TOO_SMALL");
	}
	status = RtlAppendUnicodeToString(&des, L"987");
	if (status == STATUS_BUFFER_TOO_SMALL)
	{
		DbgPrint(L"StringCatTest: STATUS_BUFFER_TOO_SMALL");
	}
	DbgPrint("%wZ", &des);
}

//4.�ַ����Ƚ�
VOID StringCompareTest()
{
	UNICODE_STRING UnicodeString1;
	UNICODE_STRING UnicodeString2;
	RtlInitUnicodeString(&UnicodeString1, L"Hello World");
	RtlInitUnicodeString(&UnicodeString1, L"Hello");
	if (RtlEqualUnicodeString(&UnicodeString1, &UnicodeString2, TRUE))
		DbgPrint("UnicodeString1 and UnicodeString2 are equal\n");
	else
		DbgPrint("UnicodeString1 and UnicodeString2 are NOT equal\n");
}

//5.�ַ������д
VOID StringToUpperTest()
{
	//��ʼ��UnicodeString1
	UNICODE_STRING UnicodeString1;
	UNICODE_STRING UnicodeString2;
	RtlInitUnicodeString(&UnicodeString1, L"Hello World");

	//�仯ǰ
	DbgPrint("UnicodeString1:%wZ\n", &UnicodeString1);

	//���д
	RtlUpcaseUnicodeString(&UnicodeString2, &UnicodeString1, TRUE);

	//�仯��
	DbgPrint("UnicodeString2:%wZ\n", &UnicodeString2);

	//����UnicodeString2��UnicodeString1�������٣�
	RtlFreeUnicodeString(&UnicodeString2);
}

//6.�ַ����������໥ת��
VOID StringToIntegerTest()
{
	//(1)�ַ���ת��������
	{
		UNICODE_STRING UnicodeString1;
		ULONG lNumber;
		NTSTATUS nStatus;

		//��ʼ��UnicodeString1
		RtlInitUnicodeString(&UnicodeString1, L"-100");
		nStatus = RtlUnicodeStringToInteger(&UnicodeString1, 10, &lNumber);
		if (NT_SUCCESS(nStatus))
		{
			DbgPrint("Conver to integer succussfully!\n");
			DbgPrint("Result:%d\n", lNumber);
		}
		else
		{
			DbgPrint("Conver to integer unsuccessfully!\n");
		}
	}
	//(2)����ת�����ַ���
	{
		NTSTATUS nStatus;
		UNICODE_STRING UnicodeString2 = { 0 };
		//��ʼ��UnicodeString2
		UnicodeString2.Buffer = (PWSTR)ExAllocatePool(PagedPool, 1024);
		UnicodeString2.MaximumLength = 1024;
		nStatus = RtlIntegerToUnicodeString(200, 10, &UnicodeString2);
		if (NT_SUCCESS(nStatus))
		{
			DbgPrint("Conver to string succussfully!\n");
			DbgPrint("Result:%wZ\n", &UnicodeString2);
		}
		else
		{
			DbgPrint("Conver to string unsuccessfully!\n");
		}

		//����UnicodeString2
		//ע��!!UnicodeString1��������
		RtlFreeUnicodeString(&UnicodeString2);
	}
}

//7. ANSI_STRING�ַ�����UNICODE_STRING�ַ����໥ת��
VOID StringConverTest()
{
	//(1)��UNICODE_STRING�ַ���ת����ANSI_STRING�ַ���
	UNICODE_STRING UnicodeString1;
	ANSI_STRING AnsiString1;
	NTSTATUS nStatus;

	//��ʼ��UnicodeString1
	RtlInitUnicodeString(&UnicodeString1, L"Hello World");
	nStatus = RtlUnicodeStringToAnsiString(&AnsiString1, &UnicodeString1, TRUE);
	if (NT_SUCCESS(nStatus))
	{
		DbgPrint("Conver succussfully!\n");
		DbgPrint("Result:%Z\n", &AnsiString1);
	}
	else
	{
		DbgPrint("Conver unsuccessfully!\n");
	}

	//����AnsiString1
	RtlFreeAnsiString(&AnsiString1);

	//(2)��ANSI_STRING�ַ���ת����UNICODE_STRING�ַ���
	{
		ANSI_STRING AnsiString2;
		UNICODE_STRING UnicodeString2;
		NTSTATUS nStatus;
		//��ʼ��AnsiString2
		RtlInitString(&AnsiString2, "Hello World");
		nStatus = RtlAnsiStringToUnicodeString(&UnicodeString2, &AnsiString2, TRUE);
		if (NT_SUCCESS(nStatus))
		{
			DbgPrint("Conver succussfully!\n");
			DbgPrint("Result:%wZ\n", &UnicodeString2);
		}
		else
		{
			DbgPrint("Conver unsuccessfully!\n");
		}

		//����UnicodeString2
		RtlFreeUnicodeString(&UnicodeString2);
	}
}


//UNICODE_STRINGzת��ΪCHAR*
//����UNICODE_STRING��ָ�룬���խ�ַ�����BUFFER��Ҫ�Ѿ�����ÿռ�
VOID UnicodeToChar(PUNICODE_STRING dst, PCHAR src)
{
	ANSI_STRING string;
	RtlUnicodeStringToAnsiString(&string, dst, TRUE);
	strcpy(src, string.Buffer);
	RtlFreeAnsiString(&string);
}

//WCHAR*ת��ΪCHAR*
//������ַ����׵�ַ�����խ�ַ�����BUFFER��Ҫ�Ѿ�����ÿռ�
VOID WcharToChar(PWCHAR src, PCHAR dst)
{
	UNICODE_STRING uString;
	ANSI_STRING aString;
	RtlInitUnicodeString(&uString, src);
	RtlUnicodeStringToAnsiString(&aString, &uString, TRUE);
	strcpy(dst, aString.Buffer);
	RtlFreeAnsiString(&aString);
}
//CHAR*תWCHAR*
//����խ�ַ����׵�ַ��������ַ�����BUFFER��Ҫ�Ѿ�����ÿռ�
VOID CharToWchar(PCHAR src, PWCHAR dst)
{
	UNICODE_STRING uString;
	ANSI_STRING aString;
	RtlInitAnsiString(&aString, src);
	RtlAnsiStringToUnicodeString(&uString, &aString, TRUE);
	wcscpy(dst, uString.Buffer);
	RtlFreeUnicodeString(&uString);
}

VOID DriverUnload(PDRIVER_OBJECT driver)
{
	DbgPrint("DriverUnload!\n");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING reg_path)
{
	DbgPrint("DriverEntry!\n");

	StringInitTest();
	StringCopyTest();
	StringCatTest();
	StringCompareTest();
	StringToUpperTest();
	StringToIntegerTest();
	StringConverTest();

	driver->DriverUnload = DriverUnload;
	
	return STATUS_SUCCESS;
}