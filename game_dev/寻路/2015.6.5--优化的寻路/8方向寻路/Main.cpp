#include <windows.h>
#include <iostream>

#pragma comment(lib, "msimg32.lib")

#define _MAP_W 16
#define _MAP_H 12
#define _GRID_W 41 //���ӵĿ��ߴ���Ϊ������Ϊ�˼�����ӵ����ĵ�
#define _GRID_H 41
#define _CLIENT_W (_MAP_W * _GRID_W)
#define _CLIENT_H (_MAP_H * _GRID_H)
#define _SLEEP_TIME 33

HWND g_hWnd;
BOOL g_AppActive = TRUE;

void GameInit();
void GameRun();
void GameEnd();

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_ACTIVATEAPP:
		{
			g_AppActive = (BOOL)wParam;
			return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "Test";
	RegisterClass(&wc);

	RECT r
		=
	{
		(GetSystemMetrics(SM_CXSCREEN) - _CLIENT_W) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - _CLIENT_H) / 2,
		(GetSystemMetrics(SM_CXSCREEN) - _CLIENT_W) / 2 + _CLIENT_W,
		(GetSystemMetrics(SM_CYSCREEN) - _CLIENT_H) / 2 + _CLIENT_H
	};

	AdjustWindowRect(&r, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

	g_hWnd = CreateWindow(
		wc.lpszClassName,
		"�򵥽ű�����",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		r.left,
		r.top,
		r.right - r.left,
		r.bottom - r.top,
		HWND_DESKTOP,
		0,
		wc.hInstance,
		0);

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	GameInit();

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (g_AppActive)
			GameRun();
		else
			WaitMessage();
	}

	GameEnd();

	return 1;
}

HDC mainDC;
HDC backDC;
HBITMAP backBMP;

void Init();
void Run();
void End();

void GameInit()
{
	mainDC = GetDC(g_hWnd);
	backDC = CreateCompatibleDC(mainDC);
	backBMP = CreateCompatibleBitmap(mainDC, _CLIENT_W, _CLIENT_H);
	SelectObject(backDC, backBMP);
	SetBkMode(backDC, TRANSPARENT);

	Init();
}

