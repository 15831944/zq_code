#include <windows.h>
#include <time.h>
#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

BOOL g_Act = TRUE;//���ڼ����־

HDC g_MainDC;
HDC g_BackDC;
HWND g_hWnd[5];
COLORREF c[3];
float ams, cms; //�ܳ���ʱ�䡢��ǰʱ��

COLORREF slerp_color(COLORREF c0, COLORREF c1, float a, float c)
{
	float bl = c / a;
	int cc0[] = {GetRValue(c0), GetGValue(c0), GetBValue(c0)};
	int cc1[] = {GetRValue(c1), GetGValue(c1), GetBValue(c1)};
	int cc2[]
	=
	{
		(cc1[0] - cc0[0]) * bl + cc0[0],
		(cc1[1] - cc0[1]) * bl + cc0[1],
		(cc1[2] - cc0[2]) * bl + cc0[2],
	};
	return RGB(cc2[0], cc2[1], cc2[2]);
}

//������Ϣ��������������������ϵͳ����
__w64 long __stdcall WindowProc(HWND hwnd,//������Ϣ�Ĵ���
								unsigned int uMsg,//��Ϣ����
								__w64 unsigned int wParam,//��Ϣ���Ӳ���1
								__w64 long lParam)//��Ϣ���Ӳ���2
{
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case 1:
				{
					COLORREF cust_c[16] = {};
					CHOOSECOLOR cc = {};
					cc.lStructSize = sizeof(cc);
					cc.lpCustColors = cust_c;
					if (IDOK == ChooseColor(&cc))
					{
						c[0] = cc.rgbResult;
						InvalidateRect(g_hWnd[0], 0, TRUE);
					}
					break;
				}
			case 2:
				{
					COLORREF cust_c[16] = {};
					CHOOSECOLOR cc = {};
					cc.lStructSize = sizeof(cc);
					cc.lpCustColors = cust_c;
					if (IDOK == ChooseColor(&cc))
					{
						c[1] = cc.rgbResult;
						InvalidateRect(g_hWnd[0], 0, TRUE);
					}
					break;
				}
			case 3:
				{
					//ȡ��Դ��ɫ��Ŀ����ɫ
					if (c[0] == c[1])
					{
						MessageBoxA(g_hWnd[0], "Դ��ɫ��Ŀ����ɫ��ͬ���ܲ�ֵ", "��ʾ", MB_OK);
						break;
					}

					//ȡ�ñ仯ʱ��
					char buf[32] = {};
					GetDlgItemTextA(g_hWnd[0], 4, buf, 32);
					ams = atoi(buf) * 1000;
					if (ams == 0)
					{
						MessageBoxA(g_hWnd[0], "ʱ��Ϊ0���ܲ�ֵ", "��ʾ", MB_OK);
						break;
					}
					cms = 0;

					//������ɫ��ֵ
					SetTimer(g_hWnd[0], 0, 10, 0);

					for (int i = 1; i <= 4; ++i)
						EnableWindow(g_hWnd[i], FALSE);

					break;
				}
			}

			return 0;
		}
	case WM_TIMER:
		{
			//��ֵ1
			//c[2] = (c[1] - c[0]) * (cms / ams) + c[0];

			//��ֵ1
			//float bl = cms / ams;
			//int c0[] = {GetRValue(c[0]), GetGValue(c[0]), GetBValue(c[0])};
			//int c1[] = {GetRValue(c[1]), GetGValue(c[1]), GetBValue(c[1])};
			//int c2[]
			//=
			//{
			//	(c1[0] - c0[0]) * bl + c0[0],
			//	(c1[1] - c0[1]) * bl + c0[1],
			//	(c1[2] - c0[2]) * bl + c0[2],
			//};
			//c[2] = RGB(c2[0], c2[1], c2[2]);

			c[2] = slerp_color(c[0], c[1], ams, cms);

			cms += 10;
			if (cms > ams)
			{
				KillTimer(g_hWnd[0], 0);
				for (int i = 1; i <= 4; ++i)
					EnableWindow(g_hWnd[i], TRUE);
			}

			InvalidateRect(g_hWnd[0], 0, TRUE);

			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC dc = BeginPaint(g_hWnd[0], &ps);

			HBRUSH b[3];
			for (int i = 0; i < 3; ++i)
				b[i] = CreateSolidBrush(c[i]);

			HBRUSH old_b = (HBRUSH)SelectObject(dc, b[0]);
			Rectangle(dc, 120, 80, 220, 240);

			SelectObject(dc, b[1]);
			Rectangle(dc, 240, 80, 340, 240);

			SelectObject(dc, b[2]);
			Rectangle(dc, 360, 80, 460, 240);

			SelectObject(dc, old_b);

			for (int i = 0; i < 3; ++i)
				DeleteObject(b[i]);

			EndPaint(g_hWnd[0], &ps);
			return 0;
		}
	}
	//���ǲ����ĵ���Ϣ�͵���DefWindowProc(windows��������Ϣ��Ĭ�ϴ�����)���������Ǵ���
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,//Ӧ�ó���ʵ�����
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	//01)���һ���������Ľṹ��
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "3dtest";
	RegisterClass(&wc);

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	RECT r = 
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		(sw - _CLIENT_W) / 2 + _CLIENT_W,
		(sh - _CLIENT_H) / 2 + _CLIENT_H
	};
	int ws = (WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME) & ~WS_MAXIMIZEBOX;
	AdjustWindowRect(&r, ws, FALSE);

	g_hWnd[0] = CreateWindow(
		wc.lpszClassName,
		"��ɫ��ֵ",//���ڱ���������
		ws,//���ڷ��
		r.left,//���ڵ����Ͻ�x����
		r.top,//���ڵ����Ͻ�y����
		r.right - r.left,//���ڵĿ����أ�
		r.bottom - r.top,//���ڵĸߣ����أ�
		HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
		0,//���ڲ˵��������ʹ�ò˵���0
		wc.hInstance,//Ӧ�ó���ʵ�����
		0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	const char* str[] = {"Դ��ɫ", "Ŀ����ɫ", "����"};
	for (int i = 1; i <= 3; ++i)
	{
		g_hWnd[i] = CreateWindow(
			"button",
			str[i - 1],//���ڱ���������
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,//���ڷ��
			i * 120,//���ڵ����Ͻ�x����
			0,//���ڵ����Ͻ�y����
			100,//���ڵĿ����أ�
			60,//���ڵĸߣ����أ�
			g_hWnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
			(HMENU)i,//���ڲ˵��������ʹ�ò˵���0
			wc.hInstance,//Ӧ�ó���ʵ�����
			0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0
	}
	g_hWnd[4] = CreateWindow(
		"edit",
		"����ʱ��",//���ڱ���������
		WS_CHILD | WS_VISIBLE | WS_BORDER,//���ڷ��
		0,//���ڵ����Ͻ�x����
		0,//���ڵ����Ͻ�y����
		80,//���ڵĿ����أ�
		20,//���ڵĸߣ����أ�
		g_hWnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
		(HMENU)4,//���ڲ˵��������ʹ�ò˵���0
		wc.hInstance,//Ӧ�ó���ʵ�����
		0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	ShowWindow(g_hWnd[0], nCmdShow);
	UpdateWindow(g_hWnd[0]);

	MSG msg = {};
	while(GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}