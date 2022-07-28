#ifndef _LLK_H
#define _LLK_H
//�ϰ�
#define _ZA 11
//ͨ·
#define _TL 12
//·��
#define _LJ 13
#define _XX 1 //����
#define _LX 2 //����
#define _YX 3 //Բ��
#define _SJ 4 //������
#define _FK 5 //����
//ѡ�и���ͼ�������ʾ
#define S_XX 6 //ʵ������
#define S_LX 7 //ʵ������
#define S_YX 8 //ʵ��Բ��
#define S_SJ 9 //ʵ��������
#define S_FK 10 //ʵ�ķ���
#define MAP_W 12
#define MAP_H 12
#define MAP_S (MAP_W) *(MAP_H)
#include <vector>
using namespace std;
class CLLK
{
	struct _NODE
	{
		int cur;
		int parent;
		int G;
		int H;
	};
	static vector<_NODE> open;
	static vector<_NODE> close;
	static unsigned int _GetMinF();
	static bool _InClose(int index);
	static int _InOpen(int index);
public:
	static int FindPath(int *map,int w,int h,int b,int e,int *path);
};
#endif