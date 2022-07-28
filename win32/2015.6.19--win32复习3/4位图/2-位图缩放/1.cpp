#include <windows.h>
#include <iostream>

#pragma comment(lib, "Msimg32.lib") //��������Msimg32.lib�⣬��ΪTransparentBlt�Ķ������������

#define _CLIENT_W 800
#define _CLIENT_H 600

//λͼ��ʹ��
//1��ͨ��LoadImage����λͼ
//2�����������豸������λͼѡ���豸��ע�Ᵽ����λͼ
//3��ͨ��BitBlt�Ȼ��Ǵ�ѡ������λͼ���豸�п�����ɫ���ݵ����豸��BeginPaint��GetDC�õ����豸��
//4������ʹ��λͼ�ˣ���ôλͼ�豸��λͼ��Ҫ�ͷ�

HBITMAP hbmp[2];
HDC bmpdc[2];

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

			//�������ŵ�ģʽ
			SetStretchBltMode(dc, HALFTONE);

			//�����Ź��ܵĻ���
			StretchBlt(
				dc, //Ŀ���豸
				0, 0, 400, 300, //Ŀ�����
				bmpdc[0], //Դ�豸
				0, 0, 1600, 1200, //Դ����
				SRCCOPY);

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

	//����λͼ
	hbmp[0] = (HBITMAP)LoadImageA(
		0, //Ӧ�ó���ʵ�����
		"bliss.bmp", //·��
		IMAGE_BITMAP, //����
		0, //���ؿ�Ϊ0��ʾ����λͼ���������
		0, //���ظߣ�Ϊ0��ʾ����λͼ�������߶�
		LR_LOADFROMFILE); //LR_LOADFROMFILE��ʾ���ⲿ�ļ�����

	//�õ����豸
	HDC main_dc = GetDC(hwnd);

	//ͨ�����豸���������豸
	bmpdc[0] = CreateCompatibleDC(main_dc);

	//�ͷ����豸
	ReleaseDC(hwnd, main_dc);

	//��λͼѡ�뵽�����豸��
	HBITMAP old_bmp0 = (HBITMAP)SelectObject(bmpdc[0], hbmp[0]);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//ж����λͼ
	DeleteObject(old_bmp0);

	//�ͷ��豸��������λͼ��
	DeleteDC(bmpdc[0]);

	return 1;
}