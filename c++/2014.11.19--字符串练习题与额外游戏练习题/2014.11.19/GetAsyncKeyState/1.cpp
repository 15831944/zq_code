#include <iostream>
#include <windows.h>

void main()
{
	//GetAsyncKeyState()

	while(1)
	{
		//��ĸ���ļ������Ǹ���ĸ�Ĵ�д�����泣��
		if(GetAsyncKeyState('A') & 0x8000)
			std::cout<<"A"<<std::endl;
		if(GetAsyncKeyState('1') & 0x8000)
			std::cout<<"�����1"<<std::endl;
		if(GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
			std::cout<<"С����1"<<std::endl;
		if(GetAsyncKeyState(VK_RETURN) & 0x8000)
			std::cout<<"�س���"<<std::endl;
		if(GetAsyncKeyState(VK_SPACE) & 0x8000)
			std::cout<<"�ո��"<<std::endl;
		if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			std::cout<<"Esc��"<<std::endl;
		if(GetAsyncKeyState(VK_UP) & 0x8000)
			std::cout<<"UP��"<<std::endl;
		if(GetAsyncKeyState(VK_DOWN) & 0x8000)
			std::cout<<"DOWN��"<<std::endl;
		if(GetAsyncKeyState(VK_LEFT) & 0x8000)
			std::cout<<"LEFT��"<<std::endl;
		if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
			std::cout<<"RIGHT��"<<std::endl;

		//ʹ��ǰ�ĳ�����Ϣָ���ĺ�����
		//ָ֡һ����ִ�ж��ٴ���Ϸѭ��
		Sleep(200);
	}
	system("pause");
}