#include "ProtocolFilter.h"
#include "DataType.h"
#include <map>
#include <iostream>
#include "FileData.h"
#include "BlackJack.h"

const char* pokers[] = 
{
	"����A","����2","����3","����4","����5","����6",
	"����7","����8","����9","����10","����J","����Q","����K",
	"����A","����2","����3","����4","����5","����6",
	"����7","����8","����9","����10","����J","����Q","����K",
	"÷��A","÷��2","÷��3","÷��4","÷��5","÷��6",
	"÷��7","÷��8","÷��9","÷��10","÷��J","÷��Q","÷��K",
	"����A","����2","����3","����4","����5","����6",
	"����7","����8","����9","����10","����J","����Q","����K"
};

extern CTcpServer ts;
extern std::map<std::string, _PLAYER> m_ID_Password;
extern std::map<std::string, _PLAYER> m_Clients;
extern _ROOM m_Rooms[_ROOM_NUM];
extern std::map<int,CBlackJack> m_Games;

extern void UpdatePlayerData(_PLAYER& player);

//Э�鴦���ɷ�
void ProtocolDispatcher(_SNET_EVENT& ne)
{
	_PROTOCOL* protocol = (_PROTOCOL*)ne.data;
	int type = protocol->type;

	if(type >= P_LOGIN_MIN && type <= P_LOGIN_MAX)
	{
		LoginProtoclTranslate(type,ne);
	}
	else if(type >= P_HALL_MIN && type <= P_HALL_MAX)
	{
		HallProtoclTranslate(type,ne);
	}
	else if(type >= P_GAME_BLACK_JACK_MIN && type <= P_GAME_BLACK_JACK_MAX)
	{
		BlackJackProtocolTranslate(type,ne);
	}
}

//��¼ģ��Э�����
void LoginProtoclTranslate(int type, _SNET_EVENT& ne)
{
	switch(type)
	{
	case DL_CS_DL:Login(ne);break;//��¼
	case DL_CS_ZC:Register(ne);break;//ע��
	}
}

//����ģ��Э�����
void HallProtoclTranslate(int type, _SNET_EVENT& ne)
{
	switch(type)
	{
	case HALL_CS_PUB_TALK:PublicTalk(ne);break;//��������
	case HALL_CS_PRI_TALK:PrivateTalk(ne);break;//˽������
	case HALL_CS_CHANGE_DATA:ChangePlayerData(ne);break;//�޸�����
	case HALL_CS_ENTER_ROOM:EnterRoom(ne);break;//���뷿��
	case HALL_CS_READ:Read(ne);break;//���׼��
	case HALL_CS_EXIT_ROOM:ExitRoom(ne);break;//�˳�����
	case HALL_CS_READY_CANCEL:ReadyCancel(ne);break;//���ȡ��׼��
	}
}

//21����Ϸģ��Э�����
void BlackJackProtocolTranslate(int type, _SNET_EVENT& ne)
{
	switch(type)
	{
	case GAME_CS_CHOICE_CONTINUE:ChoiceContinue(ne);break;//��Ҽ�������
	case GAME_CS_CHOICE_STOP:ChoiceStop(ne);break;//���ֹͣ����
	case GAME_CS_CHOICE_GIVEUP:ChoiceGiveUp(ne);break;//��ҷ�������
	case GAME_CS_TALK_IN_GAME:TalkInGame(ne);break;//�������
	case GAME_CS_RUN_AWAY:RunAway(ne);break;//�������
	}
}

static bool PlayerInTable(std::map<std::string, _PLAYER>::iterator &it, 
						  std::string key,
						  std::map<std::string, _PLAYER>& table)
{
	it = table.find(key);
	return it != table.end();
}

