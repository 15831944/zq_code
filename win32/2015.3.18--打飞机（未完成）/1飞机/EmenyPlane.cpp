#include "EmenyPlane.h"
#include <iostream>
#include <time.h>
#include "EmenyBullet.h"

CEmenyPlane::CEmenyPlane()
{
}
CEmenyPlane::~CEmenyPlane()
{}

//��ʼ����������ʼ���ɻ���λ�ã�Ѫ��
void CEmenyPlane::Init(POINT p)
{
	this->m_Point = p;
	this->m_iHp = 100;
	srand((unsigned int)time(0));
	this->m_iDirect = rand() % 3;
	m_iTimeAtt = rand() % 3;
}

//�ɻ����У���Ҫ���ڵл�,���ؼ��򱾻��������ޣ�����
bool CEmenyPlane::Run(int right,int bottom,std::vector<CBullet*> vBullet)
{
	this->m_Point.y ++;	
	if(this->m_iDirect == 1)
		this->m_Point.x --;
	else if(this->m_iDirect == 2)
		this->m_Point.x ++;

	if(this->m_Point.x < 0 || this->m_Point.x > right
		|| this->m_Point.y > bottom)
		return false;

	if(m_iTimeAtt > 0)
		m_iTimeAtt--; 
	else
	{
		m_iTimeAtt = rand() % 3;
		Attack(this->m_Point,vBullet);
	}
	return true;
}

//����Ѫ��
void CEmenyPlane::SetHP(int hp)
{
	this->m_iHp = hp;
}

//��ȡѪ��
int CEmenyPlane::GetHP()
{
	return this->m_iHp;
}

//��ȡλ��
POINT CEmenyPlane::GetPoint()
{
	return this->m_Point;
}

//����
void CEmenyPlane::Attack(POINT p,std::vector<CBullet*> vBullet)
{
	CBullet* bullet = new CEmenyBullet;
	bullet->BulletInit(p,false);
	vBullet.push_back(bullet);
}