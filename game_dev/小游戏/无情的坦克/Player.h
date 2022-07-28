#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <Windows.h>
#include <vector>
#include "GameEngine.h"
#include "Bullet.h"
#include "Player1Bullet.h"
#define _GRIDE_W_ 40
#define _GRIDE_H_ 40

#define _DIR_UP_	0
#define _DIR_DOWN_	1
#define _DIR_LEFT_	2
#define _DIR_RIGHT_ 3
class CBullet;
class CPlayer
{
	//����
	int m_iLife;
	//��ǰ����
	char m_iDir;
	//��ǰ����
	int m_iAttack;
	//��ǰλ��
	POINT m_pPlayerPoint;
public:
	CPlayer(int life,int dir,int att);
	~CPlayer();
	//���õ�ǰ����ͻ�÷���
	void SetDir(int dir);
	int GetDir();
	//��õ�ǰλ�ú����õ�ǰλ��
	POINT GetPlayerPoint();
	void SetPlayerPoint(POINT p);
	//��õ�ǰ��������������
	void SetLife(int life);
	int GetLife();
	//��õ�ǰ���������ù���
	int GetAttack();
	void SetAttack(int attack);
	//�������ӵ�
	void PlayerAttack(POINT p,std::vector<CBullet*>& vBullet);
};
#endif