//��¼���Э�鴦����
//��¼
static void  Login(_SNET_EVENT& ne)
{
	char ip[16];
	CTcpServer::ulong_str(ne.ip, ip);

	std::cout<<ip<<"���ڵ�¼"<<std::endl;

	CS_DL* dl = (CS_DL*)ne.data;
	
	std::map<std::string, _PLAYER>::iterator it;

	//�޴����
	if (!PlayerInTable(it,dl->id,m_ID_Password))
	{
		SC_NO_ID no_id;
		ts.SendData(ne.s, &no_id, sizeof(no_id));
		ts.Disconnect(ne.s);
		std::cout<<ip<<"��¼ʧ�ܣ��ʺŲ�����"<<std::endl;
	}
	else
	{
		//�����Ƿ���ȷ
		if (strcmp(it->second.m_Password.c_str(), dl->pw) != 0)
		{
			SC_PW_ERROR pw_error;
			ts.SendData(ne.s, &pw_error, sizeof(pw_error));
			ts.Disconnect(ne.s);
			std::cout<<ip<<"��¼ʧ�ܣ��������"<<"��¼�ʺ�Ϊ"<<it->first<<std::endl;
		}
		else
		{		
			//�Ƿ��ظ���¼
			std::map<std::string, _PLAYER>::iterator n;
			if (PlayerInTable(n,dl->id,m_Clients))
			{
				SC_DL_AGAIN dl_again;
				ts.SendData(ne.s, &dl_again, sizeof(dl_again));
				ts.Disconnect(ne.s);
				std::cout<<ip<<"��¼ʧ�ܣ���¼��������ߣ�"<<"��¼�ʺ�Ϊ"<<n->first<<std::endl;
				return;
			}

			//1�������¼��Ϣ�ĳ���
			int _login_len = sizeof(SC_DL_OK);
			for (n = m_Clients.begin(); n != m_Clients.end(); ++n)
			{
				_login_len += (int)n->second.m_ID.length() + 1;
				_login_len += (int)n->second.m_Name.length() + 1;
				_login_len += sizeof(int) * 8;
			}

			//2�����õ�¼��Ϣ
			SC_DL_OK* dl_ok = (SC_DL_OK*)malloc(_login_len);
			dl_ok->type = DL_SC_DL_OK;
			dl_ok->num = 0; //������Ҹ���
			char* p = (char*)(dl_ok + 1);

			for (n = m_Clients.begin(); n != m_Clients.end(); ++n)
			{
				memcpy(p, n->second.m_ID.c_str(), n->second.m_ID.length() + 1);
				p += strlen(p) + 1;
				memcpy(p, n->second.m_Name.c_str(), n->second.m_Name.length() + 1);
				p += strlen(p) + 1;
				memcpy(p, &n->second.m_Face, sizeof(int));
				p += sizeof(int);
				memcpy(p, &n->second.m_Score, sizeof(int));
				p += sizeof(int);
				memcpy(p, &n->second.m_Win, sizeof(int));
				p += sizeof(int);
				memcpy(p, &n->second.m_Lose, sizeof(int));
				p += sizeof(int);
				memcpy(p, &n->second.m_Draw, sizeof(int));
				p += sizeof(int);
				memcpy(p, &n->second.m_RoomNum, sizeof(int));
				p += sizeof(int);
				memcpy(p, &n->second.m_SiteNum, sizeof(int));
				p += sizeof(int);
				memcpy(p, &n->second.m_PlayState, sizeof(int));
				p += sizeof(int);
				dl_ok->num += 1;
			}

			//3���������¼�߷��͵�¼��Ϣ
			ts.SendData(ne.s, dl_ok, _login_len);
			free(dl_ok);

			_PLAYER loginplayer = m_ID_Password.find(dl->id)->second;
			loginplayer.m_socket = ne.s;

			//װ��������ұ�
			m_Clients.insert(std::pair<std::string, _PLAYER>(dl->id,loginplayer));

			//4����������ҷ�������ҵ�¼��Ϣ
			//1����������ҵ�¼�ĳ���
			int _newclient_len = sizeof(SC_NEW_CLIENT);

			_newclient_len += (int)loginplayer.m_ID.length() + 1;
			_newclient_len += (int)loginplayer.m_Name.length() + 1;
			_newclient_len += sizeof(int) * 8;

			//2����������ҵ�¼��Ϣ
			SC_NEW_CLIENT* new_client = (SC_NEW_CLIENT*)malloc(_newclient_len);
			new_client->type = DL_SC_NEW_CLIENT;

			p = (char*)(new_client + 1);

			memcpy(p, loginplayer.m_ID.c_str(), loginplayer.m_ID.length() + 1);
			p += strlen(p) + 1;
			memcpy(p, loginplayer.m_Name.c_str(), loginplayer.m_Name.length() + 1);
			p += strlen(p) + 1;
			memcpy(p, &loginplayer.m_Face, sizeof(int));
			p += sizeof(int);
			memcpy(p, &loginplayer.m_Score, sizeof(int));
			p += sizeof(int);
			memcpy(p, &loginplayer.m_Win, sizeof(int));
			p += sizeof(int);
			memcpy(p, &loginplayer.m_Lose, sizeof(int));
			p += sizeof(int);
			memcpy(p, &loginplayer.m_Draw, sizeof(int));
			p += sizeof(int);
			memcpy(p, &loginplayer.m_RoomNum, sizeof(int));
			p += sizeof(int);
			memcpy(p, &loginplayer.m_SiteNum, sizeof(int));
			p += sizeof(int);
			memcpy(p, &loginplayer.m_PlayState, sizeof(int));
			p += sizeof(int);

			for (n = m_Clients.begin(); n != m_Clients.end(); ++n)
			{
				//3����������ҵ�¼��Ϣ
				ts.SendData(n->second.m_socket, new_client, _newclient_len);
			}
			std::cout<<ip<<"��¼�ɹ���"<<"��¼�ʺ�Ϊ"<<it->first<<std::endl;
			free(new_client);
		}
	}
}
//ע��
static void Register(_SNET_EVENT& ne)
{
	char ip[16];
	CTcpServer::ulong_str(ne.ip, ip);

	std::cout<<ip<<"����ע��"<<std::endl;

	CS_ZC* zc = (CS_ZC*)ne.data;

	//�ж��Ƿ��Ѿ����˸��˺�
	if (m_ID_Password.find(zc->id) != m_ID_Password.end())
	{
		//����ע��ʧ��
		SC_ZC_FAIL zc_fail;
		ts.SendData(ne.s, &zc_fail, sizeof(zc_fail));
		std::cout<<ip<<"ע��ʧ�ܣ��ʺ��Ѵ���"<<std::endl;
	}
	else
	{
		_PLAYER player = {INVALID_SOCKET,zc->id,zc->id,zc->pw,0,1000,0,0,0,-1};
		m_ID_Password.insert(std::pair<std::string, _PLAYER>(zc->id, player));
		SaveFile(_CLIENT_INFO_FILE, &m_ID_Password);

		//����ע��ɹ�
		SC_ZC_OK zc_ok;
		ts.SendData(ne.s, &zc_ok, sizeof(zc_ok));
		std::cout<<ip<<"ע��ɹ���ע���ʺ�Ϊ"<<player.m_ID<<std::endl;
	}

	ts.Disconnect(ne.s);
}

