// TestAuto.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//���������ģʽ֮һ�������þ���Ϊ�˰�һ����涨Ϊ
//���ڴ���ֻ��һ��������޷����ɶ�������
class A
{
	//1�����졢������������Ϊ˽��
private:
	A(){}
	A(const A& that){}

	//2���о�̬��Ա����ָ�룬����Ϊָ�����͵�ָ��
	static A* m_Instance;

public:
	//3���й��еġ���̬�ĵõ���������ַ�ĺ���
	static A* getInstance();
};

A* A::m_Instance;
A* A::getInstance()
{
	if (!m_Instance)
		m_Instance = new A;
	return m_Instance;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//A a; //���ù���
	A* p1 = A::getInstance();
	A* p2 = A::getInstance();
	A* p3 = A::getInstance();
	//A b = *p1; //���ÿ�������

	return 0;
}

