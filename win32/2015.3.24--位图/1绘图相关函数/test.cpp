#include <windows.h>

HPEN newp;
HBRUSH newb;
HFONT newf;

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
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			HPEN oldp = (HPEN)SelectObject(hdc,newp);
			HBRUSH oldb = (HBRUSH)SelectObject(hdc,newb);
			HFONT oldf = (HFONT)SelectObject(hdc,newf);

			//-------------------�����

			//����ĳ������Ϊָ����ɫ(�뻭�ʻ�ˢ�޹�)
			SetPixel(hdc,1,1,RGB(255,0,0));

			SetPixel(hdc,1,2,RGB(0,255,0));

			//��ȡָ����ĳ�����ص���ɫ
			COLORREF c = GetPixel(hdc,1,2);

			unsigned char r = GetRValue(c);

			//--------------����(����������)
			MoveToEx(hdc,5,5,0);
			LineTo(hdc,100,50);
			//---------------����(���ʣ���ˢ)
			Rectangle(hdc,150,200,280,400);
			//---------------��Բ(���ʣ���ˢ)
			Ellipse(hdc,300,200,480,400);
			//---------------����
			//�����������ɫ
			SetTextColor(hdc,RGB(100,100,100));

			//���ñ���ģʽ
			SetBkMode(hdc,TRANSPARENT);

			//�����������
			TextOutA(hdc,200,0,"123abc",6);


			const char* s = "hellosdafsdfs���������������Ϸ���";

			RECT rect = {200,50,380,250};

			Rectangle(hdc,rect.left,rect.top,rect.right,rect.bottom);

			//���ƶ�������--���һ�������Ƕ��б�־
			DrawTextA(hdc,s,(int)strlen(s),&rect,DT_WORDBREAK);

			SelectObject(hdc,oldp);
			SelectObject(hdc,oldb);
			SelectObject(hdc,oldf);
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
	newp = CreatePen(PS_SOLID,1,RGB(255,0,0));
	newb = CreateSolidBrush(RGB(255,255,0));
	newf = CreateFont(18,12,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,
		"����");

	//01)���һ���������Ľṹ��
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
	HWND hWnd = CreateWindow(wc.lpszClassName,
							 "��һ�����ڳ���",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	ShowWindow(hWnd,nCmdShow);
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

	DeleteObject(newf);
	DeleteObject(newp);
	DeleteObject(newb);

	return 1;
}