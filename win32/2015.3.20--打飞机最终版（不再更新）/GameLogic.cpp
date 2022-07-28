#include "GameLogic.h"	
#include "Plane.h"
#include "EmenyPlane.h"
#include "HeroPlane.h"
#include "Bullet.h"
#include "EmenyBullet.h"
#include "HeroBullet.h"
#include <time.h>
#include <iostream>

CGameLogic::CGameLogic()
{}
CGameLogic::~CGameLogic()
{}

//��ʼ�����������߽�
void CGameLogic::Init(int score,int bianjr,int bianjb)
{
	m_iScore = score;
	m_vEmenyPlane.clear();
	m_pHeroPlane = new CHeroPlane;
	POINT point = {bianjr/2,bianjb/2};
	m_pHeroPlane->Init(point);
	m_vEmenyBullet.clear();
	m_vHeroBullet.clear();
	m_iBianJieRight = bianjr;
	m_iBianJieBottom = bianjb;
	m_iEmenyPlaneCreateTime = 20;
}

//����
void CGameLogic::Run()
{
	if(m_iEmenyPlaneCreateTime <= 0)
	{
		AddEmenyPlane();
		srand((unsigned int)time(0));
		m_iEmenyPlaneCreateTime = rand() % 100 + 30;
	}
	m_iEmenyPlaneCreateTime--;
	PengZhuangJianCe();
	for(std::vector<CPlane*>::iterator i = m_vEmenyPlane.begin(); i!= m_vEmenyPlane.end();)
	{
		if(!(*i)->Run(m_iBianJieRight,m_iBianJieBottom,m_vEmenyBullet))
		{
			CPlane* emenyPlane = (*i);
			i = m_vEmenyPlane.erase(i);
			delete emenyPlane;
		}
		else
			++i;
	}
	for(std::vector<CBullet*>::iterator i = m_vEmenyBullet.begin(); i != m_vEmenyBullet.end();)
	{
		if(!(*i)->BulletRun(m_iBianJieBottom))
		{
			CBullet* pBullet = (*i); 
			i = m_vEmenyBullet.erase(i);
			delete pBullet;
		}
		else
			++i;
	}
	for(std::vector<CBullet*>::iterator i = m_vHeroBullet.begin(); i != m_vHeroBullet.end();)
	{
		if(!(*i)->BulletRun(0))
		{
			CBullet* pBullet = (*i); 
			i = m_vHeroBullet.erase(i);
			delete pBullet;
		}
		else
			++i;
	}
}

//����Ӣ��λ��
void CGameLogic::SetHeroPoint(POINT point)
{
	m_pHeroPlane->SetPlanePoint(point);
}

void CGameLogic::SetHeroAttack(POINT point)
{
	m_pHeroPlane->Attack(point,m_vHeroBullet);
}

