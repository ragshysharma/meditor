// MOtherPage.cpp : implementation file
//

#include "stdafx.h"
#include "meditor2.h"
#include "MOtherPage.h"
#include "MConfig.h"
#include "reg.h"
#include "MLinkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMOtherPage dialog

CMOtherPage::CMOtherPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMOtherPage::IDD, pParent)
	, m_mpc(FALSE)
{
	//{{AFX_DATA_INIT(CMOtherPage)
	m_other = _T("");
	m_last_page = FALSE;
	m_video = _T("");
	m_audio = _T("");
	m_one = FALSE;
	CheckRealThread = NULL;
	//}}AFX_DATA_INIT
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	m_program_dir.Format(_T("%s"),szFilePath);
}


void CMOtherPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMOtherPage)
	DDX_Control(pDX, IDC_RADIO_MPLAYER, m_mplayer);
	DDX_Control(pDX, IDC_RADIO_MEDITOR, m_meditor);
	DDX_Control(pDX, IDC_EDIT_OTHER, m_other_c);
	DDX_Text(pDX, IDC_EDIT_OTHER, m_other);
	DDX_Check(pDX, IDC_CHECK_PAGE, m_last_page);
	DDX_Text(pDX, IDC_EDIT_VIDEO, m_video);
	DDX_Text(pDX, IDC_EDIT_AUDIO, m_audio);
	DDX_Check(pDX, IDC_CHECK_ONE, m_one);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON_ONLINE, m_realreg);
	DDX_Control(pDX, IDC_BUTTON_DONLINE, m_unrealreg);
	DDX_Control(pDX, IDC_CHECK_MPC, m_mpc_c);
	DDX_Check(pDX, IDC_CHECK_MPC, m_mpc);
}


BEGIN_MESSAGE_MAP(CMOtherPage, CDialog)
	//{{AFX_MSG_MAP(CMOtherPage)
	ON_BN_CLICKED(IDC_BUTTON_AUDIO, OnButtonAudio)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, OnButtonClean)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO, OnButtonVideo)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, OnButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_MEDIA, OnButtonMedia)
	ON_BN_CLICKED(IDC_BUTTON_ONLINE, OnButtonOnline)
	ON_BN_CLICKED(IDC_BUTTON_DONLINE, OnButtonDonline)
	ON_BN_CLICKED(IDC_RADIO_MPLAYER, OnRadioMplayer)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_RADIO_MEDITOR, OnRadioMeditor)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_LINK, &CMOtherPage::OnBnClickedButtonLink)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMOtherPage message handlers

