#include "HeroPlane.h"
#include "HeroBullet.h"

CHeroPlane::CHeroPlane()
{}
CHeroPlane::~CHeroPlane()
{}

//��ʼ����������ʼ���ɻ���λ�ã�Ѫ��
void CHeroPlane::Init(POINT p)
{
	this->m_Point = p;
	this->m_iHp = 100;
}

//���÷ɻ�λ�ã���Ҫ����Ӣ��
void CHeroPlane::SetPlanePoint(POINT p)
{
	this->m_Point = p;
}

//����Ѫ��
void CHeroPlane::SetHP(int hp)
{
	this->m_iHp = hp;
}

//��ȡѪ��
int CHeroPlane::GetHP()
{
	return this->m_iHp;
}

//��ȡλ��
POINT CHeroPlane::GetPoint()
{
	return this->m_Point;
}

//����
void CHeroPlane::Attack(POINT p,std::vector<CBullet*>& vBullet)
{
	CBullet* bullet = new CHeroBullet;
	bullet->BulletInit(p,true);
	vBullet.push_back(bullet);
}