#pragma once


// CRealDlg �Ի���

class CRealDlg
{
public:
	CRealDlg();

	HANDLE CheckRealThread;
	CString m_cmdline;
	BOOL m_reg_ok;
	BOOL CheckRealOnline();
	BOOL RegRealOnline();
	BOOL DRegRealOnline();

	BOOL InstallReal();
};
