#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <vector>
#include <string>

struct TN
{
	std::string data; //����
	std::vector<TN*> child; //�ӽڵ�
	TN* parent; //���ڵ�
};
//struct TN
//{
//	std::string data; //����
//	TN* child; //����
//	TN* brother; //���ֵ�
//	TN* parent; //���ڵ�
//};

inline TN* createTN()
{
	TN* tn = new TN;
	tn->parent = 0;
	return tn;
}

inline TN* cutTN(TN* p)
{
	if (p && p->parent)
	{
		//���丸�ڵ����ɾ��
		for (std::vector<TN*>::iterator it = p->parent->child.begin(); it != p->parent->child.end(); ++it)
		{
			if (*it == p)
			{
				p->parent->child.erase(it);
				break;
			}
		}
		p->parent = 0;
	}
	return p;
}

inline TN* insertTN(TN* f, TN* c)
{
	cutTN(c);
	f->child.push_back(c);
	c->parent = f;
	return c;
}

//�����ȸ�����
//���ȷ��ʸ��ڵ㣬�������ȸ������������ӽڵ�
//���ĺ������
//�������κ�������������ӽڵ㣬�ٷ��ʸ��ڵ�

inline void preTN(TN* p)
{
	if (p)
	{
		//���ȷ��ʸ��ڵ�
		std::cout<<p->data.c_str()<<' ';

		//�������ȸ������������ӽڵ�
		for (std::vector<TN*>::iterator it = p->child.begin(); it != p->child.end(); ++it)
			preTN(*it);
	}
}

inline void postTN(TN* p)
{
	if (p)
	{
		//�������κ�������������ӽڵ�
		for (std::vector<TN*>::iterator it = p->child.begin(); it != p->child.end(); ++it)
			postTN(*it);

		//�ٷ��ʸ��ڵ�
		std::cout<<p->data.c_str()<<' ';
	}
}

#endif