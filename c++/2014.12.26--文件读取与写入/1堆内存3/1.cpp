#include<iostream>


//void* malloc(size_t size)
//void free(void* memblock)

//�ڶ��ڴ��з���num * size���ֽڵ��������ڴ��
//�������׵�ַ
//void* calloc(size_t num,size_t size);

//void* f1(size_t num,size_t size)
//{
//	return malloc(num * size);
//}
//���ͷ�memblock��ָ��Ķ��ڴ�飬Ȼ�����ڶ��ڴ��
//�п���size���ֽڵ������ڴ�鲢�����׵�ַ���·���
//���ڴ���֮ǰ�ͷŵ��ڴ��û���κι�ϵ
//void* realloc(void* memblock,size_t size);
//void* f2(void* memblock,size_t size)
//{
//	free(memblock);
//	return malloc(size);
//}

int* a;
int d;

void main()
{
	int b;
	a = &b;//�þ�̬�ڴ����е�ָ��ָ��mainջ
	int* c = &d;//mainջ��ָ��ָ��̬�ڴ�
	int* e = (int*)malloc(4);//mainջ�е�ָ��ָ���
	free(e);
	//e = (int*)calloc(sizeof(int),4);
	//free(e);
	//e = (int*)realloc(e,sizeof(int) * 4);
	//free(e);
	int** f = (int**)malloc(4);
	*f = &b;//���е�ָ��ָ��mainջ
	free(f);

	system("pause");
}