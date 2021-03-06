#if !defined(AFX_MDECODEPAGE_H__3F171818_60EC_45EF_9301_BBC9F39CF3DF__INCLUDED_)
#define AFX_MDECODEPAGE_H__3F171818_60EC_45EF_9301_BBC9F39CF3DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MDecodePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMDecodePage dialog

class CMConfig;
#ifndef XLISTCTRLLIB_STATIC
#define XLISTCTRLLIB_STATIC
#endif
#include "XListCtrl.h"
#include "afxwin.h"
#include "AdvCombo\AdvComboBox.h"

enum codecs_ini
{
	inner,
	external,
	coreavc,
	lavcuvid,
};

enum Avcodec
{
	skiploopfilter,
	skipframe,
//	fast,
//	gray,
//	sb,
//	st,
	xy,
	lowres,
	threads
};

class CMDecodePage : public CDialog
{
// Construction
public:
	CMDecodePage(CWnd* pParent = NULL);   // standard constructor
	CMConfig *m_cfg;
	void SaveConfig();
	void SetNormal();
	void SetHigh();
	void SetLower();
	void RegCoreCodec();


// Dialog Data
	//{{AFX_DATA(CMDecodePage)
	enum { IDD = IDD_DECODE_DIALOG };
	//}}AFX_DATA
protected:
	CAdvComboBoxMod m_codecs;
	CXListCtrl m_vlist;
	CXListCtrl m_alist;
	CXListCtrl m_avlist;
	CStringArray m_vdecode;
	CStringArray m_adecode;
	CStringArray m_skip;
	CStringArray m_threads;
	CString m_str_skip1;
	CString m_str_skip2;
	CString m_str_skip3;
	CString m_str_skip4;
	CString m_str_skip5;
	static int m_nColWidths[];
	static int m_nColWidths_AV[];
	void FillListCtrl(CXListCtrl * pList);
	void InitListCtrl(CXListCtrl * pList);
	void FillListCtrlAV(CXListCtrl * pList);
	void InitListCtrlAV(CXListCtrl * pList);
	CString m_program_dir;
	int m_last_extract;

	CString use1;
	CString pr1;
	CString use;
	CString name;
	CString op;
	CString inf;

	CStringArray m_str_avlist;
	CStringArray m_str_codecs;

	BOOL m_auto_threads;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDecodePage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void InitFromConfig();
	// Generated message map functions
	//{{AFX_MSG(CMDecodePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDel();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonDown();
	afx_msg void OnButtonAdd2();
	afx_msg void OnButtonDel2();
	afx_msg void OnButtonUp2();
	afx_msg void OnButtonDown2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCoreavc();
	BOOL m_dshow;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDECODEPAGE_H__3F171818_60EC_45EF_9301_BBC9F39CF3DF__INCLUDED_)
