#include <windows.h>
#include "resource.h"
#include <list>
//1 ����
//2 ��Բ
//3 ����
//4 ��ˢ

//��¼�Ƿ��Ǿ��Σ���Ϊ���Σ���Ϊ��Բ
bool g_bJx = true;

//���ʻ�ˢ����ɫ
COLORREF g_pen = RGB(0,0,0);
COLORREF g_b = RGB(255,255,255);

//��¼��ʼ��
POINT g_start;

struct TX
{
	RECT r;
	bool jx;
	COLORREF p;
	COLORREF b;
};

std::list<TX>  g_tx;

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
	case WM_LBUTTONDOWN:
		{
			g_start.x = LOWORD(lParam);
			g_start.y = HIWORD(lParam);
			return 0;
		}
	case WM_LBUTTONUP:
		{
			if(g_start.x != LOWORD(lParam)
			&& g_start.y != HIWORD(lParam))
			{
				TX t;
				t.r.left = g_start.x < LOWORD(lParam) ? g_start.x: LOWORD(lParam);
				t.r.top = g_start.y < HIWORD(lParam) ? g_start.y : HIWORD(lParam);
				
				t.r.right = g_start.x < LOWORD(lParam) ? LOWORD(lParam) : g_start.x;
				t.r.bottom = g_start.y < HIWORD(lParam) ? HIWORD(lParam): g_start.y;
				
				t.jx = g_bJx;

				t.p = g_pen;

				t.b = g_b;

				g_tx.push_back(t);

				InvalidateRect(hwnd,0,TRUE);
			}
			return 0;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case ID_40001:g_bJx = true;break;
			case ID_40002:g_bJx = false;break;
			case ID_40003:
			case ID_40004:
				{
					COLORREF custColor[16] = {};
					CHOOSECOLOR cc = {};
					cc.lStructSize = sizeof(cc);
					cc.hwndOwner = hwnd;
					cc.lpCustColors = custColor;

					if(IDOK == ChooseColor(&cc))
					{
						if(LOWORD(wParam) == ID_40003)
							g_pen = cc.rgbResult;
						else
							g_b = cc.rgbResult;
					}
				}
				break;
			}
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			std::list<TX>::iterator i;
			for(i = g_tx.begin(); i != g_tx.end(); ++i)
			{
				HPEN p1 = CreatePen(PS_SOLID,1,i->p);
				HBRUSH b1 = CreateSolidBrush(i->b);

				HPEN p2 = (HPEN)SelectObject(hdc,p1);
				HBRUSH b2 = (HBRUSH)SelectObject(hdc,b1);

				if(i->jx)
					Rectangle(hdc,i->r.left,i->r.top,i->r.right,i->r.bottom);
				else
					Ellipse(hdc,i->r.left,i->r.top,i->r.right,i->r.bottom);

				SelectObject(hdc,p2);
				SelectObject(hdc,b2);
				DeleteObject(p1);
				DeleteObject(b1);
			}

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
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = "�˰�";
	RegisterClass(&wc);
	HWND hWnd = CreateWindow(wc.lpszClassName,
							 "���ʻ�ˢ������Բ",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

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