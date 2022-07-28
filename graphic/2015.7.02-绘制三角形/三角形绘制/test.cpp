#include <windows.h>
#include <vector>
#include <time.h>

#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

BOOL g_Act = TRUE;//���ڼ����־
HDC g_MainDC;
HDC g_BackDC;

void DrawTriangle(int x0, int y0,
				  int x1, int y1,
				  int x2, int y2,
				  COLORREF color);

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
	BitBlt(g_BackDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	DrawTriangle(100, 100, 300, 300, 200, 100, RGB(255, 0, 0));

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

void DrawTriangle_FlatBottom(int x0, int y0,
							 int x1, int y1,
							 int x2, int y2,
							 COLORREF color)
{
	//   (x0,y0)
	//(x1,y1)(x2,y2)
	//ֱ�߹�ʽ�е�б��k�����ʾ����˼����xÿ��
	//��һ����λy�ı仯����1/k���ʾyÿ����һ��
	//��λx�ı仯��

	//�����������ֱ�ߵ��ݶȱ仯ֵ(y��������)
	float left_grads = (float)(x0 - x1) / (y0 - y1);
	float right_grads = (float)(x0 - x2) / (y0 - y2);
	
	//�õ��߶ε�����xֵ
	float left_x = x0;
	float right_x = x0;

	//ѭ������
	for (int y = y0; y <= y1; ++y)
	{
		//�õ���ǰ�߶�����x������ֵ
		int left_int_x = (int)left_x;
		int right_int_x = (int)right_x;

		//���Ƶ�ǰ�߶�
		for (int x = left_int_x; x <= right_int_x; ++x)
			SetPixel(g_BackDC, x, y, color);

		left_x += left_grads;
		right_x += right_grads;
	}
}

void DrawTriangle_FlatTop(int x0, int y0,
						  int x1, int y1,
						  int x2, int y2,
						  COLORREF color)
{
	//(x1,y1)(x2,y2)
	//   (x0,y0)

	//�����������ֱ�ߵ��ݶȱ仯ֵ(y�ݼ�����)
	float left_grads = (float)(x1 - x0) / (y0 - y1);
	float right_grads = (float)(x2 - x0) / (y0 - y2);
	
	//�õ��߶ε�����xֵ
	float left_x = x0;
	float right_x = x0;

	//ѭ������
	for (int y = y0; y >= y1; --y)
	{
		//�õ���ǰ�߶�����x������ֵ
		int left_int_x = (int)left_x;
		int right_int_x = (int)right_x;

		//���Ƶ�ǰ�߶�
		for (int x = left_int_x; x <= right_int_x; ++x)
		{
			SetPixel(g_MainDC, x, y, color);
			//Sleep(1);
		}

		left_x += left_grads;
		right_x += right_grads;
	}
}

void DrawTriangle(int x0, int y0,
				  int x1, int y1,
				  int x2, int y2,
				  COLORREF color)
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
		//���������
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

		if (y1 == y2)
		{
			cx0 = x0; cy0 = y0;
			if (x1 < x2)
			{
				cx1 = x1; cy1 = y1;
				cx2 = x2; cy2 = y2;
			}
			else
			{
				cx1 = x2; cy1 = y2;
				cx2 = x1; cy2 = y1;
			}
		}
		else if (y0 == y1)
		{
			cx0 = x2; cy0 = y2;
			if (x0 < x1)
			{
				cx1 = x0; cy1 = y0;
				cx2 = x1; cy2 = y1;
			}
			else
			{
				cx1 = x1; cy1 = y1;
				cx2 = x0; cy2 = y0;
			}
		}
		else
		{
			cx0 = x1; cy0 = y1;
			if (x0 < x2)
			{
				cx1 = x0; cy1 = y0;
				cx2 = x2; cy2 = y2;
			}
			else
			{
				cx1 = x2; cy1 = y2;
				cx2 = x0; cy2 = y0;
			}
		}

		//ƽ��������
		if (cy0 < cy1)
		{
			DrawTriangle_FlatBottom(
				cx0, cy0,
				cx1, cy1,
				cx2, cy2,
				color);
		}
		//ƽ��������
		else
		{
			DrawTriangle_FlatTop(
				cx0, cy0,
				cx1, cy1,
				cx2, cy2,
				color);
		}
	}
}

