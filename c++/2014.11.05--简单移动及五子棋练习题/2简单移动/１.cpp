#include<iostream>
#include<conio.h>

#define _MAP_W 20 //��ͼ��
#define _MAP_H 20 //��ͼ��
#define _MAP_S _MAP_W * _MAP_H //��ͼ�ܴ�С

#define _KD 0//�յ�
#define _HERO 1 //Ӣ��
//#define _ZA 2//�ϰ�

#define _ZX(x,y) ((x) + (y) * _MAP_W) //����ת�±�
#define _XZ_X(i) ((i) % _MAP_W)//�±�ת���� x 
#define _XZ_Y(i) ((i)/_MAP_W) //�±�ת���� y 


void main()
{
	//�����ͼ
	int map[_MAP_S];
	//��ʼ��Ӣ������
	int i_Herox = 1,i_Heroy = 1;

	while(1)
	{
		//��ʼ����ͼ��Ӣ�۵�λ��
		for(int i = 0;i < _MAP_S;++i)
		{
			map[i] = _KD;
		}

		map[_ZX(i_Herox,i_Heroy)] = _HERO;

		system("cls");
		for(int i = 0;i < _MAP_S;++i)
		{
			switch(map[i])
			{
			case _KD:std::cout<<"��";break;
			case _HERO:std::cout<<"��";break;
			}
			if(_XZ_X(i) == _MAP_W - 1)
				std::cout<<std::endl;
		}
		int input = _getch();
		if((input == 'W'||input == 'w') && i_Heroy > 0)
			i_Heroy--;
		if((input == 'S' || input == 's') && i_Heroy < _MAP_H - 1)
			i_Heroy++;
		if((input == 'A'||input == 'a') && i_Herox > 0)
			i_Herox--;
		if((input == 'D' || input == 'd') && i_Herox < _MAP_W - 1)
			i_Herox++;

		if(input == 'Y' || input == 'y')
		{
			std::cout<<"��Ϸ����"<<std::endl;
			break;
		}
	}
	system("pause");
}

//��Ϸд���Ĺ���
//01)������صĺ�
//02)������صı���
//03)��ʼ����ͼ
//04)���Ƶ�ͼ
//05)������Ӧ
//06)�жϣ�����
//07)ʤ���ж�
//08)��Ϸ�Ƿ�������Ƿ����¿�ʼ