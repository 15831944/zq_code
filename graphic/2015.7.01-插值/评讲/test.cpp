#include <windows.h>
#include <vector>
#include <time.h>
#include "Vector2.h"
#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

BOOL g_Act = TRUE;//���ڼ����־

HDC g_MainDC;
HDC g_BackDC;

//Ӣ��
CVector2 pos;
CVector2 dir;

//����
struct _DOT
{
	CVector2 pos;
	CVector2 speed;
};
std::vector<std::vector<_DOT>> laser; //�����

void GameInit(HWND hwnd)
{
	g_MainDC = GetDC(hwnd);
	g_BackDC = CreateCompatibleDC(g_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_MainDC, _CLIENT_W, _CLIENT_H);
	DeleteObject(SelectObject(g_BackDC,hbmp));
	DeleteObject(hbmp);

	pos.Set(_CLIENT_W / 2, _CLIENT_H / 2);
}

void GameRun(HWND hwnd)
{
	//����
	BitBlt(g_BackDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	//�õ�����
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);
	CVector2 v(p.x, p.y);
	dir = (v - pos).Normalize();

	//����Ӣ��
	CVector2 u = pos + (40.0f * dir);
	MoveToEx(g_BackDC, u.x, u.y, 0);
	LineTo(g_BackDC, pos.x, pos.y);
	Ellipse(g_BackDC, pos.x - 10, pos.y - 10, pos.x + 10, pos.y + 10);

	//���Ƽ���
	for (int i = 0; i < laser.size(); ++i)
	{
		for (int j = 0; j < laser[i].size() - 1; ++j)
		{
			MoveToEx(g_BackDC, laser[i][j].pos.x, laser[i][j].pos.y, 0);
			LineTo(g_BackDC, laser[i][j + 1].pos.x, laser[i][j + 1].pos.y);
		}
	}

	BitBlt(g_MainDC, 0, 0, _CLIENT_W, _CLIENT_H, g_BackDC, 0, 0, SRCCOPY);

	//�����˶�
	for (int i = 0; i < laser.size(); ++i)
	{
		 //��һ�����ƶ�
		laser[i][0].pos += laser[i][0].speed;

		//�Ƿ��ǽ�淢����ײ
		if (laser[i][0].pos.x < 0 || laser[i][0].pos.x >= _CLIENT_W)
		{
			if (laser[i][0].pos.x < 0)
				laser[i][0].pos.x = 1;
			else
				laser[i][0].pos.x = _CLIENT_W - 2;

			laser[i][0].speed.x = -laser[i][0].speed.x;
			_DOT d;
			d.pos = laser[i][0].pos;
			d.speed.Set();
			laser[i].insert(laser[i].begin() + 1, d);
		}
		else if (laser[i][0].pos.y < 0 || laser[i][0].pos.y >= _CLIENT_H)
		{
			if (laser[i][0].pos.y < 0)
				laser[i][0].pos.y = 1;
			else
				laser[i][0].pos.y = _CLIENT_H - 2;

			laser[i][0].speed.y = -laser[i][0].speed.y;
			_DOT d;
			d.pos = laser[i][0].pos;
			d.speed.Set();
			laser[i].insert(laser[i].begin() + 1, d);
		}

		//���ĵ���ƶ�
		if (_IS_ZERO(laser[i].back().speed.Length()))
		{
			float len = 0.0f;
			for (int j = 0; j < laser[i].size() - 1; ++j)
			{
				len += (laser[i][j].pos - laser[i][j + 1].pos).Length();
			}
			if (len > 100.0f)
			{
				laser[i].back().speed
					= 
				laser[i][laser[i].size() - 2].pos - laser[i].back().pos;
				laser[i].back().speed = laser[i].back().speed.Normalize() * 5.0f;
			}
		}
		else
		{
			laser[i].back().pos += laser[i].back().speed;
			
			//�Ƿ��ǽ�淢����ײ
			if (laser[i].back().pos.x < 0 || laser[i].back().pos.x >= _CLIENT_W)
			{
				if (laser[i].back().pos.x < 0)
					laser[i].back().pos.x = 1;
				else
					laser[i].back().pos.x = _CLIENT_W - 2;

				laser[i].back().speed.x = -laser[i].back().speed.x;
				laser[i].erase(laser[i].end() - 2);
			}
			else if (laser[i].back().pos.y < 0 || laser[i].back().pos.y >= _CLIENT_H)
			{
				if (laser[i].back().pos.y < 0)
					laser[i].back().pos.y = 1;
				else
					laser[i].back().pos.y = _CLIENT_H - 2;

				laser[i].back().speed.y = -laser[i].back().speed.y;
				laser[i].erase(laser[i].end() - 2);
			}
		}
	}

	//�ƶ�Ӣ��
	if (GetAsyncKeyState('W') & 0x8000)
		pos.y -= 5;
	if (GetAsyncKeyState('S') & 0x8000)
		pos.y += 5;
	if (GetAsyncKeyState('A') & 0x8000)
		pos.x -= 5;
	if (GetAsyncKeyState('D') & 0x8000) //10000000 00000000
		pos.x += 5;

	//���伤��
	if (GetAsyncKeyState(VK_LBUTTON) & 1) //00000000 00000001
	{
		_DOT front;
		front.pos = pos + (60.0f * dir);
		front.speed = 5.0f * dir;

		_DOT back;
		back.pos = pos + (60.0f * dir);
		back.speed.Set();

		std::vector<_DOT> v;
		v.push_back(front);
		v.push_back(back);
		laser.push_back(v);
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