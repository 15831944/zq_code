#ifndef _HASH_H_
#define _HASH_H_

template <typename KEY, typename DATA>
class CHash //KEY������<�������KEY��Ψһ��
{
public:
	struct PAIR //��ֵ�Խṹ��
	{
		KEY key;
		DATA data;
	};

private:
	struct MAP //ӳ��
	{
		int capacity;
		int size;
		PAIR* pair;
	};
	int (* m_HashFunc)(KEY); //��ϣ����ָ��
	int m_Capacity; //��ϣ������
	int m_Size; //��ֵ�Ը���
	MAP* m_Hash; //��ϣ��

public:

	CHash(int (* HashFunc)(KEY), int Capacity = 256);
	CHash(const CHash& that);
	CHash& operator = (const CHash& that);
	~CHash();

	bool Insert(KEY key, DATA data); //����
	bool Erase(KEY key); //ɾ��
	PAIR* Find(KEY key); //ͨ���������õ����ݵ�ַ
	void Clear(); //���
	int Size(); //����

	//����д������������Hash��ı���
};

template <typename KEY, typename DATA>
CHash<KEY,DATA>::CHash(int (* HashFunc)(KEY), int Capacity)
:
m_HashFunc(HashFunc),
m_Capacity(Capacity),
m_Size(0),
m_Hash(new MAP[m_Capacity])
{
	//�����е�ӳ�����������Ϊ0��ʾΪ��ӳ��
	for (int i = 0; i < m_Capacity; ++i)
		m_Hash[i].capacity = 0;
}

template <typename KEY, typename DATA>
CHash<KEY,DATA>::CHash(const CHash& that)
:
m_HashFunc(that.m_HashFunc),
m_Capacity(that.m_Capacity),
m_Size(that.m_Size),
m_Hash(new MAP[m_Capacity])
{
	for (int i = 0; i < m_Capacity; ++i)
	{
		if (0 == that.m_Hash[i].capacity)
			m_Hash[i].capacity = 0;
		else
		{
			m_Hash[i].capacity = that.m_Hash[i].capacity;
			m_Hash[i].size = that.m_Hash[i].size;
			m_Hash[i].pair = new PAIR[m_Hash[i].capacity];
			for (int j = 0; j < m_Hash[i].size; ++j)
				m_Hash[i].pair[j] = that.m_Hash[i].pair[j];
		}
	}
}

template <typename KEY, typename DATA>
CHash<KEY,DATA>& CHash<KEY,DATA>::operator = (const CHash& that)
{
	if (this != &that)
	{
		//�ͷ�
		for (int i = 0; i < m_Capacity; ++i)
		{
			if (m_Hash[i].capacity > 0)
				delete [] m_Hash[i].pair;
		}
		delete [] m_Hash;

		//����
		m_HashFunc = that.m_HashFunc;
		m_Capacity = that.m_Capacity;
		m_Size = that.m_Size;
		m_Hash = new MAP[m_Capacity];
		for (int i = 0; i < m_Capacity; ++i)
		{
			if (0 == that.m_Hash[i].capacity)
				m_Hash[i].capacity = 0;
			else
			{
				m_Hash[i].capacity = that.m_Hash[i].capacity;
				m_Hash[i].size = that.m_Hash[i].size;
				m_Hash[i].pair = new PAIR[m_Hash[i].capacity];
				for (int j = 0; j < m_Hash[i].size; ++j)
					m_Hash[i].pair[j] = that.m_Hash[i].pair[j];
			}
		}
	}

	return true;
}

template <typename KEY, typename DATA>
CHash<KEY,DATA>::~CHash()
{
	for (int i = 0; i < m_Capacity; ++i)
	{
		if (m_Hash[i].capacity > 0)
			delete [] m_Hash[i].pair;
	}
	delete [] m_Hash;
}

template <typename KEY, typename DATA>
bool CHash<KEY,DATA>::Insert(KEY key, DATA data)
{
	//��ϣ����
	int index = (*m_HashFunc)(key) % m_Capacity;

	//��ǰ�±��ϵ�ӳ�仹û������
	if (0 == m_Hash[index].capacity)
	{
		m_Hash[index].capacity = 4;
		m_Hash[index].size = 1;
		m_Hash[index].pair = new PAIR[m_Hash[index].capacity];
		m_Hash[index].pair[0].key = key;
		m_Hash[index].pair[0].data = data;
	}
	//��ǰ�±��ϵ�ӳ���Ѿ���������
	else
	{
		//�۰����
		int begin = 0, end = m_Hash[index].size - 1;
		while (begin <= end)
		{
			int half = (begin + end) / 2;
			if (key < m_Hash[index].pair[half].key)
				end = half - 1;
			else if (m_Hash[index].pair[half].key < key)
				begin = half + 1;
			else
				return false;
		}

		//����
		if (m_Hash[index].size == m_Hash[index].capacity)
		{
			PAIR* p = new PAIR[m_Hash[index].capacity *= 2];
			for (int i = 0; i < m_Hash[index].size; ++i)
				p[i] = m_Hash[index].pair[i];
			delete [] m_Hash[index].pair;
			m_Hash[index].pair = p;
		}

		//����
		int m = m_Hash[index].size - begin;
		for (int i = 0; i < m; ++i)
			m_Hash[index].pair[m_Hash[index].size - i] = m_Hash[index].pair[m_Hash[index].size - 1 - i];
		m_Hash[index].pair[begin].key = key;
		m_Hash[index].pair[begin].data = data;
		m_Hash[index].size += 1;
	}

	m_Size += 1;

	return true;
}

template <typename KEY, typename DATA>
bool CHash<KEY,DATA>::Erase(KEY key)
{
	//��ϣ����
	int index = (*m_HashFunc)(key) % m_Capacity;

	//��ǰλ��û������
	if (m_Hash[index].capacity == 0)
		return false;

	//�۰����
	int begin = 0, end = m_Hash[index].size - 1;
	while (begin <= end)
	{
		int half = (begin + end) / 2;
		if (key < m_Hash[index].pair[half].key)
			end = half - 1;
		else if (m_Hash[index].pair[half].key < key)
			begin = half + 1;
		else
		{
			int m = m_Hash[index].size - half - 1;
			for (int i = 0; i < m; ++i)
				m_Hash[index].pair[half + i] = m_Hash[index].pair[half + 1 + i];
			m_Hash[index].size -= 1;
			m_Size -= 1;
			return true;
		}
	}

	return false;
}

template <typename KEY, typename DATA>
typename CHash<KEY,DATA>::PAIR* CHash<KEY,DATA>::Find(KEY key)
{
	//��ϣ����
	int index = (*m_HashFunc)(key) % m_Capacity;

	//��ǰλ��û������
	if (m_Hash[index].capacity == 0)
		return 0;

	//�۰����
	int begin = 0, end = m_Hash[index].size - 1;
	while (begin <= end)
	{
		int half = (begin + end) / 2;
		if (key < m_Hash[index].pair[half].key)
			end = half - 1;
		else if (m_Hash[index].pair[half].key < key)
			begin = half + 1;
		else
			return &m_Hash[index].pair[half];
	}

	return 0;
}

template <typename KEY, typename DATA>
void CHash<KEY,DATA>::Clear()
{
	for (int i = 0; i < m_Capacity; ++i)
	{
		if (m_Hash[i].capacity > 0)
		{
			delete [] m_Hash[i].pair;
			m_Hash[i].capacity = 0;
		}
	}
	m_Size = 0;
}

template <typename KEY, typename DATA>
int CHash<KEY,DATA>::Size()
{
	return m_Size;
}

#endif