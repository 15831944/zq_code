#include <iostream>

int add(int a,int b)
{
	return a + b;
}
class A
{
public:
	int sub(int a,int b)
	{
		return a - b;
	}
	int mul(int a,int b)
	{
		return a * b;
	}
};

void main()
{
	int (*p)(int,int) = add;
	//p = A::mul;
	//A�е�mul��sub������һ�����ص�ָ��this
	//ʵ�ʻᱻ����Ϊ
	//int sub(A* this,int a,int b);
	//pָ��Ҫ��ָ�������ʽ����Ϊ(int,int)��
	//����ֵΪint�ĺ���,���Բ���ָ��A������������
	
	// �޷��ӡ�int (__thiscall A::* )(int,int)��
	//ת��Ϊ��int (__cdecl *)(int,int)��
	
	//int (*p1)(A*,int,int) = &A::mul;
	//���еĳ�Ա�����ĵ�ַ��д��
	// &����::��Ա������


	//���еĳ�Ա����ָ��Ķ�������
	//����ֵ(����::*ָ����)(��ʽ������)

	//�����p1��ָ��һ��A���еĳ�Ա������ָ�룬
	//�Ҹó�Ա���������Ƿ���ֵΪint ����ʽ������
	//Ϊ(int,int)�ĺ���
	int (A::*p1)(int,int) = &A::mul;

	p1 = &A::sub;
	//p1 = add;
	//��Ա����ָ�벻��ָ����ͨ����
	//��ͨ����ָ�벻��ָ���Ա����


	A a;

	(a.*p1)(3,4);

	A* a1 = &a;

	(a1->*p1)(1,2);
	system("pause");
}
