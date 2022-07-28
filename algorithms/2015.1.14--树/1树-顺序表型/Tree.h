#ifndef _TREE_SQLIST_H_
#define _TREE_SQLIST_H_

#define TDATA int

typedef struct _TREE
{
	TDATA data;//����
	_TREE* parent;//���ڵ�ָ��
	int child_size ;//�ӽڵ�˳�������
	int child_length;//�ӽڵ�˳�����
	_TREE** child_data;//�ӽڵ�˳�������
}* TREE;

//����
TREE createTREE(int child_size = 4);
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