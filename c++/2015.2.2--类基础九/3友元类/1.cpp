#include <iostream>

class A
{
	int a;
	friend class B;

public:
	A();
	
};

class B
{
	int b;
public:
	B()
	{
		A x;
		x.a = 1;
	}

	void f()
	{
		A x;
		x.a = 1;
	}
};

//A::A()
//{
//	{
//		B b;
//		b.b = 1;
//	}
//}
void main()
{
	//��Ԫ�ǵ���ģ�B��A����Ԫ��A����B����Ԫ
	//����B�г�Ա�����ܷ���A��˽�г�Ա����A
	//�еĳ�Ա���ܷ���B�е�˽�г�Ա
	system("pause");
}