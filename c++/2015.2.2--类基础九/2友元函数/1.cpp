#include <iostream>

//��Ԫ
//��Ԫ��һ�ִ��Ʒ�װ�Ե����������ƻ�ԭ��
//��˽�з���Ȩ�ޣ�
//�����ǵ����еĳ�Աϣ���Բ��ֺ����ǹ���
//�����ⲿ�ֺ�����˽�еĻ�����ô���ǾͿ���ʹ��
//��Ԫ��
//��Ԫ�����������ö��
class A
{
	int a;

	friend void f();
	friend void f1();
	friend void f2();
	friend void f3();

};

void f()
{
	A x;
	x.a = 1;
}


void main()
{
	A x;
	//x.a= 1;
	f();
	system("pause");
}