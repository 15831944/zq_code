#ifndef _SEARCH_TREE_H_
#define _SEARCH_TREE_H_

//������
//1�����ȶ�����
//2�����еĽڵ㶼��ѭ��С�Ҵ�Ĺ���

template <typename T> //T����֧��<������������ݲ������ظ�
class CSearchTree
{
	struct NODE
	{
		T data;
		NODE* left;
		NODE* right;
		NODE* parent;
	};
	NODE* m_Root;
	int m_Size;

	NODE* _Copy(NODE* p, NODE* parent);
	void _Clear(NODE* p);

public:

	CSearchTree();
	CSearchTree(const CSearchTree& that);
	CSearchTree& operator = (const CSearchTree& that);
	~CSearchTree();

	bool Insert(T data); //����
	bool Erase(T data); //ɾ��
	T* Find(T data); //ͨ���������õ����ݵ�ַ
	void Clear(); //���
	int Size(); //����
};

template <typename T>
typename CSearchTree<T>::NODE* CSearchTree<T>::_Copy(NODE* p, NODE* parent)
{
	if (p)
	{
		NODE* q = new NODE;
		q->data = p->data;
		q->left = _Copy(p->left, q);
		q->right = _Copy(p->right, q);
		q->parent = parent;
		return q;
	}
	else
		return 0;
}

template <typename T>
void CSearchTree<T>::_Clear(NODE* p)
{
	if (p)
	{
		_Clear(p->left);
		_Clear(p->right);
		delete p;
	}
}

template <typename T>
CSearchTree<T>::CSearchTree()
:
m_Root(0),
m_Size(0)
{}

template <typename T>
CSearchTree<T>::CSearchTree(const CSearchTree& that)
:
m_Root(_Copy(that.m_Root, 0)),
m_Size(that.m_Size)
{
	//m_Root = _Copy(that.m_Root, 0);
}

template <typename T>
CSearchTree<T>& CSearchTree<T>::operator = (const CSearchTree& that)
{
	if (this != &that)
	{
		Clear();
		m_Root = _Copy(that.m_Root, 0);
		m_Size = that.m_Size;
	}

	return *this;
}

template <typename T>
CSearchTree<T>::~CSearchTree()
{
	Clear();
}

template <typename T>
bool CSearchTree<T>::Insert(T data)
{
	//û�и��ڵ㣬�����ɸ��ڵ�
	if (!m_Root)
	{
		m_Root = new NODE;
		m_Root->data = data;
		m_Root->left = m_Root->right = m_Root->parent = 0;
		m_Size += 1;
		return true;
	}

	//����ָ��ָ����ڵ�
	NODE* p = m_Root, * q;
	while (p)
	{
		q = p;
		if (data < p->data)
			p = p->left;
		else if (p->data < data)
			p = p->right;
		else
			//����ҵ������ݺʹ������������򷵻�ʧ��
			return false;
	}

	//���������ѭ����ʱ��q��ָ����Ҫ����ڵ�ĸ��ڵ�
	NODE* n = new NODE;
	n->data = data;
	n->left = n->right = 0;

	//������������ָ��
	if (data < q->data)
		q->left = n;
	else
		q->right = n;
	n->parent = q;

	//���ȵ���
	m_Size += 1;

	return true;
}

template <typename T>
bool CSearchTree<T>::Erase(T data)
{
	NODE* p = m_Root;
	while (p)
	{
		if (data < p->data)
			p = p->left;
		else if (p->data < data)
			p = p->right;
		else
			break;
	}
	//�������ѭ��pΪ������ζ�ŵ�ǰ
	//��������û��ָ��������
	if (!p)
		return false;

	//���Ҷ���
	if (!p->left && !p->right)
	{
		//����Ǹ�
		if (p == m_Root)
		{
			delete m_Root;
			m_Root = 0;
		}
		//���Ǹ�
		else
		{
			//�Ǹ��ڵ�������
			if (p->parent->left == p)
				p->parent->left = 0;
			//�Ǹ��ڵ�������
			else
				p->parent->right = 0;
			delete p;
		}
	}
	//��������
	else if (p->left && !p->right)
	{
		//����Ǹ�
		if (p == m_Root)
		{
			m_Root = p->left;
			m_Root->parent = 0;
			delete p;
		}
		//���Ǹ�
		else
		{
			//�Ǹ��ڵ�������
			if (p->parent->left == p)
				p->parent->left = p->left;
			//�Ǹ��ڵ�������
			else
				p->parent->right = p->left;
			p->left->parent = p->parent;
			delete p;
		}
	}
	//��������
	else if (!p->left && p->right)
	{
		//����Ǹ�
		if (p == m_Root)
		{
			m_Root = p->right;
			m_Root->parent = 0;
			delete p;
		}
		//���Ǹ�
		else
		{
			//�Ǹ��ڵ�������
			if (p->parent->left == p)
				p->parent->left = p->right;
			//�Ǹ��ڵ�������
			else
				p->parent->right = p->right;
			p->right->parent = p->parent;
			delete p;
		}
	}
	//���Ҷ���
	else
	{
		//�ҵ�Ҫɾ���ڵ�p���������˳���µĺ���
		//�ڵ�q��Ȼ��q������ֱ�Ӹ�ֵp�����ݣ�
		//Ȼ������ͱ�Ϊɾ��q�ˣ���ôɾ��qһ����
		//���Ҷ��޻�������������

		//�ҵ���������µĺ���ڵ�
		NODE* q = p->right;
		while (q->left)
			q = q->left;

		//��ֵ����
		p->data = q->data;

		//���Ҷ���
		if (p == m_Root)
		{
			if (q->parent->left == q)
				q->parent->left = 0;
			else
				q->parent->right = 0;
			delete q;
		}
		//��������
		else
		{
			if (q->parent->left == q)
				q->parent->left = q->right;
			else
				q->parent->right = q->right;
			q->right->parent = q->parent;
			delete q;
		}
	}

	m_Size -= 1;

	return true;
}

template <typename T>
T* CSearchTree<T>::Find(T data)
{
	NODE* p = m_Root;
	while (p)
	{
		if (data < p->data)
			p = p->left;
		else if (p->data < data)
			p = p->right;
		else
			return &p->data;
	}

	//�˳�ѭ��֮�����ζ���Ҳ�����
	return 0;
}

template <typename T>
void CSearchTree<T>::Clear()
{
	_Clear(m_Root);
	m_Root = 0;
	m_Size = 0;
}

template <typename T>
int CSearchTree<T>::Size()
{
	return m_Size;
}

#endif