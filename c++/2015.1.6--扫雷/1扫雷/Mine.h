#ifndef _MINE_H_
#define _MINE_H_

//���׽ṹ-ÿ�����ӵ�״̬
struct _MINE 
{
	bool is_mine;//�Ƿ�Ϊ��
	bool is_open;//�Ƿ��
	char mine_num;//��Χ������
};

//������ͼ�ṹ-������ͼ��״̬
typedef struct _MINE_GAME
{
	int w,h,num;//��ͼ���ߣ�������
	_MINE* map;//��ͼ
	int* help;//��������
	
}* MINEGAME;

//������ͼ-w:��,h���ߣ�num:����
//��ͼ��ַ
MINEGAME createMINEGAME(int w,int h,int num);

//MINEGAME�ĵ�ַ
//����-1,0,1����ʧ�ܣ�������ͨ��
int playMINEGAME(MINEGAME mg,int x,int y);

//����
void endMINEGAME(MINEGAME mg);
#endif
//����ͷ�ļ�Դ�ļ�ֻ�漰����Ϸ�������Լ��߼������漰��Ϸ������
//�����Ŀ�����ڷ�����ֲ����Ϊ���������ϵͳ��ϵ�Ƚ����У������
//ģ����д�������������ôһ������ϣ����ݴ�������������ϵͳ������
//Ҳ��ʹ�ã���ô����Ҫ������������޸ģ������Ͳ�����.