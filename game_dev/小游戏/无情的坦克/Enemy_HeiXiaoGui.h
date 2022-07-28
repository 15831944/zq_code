#ifndef _ENEMY_HEIXIAOGUI_H_
#define _ENEMY_HEIXIAOGUI_H_
#include "Enemy.h"
#include <windows.h>
class CEnemy_HeiXiaoGui : public CEnemy
{
	//Ѫ��
	int m_iHp;
	//����
	int m_iAttack;
	//�˶�����
	int m_iDir;
	//��������
	int m_iEnemyType;
	//�����Ƿ��ƶ�
	bool m_bMove;
	//λ��
	POINT m_pPoint;
public:
	CEnemy_HeiXiaoGui(int hp,int att,int dir,int type,bool move,int x,int y);
	~CEnemy_HeiXiaoGui();
	//���Ѫ��
	int GetHp();
	//����Ѫ��
	void SetHp(int hp);
	//���÷���
	void SetDir(char dir);
	//��÷���
	int GetDir();
	//�����Ƿ��ƶ�
	void SetMove(bool move);
	//����ƶ��ķ���
	int GetMove();
	//��õ��˵�����
	int GetType();
	//��õ��˵�λ��
	POINT GetEnemyPoint();
	//���õ��˵�λ��
	void SetEnemyPoint(POINT p);
	//��������
	void EnemyRun(int bianjieR,int bianjieD);
	//���˹������ӵ�
	void EnemyAttack(POINT p,int dir,std::vector<CBullet*>& vBullet);
};

#endif