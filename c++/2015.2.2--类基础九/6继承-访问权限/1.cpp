#include <iostream>

//����Ȩ��		public		private		protected
//�����Ա����	��			��			��
//�����Ա����	��			��			��
//�ⲿ����		��			��			��	

class A
{
public: //����
	int a1;
protected://����
	int a2;
private://˽��
	int a3;
	void f1()
	{
		a1 = 1;
		a2 = 2;
		a3 = 3;
	}
	friend class C;
};

class B : public A
{
	void f2()
	{
		a1 = 1;
		a2 = 2;
		//a3 = 3;//���ຯ���޷�����˽�г�Ա
	}
};

class C
{
	void f()
	{
		A a;//��Ԫ���Է��ʱ�����˽�к͹��г�Ա
		a.a1 = 1;
		a.a2 = 2;
		a.a3 = 5;
	}
};
void f()
{
	A a;
	a.a1 = 2;
	//a.a2 = 4;//�ⲿ�����޷����ʱ�����Ա
	//a.a3 = 3;//�ⲿ�����޷�����˽�г�Ա
}

void main()
{
	
	system("pause");
}