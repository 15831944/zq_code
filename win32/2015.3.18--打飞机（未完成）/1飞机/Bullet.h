#ifndef _BULLET_H_
#define _BULLET_H_
#include <windows.h>

class CBullet
{
	POINT m_BulletPoint;//��¼�ӵ�λ��
	bool m_bDirect;//����true�ϣ�false��
public:
	CBullet();
	virtual ~CBullet();

	//��ʼ������Ϊλ�úͷ���
	virtual void BulletInit(POINT point,bool dir);

	//�ӵ����У����ؼ���ɳ��߽������
	virtual bool BulletRun(int bianjie);

	//��ȡ�ӵ�λ��
	virtual POINT GetBulletPoint();
};

#endif