#include <iostream>

void f(int i)
{
	try
	{
		switch (i)
		{
		case 0: throw true;
		case 1: throw 'A';
		case 2: throw 1;
		case 3: throw 1.0;
		}
	}
	catch (bool b)
	{
		std::cout<<"������bool�쳣"<<b<<std::endl;
	}
}

void f2(...)
{}

int add_num(int num, ...)
{
	int* p = &num + 1;
	int add = 0;
	for (int i = 0; i < num; ++i)
		add += p[i];
	return add;
}

void main()
{
	try
	{
		f(3);
	}
	catch (int i)
	{
		std::cout<<"������int�쳣"<<i<<std::endl;
	}
	catch (...) //���Ҫд...��ôһ��Ҫд��try-catch�����
	{
		std::cout<<"������δ֪�쳣"<<std::endl;
	}

	//...�������÷�
	//1����catch���б�ʾҪ�����κ������쳣������
	//   ��ôд�Ļ��ǲ��ܵõ�������쳣ֵ
	//2�����岻���κ����ģ�...��ʾ�������ͺ�����
	//   �����ĺ���

	//f2(1);
	//f2(1, 2);
	//f2(1, 2, 3, 4, 5);

	std::cout<<add_num(3, 5, 7, 9)<<std::endl;
	std::cout<<add_num(5, 5, 7, 9, 11, 13)<<std::endl;
	
	system("pause");
}