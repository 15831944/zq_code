#include<iostream>
//�ݹ�
//������Ĭ�ϲ���
//����������
//����ָ��

//һ��������ͬ����ʽ������ͬ(���ͣ�����)
//�ĺ����͹����˺�������
//���������Զ����������ʵ�ʲ�����ȷ�����õ�
//���ĸ�ͬ������

//C++֧�ֺ������أ�C��֧�ֺ�������
//�������ص�Ŀ�ģ����ڼ������ǵĺ���ѧϰʱ�䣬һ����˵
//һ�鹦�ܽӽ��ĺ������ǿ����������໥���أ�ֻҪ������һ
//����ô���������غ�����ʹ��Ҳ�ǲ��ģ�
//����⺯���п�������
//double sqrt( double x );
//float sqrt( float x );
//long double sqrt( long double x );
//ע���Ĭ�ϲ�����ʹ�÷������ò���ȷ
int  add(int a,int b)
{
	return a + b;
}

float  add(float a,float b)
{
	return a + b;
}

int  add(int a,int b = 2 ,int c = 3)
{
	return a + b + c;
}

//int  add(int a,int b,int c = 3)
//{
//	return a + b + c;
//}

void main()
{
	std::cout<<add(1)<<std::endl;
	//std::cout<<add(1,2)<<std::endl;
	std::cout<<add(1.0f,2.0f)<<std::endl;
	std::cout<<add(1,2,3)<<std::endl;
	system("pause");
}