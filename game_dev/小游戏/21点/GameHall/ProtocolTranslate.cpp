#include "ProtocolTranslate.h"
#include "..\\GameProtocol\\Protocol.h"
#include "..\\GameProtocol\\LoginProtocol.h"
#include "..\\GameProtocol\\HallProtocol.h"
#include "..\\GameProtocol\\BlackJackProtocol.h"

//----------------------------------------------------------------------------------------------
//��½���
//----------------------------------------------------------------------------------------------
//----------------------------------
//��������ͻ��˷�����Ϣ(C-S��Ϣ)
//----------------------------------
//1.ע���˺�
//������ע�����˺ţ����룬Tcp�ͻ�����
void Register(const char* id, const char* pw, CTcpClient& tc)
{
	CS_ZC cs_zc;
	strcpy_s(cs_zc.id, 32,id);
	strcpy_s(cs_zc.pw, 32,pw);
	tc.SendData(&cs_zc, sizeof(cs_zc));
}

//2.��½�˺�
//��������½���˺ţ����룬Tcp�ͻ�����
void Login(const char* id, const char* pw, CTcpClient& tc)
{
	CS_DL cs_dl;
	strcpy_s(cs_dl.id, 32,id);
	strcpy_s(cs_dl.pw, 32,pw);
	tc.SendData(&cs_dl, sizeof(cs_dl));
}

//----------------------------------
//�ͻ��˽��ܷ�������Ϣ����(S-C��Ϣ)
//----------------------------------
//1.��½�ɹ�
//�������ͻ����¼���Ϣ����Ҫ���ĵ�ǰ������ұ�
void LoginSuccess(_CNET_EVENT& ne,std::map<std::string,_PLAYER>& players)
{
	SC_DL_OK* dl_ok = (SC_DL_OK*)ne.data;
	char* p = (char*)(dl_ok + 1);
	for(int i = 0; i < dl_ok->num; ++i)
	{
		std::string id = p;
		p += strlen(p) + 1;

		std::string name = p;
		p += strlen(p) + 1;

		int face = *((int*)p);
		p += sizeof(int);

		int score = *((int*)p);
		p += sizeof(int);

		int win = *((int*)p);
		p += sizeof(int);

		int lose = *((int*)p);
		p += sizeof(int);

		int draw = *((int*)p);
		p += sizeof(int);

		int roomnum = *((int*)p);
		p += sizeof(int);

		int sitenum = *((int*)p);
		p += sizeof(int);

		int playerstate = *((int*)p);
		p += sizeof(int);

		_PLAYER player = {id,name,face,score,win,lose,draw,roomnum,sitenum,playerstate};
		players.insert(std::pair<std::string,_PLAYER>(id,player));
	}
}

//2.����ҵ�½�ɹ�
//�������ͻ����¼���Ϣ�����������Ϣ����ǰ�ͻ�����ҵ�ID��
//����true��ʾ������Լ�����Ϣ
//����false��ʾ��������ҵ������Ϣ
bool NewClientLogin(_CNET_EVENT& ne,_PLAYER& player,std::string clientid)
{
	SC_NEW_CLIENT* new_client = (SC_NEW_CLIENT*)ne.data;
	char* p = (char*)(new_client + 1);

	player.m_ID = p;
	p += strlen(p) + 1;

	player.m_Name = p;
	p += strlen(p) + 1;

	player.m_Face = *((int*)p);
	p += sizeof(int);

	player.m_Score = *((int*)p);
	p += sizeof(int);

	player.m_Win = *((int*)p);
	p += sizeof(int);

	player.m_Lose = *((int*)p);
	p += sizeof(int);

	player.m_Draw = *((int*)p);
	p += sizeof(int);

	player.m_RoomNum = *((int*)p);
	p += sizeof(int);

	player.m_SiteNum = *((int*)p);
	p += sizeof(int);

	player.m_PlayState = *((int*)p);
	p += sizeof(int);

	return strcmp(clientid.c_str(),player.m_ID.c_str()) == 0;
}

