#include <windows.h>
#include <iostream>

#define _CLIENT_W 640
#define _CLIENT_H 480

int x, y;
bool b = true;
 
LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg, //��Ϣֵ
							WPARAM wParam, //��Ϣ�ĸ��Ӳ���1
							LPARAM lParam) //��Ϣ�ĸ��Ӳ���2
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			//����
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC dc = BeginPaint(hwnd, &ps);

			//���
			Ellipse(dc, x - 20, y - 20, x + 20, y + 20);

			EndPaint(hwnd, &ps);
			return 0;
		}
	case WM_TIMER:
		{
			//�߼�
			if (b)
			{
				x += 5;
				if (x > _CLIENT_W)
					b = false;
			}
			else
			{
				x -= 5;
				if (x < 0)
					b = true;
			}

			InvalidateRect(hwnd, 0, TRUE);
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
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "123abc";

	RegisterClass(&wc);

	//���Ը��ݿͻ�����С�����㴰�ڴ�С
	int sw = GetSystemMetrics(SM_CXSCREEN); //�õ�����Ŀ�
	int sh = GetSystemMetrics(SM_CYSCREEN); //�õ�����ĸ�
	RECT cr //cr�õ��ͻ�����λ�á��ߴ�
		=
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		(sw - _CLIENT_W) / 2 + _CLIENT_W,
		(sh - _CLIENT_H) / 2 + _CLIENT_H
	};
	//���ݴ���Ŀͻ���λ�á��ߴ������㴰��Ӧ���е�λ�á��ߴ�
	AdjustWindowRect(
		&cr, //�ͻ������Σ�������ִ�����֮������봰�ھ���
		WS_OVERLAPPEDWINDOW, //���ڷ��
		FALSE); //���޲˵�

	HWND hwnd = CreateWindowA(
		wc.lpszClassName, //ʹ�õĴ������ṹ�������
		"hello world", //���ڱ���������
		WS_OVERLAPPEDWINDOW, //���ڷ��
		cr.left, //�������Ͻ�x����
		cr.top, //�������Ͻ�y����
		cr.right - cr.left, //���ڿ�
		cr.bottom - cr.top, //���ڸ�
		HWND_DESKTOP, //�����ڣ�һ����˵��д���洰��
		0, //�˵���������þ���д0
		wc.hInstance, //Ӧ�ó���ʵ�����
		0); //��������

	//���Եõ��ͻ����ĳߴ�
	RECT r; //���νṹ�壺���Ͻǣ�left��top�������½ǣ�right��bottom��
	GetClientRect(hwnd, &r);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	SetTimer(hwnd, 0, 33, 0); //30֡/��

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	KillTimer(hwnd, 0);

	return 1;
}