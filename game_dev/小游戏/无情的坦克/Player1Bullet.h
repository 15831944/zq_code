#ifndef _PLAYER1BULLET_H_
#define _PLAYER1BULLET_H_
#include "Bullet.h"
class CPlayer1Bullet : public CBullet
{
	//�ӵ�λ��
	POINT m_pBulletPoint;
	//�ӵ�����
	char m_cDir;
	//�ӵ�����
	char m_cBulletType;
	//�ӵ�����
	int m_iAttack;
public:
	//���������
	CPlayer1Bullet(POINT p,char dir,int att,char type);
	~CPlayer1Bullet();
	//��ȡ�ӵ�λ��
	POINT GetBulletPoint();
	//��ȡ�ӵ�������
	int GetAttack();
	//�ӵ�����
	bool BulletRun(int bianjie_R,int bianjie_D);
};
#endif