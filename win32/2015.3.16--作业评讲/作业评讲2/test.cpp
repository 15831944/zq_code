#include <windows.h>
#include <iostream>

HWND g_hWnd[5];


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
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == EN_CHANGE)
			{
				if(LOWORD(wParam) == 0)
				{
					int length = GetWindowTextLength(g_hWnd[1]);
					char* buf = new char[length + 1];

					GetWindowText(g_hWnd[1],buf,length + 1);

					SetWindowText(g_hWnd[2],buf);

					delete []buf;
				}
			}
			else if(HIWORD(wParam) == BN_CLICKED)
			{
				switch(LOWORD(wParam))
				{
				case 2:
					{
						int count = SendMessage(g_hWnd[1],EM_GETLINECOUNT,0,0);
						char buf[256];
						sprintf_s(buf,256,"%d",count);

						MessageBox(g_hWnd[0],buf,"����",MB_OK);
						break;
					}
				case 3:
					{
						int count = SendMessage(g_hWnd[1],EM_GETLINECOUNT,0,0);

						for(int i = 0;i < count;++i)
						{
							char buf[256];
							sprintf_s(buf,256,"%d",i);
							char buf1[256] = {};
							*((short*)buf1) = 256;
							int r = SendMessage(g_hWnd[1],EM_GETLINE,i,(__w64 long)buf1);
							MessageBox(g_hWnd[0],buf1,buf,MB_OK);
						}
						break;
					}
				}
			}
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
	g_hWnd[0] = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 "��ҵ2",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	g_hWnd[1] = CreateWindow("edit",
							 "",//���ڱ���������
							 WS_CHILD | WS_VISIBLE | ES_MULTILINE |WS_BORDER
							 |ES_AUTOVSCROLL|ES_AUTOHSCROLL |
							 WS_HSCROLL|WS_VSCROLL|ES_WANTRETURN,//���ڷ��
							 0,//���ڵ����Ͻ�x����
							 0,//���ڵ����Ͻ�y����
							 200,//���ڵĿ����أ�
							 200,//���ڵĸߣ����أ�
							 g_hWnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	g_hWnd[2] = CreateWindow("edit",
							 "",//���ڱ���������
							 WS_CHILD | WS_VISIBLE |WS_BORDER | ES_READONLY|WS_HSCROLL,//���ڷ��
							 200,//���ڵ����Ͻ�x����
							 0,//���ڵ����Ͻ�y����
							 200,//���ڵĿ����أ�
							 30,//���ڵĸߣ����أ�
							 g_hWnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)1,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	g_hWnd[3] = CreateWindow("button",
							 "����",//���ڱ���������
							 WS_CHILD | WS_VISIBLE |WS_BORDER | BS_PUSHBUTTON,//���ڷ��
							 0,//���ڵ����Ͻ�x����
							 250,//���ڵ����Ͻ�y����
							 50,//���ڵĿ����أ�
							 30,//���ڵĸߣ����أ�
							 g_hWnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)2,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	g_hWnd[4] = CreateWindow("button",
							 "����",//���ڱ���������
							 WS_CHILD | WS_VISIBLE |WS_BORDER | BS_PUSHBUTTON,//���ڷ��
							 0,//���ڵ����Ͻ�x����
							 300,//���ڵ����Ͻ�y����
							 50,//���ڵĿ����أ�
							 30,//���ڵĸߣ����أ�
							 g_hWnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)3,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);

	//04)��ʾ����
	ShowWindow(g_hWnd[0],nCmdShow);

	//05)���´���
	UpdateWindow(g_hWnd[0]);

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}