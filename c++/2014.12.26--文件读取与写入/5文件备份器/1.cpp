#include<iostream>


void main()
{

	std::cout<<"������Ҫ���ݵ�Դ�ļ�·��:";
	char filename[256];
	std::cin>>filename;

	FILE* pf = 0;

	fopen_s(&pf,filename,"rb");
	
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
	
	//�����ڴ�ռ�
	char* filedata = (char*)malloc(filesize);
	
	//���ļ����ݶ��뵽�ڴ���
	fread(filedata,1,filesize,pf);

	//�ر��ļ�
	fclose(pf);

	//���뱸���ļ�·��
	std::cout<<"������Ҫ���ݵ�Ŀ���ļ�·��:";
	std::cin>>filename;

	//���ļ�
	fopen_s(&pf,filename,"wb");
	//д��
	fwrite(filedata,1,filesize,pf);
	//�ر��ļ�
	fclose(pf);
	//�ͷ��ڴ�
	free(filedata);
	std::cout<<"���ݳɹ�";
	system("pause");
}