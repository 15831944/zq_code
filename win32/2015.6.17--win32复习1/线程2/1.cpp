#include <iostream>
#include <conio.h>
#include <windows.h>
#include <process.h>

//һ��C���Դ�����Ա�����ɶ������䣬��������
//�ǲ����ٷֵģ������̵߳��л�һ����һ����ִ�����
//֮���л�������C���Դ���ִ������л�

//�ٽ���������߳�����ͬһʱ��ֻ����һ���߳̽����ٽ���
CRITICAL_SECTION cs;

unsigned int __stdcall music(void* p)
{
	while (1)
	{
		EnterCriticalSection(&cs); //���ٽ���

		std::cout<<"abc";
		std::cout<<"def"<<std::endl;
		Sleep(200);

		LeaveCriticalSection(&cs); //���ٽ���
	}
}

void main()
{
	InitializeCriticalSection(&cs); //��ʼ���ٽ���

	_beginthreadex(
		0,
		0,
		music,
		0,
		0,
		0);

	while (1)
	{
		EnterCriticalSection(&cs); //���ٽ���

		std::cout<<"123";
		std::cout<<"456"<<std::endl;
		Sleep(200);

		LeaveCriticalSection(&cs); //���ٽ���
	}

	DeleteCriticalSection(&cs); //ɾ���ٽ���
}