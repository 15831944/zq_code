// a.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "iostream"

int get_rand_int(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int w, h;
	int min, max;

	do
	{
		std::cout<<"������Ҫ���ɵĵ�ͼ��";
		std::cin>>w;
		std::cout<<"������Ҫ���ɵĵ�ͼ�ߣ�";
		std::cin>>h;
	} while (w < 1 || h < 1);

	do
	{
		std::cout<<"������Ҫ���ɵĵ�ͼ����Сֵ��";
		std::cin>>min;
		std::cout<<"������Ҫ���ɵĵ�ͼ���ݴ�ֵ��";
		std::cin>>max;
	} while (min < 0 || max < min || max > 9);

	char fn[256];
	std::cout<<"���������ɵĵ�ͼ�ļ�����";
	std::cin>>fn;

	std::cout<<"�������������ͼ��";
	system("pause");
	
	char* p = new char[(w + 2) * h];
	for (int y = 0; y < h; ++y)
	{
		//д���������
		for (int x = 0; x < w; ++x)
			p[y * (w + 2) + x] = get_rand_int(min + '0', max + '0');
		p[y * (w + 2) + w + 0] = '\r';
		p[y * (w + 2) + w + 1] = '\n';
	}

	FILE* pf = 0;
	fopen_s(&pf, fn, "wb");
	fwrite(p, 1, (w + 2) * h, pf);
	fclose(pf);

	return 0;
}

