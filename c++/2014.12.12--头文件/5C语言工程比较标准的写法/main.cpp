#include <iostream>
#include <conio.h>
#include "HBQ.h"


//C���Թ��̱Ƚϱ�׼��д��
//C����ģ��
//���ǰ�һ�鹦�������������صĺ�����
//ȫ�ֱ���������һ��ģ�飬����������
//�ķ�����д���ģ��
//01)һ��CPP�ļ�д��Щģ��Ķ���
//02)һ��h�ļ�д��Щģ�������
//03)һ����˵���������ļ�������ͬ��
//��cpp�ļ�����һ�����h�ļ�
//����ʹ����Щģ��ֻ��Ҫ��������
//01)�κ��õ����ģ��֮ǰ����ģ���h�ļ�
//02)��ģ���cpp�ļ����빤�̲������

void main()
{
	Init();
	int x = 0,y = 0;
	while(1)
	{
		system("cls");
		for(int i = 0; i < _QP_S;++i)
		{
			if(_XY(x,y) == i)
			{
				switch(qp[i])
				{
				case _KZ:std::cout<<"��";break;
				case _HZ:std::cout<<"��";break;
				case _BZ:std::cout<<"��";break;
				}
			}
			else
			{
				switch(qp[i])
				{
				case _KZ:std::cout<<"��";break;
				case _HZ:std::cout<<"��";break;
				case _BZ:std::cout<<"��";break;
				}
			}
			if(_XY_X(i)== _QP_W - 1)
				std::cout<<std::endl;
		}
		int input = _getch();
		if((input == 'W'|| input == 'w')&& y > 0)
			--y;
		if((input == 'S'|| input == 's')&& y < _QP_H - 1)
			++y;
		if((input == 'A'|| input == 'a')&& x > 0)
			--x;
		if((input == 'D'|| input == 'd')&& x < _QP_W - 1)
			++x;

		if(input == 'U'||input == 'u')
			Play(x,y);
	}
	system("pause");
}
