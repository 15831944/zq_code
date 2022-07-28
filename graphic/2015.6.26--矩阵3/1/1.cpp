#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <iostream>
#include "Vector2.h"
#include "Matrix.h"
#include "MY_XFORM.h"

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

HDC bmpdc;
HBITMAP hbmp;

CMY_XFORM dw; //��λ����

bool xz = true; //��ת
CVector2 pos(_CLIENT_W / 2, _CLIENT_H / 2); //λ��
CVector2 speed; //�ٶ�
float angle = 0.0f; //�Ƕ�
int power = 10; //����

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

	hbmp = (HBITMAP)LoadImageA(0, "0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc = CreateCompatibleDC(main_dc);
	DeleteObject(SelectObject(bmpdc, hbmp));
}

void GameRun()
{
	//��պ�
	BitBlt(back_dc, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	if (xz)
	{
		//�õ��н�
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(g_hWnd, &p);
		CVector2 dir = CVector2(p.x, p.y) - CVector2(_CLIENT_W / 2, _CLIENT_H / 2);
		dir = dir.Normalize(); //��λ����֮�󳤶�Ϊ1
		angle = acos(dir * CVector2(0.0f, -1.0f));
		if (p.x < _CLIENT_W / 2) //�Ƕȵ���������
			angle = -angle;

		CMY_XFORM mx1, mx2, mx3;
		mx1.Rotate(angle);
		mx2.Translate(_CLIENT_W / 2, _CLIENT_H / 2);
		mx3 = mx1 * mx2; //�����˵ľ���˷�

		SetWorldTransform(back_dc, &mx3);
		TransparentBlt(back_dc, -15, -25, 30, 50, bmpdc, 0, 0, 30, 50, RGB(0, 255, 0));
		SetWorldTransform(back_dc, &dw);

		//����
		if (GetAsyncKeyState(VK_LBUTTON) & 1)
		{
			speed = dir * power;
			pos.Set(_CLIENT_W / 2, _CLIENT_H / 2);
			xz = false;
		}
	}
	else
	{
		//�õ��仯֮ǰ��λ��
		CVector2 pre_pos = pos;

		//�ƶ�
		pos += speed;

		//�Ƕȿ���ͨ����ǰλ�ú���һ��λ��������
		CVector2 dir = speed.Normalize();
		angle = acos(dir * CVector2(0.0f, -1.0f));
		if (pos.x < _CLIENT_W / 2) //�Ƕȵ���������
			angle = -angle;

		//���ٶ�Ӱ���ٶ�
		speed += CVector2(0.0f, 2.0f); //���µļ��ٶ�

		CMY_XFORM mx1, mx2, mx3;
		mx1.Rotate(angle);
		mx2.Translate(pos.x, pos.y);
		mx3 = mx1 * mx2; //�����˵ľ���˷�

		SetWorldTransform(back_dc, &mx3);
		TransparentBlt(back_dc, -15, -25, 30, 50, bmpdc, 0, 0, 30, 50, RGB(0, 255, 0));
		SetWorldTransform(back_dc, &dw);

		if (pos.x < 0 || pos.x > _CLIENT_W || pos.y < 0 || pos.y > _CLIENT_H)
			xz = true;
	}

	//�����ı仯
	if ((GetAsyncKeyState(VK_UP) & 1) && power < 50)
		power += 1;
	if ((GetAsyncKeyState(VK_DOWN) & 1) && power > 1)
		power -= 1;
	char buf[32];
	sprintf_s(buf, 32, "%d", power);
	SetWindowTextA(g_hWnd, buf);

	//���λ���
	BitBlt(main_dc, 0, 0, _CLIENT_W, _CLIENT_H, back_dc, 0, 0, SRCCOPY);
}

void GameEnd()
{
	DeleteObject(hbmp);
	DeleteDC(bmpdc);

	//�ͷź��豸λͼ
	DeleteObject(back_bmp);

	//�ͷź��豸
	DeleteDC(back_dc);

	//�ͷ�����ͼ�豸
	ReleaseDC(g_hWnd, main_dc);
}