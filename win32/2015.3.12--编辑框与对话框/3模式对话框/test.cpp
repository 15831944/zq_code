#include <windows.h>
#include "resource.h"

//��ģʽ�Ի���
//ģʽ�Ի���
//ͨ�öԻ���

INT_PTR __stdcall f(HWND hwndDlg,
					UINT uMsg,
					WPARAM wParam,
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
			//EndDialog�˳��Ի���������DialogBox�ķ���ֵ
			if(HIWORD(wParam) == BN_CLICKED)
			{
				if(LOWORD(wParam) == IDOK)
				{
					EndDialog(hwndDlg,100);
				}
				else if(LOWORD(wParam) == IDCANCEL)
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
			//ShowWindow(g_hWnd[1],SW_SHOW);
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


	//WNDCLASS wc;
	//wc.style = CS_HREDRAW|CS_VREDRAW;
	//wc.lpfnWndProc = WindowProc;
	//wc.cbClsExtra = 0;
	//wc.cbWndExtra = 0;
	//wc.hInstance = hInstance;
	//wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	//wc.hCursor = LoadCursor(0,IDC_ARROW);
	//wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	//wc.lpszMenuName = 0;
	//wc.lpszClassName = L"�˰�";
	//RegisterClass(&wc);
	//
	//HWND hwnd = CreateWindow(wc.lpszClassName,
	//						 L"ģʽ�Ի���",//���ڱ���������
	//						 WS_OVERLAPPEDWINDOW,//���ڷ��
	//						 CW_USEDEFAULT,//���ڵ����Ͻ�x����
	//						 CW_USEDEFAULT,//���ڵ����Ͻ�y����
	//						 CW_USEDEFAULT,//���ڵĿ����أ�
	//						 CW_USEDEFAULT,//���ڵĸߣ����أ�
	//						 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
	//						 0,//���ڲ˵��������ʹ�ò˵���0
	//						 wc.hInstance,//Ӧ�ó���ʵ�����
	//						 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	//����һ��ģʽ�Ի���
	INT_PTR r = DialogBox(hInstance,
						  MAKEINTRESOURCE(IDD_DIALOG1),
						  HWND_DESKTOP,
						  f);


	MessageBoxA(0,r == 100 ? "[ȷ��]�˳�" : "[ȡ��]�˳�",0,MB_OK);
	

	//ShowWindow(hwnd,nCmdShow);
	//UpdateWindow(hwnd);
	//
	//MSG msg;
	//while(GetMessage(&msg,0,0,0))
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//}

	return 1;
}