#include<iostream>

int a;
void f1()
{
	int a;
	a = 1;//�ֲ�a
	::a = 2;//ȫ��a
}

class A
{
	int a;
public:
	void f2()
	{
		int a;
		a = 1;//�ֲ�
		this->a = 2;//��Ա
		::a = 3;//ȫ��
	}
};


void main()
{
	A x;
	x.f2();
	system("pause");
}
