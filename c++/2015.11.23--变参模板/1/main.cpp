#include <iostream>
#include <string>
#include <stdarg.h>
using namespace std;


//Cʽ�ı�δ�ӡ
void c_Print(const char* szFormat, ...)
{
	// ���ݴ���Ĳ�����ʽ���ַ���
	char strBuffer[1024] = {};
	va_list   arglist;

	// ����䳤����
	va_start(arglist, szFormat);
	vsprintf(strBuffer, szFormat, arglist);
	va_end(arglist);

	// ������������ʾ
	cout << strBuffer << endl;
}

//Cʽ�ļӷ�����
int c_Add(int count, ...)
{
	va_list ap;
	int sum = 0;

	va_start(ap, count);

	for (int i = 0; i < count; ++i)
	{
		int arg = va_arg(ap, int);
		sum += arg;
	}

	va_end(ap);

	return sum;
}

//��C++11�еı�δ�ӡ
template <typename... TS>   // typename... TSΪģ���βΰ���TSΪģʽ
void cpp_Print(const char* s, TS ... args)  // TS... argsΪ�����βΰ���argsΪģʽ
{
	 printf(s, args...);
	 printf("\n");
}

//C++11�еļӷ�����
template<typename T1, typename... T2> 
int cpp_Add(T1 p, T2... arg)
{
	cout << "p:" << p << endl;
	int sum = p + cpp_Add(arg...);
	cout << "sum:" << sum << endl;

	return sum;
}

int cpp_Add()  //�߽�����  
{
	return 0;
}

int main(int arg, char* args[])
{
	c_Print("C hello world��%d", 123456);
	cpp_Print("C++ hello world: %d", 123456);

	cout << c_Add(2, 20, 30) << endl;
	cout << cpp_Add(100, 300, 800) << endl;

	system("pause");
	return 0;
}