#include <windows.h>
#include <vector>
#include "resource.h"
#include "GameLogic.h"
#include"UseBmp.h"
#pragma comment(lib,"msimg32.lib")
#include<time.h>

#define CLIENT_W 550
#define CLIENT_H 640

BOOL g_Act = TRUE;//窗口激活标志

extern HDC g_mainDC;//主显示设备

extern HDC backDC;//后备设备

extern HDC g_bmpdc[4];

HDC g_mainDC;//主显示设备

HDC backDC;//后备设备

HDC g_bmpdc[4];





//CGameLogic : 游戏逻辑类
//CPlane:飞机父类 OK
//CEmenyPlane : public CPlane 敌人飞机类，继承与CPlane OK
//CHeroPlane:public CPlane c飞机类，继承与CPlane OK
//CBullet 子弹父类 OK
//CEmenyBullet:public CBullet 敌人子弹类 ，继承与CBullet OK
//CHeroBullet:public CBullet 英雄子弹类 ，继承与CBullet OK
//CGameOutput 输出类，主要负责绘制画面

POINT HeroPoint = {CLIENT_W/2,CLIENT_H/2};

CGameLogic g_clogic;

bool g_bInit = false;

void GameInit(HWND hwnd)
{
	g_mainDC=GetDC(hwnd);
	backDC=CreateCompatibleDC(g_mainDC);
	HBITMAP hbmp=CreateCompatibleBitmap(g_mainDC,CLIENT_W,CLIENT_H);
	DeleteObject(SelectObject(backDC,hbmp));
	DeleteObject(hbmp);
	g_bmpdc[0]=GetBmpDC(hwnd,"bmp\\0.bmp");
	g_bmpdc[1]=GetBmpDC(hwnd,"bmp\\1.bmp");
	g_bmpdc[2]=GetBmpDC(hwnd,"bmp\\2.bmp");
	g_bmpdc[3]=GetBmpDC(hwnd,"bmp\\3.bmp");
	g_clogic.Init(100,CLIENT_W,CLIENT_H);
	g_clogic.SetHeroPoint(HeroPoint);
	
}

void GameRun()
{
	BitBlt(backDC,0,0,CLIENT_W,CLIENT_H,0,0,0,WHITENESS);
	TransparentBlt(backDC,0,0,CLIENT_W,CLIENT_H,g_bmpdc[0],0,0,CLIENT_W,CLIENT_H,RGB(0,3,0));
	//TransparentBlt(backDC,0,0,CLIENT_W,CLIENT_H,g_bmpdc[4],0,550,CLIENT_W,CLIENT_H,SRCCOPY);
	POINT p={CLIENT_W/2,CLIENT_H};
	if(GetAsyncKeyState('W') & 0x8000)
	{
		HeroPoint.y-=10;
		g_clogic.SetHeroPoint(HeroPoint);
	}
	if(GetAsyncKeyState('S') & 0x8000)
	{
		HeroPoint.y+=10;
		g_clogic.SetHeroPoint(HeroPoint);
	}
	if(GetAsyncKeyState('A') & 0x8000)
	{
		HeroPoint.x-=10;
		g_clogic.SetHeroPoint(HeroPoint);
	}
	if(GetAsyncKeyState('D') & 0x8000)
	{
		HeroPoint.x+=10;
		g_clogic.SetHeroPoint(HeroPoint);
	}
	g_clogic.Run();
	g_clogic.Paint();
	BitBlt(g_mainDC,0,0,CLIENT_W,CLIENT_H,backDC,0,0,SRCCOPY);
	BitBlt(backDC,0,0,CLIENT_W,CLIENT_H,0,0,0,WHITENESS);
	Sleep(33);
}

void GameEnd(HWND hwnd)
{
	ReleaseDC(hwnd,g_mainDC);
	DeleteBmpDC(g_bmpdc[0]);
	DeleteBmpDC(g_bmpdc[1]);
	DeleteBmpDC(g_bmpdc[2]);
	DeleteBmpDC(g_bmpdc[3]);
	
}


