#include <iostream>

class A
{
public:
	A()
	{
		std::cout<<"�޲ι���"<<std::endl;
	}
	A(int a)
	{
		std::cout<<"���ι���"<<std::endl;
	}
	~A()
	{
		std::cout<<"����"<<std::endl;
	}
};

//�ھ�̬���е��ô��ι���
A  a2(2);

void main()
{
	{
	//ջ�еĴ��ι������
	A a1(1);

	//�ھ�̬���е��ô��ι���
	static A a3(3);
	}

	A* a4 = new A;//����ִ���޲ι���

	A* a5 = new A(5);//����ִ�д��ι���

	delete a4;
	delete a5;

	A* a6 = new A[5];//���е������޲ι���
	system("pause");
}