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
	void Create(int size = 8)
	{
		m_Size = size;
		m_Length = 0;
		m_Data = (CSLDATA*)malloc(sizeof(CSLDATA) * m_Size);
	}
	void Destroy()
	{}

};







#endif