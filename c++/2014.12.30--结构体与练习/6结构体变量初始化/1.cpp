#include<iostream>

struct _ABC
{
	char a;
	short b;
	int c;
};

void main()
{
	//�ṹ������ĳ�ʼ��
	//����Ĵ������γ�ʼ����
	//x.aΪ1��x.bΪ2��x.cΪ3
	_ABC x = {1,2,3};

	//����Ĵ������γ�ʼ����
	//y.aΪ1��y.bΪ2��y.c
	//û�ж�Ӧ��ʼ������
	//��ʼ��Ϊ0
	_ABC y = {1,2};

	_ABC z[3] = {{1,2,3},{4,5,6}};
	
	//t�е�3����Ա������Ϊ0
	_ABC t = {};
	system("pause");
}
