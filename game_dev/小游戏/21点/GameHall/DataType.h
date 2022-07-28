#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_

#include <Winsock2.h>
#include <string>

//���״̬
#define _PS_NONE    0
#define _PS_WAIT    1
#define _PS_READY    2
#define _PS_PLAYING 3

//�����Ϣ
struct _PLAYER
{
	std::string m_ID;
	std::string m_Name;
	int m_Face;
	int m_Score;
	int m_Win;
	int m_Lose;
	int m_Draw;
	int m_RoomNum;
	int m_SiteNum;
	int m_PlayState;
};

//����״̬
#define _RS_WAIT    0//�ȴ���
#define _RS_PLAYING 1//��Ϸ��

struct _ROOM
{
	_PLAYER* player[2];
	int m_RoomState;
};


#endif