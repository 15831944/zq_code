#include<iostream>

//typedef

//�����Ǹ����������,��typedef�ؼ����Ǹ�����
//ȡ����

//Ϊint����ȡ��һ��������MyInt
typedef int MyInt;

//Ϊint*����ȡ��һ��������pMyInt
typedef int* pMyInt;

//p��һ��ȫ�ֵĺ���ָ��
int (*p)(int,int);

//q��һ������ָ�����ͣ����;���int(*)(int,int)
typedef int (*q)(int,int);

int add(int a,int b)
{
	return a + b;
}

struct ABC1
{
	int a,b,c;
}x1,*y1,z1[3];//x1,y1,z1�ֱ���ȫ�ֱ�����ȫ��ָ�룬ȫ������

typedef struct ABC2
{
	int a,b,c;
}x2,*y2;//x2,y2�ֱ���ABC2���ͣ�ABC2*���͵ı���


void main()
{
	MyInt i = 1;//��ȫ��ͬ��int i = 1;
	pMyInt j = &i;//��ȫ��ͬ��int* j = &i;
	p = add;
	//x��q���������һ������ָ��
	//�൱��int (*x)(int,int) = add
	q x = add;

	x2 t;
	y2 tt = &t;
	system("pause");
}