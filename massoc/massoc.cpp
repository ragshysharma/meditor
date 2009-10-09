// massoc.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "massoc.h"
#include "MShared.h"
#include "AVS.h"
#include "RealDlg.h"
#include "MAssosDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmassocApp

BEGIN_MESSAGE_MAP(CmassocApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CmassocApp ����

CmassocApp::CmassocApp()
{
	hResourceHandleOld = NULL;
	hResourceHandleMod = NULL;
	IDD = IDD_ASSOS_DIALOG;
	AppLanguage = 0;
}


// Ψһ��һ�� CmassocApp ����

CmassocApp theApp;


// CmassocApp ��ʼ��

BOOL CmassocApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	SetRegistryKey(_T("MEditor2 - Assoc"));

	CString sCmdLine(this->m_lpCmdLine);

	if(sCmdLine.Find(_T("--install-avs")) >= 0) {
		int offset = sCmdLine.Find(_T("\""));
		if(offset < 0)
			return FALSE;
		CString path = sCmdLine.Right(sCmdLine.GetLength() - offset - 1);
		path.Trim();
		offset = path.Find(_T("\""));
		if(offset <= 0)
			return FALSE;
		path = path.Left(offset);

		CAVS avs;
		avs.Install(path);
		return FALSE;
	} else if(sCmdLine.Find(_T("--real-online")) >= 0)	{
		HANDLE gUniqueEvent = CreateEvent(NULL, TRUE, TRUE, _T("meditor2 - RealOnline"));
		if(GetLastError() == ERROR_ALREADY_EXISTS)
			return FALSE;

		CRealDlg dlg;
		m_pMainWnd = &dlg;
		dlg.DoModal();

		if(gUniqueEvent)
			CloseHandle(gUniqueEvent);

		return FALSE;
	}

	int langfile_tc = 0;
	int langfile_en = 0;
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	CString program_dir;
	program_dir.Format(_T("%s"),szFilePath);
	CString right = program_dir.Right(8);
	if(right == _T("\\codecs\\"))
		program_dir = program_dir.Left(program_dir.GetLength() - 7);

	if(IsFileExist(program_dir + _T("codecs\\meditor2.tc.dll")))
		langfile_tc = 2;
	if(IsFileExist(program_dir + _T("meditor2.tc.dll")))
		langfile_tc = 1;
	if(IsFileExist(program_dir + _T("codecs\\meditor2.en.dll")))
		langfile_en = 2;
	if(IsFileExist(program_dir + _T("meditor2.en.dll")))
		langfile_en = 1;

	if(langfile_tc || langfile_en)
	{
		AppLanguage = GetPrivateProfileInt(_T("Option"),_T("Language"),0,program_dir + _T("kk.ini"));
		if(AppLanguage == 0)
		{
			LANGID   _SysLangId   =   GetSystemDefaultLangID();
			if(PRIMARYLANGID(_SysLangId)   ==   LANG_CHINESE)
			{
				if(SUBLANGID(_SysLangId)   ==   SUBLANG_CHINESE_SIMPLIFIED)
					AppLanguage = 1;		//Simplified Chinese GBK
				else if(SUBLANGID(_SysLangId)   ==   SUBLANG_CHINESE_TRADITIONAL)
					AppLanguage = 4;		//Traditional Chinese Big5
				else
					AppLanguage = 3;		//ANSI
			}
			else
				AppLanguage = 2;			//ANSI
		}

	}

	HANDLE gUniqueEvent = CreateEvent(NULL, TRUE, TRUE, _T("meditor2 - Assoc"));
	if(GetLastError() == ERROR_ALREADY_EXISTS)
		return FALSE;

	CString strSatellite = _T("");
	if(AppLanguage == 2 && langfile_en) {
		IDD = IDD_ASSOS_DIALOG_EN;
		if(langfile_en == 1)
			strSatellite = program_dir + _T("meditor2.en.dll");
		else
			strSatellite = program_dir + _T("codecs\\meditor2.en.dll");
	} else if(langfile_tc && (AppLanguage == 3 || AppLanguage == 4)) {
		IDD = IDD_ASSOS_DIALOG_TC;
		if(langfile_tc == 1)
			strSatellite = program_dir + _T("meditor2.tc.dll");
		else
			strSatellite = program_dir + _T("codecs\\meditor2.tc.dll");
	}

	if (strSatellite.GetLength() > 2)
	{
		hResourceHandleOld = AfxGetResourceHandle();
		hResourceHandleMod = LoadLibrary (strSatellite);
	}

	CMAssosPage dlg;
	m_pMainWnd = &dlg;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	if(gUniqueEvent)
		CloseHandle(gUniqueEvent);

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
