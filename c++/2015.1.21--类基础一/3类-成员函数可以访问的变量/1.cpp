#include<iostream>

int c1;

void f1(int a1)
{
	int b1;//��ͨ�������Է���ȫ�ֱ������βΣ��ֲ�����
	a1 = 1;
	b1 = 1;
	c1 = 1;
}

int c2;
class XYZ
{
public:
	int d2;
	void f2(int a2)
	{
		//��Ա�������Է����βΣ��ֲ�������ȫ�ֱ�������Ա����.
		int b2;
		a2 = 2;
		b2 = 2;
		c2 = 2;
		d2 = 2;
	}
};

void main()
{
	f1(3);

	XYZ xyz;
	xyz.f2(2);
	system("pause");
}