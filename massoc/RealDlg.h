#pragma once


// CRealDlg �Ի���

class CRealDlg : public CDialog
{
	DECLARE_DYNAMIC(CRealDlg)

public:
	CRealDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRealDlg();

	CWinThread *CheckRealThread;
	CString m_cmdline;
	BOOL m_reg_ok;
	BOOL CheckRealOnline();
	BOOL RegRealOnline();
	BOOL DRegRealOnline();

// �Ի�������
	enum { IDD = IDD_REAL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