//��ײ���
void CGameLogic::PengZhuangJianCe()
{
	RECT heroRect;//Ӣ�۷ɻ�����
	RECT linshiRect;//��ʱ����
	RECT emenyRect;//�л�����
	RECT emenyBulletRect;//�����ӵ�����
	RECT heroBulletRect;//Ӣ���ӵ�����
	
	for(std::vector<CPlane*>::iterator i = m_vEmenyPlane.begin(); i!= m_vEmenyPlane.end();)
	{
		//ÿ����Ӣ�۷ɻ����
		//������Ӣ�۷ɻ���ײ������˷ɻ������٣�ͬʱӢ�۷ɻ�����Ѫ��
		heroRect.left = m_pHeroPlane->GetPoint().x - 20;
		heroRect.top = m_pHeroPlane->GetPoint().y - 20;
		heroRect.right = m_pHeroPlane->GetPoint().x + 20;
		heroRect.bottom = m_pHeroPlane->GetPoint().y + 20;
		
		emenyRect.left = (*i)->GetPoint().x - 20;
		emenyRect.top = (*i)->GetPoint().y - 20;
		emenyRect.right = (*i)->GetPoint().x + 20;
		emenyRect.bottom = (*i)->GetPoint().y + 20;

		if(IntersectRect(&linshiRect,&heroRect,&emenyRect))
		{
			CPlane* emenyPlane = (*i);
			i = m_vEmenyPlane.erase(i);
			delete emenyPlane;
			m_pHeroPlane->SetHP(m_pHeroPlane->GetHP() - 10);
		}
		else
			++i;
	}
	for(std::vector<CBullet*>::iterator i = m_vEmenyBullet.begin(); i != m_vEmenyBullet.end();)
	{
		//ÿ����Ӣ�۷ɻ����
		//������Ӣ�۷ɻ���ײ��������ӵ������٣�ͬʱӢ�۷ɻ�����Ѫ��
		heroRect.left = m_pHeroPlane->GetPoint().x - 20;
		heroRect.top = m_pHeroPlane->GetPoint().y - 20;
		heroRect.right = m_pHeroPlane->GetPoint().x + 20;
		heroRect.bottom = m_pHeroPlane->GetPoint().y + 20;
		
		emenyBulletRect.left = (*i)->GetBulletPoint().x - 10;
		emenyBulletRect.top = (*i)->GetBulletPoint().y - 10;
		emenyBulletRect.right = (*i)->GetBulletPoint().x + 10;
		emenyBulletRect.bottom = (*i)->GetBulletPoint().y + 10;

		if(IntersectRect(&linshiRect,&heroRect,&emenyBulletRect))
		{
			CBullet* pBullet = (*i); 
			i = m_vEmenyBullet.erase(i);
			delete pBullet;
			m_pHeroPlane->SetHP(m_pHeroPlane->GetHP() - 5);
		}
		else
			++i;
	}
	for(std::vector<CBullet*>::iterator i = m_vHeroBullet.begin(); i != m_vHeroBullet.end();)
	{
		bool erase = false;
		//��л����м��
		//������л��ɻ���ײ������˷ɻ������٣�ͬʱӢ���ӵ�����
		for(std::vector<CPlane*>::iterator j = m_vEmenyPlane.begin(); j!= m_vEmenyPlane.end();++j)
		{
			emenyRect.left = (*j)->GetPoint().x - 20;
			emenyRect.top = (*j)->GetPoint().y - 20;
			emenyRect.right = (*j)->GetPoint().x + 20;
			emenyRect.bottom = (*j)->GetPoint().y + 20;
			
			heroBulletRect.left = (*i)->GetBulletPoint().x - 10;
			heroBulletRect.top = (*i)->GetBulletPoint().y - 10;
			heroBulletRect.right = (*i)->GetBulletPoint().x + 10;
			heroBulletRect.bottom = (*i)->GetBulletPoint().y + 10;

			if(IntersectRect(&linshiRect,&heroBulletRect,&emenyRect))
			{
				CBullet* pBullet = (*i); 
				i = m_vHeroBullet.erase(i);
				delete pBullet;
				CPlane* emenyPlane = (*j);
				m_vEmenyPlane.erase(j);
				delete emenyPlane;
				erase = true;
				m_iScore++;
				break;
			}	
		}
		if(!erase)
			++i;
	}
}

POINT CGameLogic::GetHeroPoint()
{
	return m_pHeroPlane->GetPoint();
}

void CGameLogic::Paint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd,&ps);// GetDC(hWnd);
	char buf[256] ;
	sprintf_s(buf,256,"����:%d  Ѫ��:%d",m_iScore,m_pHeroPlane->GetHP());
	TextOutA(hdc,0,0,buf,(int)strlen(buf));
	for(std::vector<CPlane*>::iterator i = m_vEmenyPlane.begin(); i!= m_vEmenyPlane.end();++i)
	{
		Rectangle(
			hdc,
			(*i)->GetPoint().x - 20,
			(*i)->GetPoint().y - 20,
			(*i)->GetPoint().x + 20,
			(*i)->GetPoint().y + 20);	
	}
	for(std::vector<CBullet*>::iterator i = m_vEmenyBullet.begin(); i != m_vEmenyBullet.end();++i)
	{
		Ellipse(
			hdc,
			(*i)->GetBulletPoint().x - 10,
			(*i)->GetBulletPoint().y - 10,
			(*i)->GetBulletPoint().x + 10,
			(*i)->GetBulletPoint().y + 10);
	}
	for(std::vector<CBullet*>::iterator i = m_vHeroBullet.begin(); i != m_vHeroBullet.end();++i)
	{
		Ellipse(
			hdc,
			(*i)->GetBulletPoint().x - 10,
			(*i)->GetBulletPoint().y - 10,
			(*i)->GetBulletPoint().x + 10,
			(*i)->GetBulletPoint().y + 10);
	}

	Rectangle(
		hdc,
		m_pHeroPlane->GetPoint().x - 20,
		m_pHeroPlane->GetPoint().y - 20,
		m_pHeroPlane->GetPoint().x + 20,
		m_pHeroPlane->GetPoint().y + 20);

	EndPaint(hWnd,&ps);
	//ReleaseDC(hWnd,hdc);
}


void CGameLogic::AddEmenyPlane()
{
	srand((unsigned int)time(0));
	POINT point;
	point.x = rand() % m_iBianJieRight;
	point.y = 0;
	
	CPlane* emenyPlane = new CEmenyPlane;
	emenyPlane->Init(point);
	m_vEmenyPlane.push_back(emenyPlane);
}

void CGameLogic::Brom()
{
	m_vEmenyPlane.clear();
	m_vEmenyBullet.clear();
	m_vHeroBullet.clear();
}