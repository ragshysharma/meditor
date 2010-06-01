#pragma once

#include "afxwin.h"

// CMAssosPage �Ի���

class CMAssosPage : public CDialog
{
	DECLARE_DYNAMIC(CMAssosPage)

public:
	CMAssosPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMAssosPage();

// �Ի�������
	enum { IDD = IDD_ASSOS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	BOOL	m_is_vista;
	CString m_assoc_exe;
	CString m_player_exe;
	CString m_program_dir;

	bool AssosTypeDef(CString type, CString info, CString icons, bool isplaylist = false);

	DECLARE_MESSAGE_MAP()
public:
	//AssList m_olist;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAssos();
	afx_msg void OnBnClickedAssosDef();
	BOOL m_update;
};
