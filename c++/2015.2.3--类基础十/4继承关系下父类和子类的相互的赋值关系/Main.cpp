#include <iostream>

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

void main()
{
	A x;
	x.a = 1;
	B y;
	y.a = 2;
	y.b = 3;

	x = y;//������� = �������
	//y = x;

	A* p1 = &y;//����ָ�� = �������ĵ�ַ
	//B* p2 = &x;

	A& r1 = y;//�������� = ����Ķ���
	//B& r2 = x;

	//д�� = ��ߵ�ֻ���Ǹ��࣬д��
	//= �ұߵ�ֻ��������
	system("pause");
}