#include<iostream>

//�ڴ����

void main()
{
	//01)

	//��dest��ʼ�ĵ�ַ�����count���ֽڸ�ֵΪ
	//c�ĵ�һ���ֽڣ�����dest
	//void* memset(void* dest,int c,size_t count);

	char s[100];
	memset(s,0xaabbccdd,100);


	//02)

	//��src��ʼ�ĵ�ַ�����count���ֽڸ�ֵ��dest��ַ����
	//��count���ֽ���
	//void* memcpy(void* dest,const void* src,size_t count);
	
	int a = 0;
	char b[6] = {1,2,3,4};

	memcpy(&a,b,3);

	std::cout<<a<<std::endl;
	
	system("pause");
}