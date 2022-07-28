#ifndef _TEST_H_
#define _TEST_H_

//����ʱ���ṹ�壬���е�MFC�඼ͨ����
//���Դ�һ������ṹ�徲̬����
struct _RUNTIME_CLASS
{
	char* name;
	_RUNTIME_CLASS* parent_class;
	_RUNTIME_CLASS* next_class;
	static _RUNTIME_CLASS* first_class;
};

class CObject
{
public:
	static _RUNTIME_CLASS CObjectRuntimeClass;
	bool IsKindOf(const char*);
};

#define _DECLEAR_CLASS(classname) \
public: \
	static _RUNTIME_CLASS classname##RuntimeClass; \
	bool IsKindOf(const char*);

//��������������_RUNTIME_CLASS������ṹ��
class Init
{
public:
	Init(_RUNTIME_CLASS* rc)
	{
		_RUNTIME_CLASS* p = _RUNTIME_CLASS::first_class;
		while (p->next_class)
			p = p->next_class;
		p->next_class = rc;
	}
};

#define _DEFINE_CLASS(classname, parentname) \
_RUNTIME_CLASS classname##::classname##RuntimeClass = {#classname, &parentname##::parentname##RuntimeClass, 0}; \
Init classname##Init(&classname##::classname##RuntimeClass); \
bool classname##::IsKindOf(const char* name) \
{ \
	_RUNTIME_CLASS* p = &classname##RuntimeClass; \
	while (p) \
	{ \
		if (strcmp(p->name, name) == 0) \
			return true; \
		else \
			p = p->parent_class; \
	} \
	return false; \
}

class A : public CObject
{
	_DECLEAR_CLASS(A)

//public:
//	static _RUNTIME_CLASS ARuntimeClass;
//	bool IsKindOf(const char*);
};

class B : public A
{
	_DECLEAR_CLASS(B)
};

class C : public A
{
	_DECLEAR_CLASS(C)
};

#endif