#include <windows.h>
#include <time.h>
#include "Vector2.h"
#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

BOOL g_Act = TRUE;//���ڼ����־

HDC g_MainDC;
HDC g_BackDC;

#define _R 32 //�뾶
#define _SPEED 20.0f //����
#define _SPEED_SUB 0.1f //����
CVector2 pos; //λ��
CVector2 speed; //�ٶ�

void GameInit(HWND hwnd)
{
	g_MainDC = GetDC(hwnd);
	g_BackDC = CreateCompatibleDC(g_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_MainDC, _CLIENT_W, _CLIENT_H);
	DeleteObject(SelectObject(g_BackDC,hbmp));
	DeleteObject(hbmp);
}

void GameRun(HWND hwnd)
{
	BitBlt(g_BackDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	Ellipse(g_BackDC, pos.x - _R, pos.y - _R, pos.x + _R, pos.y + _R);

	BitBlt(g_MainDC, 0, 0, _CLIENT_W, _CLIENT_H, g_BackDC, 0, 0, SRCCOPY);

	//��С�ٶ�
	if (!_IS_ZERO(speed.Length()))
	{
		pos += speed;
		float speed_len = speed.Length();
		CVector2 speed_nor = speed.Normalize();
		speed_len -= _SPEED_SUB;
		if (speed_len <= 0.0f)
			speed.Set();
		else
			//speed = speed_nor * speed_len; //����*����
			speed = speed_len * speed_nor; //����*����
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 1)
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(hwnd, &p);
		if (p.x >= 0 && p.x < _CLIENT_W && p.y >= 0 && p.y < _CLIENT_H)
		{
			CVector2 dir = CVector2(p.x, p.y) - pos;
			speed = dir.Normalize();
			speed *= _SPEED;
		}
	}
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

class A
{
public:
	A(){}
	A(int a){}
	A(int a, int b){}
};

int __stdcall WinMain(HINSTANCE hInstance,//Ӧ�ó���ʵ�����
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	int aa = 1; //����=����
	A a2 = A(); //����=������ͨ�����캯��1����������ೣ����
	A a3 = A(1); //����=������ͨ�����캯��2����������ೣ����
	A a4 = A(1,2); //����=������ͨ�����캯��3����������ೣ����

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
		"��������",//���ڱ���������
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