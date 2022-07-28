#include "24bitmap.h"

BITMAPFILEHEADER* Open_24bmp(const char* fn)
{
	FILE* pf = 0;
	fopen_s(&pf, fn, "rb");
	if (!pf)
		return 0;

	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	BITMAPFILEHEADER* pbfh = (BITMAPFILEHEADER*)malloc(fs);
	fread(pbfh, 1, fs, pf);
	fclose(pf);

	return pbfh;
}

//����24λλͼ�ļ�
BITMAPFILEHEADER* Copy_24bmp(BITMAPFILEHEADER* pbfh)
{
	BITMAPFILEHEADER* q = (BITMAPFILEHEADER*)malloc(pbfh->bfSize);
	memcpy(q, pbfh, pbfh->bfSize);
	return q;
}

BITMAPFILEHEADER* Create_24bmp(int w, int h)
{
	//�õ�ÿ����ռ�ֽ���
	int rowbytes = w * 3;
	if (rowbytes % 4 != 0)
		rowbytes += 4 - rowbytes % 4;

	//�õ��ļ��ܴ�С
	int filesize = 54 + rowbytes * h;

	//�����ڴ�ռ�
	BITMAPFILEHEADER* pbfh = (BITMAPFILEHEADER*)malloc(filesize);

	//��д�ļ�ͷ����
	pbfh->bfType = 'MB';
	pbfh->bfSize = filesize;
	pbfh->bfReserved1 = 0;
	pbfh->bfReserved2 = 0;
	pbfh->bfOffBits = 54;

	//��д��Ϣͷ����
	BITMAPINFOHEADER* pbih = (BITMAPINFOHEADER*)(pbfh + 1);
	pbih->biSize = 40;
	pbih->biWidth = w;
	pbih->biHeight = h;
	pbih->biPlanes = 1;
	pbih->biBitCount = 24;
	pbih->biCompression = 0;
	pbih->biSizeImage = 0;
	pbih->biXPelsPerMeter = 0;
	pbih->biYPelsPerMeter = 0;
	pbih->biClrUsed = 0;
	pbih->biClrImportant = 0;

	return pbfh;
}

//����24λλͼ�ļ�
void Save_24bmp(const char* fn, BITMAPFILEHEADER* pbfh)
{
	FILE* pf = 0;
	fopen_s(&pf, fn, "wb");
	fwrite(pbfh, 1, pbfh->bfSize, pf);
	fclose(pf);
}

//�ر�24λλͼ�ļ�
void Close_24bmp(BITMAPFILEHEADER* pbfh)
{
	free(pbfh);
}

//�õ�λͼ����
void WH_24bmp(BITMAPFILEHEADER* pbfh, int* w, int* h)
{
	BITMAPINFOHEADER* pbih = (BITMAPINFOHEADER*)(pbfh + 1);
	*w = pbih->biWidth;
	*h = pbih->biHeight;
}

//�õ�ָ��λ�õ���ɫ
_YS* color_24bmp(BITMAPFILEHEADER* pbfh, int x, int y)
{
	_YS* p = (_YS*)((char*)pbfh + 54);

	//�õ�һ���ж����ֽ�
	BITMAPINFOHEADER* pbih = (BITMAPINFOHEADER*)(pbfh + 1);
	int rowbytes = pbih->biWidth * 3;
	if (rowbytes % 4 != 0)
		rowbytes += 4 - rowbytes % 4;

	return (_YS*)((char*)p + (pbih->biHeight - 1 - y) * rowbytes + 3 * x);
}

