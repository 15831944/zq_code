// Test1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "vector"

class A
{
public:
	A(){std::cout<<"A����"<<std::endl;}
	~A(){std::cout<<"A����"<<std::endl;}
};
class C
{
public:
	C(){std::cout<<"C����"<<std::endl;}
	~C(){std::cout<<"C����"<<std::endl;}
};
class B
{
public:
	A a;
	C c;
	B(){std::cout<<"B����"<<std::endl;}
	~B(){std::cout<<"B����"<<std::endl;}
};

void f()
{
	B b;

	//����sizeof(B)��С���ڴ�
	//ִ��b.a��b.c��b�Ĺ���
	//ʹ����������
	//ִ��b��b.c��b.a������
	//�ͷ��ڴ�
}

int _tmain(int argc, _TCHAR* argv[])
{
	f();

	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	std::vector<int*> u;
	u.push_back(new int[3]);
	u.push_back(new int[2]);
	u.push_back(new int[1]);
	for (int i = 0; i < u.size(); ++i)
		delete [] u[i];

	//class CTestDlg
	//{
	//	std::vector<_TX> tx1;
	//	std::vector<_TX> tx2;
	//	std::vector<_TX> tx3;
	//};
	//����������CTestDlg��ʱ�򣬻�ִ�����������
	//��tx1��tx3��������Ȼ����һ�����ͷ�CTestDlg
	//��ռ�ݵ��ڴ�

	return 0;
}

//��������B�а�������A�Ķ�����ô����B�����ʱ��B
//�е�A����Ҳ�ᱻִ�й��죬������B����֮ǰ��A����Ҳ��
//������

