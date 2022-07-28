#include<iostream>
#include<time.h>
#include "TCS.h"


//��ͼ
char map[_MAP_MAX_W * _MAP_MAX_H];

//��¼�߳�������
int she[_MAP_MAX_W * _MAP_MAX_H];

//�߳�
int she_num = 0;
//�߷���
int she_dir = 0;

//�ϰ�
int zhangai[_MAP_MAX_W * _MAP_MAX_H];
//�ϰ�����
int zhangai_num = 0;

//����
int gz;

//�Ƿ��ʼ���ɹ�
bool init = false;

int w;

int h;

//̰���߳�ʼ������
//mapW:��ͼ��
//mapH:��ͼ��
//����:�ɹ���ʧ��(���߲��Ϸ�Ҫ�󽫵���ʧ��)
bool tcsInit(int mapW, int mapH)
{
	srand((unsigned int)time(0));

	if(mapW < _MAP_MIN_W || mapW >_MAP_MAX_W 
		|| mapH <_MAP_MIN_H || mapH >_MAP_MAX_H)
		return false;
	else
	{
		::w = mapW;
		::h = mapH;

		she[0] = rand() % (mapW * mapH);
		she_num = 1;
		she_dir = rand() % 4;

		zhangai_num = (mapW * mapH) / 40;

		for(int i = 0; i < zhangai_num; ++i)
		{
			int suiji = rand() % (mapW * mapH);
			bool chongfu = false;
			for(int j = 0; j < i; ++j)
			{
				if(suiji == zhangai[j])
				{
					chongfu = true;
					break;
				}
			}
			if(chongfu)
				i--;
			else
				zhangai[i] = rand() % (mapW * mapH);
		}
		gz = rand() % (mapW * mapH);
		return init = true;
	}
}

//̰�������к���
//input:����,_TCS_INPUT_NONE��_TCS_INPUT_UP��
//_TCS_INPUT_DOWN��_TCS_INPUT_LEFT��
//_TCS_INPUT_RIGHT�ֱ����
//�����롢�ϡ��¡�����
//����:-3����û�г�ʼ����
//-2�����������
//-1������ͷҧ������
//0����ײ�����ϰ�
//1��������
//2�������һ������
int tcsRun(int input)
{
	if(!init)
		return -3;
	if(input < _TCS_INPUT_NONE || input > _TCS_INPUT_RIGHT)
		return -2;

	//����
	if(input != _TCS_INPUT_NONE)
	{
		switch(she_dir)
		{
		case 0:
		case 1:
			{
				if(input == _TCS_INPUT_LEFT || input == _TCS_INPUT_RIGHT)
					she_dir = input - 1;
			}
			break;
		case 2:
		case 3:
			{
				if(input == _TCS_INPUT_UP || input == _TCS_INPUT_DOWN)
					she_dir = input - 1;
			}
			break;
		}
	}

	//��ͷ�������ײ
	bool df = false;

	if(she[0] == gz)
	{
		gz = rand() % (w * h);
		she_num += 1;
		df = true;
	}

	//��ͷ������
	for(int i = 1; i < she_num ; ++i)
	{
		if(she[0] == she[i])
			return -1; 
	}

	//��ͷ���ϰ�
	for(int i = 0; i < zhangai_num ; ++i)
	{
		if(she[0] == zhangai[i])
			return 0; 
	}

	//�����ƶ�
	for(int i = she_num - 1;i > 0;--i)
		she[i] = she[i - 1];
	//��ͷ�ƶ�
	int x = she[0] % w;
	int y = she[0] / w;

	switch(she_dir)
	{
	case 0:y = ((y == 0) ? h - 1: y - 1);break;
	case 1:y = ((y == h  - 1) ? 0: y + 1);break;
	case 2:x = ((x == 0) ? w - 1: x - 1);break;
	case 3:x = ((x == w  - 1) ? 0: x + 1);break;
	}

	she[0] = x + y * w;
	return df ? 2 : 1;
}

//̰�������ú���
//����:�ɹ���ʧ��(û�г�ʼ��������ʧ��)
bool tcsRestart()
{
	return tcsInit(w,h);
}

//̰���ߵõ���ͼ����
//����:0���ͼ�����׵�ַ,
//���ڻ���(û�г�ʼ�������·���0)
const char* tcsMap()
{
	if(!init)
		return 0;
	for(int i = w * h;i >= 0;--i)
		map[i] = _KD;
	for(int i = 0; i < zhangai_num;++i)
		map[zhangai[i]] = _ZA;
	map[she[0]] = _ST;
	for(int i = 1;i < she_num;++i)
		map[she[i]] = _SS;
	map[gz] = _GZ;
	return map;
}