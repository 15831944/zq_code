#include<iostream>


void main()
{
	//ָ���Ǵ洢��ַ�ı���
	//32λ����ϵͳ��32��������λ(4���ֽ�)����
	//�ڴ��е�ÿ���ֽڽ��б��,Ҳ����˵ֻҪ��
	//��ַ�Ϳ�����4���ֽڴ洢������32λ����ϵ
	//ͳ�µ�ָ������ʲô���Ͷ���4���ֽ�
	char* a;//charָ��
	short* b;//shortָ��
	int* c;//intָ��
	double* d;//doubleָ��
	
	std::cout<<sizeof(a)<<std::endl;
	std::cout<<sizeof(b)<<std::endl;
	std::cout<<sizeof(c)<<std::endl;
	std::cout<<sizeof(d)<<std::endl;
	std::cout<<sizeof(double*)<<std::endl;
	std::cout<<sizeof(double************)<<std::endl;

	system("pause");
}