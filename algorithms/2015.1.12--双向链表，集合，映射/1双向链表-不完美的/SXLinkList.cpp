#include<iostream>
#include"SXLinkList.h"
//���е�posֵ����Ҫ�ҵ����Ǹ��ڵ��ǰ��ڵ�
//����Head(ͷ)�ڵ�
SXLINKLIST createSXLINKLIST()
{
	SXLINKLIST p = (SXLINKLIST)malloc(sizeof(_SXLINK_LIST) + sizeof(int));
	p->next = p->pre = 0;
	*((int*)(p + 1)) = 0;//��¼����,����û��
	return p;
}
//����(����)
void destroySXLINKLIST(SXLINKLIST sxlinklist)
{
	clearSXLINKLIST(sxlinklist);
	free(sxlinklist);
}
//����(�������ݣ�λ��)
bool insertSXLINKLIST(SXLINKLIST sxlinklist,LLDATA data,int pos)
{
	if(pos < 0 || pos > lengthSXLINKLIST(sxlinklist))
		return false;
	//�ҵ�ǰ��ڵ�
	SXLINKLIST p = sxlinklist;
	for(int i = 0; i < pos; ++i)
		p = p->next;

	//�����½ڵ�
	SXLINKLIST n = (SXLINKLIST)malloc(sizeof(_SXLINK_LIST));
	//��ȡ����
	n->data = data;
	//����ָ��ָ��
	n->next = p->next;

	if(pos == lengthSXLINKLIST(sxlinklist))
		n->pre = p;
	else
		n->pre = n->next->pre;
	p->next = n;
	if(pos != lengthSXLINKLIST(sxlinklist))
		n->next->pre = n;

	*((int*)(sxlinklist + 1)) += 1;
	return true;
}
//����(��������)
void pushSXLINKLIST(SXLINKLIST sxlinklist,LLDATA data)
{
	insertSXLINKLIST(sxlinklist,data,lengthSXLINKLIST(sxlinklist));
}
//ɾ��(����λ��)
bool eraseSXLINKLIST(SXLINKLIST sxlinklist,int pos)
{
	if(pos < 0 || pos > lengthSXLINKLIST(sxlinklist) - 1)
		return false;
	//�ҵ�ǰ��ڵ�
	SXLINKLIST p = sxlinklist;
	for(int i = 0; i < pos; ++i)
		p = p->next;
	//����ָ��ָ��
	SXLINKLIST q = p->next;

	p->next = q->next;
	q->next->pre = q->pre;

	free(q);
	*((int*)(sxlinklist + 1)) -= 1;
	return true;
}
//���(����)
void clearSXLINKLIST(SXLINKLIST sxlinklist)
{
	//����1
	//int length = lengthSXLINKLIST(sxlinklist);
	//for(int i = 0; i < length;++i)
	//	eraseSXLINKLIST(sxlinklist,0);
	//����2
	SXLINKLIST p = sxlinklist->next;
	while(p)
	{
		SXLINKLIST q = p->next;
		free(p);
		p = q;
	}
	sxlinklist->next = 0;
	*((int*)(sxlinklist + 1)) = 0;
}
//����(����)
int lengthSXLINKLIST(SXLINKLIST sxlinklist)
{
	return *((int*)(sxlinklist + 1));
}
//��ȡ(����λ��)
LLDATA* getSXLINKLIST(SXLINKLIST sxlinklist,int pos)
{
	if(pos < 0 || pos > lengthSXLINKLIST(sxlinklist) - 1)
		return 0;
	//�ҵ�ǰ��ڵ�
	SXLINKLIST p = sxlinklist;
	for(int i = 0; i <= pos; ++i)
		p = p->next;
	return &p->data;
}
//����(�������ݣ���ʼλ�ã���Ⱥ���)
int findSXLINKLIST(SXLINKLIST sxlinklist,LLDATA data,int begin, bool (*equal)(LLDATA,LLDATA))
{
	if(begin < 0 || begin > lengthSXLINKLIST(sxlinklist) - 1)
		return -2;
	//�ҵ�ǰ��ڵ�
	SXLINKLIST p = sxlinklist;
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
void sortSXLINKLIST(SXLINKLIST sxlinklist,bool increase,bool (*greater)(LLDATA,LLDATA))
{
	int length = lengthSXLINKLIST(sxlinklist);
	if(increase)
	{
		SXLINKLIST p;
		for(int i = length - 1; i >= 0;--i)
		{
			p = sxlinklist;
			for(int j = 0; j < i;++j)
			{
				if((*greater)(p->next->data,p->next->next->data))
				{
					SXLINKLIST q[] = {p,p->next,p->next->next};

					q[0]->next = q[2];
					q[1]->next = q[2]->next;
					q[2]->next = q[1];

					q[2]->pre = q[0];
					q[1]->next->pre = q[1];
					q[1]->pre = q[2];
					
				}
				p = p->next;
			} 
		}
	}
	else
	{
		SXLINKLIST p,q,r;
		for(int i = 0; i < length - 1; ++i)
		{
			p = sxlinklist->next;
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