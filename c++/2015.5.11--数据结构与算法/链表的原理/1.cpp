#include <iostream>

//struct ABC
//{
//	ABC x; //�ṹ���г�Ա�����������Լ�����
//};
//struct DEF
//{
//	DEF* x; //�ṹ���г�Ա�����������Լ����͵�ָ��
//};

struct NODE
{
	int data; //����
	NODE* next; //ָ��
};

struct NODE2
{
	int data; //����
	NODE2* pre; //ǰָ��
	NODE2* next; //��ָ��
};

void main()
{
	NODE n1 = {1};

	//n1.next = &n1;
	//for (NODE* p = &n1; p; p = p->next)
	//	std::cout<<p->data<<std::endl;

	NODE n2 = {2};
	NODE n3 = {3};
	NODE n4 = {4};
	NODE n5 = {5};

	n1.next = &n2;
	n2.next = &n3;
	n3.next = &n4;
	n4.next = &n5;
	n5.next = 0;
	//12345

	//for (NODE* p = &n1; p; p = p->next)
	//	std::cout<<p->data<<std::endl;

	NODE n6 = {6};
	//162345

	//����Ĳ����˳����
	n1.next = &n6;
	n6.next = &n2;

	for (NODE* p = &n1; p; p = p->next)
		std::cout<<p->data<<std::endl;

	//�����ɾ����˳����
	//16345
	n6.next = &n3;
	for (NODE* p = &n1; p; p = p->next)
		std::cout<<p->data<<std::endl;

	system("cls");

	NODE2 nn1 = {1};
	NODE2 nn2 = {2};
	NODE2 nn3 = {3};
	NODE2 nn4 = {4};
	NODE2 nn5 = {5};

	NODE2 head;
	head.next = &nn1;
	head.pre = &nn5;
	nn1.pre = &head; nn1.next = &nn2;
	nn2.pre = &nn1; nn2.next = &nn3;
	nn3.pre = &nn2; nn3.next = &nn4;
	nn4.pre = &nn3; nn4.next = &nn5;
	nn5.pre = &nn4; nn5.next = &head;
	for (NODE2* q = head.next; q != &head; q = q->next)
		std::cout<<q->data<<std::endl;
	for (NODE2* q = head.pre; q != &head; q = q->pre)
		std::cout<<q->data<<std::endl;

	system("pause");
}