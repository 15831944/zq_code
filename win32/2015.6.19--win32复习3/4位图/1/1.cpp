#include <windows.h>
#include <iostream>

#pragma comment(lib, "Msimg32.lib") //��������Msimg32.lib�⣬��ΪTransparentBlt�Ķ������������

#define _CLIENT_W 640
#define _CLIENT_H 480

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

			//��Դ�豸������ɫ���ݵ�Ŀ���豸��
			BitBlt(
				dc, //Ŀ���豸
				100, //Ŀ��������Ͻ�x
				100, //Ŀ��������Ͻ�y
				240, //Ŀ����ο�
				130, //Ŀ����θ�
				bmpdc[1], //Դ�豸
				240, //Դ�豸���Ͻ�x
				130, //Դ�豸���Ͻ�y
				SRCCOPY); //ԭ�ⲻ���ؿ���
			BitBlt(
				dc,
				0,
				0,
				240,
				130,
				bmpdc[1],
				0,
				0,
				SRCCOPY);

			//���Թ���ĳ��ָ������ɫ�����������ڿⲻ�ᱻ�Զ�ȥ
			//���ӣ�ֻҪ��C++���̣���ôĬ�϶���ȥ����C��C++����
			//������ʱ�⣬�����ᱻ�Զ����ӵĿ������[��Ŀ][����]
			//[����][����]�н������ã������Ա����ֶ��������ӿ⣬
			//ע�Ȿ�����������Ź��ܣ�ͨ��ָ��Դ���κ�Ŀ�����
			//�Ϳ��Խ�������
			TransparentBlt(
				dc, //Ŀ���豸
				200, 200, 300, 200, //Ŀ�����
				bmpdc[0], //Դ�豸
				0, 0, 50, 50, //Դ����
				RGB(0, 255, 0)); //Ҫ���˵���ɫ

			TransparentBlt(
				dc, //Ŀ���豸
				300, 400, 50, 50, //Ŀ�����
				bmpdc[0], //Դ�豸
				0, 0, 100, 100, //Դ����
				RGB(255, 0, 0)); //Ҫ���˵���ɫ

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
		"bmp\\01.bmp", //·��
		IMAGE_BITMAP, //����
		0, //���ؿ�Ϊ0��ʾ����λͼ���������
		0, //���ظߣ�Ϊ0��ʾ����λͼ�������߶�
		LR_LOADFROMFILE); //LR_LOADFROMFILE��ʾ���ⲿ�ļ�����
	hbmp[1] = (HBITMAP)LoadImageA(0, "bmp\\02.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//�õ����豸
	HDC main_dc = GetDC(hwnd);

	//ͨ�����豸���������豸
	bmpdc[0] = CreateCompatibleDC(main_dc);
	bmpdc[1] = CreateCompatibleDC(main_dc);

	//�ͷ����豸
	ReleaseDC(hwnd, main_dc);

	//��λͼѡ�뵽�����豸��
	HBITMAP old_bmp0 = (HBITMAP)SelectObject(bmpdc[0], hbmp[0]);
	HBITMAP old_bmp1 = (HBITMAP)SelectObject(bmpdc[1], hbmp[1]);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//ж����λͼ
	DeleteObject(old_bmp1);
	DeleteObject(old_bmp0);

	//�ͷ��豸��������λͼ��
	DeleteDC(bmpdc[1]);
	DeleteDC(bmpdc[0]);

	return 1;
}