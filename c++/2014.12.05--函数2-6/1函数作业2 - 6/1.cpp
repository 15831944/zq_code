#include<iostream>


//02
int GetMaxNo(int a,int b,int c)
{
	int max = a;
	if(max < b)
		max = b;
	if(max < c)
		max = c;
	return max;

	//if(a >= b && a >= c)
	//	return a;
	//else if(b >= a && b >= c)
	//	return b;
	//else
	//	return c;
}
//03
int GetMaxGongYueShu(int a,int b)
{
	if(a <= 0 || b <= 0)
		return -1;
	if(a > b)
	{
		int max = a;
		a = b;
		b = max;
	}
	//int max = 0;
	//for(int i = 1;i <= a;i++)
	//{
	//	if(a % i == 0 && b % i == 0)
	//	{
	//		if(max < i)
	//			max = i;
	//	}
	//}
	//return max;

	if(b % a == 0)
		return a;
	int qidian = a/2;
	if(a % 2 != 0)
		qidian++;
	for(int i = qidian;i >= 1;--i)
	{
		if(a % i == 0 && b % i == 0)
		{
			return i;
		}
	}
	//for(int i = a;i >= 1;--i)
	//{
	//	if(a % i == 0 && b % i == 0)
	//	{
	//		return i;
	//	}
	//}
	return 1;

	//for(int min = a < b ? a :b;min > 1;--min)
	//{
	//
	//}
}

//04
int GetMinGongBeiShu(int a,int b)
{
	if(a <= 0 || b <= 0)
		return -1;
	//��С�������ķ�Χ�ϴ���Ǹ������������Ļ�
	if(a < b)
	{
		int min = a;
		a = b;
		b = min;
	}
	//��֤a���
	for(int  i = a; i <= a * b;++i)
	{
		if(i % a == 0 && i % b == 0)
			return i;
	}
	return a * b;
}

//5
//void Swap(int a, int b)
//{//���ݻύ�����������������ڲ��ı��������ⲿ��û���κι�ϵ
//	int c = a;
//	a = b;
//	b = c;
//}

void Swap1(int* a,int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

void Swap2(int& a,int& b)
{
	//�����a,b���ⲿ(��ǰ����main�ֵ�a,b)�ı���
	//�ڱ�������a,bʵ�ʾ��Ƿ��ʵ�main�е�a,b
	int c = a;
	a = b;
	b = c;
}

//6
//C++���������double p[5]����Ϊdouble* p
double GetPinJunShu(double p[5])
{
	double a = 0;
	for(int i = 0; i < 5;++i)
		a += p[i];
	return a / 5;
}

//Ҫ�õ�������ʵ���ǵõ�������׵�ַ
double GetPinJunShu1(double* p)//(const double* p)
{
	double a = 0;
	for(int i = 0; i < 5;++i)
		a += p[i];
	return a / 5;
}


//һ����˵������һ����������������˴�������������Ҫ�������鳤��
double GetPinJunShu2(const double* p,int n)
{
	double a = 0;
	for(int i = 0; i < n;++i)
		a += p[i];
	return a / n;
}




void main()
{
	
	int x = GetMaxNo(2,2,2);
	int a = 100,b = 200;
	//Swap1(&a,&b);
	Swap2(a,b);
	double c[5] = {1.0,2.0,3.0,4.0,5.0};
	int len = sizeof(c)/sizeof(double);
	double c1 = GetPinJunShu(c);
	system("pause");
}