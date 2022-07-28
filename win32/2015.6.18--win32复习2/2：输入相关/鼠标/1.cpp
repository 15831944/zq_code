#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <iostream>

//#define _WIN32_WINNT 0x0400
//#ifndef _WIN32_WINNT
//#define _WIN32_WINNT 0x0300
//#endif

#define _CLIENT_W 640
#define _CLIENT_H 480

//WM_LBUTTONDOWN�����������£���WM_LBUTTONUP��������̧�𣩡�WM_LBUTTONDBLCLK��������˫����
//WM_MBUTTONDOWN������м����£���WM_MBUTTONUP������м�̧�𣩡�WM_MBUTTONDBLCLK������м�˫����
//WM_RBUTTONDOWN������Ҽ����£���WM_RBUTTONUP������Ҽ�̧�𣩡�WM_RBUTTONDBLCLK������Ҽ�˫����
//WM_MOUSEWHEEL�������ֹ�����Ϣ��
//WM_MOUSEMOVE������ڿͻ����ƶ���Ϣ��
//ֻҪ����������Ϣ����ôlParam�����ж����й�����������

//MessageBox
//OutputDebugString
//SetWindowText

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
			//�������ڱ����ڵĿͻ������µ�ʱ�򴥷�����Ϣ

			//����Ϣ�У��������ڱ����ڿͻ��������Ͻ�
			//�����λ���Ƿ�����lParam�����еģ��ŵķ�
			//����XX XX YY YY����LOWORD��HIWORD�����
			//�õ�һ��4�ֽ������е�ǰ�����ֽںͺ�����
			//�ֽڵ�����
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			char buf[64];
			sprintf_s(buf, 64, "[%d,%d]", x, y);
			MessageBox(hwnd, buf, "����λ��", MB_OK);

			return 0;
		}

	case WM_RBUTTONUP:
		{
			//����Ҽ��ڱ����ڵĿͻ���̧���ʱ�򴥷�����Ϣ

			//����Ϣ�У�lParamҲ�Ǵ洢�Ĺ�굱ǰ��λ��
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			char buf[64];
			sprintf_s(buf, 64, "[%d,%d]", x, y);
			MessageBox(hwnd, buf, "̧��λ��", MB_OK);

			return 0;
		}

		//���Ҫϣ�������ڿ��Խ���˫����Ϣ����ô������
		//�ڴ������ṹ��ķ���м���CS_DBLCLKS�����
		//����ʾ����˫��
	case WM_RBUTTONDBLCLK:
		{
			Beep(500, 200);
			return 0;
		}
	case WM_MOUSEWHEEL:
		{
			//ע�Ȿ��Ϣ��Ҫ_WIN32_WINNT���İ�
			//����Ҫ���ڵ���0x0400�����ǿ����ڰ�
			//��Windows.h֮ǰ���������
			//��ǰ���������������ͨ������Ĵ���
			//���жϣ����ֵ�Ƿ���wParam�ĸ��ֲ�
			//�֣�һ����WORD���������ֽڣ�һ��˫
			//��DWORD����������Ҳ���ĸ��ֽ�
			if (WHEEL_DELTA == HIWORD(wParam))
				OutputDebugStringA("��ǰ����\n");
			else if (-WHEEL_DELTA == (short)HIWORD(wParam))
				OutputDebugStringA("�������\n");

			return 0;
		}
	case WM_MOUSEMOVE:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			char buf[64];
			sprintf_s(buf, 64, "[%d,%d]", x, y);

			//����ָ�������б�����������
			SetWindowTextA(hwnd, buf);

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
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
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

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}