#include <iostream>

//���������ܱ��ı����
//���泣��
//���ų���


void main()
{
	false;
	true;//���������泣��
	'a';//��''�����һ�����ֽ��ַ������泣��
	'1';
	//û��unsinged char�����泣��д��
	L'3';//wchar_t�����泣��

	"asdfdf";//char* �ַ������泣��
	//��""�����һ�����߶�����ֽ��ַ���
	"a";
	L"a";//wchar_t* ���ֽ�(˫�ֽ�)�ַ������泣��

	//short unsigned short û�����泣����д��
	123;//int���泣��
	-123;//int���泣��
	0;//int���泣��

	123U;//�޷����������泣��unsinged int
	123u;//unsinged int
	15L;//long���������泣��
	52l;//long���������泣��

	56UL;//unsinged long �޷��ų��������泣��
	65ul;//unsinged long �޷��ų��������泣��
	55Ul;//unsinged long �޷��ų��������泣��
	65uL;//unsinged long �޷��ų��������泣��
	65LU;//unsinged long �޷��ų��������泣��
	95lu;//unsinged long �޷��ų��������泣��
	99Lu;//unsinged long �޷��ų��������泣��
	99lU;//unsinged long �޷��ų��������泣��

	35.6f;//float �����ȸ��������泣��
	66.5F;//float �����ȸ��������泣��

	65.00;//double ˫���ȸ��������泣��

	1.2L;//long double ��˫���ȸ��������泣��
	1.3l;//long double ��˫���ȸ��������泣��


	//long al = 41L;

	//sizeof()�õ������ڵ����泣���������������͵��ֽ�
	std::cout<<sizeof(false)<<std::endl;
	std::cout<<sizeof('a')<<std::endl;
	std::cout<<sizeof(L'a')<<std::endl;
	std::cout<<sizeof("a")<<std::endl;
	std::cout<<sizeof(L"assd")<<std::endl;
	std::cout<<sizeof(1)<<std::endl;
	std::cout<<sizeof(6L)<<std::endl;
	std::cout<<sizeof(8UL)<<std::endl;
	std::cout<<sizeof(3.12f)<<std::endl;
	std::cout<<sizeof(3.00)<<std::endl;
	std::cout<<sizeof(3.1L)<<std::endl;
	
	system("pause");
}