//窗口消息函数，本函数将被操作系统调用
__w64 long __stdcall WindowProc(HWND hwnd,//产生消息的窗口
								unsigned int uMsg,//消息类型
								__w64 unsigned int wParam,//消息附加参数1
								__w64 long lParam)//消息附加参数2
{
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			//投递一个WM_QUIT消息到本线程的消息队列中
			PostQuitMessage(0);
			//一般我们处理了某个消息都要直接返回0.
			return 0;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == 0)
			{
				switch(LOWORD(wParam))
				{
				case ID_40001:
					{
						DestroyWindow(hwnd);
					}
					break;
				case ID_40002:
					{
					}
					break;
				case ID_40003:
					{
					}
					break;
				case ID_40004:
					{
					}
					break;
				}
			}
			return 0;
		}
	
	case WM_KEYDOWN:
		{
			if(wParam == 'J')
			{
				POINT p;
				p.x=g_clogic.GetHeroPoint().x;
				p.y=g_clogic.GetHeroPoint().y-20;
				g_clogic.SetHeroAttack(p);
			}
			if(wParam == 'K')
			{
				if(g_bInit)
				{
					g_clogic.Brom();
					InvalidateRect(hwnd,0,TRUE);
				}
			}
			return 0;
		}
	/*case WM_MOUSEMOVE:
		{
			POINT point = {LOWORD(lParam),HIWORD(lParam)};
			if(g_bInit)
			{
				g_clogic.SetHeroPoint(point);
				InvalidateRect(hwnd,0,TRUE);
			}
			return 0;
		}*/
	case WM_ACTIVATEAPP:
		{
			g_Act=(BOOL)wParam;
			return 0;
		}
	}
	//我们不关心的消息就调用DefWindowProc(windows对所有消息的默认处理函数)来帮助我们处理
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,//应用程序实例句柄
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	//01)填充一个窗口类别的结构体
	WNDCLASS wc;
	//窗口结构体类别风格（所有被本窗口类别结构体创建出的窗口都具有）
	//CS_HREDRAW : 窗口水平尺寸发生改变就会重绘(投递WM_PAINT消息)
	//CS_VREDRAW : 窗口竖直尺寸发生改变就会重绘(投递WM_PAINT消息)
	wc.style = CS_HREDRAW|CS_VREDRAW;
	//窗口消息函数的地址
	wc.lpfnWndProc = WindowProc;
	//窗口类别的额外字节，一般不使用
	wc.cbClsExtra = 0;
	//窗口的额外字节，一般不使用
	wc.cbWndExtra = 0;
	//应用程序实例句柄
	wc.hInstance = hInstance;
	//图标
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);

	//光标
	wc.hCursor = LoadCursor(0,IDC_ARROW);

	//HBRUSH 画刷
	//操作系统用于绘制窗口背景的背景画刷
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//菜单字符串ID，如果没有则填0
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	//窗口的名字
	wc.lpszClassName = "八班";

	//02)注册填充好的窗口
	RegisterClass(&wc);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	RECT r = 
	{
		(sw - CLIENT_W) / 2,
		(sh - CLIENT_H) / 2,
		(sw - CLIENT_W) / 2 + CLIENT_W,
		(sh - CLIENT_H) / 2 + CLIENT_H
	};
	
	//03)用窗口类别结构体来创建窗口
	HWND hWnd = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 "飞机",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 r.left,//窗口的左上角x坐标
							 r.top,//窗口的左上角y坐标
							 r.right - r.left,//窗口的宽（像素）
							 r.bottom - r.top,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0
	
	//04)显示窗口
	ShowWindow(hWnd,nCmdShow);

	//05)更新窗口
	UpdateWindow(hWnd);

	srand((unsigned int)time(0));
	
	RECT clientRect;
	GetClientRect(hWnd,&clientRect);
	g_clogic.Init(0,clientRect.right,clientRect.bottom);
	g_bInit = true;
	
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