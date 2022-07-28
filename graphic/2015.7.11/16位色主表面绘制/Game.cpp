#include "Game.h"
#include "Main.h"
#include <iostream>
#include <ctime>

#include <ddraw.h>
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

#define _PIXEL_FORMAT 16

//555��ʽ
//0rrrrrgg gggbbbbb
//rrrrrrrr & 0x1f = 000rrrrr << 10
//gggggggg & 0x1f = 000ggggg << 5
//bbbbbbbb & 0x1f = 000bbbbb

#define _555_RGB(r,g,b) \
	((((r) & 0x1f) << 10) | (((g) & 0x1f) << 5) | ((b) & 0x1f))

//565��ʽ
//rrrrrggg gggbbbbb
//rrrrrrrr & 0x1f = 000rrrrr << 11
//gggggggg & 0x3f = 00gggggg << 5
//bbbbbbbb & 0x1f = 000bbbbb
#define _565_RGB(r,g,b) \
	((((r) & 0x1f) << 11) | (((g) & 0x3f) << 5) | ((b) & 0x1f))

short _555_color(unsigned char r, unsigned char g, unsigned char b)
{
	return _555_RGB(r, g, b);
}
short _565_color(unsigned char r, unsigned char g, unsigned char b)
{
	return _565_RGB(r, g, b);
}
short (*_16bit_color)(unsigned char, unsigned char, unsigned char) = 0;

LPDIRECTDRAW7 dd; //ddraw����
LPDIRECTDRAWSURFACE7 dds; //ddraw�������
int rbs = 0; //������ÿ�е��ֽ���
char* color = 0; //���������ɫ��ʼ��ַ
int offset_x = 0, offset_y = 0; //���ڿͻ������Ͻ��������Ļ��λ��

bool _is_565()
{
	//���������棬����ʼ����
	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(ddsd);
	dds->Lock(0, &ddsd, DDLOCK_WAIT, 0);

	//��ddsd.ddpfPixelFormat.dwRGBBitCountΪ16����ǰ��ɫ��ʽ��565
	//��ddsd.ddpfPixelFormat.dwRGBBitCountΪ15����ǰ��ɫ��ʽ��555
	bool r = (ddsd.ddpfPixelFormat.dwRGBBitCount == 16);

	//���������棬����������
	dds->Unlock(0);

	return r;
}

void Init()
{
	DirectDrawCreateEx(0, (void**)&dd, IID_IDirectDraw7, 0);
	dd->SetCooperativeLevel(g_hWnd, DDSCL_NORMAL);
	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(ddsd);
	dd->GetDisplayMode(&ddsd);
	dd->SetDisplayMode(ddsd.dwWidth, ddsd.dwHeight, _PIXEL_FORMAT, 0, 0);

	//����һ�����������ṹ��
	ddsd.dwSize = sizeof(ddsd); //�ṹ��Ĵ�С
	ddsd.dwFlags = DDSD_CAPS; //ָ���ṹ���е�ddsCaps��Ա������Ч
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE; //����Ҫ��������������

	//����������
	dd->CreateSurface(&ddsd, &dds, 0);

	if (_is_565())
		_16bit_color = _565_color;
	else
		_16bit_color = _555_color;
}

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

	//���ƾ���
	for (int y = 0; y < 100; ++y)
	{
		for (int x = 0; x < 200; ++x)
		{
			*((short*)(color + rbs * (y + offset_y) + (x + offset_x) * 2))
				=
			(*_16bit_color)(0, 255, 0);
		}
		//16bit				32bit
		//0		<--->		0
		//1		<--->		8
		//2		<--->		16
		//3		<--->		24
		//4		<--->		32
		//...
		//32	<--->		256
	}

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
