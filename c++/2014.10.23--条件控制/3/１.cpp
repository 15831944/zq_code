#include<iostream>


void main()
{
	int a;
	std::cin>>a;

	//switch(a)
	//{
	//case 1:
	//	{
	//		std::cout<<"1"<<std::endl;
	//	}
	//	break;
	//case 2:
	//	{
	//		std::cout<<"2"<<std::endl;
	//	}
	//	break;
	//default:
	//	{
	//		std::cout<<"����"<<std::endl;
	//	}
	//	break;
	//}

	if(a == 1)
	{
		std::cout<<"1"<<std::endl;
	}
	else if(a == 2)
	{
		std::cout<<"2"<<std::endl;
	}
	else
	{
		std::cout<<"����"<<std::endl;
	}

	//if(A)
	//{
	//	B;
	//}
	//else if(C)
	//{
	//	D;
	//}
	//........
	//else
	//{
	//	F;
	//}
	//G;
	//ִ�б��ʽA�����A�Ľ��Ϊ����ִ�б��ʽB;Ȼ��ִ��G��
	//������ʽAΪ�٣���ִ��C
	//���C�Ľ��Ϊ����ִ�б��ʽD;Ȼ��ִ��G��
	//������ʽCΪ�٣���ִ�к����else if()�еı��ʽ��
	//���һֱΪ�٣������ִ��F��Ȼ��ִ��G
	//������棬��ִ�и�Ϊ����ж��������Ǹ�{}�е����Ȼ��
	//ִ��G
	

	system("pause");
}