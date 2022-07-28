#include <iostream>
#include "TcpServer.h"
#include <windows.h>
#include "..\\GameProtocol.h"
#include <map>
#include <time.h>

CTcpServer ts; //������
char map[_GAME_MAP_S]; //��Ϸ��ͼ
std::map<SOCKET, _PLAYER> all_player; //��Ϸ���

void NetData(SOCKET s, char* data, int len)
{
	_GAME_PROTOCOL* pgp = (_GAME_PROTOCOL*)data;
	switch (pgp->id)
	{
	case _TRY_NICK_NAME:
		{
			_C_S_GP1* p = (_C_S_GP1*)data;

			//����ǳ��Ƿ�Ϸ�
			bool ok = true;
			for (std::map<SOCKET, _PLAYER>::iterator it = all_player.begin(); it != all_player.end(); ++it)
			{
				if (strcmp(p->nick_name, it->second.nick_name) == 0)
				{
					ok = false;
					break;
				}
			}

			//�Ϸ����
			if (ok)
			{
				//3��Э��
				_S_C_GP3 scgp3;

				//�õ������
				std::map<SOCKET, _PLAYER>::iterator it = all_player.find(s);

				//�����ǳƵ������
				strcpy_s(it->second.nick_name, 32, p->nick_name);

				//����λ�õ������
				it->second.x = rand() % _GAME_MAP_W;
				it->second.y = rand() % _GAME_MAP_H;
				
				//�õ���ͼ
				for (int i = 0; i < _GAME_MAP_S; ++i)
					scgp3.map[i] = map[i];

				//�õ����
				scgp3.player_num = (int)all_player.size();

				//���������Ϣ
				int i = 0;
				for (std::map<SOCKET, _PLAYER>::iterator it = all_player.begin(); it != all_player.end(); ++it)
					scgp3.player[i++] = it->second;

				ts.SendData(s, (char*)&scgp3, 4 + _GAME_MAP_S + 4 + scgp3.player_num * sizeof(_PLAYER));

				//4��Э��
				_S_C_GP4 scgp4;
				scgp4.new_player = it->second;

				for (std::map<SOCKET, _PLAYER>::iterator it = all_player.begin(); it != all_player.end(); ++it)
				{
					if (it->first != s)
						ts.SendData(it->first, (char*)&scgp4, sizeof(scgp4));
				}
			}
			//�Ƿ����
			else
			{
				//2��Э��
				_S_C_GP2 scgp2;
				ts.SendData(s, (char*)&scgp2, sizeof(scgp2));
			}

			break;
		}
	case _SEND_TALK:
		{
			_C_S_GP5* p = (_C_S_GP5*)data;

			std::map<SOCKET, _PLAYER>::iterator it = all_player.find(s);
			
			//6��Э��
			_S_C_GP6 scgp6;
			strcpy_s(scgp6.talk, 256, it->second.nick_name);
			strcat_s(scgp6.talk, 256, " ˵��");
			strcat_s(scgp6.talk, 256, p->talk);

			for (std::map<SOCKET, _PLAYER>::iterator it = all_player.begin(); it != all_player.end(); ++it)
				ts.SendData(it->first, (char*)&scgp6, sizeof(scgp6));

			break;
		}
	case _SEND_WALK:
		{
			_C_S_GP7* p = (_C_S_GP7*)data;

			//�������λ��
			std::map<SOCKET, _PLAYER>::iterator it = all_player.find(s);
			it->second.x = p->x;
			it->second.y = p->y;
			
			//8��Э��
			_S_C_GP8 scgp8;
			scgp8.player = it->second;

			for (std::map<SOCKET, _PLAYER>::iterator it = all_player.begin(); it != all_player.end(); ++it)
				ts.SendData(it->first, (char*)&scgp8, sizeof(scgp8));

			break;
		}
	}
}

void main()
{
	srand((unsigned int)time(0));

	//��������ʼ��
	ts.Init(12345, _MAX_PLAYER, 10, 10);

	//��Ϸ��ͼ��ʼ��
	int za_num = _GAME_MAP_S / 10;
	for (int i = 0; i < za_num; ++i)
		map[rand() % _GAME_MAP_S] = _ZA;

	while (ts.Continue())
	{
		ts.Run();

		//��ȡ�����¼�
		_TS_NET_EVENT tne;
		while (ts.GetTSNetEvent(&tne))
		{
			char ip[32];
			ts.GetStrIP(tne.ip, ip);
			switch (tne.type)
			{
			case 0:
				{
					//�����װ�����ӳ��
					_PLAYER player = {};
					all_player.insert(std::pair<SOCKET, _PLAYER>(tne.s, player));
					std::cout<<ip<<"���ӽ�����"<<std::endl;
					break;
				}
			case 1:
			case 2:
			case 3:
				{
					//�ҵ����
					std::map<SOCKET, _PLAYER>::iterator it = all_player.find(tne.s);
					_S_C_GP9 scgp9;
					strcpy_s(scgp9.nick_name, 32, it->second.nick_name);

					//ɾ�����
					all_player.erase(it);

					for (std::map<SOCKET, _PLAYER>::iterator it = all_player.begin(); it != all_player.end(); ++it)
						ts.SendData(it->first, (char*)&scgp9, sizeof(scgp9));

					std::cout<<ip<<"�Ͽ���"<<std::endl;
					break;
				}
			case 4:
				{
					NetData(tne.s, tne.data, tne.len);
					std::cout<<"�յ���"<<tne.len<<"���ֽڵ�����"<<std::endl;
					break;
				}
			}
			ts.ReleaseTSNetEvent(&tne);
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 1)
			ts.Stop();
		if (GetAsyncKeyState(VK_RETURN) & 1)
			std::cout<<ts.GetUseMemoryMB()<<std::endl;

		Sleep(1);
	}

	ts.End();

	system("pause");
}