#include "Game.h"
#include "Main.h"
#include <iostream>
#include <ctime>

#include <ddraw.h>
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

LPDIRECTDRAW7 dd; //ddraw����
LPDIRECTDRAWSURFACE7 dds; //ddraw�������
int rbs = 0; //������ÿ�е��ֽ���
char* color = 0; //���������ɫ��ʼ��ַ
int offset_x = 0, offset_y = 0; //���ڿͻ������Ͻ��������Ļ��λ��

void Init()
{
	DirectDrawCreateEx(0, (void**)&dd, IID_IDirectDraw7, 0);
	dd->SetCooperativeLevel(g_hWnd, DDSCL_NORMAL);
	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(ddsd);
	dd->GetDisplayMode(&ddsd);
	dd->SetDisplayMode(ddsd.dwWidth, ddsd.dwHeight, ddsd.ddpfPixelFormat.dwRGBBitCount, 0, 0);

	//����һ�����������ṹ��
	ddsd.dwSize = sizeof(ddsd); //�ṹ��Ĵ�С
	ddsd.dwFlags = DDSD_CAPS; //ָ���ṹ���е�ddsCaps��Ա������Ч
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE; //����Ҫ��������������

	//����������
	dd->CreateSurface(&ddsd, &dds, 0);
}

#define _SURFACE_COLOR(x,y) *((int*)(color + (y) * rbs + (x) * 4))
#define _RGB_COLOR(r,g,b) ((r) << 16 | (g) << 8 | (b))
void DrawRect1(int, int, int, int, int);
void DrawRect2(int, int, int, int, int);
void DrawRect3(int, int, int, int, int);

void Run()
{
	//���������棬����ʼ����
	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(ddsd);
	dds->Lock(
		0, //Ҫ�����ı����о��ε�ַ�����Ϊ�����ʾ������������
		&ddsd, //�˴��ı��������ṹ����Ϊ�˵õ�������Ϣ
		DDLOCK_WAIT, //��ʾ����������˱���͵ȴ�ֱ���ܹ���������
		0);
	rbs = ddsd.lPitch;
	color = (char*)ddsd.lpSurface;
	POINT p = {0, 0};
	ClientToScreen(g_hWnd, &p);
	offset_x = p.x;
	offset_y = p.y;


	//���������棬����������
	dds->Unlock(0);
}

void capture_screen(const char* fn)
{
	//����������
	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(ddsd);
	dds->Lock(
		0, //Ҫ�����ı����о��ε�ַ�����Ϊ�����ʾ������������
		&ddsd, //�˴��ı��������ṹ����Ϊ�˵õ�������Ϣ
		DDLOCK_WAIT, //��ʾ����������˱���͵ȴ�ֱ���ܹ���������
		0);
	rbs = ddsd.lPitch;
	color = (char*)ddsd.lpSurface;
	
	//���㵱ǰ�洢����λͼ����ռ�
	int bmp_rbs = ddsd.dwWidth * 3;
	if (bmp_rbs % 4 != 0)
		bmp_rbs += 4 - bmp_rbs % 4;
	int all_size = 54 + bmp_rbs * ddsd.dwHeight;

	//�����ڴ�
	BITMAPFILEHEADER* bfh = (BITMAPFILEHEADER*)malloc(all_size);
	BITMAPINFOHEADER* bih = (BITMAPINFOHEADER*)((char*)bfh + 14);
	char* dcolor = (char*)bfh + 54;
	memset(bfh, 0, 54);

	//�ļ�ͷ����Ϣͷ
	bfh->bfType = 'MB';
	bfh->bfSize = all_size;
	bfh->bfOffBits = 54;
	bih->biSize = 40;
	bih->biWidth = ddsd.dwWidth;
	bih->biHeight = ddsd.dwHeight;
	bih->biPlanes = 1;
	bih->biBitCount = 24;

	//��ɫ����
	for (int y = 0; y < ddsd.dwHeight; ++y)
	{
		for (int x = 0; x < ddsd.dwWidth; ++x)
		{
			char* c0 = dcolor + (ddsd.dwHeight - y - 1) * bmp_rbs + x * 3;
			char* c1 = color + y * rbs + x * 4;
			c0[0] = c1[0];
			c0[1] = c1[1];
			c0[2] = c1[2];
		}
	}

	FILE* pf = 0;
	fopen_s(&pf, fn, "wb");
	fwrite(bfh, 1, all_size, pf);
	fclose(pf);
	free(bfh);

	//���������棬����������
	dds->Unlock(0);
}

