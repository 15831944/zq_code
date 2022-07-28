#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <windows.h>
#include <vector>
#include "Bullet.h"
#include "GameEngine.h"
//����ͼƬ���ؿ��
#define ENEMY_W 40
#define ENEMY_H 40
//�����˶���ʱ��
#define ENEMY_TIME 70
//����ѭ��һ���ƶ���������
#define PIXEL_MOVE 5
class CBullet;
class CEnemy
{
	//Ѫ��
	int m_iHp;
	//������
	int m_iAttack;
	//����
	int m_iDir;
	//��������
	int m_iEnemyType;
	//�Ƿ��ƶ������ڼ����ײ��ʱ�����ܶ����ϰ���ʱ����޷��ƶ���
	bool m_bMove;
	//λ��
	POINT m_pPoint;
public:
	CEnemy();
	virtual ~CEnemy();
	//���Ѫ��
	virtual int GetHp();
	//����Ѫ��
	virtual void SetHp(int hp);
	//���÷���
	virtual void SetDir(char dir);
	//��÷���
	virtual int GetDir();
	//�����Ƿ��ƶ���ֻҪ������ײ��⣩
	virtual void SetMove(bool move);
	//��õ�ǰ�Ƿ��ƶ�
	virtual int GetMove();
	//��õ�������
	virtual int GetType();
	//��õ���λ��
	virtual POINT GetEnemyPoint();
	//���õ���λ��
	virtual void SetEnemyPoint(POINT p);
	//��������
	virtual void EnemyRun(int bianjieR,int bianjieD);
	//���˹��������ӵ�
	virtual void EnemyAttack(POINT p,int dir,std::vector<CBullet*>& vBullet);
};
#endif