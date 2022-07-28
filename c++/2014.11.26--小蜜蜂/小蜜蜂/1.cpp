#include <iostream>
#include <time.h>
#include <windows.h>

#define _MAP_W 15
#define _MAP_H 10
#define _MAP_S (_MAP_W * _MAP_H)

#define _KD 0
#define _YX 1
#define _ZD 2
#define _MF 3

#define _XY(x,y) (x)+(y)*_MAP_W
#define _XY_X(i) (i) % _MAP_W
#define _XY_Y(i) (i) / _MAP_W

#define _GAME_CHOOSE -1
#define _GAME_INIT 0
#define _GAME_RUN  1
#define _GAME_HELP 2

void main()
{
	srand((unsigned int)time(0));
	char map[_MAP_S] = {};
	int x = _MAP_W / 2;
	int y = _MAP_H - 2;
	int mfxl = 0;
	int i_HeroHP = 10;
	int defen = 0;
	int GameState = _GAME_CHOOSE;
	int jianmian = -1;
	while(1)
	{
		system("cls");
		if(GameState == _GAME_CHOOSE)
		{
			std::cout<<"[С�۷�]"<<std::endl;
			std::cout<<"01)��ʼ\n02)����\n03)�˳�"<<std::endl;
			if((GetAsyncKeyState('1') & 0x8000)
				||(GetAsyncKeyState(VK_NUMPAD1) & 0x8000))
				jianmian = 1;
			if((GetAsyncKeyState('2') & 0x8000)
				||(GetAsyncKeyState(VK_NUMPAD2) & 0x8000))
				jianmian = 2;
			if((GetAsyncKeyState('3') & 0x8000)
				||(GetAsyncKeyState(VK_NUMPAD3) & 0x8000))
				jianmian = 3;
			switch(jianmian)
			{
			case 1:
				{
					GameState = _GAME_INIT;
					jianmian = -1;
				}
				break;
			case 2:
				{
					GameState = _GAME_HELP;
					jianmian = -1;
				}
				break;
			case 3:
				{
					std::cout<<"�����˳���Ϸ,";
					system("pause");
					return;
				}
				break;
			}
		}
		else if(GameState == _GAME_INIT)
		{
			for(int i = 0 ; i < _MAP_S; ++i)
			{
				map[i] = 0;
			}
			x = _MAP_W / 2;
			y = _MAP_H - 2;
			map[_XY(x,y)] = _YX;
			mfxl = 0;
			i_HeroHP = 10;
			defen = 0;
			GameState = _GAME_RUN;
		}
		else if(GameState == _GAME_RUN)
		{
			//���Ƶ�ͼ
			for(int i = 0; i < _MAP_S; ++i)
			{
				switch(map[i])
				{
				case _KD:std::cout<<"��";break;
				case _YX:std::cout<<"��";break;
				case _ZD:std::cout<<"��";break;
				case _MF:std::cout<<"��";break;
				}
				if(_XY_X(i) == _MAP_W - 1)
					std::cout<<std::endl;
			}
			std::cout<<"���� "<<i_HeroHP<<"    �÷� "<<defen<<std::endl;
			//��ײ�ļ��
			//�ӵ����۷����ײ
			for(int i = 0; i < _MAP_S; ++i)
			{
				if(map[i] == _ZD)
				{
					if(_XY_Y(i) > 0)
					{
						//if(map[_XY(_XY_X(i),_XY_Y(i) - 1)] == _MF)
						if(map[i - _MAP_W] == _MF)
						{
							map[i] = map[i - _MAP_W] = _KD;
							defen++;
						}
					}
					break;
				}
			}
			//�۷��Ӣ�۵���ײ
			for(int i = 0; i < _MAP_S; ++i)
			{
				if(map[i] == _YX)
				{
					if(map[_XY(x,y - 1)] == _MF)
					{
						map[_XY(x,y - 1)] = _KD;
						i_HeroHP--;
					}
					break;
				}
			}
			//�ӵ�������
			for(int i = 0; i < _MAP_S; ++i)
			{
				if(map[i] == _ZD)
				{
					if(_XY_Y(i) > 0)
					{
						//if(map[_XY(_XY_X(i),_XY_Y(i) - 1)] == _MF)
						map[i] = _KD;
						map[i - _MAP_W] = _ZD;
					}
					else if(_XY_Y(i) == 0)
						map[i] = _KD;
					break;
				}
			}
			//�۷������
			if(mfxl == 10)
			{
				mfxl = 0;
				//mfxlָÿ���ٴ�ִ��һ�������ѭ��
				for(int i = _MAP_S - 1; i >= 0; --i)
				{
					if(map[i] == _MF)
					{
						if(_XY_Y(i) < _MAP_H - 1)
						{
							map[i] = _KD;
							map[i + _MAP_W] = _MF;
						}
						else if(_XY_Y(i) == _MAP_H - 1)
						{
							map[i] = _KD;
							//���۷����䵽��ͼ��ʱ��Ӣ�۵�Ѫ������
							i_HeroHP--;
						}
					}
				}
			}
			else
				mfxl ++;
			//�����۷�
			//0
			if(rand() % 10 == 0)
			{
				//map[_XY(rand() % _MAP_W,0)] = _MF;
				map[rand() % _MAP_W] = _MF;
			}
			//Ӣ�۵�λ��
			if(GetAsyncKeyState('A') & 0x8000)
			{
				//int yx_xb = 0;
				//for(;yx_xb < _MAP_S && map[yx_xb] != _YX; ++yx_xb)
				//	;
				//if(_XY_X(yx_xb) > 0)
				//{
				//	map[yx_xb] = _KD;
				//	map[yx_xb - 1] = _YX;
				//}
				if(x > 0)
				{
					x--;
					map[_XY((x + 1),y)] = _KD;
					map[_XY(x,y)] = _YX;
				}
			}
			if(GetAsyncKeyState('D') & 0x8000)
			{
				//int yx_xb = 0;
				//for(;yx_xb < _MAP_S && map[yx_xb] != _YX; ++yx_xb)
				//	;
				//if(_XY_X(yx_xb) < _MAP_W - 1)
				//{
				//	map[yx_xb] = _KD;
				//	map[yx_xb + 1] = _YX;
				//}
				if(x < _MAP_W - 1)
				{
					x++;
					map[_XY((x - 1),y)] = _KD;
					map[_XY(x,y)] = _YX;
				}
			}
			//�ӵ�����
			if(GetAsyncKeyState(VK_SPACE) & 1)
			{
				//�õ���ǰ�Ƿ����ӵ�
				bool yzd = false;
				for(int i = 0; i < _MAP_S; ++i)
				{
					if(map[i] == _ZD)
					{
						yzd = true;
						break;
					}
				}
				if(!yzd)
				{
					//��ȡӢ�۵��±�
					//int yx_xb = 0;
					//for(;yx_xb < _MAP_S && map[yx_xb] != _YX; ++yx_xb)
					//	;
					//map[yx_xb - _MAP_W] = _ZD;
					map[_XY(x,(y - 1))] = _ZD;
				}
			}

			//ʤ���ж�
			if(i_HeroHP <= 0)
			{
				std::cout<<"Game Over"<<std::endl;
				system("pause");
				GameState = _GAME_CHOOSE;
			}
		}
		else if(GameState == _GAME_HELP)
		{
			std::cout<<"��Ϸ����"<<std::endl;
			std::cout<<"A�����ƣ�D�����ƣ��ո����ӵ�"<<std::endl;
			system("pause");
			GameState = _GAME_CHOOSE;
		}
	}

	system("pause");
}