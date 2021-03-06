// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "ListCtrl/ListCtrl.h"

class CInputDlg;
class CAssocDlg;
class CPlayerDlg;
class CExtraDlg;
class COtherDlg;
class CGuiDlg;


class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler, public CWinDataExchange<CMainDlg>
{
public:
	CProgressBarCtrl	m_progress_apply;
	enum { IDD = IDD_MAINDLG };
	int			m_pos;
	int			m_appLang;
	int			m_OpenType;
	bool		isVista;
	UINT		s_uTBBC;
	ITaskbarList3 *g_pTaskbarList;

	CListCtrl	m_tablist;
	CImageList	m_Images;

	CInputDlg	*m_InputDlg;
	CAssocDlg	*m_AssocDlg;
	CPlayerDlg	*m_PlayerDlg;
	CExtraDlg	*m_ExtraDlg;
	COtherDlg	*m_OtherDlg;
	CGuiDlg		*m_GuiDlg;

	CString		m_program_dir;

	void SaveConfig();

	BEGIN_DDX_MAP(CMainDlg)
		DDX_CONTROL_HANDLE(IDC_PROGRESS_APPLEY, m_progress_apply)
	END_DDX_MAP();
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	CMainDlg();

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDC_APPLY, OnApply)
		COMMAND_ID_HANDLER(ID_MPLAYER_INI, OnMplayerIni)
		COMMAND_ID_HANDLER(ID_INPUT_INI, OnInputIni)
		COMMAND_ID_HANDLER(ID_KK_INI, OnKkIni)
		COMMAND_ID_HANDLER(ID_LOG_TXT, OnLogTxt)
		COMMAND_ID_HANDLER(IDC_GOTOHOME, OnGotohome)
		COMMAND_ID_HANDLER(IDC_SHOW_HELP, OnShowHelp)
		COMMAND_ID_HANDLER(IDC_SHOWLOG, OnShowlog)
		COMMAND_ID_HANDLER(IDC_SHOWFAQ, OnShowfaq)
		COMMAND_ID_HANDLER(ID_ABOUT, OnAbout)
		COMMAND_ID_HANDLER(ID_UPDATE, OnBnClickedUpdate)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		NOTIFY_HANDLER_EX(IDC_LIST_TAB, LCN_SELECTED, OnTabSelected)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTabSelected( LPNMHDR lpNMHDR );

	void CloseDialog(int nVal);
	LRESULT OnApply(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnMplayerIni(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnInputIni(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnKkIni(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnLogTxt(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnGotohome(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnShowHelp(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnShowlog(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnShowfaq(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedUpdate(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};
