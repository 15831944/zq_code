#include <iostream>

//��������������
//�����ڴ�
//ִ�й���
//ʹ�øö���
//ִ������
//�ͷ��ڴ�

class A
{
	int a;
public:
	A(int b)
	{
		a = b;
		std::cout<<a<<"����"<<std::endl;
	}
	~A()
	{
		std::cout<<a<<"����"<<std::endl;
	}
};

A* a4;
void f()
{
	A a2(2);
	static A a3(3);
	a4 = new A(4);
}

void main()
{
	A a5(5);
	f();
	A* a6 = new A(6);
	f();
	delete a4;
	delete a6;
	system("pause");
}

A a1(1);

//a1����
//
//a5����
//a2����
//a3����
//a4����
//a2����
//a6����
//a2����
//a4����
//a2����
//a4����
//a6����
//
//a3����  
//a5����  
//a1����