//������غ�������
//����޸�����
static void ChangePlayerData(_SNET_EVENT& ne)
{
	char ip[16];
	CTcpServer::ulong_str(ne.ip, ip);

	CS_CHANGE_DATA* cs_cd = (CS_CHANGE_DATA*)ne.data;

	//����ǳ��Ƿ��Ѿ�����
	std::map<std::string,_PLAYER>::iterator it;
	for(it = m_ID_Password.begin(); it != m_ID_Password.end();++it)
	{
		if(strcmp(it->second.m_Name.c_str(),cs_cd->Name) == 0 
			&& strcmp(it->second.m_ID.c_str(),cs_cd->ID) != 0)
		{
			//�ǳƴ���
			SC_CHANGE_DATA_FAIL sc_cdf;
			ts.SendData(ne.s,&sc_cdf,sizeof(sc_cdf));
			std::cout<<ip<<" "<<cs_cd->ID<<"�޸��������ʧ�ܣ����ǳ��Ѵ���"<<std::endl;
			return;
		}
	}

	//�ǳƲ�����
	SC_CHANGE_DATA sc_cd;
	strcpy_s(sc_cd.ID,32,cs_cd->ID);
	sc_cd.facenum = cs_cd->facenum;
	strcpy_s(sc_cd.Name,32,cs_cd->Name);

	it = m_ID_Password.find(cs_cd->ID);
	if(it != m_ID_Password.end())
	{
		it->second.m_Name = cs_cd->Name;
		it->second.m_Face = cs_cd->facenum;
	}

	for(it = m_Clients.begin(); it != m_Clients.end();++it)
	{
		if(it->second.m_ID == cs_cd->ID)
		{
			it->second.m_Name = cs_cd->Name;
			it->second.m_Face = cs_cd->facenum;
		}
		ts.SendData(it->second.m_socket,&sc_cd,sizeof(sc_cd));
	}
	SaveFile(_CLIENT_INFO_FILE, &m_ID_Password);

	std::cout<<ip<<" "<<cs_cd->ID<<"�޸�������ϳɹ���"<<std::endl;
}
//��������
static void PublicTalk(_SNET_EVENT& ne)
{
	char ip[16];
	CTcpServer::ulong_str(ne.ip, ip);

	CS_PUB_TALK* cs_pt = (CS_PUB_TALK*)ne.data;
	SC_PUB_TALK sc_pt;
	strcpy_s(sc_pt.ID,32,cs_pt->ID);
	strcpy_s(sc_pt.Message,256,cs_pt->Message);

	std::map<std::string,_PLAYER>::iterator it;

	for(it = m_Clients.begin(); it != m_Clients.end();++it)
	{
		ts.SendData(it->second.m_socket,&sc_pt,sizeof(sc_pt));
	}

	std::cout<<ip<<" "<<cs_pt->ID<<"���й������졣"<<std::endl;
}

//˽������
static void PrivateTalk(_SNET_EVENT& ne)
{
	char ip[16];
	CTcpServer::ulong_str(ne.ip, ip);

	CS_PRI_TALK* cs_pt = (CS_PRI_TALK*)ne.data;
	SC_PRI_TALK sc_pt;
	strcpy_s(sc_pt.ID,32,cs_pt->ID);
	strcpy_s(sc_pt.DESID,32,cs_pt->DESID);
	strcpy_s(sc_pt.Message,256,cs_pt->Message);

	std::map<std::string,_PLAYER>::iterator it = m_Clients.find(cs_pt->DESID);

	if(it != m_Clients.end())
	{
		ts.SendData(it->second.m_socket,&sc_pt,sizeof(sc_pt));
	}
	ts.SendData(ne.s,&sc_pt,sizeof(sc_pt));

	std::cout<<ip<<" "<<cs_pt->ID<<"����˽�����졣"<<std::endl;
}

static void EnterRoom(_SNET_EVENT& ne)
{
	char ip[16];
	CTcpServer::ulong_str(ne.ip, ip);
	CS_ENTER_ROOM* cs_er = (CS_ENTER_ROOM*)ne.data;

	std::map<std::string,_PLAYER>::iterator id = m_Clients.find(cs_er->ID);

	if(id != m_Clients.end())
	{
		if(m_Rooms[cs_er->RoomNumNew].player[cs_er->SiteNumNew] == 0)
		{
			if(id->second.m_RoomNum != -1)
			{
				m_Rooms[id->second.m_RoomNum].player[id->second.m_SiteNum] = 0;
			}

			m_Rooms[cs_er->RoomNumNew].player[cs_er->SiteNumNew] = &id->second;
			id->second.m_RoomNum = cs_er->RoomNumNew;
			id->second.m_SiteNum = cs_er->SiteNumNew;
			id->second.m_PlayState = _PS_WAIT;

			SC_ENTER_ROOM_SUCCESS sc_ers;
			strcpy_s(sc_ers.ID,32,cs_er->ID);
			sc_ers.RoomNumNew = cs_er->RoomNumNew;
			sc_ers.SiteNumNew = cs_er->SiteNumNew;

			std::map<std::string,_PLAYER>::iterator it;
			for(it = m_Clients.begin(); it != m_Clients.end(); ++it)
				ts.SendData(it->second.m_socket,&sc_ers,sizeof(sc_ers));

			std::cout<<ip<<" "<<cs_er->ID<<"���뷿��"<<cs_er->RoomNumNew<<"�ɹ���"<<std::endl;
		}
		else
		{
			SC_ENTER_ROOM_FAIL sc_erf;
			ts.SendData(ne.s,&sc_erf,sizeof(sc_erf));

			std::cout<<ip<<" "<<cs_er->ID<<"���뷿��"<<cs_er->RoomNumNew<<"ʧ�ܡ�"<<std::endl;
		}
	}
}

