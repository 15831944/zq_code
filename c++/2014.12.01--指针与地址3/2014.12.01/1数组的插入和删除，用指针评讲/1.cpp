#include<iostream>

void main()
{
	int a[10],b = 5;
	for(int i = 0; i < b; ++i)
	{
		std::cin>>*(a + i);
		//a[i]
		//(a + i)[0]
	}

	while(1)
	{
		system("cls");
		for(int i = 0; i < b; ++i)
		{
			std::cout<<"("<<*(a + i)<<")";
		}
		for(int i = b; i < 10; ++i)
		{
			std::cout<<"( )";
		}
		std::cout<<"\1)����\n2)ɾ��\n3)�˳�\n��ѡ��:";
		int sel;
		std::cin>>sel;
		if(sel == 1)
		{
			if(b == 10)
				std::cout<<"�����������ܲ���";
			else
			{
				int c,d;
				do
				{
					std::cin>>c>>d;
				}while(d < 0 || d > b);
				
				//�����Ҫ�ƶ��Ĵ���
				int m = b - d;
				for(int i = 0; i < m; ++i)
				{//���κ���
					*(a + b - i) = *(a + b - 1 - i);
				}
				*(a + d) = c;//��������
				b++;//���ȼ�1
				std::cout<<"����ɹ�";
			}
			system("pause");
		}
		else if(sel == 2)
		{
			if(b == 0)
				std::cout<<"�����ѿ�";
			else
			{
				int d;
				do
				{
					std::cin>>d;
				}while(d < 0||d >= b);
				//�õ��ƶ�����
				int m = b - d - 1;
				//������λ
				for(int i = 0; i < m; ++i)
					*(a + d + i) = *(a + d + 1 + i);
				b--;//���ȵݼ�
				std::cout<<"ɾ���ɹ�";
			}
			system("pause");
		}
		else if(sel == 3)
			break;
	}
	system("pause");
}