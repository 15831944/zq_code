#include <iostream>
int a;
class A
{
public:
	int a;
	void f(int a)
	{
		a = 1;
		this->a = 1;
		::a = 2;
	}
};

class B : public A
{
public:
	int a;
	void b(int a)
	{
		a = 1;
		this->a = 2;//B�ĳ�Ա����a
		A::a = 4;//A�ĳ�Ա����a
		::a = 4;
	}
};

void main()
{
	A x;
	x.a = 1;
	B y;
	y.a = 1;
	y.A::a = 3;//����A�ж����a

	B* y1 = &y;
	y1->A::a = 5;//����A�ж����a
	system("pause");
}