#include <iostream>

//�˴ζ�����һ�����������ͣ����Ϳ���
//�������������������������
union _ABC
{
	char a;
	short b;
	int c;
};

union _IP_ADDRESS
{
	unsigned int ip1;
	unsigned short ip2[2];
	unsigned char ip3[4];
};

void main()
{
	//�����������г�Ա����������һ���ڴ棬����ڴ�
	//�Ĵ�С�������ĳ�Ա�����Ĵ�С,���������_ABC
	//�Ĵ�С����sizeof(int)
	_ABC x;
	x.a = 1;// 01 ?? ?? ??
	x.b = 2;// 02 00 ?? ??
	x.c = 3;// 03 00 00 00 
	x.b = 2;// 02 00 00 00
	//std::cout<<sizeof(x)<<std::endl;
	std::cout<<(int)x.a<<std::endl;
	std::cout<<x.b<<std::endl;
	std::cout<<x.c<<std::endl;
	_ABC* y = &x;
	y->c = 4;// 04 00 00 00
	y->b = 5;// 05 00 00 00
	y->a = 6;// 06 00 00 00
	//�����������д�ĳ�Ա���������ܹ�����ȷ
	//��ȡ�ĳ�Ա�������������ݺͽṹ����ȫһ��
	//ע�⣬�����ip��ַ����������ж��ֱ�ʾ��ʽ
	//������4��unsigned char�����б�ʾ�Ļ����Է���
	//�û���д��ȡip��ַ
	_IP_ADDRESS ipA,ipB;
	ipA.ip3[0] = 192;
	ipA.ip3[1] = 168;
	ipA.ip3[2] = 1;
	ipA.ip3[3] = 100;//192 168 1 100

	ipB.ip3[0] = 192;
	ipB.ip3[1] = 168;
	ipB.ip3[2] = 1;
	ipB.ip3[3] = 101;// 192 168 1 101
	//������ı�ʾ��ʽ�Ͳ�̫�ʺϱȽ�IP֮��Ĳ���
	//�����ֲ��������ip1�����������Լʱ���

	//if(ipA.ip3[0] == ipB.ip3[0]
	//&&ipA.ip3[1] == ipB.ip3[1]
	//&&ipA.ip3[2] == ipB.ip3[2]
	//&&ipA.ip3[3] == ipB.ip3[3])

	//if(ipA.ip1 == ipB.ip1)��Ч�ʱ�����Ҫ��

	std::cout<<sizeof(_IP_ADDRESS)<<std::endl;

	system("pause");
}