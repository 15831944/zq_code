#include <iostream>
#include <windows.h>

struct _BGR
{
	unsigned char b, g, r;
};

void main()
{
	//'ab'���ڴ���ռ2���ֽڷֱ��ǣ�62 61
	short x = 'ab';

	std::cout<<"������256ɫλͼ�ļ�·����";
	char fn[256];
	std::cin>>fn;

	//�õ�λͼ�ļ�ͷ
	FILE* pf = 0;
	fopen_s(&pf, fn, "rb");
	if (!pf)
	{
		std::cout<<"�޷���ָ���ļ���";
		system("pause");
		return;
	}
	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	BITMAPFILEHEADER* bfh = (BITMAPFILEHEADER*)malloc(fs);
	fread(bfh, 1, fs, pf);
	fclose(pf);

	//�õ���Ϣͷ
	BITMAPINFOHEADER* bih = (BITMAPINFOHEADER*)(bfh + 1);
	if (bih->biBitCount != 8)
	{
		std::cout<<"�򿪵Ĳ���256ɫλͼ��";
		system("pause");
		free(bfh);
		return;
	}

	//�õ���ɫ��
	int* color_table = (int*)(bih + 1);

	//�õ���ɫ
	unsigned char* color = (unsigned char*)bfh + bfh->bfOffBits;

	//�õ�ÿ���ֽ���
	int rbs8 = bih->biWidth;
	if (rbs8 % 4 != 0)
		rbs8 += 4 - rbs8 % 4;

	//�õ�24λλͼ�����ֽ���
	int rbs24 = bih->biWidth * 3;
	if (rbs24 % 4 != 0)
		rbs24 += 4 - rbs24 % 4;
	int all_bytes = 54 + rbs24 * bih->biHeight;

	//��д24λλͼ���ļ�ͷ
	BITMAPFILEHEADER bfh24
		=
	{
		'MB', //BM
		all_bytes,
		0,
		0,
		54
	};

	//��д24λλͼ����Ϣͷ
	BITMAPINFOHEADER bih24
		=
	{
		40,
		bih->biWidth,
		bih->biHeight,
		1,
		24
	};

	//��д24λλͼ����ɫ����
	char* color24 = (char*)malloc(all_bytes - 54);
	for (int y = 0; y < bih->biHeight; ++y)
	{
		for (int x = 0; x < bih->biWidth; ++x)
		{
			//�õ���ɫ
			int i = *(color + (bih->biHeight - y - 1) * rbs8 + x);
			_BGR* p = (_BGR*)(&color_table[i]);
			_BGR* q = (_BGR*)(color24 + (bih->biHeight - y - 1) * rbs24 + x * 3);
			*q = *p;
		}
	}

	//д���ļ�
	std::cout<<"������24λλͼ�ļ�·����";
	std::cin>>fn;

	//д���ļ�
	fopen_s(&pf, fn, "wb");
	fwrite(&bfh24, 1, 14, pf);
	fwrite(&bih24, 1, 40, pf);
	fwrite(color24, 1, all_bytes - 54, pf);
	fclose(pf);

	std::cout<<"ת���ɹ���";
	system("pause");

	free(color24);
	free(bfh);
}