#include<iostream>
#include <assert.h>
#include <time.h>
void f()
{
	exit(0);//�˳�����
}


void main()
{
	//f();
	//exit(0);�˳�����
	//ִ��dos����
	system("pause");
	system("cls");
	system("dir");//��ӡĿ¼
	system("md c:\\8��");//�½�Ŀ¼
	system("pause");
	//���()�ı��ʽ�Ľ��Ϊ�٣���ǿ���˳�����(�õ�exit)
	//����������Ĵ���
	//���()�ı��ʽ�Ľ��Ϊ�棬��ʲô�����ᷢ��
	//��Ҫ���ڵ��ԣ�()�п�����������ʽ
	//assert(0);//����


	//01)ȡ�����ǰһ�㶼Ҫ�����������
	//02)rand�ķ���ֵ��Χ��0��32767
	//03)Ҫ����õ�һ����Χ��ֵ����ȡģ
	srand((unsigned int)time(0));

	rand() % 10 + 5;

	system("pause");
}