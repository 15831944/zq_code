#include <iostream>

//һ����˵ʹ���麯�����Ƕ���һ������ָ���������ͨ��װ��
//����������еĸ���ָ��ȥָ��ͬ���������

class A
{
public:
	int a;
};
class B : public A
{
public:
	int b;
};
class C : public A
{
public:
	int c;
};

class X
{
public:
	X(){std::cout<<"X����"<<std::endl;}
	~X(){std::cout<<"X����"<<std::endl;}
};
class Y : public X
{
public:
	Y(){std::cout<<"Y����"<<std::endl;}
	~Y(){std::cout<<"Y����"<<std::endl;}
};

class U
{
public:
	U(){std::cout<<"U����"<<std::endl;}

	//���ü̳���ϵ�¸��������Ϊ����������ô��ʹ��
	//��delete����ָ���ʱ�򣬱������ܹ���ȷ�İѴ�
	//���ൽ�������������������ִ��
	virtual ~U(){std::cout<<"U����"<<std::endl;}
};
class V : public U
{
public:
	V(){std::cout<<"V����"<<std::endl;}
	~V(){std::cout<<"V����"<<std::endl;}
};

//Y y1; //ֱ�Ӷ��徲̬������ô���졢������ִ����ȷ

void main()
{
	B b; b.a = 1; b.b = 2;
	C c; c.a = 3; c.c = 4;

	//����������鱻�����ʼ��֮��Ҳ�޷�����
	//���������Ĳ��֣��൱�ڽ�ȡ��������ӵ��
	//�ĸ���Ĳ��ֽ��г�ʼ����ֵ���������
	A x[] = {b, c};

	//y[0]��y[1]��A����ָ�룬�ֱ�ָ����b��c�ĵ�ַ
	A* y[] = {&b, &c};

	//Y y2; //ֱ�Ӷ���ջ������ô���졢������ִ����ȷ

	//ֱ�Ӷ���Ѷ����õ�ǰ��ָ��ָ����ô���졢������ִ����ȷ
	//Y* y3 = new Y;
	//delete y3;

	//ֱ�Ӷ���Ѷ����õ�ǰ��ĸ���ָ��ָ����ô����ִ����ȷ������ִ�д���
	X* y4 = new Y;
	delete y4; //��Ϊdelete���Ǹ���ָ�룬����ֻ��ָ���������

	U* p = new V;
	delete p;

	system("pause");
}