//----------------------------------------------------------------------------------------------
//�������
//----------------------------------------------------------------------------------------------
//1.����޸ĳɹ�
//�������ͻ����¼���Ϣ���������֣�ͷ�񣬵�ǰ�ͻ�����ҵ�ID��
//����true��ʾ������Լ�����Ϣ
//����false��ʾ��������ҵ������Ϣ
void ChangeDataSuccess(_CNET_EVENT& ne,std::string& name, int& face, std::string& clientid)
{
	SC_CHANGE_DATA* sc_cd = (SC_CHANGE_DATA*)ne.data;
	name = sc_cd->Name;
	face = sc_cd->facenum;
	clientid = sc_cd->ID;
}

//2.��������
//�������ͻ����¼���Ϣ�����ķ�����id�����ķ�������
void PublicTalk(_CNET_EVENT& ne,std::string& id, std::string& message)
{
	SC_PUB_TALK* sc_pt = (SC_PUB_TALK*)ne.data;
	id = sc_pt->ID;
	message = sc_pt->Message;
}

//3.˽������
//�������ͻ����¼���Ϣ�����ķ�����id�����ķ�������
void PrivateTalk(_CNET_EVENT& ne,std::string& id, std::string& desid, std::string& message)
{
	SC_PRI_TALK* sc_pt = (SC_PRI_TALK*)ne.data;
	id = sc_pt->ID;
	desid = sc_pt->DESID;
	message = sc_pt->Message;

}

//4.�������
//�������ͻ����¼���Ϣ������������id
void PlayerOffLine(_CNET_EVENT& ne,std::string& id)
{
	SC_PLAYER_OFFLINE* sc_po = (SC_PLAYER_OFFLINE*)ne.data;
	id = sc_po->ID;
}

//5.��ҽ��뷿��ɹ�
//�������ͻ����¼���Ϣ�����Ľ��뷿����id, �ɷ���ţ�����λ�ţ��·���ţ�����λ��
void EnterRoomSuccess(_CNET_EVENT& ne,std::string& id,int& roomnew, int& sitenew)
{
	SC_ENTER_ROOM_SUCCESS* sc_ers = (SC_ENTER_ROOM_SUCCESS*)ne.data;
	id = sc_ers->ID;
	roomnew = sc_ers->RoomNumNew;
	sitenew = sc_ers->SiteNumNew;
}

//6.���׼���ɹ�
//�������ͻ����¼���Ϣ�����׼����id
void ReadSuccess(_CNET_EVENT& ne,std::string& id)
{
	SC_READ_SUCCESS* sc_rs = (SC_READ_SUCCESS*)ne.data;
	id = sc_rs->ID;
}

//7.����˳�����ɹ�
//�������ͻ����¼���Ϣ�������˳�������id
void ExitRoomSuccess(_CNET_EVENT& ne,std::string& id)
{
	SC_EXIT_ROOM_SUCCESS* sc_ers = (SC_EXIT_ROOM_SUCCESS*)ne.data;
	id = sc_ers->ID;
}

//8.���ȡ��׼���ɹ�
//�������ͻ����¼���Ϣ�����׼����id
void ReadyCancelSuccess(_CNET_EVENT& ne,std::string& id)
{
	SC_READY_CANCEL_SUCCESS* sc_rcs = (SC_READY_CANCEL_SUCCESS*)ne.data;
	id = sc_rcs->ID;
}

//----------------------------------------------------------------------------------------------
//��Ϸ���
//----------------------------------------------------------------------------------------------
//1.��ʼ����Ϸ
//�������ͻ����¼���Ϣ�����׼����id
void NewGame(_CNET_EVENT& ne,std::string& id,int &num)
{
	SC_NEW_GAME* sc_ng = (SC_NEW_GAME*)ne.data;
	id = sc_ng->ID;
	num = sc_ng->firstpokernum;
}

//2.�����������
//�������ͻ����¼���Ϣ�����׼����id,���֣�ʤ������ƽ,���״̬������ţ���λ��
void UpdatePlayerData(_CNET_EVENT& ne,std::string& id,
					  int& score, int& win, int& lose, int& draw, 
					  int& playerstate, int&roomnum, int& sitenum)
{
	SC_UPDATE_PLAYER_DATA* sc_upd = (SC_UPDATE_PLAYER_DATA*)ne.data;
	id = sc_upd->ID;
	score = sc_upd->score;
	win = sc_upd->win;
	lose = sc_upd->lose;
	draw = sc_upd->draw;
	playerstate = sc_upd->playerstate;
	roomnum = sc_upd->roomnum;
	sitenum = sc_upd->sitenum;
}