BOOL CMOtherPage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_mplayer.SetCheck(1);
	if(m_cfg)
	{
		m_other = m_cfg->GetValue_Other();
		int value_i;
		bool value_b;
		m_cfg->GetValue_Integer(_T("use_windowblinds"),value_i,true);
		m_cfg->GetValue_Integer(_T("using_aero"),value_i,true);
		if(m_cfg->GetValue_Integer(_T("meditor_last_page"),value_i,true))
		{
			if(value_i > -1 && value_i < 7)
				m_last_page = TRUE;
			else
				m_last_page = FALSE;
		}
		if(m_cfg->GetValue_Boolean(_T("meditor_one_editor"),value_b,true))
		{
			if(value_b)
				m_one = TRUE;
			else
				m_one = FALSE;
		}
	}
	if(IsFileExist(m_program_dir + _T("codecs\\Real\\mloader.ini")))
	{
		m_meditor.SetCheck(1);
		m_mplayer.SetCheck(0);
	}
	m_mpc_exe = m_program_dir + _T("tools\\mplayerc.exe");
	if( IsFileExist(m_mpc_exe))
	{
		m_mpc_c.EnableWindow(TRUE);
		m_mpc = TRUE;
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMOtherPage::SetNormal()
{
	m_other = _T("");
}
void CMOtherPage::SetHigh()
{
	SetNormal();
}
void CMOtherPage::SetLower()
{
	SetNormal();
}

void CMOtherPage::SaveConfig()
{
	if(m_mplayer.GetCheck() == 1)
		DeleteFile(m_program_dir + _T("codecs\\Real\\mloader.ini"));
	else
	{
		TCHAR szProgramPath[MAX_PATH + 1];
		GetModuleFileName(NULL, szProgramPath, MAX_PATH);
		CString cmd;
		if(m_mpc)
			cmd = m_mpc_exe;
		else
			cmd.Format(_T("%s --Open MediaPlayer"), szProgramPath);
		WritePrivateProfileString(_T("Command"), _T("Program_Path"),  cmd , m_program_dir + _T("codecs\\Real\\mloader.ini"));
	}

	if(!m_cfg)
		return;
	UpdateData(TRUE);

	if(m_last_page)
		m_cfg->SetValue(_T("meditor_last_page"),_T("1"),true,ex_meditor);
	else	
		m_cfg->SetValue(_T("meditor_last_page"),_T("0"),true,ex_meditor);

	if(m_one)
		m_cfg->SetValue(_T("meditor_one_editor"),_T("1"),true,ex_meditor);
	else	
		m_cfg->RemoveValue(_T("meditor_one_editor"),true);
	
	m_other.TrimRight(_T("\r\n"));
	if(m_other.GetLength() > 1)
	{
		m_other += _T("\r\n");
		m_cfg->SetValue_Other(m_other);
	}
}

BOOL CMOtherPage::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CMOtherPage::OnButtonAudio() 
{
	// TODO: Add your control notification handler code here
	
	TCHAR szFilePath[MAX_PATH + 1];
	::GetCurrentDirectory(MAX_PATH,szFilePath);
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT
		,_T("������Ƶ��ʽ|*.mp3;*.mp2;*.m4a;*.aac;*.mpc;*.wma;*.ogg;\
*.arm;*.mka;*.flac;*.ac3;*.dts;*.wav;*.ra;*.aif|�����ļ�(*.*)|*.*||"));

	dlg.m_ofn.lpstrTitle=_T("����Ƶ�ļ�");
    if(dlg.DoModal()==IDOK)
	{
		m_audio = dlg.GetPathName();
	}
	dlg.DestroyWindow();
	::SetCurrentDirectory(szFilePath);
	UpdateData(FALSE);
}

void CMOtherPage::OnButtonClean() 
{
	// TODO: Add your control notification handler code here
	m_video = _T("");
	m_audio = _T("");
	UpdateData(FALSE);
}

void CMOtherPage::OnButtonPlay() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	if(m_video == _T("") || m_audio == _T(""))
	{
		MessageBox(_T("��Ƶ����Ƶ�ļ�������Ϊ��!"));
		return;
	}
	if(!IsFileExist(m_program_dir + _T("mplayer.exe")))
	{
		MessageBox(_T("�� mplayer.exe ������ͬĿ¼�в���ʹ�ô˹���!"));
		return;
	}
	CString mpcmd;
	mpcmd.Format(_T("-audiofile \"%s\" \"%s\""), m_audio, m_video);
	ShellExecute(0, _T("open"), _T("mplayer.exe"), mpcmd, NULL, SW_SHOW);
}

void CMOtherPage::OnButtonVideo() 
{
	// TODO: Add your control notification handler code here
	
	TCHAR szFilePath[MAX_PATH + 1];
	::GetCurrentDirectory(MAX_PATH,szFilePath);
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT
		,_T("������Ƶ��ʽ|*.avi;*.mkv;*.ogm;*.mp4;*.m4v;*.m4p;*.m4b;*.flv;*.vp6;\
*.divx;*.vg2;*.dat;*.mpg;*.mpeg;*.tp;*.ts;*.tpr;*.pva;*.pps;*.mpe;*.vob;*.rm;*.rmvb;\
*.wmv;*.asf;*.wmp;*.wm;*.mov;*.qt;*.3gp;*.3gpp;*.3g2;*.3gp2|�����ļ�(*.*)|*.*||"));

