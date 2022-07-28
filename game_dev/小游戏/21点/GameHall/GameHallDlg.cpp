// GameHallDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameHall.h"
#include "GameHallDlg.h"
#include "Login.h"
#include "DataChange.h"
#include "PTalkDlg.h"
#include "ProtocolMessageDispatcher.h"
#include "GameSel.h"

#define _ROOM_W 134
#define _ROOM_H 92
#define _FACE_L_W 64
#define _FACE_L_H 64
#define _FACE_S_W 32
#define _FACE_S_H 32
#define _LBORDER 30
#define _TBORDER 20
#define _POKER_W 75
#define _POKER_H 111


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//class CPTalkDlg;

SOCKET g_Socket;//�׽���
_PLAYER g_Player;//��ǰ�ͻ��˵��û�
CTcpClient g_TcpClient;//Tcp������
std::map<std::string,_PLAYER> g_OnlinePlayers;//������ұ�
std::map<std::string,CPTalkDlg*> g_PTalkDlgs;//˽�ĶԻ���
bool g_bInit;//�Ƿ��ʼ�����

CDC g_Table;//��Ϸ������
CDC g_Title;//��Ϸ��������
CDC g_Room;//��Ϸ��������
CDC g_Pokers;//�˿�����
CDC g_Faces[_FACE_NUM];//���ͷ������
RECT g_Site[_SITE_NUM];//��λ����
_ROOM g_Rooms[_ROOM_NUM];//��������
CPMDispatcher g_PMDispatcher;//Э����Ϣ�ɷ���

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGameHallDlg �Ի���




CGameHallDlg::CGameHallDlg(CWnd* pParent /*=NULL*/)
: CDialog(CGameHallDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	g_bInit = false;
}

void CGameHallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lbOnlinePlayers);
	DDX_Control(pDX, IDC_LIST2, m_lbMessage);
	DDX_Control(pDX, IDC_EDIT1, m_edSendMessage);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_sbRoomV);
	DDX_Control(pDX, IDC_NAME, m_stName);
	DDX_Control(pDX, IDC_SCORE, m_stScore);
	DDX_Control(pDX, IDC_HISTORY, m_stHistory);
	DDX_Control(pDX, IDC_BUTTON2, m_btRead);
}

BEGIN_MESSAGE_MAP(CGameHallDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_VSCROLL()
	//	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON3, &CGameHallDlg::OnBnClickedButton3)
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CGameHallDlg::OnBnClickedButton1)
	ON_LBN_DBLCLK(IDC_LIST1, &CGameHallDlg::OnLbnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGameHallDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CGameHallDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CGameHallDlg ��Ϣ�������

BOOL CGameHallDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	InitPMDispatcher();
	gh_GameHallInit();

	m_GameDlg.Create(MAKEINTRESOURCE(IDD_DIALOG5),this);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CGameHallDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGameHallDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); 
		dc.SetStretchBltMode(STRETCH_HALFTONE);
		dc.SetBkMode(TRANSPARENT);
		int pos = m_sbRoomV.GetScrollPos();

		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				int cx = _LBORDER + j * _ROOM_W;
				int cy = _TBORDER + _ROOM_H * i;
				dc.BitBlt(cx, cy, _ROOM_W, _ROOM_H, &g_Room,0,0,SRCCOPY);
				for(int k = 0; k < 2; ++k)
				{
					if(g_Rooms[j + (i + pos) * _R_VIEW_W].player[k])
					{
						dc.StretchBlt(cx + 5 + k * 90,cy + 30,_FACE_S_W,_FACE_S_H,&g_Faces[g_Rooms[j + (i + pos) * _R_VIEW_W].player[k]->m_Face],0,0,48,48,SRCCOPY);
						CString s = "";
						switch(g_Rooms[j + (i + pos) * _R_VIEW_W].player[k]->m_PlayState)
						{
						case _PS_WAIT:s = "�ȴ���";break;
						case _PS_READY:s = "׼����";break;
						case _PS_PLAYING:s = "��Ϸ��";break;
						}
						dc.TextOutA(cx + k * 90,cy + 15,s.GetString(),s.GetLength());
					}
				}
			}
		}

		if(g_bInit)
		{
			dc.StretchBlt(640,30,_FACE_L_W,_FACE_L_H,&g_Faces[g_Player.m_Face],0,0,48,48,SRCCOPY);
		}

		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CGameHallDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGameHallDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CGameHallDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	gh_GameHallEnd();
	CDialog::OnCancel();
}

void CGameHallDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int pos = pScrollBar->GetScrollPos();
	switch(nSBCode)
	{
	case SB_LINEUP:
		{
			pos -= 1;
			break;
		}
	case SB_LINEDOWN:
		{
			pos += 1;
			break;
		}
	case SB_PAGEUP:
		{
			pos -= 2;
			break;
		}
	case SB_PAGEDOWN:
		{
			pos += 2;
			break;
		}
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		{
			pos = nPos;
			break;
		}
	}
	pScrollBar->SetScrollPos(pos);
	this->InvalidateRect(0);

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CGameHallDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString s;
	m_edSendMessage.GetWindowTextA(s);
	if(s.GetLength() > 255)
		MessageBox("��Ϣ���͹���������С��256���ֽ�");
	else if(!s.IsEmpty())
	{
		CS_PUB_TALK cs_pt;
		strcpy_s(cs_pt.ID,32,g_Player.m_ID.c_str());
		strcpy_s(cs_pt.Message,256,s.GetString());
		g_TcpClient.SendData(&cs_pt,sizeof(cs_pt));
		m_edSendMessage.SetWindowTextA("");
	}

}

void CGameHallDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(g_Player.m_PlayState == _PS_NONE || g_Player.m_PlayState == _PS_WAIT)
	{
		int pos = m_sbRoomV.GetScrollPos();

		for(int i = 0; i < _SITE_NUM; ++i)
		{
			int sitenum = i  + pos * _R_VIEW_W * 2;
			if(PtInRect(&g_Site[i],point))
			{
				int roomnum = sitenum / 2;
				if(g_Rooms[roomnum].m_RoomState == _RS_WAIT)
				{
					if(g_Rooms[roomnum].player[sitenum % 2] == 0)
					{
						CS_ENTER_ROOM cs_er;
						strcpy_s(cs_er.ID,32,g_Player.m_ID.c_str());
						cs_er.RoomNumNew = roomnum;
						cs_er.SiteNumNew = sitenum % 2;

						g_TcpClient.SendData(&cs_er,sizeof(cs_er));
					}
					else
						MessageBox("��ǰ��λ������ҡ�");
				}
				else
					MessageBox("������������Ϸ�У��޷����롣");
				this->InvalidateRect(0);
			}
		}
	}
	else
		MessageBox("������Ϸ�л�׼��״̬���ܱ����λ��");

	CDialog::OnLButtonUp(nFlags, point);
}

void CGameHallDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	gh_GameHallRun();
	CDialog::OnTimer(nIDEvent);
}

void CGameHallDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(g_Player.m_PlayState != _PS_PLAYING)
	{
		CDataChange dcdlg;
		if(dcdlg.DoModal() == IDOK)
		{
			CS_CHANGE_DATA cs_cd;
			strcpy_s(cs_cd.ID,32,g_Player.m_ID.c_str());
			cs_cd.facenum = dcdlg.m_FaceNum;
			strcpy_s(cs_cd.Name,32,dcdlg.m_Name.GetString());
			g_TcpClient.SendData(&cs_cd,sizeof(cs_cd));
		}
	}
	else
		MessageBox("������Ϸ�л�׼��״̬�����޸����ϡ�");
}

