#ifndef LOGIN_PROTOCOL_H_
#define LOGIN_PROTOCOL_H_

#include "Protocol.h"
/*
//--------------��ϷЭ��--------------
//--------0-100Ϊ��½ע���õ�Э��---------
//--------101-200Ϊ��������Э��-------
//--------201-300Ϊ��Ϸ21������Э��-------
*/

//��½���
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

#define DL_CS_DL			0//��½��C-S)
#define DL_CS_ZC			1//ע�ᣨC-S)

#define DL_SC_NO_ID			2//û���˻���S-C)
#define DL_SC_PW_ERROR		3//�������S-C)
#define DL_SC_DL_OK			4//��½�ɹ���S-C)
#define DL_SC_NEW_CLIENT	5//��������ߣ�S-C)
#define DL_SC_ZC_FAIL		6//ע��ʧ�ܣ�S-C)
#define DL_SC_ZC_OK			7//ע��ɹ���S-C)
#define DL_SC_DL_AGAIN		8//�ظ���½��S-C)


//��½���
//----------------------------------------------------------------------------------
//1:�ͻ��������������C-S��
//----------------------------------------------------------------------------------
//��½
struct CS_DL : public _PROTOCOL
{
	CS_DL(){type = DL_CS_DL;}
	char id[32];
	char pw[32];
};

//ע��
struct CS_ZC : public _PROTOCOL
{
	CS_ZC(){type = DL_CS_ZC;}
	char id[32];
	char pw[32];
};

//----------------------------------------------------------------------------------
//2:�����������ͻ��ˣ�S-C��
//----------------------------------------------------------------------------------
//�˺Ų�����
struct SC_NO_ID : public _PROTOCOL
{
	SC_NO_ID(){type = DL_SC_NO_ID;}
};

//�������
struct SC_PW_ERROR : public _PROTOCOL
{
	SC_PW_ERROR(){type = DL_SC_PW_ERROR;}
};

//��½
struct SC_DL_OK : public _PROTOCOL
{
	SC_DL_OK(){type = DL_SC_DL_OK;}
	int num;
	//����Ҫ�������������ҵ���Ϣ
};

//���û�
struct SC_NEW_CLIENT : public _PROTOCOL
{
	SC_NEW_CLIENT(){type = DL_SC_NEW_CLIENT;}
};

//ע��ʧ��
struct SC_ZC_FAIL : public _PROTOCOL
{
	SC_ZC_FAIL(){type = DL_SC_ZC_FAIL;}
};

//ע��ɹ�
struct SC_ZC_OK : public _PROTOCOL
{
	SC_ZC_OK(){type = DL_SC_ZC_OK;}
};

//����ظ���¼
struct SC_DL_AGAIN : public _PROTOCOL
{
	SC_DL_AGAIN(){ type = DL_SC_DL_AGAIN; }
};

#endif