#include "Mine.h"
#include <time.h>
#include <iostream>

//������ͼ-w:��,h���ߣ�num:����
//��ͼ��ַ
MINEGAME createMINEGAME(int w,int h,int num)
{
	if(w < 1 || h < 1 || num < 1)
		return 0;
	srand((unsigned int)time(0));
	MINEGAME mg = (MINEGAME)malloc(sizeof(_MINE_GAME));
	mg->w = w;
	mg->h = h;
	mg->num = num;
	mg->map = (_MINE*)malloc(sizeof(_MINE) * mg->w * mg->h);
	mg->help = (int*)malloc(sizeof(int) * mg->w * mg->h);
	//�����ͼ
	//�õ���ͼ��С
	int s = mg->w * mg->h;
	for(int i = 0 ; i < s; ++i)
	{
		mg->map[i].is_mine = false;
		mg->map[i].is_open = false;
	}

	//����
	int* p = (int*)malloc(sizeof(int) * s);
	for(int i = 0; i < s;++i)
		p[i] = i;
	for(int i = 0; i < num;++i)
	{
		int index = rand() % s;
		mg->map[p[index]].is_mine = true;
		//mg->map[index].is_mine = true;
		p[index] = p[s - 1];
		s -= 1;
	}
	free(p);

	//����ÿ��������Χ������
	s = mg->w * mg->h;

	int xd[] = {0,1,1,1,0,-1,-1,-1};
	int yd[] = {-1,-1,0,1,1,1,0,-1};
	
	for(int i = 0; i < s;++i)
	{
		mg->map[i].mine_num = 0;
		int x = i % mg->w,y = i / mg->w;
		for(int j = 0; j < 8;++j)
		{
			int cx = x + xd[j];
			int cy = y + yd[j];
			if(cx >= 0 && cx < mg->w 
			&& cy >= 0 && cy < mg->h)
			{
				if(mg->map[cx + cy * mg->w].is_mine)
					mg->map[i].mine_num += 1;
			}
		}
	}
	return mg;
}

//MINEGAME�ĵ�ַ
//����-1,0,1����ʧ�ܣ�������ͨ��
int playMINEGAME(MINEGAME mg,int x,int y)
{
	if(mg->map[x + y * mg->w].is_mine)
		return -1;
	//��������
	mg->help[0] = x + y * mg->w;
	int help_len = 1;//�������鵱ǰ��Ч���ݳ���
	//ѭ����ʼ����ֹ�±�
	int begin = 0,end = 0;
	//����ͼ��
	int xd[] = {0,1,1,1,0,-1,-1,-1};
	int yd[] = {-1,-1,0,1,1,1,0,-1};
	while(1)
	{
		int cur_help_len = help_len;
		for(int i = begin ; i <= end;++i)
		{
			//��������Χ����Ϊ0�ſ���
			if(mg->map[mg->help[i]].mine_num == 0)
			{
				int x = mg->help[i] % mg->w;
				int y = mg->help[i] / mg->w;
				//�õ�(x,y)��Χ8������
				for(int j = 0; j < 8 ;++j)
				{
					int cx = x + xd[j];
					int cy = y + yd[j];
					if(cx >= 0 && cx < mg->w 
					&& cy >= 0 && cy < mg->h)
					{
						//������
						if(!mg->map[cx + cy * mg->w].is_mine)
						{
							bool no = true;
							for(int k = 0; k < help_len;++k)
							{
								if(mg->help[k] == cx + cy * mg->w)
								{
									no = false;
									break;
								}
							}
							if(no)
								mg->help[help_len++] = cx + cy * mg->w;
						}
					}
				}
			}
		}
		if(cur_help_len == help_len)
			break;
		else
		{
			begin = cur_help_len;
			end = help_len - 1;
		}
	}

	for(int i = 0 ; i < help_len;++i)
		mg->map[mg->help[i]].is_open = true;

	//�ж�ͨ��
	for(int i = 0; i < mg->w * mg->h ; ++i)
	{
		if(!mg->map[i].is_mine && !mg->map[i].is_open)
			return 0;
	}
	return 1;
}

//����
void endMINEGAME(MINEGAME mg)
{
	free(mg->help);
	free(mg->map);
	free(mg);
}