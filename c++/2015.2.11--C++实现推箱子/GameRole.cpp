#include "GameRole.h"

//��Ϸ��ɫ��ʼ������,x,y,r����x���꣬y���꣬r��ɫ����
void CGameRole::Init(int x,int y,Role r)
{
	this->m_iX = x;
	this->m_iY = y;
	this->m_role = r;
}
//�������ú���
void CGameRole::SetZuoBiao(int x,int y)
{
	this->m_iX = x;
	this->m_iY = y;
}

//���ý�ɫ����
void CGameRole::SetEnumRole(Role r)
{
	this->m_role = r;
}

//��ȡ��ɫ��X����
int CGameRole::GetZBX()
{
	return this->m_iX;
}

//��ȡ��ɫ��Y����
int CGameRole::GetZBY()
{
	return this->m_iY;
}

//��ȡ��ɫ����
Role CGameRole::GetRole()
{
	return this->m_role;
}