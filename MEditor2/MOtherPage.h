#include "afxwin.h"
#if !defined(AFX_MOTHERPAGE_H__B88A776B_CD94_4BDD_BCB9_E02FD100162E__INCLUDED_)
#define AFX_MOTHERPAGE_H__B88A776B_CD94_4BDD_BCB9_E02FD100162E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MOtherPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMOtherPage dialog

class CMConfig;

class CMOtherPage : public CDialog
{
// Construction
public:
	CMOtherPage(CWnd* pParent = NULL);   // standard constructor
	CMConfig *m_cfg;
	void SaveConfig();
	void SetNormal();
	void SetHigh();
	void SetLower();
// Dialog Data
	//{{AFX_DATA(CMOtherPage)
	enum { IDD = IDD_OTHER_DIALOG };
	CEdit	m_other_c;
	CString	m_other;
	BOOL	m_last_page;
	CString	m_video;
	CString	m_audio;
	BOOL	m_one;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMOtherPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_program_dir;
	CString m_program;

	// Generated message map functions
	//{{AFX_MSG(CMOtherPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAudio();
	afx_msg void OnButtonClean();
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonVideo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CButton m_realreg;
	CButton m_unrealreg;
protected:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	BOOL m_mpc;
	BOOL m_screensaver;
	BOOL m_info_html;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOTHERPAGE_H__B88A776B_CD94_4BDD_BCB9_E02FD100162E__INCLUDED_)

