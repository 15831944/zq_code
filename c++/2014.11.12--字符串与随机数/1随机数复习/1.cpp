#include<iostream>
#include<time.h>


void main()
{
	//��ȡ1970.1.1-0.0.0������ִ�е�time(0)��仰
	//��ʱ���������
	srand(time(0));
	//ȡ0��n-1���������Ҫrand()%n
	//ȡ7��12�������
	//ע�⣺������Ǵ�0��ʼ��n-1����Ҫȡ0֮��X
	//��Y������������ں������X����ô����ȡ��
	//X��Y֮����������Yָȡֵ�ķ�Χ�����һ����
	for(int i = 0; i < 10; ++i)
	{
		int a = rand() % 8 + 6;
		std::cout<<a<<std::endl;
	}

	system("pause");
}