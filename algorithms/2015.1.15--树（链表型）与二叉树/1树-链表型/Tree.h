#ifndef _TREE_LINKLIST_H_
#define _TREE_LINKLIST_H_

#define TDATA int

typedef struct _TREE
{
	TDATA data;//����
	_TREE* parent;//���ڵ�ָ��
	_TREE* left_child;//����ָ��
	_TREE* right_brother;//���ֵ�ָ��
}* TREE;

//����
TREE createTREE();
//�Ͽ������丸�ڵ�Ĺ�ϵ
TREE cutTREE(TREE tree);
//����
void insertTREE(TREE tree1,TREE tree2);
//ɾ��
void deleteTREE(TREE tree);
//����
int countTREE(TREE tree);
//�߶�
int heigthTREE(TREE tree);

#endif