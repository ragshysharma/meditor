#pragma once


// CRealDlg �Ի���

class CRealDlg : public CDialog
{
	DECLARE_DYNAMIC(CRealDlg)

public:
	CRealDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRealDlg();

// �Ի�������
	enum { IDD = IDD_REAL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNotifyReg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNotifyDReg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNotifyCheck(WPARAM wParam, LPARAM lParam);
};
