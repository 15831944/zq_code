#include<iostream>

void f1()
{
	std::cout<<"abc"<<std::endl;
}

void f2()
{
	f1();
	std::cout<<"def"<<std::endl;
}

void f3()
{
	f2();
	std::cout<<"ghi"<<std::endl;
}


void main()
{
	f3();
	system("pause");
}

//�ϵ�+��������
//����̵���F10
//����䵥��F11:���뵽���õĺ�����
//shift+f11�������õĺ���

//function ������
//pointer:ָ��
//referance:����
//void:�գ���