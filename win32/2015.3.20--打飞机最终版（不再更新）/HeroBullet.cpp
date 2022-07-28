#include "HeroBullet.h"

CHeroBullet::CHeroBullet()
{}
CHeroBullet::~CHeroBullet()
{}
//��ʼ������Ϊλ�úͷ���
void CHeroBullet::BulletInit(POINT point,bool dir)
{
	this->m_BulletPoint = point;
	this->m_bDirect = dir;
}

//�ӵ����У����ؼ���ɳ��߽������
bool CHeroBullet::BulletRun(int bianjie)
{
	if(this->m_bDirect)
		this->m_BulletPoint.y -= 5;
	else
		this->m_BulletPoint.y += 5;
	
	if((this->m_bDirect && this->m_BulletPoint.y < bianjie)
	||(!this->m_bDirect && this->m_BulletPoint.y > bianjie))
		return false;

	return true;
}

//��ȡ�ӵ�λ��
POINT CHeroBullet::GetBulletPoint()
{
	return this->m_BulletPoint;
}