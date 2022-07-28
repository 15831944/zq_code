#ifndef _GAME_PROTOCOL_H_
#define _GAME_PROTOCOL_H_

#define _NEW_PLAYER 0
#define _OLD_PLAYER 1
#define _PLAYER_MOVE 2
#define _SOMEONE_MOVE 3
#define _PLAYER_QUIT 4

//�����Ϣ
struct _GAME_PLAYER
{
	int name, x, y;
};

//��ϷЭ��
struct _GAME_PROTOCOL
{
	int id; //Э���id��
};

//0��Э�飺������֪ͨ�������/��/�������֡�λ�á��������Ϣ
struct _SC_NEW_PLAYER : public _GAME_PROTOCOL
{
	_SC_NEW_PLAYER()
	{
		id = _NEW_PLAYER;
	}
	_GAME_PLAYER new_player; //���������
	int old_player_num; //���������
	_GAME_PLAYER old_player[25]; //�������Ϣ
};

//1��Э�飺������֪ͨ������½���������/��/�������֡�λ��
struct _SC_OLD_PLAYER : public _GAME_PROTOCOL
{
	_SC_OLD_PLAYER()
	{
		id = _OLD_PLAYER;
	}
	_GAME_PLAYER new_player; //���������
};

//2��Э�飺�ͻ����ƶ�֮��֪ͨ���������Լ���λ��
struct _CS_PLAYER_MOVE : public _GAME_PROTOCOL
{
	_CS_PLAYER_MOVE()
	{
		id = _PLAYER_MOVE;
	}
	_GAME_PLAYER player; //�������
};

//3��Э�飺������֪ͨ�������������ƶ���
struct _SC_SOMEONE_MOVE : public _GAME_PROTOCOL
{
	_SC_SOMEONE_MOVE()
	{
		id = _SOMEONE_MOVE;
	}
	_GAME_PLAYER player; //�������
};

//4��Э�飺������֪ͨ�������������뿪��
struct _SC_PLAYER_QUIT : public _GAME_PROTOCOL
{
	_SC_PLAYER_QUIT()
	{
		id = _PLAYER_QUIT;
	}
	int name; //�������
};

#endif