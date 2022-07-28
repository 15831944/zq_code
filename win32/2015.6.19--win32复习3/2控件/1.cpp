#include <windows.h>
#include <iostream>

#define _CLIENT_W 640
#define _CLIENT_H 480

HWND g_hwnd[4];

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
			//���֣�����ǿؼ���ô���ǿؼ��¼�������ǿ�ݼ���ô����1������ǲ˵���ô����0
			//���֣��ؼ�����ݼ����˵���ID
			//lParam
			//����ǿؼ���ô���ǿؼ��Ĵ��ھ��������ǿ�ݼ����˵���ô����0

			//����ı��ʽΪ�����ζ���а�ť��������
			if (HIWORD(wParam) == BN_CLICKED)
			{
				switch (LOWORD(wParam))
				{
				case 100:
					MessageBoxA(hwnd, "��ť1������", 0, 0);
					break;
				case 101:
					MessageBoxA(hwnd, "��ť2������", 0, 0);
					break;
				case 102:
					{
						static bool b = true;
						b = !b;

						if (!b)
						{
							//��ʾ�����ش���
							ShowWindow(g_hwnd[1], SW_HIDE);

							//��������򼤻����봰��
							EnableWindow(g_hwnd[2], FALSE);
						}
						else
						{
							//��ʾ�����ش���
							ShowWindow(g_hwnd[1], SW_SHOW);

							//��������򼤻����봰��
							EnableWindow(g_hwnd[2], TRUE);
						}

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
		FALSE); //���޲˵�

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

	//���Ǵ����ؼ����ڣ�����������Ϊ�Ӵ��ڣ������Ǵ�
	//�����ڣ�����Ǵ������ڸ����޷���ӦWM_COMMAND��
	//Ϣ��Windows�������Щ�ؼ��ı��ʶ��Ǵ��ڣ�����
	//��Щ�ؼ���ʵ���Ǵ����Ӵ��ڣ�ֻ����������Ĵ���
	//���ṹ�������������ڴ�����ʱ��Ҫ��дʲô�ַ�
	//��������ͨ����MSDN��ͨ��CreateWindow���鿴��ע
	//�����еĿؼ����涼�ᷢ��һЩ���飬��Щ��������
	//���û��Կؼ�����������������ģ����ǿ�������Щ
	//�ؼ��ĸ����ڵ�WM_COMMAND��Ϣ������Ӧ��Щ�¼���
	//�����ڰ�ť����õ��¼�����BN_CLICKED�����ʾ
	//��ť���淢���˵���¼�

	//������ť
	g_hwnd[1] = CreateWindowA(
		"button", //������ť������"button"
		"��ť1", //���ڱ���������
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, //���ڷ��|��ť���
		0, //�������Ͻ�x����
		0, //�������Ͻ�y����
		100, //���ڿ�
		60, //���ڸ�
		g_hwnd[0], //�����ڣ�һ����˵��д���洰��
		(HMENU)100, //������Ӵ�����˴���дһ��������ʾ��ID�ţ��Ӵ����ǲ����в˵���
		wc.hInstance, //Ӧ�ó���ʵ�����
		0); //��������

	g_hwnd[2] = CreateWindowA(
		"button", //������ť������"button"
		"��ť2", //���ڱ���������
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, //���ڷ��|��ť���
		0, //�������Ͻ�x����
		80, //�������Ͻ�y����
		100, //���ڿ�
		60, //���ڸ�
		g_hwnd[0], //�����ڣ�һ����˵��д���洰��
		(HMENU)101,
		wc.hInstance, //Ӧ�ó���ʵ�����
		0); //��������

	g_hwnd[3] = CreateWindowA(
		"button", //������ť������"button"
		"��ť3", //���ڱ���������
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, //���ڷ��|��ť���
		0, //�������Ͻ�x����
		160, //�������Ͻ�y����
		100, //���ڿ�
		60, //���ڸ�
		g_hwnd[0], //�����ڣ�һ����˵��д���洰��
		(HMENU)102,
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