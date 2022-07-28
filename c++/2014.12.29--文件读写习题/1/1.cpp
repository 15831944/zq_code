#include<iostream>
#include "Test.h"

//f1_2��Ч�ʸ���f1_1��Ч��
void f1_1()
{
	int num;
	std::cin>>num;
	//���ٶ�
	int* p = (int*)malloc(num * sizeof(int));
	for(int i = 0; i < num;++i)
		std::cin>>p[i];
	char filename[256];
	std::cin>>filename;
	FILE* pf = 0;
	//��ֻд��ʽ���ļ�
	fopen_s(&pf,filename,"wb");
	//дNUM����һ��д4���ֽ�
	for(int i = 0; i < num;++i)
		fwrite(p + i,1,sizeof(int),pf);

	fclose(pf);
	free(p);
}

void f1_2()
{
	int num;
	std::cin>>num;
	int* p = (int*)malloc(num * sizeof(int));
	for(int i = 0; i < num;++i)
		std::cin>>p[i];
	char filename[256];
	std::cin>>filename;
	FILE* pf = 0;
	fopen_s(&pf,filename,"wb");
	//�ܹ�дNUM*4���ֽڴ�С������
	fwrite(p,sizeof(int),num,pf);

	fclose(pf);
	free(p);
}

void f2_1()
{
	char filename[256];
	std::cin>>filename;
	FILE* pf = 0;
	//��ֻд��ʽ���ļ�
	fopen_s(&pf,filename,"rb");

	if(!pf)
	{
		std::cout<<"�޷���ָ���ļ�.";
		system("pause");
		return;
	}
	//�ļ��±��ƶ������
	fseek(pf,0,SEEK_END);
	int filesize = ftell(pf);
	//�ļ��±��ƶ����ʼ
	rewind(pf);

	int num = filesize / sizeof(int);
	for(int i = 0; i < num;++i)
	{
		//������һ��д4���ֽ�
		int x;
		fread(&x,1,sizeof(int),pf);
		std::cout<<x<<std::endl;
	}
	fclose(pf);
}


void f2_2()
{
	char filename[256];
	std::cin>>filename;
	FILE* pf = 0;
	fopen_s(&pf,filename,"rb");

	if(!pf)
	{
		std::cout<<"�޷���ָ���ļ�.";
		system("pause");
		return;
	}
	fseek(pf,0,SEEK_END);
	int filesize = ftell(pf);
	rewind(pf);
	//���ٶ�
	int* p = (int*)malloc(filesize);

	fread(p,1,filesize,pf);

	fclose(pf);
	//�ܸ���
	int num = filesize / sizeof(int);
	for(int i = 0; i < num;++i)
	{
		std::cout<<p[i]<<std::endl;
	}
	free(p);
}

void f3_1()
{
	Init();
	int num;
	std::cin>>num;
	for(int i = 0; i < num;++i)
	{
		char buf[256];
		std::cin>>buf;
		//����ADDΪ����
		Add(buf,strlen(buf) + 1);
	}
	
	char filename[256];
	std::cin>>filename;
	FILE* pf = 0;
	fopen_s(&pf,filename,"wb");
	//д����NUM����һ��4���ֽ�
	fwrite(&num,1,sizeof(int),pf);
	//�ö���д
	fwrite(address,1,length,pf);

	fclose(pf);
	End();
}

void f3_2()
{
	char filename[256];
	std::cin>>filename;
	FILE* pf = 0;
	fopen_s(&pf,filename,"rb");
	if(!pf)
		return;
	fseek(pf,0,SEEK_END);
	//��ȡҪ�������ֽ���
	int filesize = ftell(pf);
	rewind(pf);
	//���ٶ�
	char* p = (char*)malloc(filesize);
	fread(p,1,filesize,pf);
	fclose(pf);
	char* q = p + 4;
	for(int i = 0; i < *((int*)p);++i)
	{
		std::cout<<q<<std::endl;
		q += strlen(q) + 1;
	}
	//�ͷŶ�
	free(q - filesize);
}

void f4_1()
{
	Init();
	int num = 0;
	char bz;
	while(1)
	{	//bz��ʾһ������
		system("cls");
		std::cout<<"01)�ַ�\n02)����\n03)������\n04)�ַ���\n05)����\n��ѡ��:";
		int sel;
		std::cin>>sel;
		if(sel >= 1 && sel <= 4)
			num++;
		//ͨ��ѡ�������ٶ�
		if(1 == sel)
		{
			char a;
			std::cin>>a;
			bz = 0;
			Add(&bz,1);
			Add(&a,sizeof(a));
		}
		else if(2 == sel)
		{
			int a;
			std::cin>>a;
			bz = 1;
			Add(&bz,1);
			Add(&a,sizeof(a));
		}
		else if(3 == sel)
		{
			double a;
			std::cin>>a;
			bz = 2;
			Add(&bz,1);
			Add(&a,sizeof(a));
		}
		else if(4 == sel)
		{
			char a[256];
			std::cin>>a;
			bz = 3;
			Add(&bz,1);
			Add(a,strlen(a) + 1);
		}
		else if(5 == sel)
		{
			break;
		}
	}

	char filename[256];
	std::cin>>filename;

	FILE* pf =0 ;
	//�ļ�����д
	fopen_s(&pf,filename,"wb");
	fwrite(&num,1,sizeof(int),pf);
	fwrite(address,1,length,pf);
	fclose(pf);
	End();
}

