#ifndef _PROTOCOL_H
#define _PROTOCOL_H


/*
//--------------��ϷЭ��--------------
//--------0-100Ϊ��½ע���õ�Э��---------
//--------101-200Ϊ��������Э��-------
//--------201-300Ϊ��Ϸ21������Э��-------
*/

#define P_LOGIN_MIN 0
#define P_LOGIN_MAX 100

#define P_HALL_MIN  101
#define P_HALL_MAX  200

#define P_GAME_BLACK_JACK_MIN 201
#define P_GAME_BLACK_JACK_MAX 300

//Э��ԭ��
struct _PROTOCOL
{
	int type;
};

#endif