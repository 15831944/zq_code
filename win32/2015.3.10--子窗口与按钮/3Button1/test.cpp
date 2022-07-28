#include <windows.h>

#define _BUTTON1 1
#define _BUTTON2 2
HWND g_hWnd[3];
RECT rButton1;
RECT rButton2;
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
		//����ǿؼ���Ϣ
		//HIWORD(wParam)�Ǹÿؼ��Ϸ������¼���Ϣ
		//LOWORD(wParam)�Ǹÿؼ���ID��
		//lParam�Ǹÿؼ��Ĵ��ھ��
	case WM_COMMAND:
		{
			//���°�ť
			if(BN_CLICKED == HIWORD(wParam))
			{
				if(LOWORD(wParam) == _BUTTON1)
					MessageBoxA(hwnd,"����1",0,0);
				else if(LOWORD(wParam) == _BUTTON2)
					MessageBoxA(hwnd,"����2",0,0);
			}
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			POINT p = {LOWORD(lParam),HIWORD(lParam)};
			if(PtInRect(&rButton1,p))
				SendMessage(g_hWnd[1],BM_CLICK,0,0);
			if(PtInRect(&rButton2,p))
				SendMessage(g_hWnd[2],BM_CLICK,0,0);
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
							 L"��ť1",//���ڱ���������
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
							 L"��ť2",//���ڱ���������
							 WS_CHILD | BS_PUSHBUTTON,//���ڷ��
							 0,//���ڵ����Ͻ�x����
							 40,//���ڵ����Ͻ�y����
							 100,//���ڵĿ����أ�
							 60,//���ڵĸߣ����أ�
							 g_hWnd[0],
							 (HMENU)_BUTTON2,//ID
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);
	rButton2.left = 0;
	rButton2.top = 40;
	rButton2.right = 100;
	rButton2.bottom = 60;
	ShowWindow(g_hWnd[2],SW_SHOW);
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