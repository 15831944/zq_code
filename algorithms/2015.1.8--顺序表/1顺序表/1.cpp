#include<iostream>
#include "SqList.h"
//����
//����
//ɾ��
//����
//���

bool xiangdeng(int,int);
bool great(int ,int);

void main()
{
	SQLIST sqlist = createSQLIST();
	
	//����������ֻ���ñ�׼����������������������
	//�򿪱����
	//std::cout<<sqlist->length<<std::endl;
	
	std::cout<<lengthSQLIST(sqlist)<<std::endl;

	//sqlist->data[0] = 1;
	std::cout<<"����"<<std::endl;
	pushSQLIST(sqlist,1);
	pushSQLIST(sqlist,2);
	pushSQLIST(sqlist,3);
	pushSQLIST(sqlist,4);
	pushSQLIST(sqlist,5);
	pushSQLIST(sqlist,7);
	pushSQLIST(sqlist,6);

	std::cout<<lengthSQLIST(sqlist)<<std::endl;
	
	for(int i = 0; i < lengthSQLIST(sqlist); ++i)
	{
		std::cout<<*getSQLIST(sqlist,i)<<std::endl;
	}
	
	std::cout<<"ɾ��"<<std::endl;
	eraseSQLIST(sqlist,3);
	
	for(int i = 0; i < lengthSQLIST(sqlist); ++i)
	{
		std::cout<<*getSQLIST(sqlist,i)<<std::endl;
	}
	std::cout<<"����"<<std::endl;
	std::cout<<findSQLIST(sqlist,3,0,xiangdeng)<<std::endl;
	
	std::cout<<"����"<<std::endl;
	sortSQLIST(sqlist,false,great);
	for(int i = 0; i < lengthSQLIST(sqlist); ++i)
	{
		std::cout<<*getSQLIST(sqlist,i)<<std::endl;
	}
	std::cout<<"���"<<std::endl;
	clearSQLIST(sqlist);
	std::cout<<lengthSQLIST(sqlist)<<std::endl;

	destroySQLIST(sqlist);

	system("pause");
}

bool xiangdeng(int a,int b)
{
	return a == b;
}
bool great(int a,int b)
{
	return a > b;
}