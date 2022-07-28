#include <windows.h>
#include <vector>
#include <time.h>
#include "Matrix3.h"
#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

BOOL g_Act = TRUE;//���ڼ����־

HDC g_MainDC;
HDC g_BackDC;

CVector2 zfx[4];

float angle = 0.0f; //�Ƕ�
bool fd = true; //�Ŵ�
float sfl = 1.0f; //������
CVector2 wz; //λ��

void GameInit(HWND hwnd)
{
	g_MainDC = GetDC(hwnd);
	g_BackDC = CreateCompatibleDC(g_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_MainDC, _CLIENT_W, _CLIENT_H);
	DeleteObject(SelectObject(g_BackDC,hbmp));
	DeleteObject(hbmp);

	srand(time(0));

	zfx[0].Set(100, 100);
	zfx[1].Set(100, -100);
	zfx[2].Set(-100, -100);
	zfx[3].Set(-100, 100);
}

void GameRun(HWND hwnd)
{
	BitBlt(g_BackDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	CMatrix3 m0, m1, m2, m3, m4;

	//�õ���ת����
	angle += 0.1f;
	m0.Rotate(angle);

	//�õ�ƽ�ƾ���
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);
	wz.x = p.x;
	wz.y = p.y;
	m1.Translate(wz.x, wz.y);

	//�õ����ž���
	if (fd)
	{
		sfl += 0.05f;
		if (sfl > 3.0f)
			fd = false;
	}
	else
	{
		sfl -= 0.05f;
		if (sfl < 0.333f)
			fd = true;
	}
	m2.Scaling(sfl, sfl);

	//�õ���Ͼ���
	_MxM(_MxM(&m0, &m2, &m3), &m1, &m4);

	//�õ��任���
	CVector2 u[4];
	for (int i = 0; i < 4; ++i)
		_VxM(&zfx[i], &m4, &u[i]); //u2�洢����ѡ����ƽ�ƵĽ��
	
	//����
	MoveToEx(g_BackDC, u[0].x, u[0].y, 0);
	LineTo(g_BackDC, u[1].x, u[1].y);
	MoveToEx(g_BackDC, u[1].x, u[1].y, 0);
	LineTo(g_BackDC, u[2].x, u[2].y);
	MoveToEx(g_BackDC, u[2].x, u[2].y, 0);
	LineTo(g_BackDC, u[3].x, u[3].y);
	MoveToEx(g_BackDC, u[3].x, u[3].y, 0);
	LineTo(g_BackDC, u[0].x, u[0].y);

	BitBlt(g_MainDC, 0, 0, _CLIENT_W, _CLIENT_H, g_BackDC, 0, 0, SRCCOPY);
}

void GameEnd(HWND hwnd)
{
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