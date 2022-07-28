#include <windows.h>
#include <iostream>

//���ڹ�ϵ
//�Ӵ���
//{
//01���Ӵ��ڱ������ڲü�
//02���Ӵ��ڲ����в˵�
//03�����Ÿ����ڵ����ٱ�����
//}
//��������
//{
//01���������ڲ��������ڲü�
//02�����Ÿ����ڵ����ٱ�����
//}

//�����Ŀؼ�
//01)�����Ǵ���
//{
//	����ϵͳԤ�����������еĿؼ���WNDCLASS
//  ���еĿؼ���ӵ���Լ��Ĵ��ڹ��̴�����
//	�¼���Ϣͨ��WM_COMMAND���͸�������
//  ����ͨ��SendMessage���Ϳ�����Ϣ������ĳЩ�ؼ�
//}
//02)����
//��ť
//{  
//	�����ı�����ʾ�ڰ�ť�ϵ��ı�
//  ��־�ַ���:button
//  ���һ������ѹʽ 
//  ��Ϣ�� �¼���Ϣ-��BN_CLICKED
//		   ������Ϣ-��BM_CLICK
//}
//�༭��
//{
//	�����ı�
//  {
//		��ʾ���ı�����
//		ÿ����0x0d,0x0a����
//      ����н�����0x00
//  }
//  ���ͣ�
//	{
//		����
//		�س�����
//	}
//	��Ϣ
//	{
//		�¼���Ϣ:EN_UPDATE,EN_CHANGE
//		������Ϣ:EM_GETLINECOUNT,EM_GETLINE,EM_LINEINDEX,EM_LINEFROMCHAR
//	}
//}

//��غ���
//EnableWindow
//GetWindowText
//GetWindowTextLength

//ÿ�ֿؼ������Լ��Ĵ�����Ϣ�����Լ�WNDCLASS

HWND g_hWnd[2];
//������Ϣ��������������������ϵͳ����
__w64 long __stdcall ButtonProc(HWND hwnd,//������Ϣ�Ĵ���
								unsigned int uMsg,//��Ϣ����
								__w64 unsigned int wParam,//��Ϣ���Ӳ���1
								__w64 long lParam)//��Ϣ���Ӳ���2
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			//��ȡ�����ڵľ��
			HWND parenthWnd = GetParent(hwnd);
			//��ȡ�˵����
			HMENU hmenu = GetMenu(hwnd);

			//�򸸴��ڷ���һ��WM_COMMAND��Ϣ
			SendMessage(parenthWnd,WM_COMMAND,MAKELONG((DWORD)hmenu,BN_CLICKED),(__w64 long)hwnd);

			SetFocus(hwnd);
			return 0;
		}
	case WM_KEYDOWN:
		{
			MessageBoxA(0,"2",0,0);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			char buf[256];

			GetWindowTextA(hwnd,buf,256);
			TextOutA(hdc,0,0,buf,(int)strlen(buf));

			EndPaint(hwnd,&ps);
			return 0;
		}
	}
	//���ǲ����ĵ���Ϣ�͵���DefWindowProc(windows��������Ϣ��Ĭ�ϴ�����)���������Ǵ���
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

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
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == BN_CLICKED)
				Beep(500,500);
			return 0;
		}
	case WM_KEYDOWN:
		{
			MessageBoxA(0,"1",0,0);
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
							 L"ģ�ⰴť",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	WNDCLASS Button_wc;
	Button_wc.style = CS_HREDRAW|CS_VREDRAW;
	Button_wc.lpfnWndProc = ButtonProc;
	Button_wc.cbClsExtra = 0;
	Button_wc.cbWndExtra = 0;
	Button_wc.hInstance = hInstance;
	Button_wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	Button_wc.hCursor = LoadCursor(0,IDC_ARROW);
	Button_wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	Button_wc.lpszMenuName = 0;
	Button_wc.lpszClassName = L"MyButton";
	RegisterClass(&Button_wc);
	g_hWnd[1] = CreateWindow(L"MyButton",//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 L"�ҵİ�ť",//���ڱ���������
							 WS_BORDER | WS_VISIBLE | WS_CHILD,//���ڷ��
							 0,//���ڵ����Ͻ�x����
							 0,//���ڵ����Ͻ�y����
							 100,//���ڵĿ����أ�
							 30,//���ڵĸߣ����أ�
							 g_hWnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)1,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0
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