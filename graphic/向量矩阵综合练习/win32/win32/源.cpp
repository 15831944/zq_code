#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <iostream>
#include <list>
#include "Vector2.h"
#include "Matrix.h"
#include <time.h>

#pragma comment(lib, "Msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

#define _R 20.0f

HWND g_hWnd = 0;
BOOL g_Act = TRUE;
XFORM dw;

HDC main_dc; //���豸
HDC back_dc; //���豸
HBITMAP back_bmp; //���豸λͼ
HBITMAP hbmp;
HDC bmpdc;

void GameInit();
void GameRun();
void GameEnd();

void DrawLine(const CVector2* v1, const CVector2* v2);

//��λ��
void XFORM_Identity(XFORM* xf);
void XFORM_Scaling(XFORM* xf, float x, float y);
void XFORM_Rotate(XFORM* xf, float a);
void XFORM_Translate(XFORM* xf, float x, float y);
XFORM* _XF_X_XF(const XFORM* xf1, const XFORM* xf2, XFORM* output);

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

class A
{
	int a, b, c,d;
public:
	A(){ a = b = c = 0; }
	A(int A, int B, int C){ a = A; b = B; c = C; }
};

int __stdcall WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	//�ೣ����д���������������()�������ò�ͬ�Ĺ��������첻ͬ���ೣ��
	int a1 = 1; //����=����
	A a2 = A(); //����=�������ó������޲ι����ʼ��
	A a3 = A(1, 2, 3); //����=�������ó��������ι����ʼ��
	a3 = A(2, 3, 4); //����=�������ó��������ι����ʼ��

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

CVector2 u = { 0.0f, -1.0f };
CVector2 pos;
CVector2 hezo = { _CLIENT_W / 2, _CLIENT_H / 2 };
CVector2 speed = {};
void DrawLine(const CVector2* v1, const CVector2* v2)
{
	MoveToEx(back_dc, v1->x, v1->y, 0);
	LineTo(back_dc, v2->x, v2->y);
}

bool fashe = false;
CVector2 zl = { 0.0f, 1.0f };
int power = 10;
float angle = 0.0f;
void GameInit()
{
	//�õ�����ͼ�豸
	main_dc = GetDC(g_hWnd);

	//�õ����豸
	back_dc = CreateCompatibleDC(main_dc);

	//�������豸λͼ
	back_bmp = CreateCompatibleBitmap(main_dc, _CLIENT_W, _CLIENT_H);

	//�����豸λͼѡ����豸
	DeleteObject(SelectObject(back_dc, back_bmp));

	//������ͼģʽ
	SetGraphicsMode(back_dc, GM_ADVANCED);

	//��ʼ����λ����
	XFORM_Identity(&dw);

	srand((unsigned int)time(0));

	hbmp = (HBITMAP)LoadImageA(0, "0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc = CreateCompatibleDC(main_dc);
	DeleteObject(SelectObject(bmpdc, hbmp));
}

void GameRun()
{

	//�õ������������������
	POINT p;
	GetCursorPos(&p);

	//���������ת��Ϊ���ڿͻ���������
	ScreenToClient(g_hWnd, &p);

	//�ڿͻ�����
	if (p.x >= 0 && p.x < _CLIENT_W && p.y >= 0 && p.y < _CLIENT_H)
		pos.Set(p.x, p.y);

	//�õ���������
	CVector2 v = pos - hezo;
	v = v.Normalize();

	//�õ��Ƕȵ�����ֵ
	float cos_angle = v * u;

	//���ؽǶ�
	angle = acos(cos_angle);
	if (pos.x <= _CLIENT_W / 2.0f)
		angle = 2 * 3.1415926f - angle;

	if (fashe)
	{
		if (hezo.x >= 0 && hezo.x < _CLIENT_W && hezo.y >= 0 && hezo.y < _CLIENT_H)
		{
			speed += zl;
			hezo += speed;

			float angle_speed = speed.Normalize() * u;
			angle = acos(angle_speed);
			if (hezo.x <= _CLIENT_W / 2.0f)
				angle = 2 * 3.1415926f - angle;
		}
		else
		{
			fashe = false;
			hezo.Set(_CLIENT_W / 2.0f, _CLIENT_H / 2.0f);
			speed.Set();
		}
	}
	else
	{
		if (p.x >= 0 && p.x < _CLIENT_W && p.y >= 0 && p.y < _CLIENT_W)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x01 && power > 1)
			{
				power -= 1;
			}

			if (GetAsyncKeyState(VK_MBUTTON) & 0x01)
			{
				fashe = true;
				speed = v * power;
			}

			if (GetAsyncKeyState(VK_RBUTTON) & 0x01 && power < 25)
			{
				power += 1;
			}
		}
	}
	//�õ��任����
	XFORM xz,py;
	XFORM_Rotate(&xz, angle);
	XFORM_Translate(&py, hezo.x, hezo.y);
	XFORM zh;
	_XF_X_XF(&xz, &py, &zh);
	BitBlt(back_dc, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	SetWorldTransform(back_dc, &zh);
	TransparentBlt(back_dc, -15, -25, 30, 50, bmpdc, 0, 0, 30, 50, RGB(0, 255, 0));
	SetWorldTransform(back_dc, &dw);
	BitBlt(main_dc,0, 0, _CLIENT_W, _CLIENT_H, back_dc, 0, 0, SRCCOPY);
}

void GameEnd()
{
	//�ͷź��豸λͼ
	DeleteObject(back_bmp);

	//�ͷź��豸
	DeleteDC(back_dc);

	//�ͷ�����ͼ�豸
	ReleaseDC(g_hWnd, main_dc);
}

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

