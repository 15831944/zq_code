#include "EmenyBullet.h"

CEmenyBullet::CEmenyBullet()
{}
CEmenyBullet::~CEmenyBullet()
{}
//��ʼ������Ϊλ�úͷ���
void CEmenyBullet::BulletInit(POINT point,bool dir)
{
	this->m_BulletPoint = point;
	this->m_bDirect = dir;
}

//�ӵ����У����ؼ���ɳ��߽������
bool CEmenyBullet::BulletRun(int bianjie)
{
	if(this->m_bDirect)
		this->m_BulletPoint.y --;
	else
		this->m_BulletPoint.y ++;
	
	if((this->m_bDirect && this->m_BulletPoint.y < bianjie)
	||(!this->m_bDirect && this->m_BulletPoint.y > bianjie))
		return false;

	return true;
}

//��ȡ�ӵ�λ��
POINT CEmenyBullet::GetBulletPoint()
{
	return this->m_BulletPoint;
}