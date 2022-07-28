#ifndef _GAME_INPUT_H_
#define _GAME_INPUT_H_

#define _KS_ERROR 0
#define _KS_KEEP_UP 1 //����̧��
#define _KS_NOW_UP 2 //��ǰ̧��
#define _KS_KEEP_DOWN 3 //��������
#define _KS_NOW_DOWN 4 //��ǰ����

class CGameInput
{
private:
	int m_KeyNum;
	int* m_Key;
	char* m_KeyState;
	
public:
	CGameInput(int* Key, int KeyNum);
	~CGameInput();

	void Run();

	//�õ�ָ���±���Ǹ����ĵ�ǰ״̬
	char KeyState(int KeyIndex);
};

#endif