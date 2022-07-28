#include "Game.h"
#include "Button.h"
#include "AppDelegate.h"
#include <assert.h>

#define _VIEW_W _DEBUG_W //�ӿڿ�
#define _VIEW_H _DEBUG_H //�ӿڸ�
#define _GRID_W 40 //���ӵ����ؿ�
#define _GRID_H 30 //���ӵ����ظ�
#define _DB_W 50 //����ť��
#define _DB_H 50 //����ť��
#define _INPUT_U 1 //������
#define _INPUT_D 2 //������
#define _INPUT_L 3 //������
#define _INPUT_R 4 //������
#define _HERO_SPEED 10 //Ӣ���ٶ�
#define _HERO_W _GRID_W //Ӣ�۵����ؿ�
#define _HERO_H _GRID_H //Ӣ�۵����ظ�

int DynamicElementManager::GetArea(CCRect* r, int* a)
{
	int x2 = r->origin.x + r->size.width - 1;
	int y2 = r->origin.y + r->size.height - 1;

	int left = r->origin.x / m_AreaW;
	int top = r->origin.y / m_AreaH;
	int right = x2 / m_AreaW;
	int bottom = y2 / m_AreaH;

	int result = 0;

	//��������һ��
	if (left == right)
	{
		//��������һ��
		if (top == bottom)
		{
			//����ֻ��һ��������
			a[result++] = left + top * m_AreaXNum;
		}
		//���������������
		else
		{
			//��������������������
			a[result++] = left + top * m_AreaXNum;
			a[result++] = left + bottom * m_AreaXNum;
		}
	}
	//���������������
	else
	{
		//��������һ��
		if (top == bottom)
		{
			//��������������������
			a[result++] = left + top * m_AreaXNum;
			a[result++] = right + top * m_AreaXNum;
		}
		//���������������
		else
		{
			//���������������ĸ�������
			a[result++] = left + top * m_AreaXNum;
			a[result++] = right + top * m_AreaXNum;
			a[result++] = left + bottom * m_AreaXNum;
			a[result++] = right + bottom * m_AreaXNum;
		}
	}

	return result;
}

DynamicElementManager::DynamicElementManager(
	int MapW, int MapH,
	int AreaXNum, int AreaYNum)
{
	assert(MapW % AreaXNum == 0 && MapH % AreaYNum == 0);

	m_MapW = MapW;
	m_MapH = MapH;
	m_AreaXNum = AreaXNum;
	m_AreaYNum = AreaYNum;
	m_AreaNum = m_AreaXNum * m_AreaYNum;
	m_AreaW = m_MapW / m_AreaXNum;
	m_AreaH = m_MapH / m_AreaYNum;

	//���������
	m_AreaList = new std::list<CCRect*>[m_AreaNum];
}

DynamicElementManager::~DynamicElementManager()
{
	delete [] m_AreaList;
}

CCRect* DynamicElementManager::CreateDE(const CCRect& r)
{
	//�������嵽�������
	m_Elements.push_back(r);

	//�õ������ַ
	CCRect* p = &(m_Elements.back());

	//��������λ�ü�������������
	int a[4];
	int n = GetArea(p, a);

	//��������Ϣ��������
	for (int i = 0; i < n; ++i)
		m_AreaList[a[i]].push_back(p);

	return p;
}

bool DynamicElementManager::DeleteDE(CCRect* e)
{
	//ɾ��������е�������Ϣ
	int a[4];
	int n = GetArea(e, a);
	for (int i = 0; i < n; ++i)
	{
		for (std::list<CCRect*>::iterator it = m_AreaList[a[i]].begin(); it != m_AreaList[a[i]].end(); ++it)
		{
			if (e == *it)
			{
				m_AreaList[a[i]].erase(it);
				break;
			}
		}
	}

	//ɾ��������е�������Ϣ
	for (std::list<CCRect>::iterator it = m_Elements.begin(); it != m_Elements.end(); ++it)
	{
		if (&(*it) == e)
			m_Elements.erase(it);
	}

	return true;
}

bool DynamicElementManager::MoveDE(CCRect* e, int mx, int my)
{
	//�õ��ƶ�ǰ���ƶ���������������
	int a1[4], a2[4];
	int n1 = GetArea(e, a1);
	CCRect e2(e->origin.x + mx, e->origin.y + my, e->size.width, e->size.height);
	int n2 = GetArea(&e2, a2);
}

void DynamicElementManager::GetRenderDE(const CCRect& view,
										std::list<CCRect*>* m_RenderDEList)
{
	
}

