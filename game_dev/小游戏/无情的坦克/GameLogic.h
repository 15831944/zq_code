#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Boom.h"
#include "Items.h"
#include <vector>
#include <map>
#include <string>
//��Ϸ�߼��ࣨ���ࣩ
class CGameLogic
{
	//��ͼ�ϰ��ṹ��
	struct ZHANGAI
	{
		int m_iType;
		int m_iDefence;
		RECT m_rRect;
	};
	//�����ָ��
	CPlayer * m_pPlayer;
	//�ͻ����ұ߽���±߽�
	int m_BianJieR;
	int m_BianJieD;
	//��ǰ�ؿ�
	int m_iStage;
	//����
	int m_iScore;
	//�Ѿ����ֵĵ�������
	int m_ItemsNum;
	//��ǰ����ʣ���������
	int m_iEnemyNum;
	//���1���ӵ�
	std::vector<CBullet*> m_vPlayer1Bullet;
	//�����ӵ���
	std::vector<CBullet*> m_vEnemyBullet;
	//���˱�
	std::vector<CEnemy*> m_vEnemy;
	//��ͼ�ϰ��ı�
	std::vector<ZHANGAI> m_vZhangAi;
	//��ըЧ����
	std::vector<CBoom*> m_vBoom;
	//���߱�
	std::vector<CItems*> m_vItems;
public:
	CGameLogic();
	~CGameLogic();
	void pengzhuang();
	//��Ϸ��ʼ��
	void GameInit();
	//��ù�����������
	int GetEnemyNum();
	//���ÿͻ����ұ߽�
	void SetBianjieR(int bianjieR);
	////���ÿͻ����±߽�
	void SetBianjieD(int bianjieD);
	//���÷���
	void SetScore(int score);
	//���ùؿ�
	void SetStage(int stage);
	//���õ�������
	void SetItemsNum(int itemnum);
	//���õ��˵�����
	void SetEnemyNum(int enemynum);
	//������ҹ���
	void SetPlayerAtt(int att);
	//�����������
	void SetPlayerLife(int life);
	//��������ָ��
	CPlayer* GetPlayer();
	//��ͼ�����ϰ�
	void SetMapStage1();
	//��Ϸ����
	void GameRun();
	//���Ƶ�ͼԪ��
	void Paint();
	//�������1�ķ���
	void SetPlayerDir(char dir);
	//�����ҵ�����ֵ
	int GetPlayerLife();
	//���1�Ĺ���
	void SetPlayerAttack(POINT p);
	//������ҵ�λ��
	void SetPlayerPoint(POINT p);
	//�����ҵ�λ��
	POINT GetPlayerPoint();
	//��ҵ��ƶ������
	void PlayerMove();
	//��ײ���
	void PengZhaungJianCe();
	void CreateItems();
	//��������
	void CreateEnemy();
	//ʰȡ����
	void PlayerGetItem();
	//������Ϸ
	void WriteGame();
};
#endif