#include "Bullet.h"

CBullet::CBullet()
{}
CBullet::~CBullet()
{}
//��ʼ������Ϊλ�úͷ���
void CBullet::BulletInit(POINT point,bool dir)
{
}

//�ӵ����У����ؼ���ɳ��߽������
bool CBullet::BulletRun(int bianjie)
{
	return true;
}

//��ȡ�ӵ�λ��
POINT CBullet::GetBulletPoint()
{
	return this->m_BulletPoint;
}