#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

//��������binary tree

template <typename T>
struct _BTN
{
	T data;
	_BTN* left; //������
	_BTN* right; //������
	_BTN* parent; //���ڵ�
};

template <typename T>
_BTN<T>* createBTN()
{
	_BTN<T>* p = new _BTN<T>;
	p->left = p->right = p->parent = 0;
	return p;
}

//�Ͽ�p���丸�ڵ����ϵ
template <typename T>
_BTN<T>* cutBTN(_BTN<T>* p)
{
	//p����Ϊ����p�����и��ڵ�
	if (p && p->parent) //����д��if (p->parent && p)
	{
		//p�����ĸ��ڵ��������
		if (p == p->parent->left)
			p->parent->left = 0;
		else
			p->parent->right = 0;
		p->parent = 0;
	}
	return p;
}

//����ĺ����ǽ�s���뵽p����߻��ұ���Ϊ��������������
//ע�⣺
//1��p������ԭ�����нڵ㣬����Ӧ�ý�s��ȥ�滻ԭ���Ľڵ㣬������
//   ԭ���Ľڵ�
//2��p������ܲ���һ�����ڵ㣬��ô�����ȶϿ�s������ԭ���ڵ�֮��
//   ����ϵ
template <typename T>
_BTN<T>* insertBTN(_BTN<T>* p, _BTN<T>* s, bool left = true)
{
	cutBTN(s);
	if (left)
	{
		//�õ�pԭ�������������п�����0��
		_BTN<T>* q = p->left;
		cutBTN(q);
		p->left = s;
		s->parent = p;
		return q;
	}
	else
	{
		//�õ�pԭ�������������п�����0��
		_BTN<T>* q = p->right;
		cutBTN(q);
		p->right = s;
		s->parent = p;
		return q;
	}
}

//template <typename T>
//void pre_printBTN(_BTN<T>* p)
//{
//	//���������ӡ
//	if (p)
//	{
//		std::cout<<p->data<<' ';
//		pre_printBTN(p->left);
//		pre_printBTN(p->right);
//	}
//}
//
//template <typename T>
//void mid_printBTN(_BTN<T>* p)
//{
//	//���������ӡ
//	if (p)
//	{
//		mid_printBTN(p->left);
//		std::cout<<p->data<<' ';
//		mid_printBTN(p->right);
//	}
//}
//
//template <typename T>
//void post_printBTN(_BTN<T>* p)
//{
//	//���������ӡ
//	if (p)
//	{
//		post_printBTN(p->left);
//		post_printBTN(p->right);
//		std::cout<<p->data<<' ';
//	}
//}

template <typename T>
int sizeBTN(_BTN<T>* p)
{
	if (p)
		return 1 + sizeBTN(p->left) + sizeBTN(p->right);
	else
		return 0;
}

template <typename T>
int heightBTN(_BTN<T>* p)
{
	if (p)
	{
		//�ȵõ��������������ĸ߶�
		int left_h = heightBTN(p->left);
		int right_h = heightBTN(p->right);

		//�����������������ϸߵ���
		//һ�������ĸ߶ȼ�һ
		return (left_h > right_h ? left_h : right_h) + 1;
	}
	else
		return 0;
}

template <typename T>
void _eraseBTN(_BTN<T>* p)
{
	if (p)
	{
		_eraseBTN(p->left);
		_eraseBTN(p->right);
		delete p;
	}
}

template <typename T>
void eraseBTN(_BTN<T>* p)
{
	//�ȶϿ�p�͸��ڵ����ϵ
	cutBTN(p);

	//�ݹ�ɾ��p�����нڵ�
	_eraseBTN(p);
}

template <typename T>
_BTN<T>* _copyBTN(_BTN<T>* p, _BTN<T>* parent)
{
	if (p)
	{
		//�����½ڵ�
		_BTN<T>* n = new _BTN<T>;

		//�õ�����
		n->data = p->data;

		//�ݹ������������п�������
		//�����½ڵ�ĸ��ڵ�
		n->left = _copyBTN(p->left, n);
		n->right = _copyBTN(p->right, n);
		n->parent = parent;

		return n;
	}
	else
		return 0;
}

template <typename T>
_BTN<T>* copyBTN(_BTN<T>* p)
{
	return _copyBTN(p, 0);
}

//������ö�����p��q��ȫһ
//�����ṹһ����������Ҳһ
//��������ô������
template <typename T>
bool equalBTN(_BTN<T>* p, _BTN<T>* q)
{
	
}

//���������ӡ
template <typename T>
void level_printBTN(_BTN<T>* p)
{
	
}

#endif