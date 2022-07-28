#include "GameOutput.h"

CGameOutput::CGameOutput(HWND hWnd)
:
m_hWnd(hWnd)
{
	//��ȡ�ͻ����Ŀ�͸�
	RECT r;
	GetClientRect(this->m_hWnd,&r);
	this->m_iClientW = r.right - r.left;
	this->m_iClientH = r.bottom - r.top;
	//�õ����豸
	this->m_MainDC = GetDC(m_hWnd);
	//��ȡ���豸
	HBITMAP hbmp = 0;
	this->m_BackDC = CreateCompatibleDC(this->m_MainDC);
	hbmp = CreateCompatibleBitmap(this->m_MainDC,this->m_iClientW,this->m_iClientH);
	DeleteObject(SelectObject(this->m_BackDC,hbmp));
	DeleteObject(hbmp);
}
CGameOutput::~CGameOutput()
{
	std::map<std::string,HDC>::iterator i;
	for(i = this->m_Bmp.begin(); i!= this->m_Bmp.end();++i)
	{
		DeleteDC(i->second);
	}
	DeleteDC(this->m_BackDC);
	ReleaseDC(this->m_hWnd,this->m_MainDC);
}

//��ʼ����,��������
void CGameOutput::Begin()
{
	BitBlt(this->m_BackDC,0,0,this->m_iClientW,this->m_iClientH,0,0,0,WHITENESS);
}

void CGameOutput::End()
{
	BitBlt(this->m_MainDC,0,0,this->m_iClientW,this->m_iClientH,this->m_BackDC,0,0,SRCCOPY);
}

//ͼԪ��غ���
void CGameOutput::DrawLine(//����
	int x1,
	int y1,
	int x2,
	int y2,
	unsigned int c,
	int w)
{
	HPEN newpen = 0;
	HPEN oldpen = 0;
	if(RGB(0,0,0) != c || 1 != w)
	{
		newpen = CreatePen(PS_SOLID,w,c);
		oldpen = (HPEN)SelectObject(this->m_BackDC,newpen);
	}

	POINT p;
	MoveToEx(this->m_BackDC,x1,y1,&p);
	LineTo(this->m_BackDC,x2,y2);
	if(newpen)
	{
		SelectObject(this->m_BackDC,oldpen);
		DeleteObject(newpen);
	}
}

void CGameOutput::DrawRectangle1(//�����ľ���
	int x1,
	int y1,
	int x2,
	int y2,
	unsigned int c)
{
	HPEN newpen = 0;
	HPEN oldpen = 0;
	if(RGB(0,0,0) != c)
	{
		newpen = CreatePen(PS_SOLID,1,c);
		oldpen = (HPEN)SelectObject(this->m_BackDC,newpen);
	}

	POINT p[]
	=
	{
		{x1,y1},
		{x2,y1},
		{x2,y2},
		{x1,y2},
		{x1,y1}
	};
	POINT q;
	for(int i = 0; i < 4;++i)
	{
		MoveToEx(m_BackDC,p[i].x,p[i].y,&q);
		LineTo(m_BackDC,p[i + 1].x , p[i + 1].y);
	}

	if(newpen)
	{
		SelectObject(this->m_BackDC,oldpen);
		DeleteObject(newpen);
	}
}

void CGameOutput::DrawRectangle2(//��ʵ�ľ���
	int x1,
	int y1,
	int x2,
	int y2,
	unsigned int pc,
	unsigned int bc)
{
	HPEN newpen = 0;
	HPEN oldpen = 0;
	HBRUSH newbrush = 0;
	HBRUSH oldbrush = 0;
	if(RGB(0,0,0) != pc)
	{
		newpen = CreatePen(PS_SOLID,1,pc);
		oldpen = (HPEN)SelectObject(this->m_BackDC,newpen);
	}
	if(RGB(255,255,255) != bc)
	{
		newbrush = CreateSolidBrush(bc);
		oldbrush = (HBRUSH)SelectObject(m_BackDC,newbrush);
	}

	Rectangle(m_BackDC,x1,y1,x2,y2);

	if(newpen)
	{
		SelectObject(this->m_BackDC,oldpen);
		DeleteObject(newpen);
	}
	if(newbrush)
	{
		SelectObject(m_BackDC,oldbrush);
		DeleteObject(newbrush);
	}
}

void CGameOutput::DrawEllipse1(//��������Բ
	int x1,
	int y1,
	int x2,
	int y2,
	unsigned int c)
{
	HPEN newpen = 0;
	HPEN oldpen = 0;
	if(RGB(0,0,0) != c)
	{
		newpen = CreatePen(PS_SOLID,1,c);
		oldpen = (HPEN)SelectObject(this->m_BackDC,newpen);
	}

	//�õ�����ϵͳԤ�����úõ�GDI����
	HBRUSH newbrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HBRUSH oldbrush = (HBRUSH)SelectObject(m_BackDC,newbrush);

	Ellipse(m_BackDC,x1,y1,x2,y2);

	SelectObject(m_BackDC,oldbrush);

	if(newpen)
	{
		SelectObject(this->m_BackDC,oldpen);
		DeleteObject(newpen);
	}
}

void CGameOutput::DrawEllipse2(//��ʵ����Բ
	int x1,
	int y1,
	int x2,
	int y2,
	unsigned int pc ,
	unsigned int bc )
{
	HPEN newpen = 0;
	HPEN oldpen = 0;
	HBRUSH newbrush = 0;
	HBRUSH oldbrush = 0;
	if(RGB(0,0,0) != pc)
	{
		newpen = CreatePen(PS_SOLID,1,pc);
		oldpen = (HPEN)SelectObject(this->m_BackDC,newpen);
	}
	if(RGB(255,255,255) != bc)
	{
		newbrush = CreateSolidBrush(bc);
		oldbrush = (HBRUSH)SelectObject(m_BackDC,newbrush);
	}

	Ellipse(m_BackDC,x1,y1,x2,y2);

	if(newpen)
	{
		SelectObject(this->m_BackDC,oldpen);
		DeleteObject(newpen);
	}
	if(newbrush)
	{
		SelectObject(m_BackDC,oldbrush);
		DeleteObject(newbrush);
	}
}

//λͼ���
int CGameOutput::LoadDirectory(const char* dn)//�����ļ������������λͼ(������Ŀ¼)
{
	return 0;
}

bool CGameOutput::LoadBmp(const char* fn)//����λͼ
{
	std::string s = fn;
	if(m_Bmp.find(s) != m_Bmp.end())
		return false;
	HBITMAP hbmp = (HBITMAP)LoadImage(0,fn,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	if(!hbmp)
		return false;

	HDC dc = CreateCompatibleDC(m_MainDC);
	DeleteObject(SelectObject(dc,hbmp));
	DeleteObject(hbmp);
	m_Bmp.insert(std::pair<std::string,HDC>(s,dc));
	return true;
}

bool CGameOutput::ReleaseBmp(const char* fn)//�ͷ�λͼ
{
	std::string s = fn;
	std::map<std::string,HDC>::iterator i = m_Bmp.find(s);
	if(i == m_Bmp.end())
		return false;
	DeleteDC(i->second);
	m_Bmp.erase(i);
	return true;
}

bool CGameOutput::DrawBmp(//����λͼ
	const char* fn,
	int dx,int dy,int dw,int dh,int sx,int sy)
{
	std::string s = fn;
	std::map<std::string,HDC>::iterator i = m_Bmp.find(s);
	if(i == m_Bmp.end())
		return false;
	BitBlt(m_BackDC,dx,dy,dw,dh,i->second,sx,sy,SRCCOPY);
	return true;
}