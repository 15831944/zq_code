#include<iostream>

//vs2005��ȫ�ֱ���������û���ڴ�����
//int a[1024 * 1024];

void main()
{
	//vs2005��ջ�ڴ��������1M
	//char a[1024 * 1000];
	
	//vs2005�ж��ڴ�������û������
	void* p = malloc(1024 * 1024 * 1024);

	free(p);
	
	system("pause");
}