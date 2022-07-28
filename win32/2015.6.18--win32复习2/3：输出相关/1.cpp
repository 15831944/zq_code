#include <windows.h>

#define _CLIENT_W 640
#define _CLIENT_H 480

LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg, //��Ϣֵ
							WPARAM wParam, //��Ϣ�ĸ��Ӳ���1
							LPARAM lParam) //��Ϣ�ĸ��Ӳ���2
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_PAINT: //������Ϣ
		{
			//�����ڴ��ڿͻ����г�������Ч����
			//�ͻᵼ�±���Ϣ��Ͷ�ݵ���Ϣ������
			//��Ч����Ĳ�������ͨ�����漸��;��
			//1�������ɱ����Ǳ�Ϊ��������
			//2���ߴ緢���仯����CS_HREDRAW��CS_VREDRAW�����ģ�
			//3��InvalidateRect����������Ч����

			//��WM_PAINT��Ϣ�У�BeginPaint��EndPaint
			//�Ǳ���д�ģ���д�������Ժ����Ǳ���
			//Ϣ��ר�ú�����BeginPaint���ڵõ���ͼ��
			//����EndPaint�����ͷŻ�ͼ�豸�����Ǳ���
			//ӵ�л�ͼ���òſ���ʹ�ø��ֻ�ͼ��������
			//ͼ�����ĵ�һ�������������ǻ�ͼ�豸����
			//ͼ�豸��������HDC������ͼ�豸�б�����
			//��ʲô��ɫ�������壬���ĸ��ط���������
			//����Щ��Ҫ��Ϣ��ָʾ��ͼ�������о����
			//����
			PAINTSTRUCT ps; //���Եõ�һЩ�ͻ�ͼ�йص���Ϣ������һ�㶼û����
			HDC dc = BeginPaint(hwnd, &ps); //ͨ��ָ�����ڴ����Ļ�ͼ�豸����ô���Ƶ���������ƶ����ڵĿͻ���

			//��ͼ�������д��BeginPaint��EndPaint֮��

			//�߶λ���

			//������ʼ��
			MoveToEx(
				dc, //��ͼ�豸
				100, //�߶���ʼ��x����
				100, //�߶���ʼ��y����
				0); //���ڵõ���һ�λ����߶ε���ֹ���POINT�����ַ���������õ���0����

			//�����Ѿ����õ���ʼ���ָ������ֹ������߶�
			LineTo(
				dc, //��ͼ�豸
				300, //�߶���ֹ��x����
				200); //�߶���ֹ��y����

			POINT p;
			MoveToEx(dc, 150, 150, &p); //�˴���p���Եõ�(300,200)
			LineTo(dc, p.x, p.y);

			//���λ���
			Rectangle(
				dc, //��ͼ�豸
				200, //�������Ͻ�x
				300, //�������Ͻ�y
				400, //�������½�x
				400); //�������½�y

			//Բ�λ���
			Ellipse(
				dc, //��ͼ�豸
				200, //��Բ�����о������Ͻ�x
				300, //��Բ�����о������Ͻ�y
				400, //��Բ�����о������½�x
				400); //��Բ�����о������½�y

			Ellipse(dc, 250, 350, 400, 400);

			//���ֻ��ƣ�����������һ����������Ĭ���ǰ�ɫ
			TextOutA(
				dc, //��ͼ�豸
				0, //�����������Ͻ�x
				0, //�����������Ͻ�y
				"123abc���", //����
				(int)strlen("123abc���")); //Ҫ���Ƶ����ֳ���

			EndPaint(hwnd, &ps);

			return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_MENU;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "123abc";

	RegisterClass(&wc);

	//���Ը��ݿͻ�����С�����㴰�ڴ�С
	int sw = GetSystemMetrics(SM_CXSCREEN); //�õ�����Ŀ�
	int sh = GetSystemMetrics(SM_CYSCREEN); //�õ�����ĸ�
	RECT cr //cr�õ��ͻ�����λ�á��ߴ�
		=
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		(sw - _CLIENT_W) / 2 + _CLIENT_W,
		(sh - _CLIENT_H) / 2 + _CLIENT_H
	};
	//���ݴ���Ŀͻ���λ�á��ߴ������㴰��Ӧ���е�λ�á��ߴ�
	AdjustWindowRect(
		&cr, //�ͻ������Σ�������ִ�����֮������봰�ھ���
		WS_OVERLAPPEDWINDOW, //���ڷ��
		FALSE); //���޲˵�

	HWND hwnd = CreateWindowA(
		wc.lpszClassName, //ʹ�õĴ������ṹ�������
		"hello world", //���ڱ���������
		WS_OVERLAPPEDWINDOW, //���ڷ��
		cr.left, //�������Ͻ�x����
		cr.top, //�������Ͻ�y����
		cr.right - cr.left, //���ڿ�
		cr.bottom - cr.top, //���ڸ�
		HWND_DESKTOP, //�����ڣ�һ����˵��д���洰��
		0, //�˵���������þ���д0
		wc.hInstance, //Ӧ�ó���ʵ�����
		0); //��������

	//���Եõ��ͻ����ĳߴ�
	RECT r; //���νṹ�壺���Ͻǣ�left��top�������½ǣ�right��bottom��
	GetClientRect(hwnd, &r);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}