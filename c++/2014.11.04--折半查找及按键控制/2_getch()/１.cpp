#include<iostream>
#include<conio.h>

void main()
{
	//����س�������,��ȡ�û�����ļ�ֵ(���µļ���ֵ)
	//int input = _getch();
	//���ص���һ������ֵ
	int input;
	while(1)
	{
		input = _getch();
		if(input == 'W'||input == 'w')
			std::cout<<"������W��"<<std::endl;
		if(input == 'A'||input == 'a')
			std::cout<<"������A��"<<std::endl;
		if(input == 'S'||input == 's')
			std::cout<<"������S��"<<std::endl;
		if(input == 'D'||input == 'd')
			std::cout<<"������D��"<<std::endl;

		if(input == ' ')
		{
			std::cout<<"�����˿ո��"<<std::endl;
			break;
		}
	}
	//01)������¹��ܼ����ȷ���0x00���ٴε��òŷ��������ļ�ֵ
	//02)������·�������ȷ���0xe0���ٴε��òŷ��������ļ�ֵ
	//03)����������˫�ֽ��ַ��򷵻�2��
	//
	//

	system("pause");
}