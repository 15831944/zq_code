#include <iostream>

//std::cout<<"":��""�е�����ԭ�ⲻ���Ĵ�ӡ������̨��
//std::cout<<��������������ֵ��ӡ������̨��
//std::cout<<���ʽ�������ʽ�Ľ����ֵ��ӡ������̨��

//std::cin>>������
//�ȴ��û�����һ������Ȼ�󰴻س���
//���û����س��󣬽������ֵ��ֵ��
//����
void main()
{
	int a;
	
	a = 10;
	
	//�����������a��ֵ
	std::cout<<a<<std::endl;
	//���a * 2��ֵ
	std::cout<<a * 2<<std::endl;

	//�ȴ��û�����һ������Ȼ�󰴻س���
	//���û����س��󣬽������ֵ��ֵ��
	//a
	std::cin>>a;//65

	std::cout<<a<<std::endl;

	system("pause");

	int b = 10;

	b = 2 * 4;

	std::cin>>b;

	std::cout<<b<<std::endl;

	system("pause");
}