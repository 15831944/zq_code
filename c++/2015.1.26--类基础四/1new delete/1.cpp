#include <iostream>

class A
{
	char x;
	short y;
public:
	A()
	{
		std::cout<<"�޲ι���"<<std::endl;
	}
	A(int a)
	{
		std::cout<<"A�Ĵ��ι���"<<std::endl;
	}
	~A()
	{
		std::cout<<"����"<<std::endl;
	}
};

void main()
{
	//malloc	
	//����sizeof(����)��ô��Ķ��ڴ�ռ�
	A* p0 = (A*)malloc(sizeof(A));

	//�ͷ��ڴ�
	free(p0);

	//new 
	//delete

	//new������
	//1)����sizeof(A)��ô��Ķ��ڴ�ռ�
	//2)ִ�й���
	A* p1 = new A;//4�ֽ�
	//int* a = new int;
	//char* a = new char;
	//double* a = new double;
	//delete������
	//01)��������
	//02)�ͷŶ��ڴ�ռ�
	delete p1;
	//delete a;

	//new ?[num]������
	//01)����sizeof(A)*num�����ڴ�ռ�
	//02)������ÿ���������ִ�й���
	int num = 3;
	A* p2 = new A[num];
	//int* a = new int[10];
	//char* a = new char[10];
	//double* a = new double[10];

	//delete []?������
	//01)����ִ��ÿ������������
	//02)�ͷŶ��ڴ�ռ�
	delete []p2;
	//delete []a
	system("pause");
}