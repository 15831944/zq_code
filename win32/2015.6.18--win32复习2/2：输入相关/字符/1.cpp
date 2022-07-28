#include <windows.h>

#define _CLIENT_W 640
#define _CLIENT_H 480

char str[1024] = {};
int len = 0;
bool db = false; //˫�ֽ����ֱ�־
char head; //˫�ֽ��������ֽ�

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
	case WM_CHAR:
		{
			//�����Ϣ��ͨ��WM_KEYDOWN��WM_KEYUP��
			//TranslateMessage�������ʹ�õ����뷨
			//�õ���һ���ַ���Ϣ���������ַ��ǵ�
			//�ֽ����֣���ô����Ϣ��ֻ�ᴥ��һ�Σ�
			//����wParam�����������ַ�����������
			//ֵ������ַ���˫�ֽ����֣���ô����Ϣ
			//�ͱ��������Σ��������ε�wParam�зֱ�
			//�����ֵ����ֽں�β�ֽ�

			//Windows�������Ե�C���ԣ�������C++
			//���ԣ�C������û��bool���ͣ�����΢��
			//Ϊ�˷�������жϣ���int��ʾBOOL����
			//0��1��ʾTRUE��FALSE���������������
			//�ж�һ���ֽ��Ƿ���һ��˫�ֽ����ֵ�
			//���ֽڣ�����Ǿͷ���TRUE��֮����FALSE
			//BOOL IsDBCSLeadByte(BYTE TestChar);

			//��ʱ��������Ҫ��ϸ�ж�һ��������
			//���ֽ����ֻ���˫�ֽ����֣���Ϊ��
			//�ֽڵ���������Щ���ǿ��Դ�ӡ����
			//�����֣�����س����˸���Щ����
			//��Ҫ���⴦����˫�ֽ�������һ��
			//���Դ�ӡ������

			//str[len++] = (char)wParam;
			//SetWindowTextA(hwnd, str);

			//��ʱӦ�ý���˫�ֽ����ֵ�β�ֽ�
			if (db)
			{
				char tail = (char)wParam;
				//��ʱ�Ѿ��õ���head��tail������β�ֽ�
				str[len++] = head;
				str[len++] = tail;
				db = false;
				SetWindowTextA(hwnd, str);
				return 0;
			}

			//��������˫�ֽ����ֵ����ֽ�
			if (IsDBCSLeadByte((BYTE)wParam))
			{
				head = (char)wParam;
				db = true;
			}
			//�������ǵ��ֽ�����
			else
			{
				//�˸��
				if (8 == wParam)
				{
					if (len > 0)
					{
						bool last_db; //��־���һ�������Ƿ���˫�ֽ�
						for (int i = 0; i < len; ++i)
						{
							if (IsDBCSLeadByte(str[i]))
							{
								last_db = true;
								i += 1;
							}
							else
								last_db = false;
						}
						str[len -= (last_db ? 2 : 1)] = 0;
						SetWindowTextA(hwnd, str);
					}
				}
				else
				{
					//�����������ж�һ�����ֽ���
					//���ǲ��ǿɴ�ӡ����
					if (isprint((int)wParam))
					{
						str[len++] = (char)wParam;
						SetWindowTextA(hwnd, str);
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