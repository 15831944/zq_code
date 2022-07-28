#ifndef _SQ_STACK_H_
#define _SQ_STACK_H_

template <typename T>
class CSqStack
{
	int m_Capacity; //����
	int m_Size; //����
	T* m_Data; //����

public:
	CSqStack();
	CSqStack(const CSqStack& that);
	CSqStack& operator = (const CSqStack& that);
	~CSqStack();

	bool Empty(); //�ж��Ƿ�Ϊ��ջ
	void Push(T data); //��ջ
	bool Pop(); //��ջ
	bool Top(T* data); //�õ�ջ��Ԫ��
	int Size(); //��С
};

template <typename T>
CSqStack<T>::CSqStack()
:
m_Capacity(8),
m_Size(0),
m_Data(new T[m_Capacity])
{}

template <typename T>
CSqStack<T>::CSqStack(const CSqStack& that)
:
m_Capacity(that.m_Capacity),
m_Size(that.m_Size),
m_Data(new T[m_Capacity])
{
	for (int i = 0; i < m_Size; ++i)
		m_Data[i] = that.m_Data[i];
}

template <typename T>
CSqStack<T>& CSqStack<T>::operator = (const CSqStack& that)
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
CSqStack<T>::~CSqStack()
{
	delete [] m_Data;
}

template <typename T>
bool CSqStack<T>::Empty()
{
	return m_Size == 0;
}

template <typename T>
void CSqStack<T>::Push(T data)
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
bool CSqStack<T>::Pop()
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
bool CSqStack<T>::Top(T* data)
{
	if (m_Size > 0)
	{
		*data = m_Data[m_Size - 1];
		return true;
	}
	else
		return false;
}

template <typename T>
int CSqStack<T>::Size()
{
	return m_Size;
}

#endif