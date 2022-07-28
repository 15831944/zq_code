#include <iostream>
#include <Windows.h>
#include <process.h>
using namespace std;

//�ٽ������ؼ��ϴ���CS��
//1����ʼ��
//void InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
//2������ؼ�����
//void EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
//3���뿪�ؼ�����
//LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
//4�����ٹؼ�����
//DaleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection)

//�ؼ��Ͽ��������̼߳�Ļ��⣬������������ͬ��
long g_nNum;
unsigned int __stdcall Fun(void *pPM);
const int THREAD_NUM = 10;
//�ؼ��α�������
CRITICAL_SECTION  g_csThreadParameter, g_csThreadCode;
int main()
{
	//�ؼ��γ�ʼ��
	InitializeCriticalSection(&g_csThreadParameter);
	InitializeCriticalSection(&g_csThreadCode);
	
	HANDLE  handle[THREAD_NUM];	
	g_nNum = 0;	
	int i = 0;
	while (i < THREAD_NUM) 
	{
		EnterCriticalSection(&g_csThreadParameter);//�������߳���Źؼ�����
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
		++i;
	}
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);

	DeleteCriticalSection(&g_csThreadCode);
	DeleteCriticalSection(&g_csThreadParameter);
	system("pause");
	return 0;
}
unsigned int __stdcall Fun(void *pPM)
{
	int nThreadNum = *(int *)pPM; 
	LeaveCriticalSection(&g_csThreadParameter);//�뿪���߳���Źؼ�����

	Sleep(50);//some work should to do

	EnterCriticalSection(&g_csThreadCode);//��������̻߳�������
	g_nNum++;
	Sleep(0);//some work should to do
	printf("�̱߳��Ϊ%d  ȫ����ԴֵΪ%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);//�뿪�����̻߳�������
	return 0;
}