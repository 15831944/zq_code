#include<iostream>
//�ݹ�
//������Ĭ�ϲ���
//����������
//����ָ��

int add1(int a,int b)
{
	return a + b;
}

int add2(int a = 1,int b = 2)
{
	return a + b;
}

int sub2(int a,int b = 2)
{
	return a - b;
}

//ʵ�ʲ��������Ǵ����ұ���ʽ�����������ʽ����д
//���м䲻���и���
//int mul2(int a = 1,int b)
//{
//	return a * b;
//}

//int add3(int a = 1,int b,int c = 3)
//{
//	return a + b + c;
//}

void main()
{
	//add2(int a = 3,int b = 4)
	std::cout<<add2(3,4)<<std::endl;
	//add2(int a = 3,int b = 2)
	std::cout<<add2(3)<<std::endl;
	//ֻ��������ʽ����a��ʵ�Σ���ʽ����bʹ��Ĭ�ϲ���
	std::cout<<add2()<<std::endl;
	//a��b ��û��ʵ�ʲ��������Զ�ʹ����Ĭ�ϲ���
	std::cout<<sub2(4)<<std::endl;

	//std::cout<<mul2(4,3)<<std::endl;

	system("pause");
}