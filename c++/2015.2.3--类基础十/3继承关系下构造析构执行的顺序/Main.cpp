#include <iostream>

class A
{
public:
	A()
	{
		std::cout<<"A���๹��"<<std::endl;
	}
	~A()
	{
		std::cout<<"A��������"<<std::endl;
	}
};

class B : public A
{
public:
	B()
	{
		std::cout<<"B���๹��"<<std::endl;
	}
	~B()
	{
		std::cout<<"B��������"<<std::endl;
	}
};

class C : public B
{
public:
	C()
	{
		std::cout<<"C���๹��"<<std::endl;
	}
	~C()
	{
		std::cout<<"C��������"<<std::endl;
	}
};

C c;

//�̳е���ϵ�£�һ����������������
//01)�����ڴ�
//02)ִ�й��죺��ִ�����ĸ���Ĺ���
//��Ȼ����ִ�д�һ��ĸ��๹�죬.....��
//  �����ִ�е�ǰ����Ĺ���
//03)ʹ�������
//04)��ǰ����������Ȼ������������......
//����������ĸ���
//05)�ͷ��ڴ�

//�����������ڸ���ĳ�ʼ����Ҳ����˵
//����Ĺ���Ҫ�ڸ���Ĺ���֮����Ϊ
//�����õ������ʼ�����һЩ���

void main()
{
	C* p = new C;
	delete p;
	system("pause");
}