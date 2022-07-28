#include <windows.h>
#include <vector>
#include <time.h>
#include <iostream>

#define _BUTTON1 1
#define _BUTTON2 2
#define _BUTTON3 3
#define _BUTTON4 4
HWND g_hWnd[7];
RECT rButton1;
RECT rButton2;
RECT rButton3;
RECT rButton4;

struct _TX
{
	RECT r;
	bool jx;
};

std::vector<_TX> tx;

//������Ϣ��������������������ϵͳ����
__w64 long __stdcall WindowProc(HWND hwnd,//������Ϣ�Ĵ���
								unsigned int uMsg,//��Ϣ����
								__w64 unsigned int wParam,//��Ϣ���Ӳ���1
								__w64 long lParam)//��Ϣ���Ӳ���2
{
	switch(uMsg)
	{
	//������Ϣ������ʽ
	//1)���ϵͳ�˵��Ĺرղ˵��Alt + F4��
	//2)���Ͻǵ�X��ť
	case WM_DESTROY:
		{
			//Ͷ��һ��WM_QUIT��Ϣ�����̵߳���Ϣ������
			PostQuitMessage(0);
			//һ�����Ǵ�����ĳ����Ϣ��Ҫֱ�ӷ���0.
			return 0;
		}
	case WM_CLOSE:
		{
			if(g_hWnd[5] == hwnd ||g_hWnd[6] == hwnd )
				ShowWindow(hwnd,SW_HIDE);
			else
				DestroyWindow(hwnd);
			return 0;
		}
		//����ǿؼ���Ϣ
		//HIWORD(wParam)�Ǹÿؼ��Ϸ������¼���Ϣ
		//LOWORD(wParam)�Ǹÿؼ���ID��
		//lParam�Ǹÿؼ��Ĵ��ھ��
	case WM_COMMAND:
		{
			//���°�ť
			if(BN_CLICKED == HIWORD(wParam))
			{
				if(LOWORD(wParam) == _BUTTON3)
				{
					ShowWindow(g_hWnd[5],SW_SHOW);
					break;
				}
				if(LOWORD(wParam) == _BUTTON4)
				{
					ShowWindow(g_hWnd[6],SW_SHOW);
					break;
				}
				RECT r;
				GetClientRect(hwnd,&r);
				
				int w = r.right - r.left;
				int h = r.bottom - r.top;

				_TX t;
				t.r.left = rand() % w;
				t.r.top = rand() % h;
				t.r.right = t.r.left + rand() % (w - t.r.left);
				t.r.bottom = t.r.top + rand() % (h - t.r.top);

				if(LOWORD(wParam) == _BUTTON1)
				{
					t.jx = true;
				}
				else if(LOWORD(wParam) == _BUTTON2)
				{
					t.jx = false;
				}
				tx.push_back(t);

				SetFocus(g_hWnd[0]);

				InvalidateRect(hwnd,0,TRUE);
			}
			return 0;
		}
	case WM_KEYDOWN:
		{
			if(wParam == 'J')
				SendMessage(g_hWnd[1],BM_CLICK,0,0);
			if(wParam == 'Y')
				SendMessage(g_hWnd[2],BM_CLICK,0,0);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			for(std::vector <_TX>::iterator i = tx.begin(); i != tx.end(); ++i)
			{
				if(i->jx)
					Rectangle(hdc,i->r.left,i->r.top,i->r.right,i->r.bottom);
				else
					Ellipse(hdc,i->r.left,i->r.top,i->r.right,i->r.bottom);	
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
	srand((unsigned int)time(0));
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
	wc.lpszClassName = L"�˰�";
	RegisterClass(&wc);

	g_hWnd[0] = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 L"��ť-��",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	//WindowsԤ��������һЩ����Ĵ��ڣ�
	//��Щ���ڸ������û����н��������� button �༭���
	//��Щ���ڳ�Ϊ�ؼ���
	//ÿ��WindowsԤ�����úõĿؼ���WNDCLASS����Ӧ��һ���ַ�������
	//���簴ť����button
	//�ؼ���id����CreateWindow��HMENU�������ã��Ӵ����ǲ����в˵���
	//�����ò˵���ʾid�ţ���Ҫע��������ڿ������Լ��Ĳ˵�.
	//��ζ�Ŵ������ڵĴ�����ʱ��HMENU������дID�ţ���������һ�㲻�ô������ڵ��ؼ�
	//��ť���
	//BS_PUSHBUTTON����ѹʽ��ť
	//BS_RADIOBUTTON:��ѡ��
	//BS_CHECKBOX:��ѡ��

	//һ�㴦��ؼ�
	//1)���Ӵ��ڴ����ؼ�
	//2)WM_COMMAND����ؼ���Ϣ
	//3)ͨ��SendMessage���Ϳؼ�������Ϣ�����ƿؼ�

	//��ť���¼���Ϣ
	//BN_CLICKED:��ť�����
	//��ť�Ŀ�����Ϣ
	//BM_CLICK:ģ���û������ť

	g_hWnd[1] = CreateWindow(L"button",
							 L"����",//���ڱ���������
							 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,//���ڷ��
							 0,//���ڵ����Ͻ�x����
							 0,//���ڵ����Ͻ�y����
							 100,//���ڵĿ����أ�
							 30,//���ڵĸߣ����أ�
							 g_hWnd[0],
							 (HMENU)_BUTTON1,//ID
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);
	rButton1.left = 0;
	rButton1.top = 0;
	rButton1.right = 100;
	rButton1.bottom = 30;
	g_hWnd[2] = CreateWindow(L"BUTTON",
							 L"��Բ",//���ڱ���������
							 WS_CHILD | BS_PUSHBUTTON,//���ڷ��
							 0,//���ڵ����Ͻ�x����
							 40,//���ڵ����Ͻ�y����
							 100,//���ڵĿ����أ�
							 30,//���ڵĸߣ����أ�
							 g_hWnd[0],
							 (HMENU)_BUTTON2,//ID
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);
	rButton2.left = 0;
	rButton2.top = 40;
	rButton2.right = 100;
	rButton2.bottom = 60;
	ShowWindow(g_hWnd[2],SW_SHOW);


	g_hWnd[3] = CreateWindow(L"BUTTON",
							 L"�Ӵ���",//���ڱ���������
							 WS_VISIBLE |  WS_CHILD | BS_PUSHBUTTON,//���ڷ��
							 0,//���ڵ����Ͻ�x����
							 80,//���ڵ����Ͻ�y����
							 100,//���ڵĿ����أ�
							 30,//���ڵĸߣ����أ�
							 g_hWnd[0],
							 (HMENU)_BUTTON3,//ID
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);

	g_hWnd[4] = CreateWindow(L"BUTTON",
							 L"��������",//���ڱ���������
							 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,//���ڷ��
							 0,//���ڵ����Ͻ�x����
							 120,//���ڵ����Ͻ�y����
							 100,//���ڵĿ����أ�
							 30,//���ڵĸߣ����أ�
							 g_hWnd[0],
							 (HMENU)_BUTTON4,//ID
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);

	g_hWnd[5] = CreateWindow(wc.lpszClassName,
							 L"�Ӵ���",//���ڱ���������
							 WS_OVERLAPPEDWINDOW|WS_CHILD,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 g_hWnd[0],
							 0,//ID
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);

	g_hWnd[6] = CreateWindow(wc.lpszClassName,
							 L"��������",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							  CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 g_hWnd[0],
							 0,//ID
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);

	ShowWindow(g_hWnd[0],nCmdShow);
	UpdateWindow(g_hWnd[0]);

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}