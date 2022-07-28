#ifndef _SQ_QUEUE_H_
#define _SQ_QUEUE_H_

template <typename T>
class CSqQueue
{
	int m_Capacity; //����
	int m_Size; //����
	T* m_Data; //����
	int m_Head; //��ͷ
	int m_Tail; //��β

public:
	CSqQueue(int Capacity = 4);
	CSqQueue(const CSqQueue& that);
	CSqQueue& operator = (const CSqQueue& that);
	~CSqQueue();

	bool Empty(); //�ж��Ƿ�Ϊ�ն���
	void Push(T data); //�����
	bool Pop(); //������
	bool Front(T* data); //�õ���ͷԪ��
	bool Back(T* data); //�õ���βԪ��
	int Size(); //��С
};

template <typename T>
CSqQueue<T>::CSqQueue(int Capacity)
:
m_Capacity(Capacity),
m_Size(0),
m_Data(new T[m_Capacity]),
m_Head(0),
m_Tail(0)
{}

template <typename T>
CSqQueue<T>::CSqQueue(const CSqQueue& that)
:
m_Capacity(that.m_Capacity),
m_Size(that.m_Size),
m_Data(new T[m_Capacity]),
m_Head(0),
m_Tail(m_Size)
{
	for (int i = 0; i < m_Size; ++i)
		m_Data[i] = that.m_Data[(that.m_Head + i) % that.m_Capacity];
}

template <typename T>
CSqQueue<T>& CSqQueue<T>::operator = (const CSqQueue& that)
{
	if (this != &that)
	{
		delete [] m_Data;

		m_Capacity = that.m_Capacity;
		m_Size = that.m_Size;
		m_Data = new T[m_Capacity];
		m_Head = 0;
		m_Tail = m_Size;
		for (int i = 0; i < m_Size; ++i)
			m_Data[i] = that.m_Data[(that.m_Head + i) % that.m_Capacity];	
	}
	return *this;
}

template <typename T>
CSqQueue<T>::~CSqQueue()
{
	delete [] m_Data;
}

template <typename T>
bool CSqQueue<T>::Empty()
{
	return m_Size == 0;
}

template <typename T>
void CSqQueue<T>::Push(T data)
{
	if (m_Size == m_Capacity)
	{
		T* p = new T[m_Capacity *= 2];
		for (int i = 0; i < m_Size; ++i)
			p[i] = m_Data[(m_Head + i) % m_Size];
		delete [] m_Data;
		m_Data = p;
		m_Head = 0;
		m_Tail = m_Size;
	}
	m_Data[m_Tail] = data;
	m_Tail = (m_Tail + 1) % m_Capacity;
	m_Size += 1;
}

template <typename T>
bool CSqQueue<T>::Pop()
{
	if (m_Size > 0)
	{
		m_Head = (m_Head + 1) % m_Capacity;
		m_Size -= 1;
		return true;
	}
	else
		return false;
}

template <typename T>
bool CSqQueue<T>::Front(T* data)
{
	if (m_Size > 0)
	{
		*data = m_Data[m_Head];
		return true;
	}
	else
		return false;
}

template <typename T>
bool CSqQueue<T>::Back(T* data)
{
	if (m_Size > 0)
	{
		*data = m_Data[m_Tail > 0 ? m_Tail - 1 : m_Capacity - 1];
		return true;
	}
	else
		return false;
}

template <typename T>
int CSqQueue<T>::Size()
{
	return m_Size;
}

#endif