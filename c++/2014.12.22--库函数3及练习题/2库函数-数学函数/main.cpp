#include<iostream>
#include <math.h>

//��ѧ����
//���� = ����/�뾶
//360�ǵĻ���2��
//180�ǵĻ����Ǧ�
//90�ǵĻ����Ǧ�/2

void main()
{
	const float pi = 3.1415926f;
	//01)������
	std::cout<<sin(pi/6.0f)<<std::endl;
	//02)������
	std::cout<<cos(pi/6.0f)<<std::endl;
	//03)����
	std::cout<<sqrt(9.0f)<<std::endl;
	std::cout<<sqrt(10.0f)<<std::endl;
	std::cout<<sqrt(25.0f)<<std::endl;


	system("pause");
}