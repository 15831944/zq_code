#ifndef _MAX_HEAP_H_
#define _MAX_HEAP_H_

template <typename T>
class CMaxHeap //Ҳ�����ȶ���
{
	int m_Capacity;
	int m_Size;
	T* m_Data;

public:

	CMaxHeap(int Capacity = 8);
	CMaxHeap(const CMaxHeap& that);
	CMaxHeap& operator = (const CMaxHeap& that);
	~CMaxHeap();

	void Push(T data); //������
	bool Pop(); //������
	bool Front(T* data); //�õ����ڵ�����
	void Clear(); //���
	int Size(); //��С
};

template <typename T>
CMaxHeap<T>::CMaxHeap(int Capacity)
:
m_Capacity(Capacity),
m_Size(0),
m_Data(new T[m_Capacity])
{}

template <typename T>
CMaxHeap<T>::CMaxHeap(const CMaxHeap& that)
:
m_Capacity(that.m_Capacity),
m_Size(that.m_Size),
m_Data(new T[m_Capacity])
{
	for (int i = 1; i <= m_Size; ++i)
		m_Data[i] = that.m_Data[i];
}

template <typename T>
CMaxHeap<T>& CMaxHeap<T>::operator = (const CMaxHeap& that)
{
	if (this !=  &that)
	{
		delete [] m_Data;

		m_Capacity = that.m_Capacity;
		m_Size = that.m_Size;
		m_Data = new T[m_Capacity];
		for (int i = 1; i <= m_Size; ++i)
			m_Data[i] = that.m_Data[i];
	}

	return *this;
}

template <typename T>
CMaxHeap<T>::~CMaxHeap()
{
	delete [] m_Data;
}

template <typename T>
void CMaxHeap<T>::Push(T data)
{
	if (m_Size + 1 == m_Capacity)
	{
		T* p = new T[m_Capacity *= 2];
		for (int i = 1; i <= m_Size; ++i)
			p[i] = m_Data[i];
		delete [] m_Data;
		m_Data = p;
	}

	//������ȫ���������з��룬���ŵ����
	m_Data[++m_Size] = data;

	//���ո��ڵ����ȼ������ӽڵ����ȼ����е���
	int index0 = m_Size; //��ǰ����Ľڵ��±�
	int index1 = index0 / 2; //��ǰ����Ľڵ�ĸ��ڵ��±�

	//ѭ������
	while (index0 > 1 && m_Data[index1] < m_Data[index0])
	{
		T t = m_Data[index1];
		m_Data[index1] = m_Data[index0];
		m_Data[index0] = t;

		//���µ�ǰ�ڵ��±���丸�ڵ��±�
		index0 = index1;
		index1 = index0 / 2;
	}
}

template <typename T>
bool CMaxHeap<T>::Pop()
{
	//��ǰû�����ݻ�ֻ
	//��һ�����ݵ����
	if (m_Size == 0)
		return false;
	else if (m_Size == 1)
	{
		m_Size -= 1;
		return true;
	}

	//����2������

	//�õ���ǰ�����ߵ�����λ��
	int index0 = 1;

	//ѭ������
	while (1)
	{
		int left_index = index0 * 2;
		int right_index = left_index + 1;

		//�����ӽڵ㶼��
		if (right_index <= m_Size)
		{
			//����ұ��ӽڵ���������ȼ���������ӽڵ�
			//���������ȼ��Ļ�����ô���Ҳ���ӽڵ�����
			//��ֵ�����ڵ�����
			if (m_Data[left_index] < m_Data[right_index])
			{
				m_Data[index0] = m_Data[right_index];
				index0 = right_index;
			}
			else
			{
				m_Data[index0] = m_Data[left_index];
				index0 = left_index;
			}
		}
		//�����ӽڵ������ӽڵ�
		else if (left_index <= m_Size)
		{
			//����������������ӽڵ�һ���ǵ�ǰ������
			//�����һ���ڵ㣬��ʱֻ��Ҫ�����ӽڵ㲹��
			//����
			m_Data[index0] = m_Data[left_index];
			m_Size -= 1;
			return true;
		}
		//���Ҷ��ޣ�������ѭ��
		else
			break;
	}

	//Ctrl + ]���������ƥ��Ĵ�����֮����ת
	//Ctrl + K + F��һ����Ҫ��ѡ��Ҫ�������
	//���������Զ��������Ƕ����ı�

	//�����λ�õ����ݷ��뵽index0λ��

	//��index0�������λ�õ�ʱ��
	if (index0 == m_Size)
	{
		m_Size -= 1;
		return true;
	}

	//��index0�������λ�õ�ʱ�򣬽�
	//���λ�õ����ݲ����index0����
	//���õ�index0�ĸ��ڵ��±�
	m_Data[index0] = m_Data[m_Size];
	int index1 = index0 / 2;

	//ѭ������
	while (index0 > 1 && m_Data[index1] < m_Data[index0])
	{
		T t = m_Data[index1];
		m_Data[index1] = m_Data[index0];
		m_Data[index0] = t;

		//���µ�ǰ�ڵ��±���丸�ڵ��±�
		index0 = index1;
		index1 = index0 / 2;
	}

	m_Size -= 1;

	return true;
}

template <typename T>
bool CMaxHeap<T>::Front(T* data)
{
	if (m_Size > 0)
	{
		*data = m_Data[1];
		return true;
	}
	else
		return false;
}

template <typename T>
void CMaxHeap<T>::Clear()
{
	m_Size = 0;
}

template <typename T>
int CMaxHeap<T>::Size()
{
	return m_Size;
}

#endif