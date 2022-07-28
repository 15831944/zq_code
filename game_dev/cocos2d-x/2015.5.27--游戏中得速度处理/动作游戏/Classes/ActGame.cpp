#include "ActGame.h"

bool RectCollide(const _RECTANGLE* r1,
				 const _RECTANGLE* r2,
				 _RECTANGLE* r3)
{
	if (r1->x1 > r2->x2 ||
		r2->x1 > r1->x2 ||
		r1->y1 > r2->y2 ||
		r2->y1 > r1->y2)
		return false;
	else
	{
		*r3 = *r1;
		if (r2->x1 > r1->x1)
			r3->x1 = r2->x1;
		if (r2->x2 < r1->x2)
			r3->x2 = r2->x2;
		if (r2->y1 > r1->y1)
			r3->y1 = r2->y1;
		if (r2->y2 < r1->y2)
			r3->y2 = r2->y2;
		return true;
	}
}

CActGame::CActGame(int MapLW, int MapLH, int GridW, int GridH)
{
	//���ǽ�������ͼ������ٰ���һȦ�ϰ�
	//��������Ϸ��ͼ�Ŀ���Ҫ��������2
	m_MapLW = MapLW + 2;
	m_MapLH = MapLH + 2;
	m_GridW = GridW;
	m_GridH = GridH;
	m_MapPW = m_MapLW * m_GridW;
	m_MapPH = m_MapLH * m_GridH;

	//���ɵ�ͼ
	m_Map = new char[m_MapLW * m_MapLH];

	//���õ�ͼ
	for (int y = 1; y < m_MapLH - 1; ++y)
	{
		for (int x = 1; x < m_MapLW - 1; ++x)
			m_Map[x + y * m_MapLW] = 1;
	}
	for (int x = 0; x < m_MapLW; ++x)
	{
		m_Map[x + 0 * m_MapLW] = 0;
		m_Map[x + (m_MapLH - 1) * m_MapLW] = 0;
	}
	for (int y = 1; y < m_MapLH - 1; ++y)
	{
		m_Map[0 + y * m_MapLW] = 0;
		m_Map[(m_MapLW - 1) + y * m_MapLW] = 0;
	}
}

CActGame::~CActGame()
{
	delete [] m_Map;
}

bool CActGame::SetMap(int x, int y, char d)
{
	//���û�����ת��Ϊϵͳ����
	x += 1;
	y += 1;

	if (x >= 1 && x < m_MapLW - 1 && y >= 1 && y < m_MapLH - 1)
	{
		m_Map[x + y * m_MapLW] = d;
		return true;
	}
	else
		return false;
}

char* CActGame::GetMap(int x, int y)
{
	x += 1;
	y += 1;
	if (x >= 1 && x < m_MapLW - 1 && y >= 1 && y < m_MapLH - 1)
		return &m_Map[x + y * m_MapLW];
	else
		return 0;
}

_OBJECT* CActGame::CreateObject(_RECTANGLE* r,
								int csx, int csy,
								int ksx, int ksy,
								int asx, int asy)
{
	r->x1 += m_GridW;
	r->x2 += m_GridW;
	r->y1 += m_GridH;
	r->y2 += m_GridH;

	//���������β����Ƿ�������ϰ�
	int x1 = r->x1 / m_GridW;
	int y1 = r->y1 / m_GridH;
	int x2 = r->x2 / m_GridW;
	int y2 = r->y2 / m_GridH;
	for (int y = y1; y <= y2; ++y)
	{
		for (int x = x1; x <= x2; ++x)
		{
			if (m_Map[x + y * m_MapLW] <= 0)
				return 0;
		}
	}

	_OBJECT obj = {*r, csx, csy, ksx, ksy, asx, asy};
	m_ObjList.push_back(obj);
	return &m_ObjList.back();
}

bool CActGame::MoveObject(_OBJECT* obj,
						  int st,
						  int sx, int sy)
{
	if (!obj || st < 0 || st > 2)
		return false;

	switch (st)
	{
	case 0: obj->csx = sx; obj->csy = sy; break;
	case 1: obj->ksx = sx; obj->ksy = sy; break;
	case 2: obj->asx = sx; obj->asy = sy; break;
	}

	return true;
}

bool CActGame::EraseObject(_OBJECT* obj)
{
	for (std::list<_OBJECT>::iterator it = m_ObjList.begin(); it != m_ObjList.end(); ++it)
	{
		if (&(*it) == obj)
		{
			m_ObjList.erase(it);
			return true;
		}
	}
	return false;
}

