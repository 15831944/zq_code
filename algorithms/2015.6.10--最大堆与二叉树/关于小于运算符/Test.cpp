// Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

struct STUDENT1
{
	int id;
	char name[32];
	int age;

	//С��������涨���ǰ���id���бȽϣ�����
	//д�����������޸ıȽϵķ���
	bool operator < (const STUDENT1& that)
	{
		return id < that.id;
	}
};

//����
struct STUDENT2;
extern bool (* less)(const STUDENT2* s1, const STUDENT2* s2);

struct STUDENT2
{
	int id;
	char name[32];
	int age;

	bool operator < (const STUDENT2& that)
	{
		return (*less)(this, &that);
	}
};

//һ������ָ��
bool (* less)(const STUDENT2* s1, const STUDENT2* s2);

bool less_id(const STUDENT2* s1, const STUDENT2* s2)
{
	return s1->id < s2->id;
}
bool less_name(const STUDENT2* s1, const STUDENT2* s2)
{
	return strcmp(s1->name, s2->name) == -1;
}
bool less_age(const STUDENT2* s1, const STUDENT2* s2)
{
	return s1->age < s2->age;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//��׼���ж������ݿ��Խ��д�С�Ƚϵ�
	//Ҫ������������ͱ���֧��<�����

	STUDENT2 sa = {10, "abc", 21}, sb = {11, "aaa", 23};

	//ͨ������Ĵ����������С��������еľ���ȽϷ�ʽ
	less = less_id;

	if (sa < sb)
		std::cout<<"!"<<std::endl;

	less = less_name;

	if (sa < sb)
		std::cout<<"!"<<std::endl;

	return 0;
}

