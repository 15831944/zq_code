#include <iostream>
#include <Windows.h>
#include <process.h>
using namespace std;

//�������Mutex)
//1������
//HANDLE CreateMutex(
//					LPSECURITY_ATTRIBUTES lpEventAttributes,//��ȫ�ȼ���NULL��ʾĬ��
//					BOOL bInitialOwner,//�������ĳ�ʼӵ���ߣ�TRUE��ʾ�����������ڲ����¼���������̵߳��߳�ID����
//										�ݹ��������Ϊ1�����ڸ��߳�ID��0�����Ի���������δ����״̬��FALSE��ʾ�����������ڲ�
//										���߳�ID������ΪNULL���ݹ����Ϊ0������ζ�Ż�������Ϊ�κ��߳�ռ�ã����ڴ���״̬
//					LPCTSTR lpName//���������ƣ���������е��߳�ͨ������������ͬһ����������NULL��ʾ�����¼�
//2����һ���¼����
//HANDLE OpenEvent(
//					DWORD dwDesiredAccess,//����Ȩ�ޣ�һ�㴫��EVENT_ALL_ACCESS
//					BOOL bInheritHandle,//����������ļ̳��ԣ���TRUE����
//					LPCTSTR lpName//��ʾ���ƣ���ͬ���̵ĸ��߳̿���ͨ��������ȷ�����Ƿ��ʵ���ͬһ���¼�
//3������������
//ReleaseMutex(HANDLE hMutex)
//���ʻ�����ԴǰӦ���õȴ���������������Ӧ�õ��øú�����ʾ�Լ��Ѿ��������ʣ������߳̿��Կ�ʼ������
//4�������¼�
//CloseHandle()����


//�Ӹô�����Կ������������͹ؼ������ƣ�Ҳ���ܽ���̼߳��ͬ������
//���������ܹ��������ĳ����������ֹ����ɵ��������⣬����һ����������̴߳�����
//��û�б��ͷ�ǰ,���̱߳�������ֹ����ʱϵͳ���Զ�ѡ��һ���߳�����ɵ��ȣ�
//��ʱ��WaitForSingleObject()�᷵��WAIT_ABANDONED_0

long g_nNum;
unsigned int __stdcall Fun(void *pPM);
const int THREAD_NUM = 10;
//�ؼ��α�������
CRITICAL_SECTION  g_csThreadCode;
//�������
HANDLE g_hThreadMutex;
int main()
{
	//�ؼ��γ�ʼ��
	g_hThreadMutex = CreateMutex(NULL, FALSE, NULL);
	InitializeCriticalSection(&g_csThreadCode);
	
	HANDLE  handle[THREAD_NUM];	
	g_nNum = 0;	
	int i = 0;
	while (i < THREAD_NUM) 
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
		WaitForSingleObject(g_hThreadMutex,INFINITE);
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
	ReleaseMutex(g_hThreadMutex);
	Sleep(50);//some work should to do

	EnterCriticalSection(&g_csThreadCode);//��������̻߳�������
	g_nNum++;
	Sleep(0);//some work should to do
	printf("�̱߳��Ϊ%d  ȫ����ԴֵΪ%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);//�뿪�����̻߳�������
	return 0;
}