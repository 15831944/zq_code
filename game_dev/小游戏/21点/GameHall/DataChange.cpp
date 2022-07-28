// DataChange.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameHall.h"
#include "DataChange.h"

#define _VIEW_W 6
#define _VIEW_H 4
#define _LBORDER 30
#define _TBORDER 140
#define _FACE_W 48
#define _FACE_H 48
// CDataChange �Ի���

IMPLEMENT_DYNAMIC(CDataChange, CDialog)

CDataChange::CDataChange(CWnd* pParent /*=NULL*/)
	: CDialog(CDataChange::IDD, pParent)
{

}

CDataChange::~CDataChange()
{
}

void CDataChange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_NewName);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_FaceLB);
}


BEGIN_MESSAGE_MAP(CDataChange, CDialog)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDOK, &CDataChange::OnBnClickedOk)
END_MESSAGE_MAP()


// CDataChange ��Ϣ�������

BOOL CDataChange::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	p = (CGameHallDlg*)this->GetParent();

	m_NewName.SetWindowTextA(g_Player.m_Name.c_str());

	m_FaceNum = g_Player.m_Face;

	m_FaceLB.SetScrollRange(0,(_FACE_NUM + 5) / _VIEW_W - _VIEW_H,FALSE);
	m_FaceLB.SetScrollPos(0,FALSE);

	m_FaceLB.MoveWindow(_LBORDER + _FACE_W * _VIEW_W,_TBORDER,15,_VIEW_H * _FACE_H,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDataChange::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(_LBORDER + 80,60,_FACE_W,_FACE_H,&g_Faces[m_FaceNum],0,0,SRCCOPY);
	int pos = m_FaceLB.GetScrollPos();

	for(int i = 0; i < _VIEW_W * _VIEW_H; ++i)
	{
		int cx = i % _VIEW_W;
		int cy = i / _VIEW_W;
		int cur = cx + (cy + pos) * _VIEW_W;
		if(cur < _FACE_NUM)
		{
			dc.BitBlt(_LBORDER + cx * _FACE_W,_TBORDER + cy * _FACE_H,_FACE_W,_FACE_H,&g_Faces[cur],0,0,SRCCOPY);
		}
	}
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}

void CDataChange::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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

void CDataChange::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int pos = m_FaceLB.GetScrollPos();

	static RECT r = 
	{
		_LBORDER,
		_TBORDER,
		r.left + _VIEW_W * _FACE_W,
		r.top + _VIEW_H * _FACE_H
	};

	if(PtInRect(&r,point))
	{
		int cx = point.x - r.left;
		int cy = point.y - r.top;
		cx /= _FACE_W;
		cy /= _FACE_H;
		cy += pos;
		int n = cx + _VIEW_W * cy;
		if(n >= 0 && n < _FACE_NUM)
		{
			m_FaceNum = n;
			this->InvalidateRect(0);
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CDataChange::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString s;
	m_NewName.GetWindowTextA(s);
	if(s.GetLength() <= 0 || s.GetLength() > 30)
		MessageBox("�ǳƳ���Ҫ����0С��30���ֽ�");
	else
	{
		m_Name = s;
		OnOK();
	}
}
