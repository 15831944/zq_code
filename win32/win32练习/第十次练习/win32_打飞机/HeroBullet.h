#ifndef _HEROBULLET_H_
#define _HEROBULLET_H_
#include "Bullet.h"

class CHeroBullet : public CBullet
{
	POINT m_BulletPoint;//��¼�ӵ�λ��
	bool m_bDirect;//����true�ϣ�false��
public:
	CHeroBullet();
	~CHeroBullet();

	//��ʼ������Ϊλ�úͷ���
	void BulletInit(POINT point,bool dir);

	//�ӵ����У����ؼ���ɳ��߽������
	bool BulletRun(int bianjie);

	//��ȡ�ӵ�λ��
	POINT GetBulletPoint();
};

#endif