#include <iostream>

class A
{
	const int x;
	//��ĳ�����Ա���뱻��ʼ����
	//ֻ���ó�Ա��ʼ���б���г�ʼ��
public:
	A()
		:
	x(0)
	{}

	int y;
	//������Ա����
	void f2() const
	{
		//������Ա�������ڳ�Ա����ֻ�ܽ���
		//������
		//y = 1;
		int z = y;
	}

	void f3() const;

	void f()
	{}
};

void A::f3() const
{

}

class B
{
public:
	//a��A�ĳ�������
	//����Ǳ�ڵ���˼����a���ܱ��޸�,
	//��ô����a.f()����a�ĳ�Ա��������
	//��ĵ�a�е�����,���Ժܳ������û����
	//ì�ܡ����Ա���
	void f(const A& a)
	{
		//a.f();

		//f2��a�ĳ�����Ա�������������޸ĵ�a��
		//�����ݵģ��������������
		a.f2();
	}

	void f1(A& a)
	{
		a.f();
	}
};

void main()
{
	A a;
	system("pause");
}