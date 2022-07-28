#include <windows.h>
#include <vector>
#include <time.h>
#include <math.h>
#include "Matrix3.h"

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

	//�õ��任����
	CMatrix3 m[5];
	m[0].Scaling(sfl, sfl);
	m[1].Rotate(angle);
	m[2].Translate(pos.x, pos.y);
	_Mat_X_Mat(_Mat_X_Mat(&m[0], &m[1], &m[3]), &m[2], &m[4]);

	//�õ��任���
	CVector2 u[3];
	for (int i = 0; i < 3; ++i)
		_Vec_X_Mat(&t[i], &m[4], &u[i]);

	Rectangle(g_BackDC, 100, 100, 300, 250);

	//����������
	DrawTriangleTexture(
		u[0].x, u[0].y,
		u[1].x, u[1].y,
		u[2].x, u[2].y,
		g_BmpDC,
		0, 0,
		0, 480 - 1,
		320 - 1, 0,
		100, 100, 300, 250);

	BitBlt(g_MainDC, 0, 0, _CLIENT_W, _CLIENT_H, g_BackDC, 0, 0, SRCCOPY);

	angle += 0.05f;
	if (fd)
	{
		sfl += 0.02f;
		if (sfl > 3.0f)
			fd = false;
	}
	else
	{
		sfl -= 0.02f;
		if (sfl < 0.333f)
			fd = true;
	}
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);
	pos.Set(p.x, p.y);
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

void DrawTriangleTexture_FlatBottom(int x0, int y0,
									int x1, int y1,
									int x2, int y2,
									HDC bmpdc,
									int u0, int v0,
									int u1, int v1,
									int u2, int v2,
									int left, int top, int right, int bottom)
{
	//�ж��Ƿ�Ҫ���л���
	if ((x0 < left && x1 < left && x2 < left) ||
		(y0 < top && y1 < top && y2 < top) ||
		(x0 >= right && x1 >= right && x2 >= right) ||
		(y0 >= bottom && y1 >= bottom && y2 >= bottom))
		return;

	//		 (x0,y0)
	//(x1,y1)		(x2,y2)

	//�õ������ݶȣ����õ�ÿһ���仯����������Ŀ����
	//������yֵÿ����һ����λ��Щ�仯������ı仯��
	float left_x_grads = (float)(x0 - x1) / (y0 - y1);
	float right_x_grads = (float)(x0 - x2) / (y0 - y2);
	float left_u_grads = (float)(u0 - u1) / (y0 - y1);
	float right_u_grads = (float)(u0 - u2) / (y0 - y2);
	float left_v_grads = (float)(v0 - v1) / (y0 - y1);
	float right_v_grads = (float)(v0 - v2) / (y0 - y2);

	//�õ�ÿ���仯������ĳ�ֵ
	float left_x = x0;
	float right_x = x0;
	float left_u = u0;
	float right_u = u0;
	float left_v = v0;
	float right_v = v0;

	//��Χ�ж�
	if (y0 < top)
	{
		//���y0��С��top����ô�������е���ʼ��
		int offset_y = top - y0;
		left_x += left_x_grads * offset_y;
		right_x += right_x_grads * offset_y;
		left_u += left_u_grads * offset_y;
		right_u += right_u_grads * offset_y;
		left_v += left_v_grads * offset_y;
		right_v += right_v_grads * offset_y;
		y0 = top;
	}
	if (y1 >= bottom)
		y1 = bottom - 1;

	//����ѭ��
	for (int y = y0; y <= y1; ++y)
	{
		int x_left = (int)left_x;
		int x_right = (int)right_x;

		//�õ���ǰu��v����xÿ����1����λ���ǵı仯��
		float u_grads = (left_u - right_u) / (left_x - right_x);
		float v_grads = (left_v - right_v) / (left_x - right_x);
		float cur_u = left_u;
		float cur_v = left_v;

		if (x_left < left)
		{
			int offset_x = left - x_left;
			cur_u += u_grads * offset_x;
			cur_v += v_grads * offset_x;
			x_left = left;
		}
		if (x_right >= right)
			x_right = right - 1;

		for (int x = x_left; x <= x_right; ++x)
		{
			COLORREF c = GetPixel(bmpdc, (int)cur_u, (int)cur_v);
			SetPixel(g_BackDC, x, y, c);
			cur_u += u_grads;
			cur_v += v_grads;
			//Sleep(1);
		}

		left_x += left_x_grads;
		right_x += right_x_grads;
		left_u += left_u_grads;
		right_u += right_u_grads;
		left_v += left_v_grads;
		right_v += right_v_grads;
	}
}

