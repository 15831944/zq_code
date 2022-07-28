#include <windows.h>
#include "UseBmp.h"

#pragma comment(lib,"Msimg32.lib")

#define CLIENT_W 640
#define CLIENT_H 480
#define _GRID_W 100
#define _GRID_H 50
#define _GRID_HW (_GRID_W / 2)
#define _GRID_HH (_GRID_H / 2)
#define _INIT_X  (CLIENT_W / 2 - _GRID_W / 2)
#define _INIT_Y  0

#define _MAP_W 6
#define _MAP_H 6
#define _MAP_S (_MAP_W * _MAP_H)


//0 ͨ· 0.bmp
//1 �ϰ� 1.bmp
//2 ���� 2.bmp
//3 ľ   3.bmp
//4 ��   4.bmp
//5 Ӣ�� 5
//6 ��
char map[_MAP_S] = 
{
	0,1,1,1,1,1,
	0,0,0,0,0,0,
	0,0,3,2,0,0,
	0,0,0,4,0,0,
	0,5,0,0,0,0,
	0,0,0,0,0,0
};

HDC bmpdc[7];

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
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			Rectangle(hdc,0,0,CLIENT_W,CLIENT_H);

			int offset[]
			= 
			{
				0,13,13,36,36,50,50
			};

			for(int i = 0; i < _MAP_S ;++i)
			{
				int x = i % _MAP_W;
				int y = i / _MAP_W;
				int rx = _INIT_X + (x - y) * _GRID_HW;
				int ry = _INIT_Y + (x + y) * _GRID_HH;

				TransparentBlt(hdc,rx,ry - offset[map[i]],_GRID_W, _GRID_H + offset[map[i]],bmpdc[map[i]],
					0,0,_GRID_W,_GRID_H + offset[map[i]],RGB(0,255,0));
			}

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
							 "������",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 r.left,//���ڵ����Ͻ�x����
							 r.top,//���ڵ����Ͻ�y����
							 r.right - r.left,//���ڵĿ����أ�
							 r.bottom - r.top,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	bmpdc[0] = GetBmpDC(hWnd,"bmp\\0.bmp");
	bmpdc[1] = GetBmpDC(hWnd,"bmp\\1.bmp");
	bmpdc[2] = GetBmpDC(hWnd,"bmp\\2.bmp");
	bmpdc[3] = GetBmpDC(hWnd,"bmp\\3.bmp");
	bmpdc[4] = GetBmpDC(hWnd,"bmp\\4.bmp");
	bmpdc[5] = GetBmpDC(hWnd,"bmp\\5.bmp");
	bmpdc[6] = GetBmpDC(hWnd,"bmp\\6.bmp");

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

	for(int i = 0; i < 7;++i)
		DeleteBmpDC(bmpdc[i]);

	return 1;
}