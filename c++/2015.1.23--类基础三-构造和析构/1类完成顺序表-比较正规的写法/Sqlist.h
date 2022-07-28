#ifndef _C_SQ_LIST_H_
#define _C_SQ_LIST_H_

#define CSLDATA int

//һ����˵�ڳ�Ա����ǰ����m_��ʾ��member����˼
class CSqList
{
	int m_Size;//����
	int m_Length;//����
	CSLDATA* m_Data;//����
public:
	void Create(int size = 8);
	void Destroy();
	bool Insert(CSLDATA data , int pos);
	void Push(CSLDATA data);
	bool Erase(int pos);
	void Clear();
	CSLDATA* Get(int pos);
	int GetLength();
};

#endif