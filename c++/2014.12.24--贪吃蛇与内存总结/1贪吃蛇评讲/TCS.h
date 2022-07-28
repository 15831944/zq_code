#define _MAP_MIN_W 5 //��ͼ������
#define _MAP_MAX_W 20 //��ͼ������
#define _MAP_MIN_H 5 //��ͼ������
#define _MAP_MAX_H 20 //��ͼ������

#define _TCS_INPUT_NONE 0 //��ָ��
#define _TCS_INPUT_UP 1 //��ָ��
#define _TCS_INPUT_DOWN 2 //��ָ��
#define _TCS_INPUT_LEFT 3 //��ָ��
#define _TCS_INPUT_RIGHT 4 //��ָ��

#define _KD 0 //�յ�
#define _ZA 1 //�ϰ�
#define _ST 2 //��ͷ
#define _SS 3 //����
#define _GZ 4 //����

//̰���߳�ʼ������
//mapW:��ͼ��
//mapH:��ͼ��
//����:�ɹ���ʧ��(���߲��Ϸ�Ҫ�󽫵���ʧ��)
bool tcsInit(int mapW, int mapH);

//̰�������к���
//input:����,_TCS_INPUT_NONE��_TCS_INPUT_UP��
//_TCS_INPUT_DOWN��_TCS_INPUT_LEFT��
//_TCS_INPUT_RIGHT�ֱ����
//�����롢�ϡ��¡�����
//����:-3����û�г�ʼ����
//-2�����������
//-1������ͷҧ������
//0����ײ�����ϰ���1����������
//2�������һ������
int tcsRun(int input);

//̰�������ú���
//����:�ɹ���ʧ��(û�г�ʼ��������ʧ��)
bool tcsRestart();

//̰���ߵõ���ͼ����
//����:0���ͼ�����׵�ַ,
//���ڻ���(û�г�ʼ�������·���0)
const char* tcsMap();