static void NewGame(int roomnum)
{
	std::map<int,CBlackJack>::iterator it = m_Games.find(roomnum);
	if(it != m_Games.end())
	{
		//�������ϷЭ��
		SC_NEW_GAME sc_ngp1,sc_ngp2;
		_PLAYER* p1,*p2;
		p1 = it->second.m_Room->player[0];
		p2 = it->second.m_Room->player[1];

		//������1
		strcpy_s(sc_ngp1.ID,32,p2->m_ID.c_str());
		int n1 = it->second.GetNewPoker();
		sc_ngp1.firstpokernum = n1;
		ts.SendData(p1->m_socket,&sc_ngp1,sizeof(sc_ngp1));
		std::cout<<"���"<<p1->m_ID<<"���"<<pokers[sc_ngp1.firstpokernum]<<std::endl;
		it->second.Player1Pokers[0] = n1;
		it->second.m_iPlayer1CurPokersNum = 1;
		n1 = n1 % 13 >= 10 ? 10 : n1 % 13 + 1;
		it->second.m_iPlayer1CurPoint = n1;

		//������2
		strcpy_s(sc_ngp2.ID,32,p1->m_ID.c_str());
		int n2 = it->second.GetNewPoker();
		sc_ngp2.firstpokernum = n2;
		ts.SendData(p2->m_socket,&sc_ngp2,sizeof(sc_ngp2));
		std::cout<<"���"<<p2->m_ID<<"���"<<pokers[sc_ngp2.firstpokernum]<<std::endl;
		it->second.Player2Pokers[0] = sc_ngp2.firstpokernum;
		it->second.m_iPlayer2CurPokersNum = 1;
		n2 = n2 % 13 >= 10 ? 10 : n2 % 13 + 1;
		it->second.m_iPlayer2CurPoint = n2;

		std::cout<<"���"<<p1->m_ID<<"���в���"<<std::endl;
		SC_MAKE_CHOICE sc_mc;
		strcpy_s(sc_mc.ID,32,p1->m_ID.c_str());

		ts.SendData(p1->m_socket,&sc_mc,sizeof(sc_mc));
		ts.SendData(p2->m_socket,&sc_mc,sizeof(sc_mc));

		//֪ͨ���������������ҵ�״̬��Ϊ��Ϸ��
		sc_ngp1.firstpokernum = -1;
		sc_ngp2.firstpokernum = -1;
		std::map<std::string,_PLAYER>::iterator info;
		for(info = m_Clients.begin(); info != m_Clients.end(); ++info)
		{
			if(strcmp(p1->m_ID.c_str(),info->second.m_ID.c_str()) != 0 && 
				strcmp(p2->m_ID.c_str(),info->second.m_ID.c_str()) != 0)
			{
				ts.SendData(info->second.m_socket,&sc_ngp1,sizeof(sc_ngp1));
				ts.SendData(info->second.m_socket,&sc_ngp2,sizeof(sc_ngp2));
			}
		}
	}
}

static void Read(_SNET_EVENT& ne)
{
	char ip[16];
	CTcpServer::ulong_str(ne.ip, ip);

	CS_READ* cs_r = (CS_READ*)ne.data;

	std::map<std::string,_PLAYER>::iterator it = m_Clients.find(cs_r->ID);

	if(it != m_Clients.end() && it->second.m_PlayState == _PS_WAIT)
	{
		it->second.m_PlayState = _PS_READY;

		SC_READ_SUCCESS sc_rs;
		strcpy_s(sc_rs.ID,32,cs_r->ID);

		std::map<std::string,_PLAYER>::iterator n;
		for(n = m_Clients.begin(); n != m_Clients.end(); ++n)
			ts.SendData(n->second.m_socket,&sc_rs,sizeof(sc_rs));

		std::cout<<ip<<" "<<cs_r->ID<<"׼����Ϸ��"<<std::endl;

		_ROOM* room = &m_Rooms[it->second.m_RoomNum];

		if(room->player[0] && room->player[0]->m_PlayState == _PS_READY &&
			room->player[1] && room->player[1]->m_PlayState == _PS_READY)
		{
			//˫����Ϊ׼��,��ʼ����Ϸ
			room->m_RoomState = _RS_PLAYING;
			room->player[0]->m_PlayState = _PS_PLAYING;
			room->player[1]->m_PlayState = _PS_PLAYING;

			CBlackJack bj(room);
			m_Games.insert(std::pair<int,CBlackJack>(it->second.m_RoomNum,bj));
			NewGame(it->second.m_RoomNum);

			std::cout<<it->second.m_RoomNum<<"�ŷ��俪ʼ����Ϸ��"<<"˫��ID�ֱ�Ϊ��"
				<<room->player[0]->m_ID<<" �Ծ� "<<room->player[1]->m_ID<<std::endl;
		}
	}
}

static void ExitRoom(_SNET_EVENT& ne)
{
	char ip[16];
	CTcpServer::ulong_str(ne.ip, ip);

	CS_EXIT_ROOM* cs_er = (CS_EXIT_ROOM*)ne.data;

	std::map<std::string,_PLAYER>::iterator it = m_Clients.find(cs_er->ID);

	if(it != m_Clients.end() && it->second.m_PlayState == _PS_WAIT)
	{
		m_Rooms[it->second.m_RoomNum].player[it->second.m_SiteNum] = 0;

		std::cout<<ip<<" "<<cs_er->ID<<"�˳�����"<<it->second.m_RoomNum<<std::endl;

		it->second.m_PlayState = _PS_NONE;
		it->second.m_RoomNum = -1;
		it->second.m_SiteNum = -1;

		SC_EXIT_ROOM_SUCCESS sc_ers;
		strcpy_s(sc_ers.ID,32,cs_er->ID);

		std::map<std::string,_PLAYER>::iterator n;
		for(n = m_Clients.begin(); n != m_Clients.end(); ++n)
			ts.SendData(n->second.m_socket,&sc_ers,sizeof(sc_ers));
	}
}

