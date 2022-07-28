#ifndef _TREE_H_
#define _TREE_H_

#include <list>

template<typename T>
struct _TREE_NODE
{
	T data; //����
	std::list<_TREE_NODE<T>*> child; //�ӽڵ�
	_TREE_NODE<T>* parent; //���ڵ�
};

template<typename T> //����
_TREE_NODE<T>* createTN()
{
	_TREE_NODE<T>* t = new _TREE_NODE<T>;
	t->parent = 0;
	return t;
}

template<typename T> //�Ͽ�
_TREE_NODE<T>* cutTN(_TREE_NODE<T>* t)
{
	if (t && t->parent)
	{
		std::list<_TREE_NODE<T>*>::iterator it;
		for (it = t->parent->child.begin(); it != t->parent->child.end(); ++it)
		{
			if (*it == t)
				break;
		}
		t->parent->child.erase(it);
		t->parent = 0;
	}
	return t;
}

template<typename T> //����
_TREE_NODE<T>* insertTN(_TREE_NODE<T>* p, _TREE_NODE<T>* c, bool back = true)
{
	cutTN(c);
	if (back)
		p->child.push_back(c);
	else
		p->child.push_front(c);
	c->parent = p;

	return c;
}

template<typename T> //ɾ��
void _eraseTN(_TREE_NODE<T>* t)
{
	if (t)
	{
		std::list<_TREE_NODE<T>*>::iterator it;
		for (it = t->child.begin(); it != t->child.end(); )
		{
			_eraseTN(*it);
			it = t->child.erase(it);
		}
		delete t;
	}
}

template<typename T> //ɾ��
void eraseTN(_TREE_NODE<T>* t)
{
	_eraseTN<T>(cutTN<T>(t));
}

template<typename T> //��С
int sizeTN(_TREE_NODE<T>* t)
{
	
}

template<typename T> //�߶�
int heightTN(_TREE_NODE<T>* t)
{
	
}

template<typename T> //��ӡ
void printTN(_TREE_NODE<T>* t)
{
	//	  1
	//	/ | \
	//	4 2 3
	//	  |
	//	  5
	//   / \
	//	6   7
	//���������ӡΪ
	//1
	//��4
	//��2
	//����5
	//��  ��6
	//��  ��7
	//��3
}

#endif