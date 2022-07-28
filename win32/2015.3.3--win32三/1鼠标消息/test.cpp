#define _WIN32_WINNT 0x0400
#include <windows.h>
#include "resource.h"
#include <iostream>

#define _CLIENT_W 640
#define _CLIENT_H 480

//ͬһʱ���У���ǰ����ϵͳ����ֻ����һ��������Ӧ
//������Ϣ.������Ӧ������Ϣ�Ĵ��ڳ�Ϊӵ�м�������
//����Ĵ��ڣ�����ʹ��GetFocus,SetFocus�õ�������
//ӵ�м������뽹��Ĵ���

//HWND GetFocus(VOID);//�õ���ǰ�߳�����ӵ�м������뽹��Ĵ���
//HWND SetFocus(HWND hWnd);//����hWndΪ��ǰӵ�м������뽹���
//���ڣ����ҷ��ظղ����õ�ӵ�м������뽹��Ĵ���

//������Ϣ
//WM_KEYDOWN:��ǰ���ڼ���״̬�°��¼����ϵļ�
//WM_KEYUP:��ǰ���ڼ���״̬��̧������ϵļ�

//ֻҪ�������Ϣ����lParam���ǵ�ǰ����ڿͻ���������
//WM_LBUTTONDOWN:���ڿͻ�������������
//WM_LBUTTONUP:���ڿͻ���̧��������
//WM_LBUTTONDBLCLK:���ڿͻ���˫��������
//WM_RBUTTONDOWN:���ڿͻ�����������Ҽ�
//WM_RBUTTONUP:���ڿͻ���̧������Ҽ�
//WM_RBUTTONDBLCLK:���ڿͻ���˫������Ҽ�
//WM_MBUTTONDOWN:���ڿͻ�����������м�
//WM_MBUTTONUP:���ڿͻ���̧������м�
//WM_MBUTTONDBLCLK:���ڿͻ���˫������м�
//WM_MOUSEMOVE:����ƶ�����
//WM_MOUSEWHEEL:����м�����

