#include "GameOutput.h"
#include <io.h>
#pragma comment(lib,"msimg32.lib")

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

	SetBkMode(m_BackDC,TRANSPARENT);

	m_MirrorDC = CreateCompatibleDC(m_MainDC);

	hbmp = CreateCompatibleBitmap(m_MainDC,m_iClientW,m_iClientH);

	DeleteObject(SelectObject(m_MirrorDC,hbmp));

	DeleteObject(hbmp);
}
CGameOutput::~CGameOutput()
{
	std::map<std::string,HDC>::iterator i;
	for(i = this->m_Bmp.begin(); i!= this->m_Bmp.end();++i)
	{
		DeleteDC(i->second);
	}

	std::map<std::string,HFONT>::iterator i1;
	for(i1 = m_Font.begin();i1 != m_Font.end(); ++i1)
	{
		DeleteObject(i1->second);
	}
	DeleteDC(this->m_BackDC);
	DeleteDC(this->m_MirrorDC);
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
	int r = 0;
	std::string s1 = dn;
	s1 += "\\*.*";
	_finddata_t fd;
	intptr_t fr = _findfirst(s1.c_str(),&fd);
	if(-1 != fr)
	{
		do
		{
			//��Ŀ¼
			if(fd.attrib & _A_SUBDIR)
			{
				if(strcmp(fd.name,".") != 0
					&& strcmp(fd.name,"..") != 0)
				{
					std::string s2 = dn;
					s2 += "\\";
					s2 += fd.name;
					r += LoadDirectory(s2.c_str());
				}
			}
			//�ļ�
			else
			{
				char* p = strchr(fd.name,'.');
				if(p)
				{
					//�õ���׺��
					std::string s3 = p + 1;
					//�����е��ַ�����Сд
					for(unsigned int  i = 0; i < s3.length();++i)
					{
						if(s3[i] >= 'A' && s3[i] <= 'Z')
							s3[i] += ('a' - 'A');
					}
					//λͼ
					if(strcmp(s3.c_str(),"bmp") == 0)
					{
						std::string s4 = dn;
						s4 += "\\";
						s4 += fd.name;
						if(LoadBmp(s4.c_str()))
							r += 1;
					}
				}
			}
		}while(0 == _findnext(fr,&fd));

		_findclose(fr);
	}
	return r;
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

bool CGameOutput::DrawBmp1(//����͸��λͼ
		const char* fn,
		int dx,int dy,int dw,int dh,int sx,int sy,
		char m ,unsigned int tc )
{
	if(m < _MIRROR_NONE || m > _MIRROR_LRTB)
		return false;
	std::string s = fn;
	std::map<std::string,HDC>::iterator i = m_Bmp.find(s);
	if(i == m_Bmp.end())
		return false;

	switch(m)
	{
	case _MIRROR_NONE:
		TransparentBlt(m_BackDC,dx,dy,dw,dh,i->second,sx,sy,dw,dh,tc);
		break;
	case _MIRROR_LR:
		{
			StretchBlt(m_MirrorDC,dw + dx,dy,-dw,dh,i->second,sx,sy,dw,dh,SRCCOPY);
			TransparentBlt(m_BackDC,dx,dy,dw,dh,m_MirrorDC,dx,dy,dw,dh,tc);
			break;
		}
	case _MIRROR_TB:
		{
			StretchBlt(m_MirrorDC,dx,dy + dh,dw,-dh,i->second,sx,sy,dw,dh,SRCCOPY);
			TransparentBlt(m_BackDC,dx,dy,dw,dh,m_MirrorDC,dx,dy,dw,dh,tc);
			break;	
		}
	case _MIRROR_LRTB:
		{
			StretchBlt(m_MirrorDC,dx + dw - 1,dy + dh - 1,-dw,-dh,i->second,sx,sy,dw,dh,SRCCOPY);
			TransparentBlt(m_BackDC,dx,dy,dw,dh,m_MirrorDC,dx,dy,dw,dh,tc);
			break;	
		}
	}
	return true;
}

bool  CGameOutput::DrawBmp2(//����λͼ
		const char* fn,
		int dx,int dy,int dw,int dh,int sx,int sy,
		char m)
{
	if(m < _MIRROR_NONE || m > _MIRROR_LRTB)
		return false;
	std::string s = fn;
	std::map<std::string,HDC>::iterator i = m_Bmp.find(s);
	if(i == m_Bmp.end())
		return false;

	switch(m)
	{
	case _MIRROR_NONE:
		BitBlt(m_BackDC,dx,dy,dw,dh,i->second,sx,sy,SRCCOPY);
		break;
	case _MIRROR_LR:
		{
			StretchBlt(m_BackDC,dx + dw - 1,dy,-dw,dh,i->second,sx,sy,dw,dh,SRCCOPY);
			break;
		}
	case _MIRROR_TB:
		{
			StretchBlt(m_BackDC,dx,dx + dh - 1,dw,-dh,i->second,sx,sy,dw,dh,SRCCOPY);
			break;	
		}
	case _MIRROR_LRTB:
		{
			StretchBlt(m_BackDC,dx + dw - 1,dy + dh - 1,-dw,-dh,i->second,sx,sy,dw,dh,SRCCOPY);
			break;	
		}
	}
	return true;
}

bool CGameOutput::LoadFont(
	const char* id,//����ID
	int w,//�����
	int h,//�����
	int we,//�����ϸ
	bool i,//�Ƿ�Ϊб��
	bool u,//�Ƿ����»���
	bool s ,//�Ƿ��д�Խ��
	const char* fn )//�����������
{
	std::string sid = id;
	if(m_Font.find(sid) != m_Font.end())
		return false;
	HFONT font = CreateFontA(h,w,0,0,we,i,u,s,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,fn);
	if(!font)
		return false;
	m_Font.insert(std::pair<std::string,HFONT>(sid,font));
	return true;
}

bool CGameOutput::ReleaseFont(const char* id)
{
	std::string s = id;
	std::map<std::string,HFONT>::iterator i = m_Font.find(s);
	if( i == m_Font.end())
		return false;

	DeleteObject(i->second);
	m_Font.erase(i);
	return true;
}

bool CGameOutput::DrawString1(//���Ƶ�������
	const char* id,//����,����Ϊ0
	int x,
	int y,
	const char* t,//����
	unsigned int c)//��ɫ
{
	if(id)
	{
		std::string s = id;
		std::map<std::string,HFONT>::iterator i = m_Font.find(s);
		if( i == m_Font.end())
			return false;
		HFONT oldfont = (HFONT)SelectObject(m_BackDC,i->second);
		unsigned int pc = SetTextColor(m_BackDC,c);
		TextOutA(m_BackDC,x,y,t,(int)strlen(t));
		SetTextColor(m_BackDC,pc);
		SelectObject(m_BackDC,oldfont);
	}
	else
	{
		unsigned int pc = SetTextColor(m_BackDC,c);
		TextOutA(m_BackDC,x,y,t,(int)strlen(t));
		SetTextColor(m_BackDC,pc);
	}
	return true;
}

bool CGameOutput::DrawString2(//���ƶ�������
	const char* id,
	int x,
	int y,
	int w,
	int h,
	const char* t,
	unsigned int c)
{
	if(id)
	{
		std::string s = id;
		std::map<std::string,HFONT>::iterator i = m_Font.find(s);
		if( i == m_Font.end())
			return false;
		HFONT oldfont = (HFONT)SelectObject(m_BackDC,i->second);
		unsigned int pc = SetTextColor(m_BackDC,c);
		RECT r = {x,y,x + w,y + h};
		DrawTextA(m_BackDC,t,(int)strlen(t),&r,DT_WORDBREAK);
		SetTextColor(m_BackDC,pc);
		SelectObject(m_BackDC,oldfont);
	}
	else
	{
		unsigned int pc = SetTextColor(m_BackDC,c);
		RECT r = {x,y,x + w,y + h};
		DrawTextA(m_BackDC,t,(int)strlen(t),&r,DT_WORDBREAK);
		SetTextColor(m_BackDC,pc);
	}
	return true;
}