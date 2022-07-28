#include <windows.h>
#include "UseBmp.h"

#pragma comment(lib,"Msimg32.lib")

#define CLIENT_W 640
#define CLIENT_H 480
#define HERO_W  20
#define HERO_H  30
#define HERO_SPEED 5
HDC bmpdc;

POINT hero = {160,240};

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
			PostQuitMessage(0);
			return 0;
		}
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_UP:
				{
					POINT p[]
					=
					{
						{hero.x,hero.y - HERO_SPEED},
						{hero.x + HERO_W / 2 ,hero.y - HERO_SPEED},
						{hero.x + HERO_W ,hero.y - HERO_SPEED}
					};

					bool go = true;

					for(int i = 0; i < 3;++i)
					{
						COLORREF c = GetPixel(bmpdc,p[i].x,p[i].y);

					    if(c == RGB(128,64,0))
						{
							go = false;
							break;
						}
					}
					if(go)
					{
						hero.y -= HERO_SPEED;
					}

				}
				break;
			case VK_DOWN:
				{
				
				}
				break;
			case VK_LEFT:
				{
				
				}
				break;
			case VK_RIGHT:
				{
					
				}
				break;
			}
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			BitBlt(hdc,0,0,640,480,bmpdc,0,0,SRCCOPY);

			Rectangle(hdc,hero.x,hero.y,hero.x + HERO_W, hero.y + HERO_H);

			EndPaint(hwnd,&ps);
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
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "�˰�";
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

	AdjustWindowRect(&r,WS_OVERLAPPED | WS_CAPTION | 
		WS_SYSMENU,FALSE);

	HWND hWnd = CreateWindow(wc.lpszClassName,
							 "������ײ",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 r.left,//���ڵ����Ͻ�x����
							 r.top,//���ڵ����Ͻ�y����
							 r.right - r.left,//���ڵĿ����أ�
							 r.bottom - r.top,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0
	
	bmpdc = GetBmpDC(hWnd,"bmp\\0.bmp");
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		//���������WM_KEYDOWN��WM_KEYUP��Ϣ�͸��ݵ�ǰ�����뷨
		//�ڲ���һ��WM_CHAR��Ϣ��Ͷ�ݵ���Ϣ������
		TranslateMessage(&msg);
		//�ɷ���Ϣ�ز���ϵͳ(���ƾ�������DispatchMessage�����ô�����Ϣ����)
		DispatchMessage(&msg);
	}

	DeleteBmpDC(bmpdc);

	return 1;
}