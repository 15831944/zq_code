#include <windows.h>
#include <iostream>

#define _CLIENT_W 640
#define _CLIENT_H 480

//R���죩G���̣�B������
//255 0 0:��׼��
//0 255 0:��׼��
//0 0 255:��׼��
//255 255 0:��׼��
//255 0 255:��׼��
//0 255 255:��׼����
//0 0 0:��
//255 255 255:��
//? ? ?:��

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
			HDC dc = BeginPaint(hwnd, &ps);

			//�߼�ģʽҪ�Կ�֧��
			SetGraphicsMode(dc, GM_ADVANCED);

			//����һ����ɫ����
			HPEN p1 = CreatePen(
				PS_SOLID, //���
				50, //���ؿ�������ؿ�ȴ���1����ô���ֻ����PS_SOLID
				RGB(255, 0, 0)); //��ɫ

			//p0�͵õ��ϵĻ���
			HPEN p0 = (HPEN)SelectObject(dc, p1);

			//����[p1]
			//��ˢ[b0]
			//����[f0]

			Rectangle(dc, 100, 100, 200, 300);
			
			HPEN p2 = CreatePen(
				PS_DOT, //���
				1, //���ؿ�������ؿ�ȴ���1����ô���ֻ����PS_SOLID
				RGB(0, 255, 0));

			SelectObject(dc, p2);

			//����[p2]
			//��ˢ[b0]
			//����[f0]

			Ellipse(dc, 200, 150, 300, 350);

			//����ʵ�Ļ�ˢ
			HBRUSH b1 = CreateSolidBrush(
				RGB(255, 255, 0)); //��ɫ

			HBRUSH b0 = (HBRUSH)SelectObject(dc, b1);

			//����[p2]
			//��ˢ[b1]
			//����[f0]

			Rectangle(dc, 250, 250, 400, 300);

			//�����з��ˢ
			HBRUSH b2 = CreateHatchBrush(
				HS_DIAGCROSS, //���
				RGB(255, 0, 255)); //��ɫ

			SelectObject(dc, b2);

			//����[p2]
			//��ˢ[b2]
			//����[f0]

			Ellipse(dc, 300, 300, 400, 450);

			HFONT f1 = CreateFontA(
				40, //��
				20, //��
				0, //�����׼��б��,��λΪ0.1��
				300, //����б��,��λΪ0.1�ȣ����뿪���߼���ͼģʽ
				400, //��ϸ0~800
				false, //�Ƿ�б��
				false, //�Ƿ��»���
				false, //�Ƿ�������
				DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_DONTCARE,
				"��Բ"); //�������

			HFONT f0 = (HFONT)SelectObject(dc, f1);

			//����[p2]
			//��ˢ[b2]
			//����[f1]

			//�������ɫ���ǻ��ʿ��ƣ����ǵ���һ������������
			SetTextColor(dc, RGB(0, 0, 255));

			//������������ı�����ʾ��ʽ��TRANSPARENT��ʾ����������ɫ
			SetBkMode(dc, TRANSPARENT);

			TextOutA(dc, 0, 0, "123abc���", 8);

			HFONT f2 = CreateFontA(
				40,
				20,
				450,
				0,
				800,
				true,
				false,
				false,
				DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_DONTCARE,
				"����");

			SelectObject(dc, f2);

			//����[p2]
			//��ˢ[b2]
			//����[f2]

			SetTextColor(dc, RGB(255, 255, 0));

			TextOutA(dc, 0, 300, "123abc���", 10);

			//�������dcһ���ͷŵ�GDI��������ֻ���Լ��ͷ�
			DeleteObject(p0);
			DeleteObject(p1);
			DeleteObject(b0);
			DeleteObject(b1);
			DeleteObject(f0);
			DeleteObject(f1);

			EndPaint(hwnd, &ps); //���ͷ�dc��p2��b2��f2
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
	wc.hbrBackground = (HBRUSH)COLOR_MENU;
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

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}