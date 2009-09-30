// Reg.h: interface for the CReg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REG_H__22726F6A_489C_48B2_BBAE_CBCD58F73289__INCLUDED_)
#define AFX_REG_H__22726F6A_489C_48B2_BBAE_CBCD58F73289__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CReg  
{
public:
	CReg();
	virtual ~CReg();

	//ע������
	HKEY hKey;
	TCHAR content[256];			//����ѯע����ֵ������
	DWORD dwType;		//�����ȡ��������
	DWORD dwLength;
	struct HKEY__*RootKey;		//ע�����������
	TCHAR *SubKey;				//����ע�����ĵ�ַ
	TCHAR *KeyName;				//�������������
	TCHAR *ValueName;			//������ֵ������
	LPBYTE SetContent_S;		//�ַ�������
	int SetContent_D[256];		//DWORD����
	BYTE SetContent_B[256];		//����������
	
	bool ShowContent_STR (struct HKEY__*ReRootKey,CString ReSubKey,CString ValueName);
	bool SetValue_S_STR (struct HKEY__*ReRootKey,CString ReSubKey,CString ValueName, CString Content);
	bool SetValue_N_STR (struct HKEY__*ReRootKey,CString ReSubKey,CString ValueName);
	bool DeleteValue_STR (struct HKEY__*ReRootKey,CString ReSubKey,CString ValueName);
	bool DeleteKey_STR (struct HKEY__*ReRootKey,CString ReSubKey,CString KeyName);
	bool SetValue_N (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName);
	
	bool ShowContent (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName);
	bool SetValue_S (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,unsigned char *ReSetContent_S,unsigned long length);
	int SetValue_D (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,int ReSetContent_D[256]);
	bool SetValue_B (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,BYTE ReSetContent_B[256]);
	int DeleteKey (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReKeyName);
	int DeleteValue (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName);

};


#endif // !defined(AFX_REG_H__22726F6A_489C_48B2_BBAE_CBCD58F73289__INCLUDED_)
