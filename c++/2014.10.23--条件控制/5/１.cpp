#include<iostream>


void main()
{
	int a;
	std::cin>>a;

	if(a > 0)
	{
		std::cout<<"����0"<<std::endl;
		if(a > 10)
		{
			std::cout<<"����10"<<std::endl;
		}
	}
	else if(a == -4)
	{
		std::cout<<"����0"<<std::endl;
	}
	else if(a == -10)
	{
		std::cout<<"С��0"<<std::endl;
	}

	//if(A)
	//{
	//	B;
	//}
	//else if(C)
	//{
	//	D;
	//}
	//.........
	//else if(E)
	//{
	//	F;
	//}
	//G;
	//���ж�A�����AΪ�棬��ִ��B��Ȼ��ִ��G
	//���AΪ����ִ��C,��CΪ��ʱִ��D��Ȼ��ִ��G
	//���CΪ�������ִ�������else if()�е�
	//���ʽ��һֱΪ����ֱ��ִ��G��
	//һ�����棬��ֻ���else if������{}�е����ݣ�
	//Ȼ��ִ��G
	//���ܻ���һ����ִ�еĵ�

	system("pause");
}