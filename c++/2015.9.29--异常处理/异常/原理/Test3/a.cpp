#include <iostream>

class A
{
	int x, y, z;
public:
	A(){x = y = z = 0;}
};

void f1(int i)
{
	std::cout<<"f1��ʼ"<<std::endl;
	try
	{
		std::cout<<"f1-try��ʼ"<<std::endl;
		switch (i)
		{
		case 0: throw true;
		case 1: throw 'A';
		case 2: throw 1;
		case 3: throw 1.0;
		case 4:
			{
				A a;
				throw a;
			}
		case 5:
			{
				throw 1.0f;
			}
		}
		std::cout<<"f1-try����"<<std::endl;
	}
	catch (bool b/*, char x*/) //catch ����������ָ��һ������
	{
		std::cout<<"������bool�쳣"<<b<<std::endl;
	}

	//��������try-catch�е�try���׳���char��int��double��A
	//�⼸���쳣����ô�����try-catch�е�catch�ǲ����˵ģ���
	//���쳣�ͻᱻ���ϴ��ݸ����ñ������ĺ������˴���f2���൱��
	//��f2�е���f1���Ǿ����������쳣

	std::cout<<"f1����"<<std::endl;
}

void f2(int i)
{
	std::cout<<"f2��ʼ"<<std::endl;
	try
	{
		std::cout<<"f2-try��ʼ"<<std::endl;
		f1(i);
		std::cout<<"f2-try����"<<std::endl;
	}
	catch (char b)
	{
		std::cout<<"������char�쳣"<<b<<std::endl;
	}
	catch (int b)
	{
		std::cout<<"������int�쳣"<<b<<std::endl;
	}
	std::cout<<"f2����"<<std::endl;
}

void f3(int i)
{
	std::cout<<"f3��ʼ"<<std::endl;
	try
	{
		std::cout<<"f3-try��ʼ"<<std::endl;
		f2(i);
		std::cout<<"f3-try����"<<std::endl;
	}
	catch (double b)
	{
		std::cout<<"������double�쳣"<<b<<std::endl;
	}
	std::cout<<"f3����"<<std::endl;
}

void main()
{
	try
	{
		f3(5);
	}
	catch (A x)
	{
		std::cout<<"������A�쳣"<<std::endl;
	}
	
	system("pause");
}