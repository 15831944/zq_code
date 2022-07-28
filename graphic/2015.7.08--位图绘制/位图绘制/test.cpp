#include <windows.h>
#include <iostream>

#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

BOOL g_Act = TRUE;
HDC g_MainDC;
HDC g_BackDC;

BITMAPFILEHEADER* LoadBitmap(const char* bmp);
void DrawBitmap(BITMAPFILEHEADER* bmp, int x, int y);

BITMAPFILEHEADER* bmp24, * bmp8;

void GameInit(HWND hwnd)
{
	g_MainDC = GetDC(hwnd);
	g_BackDC = CreateCompatibleDC(g_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_MainDC, _CLIENT_W, _CLIENT_H);
	DeleteObject(SelectObject(g_BackDC,hbmp));
	DeleteObject(hbmp);

	bmp24 = LoadBitmap("0.bmp");
	bmp8 = LoadBitmap("1.bmp");
}

void GameRun(HWND hwnd)
{
	BitBlt(g_BackDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	//DrawBitmap(bmp24, 0, 0);
	DrawBitmap(bmp8, 0, 0);

	BitBlt(g_MainDC, 0, 0, _CLIENT_W, _CLIENT_H, g_BackDC, 0, 0, SRCCOPY);
}

void GameEnd(HWND hwnd)
{
	free(bmp8);
	free(bmp24);
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

	int ws = (WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME) & ~WS_MAXIMIZEBOX;
	AdjustWindowRect(&r, ws, FALSE);
	HWND hWnd = CreateWindow(
		wc.lpszClassName,
		"λͼ����",//���ڱ���������
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

BITMAPFILEHEADER* LoadBitmap(const char* bmp)
{
	FILE* pf = 0;
	fopen_s(&pf, bmp, "rb");
	if (!pf)
		return 0;
	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	BITMAPFILEHEADER* bfh = (BITMAPFILEHEADER*)malloc(fs);
	fread(bfh, 1, fs, pf);
	fclose(pf);

	return bfh;
}

struct _BGR_COLOR
{
	unsigned char b, g, r;
};

void DrawBitmap8(BITMAPFILEHEADER* bmp, int x, int y)
{
	//�õ���Ϣͷ
	BITMAPINFOHEADER* bih = (BITMAPINFOHEADER*)(bmp + 1);

	//�õ���ɫ��
	int* color_table = (int*)(bih + 1);

	//�õ���ɫ��ʼ��ַ�����ߡ�ÿ���ֽ���
	unsigned char* color = (unsigned char*)bmp + bmp->bfOffBits;
	int w = bih->biWidth;
	int h = bih->biHeight;
	int rbs = w;
	if (rbs % 4 != 0)
		rbs += 4 - rbs % 4;

	//static unsigned char t = 0;
	//t += 1;

	//����
	for (int cy = 0; cy < h; ++cy)
	{
		for (int cx = 0; cx < w; ++cx)
		{
			//�õ�cx��cy��Ӧ��λͼ�������ɫ
			unsigned char i = *(color + (h - cy - 1) * rbs + cx);
			//i = (i + ++t) % 256;
			_BGR_COLOR* c = (_BGR_COLOR*)&color_table[i];
			SetPixel(g_BackDC, cx + x, cy + y, RGB(c->r, c->g, c->b));
		}
	}
}

void DrawBitmap24(BITMAPFILEHEADER* bmp, int x, int y)
{
	BITMAPINFOHEADER* bih = (BITMAPINFOHEADER*)(bmp + 1);

	//�õ���ɫ��ʼ��ַ�����ߡ�ÿ���ֽ���
	char* color = (char*)bmp + bmp->bfOffBits;
	int w = bih->biWidth;
	int h = bih->biHeight;
	int rbs = w * 3;
	if (rbs % 4 != 0)
		rbs += 4 - rbs % 4;

	//����
	for (int cy = 0; cy < h; ++cy)
	{
		for (int cx = 0; cx < w; ++cx)
		{
			//�õ�cx��cy��Ӧ��λͼ�������ɫ
			_BGR_COLOR* c = (_BGR_COLOR*)(color + (h - cy - 1) * rbs + cx * 3);
			SetPixel(g_BackDC, cx + x, cy + y, RGB(c->r, c->g, c->b));
		}
	}
}

void DrawBitmap(BITMAPFILEHEADER* bmp, int x, int y)
{
	//�ж���24λλͼ����256ɫͼ�����ݲ�ͬ���
	//���ò�ͬ�ĺ������л���
	BITMAPINFOHEADER* bih = (BITMAPINFOHEADER*)(bmp + 1);
	switch (bih->biBitCount)
	{
	case 8: DrawBitmap8(bmp, x, y); break;
	case 24: DrawBitmap24(bmp, x, y); break;
	}
}