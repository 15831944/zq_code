#include <iostream>
#include <conio.h>

//���̴�С�������غ�
#define _MAP_W_  20
#define _MAP_H_  20
#define _MAP_S_  _MAP_W_ * _MAP_H_ 

//�������±��������ϵ�ĺ�
#define _XY(x,y)   (x) + (y) * _MAP_W_
#define _XY_X(i)   (i) % _MAP_W_
#define _XY_Y(i)   (i) / _MAP_W_

//����Ԫ��
#define _KZ 0
#define _HZ 1
#define _BZ 2

//��Ϸ״̬
#define _GAME_INIT 0
#define _GAME_RUN  1


void main()
{
	//������Ϸ״̬Ϊ��ʼ��
	int GameState = _GAME_INIT;
	//��Ϸ��ص�:���̣���������
	char qp[_MAP_S_];//����
	int x;//���λ��
	int y;
	int qz;//��ǰ������

	while(1)
	{
		if(GameState == _GAME_INIT)
		{
			for(int i = 0; i < _MAP_S_; ++i)
			{
				qp[i] = _KZ;
			}
			x = y = 0;
			qz = _HZ;
			GameState = _GAME_RUN;
		}
		else
		{
			system("cls");
			//���̵Ļ���
			for(int i = 0; i < _MAP_S_;++i)
			{
				if(i == _XY(x,y))
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
					case _KZ:
						{
							int cx = _XY_X(i);
							int cy = _XY_Y(i);
							if(cx == 0&&cy == 0)
							{
								std::cout<<"��";
							}
							else if(cx == 0 && cy == _MAP_H_ - 1)
								std::cout<<"��";
							else if(cx == _MAP_W_ - 1 && cy == 0)
								std::cout<<"��";
							else if(cx == _MAP_W_ - 1 && cy == _MAP_H_ - 1)
								std::cout<<"��";
							else if(cx > 0 && cx < _MAP_W_ - 1 && cy == 0)
								std::cout<<"��";
							else if(cx > 0 && cx < _MAP_W_ - 1 && cy == _MAP_H_ - 1)
								std::cout<<"��";
							else if(cy > 0 && cy < _MAP_H_ - 1 && cx == 0)
								std::cout<<"��";
							else if(cy > 0 && cy < _MAP_H_ - 1 && cx == _MAP_W_ - 1)
								std::cout<<"��";
							else
								std::cout<<"��";


						}
						break;
					case _HZ:std::cout<<"��";break;
					case _BZ:std::cout<<"��";break;
					}
				}
				if(_XY_X(i) == _MAP_W_ - 1)
					std::cout<<std::endl;
			}

			//�����������
			int input = _getch();
			if((input == 'W'|| input == 'w') && y > 0)
				y--;
			if((input == 'S'|| input == 's')&& y < _MAP_H_ - 1)
				y++;
			if((input == 'A'|| input == 'a')&& x > 0)
				x--;
			if((input == 'D'|| input == 'd') && x < _MAP_W_ - 1)
				x++;
			if(input == ' ' && qp[_XY(x,y)] == _KZ)
			{
				qp[_XY(x,y)] = qz;
				char win = _KZ;

				for(int i = 0; i < 5; ++i)
				{
					//����
					//����
					//���ϵ�����
					//���µ�����
					if(x - 4 + i >= 0 && x + i < _MAP_W_ - 1)
					{
						if(qp[_XY((x - 4 + i),y)] == qp[_XY((x - 3 + i),y)]
						&& qp[_XY((x - 3 + i),y)] == qp[_XY((x - 2 + i),y)]
						&& qp[_XY((x - 2 + i),y)] == qp[_XY((x - 1 + i),y)]
						&& qp[_XY((x - 1 + i),y)] == qp[_XY((x + i),y)])
						{
							win = qz;
							break;
						}
					}
					if(y - 4 + i >= 0 && y + i < _MAP_H_ - 1)
					{
						if(qp[_XY(x,(y - 4 + i))] == qp[_XY(x,(y - 3 + i))]
						&& qp[_XY(x,(y - 3 + i))] == qp[_XY(x,(y - 2 + i))]
						&& qp[_XY(x,(y - 2 + i))] == qp[_XY(x,(y - 1 + i))]
						&& qp[_XY(x,(y - 1 + i))] == qp[_XY(x,(y + i))])
						{
							win = qz;
							break;
						}
					}
					if(x - 4 + i >= 0 && x + i < _MAP_W_ - 1
					&& y - 4 + i >= 0 && y + i < _MAP_H_ - 1)
					{
						if(qp[_XY((x - 4 + i),(y - 4 + i))] == qp[_XY((x - 3 + i),(y - 3 + i))]
						&& qp[_XY((x - 2 + i),(y - 2 + i))] == qp[_XY((x - 3 + i),(y - 3 + i))]
						&& qp[_XY((x - 2 + i),(y - 2 + i))] == qp[_XY((x - 1 + i),(y - 1 + i))]
						&& qp[_XY((x - 1 + i),(y - 1 + i))] == qp[_XY((x + i),(y + i))])
						{
							win = qz;
							break;
						}
					}
					if(x - 4 + i >= 0 && x + i < _MAP_W_ - 1
					&& y + 4 - i >= 0 && y - i < _MAP_H_ - 1)
					{
						if(qp[_XY((x - 4 + i),(y + 4 - i))] == qp[_XY((x - 3 + i),(y + 3 - i))]
						&& qp[_XY((x - 2 + i),(y + 2 - i))] == qp[_XY((x - 3 + i),(y + 3 - i))]
						&& qp[_XY((x - 2 + i),(y + 2 - i))] == qp[_XY((x - 1 + i),(y + 1 - i))]
						&& qp[_XY((x - 1 + i),(y + 1 - i))] == qp[_XY((x + i),(y - i))])
						{
							win = qz;
							break;
						}
					}
				}
				if(win != _KZ)
				{
					//char sel;//ѡ�� select
					do
					{
						std::cout<<(win == _HZ ? "��":"��")<<"��ʤ��"<<std::endl;
						std::cout<<"������Ϸ�밴Y���˳���Ϸ�밴N"<<std::endl;
						input = _getch();
					}while(input != 'Y' && input != 'y' && input != 'N' && input != 'n');
					if(input == 'Y'|| input == 'y')
						GameState = _GAME_INIT;
					else
						break;
				}
				qz = (qz == _HZ)?_BZ:_HZ;

			}
		}
	}

	system("pause");
}