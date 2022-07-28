#include <iostream>
#include "ScmDrvCtrl.h"
#pragma comment(lib,"user32.lib")

void GetAppPath(char *szCurFile)
{
	//����б��
	GetModuleFileNameA(0, szCurFile, MAX_PATH);
	for (SIZE_T i = strlen(szCurFile) - 1; i >= 0; i--)
	{
		if (szCurFile[i] == '\\')
		{
			szCurFile[i + 1] = '\0';
			break;
		}
	}
}

int main()
{
	BOOL b;
	cDrvCtrl dc;

	//������������
	char szSysFile[MAX_PATH] = {};
	char szSvcLnkName[] = "MyDriver";
	GetAppPath(szSysFile);
	strcat_s(szSysFile, "MyDriver.sys");

	//��װ����������
	b = dc.Install(szSysFile, szSvcLnkName, szSvcLnkName);
	b = dc.Start();
	printf("LoadDriver=%d\n", b);

	//���򿪡������ķ�������
	dc.Open("\\\\.\\MyDriver");

	//ʹ�ÿ��������������0x800������һ�����ֲ�����һ�����֣�
	DWORD x = 100, y = 0, z = 0;
	dc.IoControl(0x800, &x, sizeof(x), &y, sizeof(y), &z);
	printf("INPUT=%ld\nOUTPUT=%ld\nReturnBytesLength=%ld\n", x, y, z);

	//ʹ�ÿ��������������0x801����DBGVIEW����ʾHELLOWORLD��
	dc.IoControl(0x801, 0, 0, 0, 0, 0);

	//�رշ������Ӿ��
	dc.CloseDrvHandle();

	//ֹͣ��ж������
	b = dc.Stop();
	b = dc.Remove();
	printf("UnloadDriver=%d\n", b);

	getchar();
	return 0;
}