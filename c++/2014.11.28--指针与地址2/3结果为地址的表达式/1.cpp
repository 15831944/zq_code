#include<iostream>


void main()
{
	//C++�н���ǵ�ַ�ı��ʽ
	//01)������
	int a[5];//a��int���͵ĵ�ַ
	short b[3];//b��short���͵ĵ�ַ
	double c[4];//c��double���͵ĵ�ַ
	double* e[4];//e��double*���͵ĵ�ַ
	//02)�ַ������泣��
	"123abc���";//char���͵ĵ�ַ
	L"123abc���";//wchar_t���͵ĵ�ַ
	//03)&����
	int f;//&f��int���͵ĵ�ַ
	int* g;//&g��int*���͵ĵ�ַ
	//&b[2]��short���͵ĵ�ַ
	//04)ָ��(��������ʱ�Ϳ����ǵ�ַ)
	int* i = &a[3];//i��int���͵ĵ�ַ
	int** k = &g;//k��int*���͵ĵ�ַ
	//05)������
	//main����һ��void(*)(void)���͵ĵ�ַ
	//ǰ��4�ֶ������ݵ�ַ
	//���һ����ָ���ַ
	system("pause");
}