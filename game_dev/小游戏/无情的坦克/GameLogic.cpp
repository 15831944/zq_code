#include "GameLogic.h"
#include <Windows.h>
#include "GameEngine.h"
#include "Player1Bullet.h"
#include "Boom_Player_Enemy.h"
#include "Boom_Enemy_Player.h"
#include "Boom_Player_ZhangAi.h"
#include "Boom_Enemy_ZhangAi.h"
#include "Items_ShenLvMoGu.h"
#include "Items_QianLvMoGu.h"
#include "Items_HongMoGu.h"
#include "Enemy_BaiXiaoGui.h"
#include "Enemy_BaiXiaoHua.h"
#include "Enemy_HeiXiaoGui.h"
#include "Enemy_LanXiaoGui.h"
#include "Bullet_BaiXiaoGui.h"
#include "Bullet_BaiXiaoHua.h"
#include "Bullet_HeiXiaoGui.h"
#include "Bullet_LanXiaoGui.h"
using namespace std;
//���ˣ�����˶��ķ���
#define _DIR_UP_	0
#define _DIR_DOWN_	1
#define _DIR_LEFT_	2
#define _DIR_RIGHT_ 3
//��������
#define E_BAIXIAOGUI_ 0
#define E_HEIXIAOGUI_ 1
#define E_LANXIAOGUI_ 2
#define E_BAIXIAOHUA_ 3

//���ӿ��
#define GRID_W 40
#define GRID_H 40
//��Ҹ��Կ��
#define PLAYER_W 40
#define PLAYER_H 40
//��Ϸ��ʾ��Ϣ���ĸ�
#define INFO_H 80
//��һ�ص�ͼ�ϰ�
static char map1[]={
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,1,4,0,0,0,0,3,0,3,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,
		0,0,3,0,0,0,4,0,0,0,1,4,0,0,0,0,2,0,4,0,
		0,0,0,2,0,0,0,0,1,0,0,0,1,0,0,2,0,2,0,0,
		1,0,3,0,3,0,0,1,0,0,0,4,0,1,0,1,4,0,0,1,
		1,0,0,0,0,2,1,0,0,0,4,0,0,2,0,0,1,0,0,1,
		1,1,4,1,0,0,0,0,0,1,2,0,0,0,4,0,0,0,0,0,
		0,0,0,1,0,0,0,1,0,0,0,0,1,2,0,0,1,4,0,0,
		1,0,0,0,3,0,0,2,0,1,0,0,0,1,0,0,0,0,0,1,
		1,0,0,0,1,0,4,0,0,0,0,3,0,1,0,0,0,0,1,0,
		0,0,0,0,1,1,0,0,1,0,0,1,0,0,1,0,1,0,0,0,
		0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,2
	};
