#ifndef _HALL_PROTOCOL_H_
#define _HALL_PROTOCOL_H_


/*
//--------------��ϷЭ��--------------
//--------0-100Ϊ��½ע���õ�Э��---------
//--------101-200Ϊ��������Э��-------
//--------201-300Ϊ��Ϸ21������Э��-------
*/


//�������
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

#define HALL_CS_PUB_TALK			101//�����������죨C-S)
#define HALL_CS_PRI_TALK			102//˽�ģ�C-S)
#define HALL_CS_CHANGE_DATA			103//�޸����ϣ�C-S)
#define HALL_CS_ENTER_ROOM         109//���뷿��(C-S)
#define HALL_CS_READ               111//׼����Ϸ(C-S)
#define HALL_CS_EXIT_ROOM          112//�˳�����(C-S)
#define HALL_CS_READY_CANCEL        115//ȡ��׼��(C-S)

#define HALL_SC_PLAYER_OFFLINE		104//������ߣ�S-C)
#define HALL_SC_PUB_TALK			105//�����������죨S-C)
#define HALL_SC_PRI_TALK			106//˽�ģ�S-C)
#define HALL_SC_CHANGE_DATA			107//�޸����ϳɹ���S-C)		
#define HALL_SC_CHANGE_DATA_FAIL	108//�޸�����ʧ�ܣ�S-C)
#define HALL_SC_ENTER_ROOM_SUCCESS  109//���뷿��ɹ�(S-C)
#define HALL_SC_ENTER_ROOM_FAIL     110//���뷿��ʧ��(S-C)
#define HALL_SC_READ_SUCCESS       113//׼����Ϸ�ɹ�(S-C)
#define HALL_SC_EXIT_ROOM_SUCCESS   114//�˳�����ɹ�(S-C)
#define HALL_SC_READY_CANCEL_SUCCESS 116//ȡ��׼���ɹ�(S-C)


//�������
//----------------------------------------------------------------------------------
//1:�ͻ������������(C-S)
//----------------------------------------------------------------------------------
//��������
struct CS_PUB_TALK : public _PROTOCOL
{
	CS_PUB_TALK(){ type = HALL_CS_PUB_TALK; }
	char ID[32];
	char Message[256];
};

//˽������
struct CS_PRI_TALK : public _PROTOCOL
{
	CS_PRI_TALK(){ type = HALL_CS_PRI_TALK; }
	char ID[32];
	char DESID[32];
	char Message[256];
};

//�޸�����
struct CS_CHANGE_DATA : public _PROTOCOL
{
	CS_CHANGE_DATA(){ type = HALL_CS_CHANGE_DATA; }
	char ID[32];
	int facenum;
	char Name[32];
};

//���뷿��
struct CS_ENTER_ROOM : public _PROTOCOL
{
	CS_ENTER_ROOM(){ type = HALL_CS_ENTER_ROOM; }
	char ID[32];
	int RoomNumNew;
	int SiteNumNew;
};

//׼����Ϸ
struct CS_READ : public _PROTOCOL
{
	CS_READ(){ type = HALL_CS_READ; }
	char ID[32];
};

//�˳�����
struct CS_EXIT_ROOM : public _PROTOCOL
{
	CS_EXIT_ROOM(){ type = HALL_CS_EXIT_ROOM; }
	char ID[32];
};

//ȡ��׼��
struct CS_READY_CANCEL : public _PROTOCOL
{
	CS_READY_CANCEL(){ type = HALL_CS_READY_CANCEL; }
	char ID[32];
};

//-----------------------------------------------------------------------------
//2:�����������ͻ��ˣ�S-C��
//----------------------------------------------------------------------------------

//�������
struct SC_PLAYER_OFFLINE : public _PROTOCOL
{
	SC_PLAYER_OFFLINE(){ type = HALL_SC_PLAYER_OFFLINE; }
	char ID[32];
};

//��������
struct SC_PUB_TALK : public _PROTOCOL
{
	SC_PUB_TALK(){ type = HALL_SC_PUB_TALK; }
	char ID[32];
	char Message[256];
};

//˽������
struct SC_PRI_TALK : public _PROTOCOL
{
	SC_PRI_TALK(){ type = HALL_SC_PRI_TALK; }
	char ID[32];
	char DESID[32];
	char Message[256];
};

//�޸����ϳɹ�
struct SC_CHANGE_DATA : public _PROTOCOL
{
	SC_CHANGE_DATA(){ type = HALL_SC_CHANGE_DATA; }
	char ID[32];
	int facenum;
	char Name[32];
};

//�޸�����ʧ��
struct SC_CHANGE_DATA_FAIL : public _PROTOCOL
{
	SC_CHANGE_DATA_FAIL(){ type = HALL_SC_CHANGE_DATA_FAIL; }
};

//���뷿��ɹ�
struct SC_ENTER_ROOM_SUCCESS : public _PROTOCOL
{
	SC_ENTER_ROOM_SUCCESS(){ type = HALL_SC_ENTER_ROOM_SUCCESS; }
	char ID[32];
	int RoomNumNew;
	int SiteNumNew;
};

//���뷿��ʧ��
struct SC_ENTER_ROOM_FAIL : public _PROTOCOL
{
	SC_ENTER_ROOM_FAIL(){ type = HALL_SC_ENTER_ROOM_FAIL; }
};

//׼����Ϸ�ɹ�
struct SC_READ_SUCCESS : public _PROTOCOL
{
	SC_READ_SUCCESS(){ type = HALL_SC_READ_SUCCESS; }
	char ID[32];
};

//�˳�����ɹ�
struct SC_EXIT_ROOM_SUCCESS : public _PROTOCOL
{
	SC_EXIT_ROOM_SUCCESS(){ type = HALL_SC_EXIT_ROOM_SUCCESS; }
	char ID[32];
};

//ȡ��׼���ɹ�
struct SC_READY_CANCEL_SUCCESS : public _PROTOCOL
{
	SC_READY_CANCEL_SUCCESS(){ type = HALL_SC_READY_CANCEL_SUCCESS; }
	char ID[32];
};

#endif