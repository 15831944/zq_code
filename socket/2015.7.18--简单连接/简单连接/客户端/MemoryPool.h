#ifndef _MEMORY_POOL_H_
#define _MEMORY_POOL_H_

class CMemoryPool
{
	struct NODE
	{
		NODE* pre; //ǰ��ָ��
		NODE* next; //����ָ��
		short head; //ͷ����־
		short use; //ʹ�ñ�־
		int size; //�ڴ���С
	};
	int m_CurSize; //����ڴ���С
	NODE* m_First; //�׽ڵ�

	//���������ͬ�ำֵ����Ϊ˽��
	CMemoryPool(const CMemoryPool& that);
	CMemoryPool& operator = (const CMemoryPool& that);

public:

	CMemoryPool(int Size = 1024 * 1024 * 4);
	~CMemoryPool();

	void* Allocate(int Size);
	void Free(void* Mem);
};

#endif