char s[1024];
int len = 0;

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
	case WM_KEYDOWN:
		{
			if(wParam == VK_RETURN)
			{
				MessageBoxA(hwnd,"���»س���",0,0);
				return 0;
			}
		}
	case WM_KEYUP:
		{
			if(wParam == VK_SPACE)
			{
				MessageBoxA(hwnd,"̧��ո��",0,0);
				return 0;
			}
		}
	case WM_CHAR:
		{
			//�����һ�����ֽ��ַ�����Ϣ��Ӧһ�Σ�
			//��wParamΪ�õ��ֽ��ַ��ĵ�ǰ����
			//�����һ��˫�ֽ��ַ�����Ϣ��Ӧ����,
			//��wParam��һ��Ϊ��˫�ֽ��ַ������ֽڣ�
			//�ڶ���Ϊ��˫�ֽ��ַ���β�ֽ�
			s[len++] = (char)wParam;
			s[len] = 0;
			SetWindowTextA(hwnd,s);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			//#define LOWORD(l) ((WORD)((DWORD_PTR)(l) & 0xffff))
			//0x????!!!!
			//0x0000ffff
			//0x0000!!!!
			//#define HIWORD(l) ((WORD)((DWORD_PTR)(l) >> 16))
			//0x?? ?? !! !!
			///>>-----------
			//0x0000????
			//�õ�һ��˫�ֽڵĵ��ֲ���
			int x = LOWORD(lParam);

			//�õ�һ��˫�ֽڵĸ��ֲ���
			int y = HIWORD(lParam);

			char buf[64];
			sprintf_s(buf,64,"WM_LBUTTONDOWN:(%d,%d)\n",x,y);
			OutputDebugStringA(buf);
			return 0;
		}
	case WM_LBUTTONUP:
		{
			//�õ�һ��˫�ֽڵĵ��ֲ���
			int x = LOWORD(lParam);

			//�õ�һ��˫�ֽڵĸ��ֲ���
			int y = HIWORD(lParam);

			char buf[64];
			sprintf_s(buf,64,"WM_LBUTTONUP:(%d,%d)\n",x,y);
			OutputDebugStringA(buf);
			return 0;
		}
	case WM_LBUTTONDBLCLK:
		{
			//�����ڴ��ڽṹ��������������
			//����CS_DBLCLKS��־
			//�õ�һ��˫�ֽڵĵ��ֲ���
			int x = LOWORD(lParam);

			//�õ�һ��˫�ֽڵĸ��ֲ���
			int y = HIWORD(lParam);

			char buf[64];
			sprintf_s(buf,64,"WM_LBUTTONDBLCLK:(%d,%d)\n",x,y);
			OutputDebugStringA(buf);
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			//�õ�һ��˫�ֽڵĵ��ֲ���
			int x = LOWORD(lParam);

			//�õ�һ��˫�ֽڵĸ��ֲ���
			int y = HIWORD(lParam);

			char buf[64];
			sprintf_s(buf,64,"WM_MOUSEMOVE:(%d,%d)\n",x,y);
			SetWindowTextA(hwnd,buf);
			return 0;
		}
	case WM_MOUSEWHEEL:
		{
			//ע�����windows.h֮ǰҪ�ú������õ�ǰ�Ĳ���ϵͳ�İ汾
			short a = GET_WHEEL_DELTA_WPARAM(wParam);

			if(WHEEL_DELTA == a)
				OutputDebugStringA("��ǰ����\n");
			else if(-WHEEL_DELTA == a)
				OutputDebugStringA("������\n");
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
	wc.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
	//������Ϣ�����ĵ�ַ
	wc.lpfnWndProc = WindowProc;
	//�������Ķ����ֽڣ�һ�㲻ʹ��
	wc.cbClsExtra = 0;
	//���ڵĶ����ֽڣ�һ�㲻ʹ��
	wc.cbWndExtra = 0;
	//Ӧ�ó���ʵ�����
	wc.hInstance = hInstance;
	//ͼ��
	//HICON LoadIcon(����ͼ��
	//HINSTANCE hInstance,//��Ҫʹ�õ�ͼ���Ǵ����exe�ļ��е���Դ
	//                      ��˴�������дӦ�ó����ʵ��������������
	//                      ��0����.  
	//LPCSTR lpIconName);//ͼ����ַ���ID�����ͼ���Ǵ����exe�ļ��е���Դ
	//                     �����õ���ͼ��ID��������������
	//                     MAKEINTRESOURCE�꽫��ת��Ϊ�ַ�����ʽ
	wc.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));

	//���
	//HCURSOR LoadCursor(���ع��
	//HINSTANCE hInstance,//��Ҫʹ�õĹ���Ǵ����exe�ļ��е���Դ
	//                      ��˴�������дӦ�ó����ʵ��������������
	//                      ��0����.  
    //LPCSTR lpCursorName);�����ַ���ID�����ͼ���Ǵ����exe�ļ��е���Դ
	//                     �����õ��Ĺ��ID��������������
	//                     MAKEINTRESOURCE�꽫��ת��Ϊ�ַ�����ʽ
	wc.hCursor = LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1));

	//HBRUSH ��ˢ
	//����ϵͳ���ڻ��ƴ��ڱ����ı�����ˢ
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//�˵��ַ���ID�����û������0
	wc.lpszMenuName = 0;

	//���ڵ�����
	wc.lpszClassName = L"�˰�";

	//02)ע�����õĴ���
	RegisterClass(&wc);
	//һ���������Ľṹ��������ڴ������������
	//,�ṹ������д��ĳЩ��Ա������������ͼ�꣬��꣩
	//�;������½ṹ�崴�����������еĴ��ڵĹ���,��
	//ÿ������Ҳ���Լ���һ���Ķ���������˵��С,λ�ã��Ƿ���
	//�˵��ȵ�

	//�õ���ǰ����Ŀ�͸�
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	//���ڵ�λ�ã���С
	RECT r = 
	{
		(sw - _CLIENT_W)/2,
		(sh - _CLIENT_H)/2,
		(sw - _CLIENT_W)/2 + _CLIENT_W,
		(sh - _CLIENT_H)/2 + _CLIENT_H
	};

	//������ִ����ϣ��Ὣ��һ������ָ��RECT����Ϊ����Ӧ�еľ���
	AdjustWindowRect(&r,//�趨�Ŀͻ�����λ�ã����
	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,//���ڷ��
	FALSE);//�Ƿ��в˵�

	//03)�ô������ṹ������������
	HWND hWnd = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 L"��һ�����ڳ���",//���ڱ���������
							 //WS_THICKFRAME ͨ������϶��ı䴰�ڴ�С
							 //WS_MAXIMIZEBOX �������Ͻǵ���󻯺ͻ�ԭ��ť
							 WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,//���ڷ��
							 r.left,//���ڵ����Ͻ�x����
							 r.top,//���ڵ����Ͻ�y����
							 r.right - r.left,//���ڵĿ����أ�
							 r.bottom - r.top,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	//���ڴ�С����ͬ�ڿͻ�����С

	//���������к�Ὣ���ڵĴ�С�ľ��η��ظ�r
	//GetWindowRect(hWnd,&r);
	//���������к�Ὣ�ͻ����Ĵ�С�ľ��η��ظ�r
	//GetClientRect(hWnd,&r);

	//04)��ʾ����
	ShowWindow(hWnd,nCmdShow);

	//05)���´���
	UpdateWindow(hWnd);

	//���1
	//������Ϣ��ʾ��
	//MessageBoxA(hWnd,"���ڴ����ɹ�","��ʾ",MB_OK);

	//���2
	//���ô��ڵı��������ı�
	//SetWindowTextA(hWnd,"������ķ���");

	//���3
	//�����-��������ʾ�ı�
	//OutputDebugStringA("��������\n");
	//OutputDebugStringA("��Ϣѭ��");

	//06)��Ϣѭ��
	//��Ϣ�ṹ��
	//struct MSG
	//{
	//	HWND hwnd;//��������Ĵ���
	//	UINT message;//��Ϣ����
	//	WPARAM wParam;//��Ϣ���Ӳ���1,��ͬ����Ϣ���岻ͬ
	//	LPARAM lParam;//��Ϣ���Ӳ���2,��ͬ����Ϣ���岻ͬ
	//	DWORD time;//���������ʱ��
	//	POINT pt;//��������ʱ������ڵ�λ��(������������)
	//};
	//1)windows��Ϊÿ���߳�ά��һ����Ϣ����<MSG>
	//2)windows����ʱ��صļ��ÿ���������Ƿ���ĳЩ�ض����¼�
	//  ��ôwindows�ͻ�������������һ��MSG�ṹ�壬�����ýṹ��
	//  ���뵽����������ڵ��̵߳���Ϣ�����У���������ĳ����������
	//  ����������,��windows�����һ��MSG����.
	//  MSG msg;
	//  msg.hwnd = hWnd;
	//  msg.message = WM_LBUTTONDOWN;
	//  msg.wParam = MK_LBUTTON;
	//  msg.lParam = MAKELONG(���x���꣬���y����);(����ڴ��ڿͻ���)
	//	MAKELONG(WORD1,WORD2)��WORD1��WORD2��ϳ�һ��DWORD
    //  msg.time = �����¼���ʱ��
	//  msg.pt = �����¼�ʱ������ڵ�λ��(���������)
	//  �����(��Ϣ���У�msg)��
	//3)����Ӧ����GetMessage������PeekMessage���Ӷ�����
	//  ȡ����Ϣ����������صĴ���,Ȼ����Ϣ����������ϵͳ
	//4)����ϵͳ����������ڴ������ṹ�������õĴ�����Ϣ����
	//  ���������Ƿ���������ϵͳ����Ϣ.
	//  ����Ϣ������ȡ��ͷ��Ϣ�������ǰû����Ϣ�͵ȴ�
	//GetMessage(
 //   LPMSG lpMsg,//���ڻ�ȡ��Ϣ����Ϣ�ṹ���ַ
 //   HWND hWnd,//ָ����ȡ��Ϣ�Ĵ��ڣ�Ϊ0���ȡ��ǰ�߳������д��ڵ���Ϣ
 //   UINT wMsgFilterMin,//��Ϣ���˵�����
 //   UINT wMsgFilterMax);//��Ϣ���˵�����

	//����õ�����ϢWM_QUIT��Ϣ�ͷ��ؼ�.
	//��֮�ͷ����档
	//��������ӵ��þ�ֻ�ܻ�ȡ��hWnd������Ĵ��ڵ���Ϣ�����Ҳ���õ���
	//WM_LBUTTONDOWN��WM_RBUTTONDBLCLK֮�����Ϣ
	//GetMessage(&msg,hWnd,WM_LBUTTONDOWN,WM_RBUTTONDBLCLK);

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


//ֻҪ���ǳ�����ʹ������Դ�����������Զ�Ϊ���ǵĹ�����������ļ���
//resource.h
//�����������ԴID�ţ���һ��������,һ��Ҫʹ����Դ���Ƕ�Ҫ�������ͷ�ļ�
//������ʹ����Щ��
//������.rc(��Դ�ű��ļ�)
//�ǶԳ�����ʹ�õĸ�����Դ�ľ���ϸ��������
//VS����ר�ŵ���Դ����������������rc�ļ���
//����rc�������ĸ�����Դ�������ִ���ļ���