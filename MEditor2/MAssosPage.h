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

	CString m_assoc_exe;

	DECLARE_MESSAGE_MAP()
public:
	//AssList m_olist;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAssos();
};