void CActGame::Run()
{
	//ѭ����������
	for (std::list<_OBJECT>::iterator it = m_ObjList.begin(); it != m_ObjList.end(); ++it)
	{
		//�õ��������
		int objw = it->r.x2 - it->r.x1 + 1;
		int objh = it->r.y2 - it->r.y1 + 1;

		//�õ���ǰ������ƶ�
		int mx = it->csx + (it->ksx += it->asx);
		int my = it->csy + (it->ksy += it->asy);

		//Լ���ƶ���Χ
		if (mx > m_GridW)
			mx = m_GridW;
		else if (mx < -m_GridW)
			mx = -m_GridW;
		if (my > m_GridH)
			my = m_GridH;
		else if (my < -m_GridH)
			my = -m_GridH;

		//��¼δ�ƶ�֮ǰ��λ��
		int old_x = it->r.x1;
		int old_y = it->r.y1;

		//x������
		if (mx != 0)
		{
			//���ƶ�����
			if (mx > 0)
			{
				//�õ������ƶ������������и��ӷ�Χ
				int x1 = it->r.x1 / m_GridW;
				int y1 = it->r.y1 / m_GridH;
				int x2 = (it->r.x2 + mx) / m_GridW;
				int y2 = it->r.y2 / m_GridH;

				//�жϸ������Ƿ����ϰ�
				int bx, by;
				bool block = false;
				for (bx = x1; bx <= x2; ++bx)
				{
					for (by = y1; by <= y2; ++by)
					{
						if (m_Map[bx + by * m_MapLW] <= 0)
						{
							block = true;
							break;
						}
					}
					if (block)
						break;
				}

				//������ϰ�
				if (block)
				{
					it->r.x1 = bx * m_GridW - 1 - objw;
					it->r.x2 = it->r.x1 + objw - 1;
				}
				else
				{
					it->r.x1 += mx;
					it->r.x2 += mx;
				}
			}
			//���ƶ�����
			else
			{
				//�õ������ƶ������������и��ӷ�Χ
				int x1 = it->r.x2 / m_GridW;
				int y1 = it->r.y1 / m_GridH;
				int x2 = (it->r.x1 + mx) / m_GridW;
				int y2 = it->r.y2 / m_GridH;

				//�жϸ������Ƿ����ϰ�
				int bx, by;
				bool block = false;
				for (bx = x1; bx >= x2; --bx)
				{
					for (by = y1; by <= y2; ++by)
					{
						if (m_Map[bx + by * m_MapLW] <= 0)
						{
							block = true;
							break;
						}
					}
					if (block)
						break;
				}

				//������ϰ�
				if (block)
				{
					it->r.x1 = (bx * m_GridW + m_GridW) + 1;
					it->r.x2 = it->r.x1 + objw - 1;
				}
				else
				{
					it->r.x1 += mx;
					it->r.x2 += mx;
				}
			}
		}
		if (old_x == it->r.x1)
			it->ksx = 0;
		it->csx = 0;

		//y������
		if (my != 0)
		{
			//���ƶ�����
			if (my > 0)
			{
				//�õ������ƶ������������и��ӷ�Χ
				int x1 = it->r.x1 / m_GridW;
				int y1 = it->r.y1 / m_GridH;
				int x2 = it->r.x2 / m_GridW;
				int y2 = (it->r.y2 + my) / m_GridH;

				//�жϸ������Ƿ����ϰ�
				int bx, by;
				bool block = false;
				for (by = y1; by <= y2; ++by)
				{
					for (bx = x1; bx <= x2; ++bx)
					{
						if (m_Map[bx + by * m_MapLW] <= 0)
						{
							block = true;
							break;
						}
					}
					if (block)
						break;
				}

				//������ϰ�
				if (block)
				{
					it->r.y1 = by * m_GridH - 1 - objh;
					it->r.y2 = it->r.y1 + objh - 1;
				}
				else
				{
					it->r.y1 += my;
					it->r.y2 += my;
				}
			}
			//���ƶ�����
			else
			{
				//�õ������ƶ������������и��ӷ�Χ
				int x1 = it->r.x1 / m_GridW;
				int y1 = it->r.y2 / m_GridH;
				int x2 = it->r.x2 / m_GridW;
				int y2 = (it->r.y1 + my) / m_GridH;

				//�жϸ������Ƿ����ϰ�
				int bx, by;
				bool block = false;
				for (by = y1; by >= y2; --by)
				{
					for (bx = x1; bx >= x2; --bx)
					{
						if (m_Map[bx + by * m_MapLW] <= 0)
						{
							block = true;
							break;
						}
					}
					if (block)
						break;
				}

				//������ϰ�
				if (block)
				{
					it->r.y1 = (by * m_GridH + m_GridH) + 1;
					it->r.y2 = it->r.y1 + objh - 1;
				}
				else
				{
					it->r.y1 += my;
					it->r.y2 += my;
				}
			}
		}
		if (old_y == it->r.y1)
			it->ksy = 0;
		it->csy = 0;
	}
}