#include <iostream>

//�̳�
//���������Զ�ӵ�и���ĳ�Ա�����ͳ�Ա����

class A
{
public:
	int a1;
	void a2()
	{
		std::cout<<"A��a2����"<<std::endl;
	}
};

//������BΪ��A�����࣬AΪB�ĸ���(���࣬���ࡣ����)

class B : public A
{

};

//B�ᱻ����������Ϊ
//class B
//{
//public:
//	int a1;
//	void a2()
//	{
//		std::cout<<"A��a2����"<<std::endl;
//	}
//};
class C
{
public:
	int c1;
	void c2()
	{
		std::cout<<"C��c2����"<<std::endl;
	}
};

class D : public C
{
public:
	int d1;
	void d2()
	{
		std::cout<<"D��d2����"<<std::endl;
	}
};

//����������Ϊ
//class D 
//{
//public:
//	int c1;
//	void c2()
//	{
//		std::cout<<"C��c2����"<<std::endl;
//	}
//	int d1;
//	void d2()
//	{
//		std::cout<<"D��d2����"<<std::endl;
//	}
//};
void main()
{
	B a;
	a.a2();
	D d;
	d.c1 = 1;
	d.c2();
	d.d1 = 1;
	d.d2();
	system("pause");
}