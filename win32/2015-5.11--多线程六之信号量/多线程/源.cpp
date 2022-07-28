#include <iostream>
#include <Windows.h>
#include <process.h>
using namespace std;

//�ź���Semaphore
//1������
//HANDLE CreateSemaphore(
//					LPSECURITY_ATTRIBUTES lpEventAttributes,//��ȫ�ȼ���NULL��ʾĬ��
//					LONG lInitialCount,//��ʼ��Դ����
//					LONG lMaximumCount,//��󲢷�����
//					LPCTSTR lpName//�ź������ƣ���������е��߳�ͨ������������ͬһ����������NULL��ʾ�����ź���
//2����һ���ź���
//HANDLE OpenSemaphore(
//					DWORD dwDesiredAccess,//����Ȩ�ޣ�һ�㴫��EVENT_ALL_ACCESS
//					BOOL bInheritHandle,//�ź�������ļ̳��ԣ���TRUE����
//					LPCTSTR lpName//��ʾ���ƣ���ͬ���̵ĸ��߳̿���ͨ��������ȷ�����Ƿ��ʵ���ͬһ���¼�
//3�������ź����ĵ�ǰ��Դ����
//BOOL ReleaseSemaphore(
//						HANDLE hSemaphore,//�ź����������
//						LONG lReleaseCount,//��ʾ���Ӹ������������0���Ҳ����������Դ����
//						LONG lpPreviousCount//����������ǰ����Դ������NULL��ʾ����Ҫ����
//ע�⣺��ǰ��Դ��������0����ʾ�ź������ڴ���������0��ʾ��Դ�Ѿ��ľ����ź�������δ������
//		�ڶ��ź������õȴ�����ʱ���ȴ����������ź����ĵ�ǰ��Դ�������������0�����ź������ڴ���
//		״̬����1�󷵻ؼ����õ����߳�ִ�У�һ���߳̿��Զ�ε��õȴ������������ź���
//4�������ź���
//CloseHandle()����

//�ź������������
//��һ��ͣ����������Ϊ���������������ͣ����ֻ��������λ��һ��ʼ������λ���ǿյġ�
//��ʱ���ͬʱ������������������������������ֱ�ӽ��룬Ȼ����³�����ʣ�µĳ����������ڵȴ���
//�˺����ĳ�Ҳ�����ò�����ڴ��ȴ�����ʱ����һ�����뿪ͣ�����������˵�֪�󣬴򿪳�����
//���������һ����ȥ��������뿪���������ֿ��Է������������������
//�����ͣ����ϵͳ�У���λ�ǹ�����Դ��ÿ�����ñ�һ���̣߳���������ľ����ź��������á�
//������������ź������������£��ź�����һ���Ǹ���������λ������
//����ͨ�������߳�/���̣����������Ὣ��������һ��ͨ������Ȼ��Ϊ��ʹ����Դ������������ֵΪ��ʱ��
//������ͼͨ�������̶߳������ڵȴ�״̬�����ź��������Ƕ������ֲ����� Wait���ȴ��� �� Release���ͷţ���
//��һ���̵߳���Wait����ʱ����Ҫô�õ���ԴȻ���ź�����һ��Ҫôһֱ����ȥ��ָ�����������У���
//ֱ���ź������ڵ���һʱ��Release���ͷţ�ʵ���������ź�����ִ�мӲ�����
//��Ӧ�ڳ����뿪ͣ�������ò���֮���Խ������ͷš�����Ϊ�ͷ������ź����ػ�����Դ��
long g_nNum;
unsigned int __stdcall Fun(void *pPM);
const int THREAD_NUM = 10;
//�ؼ��α�������
CRITICAL_SECTION  g_csThreadCode;
//�ź���
HANDLE g_hThreadSemaphore;
int main()
{
	//��ǰ0����Դ���������һ��ͬʱ����
	g_hThreadSemaphore = CreateSemaphore(NULL,0, 1, NULL);
	//�ؼ��γ�ʼ��
	InitializeCriticalSection(&g_csThreadCode);
	
	HANDLE  handle[THREAD_NUM];	
	g_nNum = 0;	
	int i = 0;
	while (i < THREAD_NUM) 
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
		WaitForSingleObject(g_hThreadSemaphore,INFINITE);
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
	//�ź���++
	ReleaseSemaphore(g_hThreadSemaphore,1,NULL);
	Sleep(50);//some work should to do

	EnterCriticalSection(&g_csThreadCode);//��������̻߳�������
	g_nNum++;
	Sleep(0);//some work should to do
	printf("�̱߳��Ϊ%d  ȫ����ԴֵΪ%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);//�뿪�����̻߳�������
	return 0;
}