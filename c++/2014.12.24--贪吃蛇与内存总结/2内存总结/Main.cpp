#include <iostream>

void f(char** a)
{
	*a = (char*)malloc(10);
}

//ջ
//�����ڴ���
//��̬�ڴ���(ȫ�֣�static���εľֲ�����)
//��

//�����ڴ���
//ָ���ڴ���

void main()
{
	char* p = 0;
	f(&p);
	strcpy_s(p,4,"abc");
	std::cout<<p<<std::endl;
	system("pause");
}