#include<iostream>


void main()
{
	FILE* pf = 0;

	fopen_s(&pf,"�洢1.txt","rb");
	
	if(!pf)
	{
		std::cout<<"ָ���ļ��޷���,";
		system("pause");
		return;
	}

	//�õ��ļ��Ĵ�С

	//1���ƶ��ļ���д�±�
	//01)�ļ�ָ��
	//02)�ƶ���ƫ����
	//03)�ƶ���Ŀ�ĵ�
	//SEEK_CUR:��ʾ��ǰλ��
	//SEEK_END:��ʾ�ļ�ĩβ
	//SEEK_SET:��ʾ�ļ���ͷ
	fseek(pf,0,SEEK_END);
	//2���õ���ǰ��д�±�����ļ���ͷλ�õ��ֽ���
	int filesize = ftell(pf);
	//�ƶ���д�±굽�ļ���ͷ
	rewind(pf);//��ȫ��ͬ��fseek(pf,0,SEEK_SET);

	fseek(pf,6,SEEK_CUR);

	int cs = ftell(pf);

	fseek(pf,-1,SEEK_CUR);

	cs = ftell(pf);
	//rewind(pf);
	fseek(pf,0,SEEK_SET);
	cs = ftell(pf);

	fclose(pf);
	system("pause");
}