void CGameHallDlg::OnLbnDblclkList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int pos = m_lbOnlinePlayers.GetCurSel();
	CString s;
	m_lbOnlinePlayers.GetText(pos,s);

	std::map<std::string,_PLAYER>::iterator n;
	
	for(n = g_OnlinePlayers.begin(); n != g_OnlinePlayers.end(); ++n)
	{
		if(strcmp(n->second.m_Name.c_str(),s.GetString()) == 0)
		{
			std::map<std::string,CPTalkDlg*>::iterator it = g_PTalkDlgs.find(n->second.m_ID);

			if(it == g_PTalkDlgs.end())
			{
				CPTalkDlg* p = new CPTalkDlg;
				p->Create(MAKEINTRESOURCE(IDD_DIALOG3),this);
				g_PTalkDlgs.insert(std::pair<std::string,CPTalkDlg*>(n->second.m_ID,p));
				p->player = &n->second;
				p->ShowWindow(SW_SHOW);
				CString s;
				s.Format("��%s������",p->player->m_Name.c_str());
				p->SetWindowTextA(s.GetString());
			}
			else
			{
				it->second->ShowWindow(SW_SHOW);
			}
			break;
		}
	}
}
//��ʼ���ɷ���Э��
void CGameHallDlg::InitPMDispatcher()
{
	//��½���---------------------------------------------------------
	//��¼�ɹ�:DL_SC_DL_OK
	CPI_LoginSuccess* ls = new CPI_LoginSuccess(this);
	g_PMDispatcher.AddProtocol(DL_SC_DL_OK,ls);

	//����ҵ�¼:DL_SC_NEW_CLIENT
	CPI_NewClientLogin* ncl = new CPI_NewClientLogin(this);
	g_PMDispatcher.AddProtocol(DL_SC_NEW_CLIENT,ncl);

	//�������---------------------------------------------------------
	//�޸����ϳɹ�:HALL_SC_CHANGE_DATA
	CPI_DataChangeSuccess* dcs = new CPI_DataChangeSuccess(this);
	g_PMDispatcher.AddProtocol(HALL_SC_CHANGE_DATA,dcs);

	//�޸�����ʧ��:HALL_SC_CHANGE_DATA_FAIL
	CPI_DataChangeFailed*  dcf = new CPI_DataChangeFailed(this);
	g_PMDispatcher.AddProtocol(HALL_SC_CHANGE_DATA_FAIL,dcf);

	//������������:HALL_SC_PUB_TALK
	CPI_PublicTalk*  pubt = new CPI_PublicTalk(this);
	g_PMDispatcher.AddProtocol(HALL_SC_PUB_TALK,pubt);

	//˽��:HALL_SC_PRI_TALK
	CPI_PrivateTalk*  prit = new CPI_PrivateTalk(this);
	g_PMDispatcher.AddProtocol(HALL_SC_PRI_TALK,prit);

	//�������:HALL_SC_PLAYER_OFFLINE
	CPI_PlayerOffLine*  pof= new CPI_PlayerOffLine(this);
	g_PMDispatcher.AddProtocol(HALL_SC_PLAYER_OFFLINE,pof);

	//��ҽ��뷿��ɹ�:HALL_SC_ENTER_ROOM_SUCCESS
	CPI_EnterRoomSuccess*  ers = new CPI_EnterRoomSuccess(this);
	g_PMDispatcher.AddProtocol(HALL_SC_ENTER_ROOM_SUCCESS,ers);

	//��ҽ��뷿��ʧ��:HALL_SC_ENTER_ROOM_FAIL
	CPI_EnterRoomFail*  erf = new CPI_EnterRoomFail(this);
	g_PMDispatcher.AddProtocol(HALL_SC_ENTER_ROOM_FAIL,erf);

	//���׼���ɹ�:HALL_SC_READ_SUCCESS
	CPI_ReadSuccess*  rs = new CPI_ReadSuccess(this);
	g_PMDispatcher.AddProtocol(HALL_SC_READ_SUCCESS,rs);

	//����˳�����ɹ�:HALL_SC_EXIT_ROOM_SUCCESS
	CPI_ExitRoomSuccess*  pers = new CPI_ExitRoomSuccess(this);
	g_PMDispatcher.AddProtocol(HALL_SC_EXIT_ROOM_SUCCESS,pers);

	//���ȡ��׼���ɹ�:HALL_SC_READY_CANCEL_SUCCESS
	CPI_ReadyCancelSuccess*  rcs = new CPI_ReadyCancelSuccess(this);
	g_PMDispatcher.AddProtocol(HALL_SC_READY_CANCEL_SUCCESS,rcs);

	//��Ϸ���---------------------------------------------------------
	//��ʼ����Ϸ:GAME_SC_NEW_GAME
	CPI_NewGame*  ng = new CPI_NewGame(this);
	g_PMDispatcher.AddProtocol(GAME_SC_NEW_GAME,ng);

	//�����������:GAME_SC_UPDATE_PLAYER_DATA
	CPI_UpdatePlayerData* upd = new CPI_UpdatePlayerData(this);
	g_PMDispatcher.AddProtocol(GAME_SC_UPDATE_PLAYER_DATA,upd);

	//ָ���������ѡ��:GAME_SC_MAKE_CHOICE
	CPI_MakeChoice* mc = new CPI_MakeChoice(this);
	g_PMDispatcher.AddProtocol(GAME_SC_MAKE_CHOICE,mc);

	//��ҽ�������:GAME_SC_TALK_IN_GAME
	CPI_TalkInGame* tig = new CPI_TalkInGame(this);
	g_PMDispatcher.AddProtocol(GAME_SC_TALK_IN_GAME,tig);
	
	//��һ�ȡ���µ���:GAME_SC_GET_NEW
	CPI_GetNew* gn = new CPI_GetNew(this);
	g_PMDispatcher.AddProtocol(GAME_SC_GET_NEW,gn);

	//��һ��21��ʤ��:GAME_SC_WIN_21
	CPI_Win_21* w21 = new CPI_Win_21(this);
	g_PMDispatcher.AddProtocol(GAME_SC_WIN_21,w21);

    //����򱬵�ʧ��:GAME_SC_LOSE_OUT_RANGE
	CPI_LoseOutRange* lor = new CPI_LoseOutRange(this);
	g_PMDispatcher.AddProtocol(GAME_SC_LOSE_OUT_RANGE,lor);

	//������������ʧ��:GAME_SC_LOSE_GIVEUP
	CPI_LoseGiveUp* lgu = new CPI_LoseGiveUp(this);
	g_PMDispatcher.AddProtocol(GAME_SC_LOSE_GIVEUP,lgu);

	//��������ܱ���ʧ��:GAME_SC_LOSE_RUN_AWAY 
	CPI_LoseRunAway* lra = new CPI_LoseRunAway(this);
	g_PMDispatcher.AddProtocol(GAME_SC_LOSE_RUN_AWAY,lra);

	//������ձȵ�����ʤ:GAME_SC_WIN_BIGGER
	CPI_WinBigger* wb = new CPI_WinBigger(this);
	g_PMDispatcher.AddProtocol(GAME_SC_WIN_BIGGER,wb);

	//������ձȵ���ƽ��:GAME_SC_DRAW
	CPI_Draw* d = new CPI_Draw(this);
	g_PMDispatcher.AddProtocol(GAME_SC_DRAW,d);

	//��Ϸ������Ϣ:GAME_SC_GAME_END
	CPI_GameEnd* ge = new CPI_GameEnd(this);
	g_PMDispatcher.AddProtocol(GAME_SC_GAME_END,ge);
}

