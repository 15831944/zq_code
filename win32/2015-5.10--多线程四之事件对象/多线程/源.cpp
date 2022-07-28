#include <iostream>
#include <Windows.h>
#include <process.h>
using namespace std;

//�¼�EVENT
//1������
//HANDLE CreateEvent(
//					LPSECURITY_ATTRIBUTES lpEventAttributes,//��ȫ�ȼ���NULL��ʾĬ��
//					BOOL bManualRest,//TRUE��ʾ�ֶ���λ��FALSE��ʾ�Զ���λ��������Զ���λ��
//							��Ը��¼�����WaitForSingleObjec()����Զ�����RestEvent()ʹ�¼���Ϊδ����״̬
//					BOOL bInitialState,//��ʼ״̬��TRUE��ʾ�Ѵ���
//					LPCTSTR lpName//NULL��ʾ�����¼�
//2����һ���¼����
//HANDLE OpenEvent(
//					DWORD dwDesiredAccess,//����Ȩ�ޣ�һ�㴫��EVENT_ALL_ACCESS
//					BOOL bInheritHandle,//�¼�����ļ̳��ԣ���TRUE����
//					LPCTSTR lpName//��ʾ���ƣ���ͬ���̵ĸ��߳̿���ͨ��������ȷ�����Ƿ��ʵ���ͬһ���¼�
//3��������δ����
//SetEvent�������¼�
//RestEvent:���¼���Ϊδ����
//4�������¼�
//CloseHandle()����

//�ؼ��Ͽ��������̼߳�Ļ��⣬������������ͬ��
long g_nNum;
unsigned int __stdcall Fun(void *pPM);
const int THREAD_NUM = 10;
//�ؼ��α�������
CRITICAL_SECTION  g_csThreadCode;
//�¼�����
HANDLE g_hThreadEvent;
int main()
{
	//�ؼ��γ�ʼ��
	g_hThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	InitializeCriticalSection(&g_csThreadCode);
	
	HANDLE  handle[THREAD_NUM];	
	g_nNum = 0;	
	int i = 0;
	while (i < THREAD_NUM) 
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
		WaitForSingleObject(g_hThreadEvent,INFINITE);
		++i;
	}
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);

	DeleteCriticalSection(&g_csThreadCode);
	system("pause");
	return 0;
}
unsigned int __stdcall Fun(void *pPM)
{
	int nThreadNum = *(int *)pPM; 
	SetEvent(g_hThreadEvent);
	Sleep(50);//some work should to do

	EnterCriticalSection(&g_csThreadCode);//��������̻߳�������
	g_nNum++;
	Sleep(0);//some work should to do
	printf("�̱߳��Ϊ%d  ȫ����ԴֵΪ%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);//�뿪�����̻߳�������
	return 0;
}