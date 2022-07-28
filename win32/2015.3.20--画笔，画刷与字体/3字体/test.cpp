#include <windows.h>

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
	
			//������ǰ��ͼ�豸����ĸ߼���ͼģʽ�����Կ���֧��
			//�򱾺�����Ч
			SetGraphicsMode(hdc,GM_ADVANCED);

			HFONT f1 = CreateFont(
								50,//����ĸ߶�
								50,//����Ŀ��
								0,//������ߵ�б�ȣ���λ�ǽǶ�/10����������ϣ������ĵ���б����45�ȣ�����д450
								450,//���屾���б�ȣ���λ�� �Ƕ�/10 ����������ϣ�����屾���б��45�ȣ�����д450�����뿪���߼���ͼģʽ
								FW_NORMAL,//�����ϸ�̶ȣ�һ��FW_NORMAL
								FALSE,//�����Ƿ�Ϊб����
								FALSE,//�����Ƿ����»���
								FALSE,//�����Ƿ��д�Խ��
								DEFAULT_CHARSET,//����ʹ�õı���,DEFAULT_CHARSET��ʾ��ǰ��ϵͳʹ�õı���
								OUT_DEFAULT_PRECIS,//������
								CLIP_DEFAULT_PRECIS,//�ü����
								DEFAULT_QUALITY,//�������
								DEFAULT_PITCH | FF_DONTCARE,//����
								"������κ");//�������

			HFONT oldf = (HFONT)SelectObject(hdc,f1);

			//����������ɫ
			SetTextColor(hdc,RGB(0,255,0));

			//�������屳��Ϊ͸��
			SetBkMode(hdc,TRANSPARENT);

			TextOutA(hdc,0,0,"123abc���",10);


			LOGFONT logfont;
			logfont.lfHeight = 40;
			logfont.lfWidth = 20;
			logfont.lfEscapement = 0;
			logfont.lfOrientation = 0;
			logfont.lfWeight = 400;
			logfont.lfItalic = 1;
			logfont.lfUnderline = 0;
			logfont.lfStrikeOut = 0;
			logfont.lfCharSet = DEFAULT_CHARSET;
			logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
			logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
			logfont.lfQuality = DEFAULT_QUALITY;
			logfont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
			strcpy_s(logfont.lfFaceName,LF_FACESIZE,"����");

			HFONT f2 = CreateFontIndirect(&logfont);

			(HFONT)SelectObject(hdc,f2);

			SetTextColor(hdc,RGB(255,0,0));
			TextOutA(hdc,0,200,"456def����",10);

			SelectObject(hdc,oldf);

			DeleteObject(f1);
			DeleteObject(f2);

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
							 "����",//���ڱ���������
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

	return 1;
}