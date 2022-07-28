#ifndef _A_STAR_H_
#define _A_STAR_H_
#include <vector>

class AStar
{
	struct _NODE
	{
		int cur;
		int parent;
		int G;
		int H;
	};

	static std::vector<_NODE> open;
	static std::vector<_NODE> close;
	static unsigned int _GetMinF();
	static bool _InClose(int index);
	static int _InOpen(int index);

public:
	//�������-1��ʾ���������⣬
	//�������0���ʾû���ҵ�·
	//������ش���0��ʾ�ҵ�·������·��
	static int FindPath(const char* map,//��ͼ
						int w,//��ͼ�Ŀ�
						int h,//��ͼ��
						int b,//Ѱ·��ʼλ��
						int e,//Ѱ·����λ��
						int* path);//�洢Ѱ��·����
};



#endif