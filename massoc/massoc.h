// massoc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmassocApp:
// �йش����ʵ�֣������ massoc.cpp
//

class CmassocApp : public CWinApp
{
public:
	CmassocApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��
	HMODULE		hResourceHandleOld;
	HMODULE		hResourceHandleMod;
	int			AppLanguage;
	UINT		IDD;

	DECLARE_MESSAGE_MAP()
};

extern CmassocApp theApp;