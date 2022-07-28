#ifndef _DATA_DEFINE_H_
#define _DATA_DEFINE_H_

#include <map>
#include <string>
#include "DataType.h"
#include "TcpClient.h"

#define _FACE_NUM 58
#define _R_VIEW_W 4
#define _R_VIEW_H 2
#define _SITE_NUM (_R_VIEW_W * _R_VIEW_H * 2)
#define _ROOM_NUM 64

class CPTalkDlg;
class CDC;
class CPMDispatcher;

extern SOCKET g_Socket;//�׽���
extern _PLAYER g_Player;//��ǰ�ͻ��˵��û�
extern CTcpClient g_TcpClient;//Tcp������
extern std::map<std::string,_PLAYER> g_OnlinePlayers;//������ұ�
extern std::map<std::string,CPTalkDlg*> g_PTalkDlgs;//˽�ĶԻ���
extern bool g_bInit;//�Ƿ��ʼ�����

extern CDC g_Table;//��Ϸ������
extern CDC g_Title;//��Ϸ��������
extern CDC g_Room;//��Ϸ��������
extern CDC g_Pokers;//�˿�����
extern CDC g_Faces[_FACE_NUM];//���ͷ������
extern RECT g_Site[_SITE_NUM];//��λ����
extern _ROOM g_Rooms[_ROOM_NUM];//��������
extern CPMDispatcher g_PMDispatcher;//Э���ɷ���

#endif