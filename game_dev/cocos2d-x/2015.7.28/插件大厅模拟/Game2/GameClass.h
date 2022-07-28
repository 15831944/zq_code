#ifndef _GAME_CLASS_H_
#define _GAME_CLASS_H_

class CGameClass
{
public:
	virtual const char* name() = 0;
	virtual void init() = 0;
	virtual void run() = 0;
	virtual void end() = 0;
};

//ÿ����ɾ������Ϸ��DLL�ж������ṩһ����������
//CGameClass* getGame()
//{
//	return new XXX;
//}

#endif