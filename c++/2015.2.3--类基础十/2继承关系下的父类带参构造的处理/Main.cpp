#include <iostream>

class A
{
public:
	A(int a)
	{}
};

class B
{
	A x;
public:
	B()
		:
	x(1)
	{
	}
};

class C
{
	A x;
public:
	C(int y)
		:
	x(y)
	{
		
	}

};

class D:public A
{
public:
	D()
		:
	A(1)//ʹ�ó�Ա��ʼ���б�Ϊ���๹�촫�ݲ���
	{
	}
};

class E:public A
{
public:
	E(int y)
		:
	A(y)
	{}
};

//������ϵ��B����A C����A
//�̳У�D�̳���A��E�̳�A
//�������ֹ�ϵ��,���A�Ĺ���Ҫ���вΣ������ʹ��
//��Ա�б��ʼ���б������г�ʼ��������ǰ�����ϵ
//ʹ�ñ������ģ���Ķ��󣩳�Ա������������Ǽ̳У���ʹ�ø��������
void main()
{
	B b;
	C c(7);
	D d;
	E e(1);
	system("pause");
}