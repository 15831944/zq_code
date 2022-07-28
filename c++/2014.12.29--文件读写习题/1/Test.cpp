#include<iostream>
#include "Test.h"

int size = 0;
int length = 0;
char* address = 0;

void Init()
{
	//��ʼ���ڴ��С
	size = 8;
	//�������ڴ��С
	length = 0;
	//���ٳ�ʼ��С�ռ�Ķ�
	address = (char*)malloc(size);
}

void End()
{
	//�ͷŶ��ڴ�
	if(address)
		free(address);
}

void Add(void* p ,int c)
{
	//��ǰ�ѿռ䲻������չ�ռ�
	if(size - length < c)
	{
		//������ǰ������С�Ķ�
		size += c;
		size *= 2; 
		//���µ�ָ�뿪�ٶ�
		char* q = (char*)malloc(size);
		//�Ѿɶѵ��ڴ濽��length����С���¶�
		memcpy(q,address,length);
		//�ͷžɶ�
		free(address);
		//����ָ�븳ֵ��ָ��
		address = q;
	}
	//����C���ֽڵ��ɶ�
	memcpy(address + length,p,c);
	//�ܴ�С����C��
	length+=c;
}