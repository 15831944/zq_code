
�ο����ϣ�http://blog.csdn.net/morewindows/article/details/7392749

#include <windows.h>

#include <process.h>

#include <iostream>

using namespace std;


//CreateThread��_beginthreadex

//�����������ʹ�ñ�׼C���п��еĺ���ʱ������ʹ��_beginthreadex����CreateThread

//HANDLE WINAPI CreateThread(

//			   	LPSECURITY_ATTRIBUTES lpThreadAttributes,//�߳��ں˵İ�ȫ���ԣ�NULL��ʾĬ��

//				SIZE_T dwStackSize,//�߳�ջ�ռ��С��0��ʾĬ�ϴ�С��1M��

//				LPTHREAD_START_ROUTINE lpStartAddress��//ִ�е��̺߳�����ַ������߳̿���ʹ��ͬ��������ַ

//				LPVOID lpParameter��//�����̺߳����Ĳ���

//				DWORD dwCreationFlags��//ָ������ı�־�������̵߳Ĵ�����0��ʾ�̴߳������������Ϳ��Ե��ȣ����Ϊ

//							CREATE_SUSPENDED��ʾ�̴߳�������ͣ���У��������޷����ȣ�ֱ������ResumeThread()

//				LPDWORD lpThreadId,//�������̵߳�ID�ţ�NULL��ʾ����Ҫ�����߳�ID��

//�����ɹ�����һ���µľ����ʧ�ܷ���NULL
//

//HANDLE WINAPI WaitForSingleObject(

//				HANDLE hHandle,//Ҫ�ȴ����ں˶���

//				DWORD dwMilliseconds,//��ȴ�ʱ�䣬����Ϊ��λ������0�������أ�INFINITE��ʾ���޵ȴ�

//��������ֵ��

//WAIT_OBJECT_0:��ָ����ʱ���ڣ����󴥷�

//WAIT_TIMEOUT:�����ʱ�䣬������δ������

//WAIT_FAILED�������������

//һ������������̺߳�������ã���Ϊ�̵߳ľ�����߳�����ʱ��δ�����ģ��߳̽������У�������ڴ���״̬

//����������������Եȴ�һ���߳̽�������


//

#define THREAD_NUM 5

int a=0;

UINT WINAPI  f1(void *);

UINT WINAPI  f2(void*);

void main()
{
	
	HANDLE handle[THREAD_NUM];
	
	for(int i = 0; i < THREAD_NUM; ++i)
		
		handle[i]=(HANDLE)_beginthreadex(0,0, f1, 0,0,0 );
	
	WaitForMultipleObjects(THREAD_NUM,handle,true,INFINITE);
	
	cout<<"�����߳�������ϡ���"<<endl;
	
	for(int i = 0; i < THREAD_NUM; ++i)
		
		CloseHandle(handle[i]);
	
	system("pause");

}

UINT WINAPI  f1(LPVOID lparam)

{
	
	a++;
	
	cout<<"ID��Ϊ"<<GetCurrentThreadId()<<"�����߳����:"<<a<<endl;
	return 0;

}

UINT WINAPI  f2(void *)

{

	
	return 0;

}