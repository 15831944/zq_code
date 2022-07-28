#include <iostream>
#include "24bitmap.h"

void main()
{
	BITMAPFILEHEADER* bmp1 = Open_24bmp("Autumn.bmp");
	int w, h;
	WH_24bmp(bmp1, &w, &h);

	//����ɨ��
	BITMAPFILEHEADER* bmp2 = Copy_24bmp(bmp1);
	for (int y = 0; y < h; y += 2)
	{
		for (int x = 0; x < w; x += 2)
		{
			_YS* p = color_24bmp(bmp2, x, y);
			p->r = p->g = p->b = 0;
		}
	}
	Save_24bmp("����ɨ��.bmp", bmp2);
	Close_24bmp(bmp2);

	//��ɫ
	BITMAPFILEHEADER* bmp3 = Copy_24bmp(bmp1);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			_YS* p = color_24bmp(bmp2, x, y);
			p->r = ~p->r;
			p->g = ~p->g;
			p->b = ~p->b;
		}
	}
	Save_24bmp("��ɫ.bmp", bmp3);
	Close_24bmp(bmp3);

	//�Ҷȣ���ɫ���ǰ׵���֮��ľ��ȹ��ɣ�
	BITMAPFILEHEADER* bmp4 = Copy_24bmp(bmp1);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			_YS* p = color_24bmp(bmp2, x, y);
			unsigned char a = (p->r + p->g + p->b) / 3;
			p->r = p->g = p->b = a;
		}
	}
	Save_24bmp("�Ҷ�.bmp", bmp4);
	Close_24bmp(bmp4);


	Close_24bmp(bmp1);

	system("pause");
}

//Alpha��Ϲ�ʽ