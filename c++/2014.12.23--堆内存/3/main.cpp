#include<iostream>

char* f1()
{
	char a[] = "abc";
	return a;//a��f1�е�ջ�ڴ�
}

char* f2()
{
	char* a = "def";
	return a;//a�ǳ�����ַ
}

char* f3()
{
	char* a = (char*)malloc(4);
	a[0] = 'a';
	a[1] = 'b';
	a[2] = 'c';
	a[3] = 0;
	return a;
}

void main()
{
	char* p1 = f1();
	char* p2 = f2();
	char* p3 = f3();
	std::cout<<p1<<std::endl;
	std::cout<<p2<<std::endl;
	std::cout<<p3<<std::endl;
	free(p3);
	system("pause");
}