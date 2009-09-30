// MAssosPage.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "meditor2.h"
#include "MAssosPage.h"


// CMAssosPage �Ի���

IMPLEMENT_DYNAMIC(CMAssosPage, CDialog)

CMAssosPage::CMAssosPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMAssosPage::IDD, pParent)
{
	CString m_program_dir;
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	m_program_dir.Format(_T("%s"),szFilePath);

	m_assoc_exe = m_program_dir + _T("\\codecs\\massoc.exe");

	if(!IsFileExist(m_assoc_exe))
		m_assoc_exe = m_program_dir + _T("\\tools\\massoc.exe");

	if(!IsFileExist(m_assoc_exe))
		m_assoc_exe = m_program_dir + _T("\\massoc.exe");

}

CMAssosPage::~CMAssosPage()
{
}

void CMAssosPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMAssosPage, CDialog)
	ON_BN_CLICKED(IDC_ASSOS, OnBnClickedAssos)
	
END_MESSAGE_MAP()


// CMAssosPage ��Ϣ�������

BOOL CMAssosPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMAssosPage::OnBnClickedAssos()
{
	ShellExecute(0, _T("open"), m_assoc_exe , NULL, NULL, SW_SHOW);
}
