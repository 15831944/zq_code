#include<iostream>

class ABC
{
public:
	int a;//��Ա����
	void b()//��Ա����
	{
		std::cout<<"!"<<std::endl;
	}
};

void main()
{
	ABC x;
	x.a = 1;//ͨ���������
	x.b();
	ABC* y = &x;
	y->a = 2;//ͨ����ַ����
	y->b();
	system("pause");
}