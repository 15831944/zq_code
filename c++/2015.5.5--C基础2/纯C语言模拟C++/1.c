#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct _STUDENT
{
	int _id;
	char _name[32];
	int _age;

	//��C�����в����г�Ա����
	void (*Init)(struct _STUDENT*, int, const char*, int);
};

void Init_Student(struct _STUDENT* this, int id, const char* name, int age)
{
	//�˴�thisֻ��һ����ͨ��ʶ�������ǹؼ���
	this->_id = id;
	strcpy_s(this->_name, 32, name);
	this->_age = age;
}

void main()
{
	struct _STUDENT s;

	//��������ֵ����Ա����������ָ�룩��
	s.Init = Init_Student;

	//�൱�ڳ�Ա�����ĵ���
	(s.Init)(&s, 1, "abc", 2); //�е���s.Init(1, "abc", 2);

	system("pause");
}

//class Student
//{
//	int _id;
//	char _name[32];
//	int _age;
//
//	void Init(int id, const char* name, int age)
//	{
//		_id = id;
//		strcpy_s(_name, 32, name);
//		_age = age;
//	}
//};
//C++��������ѳ�Ա�������´���Ϊ������������
//void Init(Student* this, int id, const char* name, int age)
//{
//	this->_id = id;
//	strcpy_s(this->_name, 32, name);
//	this->_age = age;
//}
//Student s;
//s.Init(1, "abc", 2); //���ĵ������ᱻ�������޸�ΪInit(&s, 1, "abc", 2);