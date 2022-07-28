#ifndef _PROTOCOL_FILTER_H_
#define _PROTOCOL_FILTER_H_

//�������˵�Э��ɸѡ��
#include "..\\GameProtocol\\Protocol.h"
#include "..\\GameProtocol\\LoginProtocol.h"
#include "..\\GameProtocol\\HallProtocol.h"
#include "..\\GameProtocol\\BlackJackProtocol.h"
#include "TcpServer.h"
#include "DataType.h"
#include <map>
#include "BlackJack.h"
/*
//--------------��ϷЭ��--------------
//--------1-100Ϊ��½ע���õ�Э��---------
//--------101-200Ϊ��������Э��-------
//--------201-300Ϊ��Ϸ21������Э��-------
*/

//Э�鴦���ɷ�
void ProtocolDispatcher(_SNET_EVENT& ne);

//��¼ģ��Э�����
void LoginProtoclTranslate(int type, _SNET_EVENT& ne);
//��½
void Login(_SNET_EVENT& ne);
//ע��
void Register(_SNET_EVENT& ne);


//����ģ��Э�����
void HallProtoclTranslate(int type, _SNET_EVENT& ne);
//�����������
void ChangePlayerData(_SNET_EVENT& ne);
//��������
void PublicTalk(_SNET_EVENT& ne);
//˽��
void PrivateTalk(_SNET_EVENT& ne);
//���뷿��
void EnterRoom(_SNET_EVENT& ne);
//׼��
void Read(_SNET_EVENT& ne);
//�˳�����
void ExitRoom(_SNET_EVENT& ne);
//ȡ��׼��
void ReadyCancel(_SNET_EVENT& ne);

//21����Ϸģ��Э�����
void BlackJackProtocolTranslate(int type, _SNET_EVENT& ne);
//����Ϸ
void NewGame(int roomnum);
//��������
void ChoiceContinue(_SNET_EVENT& ne);
//ֹͣ����
void ChoiceStop(_SNET_EVENT& ne);
//����������Ϸ
void ChoiceGiveUp(_SNET_EVENT& ne);
//��Ϸ������
void TalkInGame(_SNET_EVENT& ne);
//����
void RunAway(_SNET_EVENT& ne);
//��Ϸ����
void GameEnd(_PLAYER* p1, _PLAYER* p2,std::map<int,CBlackJack>::iterator& game);
#endif