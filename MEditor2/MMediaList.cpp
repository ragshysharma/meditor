// MMediaList.cpp : implementation file
//

#include "stdafx.h"
#include "meditor2.h"
#include "MMediaList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMMediaList dialog


CMMediaList::CMMediaList(CWnd* pParent /*=NULL*/)
	: CDialog(CMMediaList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMMediaList)
	//}}AFX_DATA_INIT
	m_pParent = pParent;
}


void CMMediaList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMediaList)
	DDX_Control(pDX, IDC_PLAYLIST, m_Dlist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMMediaList, CDialog)
	//{{AFX_MSG_MAP(CMMediaList)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, OnButtonClean)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_LBN_DBLCLK(IDC_PLAYLIST, OnDblclkPlaylist)
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMediaList message handlers

void CMMediaList::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TCHAR szFileName[MAX_PATH];
	int iFileNumber;
	// �õ���ק�����е��ļ�����
	iFileNumber = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	m_wmplist = m_wmp->GetCurrentPlaylist();
	m_wmplist.SetName(_T("MMediaPlayer �����б�"));
	CWMPMedia m_media;
	for (int i = 0; i < iFileNumber; i++) 
	{
		// �õ�ÿ���ļ���
		DragQueryFile(hDropInfo, i, szFileName, MAX_PATH);
		// ���ļ�����ӵ�list��
		m_Dlist.AddString(szFileName);
		m_media = m_wmp->newMedia(szFileName);
		m_wmplist.appendItem(m_media);
	}
	CDialog::OnDropFiles(hDropInfo);
}

void CMMediaList::ReFlashList()
{
	m_wmplist = m_wmp->GetCurrentPlaylist();
	CWMPMedia m_media;
	for(int i = 0; i < m_wmplist.GetCount(); i++)
	{
		m_media = m_wmplist.GetItem(i);
		m_Dlist.AddString(m_media.GetSourceURL());
	}
}

void CMMediaList::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	
	TCHAR szFilePath[MAX_PATH + 1];
	::GetCurrentDirectory(MAX_PATH,szFilePath);
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT
		,_T("������Ƶ��ʽ|*.avi;*.mkv;*.ogm;*.mp4;*.m4v;*.m4p;*.m4b;*.flv;*.vp6;\
*.divx;*.vg2;*.dat;*.mpg;*.mpeg;*.tp;*.ts;*.tpr;*.pva;*.pps;*.mpe;*.vob;*.rm;*.rmvb;\
*.wmv;*.asf;*.wmp;*.wm;*.mov;*.qt;*.3gp;*.3gpp;*.3g2;*.3gp2\
|������Ƶ��ʽ|*.mp3;*.mp2;*.m4a;*.aac;*.mpc;*.wma;*.ogg;\
*.arm;*.mka;*.flac;*.ac3;*.dts;*.wav;*.ra;*.aif|�����ļ�(*.*)|*.*||"));

	dlg.m_ofn.lpstrTitle=_T("��ý���ļ�");
	if(dlg.DoModal()==IDOK)
	{
		CString szFileName = dlg.GetPathName();

		m_Dlist.AddString(szFileName);
		m_wmplist = m_wmp->GetCurrentPlaylist();
		CWMPMedia m_media;
		m_media = m_wmp->newMedia(szFileName);
		m_wmplist.appendItem(m_media);
		m_wmplist.SetName(_T("MMediaPlayer �����б�"));
	}
	dlg.DestroyWindow();
	::SetCurrentDirectory(szFilePath);
}

void CMMediaList::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	int cr = m_Dlist.GetCurSel();
	if(cr < 0)
		return;
	m_Dlist.DeleteString(cr);
	if(cr == m_Dlist.GetCount())
		m_Dlist.SetCurSel(cr -1);
	else
		m_Dlist.SetCurSel(cr);

	m_wmplist = m_wmp->GetCurrentPlaylist();
	CWMPMedia m_media = m_wmplist.GetItem(cr);
	m_wmplist.removeItem(m_media);
}

void CMMediaList::OnButtonClean() 
{
	// TODO: Add your control notification handler code here
	for(int j = m_Dlist.GetCount() - 1; j >= 0 ; j--)
	{
		m_Dlist.DeleteString(j);
	}
	for(int i = m_Dlist.GetCount() - 1; i >= 0 ; i--)
	{
		m_Dlist.DeleteString(i);
	}
	m_wmplist = m_wmp->GetCurrentPlaylist();
	m_wmplist.clear();
}

void CMMediaList::OnButtonUp() 
{
	// TODO: Add your control notification handler code here
	
	int cr = m_Dlist.GetCurSel();
	if(cr > 0)
	{
		CString value;
		m_Dlist.GetText(cr,value);
		m_Dlist.DeleteString(cr);
		m_Dlist.InsertString(cr - 1,value);
		m_Dlist.SetCurSel(cr - 1);
		
		m_wmplist = m_wmp->GetCurrentPlaylist();
		m_wmplist.moveItem(cr ,cr - 1);
	}
}

void CMMediaList::OnButtonDown() 
{
	// TODO: Add your control notification handler code here
	
	int cr = m_Dlist.GetCurSel();
	if(cr < m_Dlist.GetCount() - 1)
	{
		CString value;
		m_Dlist.GetText(cr,value);
		m_Dlist.DeleteString(cr);
		m_Dlist.InsertString(cr + 1,value);
		m_Dlist.SetCurSel(cr + 1);

		m_wmplist = m_wmp->GetCurrentPlaylist();
		m_wmplist.moveItem(cr ,cr + 1);
	}
}

void CMMediaList::OnDblclkPlaylist() 
{
	// TODO: Add your control notification handler code here
	int cr = m_Dlist.GetCurSel();
	if(cr >= 0)
	{
		m_wmplist = m_wmp->GetCurrentPlaylist();
		CWMPMedia m_media = m_wmplist.GetItem(cr);
		CWMPControls m_wmpctrl = m_wmp->GetControls();
		m_wmpctrl.playItem(m_media);
	}
}

BOOL CMMediaList::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message)
	{
	case   WM_KEYDOWN:
		switch(pMsg->wParam)
		{
		case   VK_DELETE:
			OnButtonDel();
			break;
		}
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
