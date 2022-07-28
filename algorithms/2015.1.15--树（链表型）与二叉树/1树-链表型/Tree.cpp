#include <iostream>
#include "Tree.h"

//����
TREE createTREE()
{
	TREE tree = (TREE)malloc(sizeof(_TREE));
	tree->parent = tree->left_child = tree->right_brother = 0;
	return tree;
}
//�Ͽ������丸�ڵ�Ĺ�ϵ
TREE cutTREE(TREE tree)
{
	if(tree->parent)
	{
		if(tree->parent->left_child == tree)
			tree->parent->left_child = tree->right_brother;
		else
		{
			TREE p = tree->parent->left_child;
			while(p->right_brother != tree)
			{
				p = p->right_brother;
			}
			p->right_brother = tree->right_brother;
		}
		tree->right_brother = tree->parent = 0;
	}
	return tree;
}
//����
void insertTREE(TREE tree1,TREE tree2)
{
	cutTREE(tree2);
	tree2->parent = tree1;
	tree2->right_brother = tree1->left_child;
	tree1->left_child  = tree2;
}
///
static void _deleteTREE(TREE tree)
{
	if(tree)
	{
		_deleteTREE(tree->left_child);
		_deleteTREE(tree->right_brother);
		free(tree);
	}
}

//ɾ��
void deleteTREE(TREE tree)
{
	cutTREE(tree);
	_deleteTREE(tree);
}
//����
int countTREE(TREE tree)
{
	if(tree)
	{
		int n = 1;
		for(TREE p = tree->left_child;p;p = p->right_brother)
			n+=countTREE(p);
		return n;
	}
	return 0;
}
//�߶�
int heigthTREE(TREE tree)
{
	if(tree)
	{
		int h = 0;
		for(TREE p = tree->left_child;p;p = p->right_brother)
		{
			int child_h = heigthTREE(p);
			if(h < child_h)
				h = child_h;
		}
		return h + 1;
	}
	return 0;
}