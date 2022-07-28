#include <windows.h>
#include "resource.h"

#define _CLIENT_W 640
#define _CLIENT_H 480

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
	case WM_COMMAND:
		{
			//wParam

			//HIWORD����
			//1������������������һ���ؼ�����ô������־�������ؼ����¼���Ϣ����һ����������ʾ����ؼ����淢�����¼���������һ����ť����������ط�����BN_CLICKED
			//2������������������һ����ݼ�����ô�������Ϊ1
			//3������������������һ���˵�����ô�������Ϊ0

			//LOWORD����
			//����������Ŀؼ�����ݼ����˵����ID�ţ���resource.h�У�

			//lParam
			//����������������һ���ؼ��������������������ؼ��Ĵ��ھ��
			//����������������һ����ݼ���һ���˵�����ô�������Ϊ0

			if (HIWORD(wParam) == 0)
			{
				switch (LOWORD(wParam))
				{
				case ID_40001:
					{
						MessageBoxA(hwnd, "������ABC", 0, 0);
						break;
					}
				case ID_40002:
					{
						PostQuitMessage(0);
						break;
					}
				case ID_40003:
					{
						MessageBoxA(hwnd, "������123", 0, 0);
						break;
					}
				}
			}

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
		TRUE); //�в˵�

	HWND hwnd = CreateWindowA(
		wc.lpszClassName, //ʹ�õĴ������ṹ�������
		"hello world", //���ڱ���������
		WS_OVERLAPPEDWINDOW, //���ڷ��
		cr.left, //�������Ͻ�x����
		cr.top, //�������Ͻ�y����
		cr.right - cr.left, //���ڿ�
		cr.bottom - cr.top, //���ڸ�
		HWND_DESKTOP, //�����ڣ�һ����˵��д���洰��

		//�ڴ˴����ز˵�Ҳ����
		LoadMenu(hInstance, MAKEINTRESOURCE(101)), 

		wc.hInstance, //Ӧ�ó���ʵ�����
		0); //��������

	//���Եõ��ͻ����ĳߴ�
	RECT r; //���νṹ�壺���Ͻǣ�left��top�������½ǣ�right��bottom��
	GetClientRect(hwnd, &r);

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