void End()
{
	if (dds)
		dds->Release();

	if (dd)
		dd->Release();
}

//void DrawRect1(int left, int top, int right, int bottom, int c)
//{
//	for (int y = top; y <= bottom; ++y)
//	{
//		for (int x = left; x <= right; ++x)
//		{
//			_SURFACE_COLOR(x + offset_x, y + offset_y) = c;
//		}
//	}
//}
//
//void DrawRect2(int left, int top, int right, int bottom, int c)
//{
//	for (int y = top; y <= bottom; ++y)
//	{
//		for (int x = left; x <= right; ++x)
//		{
//			int dx = x + offset_x;
//			int dy = y + offset_y;
//			if (dx >= 0 && dx < g_ScreenW && dy >= 0 && dy < g_ScreenH)
//				_SURFACE_COLOR(dx, dy) = c;
//		}
//	}
//}
//
//struct MY_RECT
//{
//	int left, top, right, bottom;
//};
//
//bool intersect_rect(const MY_RECT* r1,
//					const MY_RECT* r2,
//					MY_RECT* r3)
//{
//	if (r1->left > r2->right ||
//		r2->left > r1->right ||
//		r1->top > r2->bottom ||
//		r2->top > r1->bottom)
//		return false;
//	else
//	{
//		*r3 = *r1;
//		if (r2->left > r1->left)
//			r3->left = r2->left;
//		if (r2->right < r1->right)
//			r3->right = r2->right;
//		if (r2->top > r1->top)
//			r3->top = r2->top;
//		if (r2->bottom < r1->bottom)
//			r3->bottom = r2->bottom;
//		return true;
//	}
//}
//
//void DrawRect3(int left, int top, int right, int bottom, int c)
//{
//	//�õ��������
//	MY_RECT r1 = {0, 0, g_ScreenW - 1, g_ScreenH - 1};
//
//	//���ݿͻ���λ�õõ����ƾ�������������λ��
//	MY_RECT r2 = {left + offset_x, top + offset_y, right + offset_x, bottom + offset_y};
//
//	MY_RECT r3;
//	if (intersect_rect(&r1, &r2, &r3))
//	{
//		for (int y = r3.top; y <= r3.bottom; ++y)
//		{
//			for (int x = r3.left; x <= r3.right; ++x)
//				_SURFACE_COLOR(x, y) = c;
//		}
//	}
//}
//
//BITMAPFILEHEADER* LoadBmp(const char* bmpfile)
//{
//	FILE* pf = 0;
//	fopen_s(&pf, bmpfile, "rb");
//	if (!pf)
//		return 0;
//	fseek(pf, 0, SEEK_END);
//	int fs = ftell(pf);
//	rewind(pf);
//	char* fd = new char[fs];
//	fread(fd, 1, fs, pf);
//	fclose(pf);
//
//	return (BITMAPFILEHEADER*)fd;
//}
//
//void DrawBmp(int sleft, int stop,
//			 int dleft, int dtop, int dright, int dbottom,
//			 BITMAPFILEHEADER* bmp)
//{
//	//�õ��������
//	MY_RECT r1 = {0, 0, g_ScreenW - 1, g_ScreenH - 1};
//
//	//���ݿͻ���λ�õõ����ƾ�������������λ��
//	MY_RECT r2 = {dleft + offset_x, dtop + offset_y, dright + offset_x, dbottom + offset_y};
//
//	MY_RECT r3;
//	if (intersect_rect(&r1, &r2, &r3))
//	{
//		//�õ�ԭλͼ��ɫ����
//		BITMAPINFOHEADER* bih = (BITMAPINFOHEADER*)(bmp + 1);
//		int bmp_rbs = bih->biWidth * 3;
//		if (bmp_rbs % 4 != 0)
//			bmp_rbs += 4 - bmp_rbs % 4;
//		char* bmp_color = (char*)bmp + 54;
//		
//		for (int y = r3.top, sy = stop; y <= r3.bottom; ++y, ++sy)
//		{
//			for (int x = r3.left, sx = r3.left - r2.left + sleft; x <= r3.right; ++x, ++sx)
//			{
//				_SURFACE_COLOR(x, y) = *((int*)(bmp_color + (bih->biHeight - sy - 1) * bmp_rbs + 3 * sx));
//			}
//		}
//	}
//}
//
//void ReleaseBmp(BITMAPFILEHEADER* bmp)
//{
//	if (bmp)
//		delete [] bmp;
//}
