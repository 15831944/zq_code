#include<iostream>

class A
{
public:
	A& operator = (const A& that)
	{
		std::cout<<"ͬ�ำֵ"<<std::endl;
		return *this;
	}
};

class B
{
	int x;
public:
	B(int X)
	:
	x(X)
	{}

	B operator = (const B& that)
	{
		x = that.x;
		return *this;
	}
};

class C
{
	int x;
public:
	C(int X)
	:
	x(X)
	{}

	C& operator = (const C& that)
	{
		std::cout<<"Cͬ�ำֵ"<<std::endl;
		x = that.x;
		return *this;
	}
};

void main()
{
	//ͬ�ำֵ�����ϻ���һ������
	A a1;
	A a2;
	a1 = a2;//��ȫ��ͬ��a1.operator = (a2);

	int x = 1,y = 2,z = 3;
	(x = y) = z;
	//��ֵ��������ʽ�Ľ���Ǹ�ֵ���֮����ߵı���
	
	//ͬ�ำֵ������ķ���ֵ��������Ϊ���õ�ԭ��
	//�����ڿ����ø�ֵ��������ʽ�Ľ����������
	// = �����
	//B ���ͬ�ำֵ��������Ľ������һ������
	//����һ����ʱ�����ʹﲻ����C++��ϰ���÷�
	//һ��
	B b1(1),b2(2),b3(3);
	(b1 = b2) = b3;

	C c1(1),c2(2),c3(3);
	(c1 = c2) = c3;
	system("pause");
}