//��ʼ����Ϸ����
void CGameHallDlg::gh_GameHallInit()
{
	CLogin dlglg;

	if(dlglg.DoModal() == IDOK)
	{
		this->SetTimer(0,20,0);

		CClientDC dc(this);
		HBITMAP hbmp = (HBITMAP)LoadImage(0,"pic\\����\\����.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		g_Table.CreateCompatibleDC(&dc);
		DeleteObject(g_Table.SelectObject(hbmp));
		DeleteObject(hbmp);

		hbmp = (HBITMAP)LoadImage(0,"pic\\����\\����.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		g_Title.CreateCompatibleDC(&dc);
		DeleteObject(g_Title.SelectObject(hbmp));
		DeleteObject(hbmp);

		hbmp = (HBITMAP)LoadImage(0,"pic\\����\\����.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		g_Room.CreateCompatibleDC(&dc);
		DeleteObject(g_Room.SelectObject(hbmp));
		DeleteObject(hbmp);

		hbmp = (HBITMAP)LoadImage(0,"pic\\����\\�˿���.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		g_Pokers.CreateCompatibleDC(&dc);
		DeleteObject(g_Pokers.SelectObject(hbmp));
		DeleteObject(hbmp);

		for(int i = 0; i < _FACE_NUM; i++)
		{
			CString path;
			path.Format("pic\\ͷ��\\ͷ�� (%d).bmp",i);
			hbmp = (HBITMAP)LoadImage(0,path.GetString(),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
			g_Faces[i].CreateCompatibleDC(&dc);
			DeleteObject(g_Faces[i].SelectObject(hbmp));
			DeleteObject(hbmp);
		}

		for(int i = 0; i < _ROOM_NUM; i++)
		{
			g_Rooms[i].player[0] = g_Rooms[i].player[1] = 0;
			g_Rooms[i].m_RoomState = _RS_WAIT;
		}

		m_sbRoomV.SetScrollRange(0,_ROOM_NUM / _R_VIEW_W - _R_VIEW_H);
		m_sbRoomV.SetScrollPos(0);
		m_sbRoomV.MoveWindow(_ROOM_W * 4 + _LBORDER,_TBORDER,15,_ROOM_H * 2,FALSE);

		for(int i = 0; i < _SITE_NUM / 2; ++i)
		{
			int rx = i % _R_VIEW_W;
			int ry = i / _R_VIEW_W;
			int cx = _LBORDER + rx * _ROOM_W;
			int cy = _TBORDER + _ROOM_H * ry;
			g_Site[i * 2].left = cx + 5;
			g_Site[i * 2].top = cy + 30;
			g_Site[i * 2].right = g_Site[i * 2].left + _FACE_S_W;
			g_Site[i * 2].bottom = g_Site[i * 2].top + _FACE_S_H;

			g_Site[i * 2 + 1].left = cx + 96;
			g_Site[i * 2 + 1].top = cy + 30;
			g_Site[i * 2 + 1].right = g_Site[i * 2 + 1].left + _FACE_S_W;
			g_Site[i * 2 + 1].bottom = g_Site[i * 2 + 1].top + _FACE_S_H;
		}

		std::map<std::string,_PLAYER>::iterator it;
		for(it = g_OnlinePlayers.begin(); it != g_OnlinePlayers.end(); ++it)
		{
			if(it->second.m_RoomNum != -1)
				g_Rooms[it->second.m_RoomNum].player[it->second.m_SiteNum] = &it->second;
		}

		for(int i = 0; i < _POKERS_MAX; i++)
		{
			m_Pokers[i].num = i % 13 + 1;
			if(m_Pokers[i].num > 10)
				m_Pokers[i].num = 10;
			m_Pokers[i].tex.x = i % 13 * _POKER_W;
			m_Pokers[i].tex.y = i / 13 * _POKER_H;
		}
	}
	else
	{
		g_TcpClient.Disconnect();
		this->OnCancel();
	}
}
//��������
void CGameHallDlg::gh_GameHallRun()
{
	g_TcpClient.Run();

	_CNET_EVENT ne;
	while (g_TcpClient.GetNetEvent(&ne))
	{
		switch (ne.type)
		{
		case _CNE_DATA:
			{
				g_PMDispatcher.ProtocolRun(ne);
				break;
			}
		default: //���ֶϿ��¼�
			{
				Beep(500, 500);
				KillTimer(0);
				if(MessageBox("������ʧȥ����,���򼴽��رա�","����ʧ��",MB_OK) == IDOK)
				{
					this->OnCancel();
				}
				break;
			}
		}
		g_TcpClient.ReleaseNetEvent(&ne);
	}
}

//��������
void CGameHallDlg::gh_GameHallEnd()
{
	g_Table.DeleteDC();
	g_Title.DeleteDC();
	g_Room.DeleteDC();
	g_Pokers.DeleteDC();
	for(int i = 0; i < _FACE_NUM; ++i)
		g_Faces[i].DeleteDC();

	for(std::map<std::string,CPTalkDlg*>::iterator it = g_PTalkDlgs.begin(); it != g_PTalkDlgs.end(); ++it)
	{
		delete (it->second);
	}
	if(m_GameDlg.showsel)
		m_GameDlg.gs.EndDlg();

	m_GameDlg.ShowWindow(SW_HIDE);
}

//��½�ɹ�
void CGameHallDlg::gh_LoginSuccess(_CNET_EVENT& ne)
{
	LoginSuccess(ne,g_OnlinePlayers);
	std::map<std::string,_PLAYER>::iterator it;
	for(it = g_OnlinePlayers.begin(); it != g_OnlinePlayers.end(); ++it)
	{
		int count = m_lbOnlinePlayers.GetCount();
		m_lbOnlinePlayers.InsertString(count,it->second.m_Name.c_str());
	}
	InvalidateRect(0);
	MessageBox("��½�ɹ�!");
	this->OnOK();
}

//����ҵ���
void CGameHallDlg::gh_NewClientLogin(_CNET_EVENT& ne)
{
	_PLAYER newplayer;

	bool isclient = NewClientLogin(ne,newplayer,g_Player.m_ID);

	if(isclient)
	{
		g_Player = newplayer;
		CString s;
		s.Format("�ǳƣ�%s",g_Player.m_Name.c_str());
		m_stName.SetWindowTextA(s.GetString());
		s.Format("���֣�%d",g_Player.m_Score);
		m_stScore.SetWindowTextA(s.GetString());
		s.Format("ս����ʤ%d ƽ%d ��%d",g_Player.m_Win,g_Player.m_Draw,g_Player.m_Lose);
		m_stHistory.SetWindowTextA(s.GetString());

		g_bInit = true;
		InvalidateRect(0);
	}
	else
	{
		g_OnlinePlayers.insert(std::pair<std::string,_PLAYER>(newplayer.m_ID,newplayer));
		int count = m_lbOnlinePlayers.GetCount();
		m_lbOnlinePlayers.InsertString(count,newplayer.m_Name.c_str());
		InvalidateRect(0);
	}
}

//�޸�������ϳɹ�
void CGameHallDlg::gh_ChangeDataSuccess(_CNET_EVENT& ne)
{
	std::string newname;
	int newface;
	std::string id;

	ChangeDataSuccess(ne,newname,newface,id);

	if(id == g_Player.m_ID)
	{
		g_Player.m_Name = newname;
		g_Player.m_Face = newface;
		CString s;
		s.Format("�ǳƣ�%s",g_Player.m_Name.c_str());
		m_stName.SetWindowTextA(s.GetString());
		MessageBox("�����޸ĳɹ���");
		this->InvalidateRect(0);
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id.c_str());
		if(it != g_OnlinePlayers.end())
		{
			int cur = m_lbOnlinePlayers.FindString(0,it->second.m_Name.c_str());
			if(cur != LB_ERR)
			{
				m_lbOnlinePlayers.DeleteString(cur);
				m_lbOnlinePlayers.InsertString(cur,newname.c_str());
			}

			it->second.m_Name = newname;
			it->second.m_Face = newface;
			this->InvalidateRect(0);
		}
	}
}

//�޸��������ʧ��
void CGameHallDlg::gh_ChangeDataFailed(_CNET_EVENT& ne)
{
	MessageBox("�޸�ʧ�ܣ����ֲ����ظ�!");
}

//��������
void CGameHallDlg::gh_PublicTalk(_CNET_EVENT& ne)
{
	std::string id,message;

	PublicTalk(ne,id,message);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		CString ms;
		ms.Format("%s˵��%s",g_Player.m_Name.c_str(),message.c_str());
		int count  = m_lbMessage.GetCount();
		m_lbMessage.InsertString(count,ms.GetString());
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id.c_str());
		if(it != g_OnlinePlayers.end())
		{
			CString ms;
			ms.Format("%s˵��%s",it->second.m_Name.c_str(),message.c_str());
			int count  = m_lbMessage.GetCount();
			m_lbMessage.InsertString(count,ms.GetString());
		}
	}
}

//˽������
void CGameHallDlg::gh_PrivateTalk(_CNET_EVENT& ne)
{
	std::string id,desid,message;

	PrivateTalk(ne,id,desid,message);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		std::map<std::string,CPTalkDlg*>::iterator it = g_PTalkDlgs.find(desid.c_str());
		if(it != g_PTalkDlgs.end())
		{
			CString ms;
			ms.Format("%s˵��%s",g_Player.m_Name.c_str(),message.c_str());
			it->second->m_lbMessage.AddString(ms.GetString());
		}
	}
	else
	{
		std::map<std::string,CPTalkDlg*>::iterator it = g_PTalkDlgs.find(id.c_str());

		if(it != g_PTalkDlgs.end())
		{
			CString ms;
			ms.Format("%s˵��%s",it->second->player->m_Name.c_str(),message.c_str());
			it->second->m_lbMessage.AddString(ms.GetString());
			it->second->ShowWindow(TRUE);
		}
		else
		{
			std::map<std::string,_PLAYER>::iterator n = g_OnlinePlayers.find(id.c_str());
			if(n != g_OnlinePlayers.end())
			{
				CPTalkDlg* p = new CPTalkDlg;
				p->Create(MAKEINTRESOURCE(IDD_DIALOG3),this);
				g_PTalkDlgs.insert(std::pair<std::string,CPTalkDlg*>(n->second.m_ID,p));
				p->player = &n->second;
				p->ShowWindow(SW_SHOW);
				p->SetWindowTextA(p->player->m_Name.c_str());
				CString ms;
				ms.Format("%s˵��%s",n->second.m_Name.c_str(),message.c_str());
				p->m_lbMessage.AddString(ms.GetString());
			}
		}
	}
}

//�������
void CGameHallDlg::gh_PlayerOffLine(_CNET_EVENT& ne)
{
	std::string id;
	PlayerOffLine(ne,id);

	std::map<std::string,CPTalkDlg*>::iterator it = g_PTalkDlgs.find(id.c_str());

	if(it != g_PTalkDlgs.end())
	{
		it->second->ShowWindow(FALSE);
		delete it->second;
		g_PTalkDlgs.erase(it);
	}

	std::map<std::string,_PLAYER>::iterator n = g_OnlinePlayers.find(id.c_str());
	if(n != g_OnlinePlayers.end())
	{
		if(&n->second == m_Adversary && n->second.m_PlayState == _PS_PLAYING)
		{
			g_Player.m_PlayState = _PS_WAIT;

			if(m_GameDlg.showsel)
				m_GameDlg.gs.EndDlg();

			m_GameDlg.ShowWindow(SW_HIDE);

			MessageBox("����������~��ϲ����ʤ����");
			m_btRead.SetWindowTextA("׼��");
		}
		if(n->second.m_RoomNum != -1)
			g_Rooms[n->second.m_RoomNum].player[n->second.m_SiteNum] = 0;
		int cur = m_lbOnlinePlayers.FindString(-1,n->second.m_Name.c_str());
		if(cur != -1)
			m_lbOnlinePlayers.DeleteString(cur);
	}

	this->InvalidateRect(0);
}

//���뷿��ɹ�
void CGameHallDlg::gh_EnterRoomSuccess(_CNET_EVENT& ne)
{
	std::string id;
	int roomnew,sitenew;
	EnterRoomSuccess(ne,id,roomnew,sitenew);


	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		if(g_Player.m_RoomNum != -1)
		{
			g_Rooms[g_Player.m_RoomNum].player[g_Player.m_SiteNum] = 0;
		}
		g_Rooms[roomnew].player[sitenew] = &g_Player;
		g_Player.m_RoomNum = roomnew;
		g_Player.m_SiteNum = sitenew;
		g_Player.m_PlayState = _PS_WAIT;
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			if(it->second.m_RoomNum != -1)
			{
				g_Rooms[it->second.m_RoomNum].player[it->second.m_SiteNum] = 0;
			}
			g_Rooms[roomnew].player[sitenew] = &it->second;
			it->second.m_RoomNum = roomnew;
			it->second.m_SiteNum = sitenew;
			it->second.m_PlayState = _PS_WAIT;
		}
	}
	this->InvalidateRect(0);
}
//���뷿��ʧ��
void CGameHallDlg::gh_EnterRoomFail(_CNET_EVENT& ne)
{
	MessageBox("���뷿��ʧ�ܡ�");
}

