#include "SqList.h"
#include <iostream>

//����(����)
SQLIST createSQLIST(int size)
{
	SQLIST sqlist = (SQLIST)malloc(sizeof(_SQ_LIST));
	sqlist->size = size;
	sqlist->length = 0;
	sqlist->data  =  (SLDATA*)malloc(sizeof(SLDATA)* sqlist->size);
	return sqlist;
}
//����(˳���)
void destroySQLIST(SQLIST sqlist)
{
	free(sqlist->data);
	free(sqlist);
}
//����(˳������ݣ�λ��)
bool insertSQLIST(SQLIST sqlist,SLDATA data,int pos)
{
	if(pos < 0 || pos > sqlist->length)
		return false;

	if(sqlist->length == sqlist->size)
	{
		sqlist->size *= 2;
		SLDATA* p = (SLDATA*)malloc(sizeof(SLDATA) * sqlist->size);
		for(int i = 0; i < sqlist->length;++i)
			p[i] = sqlist->data[i];
		free(sqlist->data);
		sqlist->data = p;
	}

	int move = sqlist->length - pos;
	for(int i = 0; i < move; ++i)
		sqlist->data[sqlist->length - i] = sqlist->data[sqlist->length - i - 1];
	sqlist->data[pos] = data;
	sqlist->length ++;
	return true;
}
//����(˳�������)
void pushSQLIST(SQLIST sqlist,SLDATA data)
{
	insertSQLIST(sqlist,data,sqlist->length);
}
//ɾ��(˳���λ��)
bool eraseSQLIST(SQLIST sqlist,int pos)
{
	if(pos < 0 || pos >= sqlist->length)
		return  false;
	int move = sqlist->length - pos - 1;
	for(int i = 0; i < move;++i)
		sqlist->data[pos + i] = sqlist->data[pos + i + 1];
	sqlist->length -= 1;
	return true;
}
//���(˳���)
void clearSQLIST(SQLIST sqlist)
{
	sqlist->length = 0;
}
//����(˳���)
int lengthSQLIST(SQLIST sqlist)
{
	return sqlist->length;
}
//��ȡ(˳���λ��)
SLDATA* getSQLIST(SQLIST sqlist,int pos)
{
	if(pos < 0 || pos > sqlist->length  - 1)
		return 0;
	return sqlist->data + pos;
}
//����(˳������ݣ���ʼλ�ã����ں���)
int findSQLIST(SQLIST sqlist,SLDATA data,int begin,bool (*equal)(SLDATA,SLDATA))
{
	if(begin < 0 || begin > sqlist->length - 1)
		return -2;
	for(;begin < sqlist->length;++begin)
	{
		if((*equal)(data,sqlist->data[begin]))
			return begin;
	}
	return -1;
}
//����
void sortSQLIST(SQLIST sqlist,bool increase,bool (*greater)(SLDATA,SLDATA))
{
	if(increase)
	{
		for(int i = 0; i < sqlist->length - 1; ++i)
		{
			int j = i;
			for(int k = j + 1; k < sqlist->length; ++k)
			{
				if((*greater)(sqlist->data[j],sqlist->data[k]))
					j = k;
			}
			if(j != i)
			{
				SLDATA d = sqlist->data[j];
				sqlist->data[j] = sqlist->data[i];
				sqlist->data[i] = d;
			}
		}
	}
	else
	{
		for(int i = 0; i < sqlist->length - 1; ++i)
		{
			int j = i;
			for(int k = j + 1; k < sqlist->length; ++k)
			{
				if((*greater)(sqlist->data[k],sqlist->data[j]))
					j = k;
			}
			if(j != i)
			{
				SLDATA d = sqlist->data[j];
				sqlist->data[j] = sqlist->data[i];
				sqlist->data[i] = d;
			}
		}
	}
}
