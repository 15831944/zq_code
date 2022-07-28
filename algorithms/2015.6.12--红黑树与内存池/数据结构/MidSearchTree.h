#ifndef _MID_SEARCH_TREE_H_
#define _MID_SEARCH_TREE_H_

//������
//1�����ȶ�����
//2�����еĽڵ㶼��ѭ��С�Ҵ�Ĺ���

template <typename T> //T����֧��<������������ݲ������ظ�
class CMidSearchTree
{
	struct NODE
	{
		T data;
		NODE* left;
		NODE* right;
		NODE* parent;
		NODE* pre; //ǰ��ڵ�ָ��
		NODE* next; //����ڵ�ָ��
	};
	NODE* m_Root; //������������
	NODE* m_Head; //ͷ��ѭ��˫������
	int m_Size;

	NODE* _Copy(NODE* p, NODE* parent);
	void _Clear(NODE* p);

public:

	CMidSearchTree();
	CMidSearchTree(const CMidSearchTree& that);
	CMidSearchTree& operator = (const CMidSearchTree& that);
	~CMidSearchTree();

	bool Insert(T data); //����
	bool Erase(T data); //ɾ��
	T* Find(T data); //ͨ���������õ����ݵ�ַ
	void Clear(); //���
	int Size(); //����

	void PrintLink(); //��ӡ

	//������
};

template <typename T>
void CMidSearchTree<T>::PrintLink()
{
	for (NODE* p = m_Head->next; p != m_Head; p = p->next)
		std::cout<<p->data<<" ";
	std::cout<<std::endl;
}

template <typename T>
typename CMidSearchTree<T>::NODE* CMidSearchTree<T>::_Copy(NODE* p, NODE* parent)
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
void CMidSearchTree<T>::_Clear(NODE* p)
{
	if (p)
	{
		_Clear(p->left);
		_Clear(p->right);
		delete p;
	}
}

template <typename T>
CMidSearchTree<T>::CMidSearchTree()
:
m_Root(0),
m_Head(new NODE),
m_Size(0)
{
	//��������ͷ�ڵ�
	m_Head->pre = m_Head->next = m_Head;
}

template <typename T>
CMidSearchTree<T>::CMidSearchTree(const CMidSearchTree& that)
:
m_Root(_Copy(that.m_Root, 0)),
m_Size(that.m_Size)
{
	//m_Root = _Copy(that.m_Root, 0);

	//���������������ָ�뼴��
}

template <typename T>
CMidSearchTree<T>& CMidSearchTree<T>::operator = (const CMidSearchTree& that)
{
	if (this != &that)
	{
		Clear();
		m_Root = _Copy(that.m_Root, 0);
		m_Size = that.m_Size;
		
		//���������������ָ�뼴��
	}

	return *this;
}

template <typename T>
CMidSearchTree<T>::~CMidSearchTree()
{
	Clear();
	delete m_Head;
}

template <typename T>
bool CMidSearchTree<T>::Insert(T data)
{
	//û�и��ڵ㣬�����ɸ��ڵ�
	if (!m_Root)
	{
		m_Root = new NODE;
		m_Root->data = data;

		//���ö�����ָ��
		m_Root->left = m_Root->right = m_Root->parent = 0;

		//��������ָ��
		m_Head->pre = m_Head->next = m_Root;
		m_Root->pre = m_Root->next = m_Head;

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
	{
		q->left = n;
		
		//��������ָ��
		n->pre = q->pre;
		n->next = q;
		q->pre->next = n;
		q->pre = n;
	}
	else
	{
		q->right = n;

		//��������ָ��
		n->pre = q;
		n->next = q->next;
		q->next->pre = n;
		q->next = n;
	}
	n->parent = q;

	//���ȵ���
	m_Size += 1;

	return true;
}

template <typename T>
bool CMidSearchTree<T>::Erase(T data)
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
			m_Head->pre = m_Head->next = m_Head;
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
			p->pre->next = p->next;
			p->next->pre = p->pre;
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
			p->pre->next = p->next;
			p->next->pre = p->pre;
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
			p->pre->next = p->next;
			p->next->pre = p->pre;
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
			p->pre->next = p->next;
			p->next->pre = p->pre;
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
			p->pre->next = p->next;
			p->next->pre = p->pre;
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
		//NODE* q = p->right;
		//while (q->left)
		//	q = q->left;

		//��������ʽ�ṹ֮������Ĵ���
		//����������һ�������
		NODE* q = p->next;

		//��ֵ����
		p->data = q->data;

		//���Ҷ���
		if (p == m_Root)
		{
			if (q->parent->left == q)
				q->parent->left = 0;
			else
				q->parent->right = 0;
			q->pre->next = q->next;
			q->next->pre = q->pre;
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
			q->pre->next = q->next;
			q->next->pre = q->pre;
			delete q;
		}
	}

	m_Size -= 1;

	return true;
}

template <typename T>
T* CMidSearchTree<T>::Find(T data)
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
void CMidSearchTree<T>::Clear()
{
	_Clear(m_Root);
	m_Root = 0;
	m_Size = 0;
}

template <typename T>
int CMidSearchTree<T>::Size()
{
	return m_Size;
}



#endif