//׼���ɹ�
void CGameHallDlg::gh_ReadSuccess(_CNET_EVENT& ne)
{
	std::string id;
	ReadSuccess(ne,id);
	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		g_Player.m_PlayState = _PS_READY;
		m_btRead.SetWindowTextA("ȡ��׼��");
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			it->second.m_PlayState = _PS_READY;
		}
	}
	this->InvalidateRect(0);
}

//�˳�����ɹ�
void CGameHallDlg::gh_ExitRoomSuccess(_CNET_EVENT& ne)
{
	std::string id;
	ExitRoomSuccess(ne,id);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		g_Player.m_PlayState = _PS_NONE;
		g_Rooms[g_Player.m_RoomNum].player[g_Player.m_SiteNum] = 0;
		g_Player.m_RoomNum = -1;
		g_Player.m_SiteNum = -1;
		m_btRead.SetWindowTextA("׼��");
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			it->second.m_PlayState = _PS_NONE;
			g_Rooms[it->second.m_RoomNum].player[it->second.m_SiteNum] = 0;
			it->second.m_RoomNum = -1;
			it->second.m_SiteNum = -1;
		}
	}
	this->InvalidateRect(0);
}

//ȡ��׼���ɹ�
void CGameHallDlg::gh_ReadyCancelSuccess(_CNET_EVENT& ne)
{
	std::string id;
	ReadyCancelSuccess(ne,id);
	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		g_Player.m_PlayState = _PS_WAIT;
		m_btRead.SetWindowTextA("׼��");
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			it->second.m_PlayState = _PS_WAIT;
		}
	}
	this->InvalidateRect(0);
}

