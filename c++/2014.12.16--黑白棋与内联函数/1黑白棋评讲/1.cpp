#include<iostream>
#include <conio.h>
#include "HBQ.h"

void main()
{
	int x = 0,y = 0;
	HBQ_Init();
	while(1)
	{
		system("cls");
		for(int i = 0; i < _QP_S;++i)
		{
			if(x + y * _QP_W == i)
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
			if(i % _QP_W == _QP_W - 1)
				std::cout<<std::endl;
		}
		std::cout<<"��ǰΪ["<<(c == _HZ ? "��" : "��")<<"]";
		int input = _getch();
		if((input == 'w' || input == 'W')&& y > 0)
			y--;
		if((input == 's' || input == 'S')&& y < _QP_H - 1)
			y++;
		if((input == 'A' || input == 'a')&& x > 0)
			x--;
		if((input == 'D' || input == 'd')&& x < _QP_W - 1)
			x++;

		if(input == ' ')
		{
			int r = HBQ_Play(x,y);
			if(r == 1)
			{
				std::cout<<(c == _HZ?"��":"��")<<"��ʤ��";
				break;
			}
			else if(r == -1)
			{
				std::cout<<"�˴���������,";
				system("pause");
			}
		}
	}
	system("pause");
}