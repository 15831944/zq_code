#include <windows.h>
#include <iostream>
#include <vector>
#include <io.h>
#include "GameClass.h"

struct GAME
{
	HINSTANCE dll;
	CGameClass* game;
};
std::vector<GAME> game; //������Ϸ

void findGame()
{
	//�ͷ������Ѿ����ص���Ϸ
	for (int i = 0; i < (int)game.size(); ++i)
	{
		FreeLibrary(game[i].dll);
		delete game[i].game;
	}
	game.clear();

	//����Ŀ¼�õ�������Ϸ
	_finddata_t fd;
	intptr_t fr = _findfirst("game\\*.dll", &fd);
	if (-1 != fr)
	{
		do
		{
			//�õ���Ϸ�ļ���·��
			char gd[256] = "game\\";
			strcat_s(gd, 256, fd.name);

			//����Ϸ�ļ�����ȡ��Ϸ
			HINSTANCE gamedll = LoadLibraryA(gd);

			//�õ�getGame�������׵�ַ��ע���������
			//�������Ѿ���C++�������޸�Ϊ?getGame@@YAPAVCGameClass@@XZ
			FARPROC funadd = GetProcAddress(gamedll, "?getGame@@YAPAVCGameClass@@XZ");
			typedef CGameClass* (* funtype)(); //funtype��һ������ָ������
			funtype fun = (funtype)funadd; //��funtypeǿת�õ����׵�ַ

			//���ú����õ���Ϸ����
			GAME g = {gamedll, (*fun)()};
			game.push_back(g);
			
		} while (0 == _findnext(fr, &fd));
	}
}

void main()
{
	while (1)
	{
		//�õ�������Ϸ
		findGame();

		//��ӡ��Ϸ
		for (int i = 0; i < game.size(); ++i)
			std::cout<<i<<")"<<game[i].game->name()<<std::endl;

		//ѡ����Ϸ
		int s;
		do
		{
			std::cout<<"��ѡ��";
			std::cin>>s;
		} while (s < 0 || s >= game.size());
		
		//������Ϸ
		game[s].game->init();
		game[s].game->run();
		game[s].game->end();
	}

	system("pause");
}