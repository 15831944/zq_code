#include<iostream>

void main()
{
	//1)����1
	//int* p = 0;//ָ��������׵�ַ
	//int c = 0;//��¼�����ĸ���

	//while(1)
	//{
	//	for(int i = 0; i < c;++i)
	//		std::cout<<p[i]<<std::endl;
	//	int a;
	//	std::cin>>a;

	//	if(0 == p)//�״�
	//	{
	//		p = (int*)malloc(sizeof(int));
	//		p[0] = a;
	//	}
	//	else
	//	{
	//		//�����µĶ�
	//		int* q = (int*)malloc(sizeof(int) * (c + 1));
	//		//��ԭʼ�����ݴ�ԭ���зŵ��µĶ���
	//		for(int i = 0;i < c;++i)
	//			q[i] = p[i];
	//		//���µ����ݷ��뵽�µĶ���
	//		q[c] = a;
	//		//�ͷ�ԭ���Ķ�
	//		free(p);
	//		//��ԭ����ָ��ָ���µĶ�
	//		p = q;
	//	}
	//	++c;
	//}
	//free(p);
	//����2
	//int s = 8;//��������
	////pָ�������׵�ַ
	//int* p = (int*)malloc(s * sizeof(int));
	////��������
	//int c = 0;

	//while(1)
	//{
	//	int a;
	//	std::cin>>a;

	//	//�����ж�
	//	if(s == c)//˳���
	//	{
	//		s *= 2;
	//		//����ȷ�����µ����������¶�
	//		int* q = (int*)malloc(s * sizeof(int));
	//		//��ԭ���е������ƶ����µĶ���
	//		for(int i = 0; i < c;++i)
	//			q[i] = p[i];
	//		free(p);
	//		p = q;
	//	}
	//	p[c++] = a;
	//}
	//free(p);

	//2)
	int s = 256;//�ڴ�����
	char* p = (char*)malloc(s);
	int a = 0;//�����ַ����Ĵ洢�ռ�
	int c = 0;//�ַ�������

	while(1)
	{
		char* r = p;
		for(int i = 0; i < c;++i)
		{
			std::cout<<r<<std::endl;
			r += strlen(r) + 1;
		}
		char b[256];
		std::cin>>b;

		if(s - a < strlen(b) + 1)
		{
			s+=strlen(b) + 1;
			s *= 2;
			char* q = (char*)malloc(s);
			memcpy(q,p,a);
			free(p);
			p = q;
		}
		strcpy_s(p + a,s - a,b);
		a += strlen(b) + 1;
		c+=1;
	}
	free(p);

	system("pause");
}
//���ڴ�ķ�����ͷ���Ҫ����һ��ʱ��ģ�
//�����������ڴ����γ��ڴ���Ƭ�����ڴ�
//ʹ��Ӧ�������ƴ���