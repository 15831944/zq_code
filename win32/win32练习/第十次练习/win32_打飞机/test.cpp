#include <windows.h>
#include <vector>
#include "resource.h"
#include "GameLogic.h"
#include"UseBmp.h"
#pragma comment(lib,"msimg32.lib")
#include<time.h>

#define CLIENT_W 550
#define CLIENT_H 640

BOOL g_Act = TRUE;//���ڼ����־

extern HDC g_mainDC;//����ʾ�豸

extern HDC backDC;//���豸

extern HDC g_bmpdc[4];

HDC g_mainDC;//����ʾ�豸

HDC backDC;//���豸

HDC g_bmpdc[4];





//CGameLogic : ��Ϸ�߼���
//CPlane:�ɻ����� OK
//CEmenyPlane : public CPlane ���˷ɻ��࣬�̳���CPlane OK
//CHeroPlane:public CPlane c�ɻ��࣬�̳���CPlane OK
//CBullet �ӵ����� OK
//CEmenyBullet:public CBullet �����ӵ��� ���̳���CBullet OK
//CHeroBullet:public CBullet Ӣ���ӵ��� ���̳���CBullet OK
//CGameOutput ����࣬��Ҫ������ƻ���

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


//������Ϣ��������������������ϵͳ����
__w64 long __stdcall WindowProc(HWND hwnd,//������Ϣ�Ĵ���
								unsigned int uMsg,//��Ϣ����
								__w64 unsigned int wParam,//��Ϣ���Ӳ���1
								__w64 long lParam)//��Ϣ���Ӳ���2
{
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			//Ͷ��һ��WM_QUIT��Ϣ�����̵߳���Ϣ������
			PostQuitMessage(0);
			//һ�����Ǵ�����ĳ����Ϣ��Ҫֱ�ӷ���0.
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
	//���ǲ����ĵ���Ϣ�͵���DefWindowProc(windows��������Ϣ��Ĭ�ϴ�����)���������Ǵ���
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,//Ӧ�ó���ʵ�����
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	//01)���һ���������Ľṹ��
	WNDCLASS wc;
	//���ڽṹ����������б����������ṹ�崴�����Ĵ��ڶ����У�
	//CS_HREDRAW : ����ˮƽ�ߴ緢���ı�ͻ��ػ�(Ͷ��WM_PAINT��Ϣ)
	//CS_VREDRAW : ������ֱ�ߴ緢���ı�ͻ��ػ�(Ͷ��WM_PAINT��Ϣ)
	wc.style = CS_HREDRAW|CS_VREDRAW;
	//������Ϣ�����ĵ�ַ
	wc.lpfnWndProc = WindowProc;
	//�������Ķ����ֽڣ�һ�㲻ʹ��
	wc.cbClsExtra = 0;
	//���ڵĶ����ֽڣ�һ�㲻ʹ��
	wc.cbWndExtra = 0;
	//Ӧ�ó���ʵ�����
	wc.hInstance = hInstance;
	//ͼ��
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);

	//���
	wc.hCursor = LoadCursor(0,IDC_ARROW);

	//HBRUSH ��ˢ
	//����ϵͳ���ڻ��ƴ��ڱ����ı�����ˢ
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//�˵��ַ���ID�����û������0
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	//���ڵ�����
	wc.lpszClassName = "�˰�";

	//02)ע�����õĴ���
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
	
	//03)�ô������ṹ������������
	HWND hWnd = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 "�ɻ�",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 r.left,//���ڵ����Ͻ�x����
							 r.top,//���ڵ����Ͻ�y����
							 r.right - r.left,//���ڵĿ����أ�
							 r.bottom - r.top,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0
	
	//04)��ʾ����
	ShowWindow(hWnd,nCmdShow);

	//05)���´���
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