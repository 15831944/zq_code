#ifndef _BLACK_JACK_H_
#define _BLACK_JACK_H_

#include "DataType.h"

#define _POKERS_MAX        52
#define _PLAYER_MAX_POKERS  21

class CBlackJack
{
public:
	//������Ϸ���ڷ����
	_ROOM* m_Room;
	//52����
	int m_GamePokers[_POKERS_MAX];
	//ʣ��������
	int m_iRestPokersNum;

	//���1���ƣ����21��
	int Player1Pokers[_PLAYER_MAX_POKERS];
	//��ǰ���1�е�������
	int m_iPlayer1CurPokersNum;
	//��ǰ���ܵ���
	int m_iPlayer1CurPoint;
	//�Ƿ�ֹͣҪ��
	bool m_bPlayer1Stop;

	//���2���ƣ����21��
	int Player2Pokers[_PLAYER_MAX_POKERS];
	//��ǰ���2�е�������
	int m_iPlayer2CurPokersNum;
	//��ǰ���ܵ���
	int m_iPlayer2CurPoint;
	//�Ƿ�ֹͣҪ��
	bool m_bPlayer2Stop;

	//��ǰ���в��������
	bool m_bIsPlayer1Speak;

	//����
	CBlackJack(_ROOM* r);
	//��ȡ����
	int GetNewPoker();
};

#endif