#include "Enemy.h"

CEnemy :: CEnemy()
{
}
CEnemy :: ~CEnemy()
{
}
//���Ѫ��
int CEnemy :: GetHp()
{
	return this->m_iHp;
}
//����Ѫ��
void CEnemy :: SetHp(int hp)
{
	this->m_iHp = hp;
}
//���÷���
void CEnemy :: SetDir(char dir)
{
	this->m_iDir = dir;
}
//��õ��˵ķ���
int CEnemy :: GetDir()
{
	return this->m_iDir;
}
//��õ��˵�����
int CEnemy :: GetType()
{
	return this->m_iEnemyType;
}
//�����Ƿ��ƶ�
void CEnemy :: SetMove(bool move)
{
	this->m_bMove = move;
}
//��õ�ǰ�Ƿ��ƶ��ı��
int CEnemy :: GetMove()
{
	return this->m_bMove;
}
//���õ���λ��
void CEnemy :: SetEnemyPoint(POINT p)
{
	this->m_pPoint = p;
}
//��õ��˵�λ��
POINT CEnemy :: GetEnemyPoint()
{
	return this->m_pPoint;
}
void CEnemy :: EnemyAttack(POINT p,int dir,std::vector<CBullet*>& vBullet)
{
	
}
//�����ƶ��������߽�ı䷽��
void CEnemy :: EnemyRun(int bianjieR,int bianjieD)
{			
	if(m_bMove)
	{
		//��
		if(this->m_iDir == 0)
		{
			if(this->m_pPoint.y>=80 )
				this->m_pPoint.y -= PIXEL_MOVE;
			else 
				this->m_iDir = rand()%4;
		}
		//��
		if(this->m_iDir == 1)
		{
			if(this->m_pPoint.y<=bianjieD -ENEMY_H) 
				this->m_pPoint.y += PIXEL_MOVE;
			else 
				this->m_iDir = rand()%4;
		}
		//��
		if(this->m_iDir == 2)
		{
			if(this->m_pPoint.x>=0 )
				this->m_pPoint.x -= PIXEL_MOVE;
			else
				this->m_iDir = rand()%4;
		}
		//��
		if(this->m_iDir == 3)
		{
			if(this->m_pPoint.x<=bianjieR-ENEMY_W)
				this->m_pPoint.x += PIXEL_MOVE;
			else 
				this->m_iDir = rand()%4;
		}	
	}
}