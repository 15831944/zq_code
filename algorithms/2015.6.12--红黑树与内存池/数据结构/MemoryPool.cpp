#include "MemoryPool.h"
#include <iostream>

#define _NO_USE 0
#define _IN_USE 1

CMemoryPool::CMemoryPool(int Size)
:
m_First((NODE*)malloc(Size))
{
	m_First->pre = 0;
	m_First->next = 0;
	m_First->use = _NO_USE;
	m_First->size = Size - sizeof(NODE);
}

CMemoryPool::~CMemoryPool()
{
	free(m_First);
}

void* CMemoryPool::Allocate(int Size)
{
	NODE* p;
	for (p = m_First; p; p = p->next)
	{
		if (p->use == _NO_USE && p->size >= Size + (int)sizeof(NODE))
			break;
	}

	if (p)
	{
		//�õ�������ڴ��ڵ��ַ
		//NODE* q = (char*)p + sizeof(NODE) + p->size - Size - sizeof(NODE);
		NODE* q = (NODE*)((char*)p + p->size - Size);

		//�����½ڵ�
		q->pre = p;
		q->next = p->next;
		q->use = _IN_USE;
		q->size = Size;

		//�����½ڵ��ǰ��ڵ�
		p->next = q;
		p->size -= sizeof(NODE) + Size;

		//�����½ڵ�ĺ���ڵ�
		if (q->next)
			q->next->pre = q;

		return q + 1;
	}
	else
		return malloc(Size);
}

void CMemoryPool::Free(void* Mem)
{
	NODE* p;
	for (p = m_First; p; p = p->next)
	{
		if (p + 1 == Mem)
			break;
	}

	//���ڴ���еĵ�ַ
	if (p)
	{
		
	}
	else
		free(Mem);
}