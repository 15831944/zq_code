#include <iostream>
#include <windows.h>
//a����
//b����
//y����
//x����
//z����
//g����
//g�ͷ�
//x�ͷ�
//y�ͷ�
//y����
//x����
//g����
//g�ͷ�
//x�ͷ�
//y�ͷ�
//b�ͷ�
//z�ͷ�
//a�ͷ�
int f(int x, int y)
{
	static int z;
	z = x + y;
	int g = z;
	return g;
}
extern int a;
void main()
{
	int b = f(1, 2);
	a = b;
	a = f(3, 4);
	
	system("pause");
}
int a;