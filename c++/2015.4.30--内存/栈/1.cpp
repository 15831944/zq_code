#include <iostream>
#include <windows.h>

//x����
//b����
//a����
//c����
//c�ͷ�
//a�ͷ�
//b�ͷ�
//y����
//b����
//a����
//c����
//c�ͷ�
//a�ͷ�
//b�ͷ�
//b����
//a����
//c����
//c�ͷ�
//a�ͷ�
//b�ͷ�
//y�ͷ�
//x�ͷ�

int f(int a, int b)
{
	//���Ƕ���Ǿ�̬�ֲ�������ʱ��Ĭ�϶���auto����
	auto int c = a + b;
	return c;
}

void main()
{
	int x = f(1, 2);
	int y = f(x, f(4, 5));
	
	system("pause");
}