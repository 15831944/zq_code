#include<iostream>

//do-while
//while
//for

void main()
{
	//do
	//{
	//	A;
	//}while(B);
	//G;
	//01)ִ��A
	//02)ִ��B����BΪ��ʱ������01)-02)����
	//03)��BΪ��ʱ������ѭ��ִ��G

	std::cout<<"��ʼ��"<<std::endl;

	int a;
	do
	{
		std::cout<<"������һ������0����:";
		std::cin>>a;
	}while(a <= 0);

	std::cout<<"������"<<std::endl;

	system("pause");
}