void DrawTriangleTexture_FlatTop(int x0, int y0,
								 int x1, int y1,
								 int x2, int y2,
								 HDC bmpdc,
								 int u0, int v0,
								 int u1, int v1,
								 int u2, int v2,
								 int left, int top, int right, int bottom)
{
	//�ж��Ƿ�Ҫ���л���
	if ((x0 < left && x1 < left && x2 < left) ||
		(y0 < top && y1 < top && y2 < top) ||
		(x0 >= right && x1 >= right && x2 >= right) ||
		(y0 >= bottom && y1 >= bottom && y2 >= bottom))
		return;

	//(x1,y1)		(x2,y2)
	//		 (x0,y0)

	//�õ������ݶȣ����õ�ÿһ���仯����������Ŀ����
	//������yֵÿ�ݼ�һ����λ��Щ�仯������ı仯��
	float left_x_grads = (float)(x0 - x1) / (y1 - y0);
	float right_x_grads = (float)(x0 - x2) / (y2 - y0);
	float left_u_grads = (float)(u0 - u1) / (y1 - y0);
	float right_u_grads = (float)(u0 - u2) / (y2 - y0);
	float left_v_grads = (float)(v0 - v1) / (y1 - y0);
	float right_v_grads = (float)(v0 - v2) / (y2 - y0);

	//�õ�ÿ���仯������ĳ�ֵ
	float left_x = x0;
	float right_x = x0;
	float left_u = u0;
	float right_u = u0;
	float left_v = v0;
	float right_v = v0;

	//��Χ�ж�
	if (y0 >= bottom)
	{
		int offset_y = y0 - bottom;
		left_x += left_x_grads * offset_y;
		right_x += right_x_grads * offset_y;
		left_u += left_u_grads * offset_y;
		right_u += right_u_grads * offset_y;
		left_v += left_v_grads * offset_y;
		right_v += right_v_grads * offset_y;
		y0 = bottom - 1;
	}
	if (y1 < top)
		y1 = top;

	//����ѭ��
	for (int y = y0; y >= y1; --y)
	{
		int x_left = (int)left_x;
		int x_right = (int)right_x;

		//�õ���ǰu��v����xÿ����1����λ���ǵı仯��
		float u_grads = (left_u - right_u) / (left_x - right_x);
		float v_grads = (left_v - right_v) / (left_x - right_x);
		float cur_u = left_u;
		float cur_v = left_v;

		if (x_left < left)
		{
			int offset_x = left - x_left;
			cur_u += u_grads * offset_x;
			cur_v += v_grads * offset_x;
			x_left = left;
		}
		if (x_right >= right)
			x_right = right - 1;

		for (int x = x_left; x <= x_right; ++x)
		{
			COLORREF c = GetPixel(bmpdc, (int)cur_u, (int)cur_v);
			SetPixel(g_BackDC, x, y, c);
			cur_u += u_grads;
			cur_v += v_grads;
			//Sleep(1);
		}

		left_x += left_x_grads;
		right_x += right_x_grads;
		left_u += left_u_grads;
		right_u += right_u_grads;
		left_v += left_v_grads;
		right_v += right_v_grads;
	}
}