//	dlg.m_ofn.lpstrFile = new wchar_t[102400];
//	memset(dlg.m_ofn.lpstrFile,0,sizeof(wchar_t)   *   102400);
//	dlg.m_ofn.nMaxFile = 102400;
	dlg.m_ofn.lpstrTitle=_T("����Ƶ�ļ�");
    if(dlg.DoModal()==IDOK)
	{
		m_video = dlg.GetPathName();
	}
	dlg.DestroyWindow();
	::SetCurrentDirectory(szFilePath);
	UpdateData(FALSE);
}

void CMOtherPage::OnButtonFlash() 
{
	// TODO: Add your control notification handler code here
	CString m_program;
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	m_program.Format(_T("%s"),szFilePath);
	ShellExecute(0, _T("open"), m_program , _T(" --Open FlashPlayer"), NULL, SW_SHOW);
}

void CMOtherPage::OnButtonMedia() 
{
	// TODO: Add your control notification handler code here
	CString m_program;
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	m_program.Format(_T("%s"),szFilePath);
	ShellExecute(0, _T("open"), m_program , _T(" --Open MediaPlayer"), NULL, SW_SHOW);
}

bool CMOtherPage::CheckRealOnline()
{
	CReg reg;
	CString regstr = _T("CLSID\\{CFCDAA03-8BE4-11CF-B84B-0020AFBBCCFA}\\InprocServer32");
	if(!reg.ShowContent_STR(HKEY_CLASSES_ROOT,regstr,_T("")))
		return false;
	CString regstr1 = _T("Software\\RealNetworks\\Preferences\\DT_Codecs");
	if(!reg.ShowContent_STR(HKEY_CLASSES_ROOT,regstr1,_T("")))
		return false;
	return true;
}

UINT CheckThread(LPVOID pParam)
{
	CMOtherPage* This = (CMOtherPage *) pParam;
	int checktime = 0;
CheckReal:
	checktime++;
	Sleep(300);
	if(This->CheckRealOnline())
		MessageBox(This->m_hWnd , _T("Real ����֧��ע��ɹ���"),_T("Real ����֧��"), 0);
	else
	{
		if(checktime < 5)
			goto CheckReal;
		MessageBox(This->m_hWnd , _T("Real ����֧��ע��ʧ�ܣ������ԣ�"),_T("Real ����֧��"), 0);
	}
	
	This->CheckRealThread = NULL;
	return 0;
}

