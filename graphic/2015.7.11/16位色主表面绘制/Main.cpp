#include <iostream>
#include "Main.h"
#include "Game.h"

#define _SLEEP_TIME 33

BOOL g_Active = TRUE;
HWND g_hWnd = 0;
int g_ScreenW = 0;
int g_ScreenH = 0;

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
	g_ScreenW = GetSystemMetrics(SM_CXSCREEN);
	g_ScreenH = GetSystemMetrics(SM_CYSCREEN);
	RECT r = {(g_ScreenW - _CLIENT_W) / 2, (g_ScreenH - _CLIENT_H) / 2, r.left + _CLIENT_W, r.top + _CLIENT_H};
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