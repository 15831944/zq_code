#include <iostream>
#define _WIN32_WINNT 0x0500
#include <Winsock2.h>

void main()
{
	//�õ�����̨�Ĵ��ھ��
	HWND hwnd = GetConsoleWindow();

	//�õ�ϵͳ�е�ǰ̨���ڵľ��
	while (1)
	{
		if (hwnd == GetForegroundWindow())
			std::cout<<"ǰ̨��";
		else
			std::cout<<"��̨��";
		Sleep(33);
	}
	
	system("pause");
}