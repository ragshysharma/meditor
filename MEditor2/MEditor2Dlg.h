// MEditor2Dlg.h : ͷ�ļ�
//

#pragma once
#include "TabSheet.h"
#include "MPlayerPage.h"
#include "MVideoPage.h"
#include "MAudioPage.h"
#include "MDecodePage.h"
#include "MOtherPage.h"
#include "MResumePage.h"
#include "MInputPage.h"
#include "MAssosPage.h"
#include "MConfig.h"


enum Views
{
	Player,
	Video,
	Audio,
	Decode,
	Resume,
	Other,
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
	CMDecodePage m_decode;
	CMOtherPage m_other;
	CMResumePage m_resume;
	CMInputPage m_Input;
	CMAssosPage m_assos;
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
};
