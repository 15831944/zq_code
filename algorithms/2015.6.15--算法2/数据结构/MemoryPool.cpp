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
		//�����������������Ҫ���õ�ǰ�ͷŽڵ��ʹ��Ϊ_NO_USE
		p->use = _NO_USE;

		//����ǰ��ڵ㣬ǰ��ڵ�һ�����е�
		NODE* pre = p->pre;

		//���ǰ��ڵ�û��ʹ�ã���Ҫ����ǰ�ͷŽڵ���ǰ��
		//�ڵ���кϲ�
		if (pre->use == _NO_USE)
		{
			//�п���Ϊ0��Ҳ�п��ܲ�Ϊ0
			pre->next = p->next;
			pre->size += p->size + sizeof(NODE);
			if (pre->next)
				pre->next->pre = pre;
			//����p�ڵ㣬Ŀ����Ϊ����pʼ��ָ��
			//p->next��ǰ��ڵ�
			p = pre;
		}

		//���ۺ���ڵ㣬����ڵ㲻һ�����е�
		NODE* next = p->next;

		//����к���ڵ㣬�Һ���ڵ�û��ʹ�ã���Ҫ����ǰ��
		//�Žڵ������ڵ���кϲ�
		if (next && next->use == _NO_USE)
		{
			//�п���Ϊ0��Ҳ�п��ܲ�Ϊ0
			p->next = next->next;
			p->size += next->size + sizeof(NODE);
			if (p->next)
				p->next->pre = p;
		}
	}
	else
		free(Mem);
}