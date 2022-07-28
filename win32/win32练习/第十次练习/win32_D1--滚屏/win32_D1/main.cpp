#include <windows.h>
#include"UseBmp.h"
#include<time.h>
#pragma comment(lib,"msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480

#define MAP_W 16
#define MAP_H 12
#define MAP_S MAP_W*MAP_H

#define ALL_MAP_W 32
#define ALL_MAP_H 24
#define ALL_MAP_S ALL_MAP_W*ALL_MAP_H

#define _HUA 0
#define _CAO 1
#define _SHUI 2
#define _SHU 3


//����ʾ�豸
HDC	g_mainDC;
//���豸
HDC backDC;
//�����豸
HDC g_bmpdc[2];
//�����豸
HDC byDC;
//���ӵĿ�
int grid_w;
//���ӵĸ�
int grid_h;
//ȫ��ͼ
char allmap[ALL_MAP_W][ALL_MAP_H];
//��ͼ
char map[MAP_W][MAP_H];
//��ͼλ��
int offset_x;
int offset_y;
BOOL g_Act = TRUE;//���ڼ����־
//Ӣ������λ��
POINT hero_p;





void GameInit(HWND hwnd)
{
	hero_p.x =0;
	hero_p.y =0;
	grid_w = _CLIENT_W / MAP_W;
	grid_h = _CLIENT_H / MAP_H;
	g_mainDC = GetDC(hwnd);
	backDC = CreateCompatibleDC(g_mainDC);
	byDC = CreateCompatibleDC(g_mainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_mainDC,grid_w*ALL_MAP_W,grid_h*ALL_MAP_H);
	DeleteObject(SelectObject(byDC,hbmp));	
	HBITMAP hbmp1 = CreateCompatibleBitmap(g_mainDC,_CLIENT_W,_CLIENT_H);
	DeleteObject(SelectObject(backDC,hbmp1));	
	DeleteObject(hbmp);
	DeleteObject(hbmp1);
	g_bmpdc[0] = GetBmpDC(hwnd,"bmp\\0.bmp");
	g_bmpdc[1] = GetBmpDC(hwnd,"bmp\\1.bmp");
	
	offset_x = 0;
	offset_y = 0;
	for(int i=0;i<ALL_MAP_W;i++)
	{
		for(int j = 0;j<ALL_MAP_H;j++)
		{
			allmap[i][j] = rand()%4;
		}
	}
	/*for(int i=0 ;i<MAP_W;i++)
	{
		for(int j=0;j<MAP_H;j++)
		{
			map[i][j] = allmap[i][j];
		}
	}*/
	//BitBlt(backDC,0,0,grid_w*ALL_MAP_W,grid_h*ALL_MAP_H,0,0,0,WHITENESS);
	HBRUSH newh = CreateSolidBrush(RGB(255,215,0));
	HBRUSH oldh = (HBRUSH)SelectObject(byDC,newh);
	Rectangle(byDC,0,0,grid_w*ALL_MAP_W-1,grid_h*ALL_MAP_H-1);
	for(int j=0;j<ALL_MAP_H;j++)
	{
		for(int i=0;i<ALL_MAP_W;i++)
		{
			TransparentBlt(byDC,i*grid_w,j*grid_h,grid_w,grid_h,g_bmpdc[0],allmap[i][j]*40,0,40,30,RGB(0,255,0));
		}
	}
	SelectObject(backDC,oldh);
	DeleteObject(newh);
	DeleteObject(oldh);
}

void GameRun()
{
	BitBlt(backDC,0,0,grid_w*ALL_MAP_W,grid_h*ALL_MAP_H,0,0,0,WHITENESS);
	if(GetAsyncKeyState('W') & 0x8000)
	{
		if(offset_y>0&&hero_p.y<=_CLIENT_H/2)
			offset_y-=10;
		else
		{
			if(hero_p.y>0)
			{
				hero_p.y-=10;
			}
		}
	}
	if(GetAsyncKeyState('S') & 0x8000)
	{
		if(hero_p.y<_CLIENT_H/2||offset_y>=ALL_MAP_H*grid_h-_CLIENT_H)
		{
			if((hero_p.y+offset_y)<ALL_MAP_H*grid_h-grid_h)
				hero_p.y+=10;
		}
		else
			offset_y+=10;
	}
	if(GetAsyncKeyState('A') & 0x8000)
	{
		
		if(offset_x>0&&hero_p.x<=_CLIENT_W/2)
			offset_x-=10;
		else
		{
			if(hero_p.x>0)
			{
				hero_p.x-=10;
			}
		}
	}
	if(GetAsyncKeyState('D') & 0x8000)
	{
		if(hero_p.x<_CLIENT_W/2||offset_x>=ALL_MAP_W*grid_w-_CLIENT_W)
		{
			if((hero_p.x+offset_x)<ALL_MAP_W*grid_w-grid_w)
				hero_p.x+=10;
		}
		else
			offset_x+=10;
	}
	
	BitBlt(backDC,0,0,_CLIENT_W,_CLIENT_H,byDC,offset_x,offset_y,SRCCOPY);
	TransparentBlt(backDC,hero_p.x,hero_p.y,grid_w,grid_h,g_bmpdc[1],0,0,30,20,RGB(0,255,0));
	BitBlt(g_mainDC,0,0,_CLIENT_W,_CLIENT_H,backDC,0,0,SRCCOPY);
	BitBlt(backDC,0,0,grid_w*ALL_MAP_W,grid_h*ALL_MAP_H,0,0,0,WHITENESS);

	Sleep(33);

}

void GameEnd(HWND hwnd)
{
	ReleaseDC(hwnd,g_mainDC);
	DeleteBmpDC(g_bmpdc[0]);
	DeleteBmpDC(g_bmpdc[1]);
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
	case WM_ACTIVATEAPP:
	{
		g_Act=(BOOL)wParam;
		return 0;
	}
	case WM_DESTROY:
		{
			//Ͷ��һ��WM_QUIT��Ϣ�����̵߳���Ϣ������
			PostQuitMessage(0);
			//һ�����Ǵ�����ĳ����Ϣ��Ҫֱ�ӷ���0.
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
	wc.hIcon =0;

	wc.hCursor =0;

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
							 L"����",//���ڱ���������
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
	srand((unsigned int)time(0));

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


