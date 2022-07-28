#ifndef _BLACK_JACK_PROTOCOL_H_
#define _BLACK_JACK_PROTOCOL_H_

#include "Protocol.h"
/*
//--------------��ϷЭ��--------------
//--------0-100Ϊ��½ע���õ�Э��---------
//--------101-200Ϊ��������Э��-------
//--------201-300Ϊ��Ϸ21������Э��-------
*/

//21�����
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
#define GAME_SC_NEW_GAME             201//��ʼ����Ϸ(S-C)
#define GAME_SC_UPDATE_PLAYER_DATA   202//�������ս��(S-C)
#define GAME_SC_MAKE_CHOICE          203//ָ���������ѡ��(S-C)
#define GAME_SC_TALK_IN_GAME         204//��ҽ�������(S-C)
#define GAME_SC_GAME_END             205//������Ϸ����(S-C)

#define GAME_SC_GET_NEW              206//��ҳɹ���ȡ���µ���(S-C)
#define GAME_SC_WIN_21               207//��һ��21��ʤ��(S-C)
#define GAME_SC_LOSE_OUT_RANGE       208//����򱬵�ʧ��(S-C)
#define GAME_SC_LOSE_GIVEUP          209//������������ʧ��(S-C)
#define GAME_SC_LOSE_RUN_AWAY        210//��������ܱ���ʧ��(S-C)
#define GAME_SC_WIN_BIGGER           211//������ձȵ�����ʤ(S-C)
#define GAME_SC_DRAW                 212//������ձȵ���ƽ��(S-C)

#define GAME_CS_CHOICE_CONTINUE      213//���ѡ���������(C-S)
#define GAME_CS_CHOICE_STOP          214//���ѡ��ֹͣ����(C-S)
#define GAME_CS_CHOICE_GIVEUP        215//���ѡ���������(C-S)
#define GAME_CS_TALK_IN_GAME         216//��ҽ�������(C-S)
#define GAME_CS_RUN_AWAY             217//�������(C-S)

//21�����
//----------------------------------------------------------------------------------
//1:�ͻ��������������C-S��
//----------------------------------------------------------------------------------
//���ѡ���������(C-S)
struct CS_CHOICE_CONTINUE : public _PROTOCOL
{
	CS_CHOICE_CONTINUE(){type = GAME_CS_CHOICE_CONTINUE;}
	char ID[32];//���ID
};

//���ѡ��ֹͣ����(C-S)
struct CS_CHOICE_STOP : public _PROTOCOL
{
	CS_CHOICE_STOP(){type = GAME_CS_CHOICE_STOP;}
	char ID[32];//���ID
};

//���ѡ���������(C-S)
struct CS_CHOICE_GIVEUP : public _PROTOCOL
{
	CS_CHOICE_GIVEUP(){type = GAME_CS_CHOICE_GIVEUP;}
	char ID[32];//���ID
};

//��ҽ�������(C-S)
struct CS_TALK_IN_GAME : public _PROTOCOL
{
	CS_TALK_IN_GAME(){type = GAME_CS_TALK_IN_GAME;}
	char ID[32];//���ID
	char msg[256];//˵������
};

//�������(C-S)
struct CS_RUN_AWAY : public _PROTOCOL
{
	CS_RUN_AWAY(){type = GAME_CS_RUN_AWAY;}
	char ID[32];//���ID
};

//----------------------------------------------------------------------------------
//2:�����������ͻ��ˣ�S-C��
//----------------------------------------------------------------------------------
//����Ϸ
struct SC_NEW_GAME : public _PROTOCOL
{
	SC_NEW_GAME(){type = GAME_SC_NEW_GAME;}
	char ID[32];//����ID
	int firstpokernum;//��һ���Ƶı�ţ�Ϊ-1��ʾ�������뱾����Ϸ�޹أ�ֻ�Ǹ���״̬
};

//�������״̬
struct SC_UPDATE_PLAYER_DATA : public _PROTOCOL
{
	SC_UPDATE_PLAYER_DATA(){type = GAME_SC_UPDATE_PLAYER_DATA;}
	char ID[32];//���µ����ID
	int score;//����
	int win;//ʤ
	int lose;//��
	int draw;//ƽ
	int playerstate;//���״̬
	int roomnum;//�����
	int sitenum;//��λ��
};

//ָ���������ѡ��(S-C)
struct SC_MAKE_CHOICE : public _PROTOCOL
{
	SC_MAKE_CHOICE(){type = GAME_SC_MAKE_CHOICE;}
	char ID[32];//���ID
};

//��ҽ�������(S-C)
struct SC_TALK_IN_GAME : public _PROTOCOL
{
	SC_TALK_IN_GAME(){type = GAME_SC_TALK_IN_GAME;}
	char ID[32];//���ID
	char msg[256];//˵������
};

//������Ϸ����(S-C)
struct SC_GAME_END : public _PROTOCOL
{
	SC_GAME_END(){type = GAME_SC_GAME_END;}
	char ID[32];//���ID
	int state;//��Ϸ����֮���״̬
};

//��ҳɹ���ȡ���µ���(S-C)
struct SC_GET_NEW : public _PROTOCOL
{
	SC_GET_NEW(){type = GAME_SC_GET_NEW;}
	int newpoker;//(��õ��ƣ������-1��ʾ�ǶԷ�����)
};

//��һ��21��ʤ��(S-C)
struct SC_WIN_21 : public _PROTOCOL
{
	SC_WIN_21(){type = GAME_SC_WIN_21;}
	char winID[32];
	int lastpoker;
	int pokernum;
	int pokers[21];
};

//����򱬵�ʧ��(S-C)
struct SC_LOSE_OUT_RANGE : public _PROTOCOL
{
	SC_LOSE_OUT_RANGE(){type = GAME_SC_LOSE_OUT_RANGE;}
	char loseID[32];
	int lastpoker;
	int pokernum;
	int pokers[21];
};

//������������ʧ��(S-C)
struct SC_LOSE_GIVEUP : public _PROTOCOL
{
	SC_LOSE_GIVEUP(){type = GAME_SC_LOSE_GIVEUP;}
	char loseID[32];
};

//��������ܱ���ʧ��(S-C)
struct SC_LOSE_RUN_AWAY : public _PROTOCOL
{
	SC_LOSE_RUN_AWAY(){type = GAME_SC_LOSE_RUN_AWAY;}
	char loseID[32];
};

//������ձȵ�����ʤ(S-C)
struct SC_WIN_BIGGER : public _PROTOCOL
{
	SC_WIN_BIGGER(){type = GAME_SC_WIN_BIGGER;}
	char winID[32];
	int pokernum;
	int pokers[21];
};

//������ձȵ���ƽ��(S-C)
struct SC_DRAW : public _PROTOCOL
{
	SC_DRAW(){type = GAME_SC_DRAW;}
	int pokernum;
	int pokers[21];
};

#endif