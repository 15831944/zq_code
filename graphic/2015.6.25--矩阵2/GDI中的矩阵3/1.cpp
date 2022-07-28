#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <iostream>
#include "Vector2.h"
#include "Matrix.h"

#pragma comment(lib, "Msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

HWND g_hWnd = 0;
BOOL g_Act = TRUE;

void GameInit();
void GameRun();
void GameEnd();

LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_ACTIVATEAPP:
		{
			g_Act = (BOOL)wParam;
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
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
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
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, //���ڷ��
		FALSE); //���޲˵�

	g_hWnd = CreateWindowA(
		wc.lpszClassName, //ʹ�õĴ������ṹ�������
		"hello world", //���ڱ���������
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		cr.left, //�������Ͻ�x����
		cr.top, //�������Ͻ�y����
		cr.right - cr.left, //���ڿ�
		cr.bottom - cr.top, //���ڸ�
		HWND_DESKTOP, //�����ڣ�һ����˵��д���洰��
		0, //�˵���������þ���д0
		wc.hInstance, //Ӧ�ó���ʵ�����
		0); //��������

	//��Ϸ��ʼ��
	GameInit();

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	//�鿴��ǰ�Ķ�ͷ��Ϣ���������Ϣ�ͷ����棬û����Ϣ�ͷ��ؼ�
	//BOOL PeekMessage(
	//	LPMSG lpMsg, //�õ���ͷ��Ϣ����Ϣ�ṹ��
	//	HWND hWnd, //���ڣ�Ϊ0��õ���ǰ�߳��д��������д��ڵ���Ϣ
	//	UINT wMsgFilterMin, //��Ϣ��������
	//	UINT wMsgFilterMax, //��Ϣ��������
	//	UINT wRemoveMsg); //PM_REMOVE��ʾ�鿴����Ϣ֮�������Ϣ������ɾ����PM_NOREMOVE��ʾ�����鿴��Ϣ�����Ὣ�鿴������Ϣ�Ӷ�����ɾ��

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		//�������Ϣ������Ϸѭ���ʹ�����Ϣ
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//���û����Ϣ�䵱ǰ����Ϊ����״̬��ִ����Ϸѭ��
		else if (g_Act)
		{
			//ÿ֡��ʼ��ʱ��
			int t0 = GetTickCount();

			//��Ϸ����
			GameRun();

			//ÿ֡��Ϸʱ��Ĵ���
			int t1 = GetTickCount() - t0;
			Sleep(t1 < _SLEEP_TIME ? _SLEEP_TIME - t1 : 1);
		}
		else
		//���û����Ϣ�䵱ǰ����δ������͵ȴ���Ϣ
			WaitMessage();
	}

	//��Ϸ����
	GameEnd();

	return 1;
}

#include <time.h>

HDC main_dc; //���豸
HDC back_dc; //���豸
HBITMAP back_bmp; //���豸λͼ

HDC bmpdc[2];
HBITMAP hbmp[2];

XFORM dw;

float angle = 0.0f;
bool fd = true;
float sfl = 1.0f;
CVector2 pos;

//��λ��
void XFORM_Identity(XFORM* xf);
void XFORM_Scaling(XFORM* xf, float x, float y);
void XFORM_Rotate(XFORM* xf, float a);
void XFORM_Translate(XFORM* xf, float x, float y);
XFORM* _XF_X_XF(const XFORM* xf1, const XFORM* xf2, XFORM* output);

