#include <windows.h>

#include <process.h>

#include <iostream>

using namespace std;


//����������У��п��ܻ�������ݶ�Ӧ���������Ϊһ����������������������������

//�������ݺ��п��������й����б��ı䣬��������Ӧ�ö�һ��ֵ�Ĳ���ʱ����ԭ�Ӳ����������ɴ���ԣ�

//Windowsϵͳ�ṩ��Interlocked��ͷ�ĺ��������һ����

//1����������

//LONG __cdecl InterlockedIncrement(LONG volatile* Addend);
//LONG __cdecl InterlockedDecrement(LONG volatile* Addend);
//���ر���ִ����������֮���ֵ��

//LONG __cdec  InterlockedExchangeAdd(LONG volatile* Addend, LONGValue);
//����������ֵ��ע�⣡�Ӹ��������Ǽ�

//2����ֵ����
//LONG __cdecl InterlockedExchange(LONG volatile* Target, LONGValue);
//Value������ֵ�������᷵��ԭ�ȵ�ֵ��

#define THREAD_NUM 50

int a=0;

UINT WINAPI  f1(void *);
UINT WINAPI  f2(void*);

void main()

{
	
	HANDLE handle[THREAD_NUM];
	
	for(int j = 0;j < 20; ++ j)
	
	{
		
		a = 0;
		
		for(int i = 0; i < THREAD_NUM; ++i)
			
			handle[i]=(HANDLE)_beginthreadex(0,0, f1, 0,0,0 );
		
		WaitForMultipleObjects(THREAD_NUM,handle,true,INFINITE);
		
	cout<<"������"<<THREAD_NUM<<"���̣߳�a����ֵΪ��"<<a<<endl;
	
	}
	
	cout<<"�����߳�������ϡ���"<<endl;
	
	for(int i = 0; i < THREAD_NUM; ++i)
		
		CloseHandle(handle[i]);
	
	system("pause");

}

UINT WINAPI  f1(LPVOID lparam)

{
	
	Sleep(100);
	//a++;
	
	InterlockedIncrement((LPLONG)&a);
	
	return 0;

}

UINT WINAPI  f2(void *)

{

	
	return 0;

}