#include <iostream>

//���������
//1���������������ʹ�ú�ԭʼ�������ʹ��һ��
//2�������������������

class ZuoBiao
{
public:
	int x, y;

	ZuoBiao& operator ++()
	{
		x += 1;
		y += 1;
		return *this;
	}

	ZuoBiao operator ++(int)
	{
		ZuoBiao zb = *this;
		x += 1;
		y += 1;
		return zb;
	}
};

void main()
{
	//��ֵ������ʽ�Ľ���Ǹ�ֵ���֮�����ı���
	int a, b, c;
	a = 1; b = 2; c = 3;
	a = b = c; //b = c; a = b;
	std::cout<<a<<b<<c<<std::endl;

	a = 1; b = 2; c = 3;
	(a = b) = c; //a = b; a = c;
	std::cout<<a<<b<<c<<std::endl;

	//��ֵ���ʽ����C���Դ�ͳ���Է���=����

	//�������������C���Դ�ͳ�ϲ��ܷ���=���
	//�ı��ʽ����������ض���Ӧ�÷�������
	//(a + b) = 4;

	(a += b) = 5;

	//��ֵ��ǰ��������ǰ���Լ����Ը�ֵ��������±�������
	//�ķ���ֵ��Ӧ��������
	++a = 6; //++a�Ľ�����Ǳ���a
	//a++ = 7; //a++�Ľ����a��1֮ǰ��һ����ʱ����

	system("pause");
}