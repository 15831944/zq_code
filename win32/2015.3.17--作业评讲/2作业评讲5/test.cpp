#include <windows.h>
#include <vector>
#include "resource.h"

HWND g_hSel;

bool jx = true;

struct TX
{
	POINT p;
	bool jx;
};

std::vector<TX> tx;


INT_PTR CALLBACK DialogProc(HWND hwndDlg,//������Ϣ�Ĵ���
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
				case IDC_BUTTON1:jx = true;break;
				case IDC_BUTTON2:jx = false;break;
				case IDCANCEL:ShowWindow(hwndDlg,SW_HIDE);break;
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
			//Ͷ��һ��WM_QUIT��Ϣ�����̵߳���Ϣ������
			PostQuitMessage(0);
			//һ�����Ǵ�����ĳ����Ϣ��Ҫֱ�ӷ���0.
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			TX t = {LOWORD(lParam),HIWORD(lParam),jx};
			tx.push_back(t);
			InvalidateRect(hwnd,0,1);
			
			return 0;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == BN_CLICKED)
			{
				switch(LOWORD(wParam))
				{
				case 0:
					{
						ShowWindow(g_hSel,SW_SHOW);
						break;
					}
				}
			}
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			for(std::vector<TX>::iterator i = tx.begin(); i != tx.end();++i)
			{
				if(i->jx)
				{
					Rectangle(hdc,i->p.x,i->p.y,i->p.x + 50,i->p.y + 40);
				}
				else
				{
					Ellipse(hdc,i->p.x,i->p.y,i->p.x + 50,i->p.y + 40);
				}
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
	//���ڽṹ����������б����������ṹ�崴�����Ĵ��ڶ����У�
	//CS_HREDRAW : ����ˮƽ�ߴ緢���ı�ͻ��ػ�(Ͷ��WM_PAINT��Ϣ)
	//CS_VREDRAW : ������ֱ�ߴ緢���ı�ͻ��ػ�(Ͷ��WM_PAINT��Ϣ)
	wc.style = CS_HREDRAW|CS_VREDRAW;
	//������Ϣ�����ĵ�ַ
	wc.lpfnWndProc = WindowProc;
	//�������Ķ����ֽڣ�һ�㲻ʹ��
	wc.cbClsExtra = 0;
	//���ڵĶ����ֽڣ�һ�㲻ʹ��
	wc.cbWndExtra = 0;
	//Ӧ�ó���ʵ�����
	wc.hInstance = hInstance;
	//ͼ��
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);

	//���
	wc.hCursor = LoadCursor(0,IDC_ARROW);

	//HBRUSH ��ˢ
	//����ϵͳ���ڻ��ƴ��ڱ����ı�����ˢ
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//�˵��ַ���ID�����û������0
	wc.lpszMenuName = 0;

	//���ڵ�����
	wc.lpszClassName = "�˰�";

	//02)ע�����õĴ���
	RegisterClass(&wc);
	
	//03)�ô������ṹ������������
	HWND hWnd = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 "��ҵ3",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	CreateWindow("button",//�������ṹ������ƣ�����ϵͳ�����
                //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
				 //������ɴ������ڵ�����
				 "ͼ��ѡ��",//���ڱ���������
				 WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,//���ڷ��
				 0,//���ڵ����Ͻ�x����
				 30,//���ڵ����Ͻ�y����
				 60,//���ڵĿ����أ�
				 30,//���ڵĸߣ����أ�
				 hWnd,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
				 (HMENU)0,//���ڲ˵��������ʹ�ò˵���0
				 wc.hInstance,//Ӧ�ó���ʵ�����
				 0);

	g_hSel = CreateDialog(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),hWnd,DialogProc);

	//04)��ʾ����
	ShowWindow(hWnd,nCmdShow);

	//05)���´���
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