//��ʼ����Ϸ
void CGameHallDlg::gh_NewGame(_CNET_EVENT& ne)
{
	std::string id;
	int num = -1;
	NewGame(ne,id,num);
	std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);

	if(it != g_OnlinePlayers.end())
	{
		//���numΪ-1��ʾ������Ϸ�����޹أ�ֻ��Ϊ�˸����������״̬
		if(num != -1)
		{
			it->second.m_PlayState = _PS_PLAYING;
			g_Player.m_PlayState = _PS_PLAYING;

			m_MyPokers[0] = num;
			m_iPlayerCurPoint = m_Pokers[num].num;
			m_MyPokersNum = 1;

			m_Adversary = &it->second;
			m_AdversaryPokers[0] = -1;
			m_AdversaryPokersNum = 1;

			m_GameDlg.m_lbMessage.ResetContent();
			m_GameDlg.m_edSendMessage.SetWindowTextA("");

			m_GameDlg.m_lbMessage.AddString("[ϵͳ]��Ϸ��ʽ��ʼ��");

			m_GameDlg.ShowWindow(SW_SHOW);

			m_GameDlg.InvalidateRect(0);
		}
		else
		{
			it->second.m_PlayState = _PS_PLAYING;
		}
	}
}
//�������ս��
void CGameHallDlg::gh_UpdatePlayerData(_CNET_EVENT& ne)
{
	std::string id;
	int score,win,lose,draw,playerstate,roomnum,sitenum;
	UpdatePlayerData(ne,id,score,win,lose,draw,playerstate,roomnum,sitenum);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		g_Player.m_Score = score;
		g_Player.m_Win = win;
		g_Player.m_Lose = lose;
		g_Player.m_Draw = draw;

		CString s;
		s.Format("���֣�%d",g_Player.m_Score);
		m_stScore.SetWindowTextA(s.GetString());
		s.Format("ս����ʤ%d ƽ%d ��%d",g_Player.m_Win,g_Player.m_Draw,g_Player.m_Lose);
		m_stHistory.SetWindowTextA(s.GetString());

		if(playerstate == _PS_NONE)
		{
			if(g_Player.m_RoomNum != -1)
			{
				g_Rooms[g_Player.m_RoomNum].player[g_Player.m_SiteNum] = 0;
				g_Player.m_RoomNum = roomnum;
				g_Player.m_SiteNum = sitenum;
			}
			m_btRead.SetWindowTextA("׼��");
		}
		else if(playerstate == _PS_WAIT)
		{
			m_btRead.SetWindowTextA("׼��");
		}
		else if(playerstate == _PS_READY)
		{
			m_btRead.SetWindowTextA("ȡ��׼��");
		}
		else if(playerstate == _PS_PLAYING)
		{

		}

		g_Player.m_PlayState = playerstate;
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			it->second.m_Score = score;
			it->second.m_Win = win;
			it->second.m_Lose = lose;
			it->second.m_Draw = draw;

			if(playerstate == _PS_NONE)
			{
				if(it->second.m_RoomNum != -1)
				{
					g_Rooms[it->second.m_RoomNum].player[it->second.m_SiteNum] = 0;
					it->second.m_RoomNum = roomnum;
					it->second.m_SiteNum = sitenum;
				}
			}
			else if(playerstate == _PS_WAIT)
			{
				
			}
			else if(playerstate == _PS_READY)
			{
				
			}
			else if(playerstate == _PS_PLAYING)
			{

			}

			it->second.m_PlayState = playerstate;
		}
	}
	this->InvalidateRect(0);
}

