#include<iostream>
#include<time.h>
#include <windows.h>

#include "dds.h"

#define _GAME_CHOOSE	-1
#define _GAME_INIT		0
#define _GAME_RUN		1

//��Ϸ���-���Ƶ�ͼ����ʾ�����Ϣ
void Game_Output()
{
	system("cls");
	//for(int i = 0; i < _MAP_S;++i)
	//{
	//	switch(map[i])
	//	{
	//	case _KD:std::cout<<"��";break;
	//	case _LS:std::cout<<"��";break;
	//	case _GJ:std::cout<<"��";break;
	//	case _SW:std::cout<<"��";break;
	//	}
	//	if(i % _MAP_W == _MAP_W - 1)
	//		std::cout<<std::endl;
	//}
	const char* dy[] = {"��","��","��","��"};
	for(int i = 0; i < _MAP_S;++i)
	{
		std::cout<<dy[map[i]];
		if(i % _MAP_W == _MAP_W - 1)
			std::cout<<std::endl;
	}
	std::cout<<"HP:"<<hp<<"Score:"<<score<<std::endl;
}

//��Ϸ����-��������
void Game_Input()
{
	//if(GetAsyncKeyState(VK_NUMPAD1) & 1)
	//	input[6] = true;
	//if(GetAsyncKeyState(VK_NUMPAD2) & 1)
	//	input[7] = true;
	//if(GetAsyncKeyState(VK_NUMPAD3) & 1)
	//	input[8] = true;
	//if(GetAsyncKeyState(VK_NUMPAD4) & 1)
	//	input[3] = true;
	//if(GetAsyncKeyState(VK_NUMPAD5) & 1)
	//	input[4] = true;
	//if(GetAsyncKeyState(VK_NUMPAD6) & 1)
	//	input[5] = true;
	//if(GetAsyncKeyState(VK_NUMPAD7) & 1)
	//	input[0] = true;
	//if(GetAsyncKeyState(VK_NUMPAD8) & 1)
	//	input[1] = true;
	//if(GetAsyncKeyState(VK_NUMPAD9) & 1)
	//	input[2] = true;
	const int Key[] = 
	{
		VK_NUMPAD7,VK_NUMPAD8,VK_NUMPAD9,
		VK_NUMPAD4,VK_NUMPAD5,VK_NUMPAD6,
		VK_NUMPAD1,VK_NUMPAD2,VK_NUMPAD3
	};
	for(int i = 0; i < 9;++i)
	{
		input[i] = GetAsyncKeyState(Key[i])&1; 
	}
}

//�ж��Ƿ�ʤ��-����1ʤ��������0ʧ�ܣ���������
int IsWin()
{
	if(score >= 50)
		return 1;
	if(hp <= 0)
		return 0;
	return -1;
}

//��Ϸѡ��
int GameChoose()
{
	std::cout<<"�����"<<std::endl;
	std::cout<<"01)������Ϸ"<<std::endl;
	std::cout<<"02)�˳�"<<std::endl;
	int input;
	std::cin>>input;
	return input;
}

void main()
{
	srand((unsigned int)time(0));
	int GameState = _GAME_CHOOSE;
	
	while(1)
	{
		if(GameState == _GAME_CHOOSE)
		{
			int state = GameChoose(); 
			if(state == 1)
				GameState = _GAME_INIT;
			else if(state == 2)
				break;
		}
		else if(GameState == _GAME_INIT)
		{
			Game_Init();
			GameState = _GAME_RUN;
		}
		else if(GameState == _GAME_RUN)
		{
			Game_Output();
			Game_Input();
			Game_Logic();
			if(IsWin() == 0 || IsWin() == 1)
			{
				GameState = _GAME_CHOOSE;
				system("cls");
			}
		}
		Sleep(40);
	}
	system("pause");
}