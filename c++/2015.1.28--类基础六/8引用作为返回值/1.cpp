#include<iostream>

int a;
int f1()
{
	return a;
}

//����ֵ�Ǳ�ȫ�ֱ���a��ʼ��������
int& f2()
{
	return a;
}

int& f3()
{
	//�þֲ���a��ʼ������
	//�õ�һ���Ѿ������ĺ�����ջ�ڴ��еı���û������
	int a = 0;
	return a;
}


int& f4()
{
	int* a = new int;
	*a = 0;
	return *a;
}
void main()
{
	//f1() = 1;
	f2() = 1;
	f3() = 2;

	delete &(f4() = 3);
	system("pause");
}