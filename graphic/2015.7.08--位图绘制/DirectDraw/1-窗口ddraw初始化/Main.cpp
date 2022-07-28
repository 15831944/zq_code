#include <iostream>
#include "Main.h"
#include "Game.h"

#define _SLEEP_TIME 33

BOOL g_Active = TRUE;
HWND g_hWnd = 0;

LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
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
			g_Active = (BOOL)wParam;
			return 0;
		}
	case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
				PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	//���һ���������ṹ��
	WNDCLASS wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "G03113121004";

	//ע�ᴰ�����ṹ��
	RegisterClass(&wc);

	//���㴰��Ӧ�ڵ�λ��
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	RECT r = {(sw - _CLIENT_W) / 2, (sh - _CLIENT_H) / 2, r.left + _CLIENT_W, r.top + _CLIENT_H};
	AdjustWindowRect(&r, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

	//��������
	g_hWnd = CreateWindow(
		wc.lpszClassName,
		"��ʼ��DirectDraw",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		r.left,
		r.top,
		r.right - r.left,
		r.bottom - r.top,
		HWND_DESKTOP,
		0,
		wc.hInstance,
		0);

	Init(); //��ʼ��

	//��ʾ����
	ShowWindow(g_hWnd, nCmdShow);

	//���´���
	UpdateWindow(g_hWnd);

	//��Ϣѭ��
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (g_Active)
		{
			int bt = GetTickCount();
			Run(); //����
			int at = GetTickCount() - bt;
			Sleep(at < _SLEEP_TIME ? _SLEEP_TIME - at : 1);
		}
		else
			WaitMessage();
	}

	End(); //����

	//ע���������ṹ��
	UnregisterClass(wc.lpszClassName, wc.hInstance);

	//�����˳�ֵ������ϵͳ
	return (int)msg.wParam;
}

//DirectX���
//1)DirectGraphics
//{
//	a)DirectDraw����άͼ�λ���
//	b)Direct3D����άͼ�λ���
//}
//2)DirectSound���ͼ���Ƶ
//3)DirectMusic���߼���Ƶ
//4)DirectInput������
//5)DirectPlay������
//6)DirectShow����ý��

//DirectDraw��ĿǰΪֹ��չ��7.0�����ǰ�װ��DirectSDK
//��9.0��ע��DirectDraw���ĵ�����DirectSDK7.0�������е�


DEFINE_GUID( IID_IDirectDraw7,                  0x15e65ec0,0x3b9c,0x11d2,0xb9,0x2f,0x00,0x60,0x97,0x97,0xea,0x5b );