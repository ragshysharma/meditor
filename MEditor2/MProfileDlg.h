#pragma once
#include "afxwin.h"


// CMProfileDlg �Ի���

class CMProfileDlg : public CDialog
{
	DECLARE_DYNAMIC(CMProfileDlg)

public:
	CMProfileDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMProfileDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_PROFILE_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_plist;
	CString m_profile_add;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
