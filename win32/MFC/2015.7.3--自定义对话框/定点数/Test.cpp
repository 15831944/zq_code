// Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

//��������һ����������ģ�⸡��������ķ���������
//һЩcpuû�и������㹦�ܵ�ʱ����õ����ַ���

typedef int FIX; //����������
#define _FLOAT_FIX(num) ((FIX)(num * 256.0f))
#define _FIX_FLOAT(num) ((float)num / 256.0f)
#define _FIX_MUL(num1,num2) ((num1) * (num2) / 256.0f)
#define _FIX_DIV(num1,num2) (((float)(num1) / (num2)) * 256.0f)

//��cpu�����ֵļ����У�����������ȸ�����Ҫ�첻�٣�����
//��cpu��һЩû��ֱ��֧�ָ��������㣬�����ر�Ϊ��Щcpu
//������һ��Э��������������Ĳ�����Э��������

int _tmain(int argc, _TCHAR* argv[])
{
	FIX f1 = _FLOAT_FIX(3.14);
	FIX f2 = _FLOAT_FIX(6.58);
	FIX f3 = f1 + f2; //��������������
	FIX f4 = f1 - f2; //��������������
	FIX f5 = _FIX_MUL(f1, f2); //��������������
	FIX f6 = _FIX_DIV(f1, f2); //��������������
	std::cout<<_FIX_FLOAT(f3)<<std::endl;
	std::cout<<_FIX_FLOAT(f4)<<std::endl;
	std::cout<<_FIX_FLOAT(f5)<<std::endl;
	std::cout<<_FIX_FLOAT(f6)<<std::endl;

	//��ά��������Щ���ö������Ӽ����滻������
	//�Ӽ��������Ч��

	return 0;
}