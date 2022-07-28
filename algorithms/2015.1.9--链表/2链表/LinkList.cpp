#include<iostream>
#include"LinkList.h"
//���е�posֵ����Ҫ�ҵ����Ǹ��ڵ��ǰ��ڵ�
//����Head(ͷ)�ڵ�
LINKLIST createLINKLIST()
{
	LINKLIST p = (LINKLIST)malloc(sizeof(_LINK_LIST) + sizeof(int));
	p->next = 0;
	*((int*)(p + 1)) = 0;//��¼����,����û��
	return p;
}
//����(����)
void destroyLINKLIST(LINKLIST linklist)
{
	clearLINKLIST(linklist);
	free(linklist);
}
//����(�������ݣ�λ��)
bool insertLINKLIST(LINKLIST linklist,LLDATA data,int pos)
{
	if(pos < 0 || pos > lengthLINKLIST(linklist))
		return false;
	//�ҵ�ǰ��ڵ�
	LINKLIST p = linklist;
	for(int i = 0; i < pos; ++i)
		p = p->next;

	//�����½ڵ�
	LINKLIST n = (LINKLIST)malloc(sizeof(_LINK_LIST));
	//��ȡ����
	n->data = data;
	//����ָ��ָ��
	n->next = p->next;
	p->next = n;
	*((int*)(linklist + 1)) += 1;
	return true;
}
//����(��������)
void pushLINKLIST(LINKLIST linklist,LLDATA data)
{
	insertLINKLIST(linklist,data,lengthLINKLIST(linklist));
}
//ɾ��(����λ��)
bool eraseLINKLIST(LINKLIST linklist,int pos)
{
	if(pos < 0 || pos > lengthLINKLIST(linklist) - 1)
		return false;
	//�ҵ�ǰ��ڵ�
	LINKLIST p = linklist;
	for(int i = 0; i < pos; ++i)
		p = p->next;
	//����ָ��ָ��
	LINKLIST q = p->next;
	p->next = q->next;
	free(q);
	*((int*)(linklist + 1)) -= 1;
	return true;
}
//���(����)
void clearLINKLIST(LINKLIST linklist)
{
	//����1
	//int length = lengthLINKLIST(linklist);
	//for(int i = 0; i < length;++i)
	//	eraseLINKLIST(linklist,0);
	//����2
	LINKLIST p = linklist->next;
	while(p)
	{
		LINKLIST q = p->next;
		free(p);
		p = q;
	}
	linklist->next = 0;
	*((int*)(linklist + 1)) = 0;
}
//����(����)
int lengthLINKLIST(LINKLIST linklist)
{
	return *((int*)(linklist + 1));
}
//��ȡ(����λ��)
LLDATA* getLINKLIST(LINKLIST linklist,int pos)
{
	if(pos < 0 || pos > lengthLINKLIST(linklist) - 1)
		return 0;
	//�ҵ�ǰ��ڵ�
	LINKLIST p = linklist;
	for(int i = 0; i <= pos; ++i)
		p = p->next;
	return &p->data;
}
//����(�������ݣ���ʼλ�ã���Ⱥ���)
int findLINKLIST(LINKLIST linklist,LLDATA data,int begin, bool (*equal)(LLDATA,LLDATA))
{
	if(begin < 0 || begin > lengthLINKLIST(linklist) - 1)
		return -2;
	//�ҵ�ǰ��ڵ�
	LINKLIST p = linklist;
	for(int i = 0; i <= begin; ++i)
		p = p->next;
	for(;p;p = p->next,++begin)
	{
		if((*equal)(data,p->data))
			return begin;
	}
	return -1;
}
//����
void sortLINKLIST(LINKLIST linklist,bool increase,bool (*greater)(LLDATA,LLDATA))
{
	int length = lengthLINKLIST(linklist);
	if(increase)
	{
		LINKLIST p;
		for(int i = length - 1; i >= 0;--i)
		{
			p = linklist;
			for(int j = 0; j < i;++j)
			{
				if((*greater)(p->next->data,p->next->next->data))
				{
					LINKLIST q[] = {p,p->next,p->next->next};
					q[0]->next = q[2];
					q[1]->next = q[2]->next;
					q[2]->next = q[1];
				}
				p = p->next;
			} 
		}
	}
	else
	{
		LINKLIST p,q,r;
		for(int i = 0; i < length - 1; ++i)
		{
			p = linklist->next;
			for(int ii = 0; ii < i;++i)
			{
				p = p->next;
				int j = i;
				q = p;
				r = q->next;
				for(int k = j + 1; k < length;++k)
				{
					if((*greater)(r->data,q->data))
						q = r;
					r = r->next;
				}
				if(q != p)
				{
					LLDATA d = q->data;
					q->data = p->data;
					p->data = d;
				}
			}
		}
	}
}