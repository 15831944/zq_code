#include <iostream>

class A1
{
};

class B1
{
public:
	A1 a1;
};

//class A2
//{
//public:
//	A2(int q)
//	{}
//};
//
//class B2
//{
//public :
//	A2 a2;
//};

class A3
{
	public:
	A3(int q)
	{}
};

class B3
{
public :
	A3 a3;

	//������﷨�ṹ��֮Ϊ��Ա��ʼ���б�
	//���ǿ���ͨ����Ա��ʼ���б�Ϊֻ�д���
	//����ĳ�Ա�������ݹ�������Ҫ�Ĳ���
	B3()
	:
	a3(1)
	{}
};


class A4
{
public:
	A4(int q)
	{}
};

class B4
{
public:
	A4 a4;
	B4(int t)
	:
	a4(t)
	{
	
	}
};

void main()
{
	B1 x1;

	//B2�е�A2���͵ĳ�Ա����a2����Ҫ���β���
	//��������εĹ��캯��������������д���޷�
	//��a2����
	//B2 x2;

	B3 x3;

	//2���ݸ�t��֮���ִ��ݸ�x4�е�a4���й���
	B4 x4(2);
	system("pause");
}