//ָ���������ѡ��
void CGameHallDlg::gh_MakeChoice(_CNET_EVENT& ne)
{
	std::string id;
	MakeChoice(ne,id);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		m_GameDlg.m_lbMessage.AddString("[ϵͳ]������ѡ��");
		int sel = m_GameDlg.game_MakeChoice();
		if(sel == _GS_CONTINUE)
		{
			CS_CHOICE_CONTINUE cs_cc;
			strcpy_s(cs_cc.ID,32,g_Player.m_ID.c_str());
			g_TcpClient.SendData(&cs_cc,sizeof(cs_cc));
		}
		else if(sel == _GS_STOP)
		{
			CS_CHOICE_STOP cs_cs;
			strcpy_s(cs_cs.ID,32,g_Player.m_ID.c_str());
			g_TcpClient.SendData(&cs_cs,sizeof(cs_cs));
		}
		else if(sel == _GS_GIVEUP)
		{
			CS_CHOICE_GIVEUP cs_cg;
			strcpy_s(cs_cg.ID,32,g_Player.m_ID.c_str());
			g_TcpClient.SendData(&cs_cg,sizeof(cs_cg));
		}
	}
	else
	{
		CString s;
		s.Format("[ϵͳ]�ȴ����%s����ѡ��",m_Adversary->m_Name.c_str());
		m_GameDlg.m_lbMessage.AddString(s.GetString());
	}
}

//��ҽ�������
void CGameHallDlg::gh_TalkInGame(_CNET_EVENT& ne)
{
	std::string id;
	std::string msg;
	TalkInGame(ne,id,msg);

	CString s;

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		s.Format("[���]%s˵��%s",g_Player.m_Name.c_str(),msg.c_str());
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			s.Format("[���]%s˵��%s",it->second.m_Name.c_str(),msg.c_str());
		}
	}

	m_GameDlg.m_lbMessage.AddString(s.GetString());
}

//��һ�ȡ���µ���
void CGameHallDlg::gh_GetNew(_CNET_EVENT& ne)
{
	int newpoker = -1;
	GetNew(ne,newpoker);

	if(newpoker == -1)
	{
		m_AdversaryPokers[m_AdversaryPokersNum] = -1;
		m_AdversaryPokersNum += 1;
		CString s;
		s.Format("[ϵͳ]%s�����һ�����ơ�",m_Adversary->m_Name.c_str());
		m_GameDlg.m_lbMessage.AddString(s.GetString());
	}
	else
	{
		m_MyPokers[m_MyPokersNum] = newpoker;
		m_iPlayerCurPoint += m_Pokers[newpoker].num;
		m_MyPokersNum += 1;
		m_GameDlg.m_lbMessage.AddString("[ϵͳ]������һ�����ơ�");
	}
	m_GameDlg.InvalidateRect(0);
}
//��һ��21��ʤ��
void CGameHallDlg::gh_Win_21(_CNET_EVENT& ne)
{
	std::string id;
	int lastpoker;
	int pokernum;
	int pokers[21];
	CString winner;
	Win_21(ne,id,lastpoker,pokernum,pokers);

	m_AdversaryPokersNum = pokernum;
	for(int i = 0; i < pokernum; ++i)
		m_AdversaryPokers[i] = pokers[i];
	m_GameDlg.InvalidateRect(0);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		m_MyPokers[m_MyPokersNum] = lastpoker;
		m_iPlayerCurPoint += m_Pokers[lastpoker].num;
		m_MyPokersNum += 1;
		winner.Format("[ϵͳ]%s�������Ϸʤ����",g_Player.m_Name.c_str());
		m_GameDlg.MessageBox("��ϲ������21�㣬��Ϸʤ����");
	}
	else
	{
		winner.Format("[ϵͳ]%s�������Ϸʤ����",m_Adversary->m_Name.c_str());
		m_GameDlg.MessageBox("�Է������21�㣬��Ϸʧ�ܣ�");
	}

	m_GameDlg.m_lbMessage.AddString(winner.GetString());
}
//����򱬵�ʧ��
void CGameHallDlg::gh_LoseOutRange(_CNET_EVENT& ne)
{
	std::string id;
	int lastpoker;
	int pokernum;
	int pokers[21];
	CString winner;

	LoseOutRange(ne,id,lastpoker,pokernum,pokers);

	m_AdversaryPokersNum = pokernum;
	for(int i = 0; i < pokernum; ++i)
		m_AdversaryPokers[i] = pokers[i];
	m_GameDlg.InvalidateRect(0);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		m_MyPokers[m_MyPokersNum] = lastpoker;
		m_iPlayerCurPoint += m_Pokers[lastpoker].num;
		m_MyPokersNum += 1;
		m_GameDlg.InvalidateRect(0);
		winner.Format("[ϵͳ]%s�������Ϸʤ����",m_Adversary->m_Name.c_str());
		m_GameDlg.MessageBox("���汬�㣬��Ϸʧ�ܣ�");
	}
	else
	{
		winner.Format("[ϵͳ]%s�������Ϸʤ����",g_Player.m_Name.c_str());
		m_GameDlg.MessageBox("�Է����汬�㣬��Ϸʤ����");
	}

	m_GameDlg.m_lbMessage.AddString(winner.GetString());
}
//������������ʧ��
void CGameHallDlg::gh_LoseGiveUp(_CNET_EVENT& ne)
{
	std::string id;
	LoseGiveUp(ne,id);
	CString lose;

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		lose.Format("[ϵͳ]%s�������Ϸʤ����",m_Adversary->m_Name.c_str());
		m_GameDlg.MessageBox("�������֣���Ϸʧ�ܣ�");
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			lose.Format("[ϵͳ]%s�������Ϸʤ����",g_Player.m_Name.c_str());
			m_GameDlg.MessageBox("�Է��������֣���Ϸʤ����");
		}
	}

	m_GameDlg.m_lbMessage.AddString(lose.GetString());
}

