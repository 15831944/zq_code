#include<iostream>

//do-while
//while
//for

void main()
{
	//while(A)
	//{
	//	B;
	//}
	//G;
	//01)ִ��A���ж�A����١�
	//02)��AΪ�棬ִ��B��Ȼ���ظ�01)-02)����
	//03)��AΪ�٣���ִ��G

	//do-whileҪ��while��ִ��һ��

	std::cout<<"��ʼ��"<<std::endl;

	int a;
	std::cout<<"������һ������0����:";
	std::cin>>a;
	while(a <= 0)
	{
		std::cout<<"������һ������0����:";
		std::cin>>a;
	}

	std::cout<<"������"<<std::endl;

	//while(1)
	//{
	//	
	//}

	system("pause");
}