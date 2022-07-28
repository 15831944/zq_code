#include <windows.h>

//���ڴ��м���λͼ
HBITMAP CreateColorBmp(int w,int h,unsigned int c)
{
	HDC dc = GetDC(HWND_DESKTOP);
	BITMAPINFOHEADER bin = {};
	bin.biSize = sizeof(bin);
	bin.biWidth = w;
	bin.biHeight = h;
	bin.biPlanes = 1;
	bin.biBitCount = 24;
	//�õ�һ�е��ֽ���
	int rowbyte = w * 3;
	
	if(rowbyte % 4 != 0)
		rowbyte += 4 - rowbyte % 4;
	
	//�õ����ֽ���
	int allbyte = rowbyte * h;

	//������ɫ����
	char* p = new char[allbyte];
	struct _BGR
	{
		unsigned char b,g,r;
	}* pBGR;

	for(int i = 0; i < h; ++i)
	{
		pBGR = (_BGR*)(p + i * rowbyte);
		for(int j = 0; j < w;++j)
		{
			pBGR->b = GetBValue(c);
			pBGR->g = GetGValue(c);
			pBGR->r = GetRValue(c);
			pBGR += 1;
		}
	}
	//
	HBITMAP hbmp = CreateDIBitmap(
		dc,&bin,CBM_INIT,
		p,(BITMAPINFO*)(&bin),
		DIB_RGB_COLORS);
	delete []p;
	ReleaseDC(HWND_DESKTOP,dc);
	return hbmp;
}

HBITMAP hbmp[2];


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
	}
	//���ǲ����ĵ���Ϣ�͵���DefWindowProc(windows��������Ϣ��Ĭ�ϴ�����)���������Ǵ���
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,//Ӧ�ó���ʵ�����
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	hbmp[0] = CreateColorBmp(640,480,RGB(0,127,127));
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
							 "�ڴ��м���λͼ",//���ڱ���������
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