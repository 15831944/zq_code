#define _WIN32_WINNT 0x0500
#include "DataType.h"
#include "FileData.h"
#include "ProtocolFilter.h"
#include "TcpServer.h"
#include <iostream>
#include "BlackJack.h"
#include <ctime>

#define _BACKUP_TIME (1000 * 60 * 10)

CTcpServer ts;
std::map<std::string, _PLAYER> m_ID_Password;
std::map<std::string, _PLAYER> m_Clients;
_ROOM m_Rooms[_ROOM_NUM];
std::map<int,CBlackJack> m_Games;

void ClientDisconnect(SOCKET s);
void UpdatePlayerData(_PLAYER& player);

int backup = 0;

void main()
{
	
	HWND hwnd = GetConsoleWindow();
	//���ļ��ж�ȡ�˺ź�����
	GetIDPasswordFromFile(_CLIENT_INFO_FILE, &m_ID_Password);
	
	//����������
	ts.Init(12345, 256, 10, 5);

	std::cout<<"��Ϸ������������"<<std::endl;

	for(int i = 0; i < _ROOM_NUM; ++i)
	{
		m_Rooms[i].m_RoomState = _RS_WAIT;
		m_Rooms[i].player[0] = m_Rooms[i].player[1] = 0;
	}

	srand(unsigned int(time(0)));
	//ҵ��ѭ��
	while (ts.Continue())
	{
		//�Զ�����
		if(++backup == _BACKUP_TIME)
		{
			backup = 0��
			SaveFile(_CLIENT_INFO_FILE, &m_ID_Password);
		}

		//����������
		ts.Run();

		//�����¼�����
		_SNET_EVENT ne;
		while (ts.GetNetEvent(&ne))
		{
			//���������¼�
			char ip[16];

			switch (ne.type)
			{
			case _SNE_CONNECTED:
				{
					std::cout << CTcpServer::ulong_str(ne.ip, ip) << "���ӵ�������" << std::endl;							 
					break;
				}
			case _SNE_DATA:
				{
					ProtocolDispatcher(ne);
					break;
				}
			case _SNE_DISCONNECTED_C:
				{
					ClientDisconnect(ne.s);
					std::cout << CTcpServer::ulong_str(ne.ip, ip) << "�����Ͽ�" << std::endl;
					break;
				}
			case _SNE_DISCONNECTED_S:
			case _SNE_DISCONNECTED_E:
				{
					ClientDisconnect(ne.s);
					std::cout << CTcpServer::ulong_str(ne.ip, ip) << "�����Ͽ�" << std::endl;
					break;
				}
			}
			ts.ReleaseNetEvent(&ne);
		}
		if (GetAsyncKeyState(VK_ESCAPE) && (hwnd == GetForegroundWindow()))
			ts.Stop();
	}

	ts.End();

	SaveFile(_CLIENT_INFO_FILE, &m_ID_Password);

	system("pause");
}

void ClientDisconnect(SOCKET s)
{
	std::map<std::string, _PLAYER>::iterator it = m_Clients.begin();

	SC_PLAYER_OFFLINE sc_po;
	for(;it != m_Clients.end(); ++it)
	{
		if (it->second.m_socket == s)
		{
			strcpy_s(sc_po.ID,32,it->second.m_ID.c_str());

			if(it->second.m_RoomNum != -1)
			{
				if(it->second.m_PlayState == _PS_PLAYING)
				{
					std::map<int,CBlackJack>::iterator git = m_Games.find(it->second.m_RoomNum);
					if(git != m_Games.end())
					{
						if(it->second.m_SiteNum == 0)
						{
							int score = m_Rooms[it->second.m_RoomNum].player[0]->m_Score / 50;
							m_Rooms[it->second.m_RoomNum].player[0]->m_Lose += 1;
							m_Rooms[it->second.m_RoomNum].player[0]->m_Score -= score;
							std::cout<<"���"<<m_Rooms[it->second.m_RoomNum].player[0]->m_ID<<"�����ˣ�";

							m_Rooms[it->second.m_RoomNum].player[1]->m_Win += 1;
							m_Rooms[it->second.m_RoomNum].player[1]->m_Score += score;
							m_Rooms[it->second.m_RoomNum].player[1]->m_PlayState = _PS_WAIT;
							std::cout<<"���"<<m_Rooms[it->second.m_RoomNum].player[1]->m_ID<<"�����ʤ����";
						}
						else
						{
							int score = m_Rooms[it->second.m_RoomNum].player[1]->m_Score / 50;
							m_Rooms[it->second.m_RoomNum].player[1]->m_Lose += 1;
							m_Rooms[it->second.m_RoomNum].player[1]->m_Score -= score;
							std::cout<<"���"<<m_Rooms[it->second.m_RoomNum].player[1]->m_ID<<"�����ˣ�";

							m_Rooms[it->second.m_RoomNum].player[0]->m_Win += 1;
							m_Rooms[it->second.m_RoomNum].player[0]->m_Score += score;
							m_Rooms[it->second.m_RoomNum].player[0]->m_PlayState = _PS_WAIT;
							std::cout<<"���"<<m_Rooms[it->second.m_RoomNum].player[0]->m_ID<<"�����ʤ����"<<std::endl;
						}
						m_Games.erase(git);
					}
					UpdatePlayerData(*m_Rooms[it->second.m_RoomNum].player[0]);
					UpdatePlayerData(*m_Rooms[it->second.m_RoomNum].player[1]);
				}
				m_Rooms[it->second.m_RoomNum].player[it->second.m_SiteNum] = 0;
			}

			ts.Disconnect(s);
			m_Clients.erase(it);

			break;
		}
	}
	for(it = m_Clients.begin(); it != m_Clients.end();++it)
	{
		ts.SendData(it->second.m_socket,&sc_po,sizeof(sc_po));
	}
}

void UpdatePlayerData(_PLAYER& player)
{
	std::map<std::string, _PLAYER>::iterator it = m_ID_Password.find(player.m_ID);
	if(it != m_ID_Password.end())
	{
		it->second.m_Score = player.m_Score;
		it->second.m_Win = player.m_Win;
		it->second.m_Lose = player.m_Lose;
		it->second.m_Draw = player.m_Draw;
	}

	SC_UPDATE_PLAYER_DATA sc_ud;
	strcpy_s(sc_ud.ID,32,player.m_ID.c_str());
	sc_ud.score = player.m_Score;
	sc_ud.win = player.m_Win;
	sc_ud.lose = player.m_Lose;
	sc_ud.draw = player.m_Draw;
	sc_ud.playerstate = player.m_PlayState;
	sc_ud.roomnum = player.m_RoomNum;
	sc_ud.sitenum = player.m_SiteNum;

	for(it = m_Clients.begin(); it != m_Clients.end();++it)
	{
		ts.SendData(it->second.m_socket,&sc_ud,sizeof(sc_ud));
	}

	SaveFile(_CLIENT_INFO_FILE, &m_ID_Password);
}