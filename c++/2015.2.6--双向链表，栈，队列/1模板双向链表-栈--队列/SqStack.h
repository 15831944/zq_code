#ifndef _SQSTACK_H_
#define _SQSTACK_H_


//˳��ջ
template <typename T>
class CSqStack
{
	int m_Size;
	int m_Length;
	T* m_Data;
public:
	CSqStack(int size = 8);
	CSqStack(const CSqStack& that);
	CSqStack& operator = (const CSqStack& that);
	~CSqStack();

	//����
	void Push(T data);
	//����ջ��Ԫ��
	bool Pop(T* pdata);
	//��ȡջ��
	bool GetTop(T* pdata);
	//���
	void Clear();
	//����
	int Length();
};

template <typename T>
CSqStack<T>::CSqStack(int size)
:
m_Size(size),
m_Length(0),
m_Data(new T[m_Size])
{
}

template <typename T>
CSqStack<T>::CSqStack(const CSqStack& that)
:
m_Size(that.m_Size),
m_Length(that.m_Length),
m_Data(new T[m_Size])
{
	for(int i = 0; i < m_Length; ++i)
		m_Data[i] = that.m_Data[i];
}

template <typename T>
CSqStack<T>& CSqStack<T>::operator = (const CSqStack& that)
{
	if(this != &that)
	{
		delete []m_Data;
		m_Size = that.m_Size;
		m_Length = that.m_Length;
		m_Data = new T[m_Size];
		for(int i = 0; i < m_Length; ++i)
			m_Data[i] = that.m_Data[i];
	}
	return *this;
}

template <typename T>
CSqStack<T>::~CSqStack()
{
	if(m_Data)
		delete []m_Data;
}

//����
template <typename T>
void CSqStack<T>::Push(T data)
{
	if(m_Length == m_Size)
	{
		T* p = new T[m_Size *= 2];
		for(int i = 0; i < m_Length;++i)
			p[i] = m_Data[i];
		delete []m_Data;
		m_Data = p;
	}
	m_Data[m_Length++] = data;
}

//����ջ��Ԫ��
template <typename T>
bool CSqStack<T>::Pop(T* pdata)
{
	if(m_Length == 0)
		return false;
	*pdata = m_Data[m_Length - 1];
	m_Length -= 1;
	return true;
}

//��ȡջ��
template <typename T>
bool CSqStack<T>::GetTop(T* pdata)
{
	if(m_Length == 0)
		return false;
	*pdata = m_Data[m_Length - 1];
	return true;
}

//���
template <typename T>
void CSqStack<T>::Clear()
{
	m_Length = 0;
}

//����
template <typename T>
int CSqStack<T>::Length()
{
	return m_Length;
}

#endif