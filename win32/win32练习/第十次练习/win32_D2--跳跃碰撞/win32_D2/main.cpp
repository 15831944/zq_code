#include <windows.h>
#include"UseBmp.h"

#pragma comment(lib,"msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480

#define MAP_W 20
#define MAP_H 20
#define MAP_S MAP_W*MAP_H

#define _TL 0
#define _ZA 1

#define _FALL 0
#define _UP 1
#define _NOMOVE 2


//��������
int grid_w = _CLIENT_W/MAP_W;
int grid_h = _CLIENT_H/MAP_H;
//��ͼ
char map[MAP_S];
//����ʾ�豸
HDC mainDC;
//���豸
HDC backDC;
//�����豸
HDC bmpdc[2];


BOOL g_Act = TRUE;//���ڼ����־

//Ӣ��λ��RECT
RECT hero_r;
//Ӣ�۴��ڱ�־
bool live;
//��Ӣ��λ��
RECT new_hero_r;
//Ӣ�۽�����ٶ�
int a;
//Ӣ���ٶ�
int v;
//Ӣ��״̬�ı�־
int bz;


void GameInit(HWND hwnd)
{
	a= 2;
	v=10;
	bz=_FALL;
	mainDC = GetDC(hwnd);
	backDC = CreateCompatibleDC(mainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(mainDC,_CLIENT_W,_CLIENT_H);
	DeleteObject(SelectObject(backDC,hbmp));	
	DeleteObject(hbmp);
	bmpdc[0] =GetBmpDC(hwnd,"bmp\\0.bmp");
	bmpdc[1] =GetBmpDC(hwnd,"bmp\\1.bmp");
	
	live= false;
	for(int i=0;i<MAP_S;i++)
	{
		map[i] = _TL;
	}	
}
void GameRun()
{
	if(GetAsyncKeyState('A') & 0x8000)
	{
		int x = (hero_r.left - 10)/grid_w;
		int y1 = hero_r.top/grid_h;
		int y2 = hero_r.bottom/grid_h;
		if((hero_r.left - 10)>0)
		{
			int flag =0;
			for(int i=y1;i<=y2;i++)
			{
				if(map[x+i*MAP_W]==_ZA)
				{
					int cz = hero_r.left-(x+1)*grid_w-1;
					hero_r.left = (x+1)*grid_w+1;
					hero_r.right = hero_r.right - cz;
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				hero_r.left-=10;
				hero_r.right-=10;
			}
			
		}else
		{
			int cz = hero_r.left-1;
			hero_r.left = 1;
			hero_r.right = hero_r.right-cz;
		}
	}
	if(GetAsyncKeyState('D') & 0x8000)
	{
		int x = (hero_r.right + 10)/grid_w;
		int y1 = hero_r.top/grid_h;
		int y2 = hero_r.bottom/grid_h;
		if((hero_r.right + 10)<_CLIENT_W)
		{
			int flag =0;
			for(int i=y1;i<=y2;i++)
			{
				if(map[x+i*MAP_W]==_ZA)
				{
					int cz = x*grid_w-1-hero_r.right;
					hero_r.right = x*grid_w-1;
					hero_r.left = hero_r.left+cz;
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				hero_r.left+=10;
				hero_r.right+=10;
			}
			
		}else
		{
			int cz = _CLIENT_W-1 -hero_r.right;
			hero_r.right =_CLIENT_W-1 ;
			hero_r.left = hero_r.left +cz;
		}
	}
	if(GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		v = -14;
		bz = _UP;
	}
	BitBlt(backDC,0,0,_CLIENT_W,_CLIENT_H,0,0,0,WHITENESS);
	for(int i=0;i<MAP_S;i++)
	{
		int x = i%MAP_W;
		int y = i/MAP_W;
		if(map[i]==_ZA)
			TransparentBlt(backDC,x*grid_w,y*grid_h,grid_w,grid_h,bmpdc[0],0,0,40,30,RGB(0,255,0));
	}
	if(live)
	{
		TransparentBlt(backDC,hero_r.left,hero_r.top,hero_r.right-hero_r.left,hero_r.bottom-hero_r.top,bmpdc[1],0,0,56,56,RGB(0,255,0));
	}
	
	BitBlt(mainDC,0,0,_CLIENT_W,_CLIENT_H,backDC,0,0,SRCCOPY);
	BitBlt(backDC,0,0,_CLIENT_W,_CLIENT_H,0,0,0,WHITENESS);
	
	if(bz==_FALL)
	{
		if(v<=22)
			v= v+ a;
		int x1 = hero_r.left/grid_w;
		int x2 = hero_r.right/grid_w;
		int y = (hero_r.bottom+v)/grid_h;
			
		
		if(hero_r.bottom+v<_CLIENT_H)
		{
			for(int i=x1;i<=x2;i++)
			{
				if(map[i+y*MAP_W] == _ZA)
				{
					int cz = y*grid_h-1  - hero_r.bottom;
					hero_r.bottom = y*grid_h-1;
					hero_r.top =hero_r.top + cz;
					bz=_NOMOVE;
					v=10;
					break;
				}
			}
			if(bz==_FALL)
			{
				hero_r.bottom +=v;
				hero_r.top +=v;
			}
		}else
		{
			//��ֵ
			int cz = _CLIENT_H-1 - hero_r.bottom;
			hero_r.bottom=_CLIENT_H-1;
			hero_r.top =hero_r.top + cz;
			bz=_NOMOVE;
			v=10;
		}
	}else
	if(bz==_NOMOVE)
	{
		int x1 = hero_r.left/grid_w;
		int x2 = hero_r.right/grid_w;
		int y = hero_r.bottom/grid_h+1;
		if(y<MAP_W)
		{
			int flag =0 ;
			for(int i=x1;i<=x2;i++)
			{
				if(map[i+y*MAP_W] == _ZA)
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
			{
				bz = _FALL;
			}
		}
	}else
	{
		int x1 = hero_r.left/grid_w;
		int x2 = hero_r.right/grid_w;
		int y = (hero_r.top+v)/grid_h;
			
		
		if(hero_r.top+v>0)
		{
			for(int i=x1;i<=x2;i++)
			{
				if(map[i+y*MAP_W] == _ZA)
				{
					int cz = hero_r.top-((y+1)*grid_h+1);
					hero_r.top =(y+1)*grid_h+1;
					hero_r.bottom = hero_r.bottom-cz;
					bz=_FALL;
					v=0;
					break;
				}
			}
			if(bz!=_FALL)
			{
				hero_r.bottom +=v;
				hero_r.top +=v;
			}
		}else
		{
			//��ֵ
			int cz = hero_r.top-1;
			hero_r.top =1;
			hero_r.bottom=hero_r.bottom-cz;
			bz=_FALL;
			v=0;
		}
		v+=a;
		if(v==0)
			bz = _FALL;
	}
	Sleep(33);
}

void GameEnd(HWND hwnd)
{
	ReleaseDC(hwnd,mainDC);
	DeleteBmpDC(bmpdc[0]);
	DeleteBmpDC(bmpdc[1]);
}

__w64 long __stdcall WindowProc(HWND hwnd,//������Ϣ�Ĵ���
								unsigned int uMsg,//��Ϣ����
								__w64 unsigned int wParam,//��Ϣ���Ӳ���1
								__w64 long lParam)//��Ϣ���Ӳ���2
{
	switch(uMsg)
	{
	//������Ϣ������ʽ
	//1)���ϵͳ�˵��Ĺرղ˵��Alt + F4��
	//2)���Ͻǵ�X��ť
	case WM_LBUTTONDOWN:
		{
			new_hero_r.left = LOWORD(lParam);
			new_hero_r.top = HIWORD(lParam);
			return 0;
		}
	case WM_LBUTTONUP:
		{
			new_hero_r.right = LOWORD(lParam);
			new_hero_r.bottom = HIWORD(lParam);
			if(new_hero_r.left!=new_hero_r.right||new_hero_r.bottom!=new_hero_r.top)
			{
				live = true;
				bz=_FALL;
				if(new_hero_r.left>new_hero_r.right)
				{
					int l = new_hero_r.left;
					new_hero_r.left = new_hero_r.right;
					new_hero_r.right =l;
				}
				if(new_hero_r.top>new_hero_r.bottom)
				{
					int l =new_hero_r.top;
					new_hero_r.top = new_hero_r.bottom;
					new_hero_r.bottom =l;
				}
				hero_r.left = new_hero_r.left;
				hero_r.right = new_hero_r.right;
				hero_r.top = new_hero_r.top;
				hero_r.bottom = new_hero_r.bottom;
			}
			else
				live = false;
			return 0;
		}
	case WM_DESTROY:
		{
			//Ͷ��һ��WM_QUIT��Ϣ�����̵߳���Ϣ������
			PostQuitMessage(0);
			//һ�����Ǵ�����ĳ����Ϣ��Ҫֱ�ӷ���0.
			return 0;
		}
	case WM_ACTIVATEAPP:
		{
			g_Act=(BOOL)wParam;
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			POINT p ={LOWORD(lParam),HIWORD(lParam)};
			int x = p.x/grid_w;
			int y = p.y/grid_h;
			RECT r;
			RECT r1 ={x*grid_w,y*grid_h,x*grid_w+grid_w,y*grid_h+grid_h};
			if(!IntersectRect(&r,&r1,&hero_r))
			{
				if(map[x+y*MAP_W] == _TL)
					map[x+y*MAP_W] = _ZA;
				else
					map[x+y*MAP_W] = _TL;
			}
			return 0;
		}
	}
	//���ǲ����ĵ���Ϣ�͵���DefWindowProc(windows��������Ϣ��Ĭ�ϴ�����)���������Ǵ���
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,//Ӧ�ó���ʵ�����
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = 0;

	wc.hCursor = 0;

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wc.lpszMenuName = 0;

	wc.lpszClassName = L"�˰�";

	RegisterClass(&wc);

	//�õ���ǰ����Ŀ�͸�
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	//���ڵ�λ�ã���С
	RECT r = 
	{
		(sw - _CLIENT_W)/2,
		(sh - _CLIENT_H)/2,
		(sw - _CLIENT_W)/2 + _CLIENT_W,
		(sh - _CLIENT_H)/2 + _CLIENT_H
	};

	AdjustWindowRect(&r,//�趨�Ŀͻ�����λ�ã����
	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,//���ڷ��
	FALSE);//�Ƿ��в˵�

	//03)�ô������ṹ������������
	HWND hWnd = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 L"���ƶ�",//���ڱ���������
							 //WS_THICKFRAME ͨ������϶��ı䴰�ڴ�С
							 //WS_MAXIMIZEBOX �������Ͻǵ���󻯺ͻ�ԭ��ť
							 WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,//���ڷ��
							 r.left,//���ڵ����Ͻ�x����
							 r.top,//���ڵ����Ͻ�y����
							 r.right - r.left,//���ڵĿ����أ�
							 r.bottom - r.top,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	
	GameInit(hWnd);
	MSG msg={} ;
	while (msg.message!=WM_QUIT)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(g_Act)
			GameRun();
		else
			WaitMessage();
	}
	GameEnd(hWnd);

	return 1;
}


