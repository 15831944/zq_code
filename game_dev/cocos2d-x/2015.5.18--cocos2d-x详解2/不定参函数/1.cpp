#include <iostream>

//�����κ�����ʹ�ùؼ���...��ʾ�Ӵ˴���ʼ��������
int add(int num, ...)
{
	int* p = &num + 1;
	int a = 0;
	for (int i = 0; i < num; ++i)
		a += p[i];
	return a;
}

void main()
{
	std::cout<<add(3, 100, 101, 102)<<std::endl;
	std::cout<<add(4, 100, 101, 102, 103)<<std::endl;

	system("pause");
}