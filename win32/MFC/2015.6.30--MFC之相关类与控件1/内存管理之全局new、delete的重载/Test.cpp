#include <iostream>

class A
{
public:
	A(){std::cout<<"A����"<<std::endl;}
	~A(){std::cout<<"A����"<<std::endl;}
};

void main()
{
	//new ����;
	//����ı��ʽ����Ϊnew������ʽ��new������ʽ��ִ����������
	//1��ȥѰ��ȫ�ֵ�new�������������ڴ�
	//2��ִ�й���

	//delete ��ַ;
	//����ı��ʽ����Ϊdelete������ʽ��delete������ʽ��ִ����������
	//1��ִ������
	//2��ȥѰ��ȫ�ֵ�delete��������ͷŶ��ڴ�

	int* p = new int;
	int* q = new int[2];
	delete p;
	delete [] q;

	A* r = new A;
	delete r;

	system("pause");
}