void f4_2()
{
	char filename[256];
	std::cin>>filename;
	FILE* pf = 0;
	fopen_s(&pf,filename,"rb");
	if(!pf)
		return;
	fseek(pf,0,SEEK_END);
	//��ȡ���ֽ���
	int filesize = ftell(pf);
	rewind(pf);
	char* p = (char*)malloc(filesize);
	fread(p,1,filesize,pf);
	fclose(pf);
	char* q = p + 4;
	//ͨ��BZ�����Ͷ�����ΪBZռһ���ֽڣ��������е����Ͷ�Ҫ��һ���ֽ�
	for(int i = 0; i < *((int*)p);++i)
	{
		switch(*q)
		{
		case 0:
			{
				std::cout<<*(q + 1)<<std::endl;
				q += 2;
			}
			break;
		case 1:
			{
				std::cout<<*((int*)(q + 1))<<std::endl;
				q += 5;
			}
			break;
		case 2:
			{
				std::cout<<*((double*)(q + 1))<<std::endl;
				q += 9;
			}
			break;
		case 3:
			{
				std::cout<<q + 1<<std::endl;
				q += 1 + strlen(q + 1) + 1;
			}
			break;
		}
	}
	free(p);
}

void printbyte(void* p)
{
	unsigned char uc = *((unsigned char*)p);
	int a[2] = {};
	int b = 0;
	//��ӡ16����
	while(uc)
	{
		a[b++] = uc % 16;
		uc /= 16;
	}
	const char* _16 = "0123456789abcdef";
	std::cout<<_16[a[1]]<<_16[a[0]];
}
//�༭����
void edit()
{
	char fn[256];
	std::cin>>fn;
	FILE* pf =0 ;
	fopen_s(&pf,fn,"rb");
	if(!pf)
		return;
	fseek(pf,0,SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	//���ٶ�
	char* fd = (char*)malloc(fs);
	fread(fd,1,fs,pf);
	fclose(pf);

	int allpage = fs / 256;
	//ҳ��
	if(fs % 256 != 0)
		allpage ++;

	int curpage = 1;
	while(1)
	{
		system("cls");
		char* p = fd + (curpage - 1)* 256;
		std::cout<<"���ֽ�["<<fs<<"]  ��ǰҳ��["<<curpage<<"/"<<allpage<<"]"<<std::endl;
		for(int i = 0; i < 256; ++i)
		{
			if(i % 16 == 0)
			{
				void* q = (void*)((p + i) - fd);
				std::cout<<q<<" ";
			}
			printbyte(p + i);
			std::cout<<' ';
			if( i % 16 == 15)
				std::cout<<std::endl;
			if((curpage - 1)* 256 + i > fs)
			{
				std::cout<<std::endl;
				break;
			}
		}
		std::cout<<"01)��ת\n02)�༭\n03)���\n04)�˳�\n��ѡ��:";
		int sel;
		std::cin>>sel;
		if(1 == sel)
		{
			do
			{
				std::cin>>curpage;
			}while(curpage < 1|| curpage > allpage);
		}
		//�޸��ֽ�
		else if(2 == sel)
		{
			int index,byte;
			do
			{
				std::cin>>index>>byte;
			}while(index < 0||index >= fs || byte < 0||byte > 255);
			fd[index] = (char)byte;
			std::cout<<"�޸ĳɹ�";
			system("pause");
		}
		//�޸Ĳ�����
		else if(3 == sel)
		{
			char fn[256];
			std::cin>>fn;
			FILE* pf = 0;
			fopen_s(&pf,fn,"wb");
			fwrite(fd,1,fs,pf);
			fclose(pf);
			std::cout<<"����ɹ�";
			system("pause");
		}
		else if(4 == sel)
			break;
	}
	free(fd);
}

void main()
{	
	//f1_2();
	//f2_2();
	//f3_1();
	//f3_2();
	//f4_1();
	//f4_2();

	while(1)
	{
		system("cls");
		std::cout<<"01)��\n02)�˳�\n��ѡ��:";
		int sel;
		std::cin>>sel;
		if(1 == sel)
			edit();
		else
			break;
	}

	system("pause");
}