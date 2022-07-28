#include <windows.h>
#include <iostream>

//����֮���������νṹ����֯������ÿ�����ڶ���һ��
//�����ڣ�Ҳ�������Ӵ��ڣ����ߴ������ڣ������Ӵ���
//���������𣩣�һ��Ĵ��ڶ��������洰��Ϊ�����ڵ�

#define _CLIENT_W 640
#define _CLIENT_H 480

HWND g_hwnd[4]; //���д���

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
	case WM_CLOSE:
		{
			//����������ڷ�����WM_CLOSE��Ϣ����ô
			//����DefWindowProc�����������Ϣ������
			//��WM_DESTROY������
			if (hwnd == g_hwnd[0] || hwnd == g_hwnd[3])
				break;

			//���������������ôʲô������
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

	//������
	g_hwnd[0] = CreateWindowA(
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

	//�Ӵ��ڣ�Ҫ��дWS_CHILD��
	//1���ᱻ�����ڲü������ǳ��������ڵı߽�Ĳ��ֲ�������
	//2�����游�����ƶ�
	//3����������ڱ����٣���ô�Ӵ���һ�������ڸ����ڱ�����
	g_hwnd[1] = CreateWindowA(
		wc.lpszClassName, //ʹ�õĴ������ṹ�������
		"�Ӵ���", //���ڱ���������
		WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE, //���ڷ�������WS_CHILD���Ӵ��ڣ���WS_VISIBLE���ɼ���
		0, //�������Ͻ�x����
		0, //�������Ͻ�y����
		300, //���ڿ�
		200, //���ڸ�
		g_hwnd[0], //������
		0, //�˵���������þ���д0
		wc.hInstance, //Ӧ�ó���ʵ�����
		0); //��������

	//�������ڣ���Ҫ��дWS_CHILD��
	//1�����ᱻ�����ڲü�
	//2�������游�����ƶ�
	//3����������ڱ����٣���ô�Ӵ���һ�������ڸ����ڱ�����
	g_hwnd[2] = CreateWindowA(
		wc.lpszClassName, //ʹ�õĴ������ṹ�������
		"��������", //���ڱ���������
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, //���ڷ�������WS_VISIBLE���ɼ���
		200, //�������Ͻ�x����
		300, //�������Ͻ�y����
		100, //���ڿ�
		150, //���ڸ�
		g_hwnd[0], //������
		0, //�˵���������þ���д0
		wc.hInstance, //Ӧ�ó���ʵ�����
		0); //��������

	g_hwnd[3] = CreateWindowA(
		wc.lpszClassName, //ʹ�õĴ������ṹ�������
		"�Ӵ��ڵ��Ӵ���", //���ڱ���������
		WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE, //���ڷ�������WS_VISIBLE���ɼ���
		0, //�������Ͻ�x����
		0, //�������Ͻ�y����
		100, //���ڿ�
		150, //���ڸ�
		g_hwnd[1], //������
		0, //�˵���������þ���д0
		wc.hInstance, //Ӧ�ó���ʵ�����
		0); //��������

	ShowWindow(g_hwnd[0], nCmdShow);
	UpdateWindow(g_hwnd[0]);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}