//���������
CGameLogic :: CGameLogic()
{
	this->m_pPlayer = new CPlayer(10,0,1);
}
//�����������ͷſ��Ķ�
CGameLogic :: ~CGameLogic()
{
	delete m_pPlayer;
	for(std::vector<CBullet*> ::iterator i = m_vPlayer1Bullet.begin(); i!=m_vPlayer1Bullet.end();++i)
		delete (*i);
	for(std::vector<CBullet*> ::iterator i = m_vEnemyBullet.begin(); i!=m_vEnemyBullet.end();++i)
		delete (*i);
	for(std::vector<CEnemy*> ::iterator i = m_vEnemy.begin(); i!=m_vEnemy.end();++i)
		delete (*i);
	for(std::vector<CBoom*> ::iterator i = m_vBoom.begin(); i!=m_vBoom.end();++i)
		delete (*i);
	for(std::vector<CItems*> ::iterator i = m_vItems.begin(); i!=m_vItems.end();++i)
		delete (*i);
}
//������Ϸ
void CGameLogic ::  WriteGame()
{
	//������Ϸ�ķ�����������������
	CGameEngine::GetGE()->GetWF()->Create();
	CGameEngine::GetGE()->GetWF()->WriteMemory(&m_iStage,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&m_BianJieD,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&m_BianJieR,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&m_iEnemyNum,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&m_iScore,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&m_ItemsNum,4);
	int att = m_pPlayer->GetAttack();
	int dir = m_pPlayer->GetDir();
	int life = m_pPlayer->GetLife();
	POINT p = {0,560};
	CGameEngine::GetGE()->GetWF()->WriteMemory(&att,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&dir,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&life,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&p,sizeof(POINT));
	CGameEngine::GetGE()->GetWF()->Write("save\\save1");
}
//��ʼ����ͼԪ�ر�
void CGameLogic :: SetMapStage1()
{
	for(int i = 0;i < 15; ++i)
	{
		for(int j = 0;j < 20 ;++j)
		{
			if(::map1[j+i*20] >= 1)
			{
				//�ѵ�ǰ��ͼ���ϰ�������һ��������
				ZHANGAI za;
				RECT r={j*40,i*40,j*40+40,i*40+40};
				za.m_iType = ::map1[j+i*20];
				if(za.m_iType == 1)
					za.m_iDefence = 6;
				switch (za.m_iType)
				{
				case 1:za.m_iDefence = 6 ;break;
				case 2:za.m_iDefence = 10 ;break;
				case 3:za.m_iDefence = -1 ;break;
				case 4:za.m_iDefence = -1 ;break;
				}
				za.m_rRect =r;
				this->m_vZhangAi.push_back(za);
			}
		}
	}
}
//��Ϸ��ʼ��
void CGameLogic :: GameInit()
{
	//�õ���ǰ�ͻ������
	int w = CGameEngine::GetGE()->GetW();
	int h = CGameEngine::GetGE()->GetH();
	//��ʼ���������������������ʵ������Ҷ���
	this->m_iStage = 1;
	this->m_iScore = 0;
	this->m_ItemsNum = 0;
	this->m_iEnemyNum = 30;
	this->m_BianJieR = w;
	this->m_BianJieD = h;
	this->m_pPlayer->SetAttack(1);
	this->m_pPlayer->SetDir(0);
	this->m_pPlayer->SetLife(30);
	POINT p={0,560};
	this->m_pPlayer->SetPlayerPoint(p);
	//��ձ�
	this->m_vPlayer1Bullet.clear();
	this->m_vEnemyBullet.clear();
	this->m_vEnemy.clear();
	this->m_vBoom.clear();
	this->m_vZhangAi.clear();
	this->m_vItems.clear();
	//���õ�������
	//ÿ������Ϊ3��
	for(int i =0 ;i<3;++i)
	{
		CItems* p = new CShenLvMoGU("����Ģ��",5,0,0,false);
		m_vItems.push_back(p);
	}
	for(int i =0 ;i<3;++i)
	{
		CItems* p = new CQianLvMoGU("ǳ��Ģ��",0,5,0,false);
		m_vItems.push_back(p);
	}
	for(int i =0 ;i<3;++i)
	{
		CItems* p = new CHongMoGU("��Ģ��",0,0,5,false);
		m_vItems.push_back(p);
	}
	
}
//���õ�ǰ�ؿ�
void CGameLogic :: SetStage(int stage)
{
	this->m_iStage = stage;
}
//������ҹ���
void CGameLogic :: SetPlayerAtt(int att)
{
	this->m_pPlayer->SetAttack(att);
}
//�����������
void CGameLogic :: SetPlayerLife(int life)
{
	this->m_pPlayer->SetLife(life);
}
//���������ָ��
CPlayer* CGameLogic :: GetPlayer()
{
	return this->m_pPlayer;
}
//���ÿͻ����ұ߽�
void CGameLogic :: SetBianjieR(int bianjieR)
{
	this->m_BianJieR = bianjieR;
}
//���ÿͻ�����߽�
void CGameLogic ::SetBianjieD(int bianjieD)
{
	this->m_BianJieD = bianjieD;
}
//���÷���
void CGameLogic ::SetScore(int score)
{
	this->m_iScore = score;
}
//���õ�������
void CGameLogic ::SetItemsNum(int itemnum)
{
	this->m_ItemsNum = itemnum;
}
//���õ�������
void CGameLogic ::SetEnemyNum(int enemynum)
{
	this->m_iEnemyNum = enemynum;
}
//����������ֵ
int CGameLogic :: GetPlayerLife()
{
	return m_pPlayer->GetLife();
}
//������ҵĹ���
void CGameLogic :: SetPlayerAttack(POINT p)
{
	this->m_pPlayer->PlayerAttack(p,m_vPlayer1Bullet);
}
//������ҵķ���
void CGameLogic :: SetPlayerDir(char dir)
{
	this->m_pPlayer->SetDir(dir);
}
//������ҵ�λ��
void CGameLogic :: SetPlayerPoint(POINT p)
{
	this->m_pPlayer->SetPlayerPoint(p);
}
//�����ҵ�λ��
POINT CGameLogic :: GetPlayerPoint()
{
	return this->m_pPlayer->GetPlayerPoint();
}
//��õ�����������
int CGameLogic :: GetEnemyNum()
{
	return this->m_iEnemyNum;
}
//���1�Ĳ����ƶ�
void CGameLogic :: PlayerMove()
{
	//�߽��ж�
	if( GetPlayerPoint().x>=0 && GetPlayerPoint().x <=m_BianJieR
		&& GetPlayerPoint().y>=0 && GetPlayerPoint().y<=m_BianJieD)
	{
		POINT p;
		RECT heroRect;//Ӣ�۾���
		RECT enemyRect;//���˾���
		RECT linshiRect;//��ʱ����
		bool pengzhuang =false;
		//�ϲ���
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_W) == _KS_DH)
		{	
			SetPlayerDir(_DIR_UP_);
			p.x = GetPlayerPoint().x;
			p.y = GetPlayerPoint().y - 5;
			heroRect.left = p.x;
			heroRect.top = p.y;
			heroRect.right = p.x +PLAYER_H;
			heroRect.bottom = p.y +PLAYER_H;
			//�����ϰ��޷�ǰ��
			for(std::vector<ZHANGAI> ::iterator i=m_vZhangAi.begin();i!=m_vZhangAi.end();++i)
			{
				if(IntersectRect(&linshiRect,&heroRect,&i->m_rRect))
					return;
			}
			//���������޷�ǰ��
			for(std::vector<CEnemy*>::iterator i = m_vEnemy.begin(); i != m_vEnemy.end();++i)
			{
				enemyRect.left = (*i)->GetEnemyPoint().x;
				enemyRect.top = (*i)->GetEnemyPoint().y;
				enemyRect.right =(*i)->GetEnemyPoint().x +40;
				enemyRect.bottom = (*i)->GetEnemyPoint().y +40 ;
				if(IntersectRect(&linshiRect,&heroRect,&enemyRect))
						return ;
			}
			//�����û�У��������ƶ�
			if(!pengzhuang)
				SetPlayerPoint(p);
			if(p.y < 80)
			{
				p.y = 80;
				SetPlayerPoint(p);
			}
			
		}
		//�²���
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_S) == _KS_DH)
		{
			p.x = GetPlayerPoint().x;
			p.y = GetPlayerPoint().y + 5;
			SetPlayerDir(_DIR_DOWN_);
			heroRect.left = p.x;
			heroRect.top = p.y;
			heroRect.right = p.x +PLAYER_H;
			heroRect.bottom = p.y +PLAYER_H;
			//�����ϰ��޷�ǰ��
			for(std::vector<ZHANGAI> ::iterator i=m_vZhangAi.begin();i!=m_vZhangAi.end();++i)
			{
				if(IntersectRect(&linshiRect,&heroRect,&i->m_rRect))
					return;
			}
			//���������޷�ǰ��
			for(std::vector<CEnemy*>::iterator i = m_vEnemy.begin(); i != m_vEnemy.end();++i)
			{
				enemyRect.left = (*i)->GetEnemyPoint().x;
				enemyRect.top = (*i)->GetEnemyPoint().y;
				enemyRect.right =(*i)->GetEnemyPoint().x +40;
				enemyRect.bottom = (*i)->GetEnemyPoint().y +40 ;
				if(IntersectRect(&linshiRect,&heroRect,&enemyRect))
						return ;
			}
			//�����û�У�������ǰ��
			if(!pengzhuang)
				SetPlayerPoint(p);
			if(p.y > m_BianJieD - 40)
			{
				p.y = m_BianJieD - 40;
				SetPlayerPoint(p);
			}
			
		}
		//�����
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_A) == _KS_DH)
		{
			p.x = GetPlayerPoint().x -5;
			p.y = GetPlayerPoint().y;
			SetPlayerDir(_DIR_LEFT_);
					heroRect.left = p.x;
			heroRect.top = p.y;
			heroRect.right = p.x +PLAYER_W;
			heroRect.bottom = p.y +PLAYER_W;
			//�����ϰ��޷�ǰ��
			for(std::vector<ZHANGAI> ::iterator i=m_vZhangAi.begin();i!=m_vZhangAi.end();++i)
			{
				if(IntersectRect(&linshiRect,&heroRect,&i->m_rRect))
					return;
			}
			//���������޷�ǰ��
			for(std::vector<CEnemy*>::iterator i = m_vEnemy.begin(); i != m_vEnemy.end();++i)
			{
				enemyRect.left = (*i)->GetEnemyPoint().x;
				enemyRect.top = (*i)->GetEnemyPoint().y;
				enemyRect.right =(*i)->GetEnemyPoint().x +40;
				enemyRect.bottom = (*i)->GetEnemyPoint().y +40 ;
				if(IntersectRect(&linshiRect,&heroRect,&enemyRect))
						return ;
			}
			//�����û�У�������ǰ��
			if(!pengzhuang)
				SetPlayerPoint(p);
			if(p.x<0)
			{
				p.x=0;
				SetPlayerPoint(p);
			}
		}
		//�Ҳ���
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_D) == _KS_DH)
		{
			p.x = GetPlayerPoint().x + 5;
			p.y = GetPlayerPoint().y ;
			SetPlayerDir(_DIR_RIGHT_);
			heroRect.left = p.x;
			heroRect.top = p.y;
			heroRect.right = p.x +PLAYER_W;
			heroRect.bottom = p.y +PLAYER_W;
			//�����ϰ��޷�ǰ��
			for(std::vector<ZHANGAI> ::iterator i=m_vZhangAi.begin();i!=m_vZhangAi.end();++i)
			{
				if(IntersectRect(&linshiRect,&heroRect,&i->m_rRect))
					return;
			}
			//���������޷�ǰ��
			for(std::vector<CEnemy*>::iterator i = m_vEnemy.begin(); i != m_vEnemy.end();++i)
			{
				enemyRect.left = (*i)->GetEnemyPoint().x;
				enemyRect.top = (*i)->GetEnemyPoint().y;
				enemyRect.right =(*i)->GetEnemyPoint().x +40;
				enemyRect.bottom = (*i)->GetEnemyPoint().y +40 ;
				if(IntersectRect(&linshiRect,&heroRect,&enemyRect))
						return ;
			}
			//�����û�У�������ǰ��
			if(!pengzhuang)
				SetPlayerPoint(p);
			if(p.x > m_BianJieR - 40)
			{
				p.x = m_BianJieR - 40;
				SetPlayerPoint(p);
			}
		}
	}
	//�����
	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_J) == _KS_DC)
	{
			SetPlayerAttack(GetPlayerPoint());
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("������");
	}
}
//��������
void CGameLogic :: CreateItems()
{
	RECT itemRect;
	RECT linshiRect;
	//����Ϊ20%�����ҵ�ͼ������3������
	if( rand()% 20 == 0 && m_ItemsNum <3)
	{
		int x = rand() % (this->m_BianJieR - 40);
		int y = rand() % 200 + 80;
		itemRect.left = x;
		itemRect.top = y ;
		itemRect.right = x + 40;
		itemRect.bottom = y + 40;
		//���ֵ�λ�ò��ܺ��ϰ��غ�
		for(vector<ZHANGAI> ::iterator j=m_vZhangAi.begin();j!=m_vZhangAi.end();++j)
		{
			if(IntersectRect(&linshiRect,&itemRect,&j->m_rRect))
				return ;
		}
		int suiji = rand()% 9;
		for(int i=0;i< (int)m_vItems.size(); ++i)
		{
			if(suiji == i && !m_vItems.at(i)->GetApper())
			{
				//���ֺ�Ģ��
				if(strcmp(m_vItems.at(i)->GetName().c_str(),"��Ģ��") == 0)
				{
					m_vItems.at(i)->SetRect(itemRect);
					m_vItems.at(i)->SetApper(true);
				}
				//��������Ģ��
				if(strcmp(m_vItems.at(i)->GetName().c_str(),"����Ģ��") == 0)
				{
					m_vItems.at(i)->SetRect(itemRect);
					m_vItems.at(i)->SetApper(true);
				}
				//����ǳ��Ģ��
				if(strcmp(m_vItems.at(i)->GetName().c_str(),"ǳ��Ģ��") == 0)
				{
					m_vItems.at(i)->SetRect(itemRect);
					m_vItems.at(i)->SetApper(true);
				}
				m_ItemsNum ++ ;
				break;
			}
		}
	}
}
//�񵽵���
void CGameLogic :: PlayerGetItem()
{
	RECT heroRect;//Ӣ�۾���
	RECT linshiRect;//��ʱ����
	//���Ӣ��λ��
	heroRect.left = m_pPlayer->GetPlayerPoint().x;
	heroRect.top = m_pPlayer->GetPlayerPoint().y;
	heroRect.right = m_pPlayer->GetPlayerPoint().x + 40;
	heroRect.bottom = m_pPlayer->GetPlayerPoint().y + 40;
	//�������߱�
	for(vector<CItems*> ::iterator i=m_vItems.begin();i!=m_vItems.end();++i)
	{
		//���߳����˲����ж�
		if((*i)->GetApper())
		{
			//ʰȡ���˵���
			if(IntersectRect(&linshiRect,&heroRect,&(*i)->GetRect()))
			{
				//���ݵ������ͣ���һ����Ӧ����
				if(strcmp((*i)->GetName().c_str(),"��Ģ��") == 0)
					m_pPlayer->SetLife(m_pPlayer->GetLife() + (*i)->GetHp());
				if(strcmp((*i)->GetName().c_str(),"����Ģ��") == 0)
					m_pPlayer->SetLife(m_pPlayer->GetLife() + (*i)->GetDefence());
				if(strcmp((*i)->GetName().c_str(),"ǳ��Ģ��") == 0)
					m_pPlayer->SetAttack(m_pPlayer->GetAttack()+(*i)->GetAtt());
				i = m_vItems.erase(i);
				m_ItemsNum -- ;
				break;
			}
		}
	}
}
//��������
void CGameLogic :: CreateEnemy()
{
	RECT heroRect;//Ӣ�۾���
	RECT linshiRect;//��ʱ����
	RECT enemyRect;//���˾���
	RECT enemyRect1;//���˾���
	//�����ĵ����ڿͻ�����
	bool add = true;
	int x = CGameEngine::GetGE()->GetW();
	x = rand() % 152;
	x *= 5;
	int y = rand() % 96;
	y *= 5;
	y += 80;
	enemyRect1.left  = x;
	enemyRect1.top = y;
	enemyRect1.right = x + 40;
	enemyRect1.bottom = y +40;
	heroRect.left = m_pPlayer->GetPlayerPoint().x;
	heroRect.top = m_pPlayer->GetPlayerPoint().y;
	heroRect.right = m_pPlayer->GetPlayerPoint().x + 40;
	heroRect.bottom = m_pPlayer->GetPlayerPoint().y + 40;
	//�����ĵ��˲��ܺ�����غ�
	if(IntersectRect(&linshiRect,&enemyRect1,&heroRect))
		return;
	//�����ĵ��˲��ܺ����е����غ�
	for(std::vector<CEnemy*>::iterator i = m_vEnemy.begin(); i != m_vEnemy.end();++i)
	{
		enemyRect.left = (*i)->GetEnemyPoint().x;
		enemyRect.top = (*i)->GetEnemyPoint().y;
		enemyRect.right =(*i)->GetEnemyPoint().x +40;
		enemyRect.bottom = (*i)->GetEnemyPoint().y +40 ;
		if(IntersectRect(&linshiRect,&enemyRect1,&enemyRect))
				return ;
	}
	//�����ĵ��˲��ܺ��ϰ��غ�
	for(vector<ZHANGAI> ::iterator j=m_vZhangAi.begin();j!=m_vZhangAi.end();++j)
	{
		if(IntersectRect(&linshiRect,&enemyRect1,&j->m_rRect))
			return ;
	}
	//�������ˣ����10��
	if(rand() % 10 == 0 && add && (int)m_vEnemy.size() < m_iEnemyNum)
	{
		if(this->m_iEnemyNum > 0)
		{
			CEnemy * enemy;
			int suiji = rand()%4;
			//�������һ�ֵ���
			if(suiji == E_BAIXIAOGUI_)
				enemy = new CEnemy_BaiXiaoGui(2,2,rand()%4,E_BAIXIAOGUI_,true,enemyRect1.left,enemyRect1.top);
			if(suiji == E_HEIXIAOGUI_)
				enemy = new CEnemy_HeiXiaoGui(2,6,rand()%4,E_HEIXIAOGUI_,true,enemyRect1.left,enemyRect1.top);
			if(suiji == E_LANXIAOGUI_)
				enemy = new CEnemy_LanXiaoGui(3,5,rand()%4,E_LANXIAOGUI_,true,enemyRect1.left,enemyRect1.top);
			if(suiji == E_BAIXIAOHUA_)
				enemy = new CEnemy_BaiXiaoHua(4,8,rand()%4,E_BAIXIAOHUA_,true,enemyRect1.left,enemyRect1.top);
			this->m_vEnemy.push_back(enemy);
		}
	}
}
//----��Ϸ����----
//-------����-----
//---���˵�����--
//---�ӵ�������--
//---��ײ�ļ��--
void CGameLogic :: GameRun()
{
	RECT enemyBulletRect;//�����ӵ�����
	RECT heroBulletRect;//Ӣ���ӵ�����
	RECT linshiRect;//��ʱ����
	//��������
	CreateEnemy();
	//��������
	CreateItems();
	//ʰȡ���߼��
	PlayerGetItem();
	//��ײ���
	PengZhaungJianCe();
	//���˵����У����ӵ�
	for(vector<CEnemy*>::iterator i=m_vEnemy.begin();i!=m_vEnemy.end();++i)
	{
		//20%���ʷ�һ���ӵ�
		if(rand() % 10 == 0)
		{
			if((*i)->GetType() == E_BAIXIAOGUI_)
				(*i)->EnemyAttack((*i)->GetEnemyPoint(),(*i)->GetDir(),this->m_vEnemyBullet);
			if((*i)->GetType() == E_BAIXIAOHUA_)
				(*i)->EnemyAttack((*i)->GetEnemyPoint(),(*i)->GetDir(),this->m_vEnemyBullet);
			if((*i)->GetType() == E_HEIXIAOGUI_)
				(*i)->EnemyAttack((*i)->GetEnemyPoint(),(*i)->GetDir(),this->m_vEnemyBullet);
			if((*i)->GetType() == E_LANXIAOGUI_)
				(*i)->EnemyAttack((*i)->GetEnemyPoint(),(*i)->GetDir(),this->m_vEnemyBullet);
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("�������");
		}
		(*i)->EnemyRun(this->m_BianJieR,this->m_BianJieD);
	}
	//���1���ӵ����ϰ�����ײ
	for(vector<CBullet*>::iterator i=m_vPlayer1Bullet.begin();i!=m_vPlayer1Bullet.end();)
	{
		bool ereas = false;
		heroBulletRect.left = (*i)->GetBulletPoint().x ;
		heroBulletRect.top = (*i)->GetBulletPoint().y ;
		heroBulletRect.right = (*i)->GetBulletPoint().x + 20;
		heroBulletRect.bottom = (*i)->GetBulletPoint().y + 20;
		for(vector<ZHANGAI> ::iterator j=m_vZhangAi.begin();j!=m_vZhangAi.end();++j)
		{
			if(IntersectRect(&linshiRect,&heroBulletRect,&j->m_rRect))
			{
				//��⵽�ˣ��ѱ�ըЧ�����뱬ը��
				CBoom *pBoom= new CBoom_Player_ZhangAi(linshiRect,0);
				this->m_vBoom.push_back(pBoom);
				//�����ϰ��ķ����������ж��ϰ��Ƿ񱻴ݻ�
				if(j->m_iType ==1 || j->m_iType == 2)
				{
					j->m_iDefence -= 2;
					if(	j->m_iDefence <= 0)
						j = m_vZhangAi.erase(j);
				}
				//ɾ���ӵ�
				CBullet * pBullet = (*i);
				i = m_vPlayer1Bullet.erase(i);
				delete pBullet;
				ereas =true;
				break;
			}
		}
		if(!ereas)
			++i;
	}
	//���1�ӵ�����
	for(vector<CBullet*>::iterator i=m_vPlayer1Bullet.begin();i!=m_vPlayer1Bullet.end();)
	{
		//�����߽�����
		if(!(*i)->BulletRun(m_BianJieR,m_BianJieD))
		{
			CBullet *pBullet = (*i);
			i=m_vPlayer1Bullet.erase(i);
			delete pBullet;
		}
		else
			++i;
	}
	//�����ӵ����ϰ�֮�����ײ
	for(vector<CBullet*>::iterator i=m_vEnemyBullet.begin();i!=m_vEnemyBullet.end();)
	{
		bool ereas = false;
		enemyBulletRect.left = (*i)->GetBulletPoint().x;
		enemyBulletRect.top = (*i)->GetBulletPoint().y;
		enemyBulletRect.right = (*i)->GetBulletPoint().x + 16;
		enemyBulletRect.bottom = (*i)->GetBulletPoint().y + 16;
		for(vector<ZHANGAI> ::iterator j=m_vZhangAi.begin();j!=m_vZhangAi.end();++j)
		{
			if(IntersectRect(&linshiRect,&enemyBulletRect,&j->m_rRect))
			{
				//�����ϰ��ķ����������ж��ϰ��Ƿ񱻴ݻ�
				CBoom *pBoom= new CBoom_Enemy_ZhangAi(linshiRect,0);
				this->m_vBoom.push_back(pBoom);
				if(j->m_iType ==1 || j->m_iType == 2)
				{
					j->m_iDefence -= 1;
					if(	j->m_iDefence <= 0)
						j = m_vZhangAi.erase(j);
				}
				//ɾ���ӵ�
				CBullet * pBullet = (*i);
				i = m_vEnemyBullet.erase(i);
				delete pBullet;
				ereas =true;
				break;
			}
		}
		if(!ereas)
			++i;
	}
	//���˵��ӵ�������
	for(vector<CBullet*>::iterator i=m_vEnemyBullet.begin();i!=m_vEnemyBullet.end();)
	{
		//�ӵ������߽�����
		if(!(*i)->BulletRun(m_BianJieR,m_BianJieD))
		{
			CBullet *pBullet = (*i);
			i=m_vEnemyBullet.erase(i);
			delete pBullet;
		}
		else
			++i;
	}
}
//��ײ���
void CGameLogic :: PengZhaungJianCe()
{
	RECT heroRect;//Ӣ�۾���
	RECT linshiRect;//��ʱ����
	RECT enemyRect;//���˾���
	RECT enemyRect1;
	RECT enemyBulletRect;//�����ӵ�����
	RECT heroBulletRect;//Ӣ���ӵ�����
	//�����ӵ���1����ҵ���ײ
	for(std::vector<CBullet*>::iterator i = m_vEnemyBullet.begin(); i!= m_vEnemyBullet.end();)
	{
		heroRect.left = m_pPlayer->GetPlayerPoint().x;
		heroRect.top = m_pPlayer->GetPlayerPoint().y;
		heroRect.right = m_pPlayer->GetPlayerPoint().x + 40;
		heroRect.bottom = m_pPlayer->GetPlayerPoint().y + 40;
		
		enemyBulletRect.left = (*i)->GetBulletPoint().x;
		enemyBulletRect.top = (*i)->GetBulletPoint().y;
		enemyBulletRect.right = (*i)->GetBulletPoint().x + 16;
		enemyBulletRect.bottom = (*i)->GetBulletPoint().y + 16;
		//���ɹ�
		if(IntersectRect(&linshiRect,&heroRect,&enemyBulletRect))
		{
			//�ѱ�ը�������뱬ը��
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("��ը");
			m_pPlayer->SetLife(m_pPlayer->GetLife() -(*i)->GetAttack());
			CBoom *pBoom= new CBoom_Enemy_Player(linshiRect,0);
			this->m_vBoom.push_back(pBoom);
			//ɾ���ӵ�
			CBullet* bullet = (*i);
			i = m_vEnemyBullet.erase(i);
			delete bullet;
		}
		else
			++i;
	}
	//���������,��ң��ϰ�֮���໥����ײ����ײ��ı䷽��
	for(std::vector<CEnemy*>::iterator i = m_vEnemy.begin(); i != m_vEnemy.end();++i)
	{
		//�жϵ�ǰλ�õ��¸�λ�ã������õ��˿����ƶ�
		(*i)->SetMove(true);
		//�жϵ��ĸ�������������
		RECT r[4];

			r[0].left = (*i)->GetEnemyPoint().x;
			r[0].top = (*i)->GetEnemyPoint().y-5;
			r[0].right =(*i)->GetEnemyPoint().x + 40;
			r[0].bottom = (*i)->GetEnemyPoint().y + 40-5;

			r[1].left = (*i)->GetEnemyPoint().x;
			r[1].top = (*i)->GetEnemyPoint().y+5;
			r[1].right =(*i)->GetEnemyPoint().x + 40;
			r[1].bottom = (*i)->GetEnemyPoint().y + 40+5;

			r[2].left = (*i)->GetEnemyPoint().x-5;
			r[2].top = (*i)->GetEnemyPoint().y;
			r[2].right =(*i)->GetEnemyPoint().x + 40-5;
			r[2].bottom = (*i)->GetEnemyPoint().y + 40;

			r[3].left = (*i)->GetEnemyPoint().x+5;
			r[3].top = (*i)->GetEnemyPoint().y;
			r[3].right =(*i)->GetEnemyPoint().x + 40+5;
			r[3].bottom = (*i)->GetEnemyPoint().y + 40;
		//������ʱ��4����־��������¼��ǰ�����Ƿ�����ƶ�
		bool flag[4] = {};
		//4������
		for(int k = 0;k < 4; ++k)
		{
			//��ǰ�����Ƿ��е���
			for(std::vector<CEnemy*>::iterator j = m_vEnemy.begin(); j != m_vEnemy.end(); ++j)
			{
				//��ȡҪ�����ײ�ĵ��˵�λ��
				enemyRect1.left = (*j)->GetEnemyPoint().x ;
				enemyRect1.top = (*j)->GetEnemyPoint().y ;
				enemyRect1.right = (*j)->GetEnemyPoint().x + 40;
				enemyRect1.bottom = (*j)->GetEnemyPoint().y + 40;
				if( (*i) != (*j))
				{
					//���ɹ�����ǰ�������ƶ������ñ�־ΪTRUE
					if(IntersectRect(&linshiRect,&r[k],&enemyRect1))
					{						
						flag[k] = true;
						break;
					}
				}//�Ƿ��������
			}
			//---------�������ײ�ļ��-------
			//��ȡ��ǰ��ҵ�λ��
			heroRect.left = m_pPlayer->GetPlayerPoint().x;
			heroRect.top = m_pPlayer->GetPlayerPoint().y;
			heroRect.right = m_pPlayer->GetPlayerPoint().x + 40;
			heroRect.bottom = m_pPlayer->GetPlayerPoint().y + 40;
			//���ɹ�����ǰ�����־ΪTRUE
			if(IntersectRect(&linshiRect,&heroRect,&r[k]))
				flag[k] = true ;
			//--------���ϰ�֮�����ײ------------
			for(std::vector<ZHANGAI> ::iterator j=m_vZhangAi.begin();j!=m_vZhangAi.end();++j)
			{
				//���ɹ�����ǰ�����־ΪTRUE
				if(IntersectRect(&linshiRect,&r[k],&j->m_rRect))
				{						
					flag[k] = true;
					break;
				}
			}
		}
		//������������ƶ�ʱ����Ҫ�ı䷽��
		if(flag[(*i)->GetDir()] )
		{
			int suiji=0;
			//�ı䷽��ֱ����������ķ������ƶ�
			do
			{
				//���4�����򶼲����ƶ������ò����ƶ�
				if(flag[0] &&flag[1]&&flag[2]&&flag[3])
				{
					(*i)->SetMove(false);
					break;
				}
				else
					suiji =rand()%4;
			}while(flag[suiji]);
			(*i)->SetDir(suiji);
		}
	}//���for����
	//����ӵ�����˵���ײ
	for(std::vector<CBullet*>::iterator i = m_vPlayer1Bullet.begin(); i != m_vPlayer1Bullet.end();)
	{
		bool erase = false;
		
		for(std::vector<CEnemy*>::iterator j = m_vEnemy.begin(); j!= m_vEnemy.end();++j)
		{
			enemyRect.left = (*j)->GetEnemyPoint().x;
			enemyRect.top = (*j)->GetEnemyPoint().y;
			enemyRect.right = (*j)->GetEnemyPoint().x + 40;
			enemyRect.bottom = (*j)->GetEnemyPoint().y + 40;
			
			heroBulletRect.left = (*i)->GetBulletPoint().x ;
			heroBulletRect.top = (*i)->GetBulletPoint().y ;
			heroBulletRect.right = (*i)->GetBulletPoint().x + 20;
			heroBulletRect.bottom = (*i)->GetBulletPoint().y + 20;
			//���ɹ���ɾ���ӵ�
			if(IntersectRect(&linshiRect,&heroBulletRect,&enemyRect))
			{
				if((*j)->GetHp()<=0)
				{
					CEnemy* enemy = (*j);
					m_vEnemy.erase(j);
					delete enemy;
					m_iScore++;
					this->m_iEnemyNum -- ;
				}
				//���ݵ������������õ��˵���Ӧ����
				else
					(*j)->SetHp((*j)->GetHp()-(*i)->GetAttack());
				//������ը
				CGameEngine::GetGE()->GetAM()->PlayOnceAudio("��ը");
				CBoom *pBoom= new CBoom_Player_Enemy(linshiRect,0);
				this->m_vBoom.push_back(pBoom);
				//ɾ���ӵ�
				CBullet* pBullet = (*i); 
				i = m_vPlayer1Bullet.erase(i);
				delete pBullet;
				erase = true;
				
				break;
			}	
		}
		if(!erase)
			++i;
	}
}
//���ƺ���
void CGameLogic :: Paint()
{
	//��������
	CGameEngine::GetGE()->GetGO()->LoadFont("��Ϸ��ʾ��Ϣ����",
		15, 15, 20, false, false, false, "����");
	//���ƿͻ����ϲ��ֵı���
	CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\black.bmp",
		0, 0,this->m_BianJieR, INFO_H,0, 0,50,50);
	//������Ϸ��Ϣ�����������������������ȣ�
	char buf[16];
	sprintf_s(buf,16,"������%d",this->m_iScore);
	CGameEngine::GetGE()->GetGO()->DrawString1("��Ϸ��ʾ��Ϣ����",0,0,buf,RGB(255,0,0));
	char buf1[16];
	sprintf_s(buf1,16,"������%d",this->m_pPlayer->GetLife());
	CGameEngine::GetGE()->GetGO()->DrawString1("��Ϸ��ʾ��Ϣ����",150,0,buf1,RGB(255,0,0));
	char buf2[20];
	sprintf_s(buf2,20,"��ǰʣ����ˣ�%d",this->m_iEnemyNum);
	CGameEngine::GetGE()->GetGO()->DrawString1("��Ϸ��ʾ��Ϣ����",0,30,buf2,RGB(255,0,0));
	char buf3[20];
	sprintf_s(buf3,20,"��ǰ��������%d",this->m_pPlayer->GetAttack());
	CGameEngine::GetGE()->GetGO()->DrawString1("��Ϸ��ʾ��Ϣ����",280,0,buf3,RGB(255,0,0));
	//������Ϸ����ͼ
	CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\background.bmp",
		0, INFO_H, this->m_BianJieR, this->m_BianJieD,0, 0,33,30);
	//���Ƶ�ͼ�ϰ�
	for(std::vector<ZHANGAI>::iterator i =m_vZhangAi.begin();i!=m_vZhangAi.end();++i)
	{
		if(i->m_iType == 1)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\zhangai1.bmp",
				i->m_rRect.left, i->m_rRect.top, 40, 40,0, 0,16,15);
		if(i->m_iType == 2)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\zhangai7.bmp",
				i->m_rRect.left, i->m_rRect.top, 40, 40,0, 0,16,16);
		if(i->m_iType == 3)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\zhangai5.bmp",
				i->m_rRect.left, i->m_rRect.top, 40, 40,0, 0,16,16);
		if(i->m_iType == 4)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\zhangai2.bmp",
				i->m_rRect.left, i->m_rRect.top, 40, 40,0, 0,16,16);
	}
	//�������1
	if(this->m_pPlayer->GetDir() == _DIR_UP_)
		CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\����1.bmp",
			this->GetPlayerPoint().x, this->GetPlayerPoint().y, 40, 40,0, 0,132,126,RGB(255,255,255));
	if(this->m_pPlayer->GetDir() == _DIR_DOWN_)
		CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\����2.bmp",
			this->GetPlayerPoint().x, this->GetPlayerPoint().y, 40, 40,0, 0,132,126,RGB(255,255,255));
	if(this->m_pPlayer->GetDir() == _DIR_LEFT_)
		CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\����3.bmp",
			this->GetPlayerPoint().x, this->GetPlayerPoint().y, 40, 40,0, 0,142,106,RGB(255,255,255));
	if(this->m_pPlayer->GetDir() == _DIR_RIGHT_)
		CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\����4.bmp",
			this->GetPlayerPoint().x, this->GetPlayerPoint().y, 40, 40,0, 0,142,106,RGB(255,255,255));
	//�������1���ӵ�
	for(vector<CBullet*>::iterator i=m_vPlayer1Bullet.begin();i!=m_vPlayer1Bullet.end();++i)
		CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\fireball.bmp",
			(*i)->GetBulletPoint().x,(*i)->GetBulletPoint().y, 30, 30,78, 0,13,17);
	//���Ƶ��˵��ӵ�
	for(vector<CBullet*>::iterator i=m_vEnemyBullet.begin();i!=m_vEnemyBullet.end();++i)
		CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\fireball.bmp",
			(*i)->GetBulletPoint().x,(*i)->GetBulletPoint().y, 16, 16,78, 0,13,16);
	//���ݵ��˵����������Ƶ���
	for(vector<CEnemy*>::iterator i=m_vEnemy.begin();i!=m_vEnemy.end();++i)
	{
		if((*i)->GetType() == 0)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\Enemy1.bmp",
				(*i)->GetEnemyPoint().x,(*i)->GetEnemyPoint().y, 40, 40,60, 0,20,16);
		if((*i)->GetType() == 1)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\Enemy2.bmp",
				(*i)->GetEnemyPoint().x,(*i)->GetEnemyPoint().y, 40, 40,0, 0,19,17);
		if((*i)->GetType() == 2)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\Enemy3.bmp",
				(*i)->GetEnemyPoint().x,(*i)->GetEnemyPoint().y, 40, 40,0, 0,17,16);
		if((*i)->GetType() == 3)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\Enemy6.bmp",
				(*i)->GetEnemyPoint().x,(*i)->GetEnemyPoint().y, 40, 40,0, 0,32,32,RGB(0,0,0));
	}
	//���Ʊ�ըЧ��
	for(vector<CBoom*>::iterator i=m_vBoom.begin();i!=m_vBoom.end();)
	{
		if(!(*i)->Run())
			i=m_vBoom.erase(i);
		else
		{
			(*i)->Paint();
			++i;
		}
	}
	//���Ƶ���
	for(vector<CItems*> ::iterator i=m_vItems.begin();i!=m_vItems.end();++i)
	{
		if((*i)->GetApper())
		{
			if(strcmp((*i)->GetName().c_str(),"��Ģ��") == 0)
				CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\��Ģ��.bmp",
				(*i)->GetRect().left,(*i)->GetRect().top, 40, 40,0, 0,18,17);
			if(strcmp((*i)->GetName().c_str(),"ǳ��Ģ��") == 0)
				CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\ǳ��Ģ��.bmp",
				(*i)->GetRect().left,(*i)->GetRect().top, 40, 40,0, 0,16,17);
			if(strcmp((*i)->GetName().c_str(),"����Ģ��") == 0)
				CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\����Ģ��.bmp",
				(*i)->GetRect().left,(*i)->GetRect().top, 40, 40,0, 0,16,16);
		}
		
	}
}	