#include <iostream>
#include <windows.h>

#define _BMP_W 20
#define _BMP_H 12

struct _COLOR
{
	unsigned char b,g,r;
};

#define �� {0,0,0}
#define �� {255,255,255}
#define �� {0,0,255}
#define �� {0,255,0}
#define �� {255,0,0}

void main()
{
	BITMAPFILEHEADER bfh = {};
	((char*)&bfh.bfType)[0] = 'B';
	((char*)&bfh.bfType)[1] = 'M';
	bfh.bfSize = 14 + 40 + 720;
	bfh.bfOffBits = 14 + 40;
	
	BITMAPINFOHEADER bih = {};
	bih.biSize = 40;
	bih.biWidth = _BMP_W;
	bih.biHeight = _BMP_H;
	bih.biPlanes = 1;
	bih.biBitCount = 24;

	_COLOR c[_BMP_W * _BMP_H] =
	{
		��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,
		��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,
		��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,
		��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,
		��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,
		��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,
		��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,
		��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,
		��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,
		��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,
		��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,
		��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��
	};

	FILE* pf = 0;
	fopen_s(&pf,"2.bmp","wb");
	fwrite(&bfh,1,14,pf);
	fwrite(&bih,1,40,pf);
	fwrite(c,1,720,pf);
	fclose(pf);
	system("pause");
}