#include <iostream>

void main()
{
	int a;
	int b;
	int c;

	//�����Զ������ͨ������ķ�ʽ��ֵ����������ʱ
	//�ÿո������Ǹ�����
	std::cin>>a;
	std::cin>>b;
	std::cin>>c;

	std::cout<<a<<" "<<b<<" "<<c<<std::endl;


	int d = 10;
	d = 29;

	a = 045;//��������������ǰ�����һ��0��ʾ��
	//��һ���˽�������
	std::cout<<a<<std::endl;
	a = 0x145;//��������������ǰ�����0x���ʾ���
	//��һ��ʮ����������
	std::cout<<a<<std::endl;

	//û�ж����Ƶ�����������д��

	system("pause");
}