void GameInit()
{
	//�õ�����ͼ�豸
	main_dc = GetDC(g_hWnd);

	//�õ����豸
	back_dc  = CreateCompatibleDC(main_dc);

	//�������豸λͼ
	back_bmp = CreateCompatibleBitmap(main_dc, _CLIENT_W, _CLIENT_H);

	//�����豸λͼѡ����豸
	DeleteObject(SelectObject(back_dc, back_bmp));

	//�����߼���ͼģʽ
	SetGraphicsMode(back_dc, GM_ADVANCED);

	//��ʼ����λ����
	XFORM_Identity(&dw);

	//Ϊ��ʹ�û��Ƶ�Ч�ʸ��ߣ�Windows��ѻ�������洢��
	//һ������֮���ٷ����Կ������Կ����л��ƣ�����Ĵ���
	//ǿ��ʹ��ֻҪ��һ���������һ��GDI���ƺ����ĵ��ã�
	//��ô�Կ������̽��л���
	GdiSetBatchLimit(1);

	hbmp[0] = (HBITMAP)LoadImageA(0, "0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc[0] = CreateCompatibleDC(main_dc);
	DeleteObject(SelectObject(bmpdc[0], hbmp[0]));
	hbmp[1] = (HBITMAP)LoadImageA(0, "1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc[1] = CreateCompatibleDC(main_dc);
	DeleteObject(SelectObject(bmpdc[1], hbmp[1]));
}

void GameRun()
{
	//�õ��任����
	XFORM xz, sf, py;
	XFORM_Rotate(&xz, angle);
	XFORM_Scaling(&sf, sfl, sfl);
	XFORM_Translate(&py, pos.x, pos.y);
	XFORM zh1, zh2;
	_XF_X_XF(_XF_X_XF(&xz, &sf, &zh1), &py, &zh2);

	//��պ�
	BitBlt(back_dc, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	//���Ʊ���ͼ
	BitBlt(back_dc, 0, 0, _CLIENT_W, _CLIENT_H, bmpdc[0], 0, 0, SRCCOPY);
	
	//���б��λ��Ƶ�ʱ�����ñ任���������ʹ����
	//�������ͼ�εı任֮���ٽ��еĻ��ƵĻ������
	//Ҫ���õ�ǰ�任Ϊ��λ���󼴿�
	SetWorldTransform(back_dc, &zh2);
	MoveToEx(back_dc, 0, 0, 0);
	LineTo(back_dc, 100, 100);
	TransparentBlt(back_dc, -50, -50, 100, 100, bmpdc[1], 0, 0, 100, 100, RGB(0, 255, 0));
	//SetWorldTransform(back_dc, &dw); //�˴����Բ�Ҫ

	XFORM_Rotate(&xz, -angle * 5.0f);
	XFORM_Scaling(&sf, sfl * 2.0f, sfl * 0.5f);
	XFORM_Translate(&py, _CLIENT_W / 2, _CLIENT_H / 2);
	_XF_X_XF(_XF_X_XF(&xz, &sf, &zh1), &py, &zh2);
	SetWorldTransform(back_dc, &zh2);
	TextOutA(back_dc, 0, 0, "123abc���", 10);
	TransparentBlt(back_dc, -50, -50, 100, 100, bmpdc[1], 0, 0, 100, 100, RGB(255, 0, 0));
	SetWorldTransform(back_dc, &dw); //�˴�һ��Ҫ

	//���λ���
	BitBlt(main_dc, 0, 0, _CLIENT_W, _CLIENT_H, back_dc, 0, 0, SRCCOPY);

	//���ݱ任
	angle += 0.05f;
	if (fd)
	{
		sfl += 0.01f;
		if (sfl > 2.0f)
			fd = false;
	}
	else
	{
		sfl -= 0.01f;
		if (sfl < 0.5f)
			fd = true;
	}
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(g_hWnd, &p);
	pos.Set(p.x, p.y);
}

void GameEnd()
{
	DeleteObject(hbmp[1]);
	DeleteDC(bmpdc[1]);
	DeleteObject(hbmp[0]);
	DeleteDC(bmpdc[0]);

	//�ͷź��豸λͼ
	DeleteObject(back_bmp);

	//�ͷź��豸
	DeleteDC(back_dc);

	//�ͷ�����ͼ�豸
	ReleaseDC(g_hWnd, main_dc);
}

//Windows���ṩ�ľ����XFORM����ṹ����
//eM11 eM12 0
//eM21 eM22 0
//eDx  eDy  1
//����Windows��û���ṩֱ�Ӵ������ֱ任����ĺ�����������Щ����ֻ�������Լ�ʵ��
//1��Windows��Ҫʹ��ͼ�α任�����뿪���߼����ƹ���
//2����SetWorldTransform�����õ�ǰ���Ƶı任����
//   һ����������任�����Ӱ��������еĻ��ƣ���
//   ����ĳ������֮ǰ��ϣ���û����վ���Ӱ�죬��ô
//   ���ñ任����Ϊ��λ���󼴿�

//��λ��
void XFORM_Identity(XFORM* xf)
{
	xf->eM11 = xf->eM22 = 1.0f;
	xf->eM12 = xf->eM21 = xf->eDx = xf->eDy = 0.0f;
}

//����
void XFORM_Scaling(XFORM* xf, float x, float y)
{
	xf->eM11 = x;		xf->eM12 = 0.0f;
	xf->eM21 = 0.0f;	xf->eM22 = y;
	xf->eDx = 0.0f;		xf->eDy = 0.0f;
}

//��ת
void XFORM_Rotate(XFORM* xf, float a)
{
	xf->eM11 = cos(a);		xf->eM12 = sin(a);
	xf->eM21 = -xf->eM12;	xf->eM22 = xf->eM11;
	xf->eDx = 0.0f;			xf->eDy = 0.0f;
}

//ƽ��
void XFORM_Translate(XFORM* xf, float x, float y)
{
	xf->eM11 = 1.0f;	xf->eM12 = 0.0f;
	xf->eM21 = 0.0f;	xf->eM22 = 1.0f;
	xf->eDx = x;		xf->eDy = y;
}

XFORM* _XF_X_XF(const XFORM* xf1,
				const XFORM* xf2,
				XFORM* output)
{
	//eM11 eM12 0
	//eM21 eM22 0
	//eDx  eDy  1

	output->eM11 = xf1->eM11 * xf2->eM11 + xf1->eM12 * xf2->eM21;
	output->eM12 = xf1->eM11 * xf2->eM12 + xf1->eM12 * xf2->eM22;

	output->eM21 = xf1->eM21 * xf2->eM11 + xf1->eM22 * xf2->eM21;
	output->eM22 = xf1->eM21 * xf2->eM12 + xf1->eM22 * xf2->eM22;

	output->eDx = xf1->eDx * xf2->eM11 + xf1->eDy * xf2->eM21 + xf2->eDx;
	output->eDy = xf1->eDx * xf2->eM12 + xf1->eDy * xf2->eM22 + xf2->eDy;

	return output;
}