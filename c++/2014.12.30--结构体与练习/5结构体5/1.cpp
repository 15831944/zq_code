#include<iostream>

struct _ABC
{
	char a;
	short b;
	int c;
};

struct _DEF
{
	char a;
	short b;
	char* c;
};

//�ṹ������ĵ�ַ���ܸ�ֵ���ǽṹ��ָ��
void main()
{
	_ABC x;//?? ?? ?? ?? ?? ?? ?? ?? 

	int* p = &(x.c);//int������ֵ��intָ��

	//int* q = &x;//_ABC���͵ĵ�ַ���ܸ�ֵ��int����ָ��
	//char* q = &x;
	//short* q = &x;
	//bool* xx = &x;

	p[-1] = 0;//00 00 00 00  ?? ?? ?? ?? 
	p[0] = -1;//00 00 00 00  ff ff ff ff
	//00000000 00000000 00000000 00000001
	//11111111 11111111 11111111 11111110
	//11111111 11111111 11111111 11111111
	//ff ff ff ff

	_DEF y;
	y.c = &y.a;
	*(y.c) = 'a';
	y.a = 'b';
	y.c[1] = y.c[2] = y.c[3] = 3;

	system("pause");
}
