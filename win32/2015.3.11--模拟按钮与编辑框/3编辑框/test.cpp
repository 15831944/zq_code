#include <windows.h>
#include <iostream>

//�¼���Ϣ:
//BN_UPDATE
//BN_CHANGE
//BN_CLICKED
//������Ϣ:
//EM_GETLINECOUNT
//EM_GETLINE
//EM_LINGINDEX
//EM_LINEFROMCHAR
//BM_CLICK
HWND g_hWnd[5];
HWND g_hButton[4];
int i;

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
	case WM_LBUTTONDOWN:
		{
			//������б༭����õ����ַ�����0x0d,0x0a����
			for(int i = 1; i < 5; ++i)
			{
				int len = GetWindowTextLength(g_hWnd[i]);
				char* str = new char[len + 1];

				//GetWindowText�õ����ַ������н�����0
				GetWindowText(g_hWnd[i],str,len + 1);

				MessageBox(hwnd,str,"����",MB_OK);

				delete []str;
			}
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			i += 1;
			char buf[32];
			sprintf_s(buf,32,"%d",i);
			SetWindowTextA(g_hWnd[2],buf);
			return 0;
		}
	case WM_COMMAND:
		{

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
	wc.lpszClassName = "�˰�";
	RegisterClass(&wc);

	g_hWnd[0] = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 "�༭��",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	//�༭��ķ��
	//ES_AUTOHSCROLL:�Զ�ˮƽ��
	//ES_AUTOVSCROLL:�Զ���ֱ��
	//ES_MULTILINE:����
	//ES_WANTRETURN:�س�����
	//ES_PASSWORD:����
	//ES_READONLY:ֻ��

	//���б༭��
	g_hWnd[1] =  CreateWindow("edit",//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 "1:���б༭��",//���ڱ���������
							 WS_VISIBLE | WS_CHILD | WS_BORDER,//WS_BORDER:ϸ�߿�
							 0,//���ڵ����Ͻ�x����
							 0,//���ڵ����Ͻ�y����
							 200,//���ڵĿ����أ�
							 30,//���ڵĸߣ����أ�
							 g_hWnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)1,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);

	//ֻ��
	g_hWnd[2] =  CreateWindow("edit",//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 "2:ֻ���༭��",//���ڱ���������
							 ES_READONLY | WS_VISIBLE | WS_CHILD | WS_BORDER,//WS_BORDER:ϸ�߿�
							 0,//���ڵ����Ͻ�x����
							 40,//���ڵ����Ͻ�y����
							 200,//���ڵĿ����أ�
							 30,//���ڵĸߣ����أ�
							 g_hWnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)2,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);

	//����
	g_hWnd[3] =  CreateWindow("edit",//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 "3:����༭��",//���ڱ���������
							 ES_PASSWORD | WS_VISIBLE | WS_CHILD | WS_BORDER,//WS_BORDER:ϸ�߿�
							 0,//���ڵ����Ͻ�x����
							 80,//���ڵ����Ͻ�y����
							 200,//���ڵĿ����أ�
							 30,//���ڵĸߣ����أ�
							 g_hWnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)3,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);

	//����
	//WS_HSCROLL:�����Դ���ˮƽ������
	//WS_VSCROLL:�����Դ��Ĵ�ֱ������
	g_hWnd[4] =  CreateWindow("edit",//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 "4:���б༭��",//���ڱ���������
							 ES_WANTRETURN | ES_AUTOVSCROLL | ES_MULTILINE| ES_AUTOHSCROLL
							 |WS_HSCROLL|WS_VSCROLL
							 | WS_VISIBLE | WS_CHILD | WS_BORDER,//WS_BORDER:ϸ�߿�
							 0,//���ڵ����Ͻ�x����
							 120,//���ڵ����Ͻ�y����
							 200,//���ڵĿ����أ�
							 100,//���ڵĸߣ����أ�
							 g_hWnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)4,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);

	char* bn[] = {"EM_GETLINECOUNT","EM_GETLINE","EM_LINEINDEX","EM_LINEFROMCHAR"};

	for(int i = 0; i < 4;++i)
	{
		g_hButton[i] =  CreateWindow("button",//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 bn[i],//���ڱ���������
							 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,//WS_BORDER:ϸ�߿�
							 250,//���ڵ����Ͻ�x����
							 i * 60,//���ڵ����Ͻ�y����
							 200,//���ڵĿ����أ�
							 30,//���ڵĸߣ����أ�
							 g_hWnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)(i + 5),//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);
	}
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