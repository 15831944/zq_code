#ifndef _TREE_H_
#define _TREE_H_

#include <list>
#include <iostream>

//template<typename T>
//struct _TREE_NODE
//{
//	T data; //����
//	_TREE_NODE* left_child; //����
//	_TREE_NODE* right_brother; //���ֵ�
//	_TREE_NODE* parent; //���ڵ�
//};
//����������к������°�����������ڵ��������

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
	if (t)
	{
		int child_num = 0;
		std::list<_TREE_NODE<T>*>::iterator it;
		for (it = t->child.begin(); it != t->child.end(); ++it)
			child_num += sizeTN(*it);
		return child_num + 1;
	}
	else
		return 0;
}

template<typename T> //�߶�
int heightTN(_TREE_NODE<T>* t)
{
	if (t)
	{
		int child_max_height = 0;
		std::list<_TREE_NODE<T>*>::iterator it;
		for (it = t->child.begin(); it != t->child.end(); ++it)
		{
			int child_height = heightTN(*it);
			if (child_max_height < child_height)
				child_max_height = child_height;
		}
		return child_max_height + 1;
	}
	else
		return 0;
}

template<typename T> //��ӡ
void _printTN(_TREE_NODE<T>* t, int level)
{
	if (t)
	{
		if (level > 0)
		{
			if (level > 1)
			{
				std::cout<<"��";
				for (int i = 0; i < level - 2; ++i)
					std::cout<<"  ";

				//�����ǰ�ڵ���Ǹ��ڵ�����һ������
				if (t == t->parent->child.back())
					std::cout<<"��";
				else
					std::cout<<"��";
			}
			else
			{
				if (t == t->parent->child.back())
					std::cout<<"��";
				else
					std::cout<<"��";
			}
		}
		
		std::cout<<t->data<<std::endl;
		std::list<_TREE_NODE<T>*>::iterator it;
		for (it = t->child.begin(); it != t->child.end(); ++it)
			_printTN(*it, level + 1);
	}
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

	//���ı���
	//�ȸ����������ȷ��ʸ��ڵ㣬���ȸ�����ÿ������
	//������������Ⱥ������ÿ���������ٷ��ʸ��ڵ�

	_printTN(t, 0);
}

#endif