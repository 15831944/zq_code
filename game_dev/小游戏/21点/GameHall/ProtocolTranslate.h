#ifndef _PROTOCOL_TRANSLATE_H_
#define _PROTOCOL_TRANSLATE_H_

#include "DataType.h"
#include <map>
#include "TcpClient.h"
//----------------------------------------------------------------------------------------------
//��½���
//----------------------------------------------------------------------------------------------
//----------------------------------
//��������ͻ��˷�����Ϣ(C-S��Ϣ)
//----------------------------------
//1.ע���˺�
//������ע�����˺ţ����룬Tcp�ͻ�����
void Register(const char* id, const char* pw, CTcpClient& tc);

//2.��½�˺�
//��������½���˺ţ����룬Tcp�ͻ�����
void Login(const char* id, const char* pw, CTcpClient& tc);

//----------------------------------
//�ͻ��˽��ܷ�������Ϣ����(S-C��Ϣ)
//----------------------------------
//1.��½�ɹ�
//�������ͻ����¼���Ϣ����Ҫ���ĵ�ǰ������ұ�
void LoginSuccess(_CNET_EVENT& ne,std::map<std::string,_PLAYER>& players);

//2.����ҵ�½�ɹ�
//�������ͻ����¼���Ϣ�����������Ϣ����ǰ�ͻ�����ҵ�ID��
//����true��ʾ������Լ�����Ϣ
//����false��ʾ��������ҵ������Ϣ
bool NewClientLogin(_CNET_EVENT& ne,_PLAYER& player,std::string clientid);


//----------------------------------------------------------------------------------------------
//�������
//----------------------------------------------------------------------------------------------
//1.����޸ĳɹ�
//�������ͻ����¼���Ϣ���������֣�ͷ������ID��
//����true��ʾ������Լ�����Ϣ
//����false��ʾ��������ҵ������Ϣ
void ChangeDataSuccess(_CNET_EVENT& ne,std::string& name, int& face, std::string& clientid);

//2.��������
//�������ͻ����¼���Ϣ�����ķ�����id�����ķ�������
void PublicTalk(_CNET_EVENT& ne,std::string& id, std::string& message);

//3.˽������
//�������ͻ����¼���Ϣ�����ķ�����id�����ķ�������
void PrivateTalk(_CNET_EVENT& ne,std::string& id, std::string& desid, std::string& message);

//4.�������
//�������ͻ����¼���Ϣ������������id
void PlayerOffLine(_CNET_EVENT& ne,std::string& id);

//5.��ҽ��뷿��ɹ�
//�������ͻ����¼���Ϣ�����Ľ��뷿����id, �·���ţ�����λ��
void EnterRoomSuccess(_CNET_EVENT& ne,std::string& id, int& roomnew, int& sitenew);

//6.���׼���ɹ�
//�������ͻ����¼���Ϣ�����׼����id
void ReadSuccess(_CNET_EVENT& ne,std::string& id);

//7.����˳�����ɹ�
//�������ͻ����¼���Ϣ�������˳�������id
void ExitRoomSuccess(_CNET_EVENT& ne,std::string& id);

//8.���ȡ��׼���ɹ�
//�������ͻ����¼���Ϣ�����׼����id
void ReadyCancelSuccess(_CNET_EVENT& ne,std::string& id);

//----------------------------------------------------------------------------------------------
//��Ϸ���
//----------------------------------------------------------------------------------------------
//1.��ʼ����Ϸ
//�������ͻ����¼���Ϣ��������id����õĳ�ʼ��
void NewGame(_CNET_EVENT& ne,std::string& id,int &num);

//2.�����������
//�������ͻ����¼���Ϣ�����׼����id,���֣�ʤ������ƽ
void UpdatePlayerData(_CNET_EVENT& ne,std::string& id,
					  int& score, int& win, int& lose, int& draw);

//3.�������ѡ��
//�������ͻ����¼���Ϣ��������id
void MakeChoice(_CNET_EVENT& ne,std::string& id);

//4.��һ������
//�������ͻ����¼���Ϣ������Ʊ��
void GetNew(_CNET_EVENT& ne,int &num);

//5��һ��21��ʤ��
//�������ͻ����¼���Ϣ�����ʤ����id, ʤ���ߵ����һ���ƣ���һ�����Ƶ���������һ��������
void Win_21(_CNET_EVENT& ne,std::string& id,
			int& lastpoker,int& pokernum,int* pokers);

//6��ұ���ʧ��
//�������ͻ����¼���Ϣ�����ʧ����id,ʧ���ߵ����һ���ƣ���һ�����Ƶ���������һ��������
void LoseOutRange(_CNET_EVENT& ne,std::string& id,
			int& lastpoker,int& pokernum,int* pokers);

//7��ұȵ�����ʤ
//�������ͻ����¼���Ϣ�����ʤ����id,��һ�����Ƶ���������һ��������
void WinBigger(_CNET_EVENT& ne,std::string& id,
			int& pokernum,int* pokers);

//8��ұȵ���ƽ��
//�������ͻ����¼���Ϣ����һ�����Ƶ���������һ��������
void Draw(_CNET_EVENT& ne,int& pokernum,int* pokers);

//9��Ϸ������Ϣ
//�������ͻ����¼���Ϣ�����׼����id,���֣�ʤ������ƽ,���״̬������ţ���λ��
void UpdatePlayerData(_CNET_EVENT& ne,std::string& id,
					  int& score, int& win, int& lose, int& draw, 
					  int& playerstate, int&roomnum, int& sitenum);

//10��ҷ�������ʧ��
//�������ͻ����¼���Ϣ�����ʧ����id
void LoseGiveUp(_CNET_EVENT& ne,std::string& id);

//11�������ʧ��
//�������ͻ����¼���Ϣ�����������id
void LoseRunAway(_CNET_EVENT& ne,std::string& id);

//12�����Ϸ������
//�������ͻ����¼���Ϣ�����ķ�����id�����ķ�������
void TalkInGame(_CNET_EVENT& ne,std::string& id, std::string& message);

#endif