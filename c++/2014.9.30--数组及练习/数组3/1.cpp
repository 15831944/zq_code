#include <iostream>

//sizeof
//1)���Եõ�һ��������ռ���ֽڵ�����
//2)���Եõ�һ�����ʽ�����ռ���ֽڵ�����
//3)��sizeof��������ͬһ������,��sizeof(��
//  ����)���Եõ����������ܴ�С(���ֽ���)

void main()
{
	int a[5];
	std::cout<<sizeof(a)<<std::endl; //sizeof(int) * ���鳤��  sizeof (a) / sizeof (int)  ����Ԫ�صĳ���

	double b[3];

	std::cout<<sizeof(b)<<std::endl;
	

	system("pause");
}