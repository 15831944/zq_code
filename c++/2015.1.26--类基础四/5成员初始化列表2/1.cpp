#include <iostream>

//ֻ���ǹ���ʹ�ó�Ա��ʼ���б�
//��Ա��ʼ���б���д�ĳ�Ա��������ʼ��
//��Ա��ʼ���б��ʼ����˳���ǳ�Ա������˳��

class A
{
	int a,b;
	const int c;//���еķ��ų���
	int& d;//���е�����
public:
	A()
	:
	a(1),c(3),d(a)
	{
		b = 2;//�����Ǹ�ֵ
		//c = 3;//����
		//��Ա�������з��ų����Ļ��������ͨ����Ա
		//��ʼ���б���г�ʼ��
	}

	//void f()
	//:
	//a(1)
	//{}
};


class B
{
	int* p;
	int a;
public:
	B()
	:
	a(5),p(new int[a])
	{}
};

class C
{
	int a;
	int* p;
public:
	C()
	:
	p(new int[a]),a(5)
	{}
};


void main()
{
	A x;
	//B b;

	C c;
	system("pause");
}
