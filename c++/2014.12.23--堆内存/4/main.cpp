#include<iostream>

////p�Ƕ��ڴ棬p��qû���κεĹ�ϵ
//void f(char* p)
//{
//	p = (char*)malloc(10);
//}

void f(char** p)
{
	*p = (char*)malloc(10);
}

void main()
{
	char* q = 0;
	//f(q);
	f(&q);
	strcpy_s(q,4,"abc");
	std::cout<<q<<std::endl;
	system("pause");
}