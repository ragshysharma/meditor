// ProgressDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "massoc.h"
#include "ProgressDlg.h"


// CProgressDlg �Ի���

IMPLEMENT_DYNAMIC(CProgressDlg, CDialog)

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{

}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CProgressDlg ��Ϣ�������

BOOL CProgressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_progress.SetRange(0,100);
	m_progress.SetPos(0);
	SetTimer(0, 100, 0);

	::SetWindowPos(this->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString percent;
	int p = m_progress.GetPos();
	percent.Format(_T("%d%%"), p);
	SetWindowText(percent);
	if(p >= 100) {
		KillTimer(0);
		OnOK();
	}
	CDialog::OnTimer(nIDEvent);
}
