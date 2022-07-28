#include "BinaryTree.h"
#include <iostream>

//����
BINARYTREE createBINARYTREE()
{
	BINARYTREE tree = (BINARYTREE)malloc(sizeof(_BINARY_TREE));
	tree->parent = tree->left = tree->right = NULL;
	return tree;
}

//�Ͽ������丸�ڵ����ϵ
BINARYTREE cutBINARYTREE(BINARYTREE bt)
{
	if(bt && bt->parent)
	{
		if(bt->parent->left == bt)
			bt->parent->left = 0;
		if(bt->parent->right == bt)
			bt->parent->right = 0;
		bt->parent = 0;
	}
	return bt;
}

//����:��bt2����bt1��leftΪ�����ߣ��ٲ��ұ�
BINARYTREE insertBINARYTREE(BINARYTREE bt1,BINARYTREE bt2,bool left)
{
	BINARYTREE p = 0;
	if(bt1)
	{
		cutBINARYTREE(bt2);
		if(left)
		{
			p = bt1->left;
			if(p)
				p->parent = 0;
			bt1->left = bt2;
			bt2->parent = bt1;
		}
		else
		{
			p = bt1->right;
			if(p)
				p->parent = 0;
			bt1->right = bt2;
			bt2->parent = bt1;
		}
	}
	return p;
}

void _deleteBINARYTREE(BINARYTREE bt)
{
	if(bt)
	{
		_deleteBINARYTREE(bt->left);
		_deleteBINARYTREE(bt->right);
		free(bt);
	}
}

//ɾ��
void deleteBINARYTREE(BINARYTREE bt)
{
	cutBINARYTREE(bt);
	_deleteBINARYTREE(bt);
}

//����
int  countBINARYTREE(BINARYTREE bt)
{
	if(bt)
	{
		return 1 + countBINARYTREE(bt->left) + countBINARYTREE(bt->right);
	}
	return 0;
}

//�߶�
int heightBINARYTREE(BINARYTREE bt)
{
	if(bt)
	{
		int l_h = heightBINARYTREE(bt->left);
		int r_h = heightBINARYTREE(bt->right);
		return ((l_h > r_h)? l_h:r_h) + 1;
	}
	return 0;
}

//ǰ��--�ݹ�
void recursion_pre_travelBINARYTREE(BINARYTREE bt)
{
	if(bt)
	{
		std::cout<<bt->data<<std::endl;
		recursion_pre_travelBINARYTREE(bt->left);
		recursion_pre_travelBINARYTREE(bt->right);
	}
}
//����
void recursion_mid_travelBINARYTREE(BINARYTREE bt)
{
	if(bt)
	{
		recursion_pre_travelBINARYTREE(bt->left);
		std::cout<<bt->data<<std::endl;
		recursion_pre_travelBINARYTREE(bt->right);
	}
}
//����
void recursion_post_travelBINARYTREE(BINARYTREE bt)
{
	if(bt)
	{
		recursion_pre_travelBINARYTREE(bt->left);
		recursion_pre_travelBINARYTREE(bt->right);
		std::cout<<bt->data<<std::endl;
	}
}

//ǰ��---�ǵݹ�
void pre_travelBINARYTREE(BINARYTREE bt)
{
	BINARYTREE stack[256];
	int top= 0;
	stack[top++] = bt;
	while(top != 0)
	{
		BINARYTREE q = stack[--top];
		std::cout<<q->data<<std::endl;
		if(q->right)
			stack[top++] = q->right;
		if(q->left)
			stack[top++] = q->left;
	}	
}
//����
void mid_travelBINARYTREE(BINARYTREE bt)
{
	BINARYTREE stack[256];
	int top= 0;
	if(bt->right)
		stack[top++] = bt->right;
	stack[top++] = bt;
	if(bt->left)
		stack[top++] = bt->left;
	while(top != 0)
	{
		BINARYTREE q = stack[--top];
		if(q->right)
			stack[top++] = q->right;
		stack[top++] = q;
		if(q->left)
			stack[top++] = q->left;
	}
}
//����
void post_travelBINARYTREE(BINARYTREE bt);

//����--�ǵݹ�
void level_travelBINARYTREE(BINARYTREE bt);