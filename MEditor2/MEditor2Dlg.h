// MEditor2Dlg.h : ͷ�ļ�
//

#pragma once
#include "TabSheet.h"
#include "MPlayerPage.h"
#include "MVideoPage.h"
#include "MAudioPage.h"
#include "MSubPage.h"
#include "MDecodePage.h"
#include "MOtherPage.h"
#include "MResumePage.h"
#include "MProfilePage.h"
#include "MInputPage.h"
#include "MAssosPage.h"
#include "MShowInfoDlg.h"
#include "MConfig.h"

enum Views
{
	Player,
	Video,
	Audio,
	Subtitle,
	Decode,
	Resume,
	Other,
	Profile,
	Input,
	Assos
};

// CMEditor2Dlg �Ի���
class CMEditor2Dlg : public CDialog
{
// ����
public:
	CMEditor2Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	int m_OpenType;

// �Ի�������
	enum { IDD = IDD_MEDITOR2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HANDLE gUniqueEvent;
	HICON m_hIcon;
	CTabSheet m_TabSheet;
	CMPlayerPage m_player;
	CMVideoPage m_video;
	CMAudioPage m_audio;
	CMSubPage m_subtitle;
	CMDecodePage m_decode;
	CMOtherPage m_other;
	CMProfilePage m_profile;
	CMResumePage m_resume;
	CMInputPage m_Input;
	CMAssosPage m_assos;
	CMShowInfoDlg infoDlg;
	CMConfig m_config;
	CString m_program_dir;
	int m_pos;
	CProgressCtrl m_progress_apply;
	// ���ɵ���Ϣӳ�亯��
	bool SaveAll();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
	void ShowInfo(int type);

public:
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedHelp();
	virtual BOOL DestroyWindow();
	afx_msg void OnNormal();
	afx_msg void OnHigh();
	afx_msg void OnLower();
	afx_msg void OnMplayerIni();
	afx_msg void OnInputIni();
	afx_msg void OnKkIni();
	afx_msg void OnLogTxt();
protected:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnAbout();
	afx_msg void OnGotohome();
	afx_msg void OnShowlog();
	afx_msg void OnShowHelp();
	afx_msg void OnShowfaq();
	afx_msg void OnResetinfo();
};
