#ifndef SCM_DRV_CTRL_H
#define SCM_DRV_CTRL_H

#include <windows.h>
#pragma comment(lib,"advapi32.lib")

class cDrvCtrl
{
public:
	cDrvCtrl();
	~cDrvCtrl();
private:

	//������
	DWORD m_dwLastError;

	//�����ļ�·��
	PCHAR m_pSysPath;

	//������
	PCHAR m_pServiceName;

	//�û�������ʾ��
	PCHAR m_pDisplayName;

	//�������Ӿ�����
	HANDLE m_hDriver;

	//������ƹ��������
	SC_HANDLE m_hSCManager;

	//������������
	SC_HANDLE m_hService;
public:

	//��װ����
	BOOL Install(PCHAR pSysPath, PCHAR pServiceName, PCHAR pDisplayName);

	//��������
	BOOL Start();

	//��ͣ����
	BOOL Stop();

	//ж������
	BOOL Remove();

	//"��"�����ķ�������,�൱�ڻ��һ��������ͨ�ŵľ��
	BOOL Open(PCHAR pLinkName);

	//����������IO����
	BOOL IoControl(DWORD dwIoCode, PVOID InBuff, DWORD InBuffLen, PVOID OutBuff, DWORD OutBuffLen, DWORD *RealRetBytes);

	//�رշ������Ӿ��
	void CloseDrvHandle();

private:

	//ͨ������������÷�����
	BOOL GetSvcHandle(PCHAR pServiceName);

	//����IO���ƴ���
	DWORD CTL_CODE_GEN(DWORD lngFunction);
};



#endif
