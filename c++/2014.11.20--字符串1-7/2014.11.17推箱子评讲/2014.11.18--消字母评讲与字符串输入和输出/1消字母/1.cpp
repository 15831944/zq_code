#include<iostream>
#include<conio.h>
#include<time.h>

#define _MAP_W 20
#define _MAP_H 10
#define _MAP_S (_MAP_W * _MAP_H)

#define _XY(x,y) (x) + (y) * _MAP_W
#define _XY_X(i) (i) % _MAP_W
#define _XY_Y(i) (i) / _MAP_W

#define _CHAR_MIN 'a'
#define _CHAR_MAX 'c'
#define _CHAR_NONE 0

#define _GAME_INIT 0
#define _GAME_RUN  1

void main()
{
	srand(time(0));
	char map[_MAP_S];
	int x;
	int y;
	int GameState = _GAME_INIT;

	while(1)
	{
		if(_GAME_INIT == GameState)
		{
			for(int i = 0; i < _MAP_S; ++i)
			{
				map[i] = rand()%(_CHAR_MAX - _CHAR_MIN + 1) + _CHAR_MIN;
			}
			x = y = 0;
			GameState = _GAME_RUN;
		}
		else
		{
			system("cls");
			for(int i = 0; i < _MAP_S; ++i)
			{
				if(i == _XY(x,y))
				{
					if(map[i] == _CHAR_NONE)
						std::cout<<"*";
					else
						std::cout<<(char)(map[i] + ('A' - 'a'));
				}
				else
				{
					if(map[i] == _CHAR_NONE)
						std::cout<<" ";
					else
						std::cout<<map[i];
				}
				if(_XY_X(i) == _MAP_W - 1)
					std::cout<<std::endl;
			}

			//
			int input = _getch();

			if((input == 'W' || input == 'w') && y > 0)
				--y;
			if((input == 'S' || input == 's') && y < _MAP_H - 1)
				++y;
			if((input == 'A' || input == 'a') && x > 0)
				--x;
			if((input == 'D' || input == 'd') && x < _MAP_W - 1)
				++x;
			//����ĸ��ѭ���жϹ��̼�����ĸ�Ĺ���
			if(input == ' ' && map[_XY(x,y)] != _CHAR_NONE)
			{
				//�������飬�������鳤��
				int help[_MAP_S];
				int helpLen = 0;
				//����ǰ����λ�÷���������
				help[0] = _XY(x,y);
				helpLen = 1;
				//����һ����������ʼ��ֹ�±�
				int begin = 0,end = 0;
				//4������(��������)��ƫ����
				int xdir[] = {0,0,-1,1};
				int ydir[] = {-1,1,0,0};
				while(1)
				{
					//�õ�û�з�ɢ�ĳ���
					int curlen = helpLen;
					//ѭ����ɢ�µ��±�
					for(int i = begin; i <= end; ++i)
					{
						int cx = _XY_X(help[i]);
						int cy = _XY_Y(help[i]);
						//ѭ���������ҷ���
						for(int j = 0; j < 4;++j)
						{
							//�õ��÷�������λ�õ�����
							int dx = cx + xdir[j];
							int dy = cy + ydir[j];
							//�ж��Ƿ����
							if(dx >= 0 && dx < _MAP_W && dy >= 0 && dy < _MAP_H)
							{
								//�ж��Ƿ�ͳ�ʼλ�õ�ֵ��ͬ
								if(map[_XY(dx,dy)] == map[_XY(x,y)])
								{
									//�ж��Ƿ�������
									bool in = false;
									for(int k = 0; k < helpLen;++k)
									{
										if(help[k] == _XY(dx,dy))
										{
											in = true;
											break;
										}
									}
									if(!in)
										help[helpLen++] = _XY(dx,dy);
								}
							}
						}

					}
					//��ɢ���µ㣬����begin,end
					if(helpLen > curlen)
					{
						begin = curlen;
						end = helpLen - 1;
					}
					else
					{
						break;
					}
				}
				//��ȥ��ĸ
				for(int i = 0; i < helpLen; ++i)
				{
					map[help[i]] = _CHAR_NONE;
				}
				
				bool win = true;
				for(int i = 0; i < _MAP_S; ++i)
				{
					if(map[i]!= _CHAR_NONE)
					{
						win = false;
						break;
					}
				}
				if(win)
				{
					std::cout<<"�س������������˳�:";
					if('\r' == _getch())
					{
						GameState = _GAME_INIT;
					}
					else
						break;
				}
			}
		}
	}
	system("pause");
}

//��صĺ�
//�������
//��ʼ������
//��Ϸѭ��
//{
//���
//����
//�߼�
//}
//��β