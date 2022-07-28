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

inline void _eraseTN(TN* p)
{
	if (p)
	{
		for (std::vector<TN*>::iterator it = p->child.begin(); it != p->child.end(); ++it)
			_eraseTN(*it);
		delete p;
	}
}

inline void eraseTN(TN* p)
{
	cutTN(p);
	_eraseTN(p);
}

inline void preTN(TN* p, int level)
{
	if (p)
	{
		for (int i = 0; i < level; ++i)
			std::cout<<"��";

		//���ȷ��ʸ��ڵ�
		std::cout<<p->data.c_str()<<std::endl;

		//�������ȸ������������ӽڵ�
		for (std::vector<TN*>::iterator it = p->child.begin(); it != p->child.end(); ++it)
			preTN(*it, level + 1);
	}
}

#endif