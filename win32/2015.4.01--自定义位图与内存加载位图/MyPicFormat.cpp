#include "MyPicFormat.h"
#include <iostream>


bool Create_mpf_file(char** bmp,//ԭʼ��λͼ�ļ�������
					 int num,//�Զ���λͼ����
					 const char* mpf)//Ҫ���ɵ��Զ���λͼ�ļ�������
{
	FILE* pf = 0;
	fopen_s(&pf,mpf,"wb");
	//��������д���ļ�
	fwrite(&num,4,1,pf);

	for(int i = 0; i < num;++i)
	{
		FILE* qf = 0;
		fopen_s(&qf,bmp[i],"rb");
		if(!qf)
		{
			fclose(pf);
			return false;
		}

		fseek(qf,0,SEEK_END);
		int fs = ftell(qf);
		rewind(qf);

		char* p = new char[fs];
		fread(p,1,fs,qf);
		fclose(qf);
		fwrite(p,fs,1,pf);
		delete []p;
	}

	fclose(pf);
	return true;
}