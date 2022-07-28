#include <windows.h>
#include <iostream>

#pragma comment(lib, "Msimg32.lib") //��������Msimg32.lib�⣬��ΪTransparentBlt�Ķ������������

#define _CLIENT_W 800
#define _CLIENT_H 600

//������ڴ��д���λͼ
//HBITMAP CreateDIBitmap(
//						HDC hdc,
//					   CONST BITMAPINFOHEADER *lpbmih,
//					   DWORD fdwInit,
//					   CONST VOID *lpbInit,
//					   CONST BITMAPINFO *lpbmi,
//					   UINT fuUsage);

char fd[1440054];
HBITMAP hbmp;
HDC bmpdc;

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
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC dc = BeginPaint(hwnd, &ps); //���豸

			BitBlt(dc, 0, 0, 800, 600, bmpdc, 0, 0, SRCCOPY);

			EndPaint(hwnd, &ps);
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

	//��ȡλͼ�ļ����ڴ���
	//���ļ�ͷ��14
	//����Ϣͷ��40
	//����ɫ���ݡ�??
	FILE* pf = 0;
	fopen_s(&pf, "abc", "rb");
	fread(fd, 1, 1440054, pf);
	fclose(pf);

	//���ԭ
	for (int i = 0; i < 1440054; ++i)
	{
		fd[i] = fd[i] ^ 0xa7;
	}

	BITMAPINFOHEADER* pbih = (BITMAPINFOHEADER*)(fd + 14);

	HDC dc = GetDC(hwnd);

	hbmp = CreateDIBitmap(
		dc,
		pbih,
		CBM_INIT,
		fd + 54,
		(BITMAPINFO*)(pbih),
		DIB_RGB_COLORS);

	bmpdc = CreateCompatibleDC(dc);

	DeleteObject(SelectObject(bmpdc, hbmp));

	ReleaseDC(hwnd, dc);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DeleteDC(bmpdc);

	return 1;
}