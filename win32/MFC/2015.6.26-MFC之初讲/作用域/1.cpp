#include <iostream>

int a;
class X
{
public:
	int a;
	void f(int a)
	{
		a = 1; //�β�a
		this->a = 1; //��Ա����a
		::a = 1; //ȫ�ֱ���a
	}
};

void ff()
{
	std::cout<<"ff"<<std::endl;
}
class B
{
public:
	void ff()
	{
		std::cout<<"B::ff"<<std::endl;
	}
	void y()
	{
		ff();
		::ff();
	}
};

void main()
{
	B b;
	b.y();

	system("pause");
}