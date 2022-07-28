#include <windows.h>

HWND g_hWnd[3];

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
			if(hwnd == g_hWnd[0])
				DestroyWindow(hwnd);
			else
				ShowWindow(hwnd,SW_HIDE);
			return 0;
		}
	case WM_KEYDOWN:
		{
			if(wParam == VK_F1)
				ShowWindow(g_hWnd[1],SW_SHOW);
			if(wParam == VK_F2)
				ShowWindow(g_hWnd[2],SW_SHOW);
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

	g_hWnd[0] = CreateWindow(wc.lpszClassName,
							 L"������",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	//WS_VISIBLE ʹ����һ��ʼ�ɼ�����ȻҲ����ʹ��
	//ShowWindow(g_hWnd[2],SW_SHOW)ʹ��ɼ�.

	//���ڽڵ�֮��Ĺ�ϵ
	//1)������<---->�Ӵ���(Ҫ��WS_CHILD,Ҫ�������ڲü�)
	//2)������<---->��������(����WS_CHILD,���������ڲü�)

	//���ڵ�������һ��������������еĵ�ǰ���ڵ��ӽڵ㶼���ڵ�ǰ
	//�Ĵ������٣��������Ӵ��ڻ��Ǵ������ڴ�����ʱ��hWndParent
	//�Ǳ���Ҫ��д�丸���ڵľ��.
	g_hWnd[1] = CreateWindow(wc.lpszClassName,
							 L"�Ӵ���(F1��ʾ)",
							 WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CHILD,
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 g_hWnd[0],
							 0,
							 wc.hInstance,
							 0);
	g_hWnd[2] = CreateWindow(wc.lpszClassName,
							 L"��������(F2��ʾ)",
							 WS_OVERLAPPEDWINDOW,
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 g_hWnd[0],
							 0,
							 wc.hInstance,
							 0);
	
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