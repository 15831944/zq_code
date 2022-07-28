#include "MemoryPool.h"
#include <iostream>

#define _NO_HEAD 0 //��ͷ�ڵ�
#define _IS_HEAD 1 //ͷ�ڵ�
#define _NO_USE 0 //δʹ��
#define _IN_USE 1 //ʹ��

CMemoryPool::CMemoryPool(const CMemoryPool& that)
{}
CMemoryPool& CMemoryPool::operator = (const CMemoryPool& that)
{return *this;}

CMemoryPool::CMemoryPool(int Size)
:
m_CurSize(Size),
m_First((NODE*)malloc(m_CurSize))
{
	m_First->pre = 0;
	m_First->next = 0;
	m_First->head = _IS_HEAD;
	m_First->use = _NO_USE;
	m_First->size = m_CurSize - sizeof(NODE);
}

CMemoryPool::~CMemoryPool()
{
	NODE* p = m_First;
	while (p)
	{
		NODE* q = p->next;
		while (q && q->head == _NO_HEAD)
			q = q->next;

		free(p);

		p = q;
	}
}

void* CMemoryPool::Allocate(int Size)
{
	NODE* p, * last;
	for (p = m_First; p; p = p->next)
	{
		last = p;
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
		q->head = _NO_HEAD;
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
	{
		//�������ڴ��
		m_CurSize = m_CurSize * 2 + Size;
		NODE* r = (NODE*)malloc(m_CurSize);

		//�������ڴ��
		r->pre = last;
		r->next = 0;
		r->head = _IS_HEAD;
		r->use = _NO_USE;
		r->size = m_CurSize - sizeof(NODE);

		//�������ڴ���ǰ��ڵ�
		last->next = r;

		//�����ⲿ��Ҫ���ڴ�
		NODE* q = (NODE*)((char*)r + r->size - Size);

		//�����½ڵ�
		q->pre = r;
		q->next = r->next;
		q->head = _NO_HEAD;
		q->use = _IN_USE;
		q->size = Size;

		//�����½ڵ��ǰ��ڵ�
		r->next = q;
		r->size -= sizeof(NODE) + Size;

		return q + 1;
	}
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

		//����ǰ��ڵ㣬ǰ��ڵ�һ�����е���һ�����ͷŽڵ�������һ���
		NODE* pre = p->pre;

		//���ǰ��ڵ�û��ʹ�ã���Ҫ����ǰ�ͷŽڵ���ǰ��ڵ���кϲ�
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

		//���ۺ���ڵ㣬����ڵ㲻һ�����еģ�������
		//Ҳ�п������ڴ���ͷ���ڵ�
		NODE* next = p->next;

		//����к���ڵ㣬�Һ���ڵ�û��ʹ�ã���Ҫ����ǰ��
		//�Žڵ������ڵ���кϲ�
		if (next && next->use == _NO_USE && next->head == _NO_HEAD)
		{
			//�п���Ϊ0��Ҳ�п��ܲ�Ϊ0
			p->next = next->next;
			p->size += next->size + sizeof(NODE);
			if (p->next)
				p->next->pre = p;
		}
	}
}