//��������ܱ���ʧ��
void CGameHallDlg::gh_LoseRunAway(_CNET_EVENT& ne)
{
	std::string id;
	LoseRunAway(ne,id);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		if(m_GameDlg.showsel)
			m_GameDlg.gs.EndDlg();
		m_GameDlg.ShowWindow(SW_HIDE);

		MessageBox("��ô�������أ���ȥ�һس���ȥ��");
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			if(m_GameDlg.showsel)
				m_GameDlg.gs.EndDlg();
			m_GameDlg.ShowWindow(SW_HIDE);

			MessageBox("����������~��ϲ����ʤ����");
		}
	}
}

//������ձȵ�����ʤ
void CGameHallDlg::gh_WinBigger(_CNET_EVENT& ne)
{
	std::string id;
	int pokernum;
	int pokers[21];
	CString winner;

	WinBigger(ne,id,pokernum,pokers);

	m_AdversaryPokersNum = pokernum;
	for(int i = 0; i < pokernum; ++i)
		m_AdversaryPokers[i] = pokers[i];
	m_GameDlg.InvalidateRect(0);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		winner.Format("[ϵͳ]%s�������Ϸʤ����",g_Player.m_Name.c_str());
		m_GameDlg.MessageBox("�ҷ��������ڶԷ�����Ϸʤ����");
	}
	else
	{
		winner.Format("[ϵͳ]%s�������Ϸʤ����",m_Adversary->m_Name.c_str());
		m_GameDlg.MessageBox("�ҷ�����С�ڶԷ�����Ϸʧ�ܣ�");
	}
	m_GameDlg.m_lbMessage.AddString(winner.GetString());
}
//������ձȵ���ƽ��
void CGameHallDlg::gh_Draw(_CNET_EVENT& ne)
{
	int pokernum;
	int pokers[21];

	Draw(ne,pokernum,pokers);

	m_AdversaryPokersNum = pokernum;
	for(int i = 0; i < pokernum; ++i)
		m_AdversaryPokers[i] = pokers[i];

	m_GameDlg.m_lbMessage.AddString("[ϵͳ]��Ϸƽ��!");
	m_GameDlg.InvalidateRect(0);

	m_GameDlg.MessageBox("��Ϸƽ�֣�");
}

//�յ���Ϸ������Ϣ
void CGameHallDlg::gh_GameEnd(_CNET_EVENT& ne)
{
}

void CGameHallDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(g_Player.m_PlayState == _PS_WAIT)
	{
		CS_READ cs_r;
		strcpy_s(cs_r.ID,32,g_Player.m_ID.c_str());
		g_TcpClient.SendData(&cs_r,sizeof(cs_r));
		m_GameDlg.ShowWindow(SW_HIDE);
	}
	else if(g_Player.m_PlayState == _PS_READY)
	{
		CS_READY_CANCEL cs_rc;
		strcpy_s(cs_rc.ID,32,g_Player.m_ID.c_str());
		g_TcpClient.SendData(&cs_rc,sizeof(cs_rc));
	}
}

void CGameHallDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(g_Player.m_PlayState == _PS_READY || g_Player.m_PlayState == _PS_PLAYING)
	{
		MessageBox("��ǰ״̬�����˳����䡣");
	}
	else if(g_Player.m_RoomNum != -1)
	{
		CS_EXIT_ROOM cs_er;
		strcpy_s(cs_er.ID,32,g_Player.m_ID.c_str());
		g_TcpClient.SendData(&cs_er,sizeof(cs_er));
	}
}



