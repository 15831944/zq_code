#include<iostream>

//���̿������
//01)��֧��䣺switch-case-break-default,if-else
//02��ѭ����䣺do-while ,while ,for
//03����ת��䣺break,continue,return,goto

void main()
{
	int a;
	std::cin>>a;

	switch(a)
	{
	case 1:
		{
			std::cout<<"1"<<std::endl;
		}
		break;
	case 2:
		{
			std::cout<<"2"<<std::endl;
		}
		break;
	default:
		{
			std::cout<<"����"<<std::endl;
		}
		break;
	}

	//switch �����أ�ѡ��
	//case:���������
	//break:�ƻ�������
	//default��Ĭ�ϡ�ȱʡ

	//switch(A)
	//{
	//case ����1��B;break;
	//case ����2��C;break;
	//case ����3��D;break;
	//case ����4��E;break;
	//defaule:F;break;
	//}
	//G;
	//ִ��A����A�Ľ�����������ÿ��case����ĳ���
	//���ʽ�Ľ�������������ظ���������ͱ�����������
	//���ַ�������������������ж�
	//01����ĳ��case����ĳ������ʽ�Ľ�����
	//��ִ�и�case����д�����е���䣬֮���case��
	//���ڽ�������жϣ�Ҳ����˵���������е�case��䶼
	//������ִ�У�ֱ������break����������switch���飬
	//02�������е�case����ĳ������ʽ�Ľ���������
	// ��default����ִ��default�����еĴ��롣û����
	//ʲô����ִ�С�

	//case��ĳ������ʽ�Ľ�������������������ظ�
	//ÿ��case���������дbreak
	system("pause");
}