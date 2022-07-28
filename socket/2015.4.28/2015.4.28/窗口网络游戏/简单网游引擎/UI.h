#ifndef _UI_H_
#define _UI_H_

#include <string>

//UI��״̬
//1)�ɼ�
//  1)����
//  2)������
//2)���ɼ�

//UI�Ĺ���
//��������
//�������
//֪ͨ����

//UI���յ�����������¼�����ÿ��UIҪ����
//�Լ����ص��ж�����������¼�Ȼ�����UI
//�Լ�����Ϣ����������дһ����ťUI����ô
//һ����ťUI�յ������������ڲ����¡���
//��������ڲ�̧�����ǾͿ����жϳ�����
//���������ťUI������һ�����������Ȼ��
//���ǾͿ��԰�����������д��һ����ť��
//��Ϣ������֪ͨ�����ĳ���
#define _UIE_CURSOR_ENTER 0 //������
#define _UIE_CURSOR_QUIT 1 //����˳�
#define _UIE_CURSOR_MOVE_IN 2 //������ڲ��ƶ�
#define _UIE_CURSOR_MOVE_OUT 3 //������ⲿ�ƶ�
#define _UIE_L_DOWN_IN 4 //���������ڲ�����
#define _UIE_L_DOWN_OUT 5 //���������ⲿ����
#define _UIE_L_UP_IN 6 //���������ڲ�̧��
#define _UIE_L_UP_OUT 7 //���������ⲿ̧��
#define _UIE_R_DOWN_IN 8 //����Ҽ����ڲ�����
#define _UIE_R_DOWN_OUT 9 //����Ҽ����ⲿ����
#define _UIE_R_UP_IN 10 //����Ҽ����ڲ�̧��
#define _UIE_R_UP_OUT 11 //����Ҽ����ⲿ̧��
#define _UIE_K_DOWN 12 //���̰���
#define _UIE_K_UP 13 //����̧��
#define _UIE_CHAR 14 //�ַ�

class CScene;

class CUI
{
	friend class CGameEngine;
	friend class CScene;

protected:
	int m_X, m_Y, m_W, m_H; //����
	bool m_Visible; //�ɼ���
	bool m_Enable; //������
	std::string m_ID; //����
	CScene* m_Scene; //�����ĳ���

public:
	CUI(int X, int Y, int W, int H, bool Visible = true, bool Enable = true);
	virtual ~CUI();

	void SetRect(int X, int Y, int W, int H);
	void GetRect(int* X, int* Y, int* W, int* H);
	void SetVisible(bool Visible);
	bool GetVisible();
	void SetEnable(bool Enable);
	bool GetEnable();

	virtual void Init(); //��ʼ��
	virtual void Enter(); //������������
	virtual void Quit(); //���������˳�
	virtual void End(); //�˳�
	
	//��Event������¼���ʱ��X��Y��ʾ��ǰ����λ��
	//��Event��_UIE_K_DOWN��_UIE_K_UP��ʱ��XΪ���µļ��ļ�ֵ
	//��Event��_UIE_CHAR��ʱ��XΪ�ַ��ı��룬YΪ˫�ֽڱ�־��Ϊ0��ʾ���ֽ����֣�Ϊ1��ʾ˫�ֽ����֣�
	virtual void OnEvent(int Event, int X, int Y); //����������¼�
	virtual void Render(bool Enable); //���
};

#endif