//3.�������ѡ��
//�������ͻ����¼���Ϣ��������id
void MakeChoice(_CNET_EVENT& ne,std::string& id)
{
	SC_MAKE_CHOICE* sc_mc = (SC_MAKE_CHOICE*)ne.data;
	id = sc_mc->ID;
}

//4.��һ������
//�������ͻ����¼���Ϣ������Ʊ��
void GetNew(_CNET_EVENT& ne,int &num)
{
	SC_GET_NEW* sc_gn = (SC_GET_NEW*)ne.data;
	num = sc_gn->newpoker;
}

//5��һ��21��ʤ��
//�������ͻ����¼���Ϣ�����ʤ����id, ʤ���ߵ����һ���ƣ���һ�����Ƶ���������һ��������
void Win_21(_CNET_EVENT& ne,std::string& id,
			int& lastpoker,int& pokernum,int* pokers)
{
	SC_WIN_21* sc_w21 = (SC_WIN_21*)ne.data;
	id = sc_w21->winID;
	lastpoker = sc_w21->lastpoker;
	pokernum = sc_w21->pokernum;
	for(int i = 0; i< pokernum; ++i)
		pokers[i] = sc_w21->pokers[i];
}

//6��ұ���ʧ��
//�������ͻ����¼���Ϣ�����ʧ����id,ʧ���ߵ����һ���ƣ���һ�����Ƶ���������һ��������
void LoseOutRange(_CNET_EVENT& ne,std::string& id,
			int& lastpoker,int& pokernum,int* pokers)
{
	SC_LOSE_OUT_RANGE* sc_lor = (SC_LOSE_OUT_RANGE*)ne.data;
	id = sc_lor->loseID;
	lastpoker = sc_lor->lastpoker;
	pokernum = sc_lor->pokernum;
	for(int i = 0; i< pokernum; ++i)
		pokers[i] = sc_lor->pokers[i];
}

//7��ұȵ�����ʤ
//�������ͻ����¼���Ϣ�����ʤ����id,��һ�����Ƶ���������һ��������
void WinBigger(_CNET_EVENT& ne,std::string& id,
			int& pokernum,int* pokers)
{
	SC_WIN_BIGGER* sc_wb = (SC_WIN_BIGGER*)ne.data;
	id = sc_wb->winID;
	pokernum = sc_wb->pokernum;
	for(int i = 0; i< pokernum; ++i)
		pokers[i] = sc_wb->pokers[i];
}

//8��ұȵ���ƽ��
//�������ͻ����¼���Ϣ����һ�����Ƶ���������һ��������
void Draw(_CNET_EVENT& ne,int& pokernum,int* pokers)
{
	SC_DRAW* sc_d = (SC_DRAW*)ne.data;
	pokernum = sc_d->pokernum;
	for(int i = 0; i< pokernum; ++i)
		pokers[i] = sc_d->pokers[i];
}

//9��Ϸ������Ϣ
//�������ͻ����¼���Ϣ������޸�״̬��id
void GameEnd(_CNET_EVENT& ne,std::string& id, int& state)
{
	SC_GAME_END* sc_ge = (SC_GAME_END*)ne.data;
	id = sc_ge->ID;
	state = sc_ge->state;
}

//10��ҷ�������ʧ��
//�������ͻ����¼���Ϣ�����ʧ����id
void LoseGiveUp(_CNET_EVENT& ne,std::string& id)
{
	SC_LOSE_GIVEUP* sc_lg = (SC_LOSE_GIVEUP*)ne.data;
	id = sc_lg->loseID;
}

//11�������ʧ��
//�������ͻ����¼���Ϣ�����������id
void LoseRunAway(_CNET_EVENT& ne,std::string& id)
{
	SC_LOSE_RUN_AWAY* sc_lr = (SC_LOSE_RUN_AWAY*)ne.data;
	id = sc_lr->loseID;
}

//12�����Ϸ������
//�������ͻ����¼���Ϣ�����ķ�����id�����ķ�������
void TalkInGame(_CNET_EVENT& ne,std::string& id, std::string& message)
{
	SC_TALK_IN_GAME* sc_tig = (SC_TALK_IN_GAME*)ne.data;
	id = sc_tig->ID;
	message = sc_tig->msg;
}