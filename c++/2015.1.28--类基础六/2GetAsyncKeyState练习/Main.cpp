#include <iostream>
#include <windows.h>
#include "GameInput.h"

CGameInput* gi = 0;

void f()
{
	int Key[] = {VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_RETURN, VK_ESCAPE};
	gi = new CGameInput(Key, sizeof(Key) / sizeof(int));
}

void main()
{
	
	//CGameInput gi(Key, sizeof(Key) / sizeof(int));
	f();
	while (1)
	{
		gi->Run();

		if (_KS_KEEP_DOWN == gi->KeyState(0))
			std::cout<<"��������UP"<<std::endl;
		if (_KS_KEEP_DOWN == gi->KeyState(1))
			std::cout<<"��������DOWN"<<std::endl;
		if (_KS_KEEP_DOWN == gi->KeyState(2))
			std::cout<<"��������LEFT"<<std::endl;
		if (_KS_KEEP_DOWN == gi->KeyState(3))
			std::cout<<"��������RIGHT"<<std::endl;
		if (_KS_NOW_DOWN == gi->KeyState(4))
			std::cout<<"��ǰ����ENTER"<<std::endl;
		if (_KS_NOW_UP == gi->KeyState(5))
		{
			std::cout<<"��ǰ̧��ESC"<<std::endl;
			break;
		}

		Sleep(33);
	}
	delete gi;

	system("pause");
}