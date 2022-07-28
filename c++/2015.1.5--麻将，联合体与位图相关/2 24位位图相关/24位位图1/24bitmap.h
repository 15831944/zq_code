#ifndef _24_BITMAP_H_
#define _24_BITMAP_H_

#include <iostream>
#include <windows.h>

//��24λλͼ�ļ�
BITMAPFILEHEADER* Open_24bmp(const char* fn);

//����24λλͼ�ļ�
BITMAPFILEHEADER* Copy_24bmp(BITMAPFILEHEADER* pbfh);

//����24λλͼ�ļ�
void Save_24bmp(const char* fn, BITMAPFILEHEADER* pbfh);

//�ر�24λλͼ�ļ�
void Close_24bmp(BITMAPFILEHEADER* pbfh);

//�õ�λͼ����
void WH_24bmp(BITMAPFILEHEADER* pbfh, int* w, int* h);

//��ɫ�ṹ��
struct _YS
{
	unsigned char b, g, r;
};
//�õ�ָ��λ�õ���ɫ
_YS* color_24bmp(BITMAPFILEHEADER* pbfh, int x, int y);

#endif