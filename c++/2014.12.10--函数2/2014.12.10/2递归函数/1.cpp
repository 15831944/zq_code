#include<iostream>
//�ݹ�
//������Ĭ�ϲ���
//����������
//����ָ��

//01)�໥���ã�����Aֱ�ӻ��߼�ӵ��ú���B
//02)�ݹ����: ����Aֱ�ӻ��߼�ӵ��ú���A
unsigned int f1(unsigned int a)
{
	int b = 1;
	for(unsigned int i = 1; i <= a; ++i)
		b += i;
	return b;
}

unsigned int f2(unsigned int a)
{
	if(1 == a)
		return 1;
	else
		return a * f2(a - 1);
}

//f3û�а취�˳�����
//int f3(int a)
//{
//	return a + f3(a -1);
//}

int f3_1(int a)
{
	if(a < 0)
		return 0;
	return a + f3_1(a - 1);
}

void main()
{
	std::cout<<f1(5)<<std::endl;
	std::cout<<f2(5)<<std::endl;
	//std::cout<<f3(5)<<std::endl;
	std::cout<<f3_1(5)<<std::endl;
	//return 5 * f2(4);
	//return 5 * 4 * f2(3);
	//return 5 * 4 * 3 * f2(2);
	//return 5 * 4 * 3 * 2 * f2(1);
	//return 5 * 4 * 3 * 2 * 1 * 1;
	system("pause");
}
//�ݹ麯��������Ҫ����������ĳ��������ʱ��
//�Ͳ�������������