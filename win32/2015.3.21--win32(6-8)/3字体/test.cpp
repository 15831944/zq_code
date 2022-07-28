#include <windows.h>
#include "resource.h"
#include <string>
HWND dlg;

RECT g_rect = {100,100,400,400};
POINT start;
bool g_bButtonDown = false;

COLORREF c = RGB(0,0,0);
LOGFONT lf;

std::string s;

INT_PTR CALLBACK DialogProc(HWND hwnd,//������Ϣ�Ĵ���
							UINT uMsg,//��Ϣ����
							WPARAM wParam,//��Ϣ���Ӳ���1
							LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		{
			return 1;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == BN_CLICKED)
			{
				switch(LOWORD(wParam))
				{
				case IDC_BUTTON1:
					{
						COLORREF custColor[16] = {};
						CHOOSECOLOR cc = {};
						cc.lStructSize = sizeof(cc);
						cc.hwndOwner = hwnd;
						cc.lpCustColors = custColor;
						if(IDOK == ChooseColor(&cc))
						{
							c = cc.rgbResult;
							InvalidateRect(GetParent(hwnd),0,TRUE);
						}
						break;
					}
				case IDC_BUTTON2:
					{
						CHOOSEFONT cf = {};
						cf.lStructSize = sizeof(cf);
						cf.hwndOwner = hwnd;
						cf.lpLogFont = &lf;
						cf.Flags = CF_SCREENFONTS;

						if(IDOK == ChooseFont(&cf))
						{
							InvalidateRect(GetParent(hwnd),0,TRUE);
						}
						break;
					}
				case IDCANCEL:
					{
						ShowWindow(dlg,SW_HIDE);
						break;
					}
				}
			}
			else if(HIWORD(wParam) == EN_CHANGE)
			{
				char buf[1024];
				HWND edit = GetDlgItem(hwnd,IDC_EDIT1);
				GetWindowTextA(edit,buf,1024);
				s = buf;
				InvalidateRect(GetParent(hwnd),0,TRUE);
			}
			return 1;
		}
	}
	return 0;
}


//������Ϣ��������������������ϵͳ����
__w64 long __stdcall WindowProc(HWND hwnd,//������Ϣ�Ĵ���
								unsigned int uMsg,//��Ϣ����
								__w64 unsigned int wParam,//��Ϣ���Ӳ���1
								__w64 long lParam)//��Ϣ���Ӳ���2
{
	switch(uMsg)
	{
	case WM_CREATE:
		{
			HDC hdc = GetDC(hwnd);

			HFONT f = (HFONT)GetCurrentObject(hdc,OBJ_FONT);

			GetObject(f,sizeof(lf),&lf);

			ReleaseDC(hwnd,hdc);
			return 0;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			start.x = LOWORD(lParam);
			start.y = HIWORD(lParam);
			g_bButtonDown = true;
			return 0;
		}
	case WM_LBUTTONUP:
		{
			g_bButtonDown = false;
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			ShowWindow(dlg,SW_SHOW);
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			if(g_bButtonDown && start.x != LOWORD(lParam) && start.y != HIWORD(lParam))
			{
				g_rect.left = start.x < LOWORD(lParam) ? start.x : LOWORD(lParam);
				g_rect.top = start.y < HIWORD(lParam) ? start.y : HIWORD(lParam);

				g_rect.right = start.x > LOWORD(lParam) ? start.x : LOWORD(lParam);
				g_rect.bottom = start.y > HIWORD(lParam) ? start.y : HIWORD(lParam);

				InvalidateRect(hwnd,0,TRUE);
			}
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			Rectangle(hdc,g_rect.left,g_rect.top,g_rect.right,g_rect.bottom);

			HFONT f1 = CreateFontIndirect(&lf);

			HFONT f2 = (HFONT)SelectObject(hdc,f1);

			SetTextColor(hdc,c);

			DrawTextA(hdc,s.c_str(),s.length(),&g_rect,DT_WORDBREAK);

			SelectObject(hdc,f2);

			DeleteObject(f1);


			EndPaint(hwnd,&ps);
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
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "�˰�";
	RegisterClass(&wc);
	HWND hWnd = CreateWindow(wc.lpszClassName,
							 "����",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	dlg = CreateDialog(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),hWnd,DialogProc);


	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		//���������WM_KEYDOWN��WM_KEYUP��Ϣ�͸��ݵ�ǰ�����뷨
		//�ڲ���һ��WM_CHAR��Ϣ��Ͷ�ݵ���Ϣ������
		TranslateMessage(&msg);
		//�ɷ���Ϣ�ز���ϵͳ(���ƾ�������DispatchMessage�����ô�����Ϣ����)
		DispatchMessage(&msg);
	}

	return 1;
}