#include<iostream>

class A
{
	char* p;
public:
	A()
	{
		p = new char;
	}
	~A()
	{
		delete p;
	}
};
void main()
{
	
	A a1;
	{
	A a2 = a1;//����Ĭ�ϵı������ṩ�Ŀ�������
	}

	//A a1;
	//A a2;
	//a1 = a2;//����Ĭ�ϵı������ṩ��ͬ�ำֵ


	system("pause");
}