#include<iostream>

void f1(int a)
{
	a = 2;
}

//void f2(int* a)
//{
//	*a = 2;
//}

void f2(int& a)
{
	a = 2;
	int b = a;
}

void f3(const int& a)
{
	//a = 2;//a�����ã�Ҳ�Ǳ����ı�����ֻ�ܶ�
	int b = a;
}

void main()
{
	int x = 1;
	f1(x);
	std::cout<<x<<std::endl;
	f2(x);
	std::cout<<x<<std::endl;
	f1(x);

	f1(1);
	//f2(1);//ֻ�ܸ�����ȡ����
	system("pause");
}