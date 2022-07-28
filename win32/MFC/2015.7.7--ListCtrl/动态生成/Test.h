#ifndef _TEST_H_
#define _TEST_H_

class CObject;

//����ʱ���ṹ�壬���е�MFC�඼ͨ����
//���Դ�һ������ṹ�徲̬����
struct _RUNTIME_CLASS
{
	char* name;
	CObject* (* create)();
	_RUNTIME_CLASS* parent_class;
	_RUNTIME_CLASS* next_class;
	static _RUNTIME_CLASS* first_class;

	static CObject* createClass(const char* name);
};

class CObject
{
public:
	virtual ~CObject(){}
	static _RUNTIME_CLASS CObjectRuntimeClass;
	static CObject* createCObject();
	bool IsKindOf(const char*);
};

#define _DECLEAR_CLASS(classname) \
public: \
	static _RUNTIME_CLASS classname##RuntimeClass; \
	static CObject* create##classname##RuntimeClass(); \
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
	_RUNTIME_CLASS classname##::classname##RuntimeClass = {#classname, classname::##create##classname##RuntimeClass, &parentname##::parentname##RuntimeClass, 0}; \
Init classname##Init(&classname##::classname##RuntimeClass); \
CObject* classname::##create##classname##RuntimeClass() \
{ \
	return new classname; \
} \
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

#include <iostream>

class A : public CObject
{
	_DECLEAR_CLASS(A)

//public:
//	static _RUNTIME_CLASS ARuntimeClass;
//	bool IsKindOf(const char*);

public:
	A(){std::cout<<"A����"<<std::endl;}
	~A(){std::cout<<"A����"<<std::endl;}
};

class B : public A
{
	_DECLEAR_CLASS(B)
public:
	B(){std::cout<<"B����"<<std::endl;}
	~B(){std::cout<<"B����"<<std::endl;}
};

class C : public A
{
	_DECLEAR_CLASS(C)
public:
	C(){std::cout<<"C����"<<std::endl;}
	~C(){std::cout<<"C����"<<std::endl;}
};

#endif

//������ǳ��MFC�����
//����ʱ������ʶ�𡢶�̬���ɵȹ����ڸ��߲�ε�
//�����кܶ඼������ֱ��֧�֣�����Java��C#��ObjectiveC