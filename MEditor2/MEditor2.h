// MEditor2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "MShared.h"

// CMEditor2App:
// �йش����ʵ�֣������ MEditor2.cpp
//

class CMEditor2App : public CWinApp
{
public:
	CMEditor2App();

// ��д
	public:
	virtual BOOL InitInstance();

	HMODULE		hResourceHandleOld;
	HMODULE		hResourceHandleMod;
	int			AppLanguage;
	UINT		DialogIDD;

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMEditor2App theApp;
