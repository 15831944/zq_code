#ifndef _SET_H_
#define _SET_H_

//˳�򼯺��е��������ݶ��ǰ���һ���Ĵ�С˳������
//�ģ���С���󣩣����ҵ�ʱ������۰���Ҽ���

template <typename T> //T����֧��<���������׼���жԿ��ԱȽϴ�С�����ݶ�Ҫ�����<�������
class CSet
{
	int m_Capacity; //����
	int m_Size; //����
	T* m_Data; //����

public:
	CSet();
	CSet(const CSet& that);
	CSet& operator = (const CSet& that);
	~CSet();

	//�����У�������Ψһ�ģ�Ҳ����˵
	//��������ͬ�����ݣ�ʹ��˳��洢
	//ʵ�ֵļ��ϣ���Ҫ���ڽ��в���

	bool Insert(T data); //����
	bool Erase(T data); //ɾ��
	T* Find(T data); //ͨ���������õ����ݵ�ַ
	T* At(int i); //ͨ���±�õ����ݵ�ַ
	void Clear(); //���
	int Size(); //����
};

template <typename T>
CSet<T>::CSet()
:
m_Capacity(8),
m_Size(0),
m_Data(new T[m_Capacity])
{}

template <typename T>
CSet<T>::CSet(const CSet& that)
:
m_Capacity(that.m_Capacity),
m_Size(that.m_Size),
m_Data(new T[m_Capacity])
{
	for (int i = 0; i < m_Size; ++i)
		m_Data[i] = that.m_Data[i];
}
template <typename T>
CSet<T>& CSet<T>::operator = (const CSet& that)
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
CSet<T>::~CSet()
{
	delete [] m_Data;
}

template <typename T>
bool CSet<T>::Insert(T data)
{
	//�۰���뷨��ͨ���۰���ҵõ�Ӧ�ò����λ��p����
	//���p����������ݣ����Ա�֤���˳��洢�����黹
	//�����кõ�
	int begin = 0, end = m_Size - 1;
	while (begin <= end)
	{
		int half = (begin + end) / 2;
		if (data < m_Data[half])
			end = half - 1;
		else if (m_Data[half] < data)
			begin = half + 1;
		else
			//��������ͬ������
			return false;
	}

	//begin����Ӧ�÷��������ݵ�λ��

	if (m_Size == m_Capacity)
	{
		T* p = new T[m_Capacity *= 2];
		for (int i = 0; i < m_Size; ++i)
			p[i] = m_Data[i];
		delete [] m_Data;
		m_Data = p;
	}

	int m = m_Size - begin;

	//˳��ʵ�ֵļ��ϵ�ƿ����������Ĵ���
	for (int i = 0; i < m; ++i)
		m_Data[m_Size - i] = m_Data[m_Size - 1 - i];

	m_Data[begin] = data;
	m_Size += 1;

	return true;
}

template <typename T>
bool CSet<T>::Erase(T data)
{
	int begin = 0, end = m_Size - 1;
	while (begin <= end)
	{
		int half = (begin + end) / 2;
		if (data < m_Data[half])
			end = half - 1;
		else if (m_Data[half] < data)
			begin = half + 1;
		else
		{
			int m = m_Size - half - 1;

			//˳��ʵ�ֵļ��ϵ�ƿ����������Ĵ���
			for (int i = 0; i < m; ++i)
				m_Data[half + i] = m_Data[half + 1 + i];

			m_Size -= 1;
			return false;
		}
	}

	return false;
}

template <typename T>
T* CSet<T>::Find(T data)
{
	int begin = 0, end = m_Size - 1;
	while (begin <= end)
	{
		int half = (begin + end) / 2;
		if (data < m_Data[half])
			end = half - 1;
		else if (m_Data[half] < data)
			begin = half + 1;
		else
			return m_Data + half;
	}

	return 0;
}

template <typename T>
T* CSet<T>::At(int i)
{
	return pos >= 0 && pos < m_Size ? m_Data + pos : 0;
}

template <typename T>
void CSet<T>::Clear()
{
	m_Size = 0;
}

template <typename T>
int CSet<T>::Size()
{
	return m_Size;
}

#endif