#include <iostream>

class A
{
public:
	A()
	{
		std::cout<<"A����"<<std::endl;
	}
	virtual ~A()//������
	{
		std::cout<<"A����"<<std::endl;
	}
};

class B : public A
{
public :
	B()
	{
		std::cout<<"B����"<<std::endl;
	}
	~B()
	{
		std::cout<<"B����"<<std::endl;
	}
};

class C
{
public:
	C()
	{
		std::cout<<"C����"<<std::endl;
	}
	~C()
	{
		std::cout<<"C����"<<std::endl;
	}
};

class D : public C
{
public :
	D()
	{
		std::cout<<"D����"<<std::endl;
	}
	~D()
	{
		std::cout<<"D����"<<std::endl;
	}
};




void main()
{
	//A* pA = new A;
	//delete pA;

	//B* pB = new B;
	//delete pB;

	//delete���Ǹ����ָ�룬����ֻ��ִ�и����
	//��������ִ�����������
	C* pC = new D;
	delete pC;

	//������ִ�е��������������ΪA��������
	//������
	A* pA1 = new B;
	delete pA1;

	
	system("pause");
}

//�ڼ̳���ϵ��(�ر���Ҫʹ�ö�̬)��
//һ�������ĸ������������Ϊ�飬
//�����ܹ���֤delete����ָ���ʱ����
//��ȷ��ִ�����ൽ�����ÿһ����������
//ֻ�������������飬���첻��Ϊ��