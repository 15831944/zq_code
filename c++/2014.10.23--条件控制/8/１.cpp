#include<iostream>

//do-while
//while
//for

void main()
{
	std::cout<<"��ʼ��"<<std::endl;

	int a;
	std::cout<<"������һ������0����:";
	std::cin>>a;
	int i;
	//while(a <= 0 && i < 3)
	//{
	//	std::cout<<"������һ������0����:";
	//	std::cin>>a;
	//	++i;
	//}

	
	//for(A;B;C)
	//{
	//	D;
	//}
	//G;
	//01)��ִ�У�
	//02)�ж�B
	//03)���BΪ����ִ��D
	//04)ִ��C Ȼ���ظ�02)��04)����
	//05)���BΪ�٣�������ѭ��ִ��G��

	for(i = 0; i < 3; ++i)
	{
		if(a <= 0)
		{
			std::cout<<"������һ������0����:";
			std::cin>>a;
		}
	}

	std::cout<<"������"<<std::endl;


	//70%����������д��
	for(int j = 0; j < 10; ++j)
	{
		
	}

	//for(;;)
	//{
	//	
	//}

	//for(;B;C)
	//{}

	//for(;B;)
	//{}

	//A��B��C��һ��д��������
	//�����������Ŀ���

	system("pause");
}