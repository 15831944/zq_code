#include <iostream>
#include <assert.h>

//Ҫ����������������һ������������ȡ����������
int get_int_from_float(float num)
{
	//�������������ֵǿת
	//return (int)num;

	//����������ĵ�ַǿת
	int* p = (int*)&num;
}

void main()
{
	float a = 13.125f;

	system("pause");
}