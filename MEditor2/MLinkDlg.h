#pragma once


// CMLinkDlg �Ի���

class CMLinkDlg : public CDialog
{
	DECLARE_DYNAMIC(CMLinkDlg)

public:
	CMLinkDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMLinkDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_LINK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_mplayer_desk;
	BOOL m_meditor_desk;
	BOOL m_mplayer_start;
	BOOL m_meditor_start;
	BOOL m_tools_start;
	BOOL m_flash_start;
	BOOL m_dshow_start;
	BOOL m_mpc_start;
};