void GameRun()
{
	//�õ�����ϵͳһ˲�䵽Ŀǰ�����ĺ���
	int bt = GetTickCount();
	BitBlt(backDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	Run();

	//�õ�������Ϸѭ��������ʱ��
	BitBlt(mainDC, 0, 0, _CLIENT_W, _CLIENT_H, backDC, 0, 0, SRCCOPY);
	int et = GetTickCount() - bt;
	if (et < _SLEEP_TIME)
		Sleep(_SLEEP_TIME - et);
	else
		Sleep(10);
}

void GameEnd()
{
	End();

	DeleteObject(backBMP);
	DeleteDC(backDC);
	ReleaseDC(g_hWnd, mainDC);
}

#include "FindPathW.h"
#include <vector>
#include <string>



typedef struct _OBJECT
{
	int x, y; //�������ĵ�
	int wd2, hd2; //������ߵ�һ��
	int speed; //�ƶ��ٶ�
	std::vector<int> path; //·��
}OBJECT;

std::vector<OBJECT> obj_vec; //�����

void ObjectMove(OBJECT* obj);

void DrawRect(int x1, int y1, int x2, int y2, COLORREF c)
{
	HBRUSH b1 = CreateSolidBrush(c);
	HBRUSH b0 = (HBRUSH)SelectObject(backDC, b1);
	Rectangle(backDC, x1, y1, x2, y2);
	SelectObject(backDC, b0);
	DeleteObject(b1);
}

char map[_MAP_W * _MAP_H] = 
{
	0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,
	1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,
	1,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1,
	1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,
	1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,
	0,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,
	1,1,0,1,1,1,1,0,0,0,0,0,1,0,0,1,
	1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,
	1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1
};

void Init()
{
	_OBJECT obj = {60, 12, 7, 7, 5};
	obj_vec.push_back(obj);
}

void Run()
{
	//���Ƶ�ͼ
	for (int i = 0; i < _MAP_W * _MAP_H; ++i)
	{
		int x = (i % _MAP_W) * _GRID_W;
		int y = (i / _MAP_W) * _GRID_H;
		DrawRect(x, y, x + _GRID_W, y + _GRID_H, map[i] == 0 ? RGB(127, 127, 127) : RGB(255, 255, 255));
		char buf[32];
		sprintf_s(buf, 32, "%d", i);
		TextOutA(backDC, x, y, buf, (int)strlen(buf));
	}

	//��������
	for (int i = 0; i < (int)obj_vec.size(); ++i)
	{
		DrawRect(
			obj_vec[i].x - obj_vec[i].wd2,
			obj_vec[i].y - obj_vec[i].hd2,
			obj_vec[i].x + obj_vec[i].wd2,
			obj_vec[i].y + obj_vec[i].hd2,
			RGB(255, 0, 0));
	}

	//�ƶ�
	for (int i = 0; i < (int)obj_vec.size(); ++i)
		ObjectMove(&obj_vec[i]);

	//Ѱ·
	if (GetAsyncKeyState(VK_LBUTTON) & 1)
	{
		//�õ���ǰ������������������
		POINT p;
		GetCursorPos(&p);

		//����������ת��Ϊ���ڿͻ�������
		ScreenToClient(g_hWnd, &p);

		//���пͻ���
		if (p.x >= 0 && p.x < _CLIENT_W && p.y >= 0 && p.y < _CLIENT_H)
		{
			//�����˿����ƶ���λ��
			int dest = (p.x / _GRID_W) + (p.y / _GRID_H) * _MAP_W;
			if (map[dest] == 1)
			{
				int cur = (obj_vec[0].x / _GRID_W) + (obj_vec[0].y / _GRID_H) * _MAP_W;
				FindPathW(map, _MAP_W, _MAP_H, cur, dest, &obj_vec[0].path);
			}
		}
	}
}

void End()
{
	
}

#define _JDZ(a) ((a)<0?(-(a)):(a))

void ObjectMove(OBJECT* obj)
{
	//��ǰ��·�����ƶ���
	if (obj->path.empty())
		return;

	//�õ���ǰ��Ŀ�����
	int ti = obj->path.back();

	//�õ�Ŀ����ӵ����ϡ����½�
	int gx1 = (ti % _MAP_W) * _GRID_W;
	int gy1 = (ti / _MAP_W) * _GRID_H;
	int gx2 = gx1 + _GRID_W - 1;
	int gy2 = gy1 + _GRID_H - 1;

	//�õ�����ĵ����ϡ����½�
	int ox1 = obj->x - obj->wd2;
	int oy1 = obj->y - obj->hd2;
	int ox2 = obj->x + obj->wd2;
	int oy2 = obj->y + obj->hd2;

	//��ǰ�����Ƿ��Ѿ���Ŀ�����
	if (ox1 >= gx1 && ox2 <= gx2 && oy1 >= gy1 && oy2 <= gy2)
	{
		//ɾ������ǰĿ�����
		obj->path.pop_back();
		return;
	}

	//�õ����ӵ����ĵ�
	int gcx = (gx1 + gx2) / 2;
	int gcy = (gy1 + gy2) / 2;

	//�ƶ�

	//�����ڸ��ӵ�������
	if (ox1 >= gx1 && ox2 <= gx2)
	{
		//�Ϸ�
		if (obj->y < gcy)
			obj->y += obj->speed;
		//�·�
		else
			obj->y -= obj->speed;
	}
	//�����ڸ��ӵĺ᷽��
	else if (oy1 >= gy1 && oy2 <= gy2)
	{
		//��
		if (obj->x < gcx)
			obj->x += obj->speed;
		//�·�
		else
			obj->x -= obj->speed;
	}
	else
	{
		//�жϵ�ǰ�������ĵ��Ƿ�����
		//Ŀ����ӵĶԽ����ӳ�������
		if (_JDZ(gcx - obj->x) == _JDZ(gcy - obj->y))
		{
			//4���������
			if (obj->x <= gcx && obj->y <= gcy)
			{
				obj->x += obj->speed;
				obj->y += obj->speed;
			}
			else if (obj->x <= gcx && obj->y >= gcy)
			{
				obj->x += obj->speed;
				obj->y -= obj->speed;
			}
			else if (obj->x >= gcx && obj->y >= gcy)
			{
				obj->x -= obj->speed;
				obj->y -= obj->speed;
			}
			else
			{
				obj->x -= obj->speed;
				obj->y += obj->speed;
			}
		}
		else
		{
			//8���������
			
			//6��7����
			if (obj->x <= gcx && obj->y <= gcy)
			{
				//6����
				if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
				{
					int x = obj->x;
					obj->x += obj->speed;
					if (_JDZ(gcx - obj->x) < _JDZ(gcy - obj->y))
						obj->x = x + (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
				//7����
				else
				{
					int y = obj->y;
					obj->y += obj->speed;
					if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
						obj->y = y + (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
			}
			//4��5����
			else if (obj->x <= gcx && obj->y >= gcy)
			{
				//5����
				if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
				{
					int x = obj->x;
					obj->x += obj->speed;
					if (_JDZ(gcx - obj->x) < _JDZ(gcy - obj->y))
						obj->x = x + (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
				//4����
				else
				{
					int y = obj->y;
					obj->y -= obj->speed;
					if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
						obj->y = y - (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
			}
			//2��3����
			else if (obj->x >= gcx && obj->y >= gcy)
			{
				//2����
				if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
				{
					int x = obj->x;
					obj->x -= obj->speed;
					if (_JDZ(gcx - obj->x) < _JDZ(gcy - obj->y))
						obj->x = x - (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
				//3����
				else
				{
					int y = obj->y;
					obj->y -= obj->speed;
					if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
						obj->y = y - (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
			}
			//0��1����
			else
			{
				//1����
				if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
				{
					int x = obj->x;
					obj->x -= obj->speed;
					if (_JDZ(gcx - obj->x) < _JDZ(gcy - obj->y))
						obj->x = x - (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
				//0����
				else
				{
					int y = obj->y;
					obj->y += obj->speed;
					if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
						obj->y = y + (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
			}
		}
	}
}