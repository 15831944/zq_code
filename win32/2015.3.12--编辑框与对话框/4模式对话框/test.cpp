#include <windows.h>
#include "resource.h"

//��ģʽ�Ի���
//ģʽ�Ի���
//ͨ�öԻ���

char buf[256];

INT_PTR __stdcall f(HWND hwndDlg,
					UINT uMsg,
					WPARAM wParam,
					LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		{
			HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
			SetWindowTextA(hwnd,"������Ҫ�޸ĵĴ��ڱ���������");
			return 1;
		}
	case WM_COMMAND:
		{
			
			if(HIWORD(wParam) == BN_CLICKED)
			{
				if(LOWORD(wParam) == IDC_BUTTON1)
				{
					HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);

					GetWindowTextA(hwnd,buf,256);

					EndDialog(hwndDlg,100);
				}
				else if(LOWORD(wParam) == IDC_BUTTON2)
				{
					EndDialog(hwndDlg,101);
				}
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
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

	case WM_RBUTTONDOWN:
		{
			
			//����һ��ģʽ�Ի���
			INT_PTR r = DialogBox(GetModuleHandle(0),
								  MAKEINTRESOURCE(IDD_DIALOG1),
								  hwnd,
								  f);

			if(r == 100)
				SetWindowTextA(hwnd,buf);

			return 0;
		}
	case WM_KEYDOWN:
		{
			//if(wParam == VK_F1)
			//	ShowWindow(g_hWnd[1],SW_SHOW);
			return 0;
		}
	}
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
	
	HWND hwnd = CreateWindow(wc.lpszClassName,
							 L"ģʽ�Ի���1",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);
	
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

//01)ģʽ�Ի��򣺶Ի�����ʧ�����������޷���Ӧ
//02)��ģʽ�Ի��򣺶Ի�����ʧ��񣬲�Ӱ���������ڵ���Ӧ

//�ô�:���Էǳ��������ӣ��༭�ؼ�
//����Ի���ʵ�����ǶԶԻ�������Ŀؼ��Ĳ���(���ؼ�����Ϣ�Ĵ���)��
//����Ϣ��Ҫ�ǳ�ʼ����Ϣ���¼���Ϣ,��Щ��Ϣ��Ҫ���ڶԻ���
//��Ӧ����Ϣ����������Ӧ