CGame::CGame()
{
	//����
	t0 = CCTextureCache::sharedTextureCache()->addImage("Game/00.PNG");

	//Ӣ��
	t1 = CCTextureCache::sharedTextureCache()->addImage("Game/01.PNG");

	//1234�ֱ����ť��������
	LoadUI(_INPUT_U, new CButton(CCRect(50, _VIEW_H - 150, _DB_W, _DB_H), "Game/Dir/d_i.PNG", "Game/Dir/d_n.PNG", "Game/Dir/d_d.PNG"));
	LoadUI(_INPUT_D, new CButton(CCRect(50, _VIEW_H - 50, _DB_W, _DB_H), "Game/Dir/d_i.PNG", "Game/Dir/d_n.PNG", "Game/Dir/d_d.PNG"));
	LoadUI(_INPUT_L, new CButton(CCRect(0, _VIEW_H - 100, _DB_W, _DB_H), "Game/Dir/d_i.PNG", "Game/Dir/d_n.PNG", "Game/Dir/d_d.PNG"));
	LoadUI(_INPUT_R, new CButton(CCRect(100, _VIEW_H - 100, _DB_W, _DB_H), "Game/Dir/d_i.PNG", "Game/Dir/d_n.PNG", "Game/Dir/d_d.PNG"));

	//�õ���Ϸ��ͼ
	_FILE_DATA fd = GetResourceFileData("Game/game.txt");
	for (int i = 0, j = 0; i < fd.fs; ++i)
	{
		if (fd.fd[i] >= '0' && fd.fd[i] <= '9')
			map[j++] = fd.fd[i] - '0';
	}
	delete [] fd.fd;

	//��ʼ��Ӣ��
	x = 0;
	y = 0;
}

void CGame::InputUp(CCPoint* p)
{
}

void CGame::Logic(float dt)
{
#ifdef _WIN32
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (y > 0)
			y -= _HERO_SPEED;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (y < _MAP_H * _GRID_H - _HERO_H)
			y += _HERO_SPEED;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (x > 0)
			x -= _HERO_SPEED;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (x < _MAP_W * _GRID_W - _HERO_W)
			x += _HERO_SPEED;
	}
#endif
}

void CGame::Output()
{
	//����Ӣ��λ�ü����ӿ�λ��
	int vx, vy;
	if (x <= (_VIEW_W - _HERO_W) / 2)
		vx = 0;
	else if (x > (_GRID_W * _MAP_W) - (_VIEW_W + _HERO_W) / 2)
		vx = (_GRID_W * _MAP_W) - _VIEW_W;
	else
		vx = x - (_VIEW_W - _HERO_W) / 2;
	if (y <= (_VIEW_H - _HERO_H) / 2)
		vy = 0;
	else if (y > (_GRID_H * _MAP_H) - (_VIEW_H + _HERO_H) / 2)
		vy = (_GRID_H * _MAP_H) - _VIEW_H;
	else
		vy = y - (_VIEW_H - _HERO_H) / 2;

	//���Ƶ�ͼ����1��Ч��̫�ͣ������˺ܶ�����������ĵ�ͼ����
	//for (int cy = 0; cy < _MAP_H; ++cy)
	//{
	//	for (int cx = 0; cx < _MAP_W; ++cx)
	//	{
	//		DrawImage1(
	//			t0,
	//			map[cx + cy * _MAP_W] * _GRID_W, 0, _GRID_W, _GRID_H,
	//			cx * _GRID_W - vx, cy * _GRID_H - vy, _GRID_W, _GRID_H);
	//	}
	//}

	//���Ƶ�ͼ����2��ͨ�������ӿڷ�Χ֮�ڵĸ�����ȷ����̬����Ļ���
	int x1 = vx / _GRID_W;
	int y1 = vy / _GRID_H;
	int x2 = (vx + _VIEW_W - 1) / _GRID_W;
	int y2 = (vy + _VIEW_H - 1) / _GRID_H;
	int offsetx = vx % _GRID_W;
	int offsety = vy % _GRID_H;
	for (int cy = y1; cy <= y2; ++cy)
	{
		for (int cx = x1; cx <= x2; ++cx)
		{
			DrawImage1(
				t0,
				map[cx + cy * _MAP_W] * _GRID_W, 0, _GRID_W, _GRID_H,
				(cx - x1) * _GRID_W - offsetx,
				(cy - y1) * _GRID_H - offsety,
				_GRID_W,
				_GRID_H);
		}
	}

	//����Ӣ��
	DrawImage1(
		t1,
		0, 0, _HERO_W, _HERO_H,
		x - vx, y - vy, _HERO_W, _HERO_H);
}

void CGame::OnUIMessage(int id, int msg)
{
	//switch (msg)
	//{
	//	//��ǰ�����а�ť������
	//case _BUTTON_CLICK:
	//	{
	//		switch (id)
	//		{
	//		case _INPUT_U:
	//			{
	//				if (y > 0)
	//					y -= _HERO_SPEED;
	//				break;
	//			}
	//		}
	//		switch (id)
	//		{
	//		case _INPUT_D:
	//			{
	//				if (y < _MAP_H * _GRID_H - _HERO_H)
	//					y += _HERO_SPEED;
	//				break;
	//			}
	//		}
	//		switch (id)
	//		{
	//		case _INPUT_L:
	//			{
	//				if (x > 0)
	//					x -= _HERO_SPEED;
	//				break;
	//			}
	//		}
	//		switch (id)
	//		{
	//		case _INPUT_R:
	//			{
	//				if (x < _MAP_W * _GRID_W - _HERO_W)
	//					x += _HERO_SPEED;
	//				break;
	//			}
	//		}
	//		break;
	//	}
	//}
}