// 123.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	FILE* pf = 0;
	fopen_s(&pf, "ASCII.txt", "wb");


	//ASCII�����ǰ0~31���ַ��ǿ����ַ����Ǵ�ӡ
	//�������ģ�ǿ���ü��±���ʾ�Ļ���������
	char x = ' ';
	for (int i = 0; i <= 31; ++i)
		fwrite(&x, 1, 1, pf);
	
	//��ӡ32~127������
	for (int i = 32; i <= 127; ++i)
	{
		if (i % 32 == 0)
			fwrite("\r\n", 2, 1, pf);
		x = i;
		fwrite(&x, 1, 1, pf);
	}
	fclose(pf);

	return 0;
}

