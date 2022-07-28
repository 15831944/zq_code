#ifndef _SQ_LIST_H_
#define _SQ_LIST_H_

//C++�Ѽ������е�C����ͷ�ļ�������һ���ٰ�װ��ȥ����.h��Ȼ��
//��ǰ�����c�Ա�ʾ����ļ��Ǳ�׼C���Ե��ļ�
//#include <assert.h>
#include <cassert>

template <typename T>
class CSqList
{
	int m_Capacity; //����
	int m_Size; //����
	T* m_Data; //����

public:
	
	CSqList();
	CSqList(const CSqList& that);
	CSqList& operator = (const CSqList& that);
	~CSqList();

	//˳�����Խ��к�����
	void Push_Back(T data);

	//˳�����Խ��к󵯳�
	bool Pop_Back();

	//��С
	int Size();

	//������û������Ĳ�����
	T* At(int pos);

	void Clear();

	//��������Ϊһ�����е���Ҫ����Ϊ���У�����
	//���ⲿ�ñ���::����
	class Iterator
	{
		template <typename T>
		friend class CSqList;

		//������Ҫ֪���Լ����ĸ�˳�������
		//��ϵ������Ҫ�洢һ��ָ��˳����ָ��
		CSqList* p;

		//��Ϊ˳��洢��˳�����������ڲ�Ҫ
		//����һ���±�
		int i;

	public:

		//����
		Iterator();

		//�����ж�
		bool operator != (const Iterator& that);

		//ǰ������
		Iterator& operator ++ ();

		//������
		T& operator * ();

		//��ַ����
		T* operator -> ();
	};

	//���������
	Iterator Insert(T data, Iterator it);
	Iterator Erase(Iterator it);
	Iterator Begin();
	Iterator End();
};

template <typename T>
CSqList<T>::CSqList()
:
m_Capacity(8),
m_Size(0),
m_Data(new T[m_Capacity])
{}

template <typename T>
CSqList<T>::CSqList(const CSqList& that)
:
m_Capacity(that.m_Capacity),
m_Size(that.m_Size),
m_Data(new T[m_Capacity])
{
	for (int i = 0; i < m_Size; ++i)
		m_Data[i] = that.m_Data[i];
}

template <typename T>
CSqList<T>& CSqList<T>::operator = (const CSqList& that)
{
	if (this != &that)
	{
		delete [] m_Data;

		m_Capacity = that.m_Capacity;
		m_Size = that.m_Size;
		m_Data = new T[m_Capacity];

		for (int i = 0; i < m_Size; ++i)
			m_Data[i] = that.m_Data[i];
	}
	return *this;
}

template <typename T>
CSqList<T>::~CSqList()
{
	//delete�����������ֺ���ĵ�ַ��0��ʲô������
	delete [] m_Data;
}

template <typename T>
void CSqList<T>::Push_Back(T data)
{
	if (m_Size == m_Capacity)
	{
		T* p = new T[m_Capacity *= 2];
		for (int i = 0; i < m_Size; ++i)
			p[i] = m_Data[i];
		delete [] m_Data;
		m_Data = p;
	}
	m_Data[m_Size++] = data;
}

template <typename T>
bool CSqList<T>::Pop_Back()
{
	if (m_Size > 0)
	{
		m_Size -= 1;
		return true;
	}
	else
		return false;
}

template <typename T>
int CSqList<T>::Size()
{
	return m_Size;
}

template <typename T>
void CSqList<T>::Clear()
{
	m_Size = 0;
}

template <typename T>
T* CSqList<T>::At(int pos)
{
	return pos >= 0 && pos < m_Size ? m_Data + pos : 0;
}

template <typename T>
CSqList<T>::Iterator::Iterator()
:
p(0),
i(-1)
{}

template <typename T>
bool CSqList<T>::Iterator::operator != (const Iterator& that)
{
	return p != that.p || i != that.i;
}

template <typename T>
typename CSqList<T>::Iterator& CSqList<T>::Iterator::operator ++ ()
{
	//���ԣ�������ָ���±������ڵ���0С�ڳ��ȣ�
	assert(p && i >= 0 && i < p->m_Size);
	i += 1;
	return *this;
}

template <typename T>
T& CSqList<T>::Iterator::operator * ()
{
	assert(p && i >= 0 && i < p->m_Size);
	return p->m_Data[i];
}

template <typename T>
T* CSqList<T>::Iterator::operator -> ()
{
	assert(p && i >= 0 && i < p->m_Size);
	return &p->m_Data[i];
}

//[begin,end]
//
//push_back(1);
//
//[begin,1][end]
//
//push_back(2);
//
//[begin,1][2][end]
//
//push_back(3);
//
//[begin,1][2][3][end]

template <typename T>
typename CSqList<T>::Iterator CSqList<T>::Insert(T data, Iterator it)
{
	//����֮��Ӧ�÷��ش������λ�õĵ�����

	assert(it.p == this && it.i >= 0 && it.i <= m_Size);

	if (m_Size == m_Capacity)
	{
		T* p = new T[m_Capacity *= 2];
		for (int i = 0; i < m_Size; ++i)
			p[i] = m_Data[i];
		delete [] m_Data;
		m_Data = p;
	}

	int m = m_Size - it.i;
	for (int i = 0; i < m; ++i)
		m_Data[m_Size - i] = m_Data[m_Size - 1 - i];
	m_Data[it.i] = data;
	m_Size += 1;

	return it;
}

template <typename T>
typename CSqList<T>::Iterator CSqList<T>::Erase(Iterator it)
{
	assert(it.p == this && it.i >= 0 && it.i < m_Size);

	int m = m_Size - it.i - 1;
	for (int i = 0; i < m; ++i)
		m_Data[it.i + i] = m_Data[it.i + 1 + i];
	m_Size -= 1;

	return it;
}

template <typename T>
typename CSqList<T>::Iterator CSqList<T>::Begin()
{
	Iterator it;
	it.p = this;
	it.i = 0;
	return it;
}

template <typename T>
typename CSqList<T>::Iterator CSqList<T>::End()
{
	Iterator it;
	it.p = this;
	it.i = m_Size;
	return it;
}

#endif