static void ReadyCancel(_SNET_EVENT& ne)
{
	char ip[16];
	CTcpServer::ulong_str(ne.ip, ip);

	CS_READY_CANCEL* cs_rc = (CS_READY_CANCEL*)ne.data;

	std::map<std::string,_PLAYER>::iterator it = m_Clients.find(cs_rc->ID);

	if(it != m_Clients.end() && it->second.m_PlayState == _PS_READY)
	{
		it->second.m_PlayState = _PS_WAIT;

		SC_READY_CANCEL_SUCCESS sc_rcs;
		strcpy_s(sc_rcs.ID,32,cs_rc->ID);

		std::map<std::string,_PLAYER>::iterator n;
		for(n = m_Clients.begin(); n != m_Clients.end(); ++n)
			ts.SendData(n->second.m_socket,&sc_rcs,sizeof(sc_rcs));

		std::cout<<ip<<" "<<cs_rc->ID<<"ȡ��׼����Ϸ��"<<std::endl;
	}
}

static void ChoiceContinue(_SNET_EVENT& ne)
{
	char ip[16];
	CTcpServer::ulong_str(ne.ip, ip);

	CS_CHOICE_CONTINUE* cs_c = (CS_CHOICE_CONTINUE*)ne.data;

	std::map<std::string,_PLAYER>::iterator pit = m_Clients.find(cs_c->ID);

	if(pit != m_Clients.end())
	{
		std::map<int,CBlackJack>::iterator it = m_Games.find(pit->second.m_RoomNum);
		
		if(it != m_Games.end())
		{
			bool g_GameEnd = false;

			int p = it->second.GetNewPoker();
			int num = p % 13 >= 10 ? 10 : p % 13 + 1;

			_PLAYER* p1 = it->second.m_Room->player[0];
			_PLAYER* p2 = it->second.m_Room->player[1];
			
			if(pit->second.m_SiteNum == 0)
			{
				std::cout<<"���"<<p1->m_ID<<"���һ��"<<pokers[p]<<" ����Ϊ"<<num<<std::endl;
				it->second.Player1Pokers[it->second.m_iPlayer1CurPokersNum++] = p;

				//21��
				if(it->second.m_iPlayer1CurPoint + num == 21)
				{
					std::cout<<"���"<<p1->m_ID<<"�õ�21��ʤ��"<<std::endl;

					int addscore = p2->m_Score / 50;
					p1->m_Win += 1;
					p1->m_Score += addscore;

					p2->m_Lose += 1;
					p2->m_Score -= addscore;

					//���͸�ʤ���ߵ���Ϣ
					SC_WIN_21 sc_w21_win;
					strcpy_s(sc_w21_win.winID,32,p1->m_ID.c_str());
					sc_w21_win.lastpoker = p;
					sc_w21_win.pokernum = it->second.m_iPlayer2CurPokersNum;
					for(int i = 0; i < it->second.m_iPlayer2CurPokersNum; i++)
						sc_w21_win.pokers[i] = it->second.Player2Pokers[i];
					ts.SendData(p1->m_socket,&sc_w21_win,sizeof(sc_w21_win));

				
					//���͸�ʧ���ߵ���Ϣ
					SC_WIN_21 sc_w21_lose;
					strcpy_s(sc_w21_lose.winID,32,p1->m_ID.c_str());
					sc_w21_lose.lastpoker = p;
					sc_w21_lose.pokernum = it->second.m_iPlayer1CurPokersNum;
					for(int i = 0; i < it->second.m_iPlayer1CurPokersNum; i++)
						sc_w21_lose.pokers[i] = it->second.Player1Pokers[i];
					ts.SendData(p2->m_socket,&sc_w21_lose,sizeof(sc_w21_lose));

					g_GameEnd = true;

				}
				//����ʧ��
				else if(it->second.m_iPlayer1CurPoint + num > 21)
				{
					std::cout<<"���"<<p1->m_ID<<"����ʧ��"<<std::endl;

					int addscore = p1->m_Score / 100;
					p2->m_Win += 1;
					p2->m_Score += addscore;

					p1->m_Lose += 1;
					p1->m_Score -= addscore;

					//���͸�ʧ���ߵ���Ϣ
					SC_LOSE_OUT_RANGE sc_lor_lose;
					strcpy_s(sc_lor_lose.loseID,32,p1->m_ID.c_str());
					sc_lor_lose.lastpoker = p;
					sc_lor_lose.pokernum = it->second.m_iPlayer2CurPokersNum;
					for(int i = 0; i < it->second.m_iPlayer2CurPokersNum; i++)
						sc_lor_lose.pokers[i] = it->second.Player2Pokers[i];
					ts.SendData(p1->m_socket,&sc_lor_lose,sizeof(sc_lor_lose));

					//���͸�ʤ���ߵ���Ϣ
					SC_LOSE_OUT_RANGE sc_lor_win;
					strcpy_s(sc_lor_win.loseID,32,p1->m_ID.c_str());
					sc_lor_win.lastpoker = p;
					sc_lor_win.pokernum = it->second.m_iPlayer1CurPokersNum;
					for(int i = 0; i < it->second.m_iPlayer1CurPokersNum; i++)
						sc_lor_win.pokers[i] = it->second.Player1Pokers[i];
					ts.SendData(p2->m_socket,&sc_lor_win,sizeof(sc_lor_win));

					g_GameEnd = true;

				}
				//��������
				else
				{
					SC_GET_NEW sc_gn;
					sc_gn.newpoker = p;
					ts.SendData(p1->m_socket,&sc_gn,sizeof(sc_gn));
					sc_gn.newpoker = -1;
					ts.SendData(p2->m_socket,&sc_gn,sizeof(sc_gn));
					it->second.m_iPlayer1CurPoint += num;

					if(!it->second.m_bPlayer2Stop)
					{
						std::cout<<"�������"<<std::endl;
						SC_MAKE_CHOICE sc_mc;
						strcpy_s(sc_mc.ID,32,p2->m_ID.c_str());
						ts.SendData(p1->m_socket,&sc_mc,sizeof(sc_mc));
						ts.SendData(p2->m_socket,&sc_mc,sizeof(sc_mc));
					}
					else
					{
						std::cout<<"���"<<p1->m_ID<<"����ѡ��"<<std::endl;
						SC_MAKE_CHOICE sc_mc;
						strcpy_s(sc_mc.ID,32,p1->m_ID.c_str());
						ts.SendData(p1->m_socket,&sc_mc,sizeof(sc_mc));
						ts.SendData(p2->m_socket,&sc_mc,sizeof(sc_mc));
					}
				}
			}
			else
			{
				std::cout<<"���"<<p2->m_ID<<"���һ��"<<pokers[p]<<" ����Ϊ"<<num<<std::endl;
				it->second.Player2Pokers[it->second.m_iPlayer2CurPokersNum++] = p;
				//21��
				if(it->second.m_iPlayer2CurPoint + num == 21)
				{
					std::cout<<"���"<<p2->m_ID<<"�õ�21��ʤ��"<<std::endl;

					int addscore = p1->m_Score / 50;
					p2->m_Win += 1;
					p2->m_Score += addscore;

					p1->m_Lose += 1;
					p1->m_Score -= addscore;

					//���͸�ʤ���ߵ���Ϣ
					SC_WIN_21 sc_w21_win;
					strcpy_s(sc_w21_win.winID,32,p2->m_ID.c_str());
					sc_w21_win.lastpoker = p;
					sc_w21_win.pokernum = it->second.m_iPlayer1CurPokersNum;
					for(int i = 0; i < it->second.m_iPlayer1CurPokersNum; i++)
						sc_w21_win.pokers[i] = it->second.Player1Pokers[i];
					ts.SendData(p2->m_socket,&sc_w21_win,sizeof(sc_w21_win));


					//���͸�ʧ���ߵ���Ϣ
					SC_WIN_21 sc_w21_lose;
					strcpy_s(sc_w21_lose.winID,32,p2->m_ID.c_str());
					sc_w21_lose.lastpoker = p;
					sc_w21_lose.pokernum = it->second.m_iPlayer2CurPokersNum;
					for(int i = 0; i < it->second.m_iPlayer2CurPokersNum; i++)
						sc_w21_lose.pokers[i] = it->second.Player2Pokers[i];
					ts.SendData(p1->m_socket,&sc_w21_lose,sizeof(sc_w21_lose));

					g_GameEnd = true;

				}
				//����ʧ��
				else if(it->second.m_iPlayer2CurPoint + num > 21)
				{
					std::cout<<"���"<<p2->m_ID<<"����ʧ��"<<std::endl;

					int addscore = p2->m_Score / 100;
					p1->m_Win += 1;
					p1->m_Score += addscore;

					p2->m_Lose += 1;
					p2->m_Score -= addscore;

					//���͸�ʧ���ߵ���Ϣ
					SC_LOSE_OUT_RANGE sc_lor_lose;
					strcpy_s(sc_lor_lose.loseID,32,p2->m_ID.c_str());
					sc_lor_lose.lastpoker = p;
					sc_lor_lose.pokernum = it->second.m_iPlayer1CurPokersNum;
					for(int i = 0; i < it->second.m_iPlayer1CurPokersNum; i++)
						sc_lor_lose.pokers[i] = it->second.Player1Pokers[i];
					ts.SendData(p2->m_socket,&sc_lor_lose,sizeof(sc_lor_lose));

					//���͸�ʤ���ߵ���Ϣ
					SC_LOSE_OUT_RANGE sc_lor_win;
					strcpy_s(sc_lor_win.loseID,32,p2->m_ID.c_str());
					sc_lor_win.lastpoker = p;
					sc_lor_win.pokernum = it->second.m_iPlayer2CurPokersNum;
					for(int i = 0; i < it->second.m_iPlayer2CurPokersNum; i++)
						sc_lor_win.pokers[i] = it->second.Player2Pokers[i];
					ts.SendData(p1->m_socket,&sc_lor_win,sizeof(sc_lor_win));

					g_GameEnd = true;
				}
				//��������
				else
				{
					SC_GET_NEW sc_gn;
					sc_gn.newpoker = p;
					ts.SendData(p2->m_socket,&sc_gn,sizeof(sc_gn));
					sc_gn.newpoker = -1;
					ts.SendData(p1->m_socket,&sc_gn,sizeof(sc_gn));
					it->second.m_iPlayer2CurPoint += num;

					if(!it->second.m_bPlayer1Stop)
					{
						std::cout<<"�������"<<std::endl;
						SC_MAKE_CHOICE sc_mc;
						strcpy_s(sc_mc.ID,32,p1->m_ID.c_str());

						ts.SendData(p1->m_socket,&sc_mc,sizeof(sc_mc));
						ts.SendData(p2->m_socket,&sc_mc,sizeof(sc_mc));
					}
					else
					{
						std::cout<<"���"<<p2->m_ID<<"����ѡ��"<<std::endl;
						SC_MAKE_CHOICE sc_mc;
						strcpy_s(sc_mc.ID,32,p2->m_ID.c_str());
						ts.SendData(p1->m_socket,&sc_mc,sizeof(sc_mc));
						ts.SendData(p2->m_socket,&sc_mc,sizeof(sc_mc));
					}

				}
			}
			if(g_GameEnd)
			{
				p1->m_PlayState = _PS_WAIT;
				p2->m_PlayState = _PS_WAIT;

				GameEnd(p1,p2,it);
			}
		}
	}
}
static void ChoiceStop(_SNET_EVENT& ne)
{
	char ip[16];
	CTcpServer::ulong_str(ne.ip, ip);

	CS_CHOICE_STOP* cs_cs = (CS_CHOICE_STOP*)ne.data;

	std::map<std::string,_PLAYER>::iterator pit = m_Clients.find(cs_cs->ID);
	if(pit != m_Clients.end())
	{
		std::map<int,CBlackJack>::iterator it = m_Games.find(pit->second.m_RoomNum);
		
		if(it != m_Games.end())
		{
			_PLAYER* p1 = it->second.m_Room->player[0];
			_PLAYER* p2 = it->second.m_Room->player[1];

			if(it->second.m_bPlayer1Stop && it->second.m_bPlayer2Stop)
			{
				std::cout<<"˫��ֹͣ�������ƣ����㱾�ֽ����"<<std::endl;
				std::cout<<"���"<<p1->m_ID<<"����Ϊ"<<it->second.m_iPlayer1CurPoint<<std::endl;
				std::cout<<"���"<<p2->m_ID<<"����Ϊ"<<it->second.m_iPlayer2CurPoint<<std::endl;

				//˫����ֹͣ��������
				if(it->second.m_iPlayer1CurPoint > it->second.m_iPlayer2CurPoint)
				{
					std::cout<<"���"<<p1->m_ID<<"���ʤ��"<<std::endl;

					int addscore = p2->m_Score / 100;
					p1->m_Win += 1;
					p1->m_Score += addscore;

					p2->m_Lose += 1;
					p2->m_Score -= addscore;

					//ʤ����
					SC_WIN_BIGGER sc_wb_win;
					strcpy_s(sc_wb_win.winID,32,p1->m_ID.c_str());
					sc_wb_win.pokernum = it->second.m_iPlayer2CurPokersNum;
					for(int i = 0; i < it->second.m_iPlayer2CurPokersNum; ++i)
						sc_wb_win.pokers[i] = it->second.Player2Pokers[i];
					ts.SendData(p1->m_socket,&sc_wb_win,sizeof(sc_wb_win));

					//ʧ����
					SC_WIN_BIGGER sc_wb_lose;
					strcpy_s(sc_wb_win.winID,32,p1->m_ID.c_str());
					sc_wb_lose.pokernum = it->second.m_iPlayer1CurPokersNum;
					for(int i = 0; i < it->second.m_iPlayer1CurPokersNum; ++i)
						sc_wb_lose.pokers[i] = it->second.Player1Pokers[i];
					ts.SendData(p2->m_socket,&sc_wb_lose,sizeof(sc_wb_lose));
				}
				else if(it->second.m_iPlayer1CurPoint < it->second.m_iPlayer2CurPoint)
				{
					std::cout<<"���"<<p2->m_ID<<"���ʤ��"<<std::endl;

					int addscore = p1->m_Score / 100;
					p2->m_Win += 1;
					p2->m_Score += addscore;

					p1->m_Lose += 1;
					p1->m_Score -= addscore;

					//ʤ����
					SC_WIN_BIGGER sc_wb_win;
					strcpy_s(sc_wb_win.winID,32,p2->m_ID.c_str());
					sc_wb_win.pokernum = it->second.m_iPlayer1CurPokersNum;
					for(int i = 0; i < it->second.m_iPlayer1CurPokersNum; ++i)
						sc_wb_win.pokers[i] = it->second.Player1Pokers[i];
					ts.SendData(p2->m_socket,&sc_wb_win,sizeof(sc_wb_win));
					
					//ʧ����
					SC_WIN_BIGGER sc_wb_lose;
					strcpy_s(sc_wb_win.winID,32,p2->m_ID.c_str());
					sc_wb_lose.pokernum = it->second.m_iPlayer2CurPokersNum;
					for(int i = 0; i < it->second.m_iPlayer2CurPokersNum; ++i)
						sc_wb_lose.pokers[i] = it->second.Player2Pokers[i];
					ts.SendData(p1->m_socket,&sc_wb_lose,sizeof(sc_wb_lose));

				}
				else
				{
					std::cout<<"ƽ��"<<std::endl;
					p1->m_Draw += 1;
					p2->m_Draw += 1;

					SC_DRAW sc_d_p1;
					sc_d_p1.pokernum = it->second.m_iPlayer2CurPokersNum;
					for(int i = 0; i < it->second.m_iPlayer2CurPokersNum; ++i)
						sc_d_p1.pokers[i] = it->second.Player2Pokers[i];
					ts.SendData(p1->m_socket,&sc_d_p1,sizeof(sc_d_p1));

					SC_DRAW sc_d_p2;
					sc_d_p2.pokernum = it->second.m_iPlayer1CurPokersNum;
					for(int i = 0; i < it->second.m_iPlayer1CurPokersNum; ++i)
						sc_d_p2.pokers[i] = it->second.Player1Pokers[i];
					ts.SendData(p2->m_socket,&sc_d_p2,sizeof(sc_d_p2));
				}

				p1->m_PlayState = _PS_WAIT;
				p2->m_PlayState = _PS_WAIT;

				GameEnd(p1,p2,it);
			}
			else
			{
				if(pit->second.m_SiteNum == 0)
				{
					std::cout<<"���"<<p1->m_ID<<"ֹͣ��������"<<std::endl;
					it->second.m_bPlayer1Stop = true;

					std::cout<<"�������"<<std::endl;
					SC_MAKE_CHOICE sc_mc;
					strcpy_s(sc_mc.ID,32,p2->m_ID.c_str());

					ts.SendData(p1->m_socket,&sc_mc,sizeof(sc_mc));
					ts.SendData(p2->m_socket,&sc_mc,sizeof(sc_mc));
				}
				else
				{
					std::cout<<"���"<<p2->m_ID<<"ֹͣ��������"<<std::endl;
					it->second.m_bPlayer2Stop = true;

					std::cout<<"�������"<<std::endl;
					SC_MAKE_CHOICE sc_mc;
					strcpy_s(sc_mc.ID,32,p1->m_ID.c_str());

					ts.SendData(p1->m_socket,&sc_mc,sizeof(sc_mc));
					ts.SendData(p2->m_socket,&sc_mc,sizeof(sc_mc));
				}
			}
		}
	}
}
static void ChoiceGiveUp(_SNET_EVENT& ne)
{
	char ip[16];
	CTcpServer::ulong_str(ne.ip, ip);

	CS_CHOICE_GIVEUP * cs_cg = (CS_CHOICE_GIVEUP*)ne.data;

	std::map<std::string,_PLAYER>::iterator pit = m_Clients.find(cs_cg->ID);
	if(pit != m_Clients.end())
	{
		std::map<int,CBlackJack>::iterator it = m_Games.find(pit->second.m_RoomNum);
		
		if(it != m_Games.end())
		{
			_PLAYER* win, *lose;

			SC_LOSE_GIVEUP sc_lg;

			if(pit->second.m_SiteNum == 0)
			{
				lose = it->second.m_Room->player[0];
				win = it->second.m_Room->player[1];
			}
			else
			{
				lose = it->second.m_Room->player[1];
				win = it->second.m_Room->player[0];
			}

			std::cout<<"���"<<lose->m_ID<<"ѡ������þ���Ϸ"<<std::endl;

			int addscore = lose->m_Score / 200;
			win->m_Win += 1;
			win->m_Score += addscore;

			lose->m_Lose += 1;
			lose->m_Score -= addscore;

			strcpy_s(sc_lg.loseID,32,lose->m_ID.c_str());

			ts.SendData(win->m_socket,&sc_lg,sizeof(sc_lg));
			ts.SendData(lose->m_socket,&sc_lg,sizeof(sc_lg));

			win->m_PlayState = _PS_WAIT;
			lose->m_PlayState = _PS_WAIT;

			GameEnd(win,lose,it);
		}
	}
}
static void TalkInGame(_SNET_EVENT& ne)
{
	char ip[16];
	CTcpServer::ulong_str(ne.ip, ip);

	CS_TALK_IN_GAME * cs_tig = (CS_TALK_IN_GAME*)ne.data;

	std::map<std::string,_PLAYER>::iterator pit = m_Clients.find(cs_tig->ID);

	std::map<int,CBlackJack>::iterator it = m_Games.find(pit->second.m_RoomNum);

	if(pit != m_Clients.end() && it != m_Games.end())
	{
		SC_TALK_IN_GAME sc_tig;
		strcpy_s(sc_tig.ID,32,cs_tig->ID);
		strcpy_s(sc_tig.msg,256,cs_tig->msg);

		ts.SendData(it->second.m_Room->player[0]->m_socket,&sc_tig,sizeof(sc_tig));
		ts.SendData(it->second.m_Room->player[1]->m_socket,&sc_tig,sizeof(sc_tig));
	}

}
static void RunAway(_SNET_EVENT& ne)
{
	char ip[16];
	CTcpServer::ulong_str(ne.ip, ip);

	CS_RUN_AWAY * cs_ra = (CS_RUN_AWAY*)ne.data;

	std::map<std::string,_PLAYER>::iterator pit = m_Clients.find(cs_ra->ID);

	if(pit != m_Clients.end() && pit->second.m_PlayState == _PS_PLAYING)
	{
		std::map<int,CBlackJack>::iterator it = m_Games.find(pit->second.m_RoomNum);
		
		if(it != m_Games.end())
		{
			_PLAYER* lose;
			_PLAYER* win;

			if(pit->second.m_SiteNum == 0)
			{
				lose = it->second.m_Room->player[0];
				win = it->second.m_Room->player[1];
			}
			else
			{
				lose = it->second.m_Room->player[1];
				win = it->second.m_Room->player[0];
			}

			int addscore = lose->m_Score / 200;
			win->m_Win += 1;
			win->m_Score += addscore;

			lose->m_Lose += 1;
			lose->m_Score -= addscore;

			SC_LOSE_RUN_AWAY sc_lra;
			strcpy_s(sc_lra.loseID,32,lose->m_ID.c_str());

			ts.SendData(win->m_socket,&sc_lra,sizeof(sc_lra));
			ts.SendData(lose->m_socket,&sc_lra,sizeof(sc_lra));

			std::cout<<"���"<<lose->m_ID<<"ѡ�����ܣ������þ���Ϸ"<<std::endl;

			win->m_PlayState = _PS_WAIT;

			it->second.m_Room->player[pit->second.m_SiteNum] = 0;

			lose->m_PlayState = _PS_NONE;
			lose->m_RoomNum = -1;
			lose->m_SiteNum = -1;

			GameEnd(win,lose,it);
		}
	}
}

static void GameEnd(_PLAYER* p1, _PLAYER* p2,std::map<int,CBlackJack>::iterator& game)
{
	std::cout<<game->first<<"�ŷ�����Ϸ������"<<std::endl;
	m_Games.erase(game);

	std::map<std::string,_PLAYER>::iterator info;
	for(info = m_Clients.begin(); info != m_Clients.end(); ++info)
	{
		UpdatePlayerData(*p1);
		UpdatePlayerData(*p2);
	}
}