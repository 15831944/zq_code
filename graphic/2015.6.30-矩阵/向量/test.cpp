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

#define _R 32 //�뾶
#define _SPEED 10.0f //����
#define _SPEED_SUB 0.1f //����
CVector2 pos; //λ��
CVector2 speed; //�ٶ�

struct _SEGMENT
{
	CVector2 v[2];
};
std::vector<_SEGMENT> segments; //�߶α�

//����߶ε���ײ
bool Collide(CVector2& pos, CVector2& speed, CVector2& v0, CVector2& v1, CVector2& jd)
{
	//�õ�֮ǰ��λ��
	CVector2 pre_pos = pos - speed;

	//�õ���ص���������
	CVector2 u1 = pre_pos - v0;
	CVector2 u2 = pos - v0;
	CVector2 u3 = v1 - v0;

	//����Ϊ��ά����
	float w1[] = {u1.x, u1.y, 0.0f};
	float w2[] = {u2.x, u2.y, 0.0f};
	float w3[] = {u3.x, u3.y, 0.0f};

	//�õ���˵�zֵ
	float z1 = u3.x * u1.y - u3.y * u1.x;
	float z2 = u3.x * u2.y - u3.y * u2.x;

	//���ͬ����ôpos��pre_pos�����߶�v0-v1��ͬ��
	if (z1 * z2 >= 0.0f)
		return false;
	
	//�õ�����ֱ�ߣ�y=kx+b��
	float k1 = (pos.y - pre_pos.y) / (pos.x - pre_pos.x);
	float b1 = pos.y - k1 * pos.x;
	float k2 = (v1.y - v0.y) / (v1.x - v0.x);
	float b2 = v0.y - k2 * v0.x;

	//�õ�����ֱ�ߵĽ���
	//y=k1x+b1
	//y=k2x+b2
	float x = (b2 - b1) / (k1 - k2);

	jd.x = x;
	jd.y = k1 * x + b1;

	//�õ��߶ε�x��ֵ
	float minx = v0.x < v1.x ? v0.x : v1.x;
	float maxx = v0.x > v1.x ? v0.x : v1.x;

	return x >= minx && x <= maxx;
}

void Rebound(CVector2& pos, CVector2& speed, CVector2& v0, CVector2& v1)
{
	CVector2 jd;
	bool b = Collide(pos, speed, v0, v1, jd);
	if (b)
	{
		pos = jd - speed.Normalize();
		CVector2 v = v0 - v1;
		CVector2 u = speed.Projection(v);
		CVector2 w = speed - u;
		speed = -w + u;
	}
}

void GameInit(HWND hwnd)
{
	g_MainDC = GetDC(hwnd);
	g_BackDC = CreateCompatibleDC(g_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_MainDC, _CLIENT_W, _CLIENT_H);
	DeleteObject(SelectObject(g_BackDC,hbmp));
	DeleteObject(hbmp);

	srand(time(0));
}

void GameRun(HWND hwnd)
{
	//����
	BitBlt(g_BackDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	Ellipse(g_BackDC, pos.x - _R, pos.y - _R, pos.x + _R, pos.y + _R);
	for (int i = 0; i < segments.size(); ++i)
	{
		MoveToEx(g_BackDC, segments[i].v[0].x, segments[i].v[0].y, 0);
		LineTo(g_BackDC, segments[i].v[1].x, segments[i].v[1].y);
	}

	BitBlt(g_MainDC, 0, 0, _CLIENT_W, _CLIENT_H, g_BackDC, 0, 0, SRCCOPY);

	//��С�ٶ�
	if (!_IS_ZERO(speed.Length()))
	{
		pos += speed;

		for (int i = 0; i < segments.size(); ++i)
			Rebound(pos, speed, segments[i].v[0], segments[i].v[1]);

		float speed_len = speed.Length();
		CVector2 speed_nor = speed.Normalize();
		speed_len -= _SPEED_SUB;
		if (speed_len <= 0.0f)
			speed.Set();
		else
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

	if (GetAsyncKeyState(VK_RETURN) & 1)
	{
		_SEGMENT s;
		s.v[0].Set(rand() % _CLIENT_W, rand() % _CLIENT_H);
		s.v[1].Set(rand() % _CLIENT_W, rand() % _CLIENT_H);
		segments.push_back(s);
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