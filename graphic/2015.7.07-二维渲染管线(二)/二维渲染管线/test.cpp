#include <windows.h>
#include <vector>
#include <time.h>
#include <math.h>
#include "Matrix3.h"
#include "Render2D.h"

#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

BOOL g_Act = TRUE;
HDC g_MainDC;
HDC g_BackDC;

#define _S_W 600
#define _S_H 400
#define _V_LEFT 100
#define _V_TOP 100
#define _V_W 300
#define _V_H 200
MODAL2D fk;
HDC g_BmpDC;

void GameInit(HWND hwnd)
{
	g_MainDC = GetDC(hwnd);
	g_BackDC = CreateCompatibleDC(g_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_MainDC, _CLIENT_W, _CLIENT_H);
	DeleteObject(SelectObject(g_BackDC,hbmp));
	DeleteObject(hbmp);

	srand(time(0));

	//����ģ�ͺ�����
	LoadMODAL2D(&fk, "modal\\fk.txt");
	g_BmpDC = CreateCompatibleDC(g_MainDC);
	hbmp = (HBITMAP)LoadImageA(0, "texture\\01.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	DeleteObject(SelectObject(g_BmpDC,hbmp));
	DeleteObject(hbmp);

	//�����ӿں��ӿڱ任����
	CMatrix3 m;
	SetView(_V_LEFT, _V_TOP, _V_W, _V_H);
	GetViewMatrix(&m, _S_W, _S_H, _V_LEFT, _V_TOP, _V_W, _V_H);
	SetMatrix(_VIEW_MATRIX, &m);
}

int get_rand_int(int min, int max)
{
	return min + rand() % (max - min + 1);
}

void GameRun(HWND hwnd)
{
	//����������任����
	CMatrix3 m;
	static CVector2 eye(0.0f, 0.0f);
	static CVector2 at(0.0f, 1.0f);
	GetCameraMatrix(&m, &eye, &at);
	SetMatrix(_CAMERA_MATRIX, &m);
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		CVector2 dir = at - eye;
		eye += dir.Normalize();
		at += dir.Normalize();
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		CVector2 dir = at - eye;
		eye -= dir.Normalize();
		at -= dir.Normalize();
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		CVector2 dir = at - eye, new_dir;
		dir = dir.Normalize();
		CMatrix3 m;
		m.Rotate(-0.3f);
		_Vec_X_Mat(&dir, &m, &new_dir);
		at = eye + new_dir;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		CVector2 dir = at - eye, new_dir;
		dir = dir.Normalize();
		CMatrix3 m;
		m.Rotate(+0.3f);
		_Vec_X_Mat(&dir, &m, &new_dir);
		at = eye + new_dir;
	}

	BitBlt(g_BackDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	Rectangle(g_BackDC, _V_LEFT, _V_TOP, _V_LEFT + _V_W, _V_TOP + _V_H);

	//��������1
	static float angle = 0.0f;
	//angle += 0.01f;
	CMatrix3 m0;
	m0.Rotate(angle);
	static float x = 0.0f, y = 0.0f;
	if (GetAsyncKeyState('W') & 0x8000)
		y -= 5.0f;
	if (GetAsyncKeyState('S') & 0x8000)
		y += 5.0f;
	if (GetAsyncKeyState('A') & 0x8000)
		x -= 5.0f;
	if (GetAsyncKeyState('D') & 0x8000)
		x += 5.0f;
	CMatrix3 m1;
	m1.Translate(x, y);
	CMatrix3 m2;
	SetMatrix(_WORLD_MATRIX, _Mat_X_Mat(&m0, &m1, &m2));
	DrawMODAL2D(g_BackDC, &fk, g_BmpDC);

	//��������2
	m1.Translate(200, 200);
	SetMatrix(_WORLD_MATRIX, &m1);
	DrawMODAL2D(g_BackDC, &fk, g_BmpDC);

	//���������
	MoveToEx(g_BackDC, (_V_LEFT + (_V_LEFT + _V_W)) / 2, (_V_TOP + (_V_TOP + _V_H)) / 2, 0);
	LineTo(g_BackDC, (_V_LEFT + (_V_LEFT + _V_W)) / 2, (_V_TOP + (_V_TOP + _V_H)) / 2 - 64);

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