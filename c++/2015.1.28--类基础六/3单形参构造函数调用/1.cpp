#include<iostream>

class A
{
public:
	A()
	{
		std::cout<<"�޲�"<<std::endl;
	}
	A(int a)
	{
		std::cout<<"����"<<std::endl;
	}
	A(int a,int b)
	{
		std::cout<<"����1"<<std::endl;
	}
	A(const char* c)
	{
		std::cout<<"����2"<<std::endl;
	}
};

void main()
{
	A a1;
	A a2(1);
	A a3(1,2);
	//���һ�����캯��ֻ��һ���β�,��ô
	//�ù��캯���ĵ��ÿ����� = ���
	A a4 = 3;

	A a5("abc");

	A a6 = "abc";

	system("pause");
}