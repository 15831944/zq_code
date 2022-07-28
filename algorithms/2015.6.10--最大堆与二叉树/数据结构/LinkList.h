#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

template <typename T>
class CLinkList
{
	struct NODE
	{
		T data; //����
		NODE* pre; //ǰָ��
		NODE* next; //��ָ��
	};
	NODE* m_Head; //ͷ���
	int m_Size; //����

	void _Copy(const CLinkList& that);

public:
	
	CLinkList();
	CLinkList(const CLinkList& that);
	CLinkList& operator = (const CLinkList& that);
	~CLinkList();

	void Push_Front(T data);
	bool Pop_Front();
	void Push_Back(T data);
	bool Pop_Back();
	int Size();
	void Clear();

	//������û������Ĳ�����
	//T* At(int pos);

	class Iterator
	{
		template <typename T>
		friend class CLinkList;

		CLinkList* p;
		NODE* i;

	public:

		Iterator();
		bool operator != (const Iterator& that);
		Iterator& operator ++ ();
		T& operator * ();
		T* operator -> ();
	};

	//���������
	Iterator Insert(T data, Iterator it);
	Iterator Erase(Iterator it);
	Iterator Begin();
	Iterator End();
};

template <typename T>
void CLinkList<T>::_Copy(const CLinkList& that)
{
	//this��ǰ�����ǿձ�
	NODE* p = that.m_Head->next;
	NODE* q = m_Head;

	//ѭ��������
	for (; p != that.m_Head; p = p->next)
	{
		NODE* r = new NODE;

		r->data = p->data;

		q->next = r;
		r->pre = q;
		q = r;
	}
	q->next = m_Head;
	m_Head->pre = q;
	m_Size = that.m_Size;
}

template <typename T>
CLinkList<T>::CLinkList()
:
m_Head(new NODE),
m_Size(0)
{
	m_Head->pre = m_Head->next = m_Head;
}

template <typename T>
CLinkList<T>::CLinkList(const CLinkList& that)
:
m_Head(new NODE),
m_Size(0)
{
	m_Head->pre = m_Head->next = m_Head;
	_Copy(that);
}

template <typename T>
CLinkList<T>& CLinkList<T>::operator = (const CLinkList& that)
{
	if (this != &that)
	{
		Clear();
		_Copy(that);
	}
	return *this;
}

template <typename T>
CLinkList<T>::~CLinkList()
{
	Clear();
	delete m_Head;
}

template <typename T>
void CLinkList<T>::Push_Front(T data)
{
	NODE* p = new NODE;
	p->data = data;

	p->pre = m_Head;
	p->next = m_Head->next;
	m_Head->next->pre = p;
	m_Head->next = p;

	m_Size += 1;
}

template <typename T>
bool CLinkList<T>::Pop_Front()
{
	if (m_Size > 0)
	{
		NODE* p = m_Head->next;
		NODE* q = p->next;

		//����ָ��
		q->pre = m_Head;
		m_Head->next = q;

		//�ͷ��ڴ�
		delete p;

		m_Size -= 1;

		return true;
	}
	else
		return false;
}

template <typename T>
void CLinkList<T>::Push_Back(T data)
{
	NODE* p = new NODE;
	p->data = data;

	p->pre = m_Head->pre;
	p->next = m_Head;
	m_Head->pre->next = p;
	m_Head->pre = p;

	m_Size += 1;
}

template <typename T>
bool CLinkList<T>::Pop_Back()
{
	if (m_Size > 0)
	{
		//m_Head->pre��m_Head��ǰ��

		//p�õ�m_Head->pre��ǰ��
		NODE* p = m_Head->pre;
		NODE* q = p->pre;

		//����ָ��
		q->next = m_Head;
		m_Head->pre = q;

		//�ͷ��ڴ�
		delete p;

		m_Size -= 1;

		return true;
	}
	else
		return false;
}

template <typename T>
int CLinkList<T>::Size()
{
	return m_Size;
}

template <typename T>
void CLinkList<T>::Clear()
{
	NODE* p = m_Head->next;
	while (p != m_Head)
	{
		NODE* q = p->next;
		delete p;
		p = q;
	}
	m_Head->pre = m_Head->next = m_Head;
	m_Size = 0;
}

template <typename T>
CLinkList<T>::Iterator::Iterator()
:
//�����������������ָ��
p(0),
i(0)
{}

template <typename T>
bool CLinkList<T>::Iterator::operator != (const Iterator& that)
{
	return p != that.p || i != that.i;
}

template <typename T>
typename CLinkList<T>::Iterator& CLinkList<T>::Iterator::operator ++ ()
{
	assert(p && i != p->m_Head);
	i = i->next;
	return *this;
}

template <typename T>
T& CLinkList<T>::Iterator::operator * ()
{
	assert(p && i != p->m_Head);
	return i->data;
}

template <typename T>
T* CLinkList<T>::Iterator::operator -> ()
{
	assert(p && i != p->m_Head);
	return &i->data;
}

template <typename T>
typename CLinkList<T>::Iterator CLinkList<T>::Insert(T data, Iterator it)
{
	assert(it->p == this && it->i);

	NODE* p = new NODE;
	p->data = data;
	p->next = it.i;
	p->pre = it.i->pre;
	p->pre->next = p;
	p->next->pre = p;

	//�޸�it������
	it.i = p;

	m_Size += 1;

	return it;
}

template <typename T>
typename CLinkList<T>::Iterator CLinkList<T>::Erase(Iterator it)
{
	assert(it.p == this && it.i && it.i != m_Head);

	NODE* r = it.i->next;
	it.i->pre->next = it.i->next;
	it.i->next->pre = it.i->pre;
	delete it.i;
	m_Size -= 1;

	it.i = r;
	return it;
}

template <typename T>
typename CLinkList<T>::Iterator CLinkList<T>::Begin()
{
	Iterator it;
	it.p = this;
	it.i = m_Head->next; //Begin
	return it;
}

template <typename T>
typename CLinkList<T>::Iterator CLinkList<T>::End()
{
	Iterator it;
	it.p = this;
	it.i = m_Head; //End
	return it;
}

#endif