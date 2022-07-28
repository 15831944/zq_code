#ifndef _UI_H_
#define _UI_H_

//UI(User Interface) : �û��ӿ�,������Ϸ���������û�
//���н����Ľ���Ԫ��
//UI��Ϣ
#define _UIM_C_ENTER		0 // ������
#define _UIM_C_QUIT			1 //����˳�
#define _UIM_C_MOVE_IN		2 //����ڿؼ����ƶ�
#define _UIM_C_MOVE_OUT		3 //����ڿؼ����ƶ�
#define _UIM_C_LBD_IN		4 //����ڿؼ��ϰ���
#define _UIM_C_LBU_IN		5 //����ڿؼ���̧��
#define _UIM_C_LBD_OUT		6 //����ڿؼ��ⰴ��
#define _UIM_C_LBU_OUT		7 //����ڿؼ���̧��
#define _UIM_C_RBD_IN		8 //�Ҽ��ڿؼ��ϰ���
#define _UIM_C_RBU_IN		9 //�Ҽ��ڿؼ���̧��
#define _UIM_C_RBD_OUT		10//�Ҽ��ڿؼ��ⰴ��
#define _UIM_C_RBU_OUT		11//�Ҽ��ڿؼ���̧��

//ͬһʱ����ͬһ������ֻ����һ���ؼ��յ�������Ϣ���ַ���Ϣ
#define _UIM_K_D			12//������
#define _UIM_K_U			13//��̧��
#define _UIM_K_CHAR			14//����

class CUI
{
	int m_X,m_Y,m_W,m_H;//����
	bool m_View;//�ܷ񿴼�
	bool m_Act;//�Ƿ񼤻�
public:
	CUI(int x,int y,int w,int h,bool v = true,bool a = true);

	void SetRect(int x,int y,int w,int h);

	void GetRect(int* x,int* y,int* w,int* h);

	void SetView(bool View);

	bool GetView();

	void SetAct(bool Act);

	bool GetAct();

	//��Ҫ����ʵ�ֵ��麯��
	virtual void Init();//��ʼ��
	virtual void ActRender();//������Ⱦ
	virtual void UnactRender();//�Ǽ�����Ⱦ

	//�����Ϣ��p1Ϊx����,p2Ϊy����,(����ڿؼ����ζ���)
	//������Ϣ��p1�����ֵ
	//�ַ���Ϣ��p1�����ַ���p2��ʾ��(1)��(0)Ϊ˫�ֽ�
	virtual void OnMsg(int Msg,int p1,int p2);//�õ���Ϣ
	
	virtual void End();
};

#endif