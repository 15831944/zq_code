#include "Plane.h"

CPlane::CPlane()
{
}
CPlane::~CPlane()
{}

//��ʼ����������ʼ���ɻ���λ�ã�Ѫ��
void CPlane::Init(POINT p)
{}
//���÷ɻ�λ�ã���Ҫ����Ӣ��
void CPlane::SetPlanePoint(POINT p)
{}

//�ɻ����У���Ҫ���ڵл�
bool CPlane::Run(int right,int bottom,std::vector<CBullet*> vBullet)
{
	return true;
}

//����Ѫ��
void CPlane::SetHP(int hp)
{}

//��ȡѪ��
int CPlane::GetHP()
{
	return m_iHp;
}

//��ȡλ��
POINT CPlane::GetPoint()
{
	return m_Point;
}

//����
void CPlane::Attack(POINT p,std::vector<CBullet*> vBullet)
{}