void CMOtherPage::OnButtonOnline() 
{
	// TODO: Add your control notification handler code here
	if(CheckRealOnline())
	{
		if(MessageBox(_T("Real ����֧����ע�ᣬ�Ƿ�����ע�᣿"),_T("Real ����֧��"),MB_OKCANCEL) != IDOK)
			return;
	}
	
	if(CheckRealThread != NULL)
		return;
	UpdateData(TRUE);
	TCHAR szFilePath[MAX_PATH + 1];
	CString m_dir, m_sysdir;
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	m_dir.Format(_T("%s"),szFilePath);

	if(m_mplayer.GetCheck() == 1)
		DeleteFile(m_dir + _T("codecs\\Real\\mloader.ini"));
	else
	{
		TCHAR szProgramPath[MAX_PATH + 1];
		GetModuleFileName(NULL, szProgramPath, MAX_PATH);
		CString cmd;
		if(m_mpc)
			cmd = m_mpc_exe;
		else
			cmd.Format(_T("%s --Open MediaPlayer"), szProgramPath);
		WritePrivateProfileString(_T("Command"), _T("Program_Path"),  cmd , m_dir + _T("codecs\\Real\\mloader.ini"));
	}

	if(!IsFileExist(m_dir + _T("codecs\\Real\\rmoc3260.dll")))
	{
		if(IsFileExist(m_dir + _T("codecs\\realonline.7z")))
			Decode7zFile(m_dir + _T("codecs\\realonline.7z"),m_dir + _T("codecs\\"));
		else if(IsFileExist(m_dir + _T("codecs\\realonline.rar")))
			UnRarFile(m_dir + _T("codecs\\realonline.rar"),m_dir + _T("codecs\\"));
	}

	if((!IsFileExist(m_dir + _T("codecs\\Real\\realreg"))) ||
		(!IsFileExist(m_dir + _T("codecs\\Real\\rmoc3260.dll"))) ||
		(!IsFileExist(m_dir + _T("codecs\\Real\\mloader.exe"))) ||
		(!IsFileExist(m_dir + _T("codecs\\pncrt.dll"))))
	{
		MessageBox(_T("Real ����֧��ע��ʧ�ܣ�δ�ҵ���Ҫ���ļ���"),_T("Real ����֧��"));
		return;
	}

	TCHAR szCurPath[MAX_PATH + 1];
	::GetCurrentDirectory(MAX_PATH,szCurPath);
	::SetCurrentDirectory(szFilePath);
	TCHAR szSystemPath[MAX_PATH + 1];
	::GetSystemDirectory(szSystemPath,MAX_PATH);
	m_sysdir.Format(_T("%s\\"),szSystemPath);
	ShellExecute(0, _T("open"), _T("regsvr32.exe") , _T(" /s \"")+ m_dir + _T("codecs\\Real\\rmoc3260.dll\"") , NULL, SW_HIDE);
	ShellExecute(0, _T("open"), _T("regedit") , _T(" /s \"")+ m_dir + _T("codecs\\Real\\aero\"") , NULL, SW_HIDE);
	CopyFile(m_dir +_T("codecs\\pncrt.dll") , m_sysdir + _T("pncrt.dll") , TRUE);
	CopyFile(m_dir +_T("codecs\\msvcp71.dll") , m_sysdir + _T("msvcp71.dll") , FALSE);
	CopyFile(m_dir +_T("codecs\\msvcr71.dll") , m_sysdir + _T("msvcr71.dll") , FALSE);
	CopyFile(m_dir +_T("codecs\\Real\\realreg") , m_dir +_T("realreg.inf") , TRUE);
	WinExec("rundll32.exe setupapi,InstallHinfSection DefaultInstall 128 .\\realreg.inf",SW_HIDE);
	DeleteFile(m_dir +_T("realreg.inf"));
	::SetCurrentDirectory(szCurPath);

	if(CheckRealThread == NULL)
	{
		CheckRealThread = AfxBeginThread(CheckThread,this);
	}
}

void CMOtherPage::OnButtonDonline() 
{
	// TODO: Add your control notification handler code here
	if(!CheckRealOnline())
	{
		MessageBox(_T("Real ����֧����δע�ᣡ"),_T("Real ����֧��"));
		return;
	}
	UpdateData(TRUE);
	TCHAR szFilePath[MAX_PATH + 1];
	CString m_dir;
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	m_dir.Format(_T("%s"),szFilePath);

	if((!IsFileExist(m_dir + _T("codecs\\Real\\unrealreg"))) ||
		(!IsFileExist(m_dir + _T("codecs\\Real\\rmoc3260.dll"))))
	{
		MessageBox(_T("Real ����֧�ַ�ע��ʧ�ܣ�δ�ҵ���Ҫ���ļ���"),_T("Real ����֧��"));
		return;
	}
	TCHAR szCurPath[MAX_PATH + 1];
	::GetCurrentDirectory(MAX_PATH,szCurPath);
	::SetCurrentDirectory(szFilePath);
	
	ShellExecute(0, _T("open"), _T("regsvr32.exe") , _T(" /u /s \"")+ m_dir + _T("codecs\\Real\\rmoc3260.dll\"") , NULL, SW_HIDE);
	CopyFile(m_dir +_T("codecs\\Real\\unrealreg") , m_dir +_T("unrealreg.inf") , TRUE);
	WinExec("rundll32.exe setupapi,InstallHinfSection DefaultInstall 128 .\\unrealreg.inf",SW_HIDE);
	DeleteFile(m_dir +_T("unrealreg.inf"));
	::SetCurrentDirectory(szCurPath);
	if(!CheckRealOnline())
		MessageBox(_T("Real ����֧�ַ�ע��ɹ���"),_T("Real ����֧��"));
	else
		MessageBox(_T("Real ����֧�ַ�ע��ɹ��������ԣ�"),_T("Real ����֧��"));
	
}

