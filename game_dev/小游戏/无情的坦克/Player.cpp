#include "Player.h"
//���캯�������������򣬹���
CPlayer :: CPlayer(int life,int dir,int att)
	:
	m_iLife(life),
	m_iDir(dir),
	m_iAttack(att)
{
	//��ʼ����ҽ���Ϸ��λ��
	int x = CGameEngine::GetGE()->GetW();
	int y = CGameEngine::GetGE()->GetH();
	this->m_pPlayerPoint.x = 0;
	this->m_pPlayerPoint.y = 560;
}
CPlayer :: ~CPlayer()
{
}
//��������
void CPlayer :: SetLife(int life)
{
	this->m_iLife = life;
}
//�������
int CPlayer :: GetLife()
{
	return this->m_iLife;
}//���÷���
void CPlayer :: SetDir(int dir)
{
	this->m_iDir = dir;
}
//��÷���
int CPlayer :: GetDir()
{
	return this->m_iDir;
}
//���ù���
void CPlayer :: SetAttack(int attack)
{
	this->m_iAttack = attack;
}
//��ù���
int CPlayer :: GetAttack()
{
	return this->m_iAttack;
}
//������λ��
POINT CPlayer :: GetPlayerPoint()
{
	return this->m_pPlayerPoint;
}
//�������λ��
void CPlayer :: SetPlayerPoint(POINT p)
{
	this->m_pPlayerPoint = p;
}
//��ҹ������ӵ�
void CPlayer :: PlayerAttack(POINT p,std::vector<CBullet*>& vBullet)
{
	CBullet *bullet = new CPlayer1Bullet(p,m_iDir,m_iAttack,0);
	vBullet.push_back(bullet);
}
