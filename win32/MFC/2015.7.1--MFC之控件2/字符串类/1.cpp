#include "MyString.h"

//��Ϊ���캯�����������ֻ��һ������ô�ǿ���������ķ�ʽ��д��
//A a(x);
//A a = x;

void main()
{
	CMyString ms1;
	CMyString ms2("abcdef");
	CMyString ms3 = "def";
	CMyString ms4 = ms3;
	ms4 = ms2; //��ȫ��ͬ��ms4.operator =(ms2);
	ms4 = "���"; //��ȫ��ͬ��ms4.operator =("���");
	ms4 = ms4 + ms3; //ͬ��ӷ���ͬ�ำֵ
	ms4 = ms4 + "����"; //�ӷ���ͬ�ำֵ
	ms4 += ms3; //ms4.operator +=(ms3);
	ms4 += ms4; //ms4.operator +=(ms4);
	ms4 += "XYZ"; //ms4.operator +=("XYZ");
	ms4 += 'R'; std::cout<<ms4.GetString()<<std::endl;
	ms4[0] = 'T'; std::cout<<ms4.GetString()<<std::endl;
	ms4[1] = 'W'; std::cout<<ms4.GetString()<<std::endl;

	system("pause");
}