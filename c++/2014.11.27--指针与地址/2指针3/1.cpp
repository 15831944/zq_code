#include<iostream>


void main()
{
	int a1,b1,c1;//a1,b1,c1��int���͵ı���
	int* a2,b2,c2;//a2��int���͵�ָ�룬b2,c2��int���͵ı���
	//int *a2;
	//int b2;
	//int c2;
	a2 = &a1;
	//b2 = &b1;
	//c2 = &c1;
	a2 = &b2;
	a2 = &c2;

	int *a3,*b3,*c3;//a3,b3,c3����int���͵�ָ��
	a3 = &a1;
	b3 = &b1;
	c3 = &c1;
	system("pause");
}