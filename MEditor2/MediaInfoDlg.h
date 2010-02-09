#pragma once
#include "explorer_html.h"


// CMediaInfoDlg �Ի���

class CMediaInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CMediaInfoDlg)

public:
	CMediaInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMediaInfoDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_MEDIAINFO };

protected:
	HICON m_hIcon;
	CString URL;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CExplorer_html m_html;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	void DownloadCompleteExplorerHtml();
	void NavigateComplete2ExplorerHtml(LPDISPATCH pDisp, VARIANT* URL);
};
