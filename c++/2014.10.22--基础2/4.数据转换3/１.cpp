#include <iostream>


void main()
{
	int a = 'x';
	short b = 'x';
	char c = 'x';
	//a,b,c�ж��洢��������120����������ʾ��ʱ��
	//int��short����ʾΪ������char��ʾΪ����
	std::cout<<a<<std::endl;
	std::cout<<b<<std::endl;
	std::cout<<c<<std::endl;

	//����a��int����,�����(char)a��������char����
	std::cout<<(char)a<<std::endl;
	//����(char)a��ǿ��ת��ֻ�������������������á�
	//�����ܸı�a�������������
	std::cout<<a<<std::endl;

	std::cout<<(int)((char)a)<<std::endl;

	system("pause");
}