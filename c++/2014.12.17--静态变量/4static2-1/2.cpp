#include <iostream>

int x1;
void y1()
{
	std::cout<<x1<<std::endl;
}
//static�÷�2:����ȫ�ֱ����ͺ���
//01)��static���ε�ȫ�ֱ����ͺ��������ӵ�ʱ��
//�������������̿ɼ�,ֻ������Դ�ļ��ɼ�,Ҳ����
//˵�����x2,y2�Ķ��������ӵ�ʱ���ܱ�1.cpp��
//�ĺ������֣�ֻ�ܱ�2.cpp�еĺ�������
//02)�򵥵�˵���Ǳ�static���ε�ȫ�ֱ���������ֻ
//�ܱ������ڵ�Դ�ļ��еĺ�������.

static int x2;

static void y2()
{
	std::cout<<x1<<std::endl;
}

void z()
{
	x2 = 200;
	y2();
}

//ͨ��static����������
static int a[10];
int* GetNum(int index)
{
	if(index < 0 || index >= 10)
		return 0;
	else
		return a + index;
}

void SetNum(int index,int Number)
{
	if(index < 0 || index >= 10)
		return;
	else
		a[index] = Number;
}



