//����Ϸ��Ҫ���߼�������Ҫ��һЩ��
//ȫ�ֱ���������������(��ֻ�Ǳ�ģ���õ�
//����ģ�����Ҳ�õĵ�)
//���ֻ�б������õ����ڸ�ģ���cpp�ļ���
//����
#define _MAP_W 3   //��ͼ��
#define _MAP_H 3   //��ͼ��
#define _MAP_S (_MAP_W * _MAP_H) //��ͼ�ܴ�С

#define _KD 0  //�յ�
#define _LS 1  //����
#define _GJ 2  //����
#define _SW 3  //����

extern char map[_MAP_S];//��ͼ
extern bool input[9];//����״̬
extern int hp,score;//Ѫ��������

void Game_Init();//��Ϸ��ʼ��

void Game_Logic();//��Ϸ�߼�
