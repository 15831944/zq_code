#include<iostream>


void main()
{
	char a[] = "123abc";
	char b[7] = "123abc";
	char c[256] = "123abc";

	//01
	char* a1 = "456def";
	std::cout<<a1<<std::endl;

	std::cout<<a<<std::endl;

	a[0] = 'A';

	std::cout<<a<<std::endl;

	//a1[0] = 'A';

	//std::cout<<a1<<std::endl;

	for(int i = 0; i < 6; ++i)
	{
		a[i] = a1[i];
	}
	std::cout<<a<<std::endl;

	//��ַ�ǳ�����a1��ָ�룬ָ���Ǵ洢��ַ�ı���
	//a = a1;//=��಻���ǳ���

	a1 = a;

	system("pause");
}