#ifndef _EMENYBULLET_H_
#define _EMENYBULLET_H_
#include "Bullet.h"

class CEmenyBullet : public CBullet
{
	POINT m_BulletPoint;//��¼�ӵ�λ��
	bool m_bDirect;//����true�ϣ�false��
public:
	CEmenyBullet();
	~CEmenyBullet();

	//��ʼ������Ϊλ�úͷ���
	void BulletInit(POINT point,bool dir);

	//�ӵ����У����ؼ���ɳ��߽������
	bool BulletRun(int bianjie);

	//��ȡ�ӵ�λ��
	POINT GetBulletPoint();
};

#endif