void DrawTriangleTexture(int x0, int y0,
						 int x1, int y1,
						 int x2, int y2,
						 HDC bmpdc,
						 int u0, int v0,
						 int u1, int v1,
						 int u2, int v2,
						 int left, int top, int right, int bottom)
{
	//������ͬ���ж�
	if (x0 == x1 && x1 == x2 && y0 == y1 && y1 == y2)
		return;

	//���㹲�ߵ��ж�
	if ((y0 - y1) * (x1 - x2) == (y1 - y2) * (x0 - x1))
		return;

	//�����yֵ������ͬ
	if (y0 != y1 && y1 != y2 && y0 != y2)
	{
		//����yֵ��С������������
		POINT p[3] = {{x0, y0}, {x1, y1}, {x2, y2}};
		POINT q[3] = {{u0, v0}, {u1, v1}, {u2, v2}};
		for (int i = 2; i > 0; --i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (p[j].y > p[j + 1].y)
				{
					POINT r;

					r = p[j];
					p[j] = p[j + 1];
					p[j + 1] = r;

					r = q[j];
					q[j] = q[j + 1];
					q[j + 1] = r;
				}
			}
		}

		//��xy�µ�
		POINT r = {0, p[1].y};
		float k, b;
		if (p[0].x != p[2].x)
		{
			k = (float)(p[0].y - p[2].y) / (p[0].x - p[2].x);
			b = p[0].y - k * p[0].x;
			r.x = (int)(((float)r.y - b) / k);
		}
		else
			r.x = p[0].x;

		float len1 = sqrt((float)(r.x - p[0].x) * (r.x - p[0].x) + (r.y - p[0].y) * (r.y - p[0].y));
		float len2 = sqrt((float)(p[2].x - p[0].x) * (p[2].x - p[0].x) + (p[2].y - p[0].y) * (p[2].y - p[0].y));
		float bl = len1 / len2;

		//��uv�µ�
		float f0[2] = {q[0].x, q[0].y};
		float f2[2] = {q[2].x, q[2].y};
		float f3[2] = {f2[0] - f0[0], f2[1] - f0[1]};
		float new_u = q[0].x + f3[0] * bl;
		float new_v = q[0].y + f3[1] * bl;

		//����ƽ����ƽ��������
		if (r.x < p[1].x)
		{
			// p[0]
			//r	p[1]
			// p[2]

			DrawTriangleTexture_FlatBottom(
				p[0].x, p[0].y,
				r.x, r.y,
				p[1].x, p[1].y,
				bmpdc,
				q[0].x, q[0].y,
				new_u, new_v,
				q[1].x, q[1].y,
				left, top, right, bottom);

			DrawTriangleTexture_FlatTop(
				p[2].x, p[2].y,
				r.x, r.y,
				p[1].x, p[1].y,
				bmpdc,
				q[2].x, q[2].y,
				new_u, new_v,
				q[1].x, q[1].y,
				left, top, right, bottom);
		}
		else
		{
			// p[0]
			//p[1] r
			// p[2]

			DrawTriangleTexture_FlatBottom(
				p[0].x, p[0].y,
				p[1].x, p[1].y,
				r.x, r.y,
				bmpdc,
				q[0].x, q[0].y,
				q[1].x, q[1].y,
				new_u, new_v,
				left, top, right, bottom);

			DrawTriangleTexture_FlatTop(
				p[2].x, p[2].y,
				p[1].x, p[1].y,
				r.x, r.y,
				bmpdc,
				q[2].x, q[2].y,
				q[1].x, q[1].y,
				new_u, new_v,
				left, top, right, bottom);
		}
	}
	//�����е�2�����yֵ��ͬ
	else
	{
		//��cx0��cy0�õ��������Ǹ��������
		//��cx1��cy1��cx2��cy2�õ�yֵ��ȵ�������������꣬��cx1��cx2���
		//������������һ���õ���������
		//			(cx0��cy0)
		//(cx1��cy1)		(cx2��cy2)
		//��
		//(cx1��cy1)		(cx2��cy2)
		//			(cx0��cy0)
		int cx0, cx1, cx2, cy0, cy1, cy2;
		int cu0, cu1, cu2, cv0, cv1, cv2;

		if (y1 == y2)
		{
			cx0 = x0; cy0 = y0;
			cu0 = u0; cv0 = v0;
			if (x1 < x2)
			{
				cx1 = x1; cy1 = y1;
				cu1 = u1; cv1 = v1;
				cx2 = x2; cy2 = y2;
				cu2 = u2; cv2 = v2;
			}
			else
			{
				cx1 = x2; cy1 = y2;
				cu1 = u2; cv1 = v2;
				cx2 = x1; cy2 = y1;
				cu2 = u1; cv2 = v1;
			}
		}
		else if (y0 == y1)
		{
			cx0 = x2; cy0 = y2;
			cu0 = u2; cv0 = v2;
			if (x0 < x1)
			{
				cx1 = x0; cy1 = y0;
				cu1 = u0; cv1 = v0;
				cx2 = x1; cy2 = y1;
				cu2 = u1; cv2 = v1;
			}
			else
			{
				cx1 = x1; cy1 = y1;
				cu1 = u1; cv1 = v1;
				cx2 = x0; cy2 = y0;
				cu2 = u0; cv2 = v0;
			}
		}
		else
		{
			cx0 = x1; cy0 = y1;
			cu0 = u1; cv0 = v1;
			if (x0 < x2)
			{
				cx1 = x0; cy1 = y0;
				cu1 = u0; cv1 = v0;
				cx2 = x2; cy2 = y2;
				cu2 = u2; cv2 = v2;
			}
			else
			{
				cx1 = x2; cy1 = y2;
				cu1 = u2; cv1 = v2;
				cx2 = x0; cy2 = y0;
				cu2 = u0; cv2 = v0;
			}
		}

		//ƽ��������
		if (cy0 < cy1)
		{
			DrawTriangleTexture_FlatBottom(
				cx0, cy0,
				cx1, cy1,
				cx2, cy2,
				bmpdc,
				cu0, cv0,
				cu1, cv1,
				cu2, cv2,
				left, top, right, bottom);
		}
		//ƽ��������
		else
		{
			DrawTriangleTexture_FlatTop(
				cx0, cy0,
				cx1, cy1,
				cx2, cy2,
				bmpdc,
				cu0, cv0,
				cu1, cv1,
				cu2, cv2,
				left, top, right, bottom);
		}
	}
}