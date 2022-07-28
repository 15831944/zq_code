#ifndef _BULLET_H_
#define _BULLET_H_
#include <Windows.h>
//�˶��ķ���
#define _DIR_UP_	0
#define _DIR_DOWN_	1
#define _DIR_LEFT_	2
#define _DIR_RIGHT_ 3

//�ӵ������ٶ�
#define BULLET_SPEED 15

class CBullet
{
	//�ӵ�λ��
	POINT m_pBulletPoint;
	//�ӵ�����
	char m_cDir;
	//�ӵ�����
	char m_cBulletType;
	//�ӵ��Ĺ���
	int m_iAttack;
public:
	CBullet();
	virtual ~CBullet();
	//ͨ���ӵ������ĵ��˵Ĺ�����
	virtual int GetAttack();
	//����ӵ�λ��
	virtual POINT GetBulletPoint();
	//�ӵ����У������߽������
	virtual bool BulletRun(int bianjie_R,int bianjie_D);
};
#endif