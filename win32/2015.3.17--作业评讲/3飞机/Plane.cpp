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

//���÷ɻ�λ�ã���Ҫ���ڵл�
void CPlane::SetPlanePoint()
{}

//�ɻ����У���Ҫ���ڵл�
void CPlane::Run()
{}

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
void CPlane::Attack(POINT p)
{}