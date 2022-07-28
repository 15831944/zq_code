#include "Astar.h"

std::vector<AStar::_NODE> AStar::open;
std::vector<AStar::_NODE> AStar::close;

#define _ABS(v) ((v) < 0 ? -(v) : (v))
#define _H_VALUE(c,e) (_ABS((c)%w - (e)%w) + _ABS((c)/w - (e)/w))


unsigned int AStar::_GetMinF()
{
	unsigned int i = 0;
	for(unsigned int j = 1;j < open.size();++j)
	{
		if((open[i].G + open[i].H) > (open[j].G + open[j].H))
			i = j;
	}
	return i;
}
bool AStar::_InClose(int index)
{
	for(int i = 0; i < close.size();++i)
	{
		if(index == close[i].cur)
			return true;
	}
	return false;
}
int AStar::_InOpen(int index)
{
	for(int i = 0; i < open.size();++i)
	{
		if(index == open[i].cur)
			return i;
	}
	return -1;
}

//�������-1��ʾ���������⣬
//�������0���ʾû���ҵ�·
//������ش���0��ʾ�ҵ�·������·��
int AStar::FindPath(const char* map,//��ͼ
						int w,//��ͼ�Ŀ�
						int h,//��ͼ��
						int b,//Ѱ·��ʼλ��
						int e,//Ѱ·����λ��
						int* path)//�洢Ѱ��·����
{
	if(!map || w < 1 || h < 1|| b < 0 || b >= w * h || e < 0 || e >= w * h || !path)
		return -1;

	//�˷���ƫ��
	// 701
	// 6 2
	// 543
	
	const int offset_x[] = 
	{
		0,1,1,1,0,-1,-1,-1
	};
	const int offset_y[] =
	{
		-1,-1,0,1,1,1,0,-1	
	};

	//��տ���ձ�
	open.clear();
	close.clear();

	//����뿪��
	_NODE begin = {b,-1,0,_H_VALUE(b,e)};

	open.push_back(begin);
	//Ѱ·ѭ��
	while(!open.empty())
	{
		//�õ�������Fֵ��С�Ľڵ���±�
		unsigned int min_f_i = _GetMinF();
		//��������Fֵ��С���Ǹ��ڵ�ɾ��
		_NODE min_f_n = open[min_f_i];
		//std::vector <_NODE>::iterator it = open.begin();
		//open.erase(it + min_f_i);
		open.erase(open.begin() + min_f_i);
		//����ձ�
		close.push_back(min_f_n);
		//�õ���ǰ����ڵ������
		int cx = min_f_n.cur % w;
		int cy = min_f_n.cur / w;
		//ѭ����ǰ��İ˸�����
		for(int i = 0; i < 8 ; ++i)
		{
			int dx = cx + offset_x[i];
			int dy = cy + offset_y[i];
			if(dx >= 0 && dx < w && dy >= 0 && dy < h)
			{
				//�ҵ�·
				int di = dx + dy * w;
				if(di == e)
				{
					//��ֹ����ձ�
					_NODE node = {di,min_f_n.cur,0,0};
					close.push_back(node);
					//������Ľڵ���±�
					int index = close.size() - 1;
					//ѭ���õ�·
					int pathlen = 0;
					while(index != -1)
					{
						path[pathlen++] = close[index].cur;
						int j = index;
						int k = close[index].parent;
						if(k == -1)
							break;

						while(1)
						{
							if(close[j].cur == k)
								break;
							else 
								--j;
						}
						index = j;
					}

					return pathlen;
				}
				else
				{
					//�����ϰ�
					if(map[di] > 0)
					{
						//���ڱձ���
						if(!_InClose(di))
						{
							
							int r = _InOpen(di);
							int curG = min_f_n.G + (i % 2 == 1 ? 7 : 5);
							//���ڿ�����
							if(r == -1)
							{
								_NODE node = {di,min_f_n.cur,curG,_H_VALUE(di,e)};
								open.push_back(node);
							}
							else
							{
								//�����ǰ��Gֵ���ڿ����е�GС��
								//�����Gֵ
								if(open[r].G < curG)
								{
									open[r].parent = min_f_n.cur;
									open[r].G = curG;
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}