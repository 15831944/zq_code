#include<iostream>

extern int a;

//ȫ�ֱ������Գ�ʼ��
int a = 2;

void f()
{
	a = 1;
}

void main()
{
	std::cout<<a<<std::endl;
	f();
	std::cout<<a<<std::endl;
	system("pause");
}