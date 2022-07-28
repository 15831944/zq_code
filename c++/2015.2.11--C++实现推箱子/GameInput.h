//------------------------
//CGameInput:��Ϸ������
//��Ҫ������Ϸ�м�������ļ�ֵ
//------------------------

#ifndef _GAMEINPUT_H_
#define _GAMEINPUT_H_

#define _KEY_UP   0   //��̧��
#define _KEY_DOWN 1   //������

class CGameInput
{
	int m_iKeyCount;//����������
	char* m_pKey;//��¼��Ҫ�ļ�ֵ���������¼�����ϵ����еĴ�д��ĸ��ʽ
	char* m_pKeyState;//����״̬
public:
	CGameInput();
	~CGameInput();

	//���ü���״̬
	void SetKeyState(char state);

	//��ȡָ���ļ���״̬ ����indexΪ�±�ļ���״̬
	char GetKeyState(int index);

	//��ȡָ���ļ���״̬���ذ��µļ�
	char GetKeyState();
};

#endif