#include <windows.h>
#include <vector>
#include <time.h>
#include <math.h>
#include "Matrix3.h"
#include"Render2D.h"

#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

BOOL g_Act = TRUE;//���ڼ����־
HDC g_MainDC;
HDC g_BackDC;
HDC g_BmpDC;

CVector2 t[3];
float angle = 0.0f;
bool fd = true;
float sfl = 1.0f;
CVector2 pos;

_MODAL_2D my_modal;

void DrawTriangleTexture(int x0, int y0,
						 int x1, int y1,
						 int x2, int y2,
						 HDC bmpdc,
						 int u0, int v0,
						 int u1, int v1,
						 int u2, int v2,
						 int left, int top, int right, int bottom);

void GameInit(HWND hwnd)
{
	g_MainDC = GetDC(hwnd);
	g_BackDC = CreateCompatibleDC(g_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_MainDC, _CLIENT_W, _CLIENT_H);
	DeleteObject(SelectObject(g_BackDC,hbmp));
	DeleteObject(hbmp);

	g_BmpDC = CreateCompatibleDC(g_MainDC);
	hbmp = (HBITMAP)LoadImageA(0, "01.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	DeleteObject(SelectObject(g_BmpDC,hbmp));
	DeleteObject(hbmp);

	srand(time(0));

	t[0].Set(-50, -50);
	t[1].Set(+50, -50);
	t[2].Set(0, +50);

	LoadMODAL2D(&my_modal,"fk.txt");
	
}

int get_rand_int(int min, int max)
{
	return min + rand() % (max - min + 1);
}

void GameRun(HWND hwnd)
{
	BitBlt(g_BackDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	//���������ұ�
	//BitBlt(g_BackDC, 320, 0, 320, _CLIENT_H, g_BmpDC, 0, 0, SRCCOPY);

	

	::Rectangle(g_BackDC,199,99,501,401);
	CMatrix3 m1,m2,m3;
	m1.Translate(100,300);
	GetCameraMatrix(&m2,&CVector2(200.0f,300.0f),&CVector2(300.0f,200.0f));
	GetViewMatrix(&m3,200,200,200,100,300,300);

	SetMatrix(_WORLD_MATRIX,&m1);
	SetMatrix(_CAMERA_MATRIX,&m2);
	SetMatrix(_VIEW_MATRIX,&m3);

	DrawMODAL2D(&my_modal,g_BmpDC,200,100,500,400);

	
	
	

	BitBlt(g_MainDC, 0, 0, _CLIENT_W, _CLIENT_H, g_BackDC, 0, 0, SRCCOPY);

	
}

void GameEnd(HWND hwnd)
{
	DeleteDC(g_BmpDC);
	DeleteDC(g_BackDC);
	ReleaseDC(hwnd, g_MainDC); 
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
			PostQuitMessage(0);
			return 0;
		}
	case WM_ACTIVATEAPP:
		{
			g_Act = (BOOL)wParam;
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
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "3dtest";
	RegisterClass(&wc);

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	RECT r = 
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		(sw - _CLIENT_W) / 2 + _CLIENT_W,
		(sh - _CLIENT_H) / 2 + _CLIENT_H
	};

	//�õ����ڷ��
	//��֪�ֽ�????????�ͷ��00001000
	//��ô(�ֽ�&~���)��Ϊ
	//????????
	//11110111
	//--------
	//????0???
	int ws = (WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME) & ~WS_MAXIMIZEBOX;

	AdjustWindowRect(&r, ws, FALSE);

	HWND hWnd = CreateWindow(
		wc.lpszClassName,
		"�������",//���ڱ���������
		ws,//���ڷ��
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

	MSG msg = {};
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(g_Act)
		{
			int bt = GetTickCount();
			GameRun(hWnd);
			int at = GetTickCount() - bt;
			Sleep(at < _SLEEP_TIME ? _SLEEP_TIME - at : 1);
		}
		else
			WaitMessage();
	}

	GameEnd(hWnd);

	return 1;
}

