#include <windows.h>
#include "resource.h"

//��ģʽ�Ի���
//ģʽ�Ի���
//ͨ�öԻ���

HWND g_hWnd[2];

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
			SetWindowTextA(hwnd,"123abc");
			return 1;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == BN_CLICKED)
			{
				if(LOWORD(wParam) == IDC_BUTTON1)
				{
					char buf[256];
					//��ȡ���Ի�����ָ����ID�Ŀؼ�����
					HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
					GetWindowTextA(hwnd,buf,256);

					HWND phwnd = GetParent(hwndDlg);
					SetWindowTextA(phwnd,buf);
				}
				else if(LOWORD(wParam) == IDC_BUTTON2 
					||	LOWORD(wParam) == IDCANCEL)
					ShowWindow(hwndDlg,SW_HIDE);
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
			ShowWindow(g_hWnd[1],SW_SHOW);
			return 0;
		}
	case WM_KEYDOWN:
		{
			if(wParam == VK_F1)
				ShowWindow(g_hWnd[1],SW_SHOW);
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
	
	g_hWnd[0] = CreateWindow(wc.lpszClassName,
							 L"��ģʽ�Ի���",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	//������ģʽ�Ի���
	g_hWnd[1] = CreateDialog(GetModuleHandle(0),//��ȡ�Ի���ľ��
							MAKEINTRESOURCE(IDD_DIALOG1),//�Ի����ID
							g_hWnd[0],//������
							f);//�Ի������Ϣ������

	ShowWindow(g_hWnd[1],SW_SHOW);
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