void CMOtherPage::OnRadioMplayer() 
{
	// TODO: Add your control notification handler code here
	m_meditor.SetCheck(0);
}

void CMOtherPage::OnRadioMeditor() 
{
	// TODO: Add your control notification handler code here
	m_mplayer.SetCheck(0);
}
void CMOtherPage::OnBnClickedButtonLink()
{
	CMLinkDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		HRESULT hr = CoInitialize(NULL);
		if (SUCCEEDED(hr))
		{
			HRESULT hres;
			IShellLink* psl;
			IPersistFile* ppf;
			TCHAR szPath[MAX_PATH + 1];
			GetModuleFileName(NULL, szPath, MAX_PATH);
			CString meditor_exe(szPath);
			CString mplayer_exe(m_program_dir + _T("mplayer.exe"));
			CString DeskTop_dir;
			CString StartMenu_dir;
			CString LinkPath;
			if(GetSpecialFolder(CSIDL_DESKTOPDIRECTORY , szPath))
				DeskTop_dir.Format(_T("%s\\") , szPath);

			if(GetSpecialFolder(CSIDL_PROGRAMS , szPath))
			{
				CString dir;
				dir.Format(_T("%s\\MPlayer") , szPath);
				if(dlg.m_meditor_start || dlg.m_mplayer_start || dlg.m_tools_start
					 || dlg.m_flash_start  || dlg.m_dshow_start)
				{
					CreateDirectory(dir,NULL);
					StartMenu_dir.Format(_T("%s\\") , dir);
					dir.Format(_T("%s\\MPlayer\\���ù���") , szPath);
					if(dlg.m_tools_start && IsFileExist(m_program_dir + _T("tools")))
						CreateDirectory(dir,NULL);
					else
						DeleteFolder(dir);
				}
				else
					DeleteFolder(dir);
			}
			hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&psl);
			if(! FAILED(hres))
			{
				psl->SetPath(meditor_exe);
				hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);
				if(! FAILED(hres) )
				{
					if(DeskTop_dir.GetLength() > 3)
					{
						LinkPath.Format(_T("%sMPlayer��ѡ��.lnk") , DeskTop_dir);
						if(dlg.m_meditor_desk)
							ppf->Save(LinkPath, STGM_READWRITE);
						else
							DeleteFile(LinkPath);
					}
					if(StartMenu_dir.GetLength() > 3)
					{
						LinkPath.Format(_T("%sMPlayer��ѡ��.lnk") , StartMenu_dir);
						if(dlg.m_meditor_start)
							ppf->Save(LinkPath, STGM_READWRITE);
						else
							DeleteFile(LinkPath);

						LinkPath.Format(_T("%sFlash ������.lnk") , StartMenu_dir);
						if(dlg.m_flash_start)
						{
							psl->SetArguments(_T("--Open FlashPlayer"));
							psl->SetIconLocation(meditor_exe, 1);
							ppf->Save(LinkPath, STGM_READWRITE);
						}
						else
							DeleteFile(LinkPath);

						LinkPath.Format(_T("%sDirectShow ������.lnk") , StartMenu_dir);
						if(dlg.m_dshow_start)
						{
							psl->SetArguments(_T("--Open MediaPlayer"));
							psl->SetIconLocation(meditor_exe, 2);
							ppf->Save(LinkPath, STGM_READWRITE);
						}
						else
							DeleteFile(LinkPath);
					}
				}
			}

			ppf->Release();
			psl->Release();
			hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&psl);
			if( ! FAILED(hres))
			{
				psl->SetPath(mplayer_exe);
				hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);
				if(! FAILED(hres) && StartMenu_dir.GetLength() > 5)
				{
					if(DeskTop_dir.GetLength() > 3)
					{
						LinkPath.Format(_T("%sMPlayer.lnk") , DeskTop_dir);
						if(dlg.m_mplayer_desk && IsFileExist(mplayer_exe))
							ppf->Save(LinkPath, STGM_READWRITE);
						else
							DeleteFile(LinkPath);
					}
					if(StartMenu_dir.GetLength() > 3)
					{
						LinkPath.Format(_T("%sMPlayer.lnk") , StartMenu_dir);
						if(dlg.m_mplayer_start && IsFileExist(mplayer_exe))
							ppf->Save(LinkPath, STGM_READWRITE);
						else
							DeleteFile(LinkPath);
					}
				}
			}

			CString tools_name;
			if(dlg.m_mpc_start)
			{
				tools_name.Format(_T("%stools\\mplayerc.exe") , m_program_dir);
				LinkPath.Format(_T("%sMedia Player Classic.lnk") , StartMenu_dir);
				if( IsFileExist(tools_name))
				{
					ppf->Release();
					psl->Release();
					hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&psl);
					if(! FAILED(hres))
					{
						psl->SetPath(tools_name);
						hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);
						if(! FAILED(hres))
							ppf->Save(LinkPath, STGM_READWRITE);
					}
				}
				else
					DeleteFile(LinkPath);
			}

			if(dlg.m_tools_start && IsFileExist(m_program_dir + _T("tools")) && StartMenu_dir.GetLength() > 3)
			{
				for(int tools_i = 1 ; tools_i <= 7 ; tools_i++)
				{
					switch(tools_i)
					{
					case 1:
						tools_name.Format(_T("%stools\\mmg.exe") , m_program_dir);
						LinkPath.Format(_T("%s���ù���\\MKV ת���ϳɹ���.lnk") , StartMenu_dir);
						break;
					case 2:
						tools_name.Format(_T("%stools\\MKVextractGUI.exe") , m_program_dir);
						LinkPath.Format(_T("%s���ù���\\MKV ������ȡ����.lnk") , StartMenu_dir);
						break;
					case 3:
						tools_name.Format(_T("%stools\\flvmdigui.exe") , m_program_dir);
						LinkPath.Format(_T("%s���ù���\\FLV �޸�����.lnk") , StartMenu_dir);
						break;
					case 4:
						tools_name.Format(_T("%stools\\FLVExtract.exe") , m_program_dir);
						LinkPath.Format(_T("%s���ù���\\FLV ������ȡ����.lnk") , StartMenu_dir);
						break;
					case 5:
						tools_name.Format(_T("%stools\\GSpot.exe") , m_program_dir);
						LinkPath.Format(_T("%s���ù���\\GSpot ӰƬ��Ϣ�鿴����.lnk") , StartMenu_dir);
						break;
					case 6:
						tools_name.Format(_T("%stools\\MediaInfo.exe") , m_program_dir);
						LinkPath.Format(_T("%s���ù���\\MediaInfo ӰƬ��Ϣ�鿴����.lnk") , StartMenu_dir);
						break;
					case 7:
						tools_name.Format(_T("%stools\\pmp_demuxer_gui.exe") , m_program_dir);
						LinkPath.Format(_T("%s���ù���\\PMP ������ȡ����.lnk") , StartMenu_dir);
						break;
					default:
						tools_name = _T("");
						break;
					}
					if( IsFileExist(tools_name))
					{
						ppf->Release();
						psl->Release();
						hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&psl);
						if(! FAILED(hres))
						{
							psl->SetPath(tools_name);
							hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);
							if(! FAILED(hres))
								ppf->Save(LinkPath, STGM_READWRITE);
						}
					}
					else
						DeleteFile(LinkPath);
				}
			}
			ppf->Release();
			psl->Release();
			CoUninitialize();
		}
	}
}
