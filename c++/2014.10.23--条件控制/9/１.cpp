#include<iostream>

//break continue return goto

void main()
{
	for(int i = 0; i < 10 ; ++i)
	{
		if(i == 4)
			continue;
		//һ�����е�continue���򱾴�ѭ������,
		//����Ĵ�ӡ������ִ�У�Ȼ��ִ��
		//++i,Ȼ������´�ѭ��
		//ֻ�����ֱ�Ӱ�������ѭ��
		for(int j = 0; j < 10; ++j)
		{
			if(j == 5)
				break;
			//һ�����е�break������ѭ���������ѭ��������ִ��
			//ֻ���ֱ�Ӱ�������ѭ��
			if(j == 3)
				return;
			//һ�����е�return����ú����������еĶ�����ִ�У�
			//ֱ���˳�������
			//��Ե���ֱ�Ӱ������ĺ���
			std::cout<<j;
		}
		std::cout<<std::endl;
		//std::cout<<i<<std::endl;
	}
	system("pause");
}