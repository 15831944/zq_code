#ifndef _MY_VECTOR_H_
#define _MY_VECTOR_H_

#include <assert.h>

template <typename T>
class my_vector
{
	int m_capacity;
	int m_size;
	T* m_data;

public:

	my_vector(int capacity = 8);
	my_vector(const my_vector& that);
	my_vector& operator = (const my_vector& that);
	~my_vector();

	void push_back(T data);
	void clear();
	int size();
	T& at(int index);
	
	class iterator
	{
		template <typename T>
		friend class my_vector;

		my_vector* p; //ָ���my_vector
		int cur; //��ǰ��ʾ��my_vector�е��±�

	public:
		iterator();
		bool operator != (const iterator& that);
		iterator& operator ++ ();
		iterator operator ++ (int);
		iterator& operator -- ();
		iterator operator -- (int);
		iterator operator + (int num);
		iterator& operator += (int num);
		iterator operator - (int num);
		iterator& operator -= (int num);
		T& operator * ();
		T* operator -> ();
	};

	iterator begin();
	iterator end();
	iterator insert(iterator& it, T data);
	iterator erase(iterator& it);
};

template <typename T>
my_vector<T>::my_vector(int capacity)
:
m_capacity(capacity),
m_size(0),
m_data(new T[m_capacity])
{}

template <typename T>
my_vector<T>::my_vector(const my_vector& that)
:
m_capacity(that.m_capacity),
m_size(that.m_size),
m_data(new T[m_capacity])
{
	for (int i = 0; i < m_size; ++i)
		m_data[i] = that.m_data[i];
}

template <typename T>
my_vector<T>& my_vector<T>::operator = (const my_vector& that)
{
	if (this != &that)
	{
		delete [] m_data;
		m_capacity = that.m_capacity;
		m_size = that.m_size;
		m_data = new T[m_capacity];
		for (int i = 0; i < m_size; ++i)
			m_data[i] = that.m_data[i];
	}

	return *this;
}

template <typename T>
my_vector<T>::~my_vector()
{
	delete [] m_data;
}

template <typename T>
void my_vector<T>::push_back(T data)
{
	if (m_size == m_capacity)
	{
		T* p = new T[m_capacity *= 2];
		for (int i = 0; i < m_size; ++i)
			p[i] = m_data[i];
		delete [] m_data;
		m_data = p;
	}
	m_data[m_size++] = data;
}

template <typename T>
void my_vector<T>::clear()
{
	m_size = 0;
}

template <typename T>
int my_vector<T>::size()
{
	return m_size;
}

template <typename T>
T& my_vector<T>::at(int index)
{
	assert(index >= 0 && index < m_size);
	return m_data[index];
}

template <typename T>
my_vector<T>::iterator::iterator()
:
p(0), //��ʼ��ָ���my_vectorΪ��
cur(-1) //��ʼ��������±�Ϊ-1
{}

template <typename T>
bool my_vector<T>::iterator::operator != (const iterator& that)
{
	return p != that.p || cur != that.cur;
}

//���ģ�����к�������ֵ������ģ�����е��࣬��ôǰ��������
//typename�Ա�ʾ���������һ��ģ�����е���

template <typename T>
typename my_vector<T>::iterator& my_vector<T>::iterator::operator ++ ()
{
	//���Ե�ǰ��������ʾ��λ���ǿ��Խ���ǰ��++
	assert(p && cur >= 0 && cur < p->m_size);
	++cur;
	return *this;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::iterator::operator ++ (int)
{
	//���Ե�ǰ��������ʾ��λ���ǿ��Խ��к���++
	assert(p && cur >= 0 && cur < p->m_size);
	iterator it = *this;
	cur++;
	return it;
}

template <typename T>
typename my_vector<T>::iterator& my_vector<T>::iterator::operator -- ()
{
	//���Ե�ǰ��������ʾ��λ���ǿ��Խ���ǰ��--
	assert(p && cur > 0 && cur <= p->m_size);
	--cur;
	return *this;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::iterator::operator -- (int)
{
	//���Ե�ǰ��������ʾ��λ���ǿ��Խ��к���--
	assert(p && cur > 0 && cur <= p->m_size);
	iterator it = *this;
	cur--;
	return it;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::iterator::operator + (int num)
{
	assert(p && cur + num >= 0 && cur + num <= p->m_size);
	iterator it;
	it.p = p;
	it.cur = cur + num;
	return it;
}

template <typename T>
typename my_vector<T>::iterator& my_vector<T>::iterator::operator += (int num)
{
	assert(p && cur + num >= 0 && cur + num <= p->m_size);
	cur += num;
	return *this;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::iterator::operator - (int num)
{
	assert(p && cur - num >= 0 && cur - num <= p->m_size);
	iterator it;
	it.p = p;
	it.cur = cur - num;
	return it;
}

template <typename T>
typename my_vector<T>::iterator& my_vector<T>::iterator::operator -= (int num)
{
	assert(p && cur - num >= 0 && cur - num <= p->m_size);
	cur -= num;
	return *this;
}

template <typename T>
T& my_vector<T>::iterator::operator * ()
{
	//���Ե�ǰ��������ʾ��λ���ǿ��Եõ�����
	assert(p && cur >= 0 && cur < p->m_size);
	return p->m_data[cur];
}

template <typename T>
T* my_vector<T>::iterator::operator -> ()
{
	//���Ե�ǰ��������ʾ��λ���ǿ��Եõ�����
	assert(p && cur >= 0 && cur < p->m_size);
	return p->m_data + cur;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::begin()
{
	iterator it;
	it.p = this;
	it.cur = 0;
	return it;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::end()
{
	iterator it;
	it.p = this;
	it.cur = m_size;
	return it;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::insert(iterator& it, T data)
{
	iterator r = end();

	//һ��������Ч�ͷ���endλ��
	if (it.p != this || it.cur < 0 || it.cur > m_size)
		return r;

	//����
	if (m_size == m_capacity)
	{
		T* p = new T[m_capacity *= 2];
		for (int i = 0; i < m_size; ++i)
			p[i] = m_data[i];
		delete [] m_data;
		m_data = p;
	}

	//����
	int move = m_size - it.cur;
	for (int i = 0; i < move; ++i)
		m_data[m_size - i] = m_data[m_size - 1 - i];
	m_data[it.cur] = data;
	m_size += 1;

	//���÷���ֵ
	r = it;

	//���ô���ĵ�������Ч
	it.p = 0;
	it.cur = -1;

	//����
	return r;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::erase(iterator& it)
{
	assert(it.p == this && it.cur >= 0 && it.cur < m_size);

	//ɾ��
	int move = m_size - it.cur - 1;
	for (int i = 0; i < move; ++i)
		m_data[it.cur + i] = m_data[it.cur + 1 + i];
	m_size -= 1;

	//���÷���ֵ
	iterator r = it;

	//���ô���ĵ�������Ч
	it.p = 0;
	it.cur = -1;

	//����
	return r;
}

#endif