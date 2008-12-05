// MInputList.h: interface for the CMInputList class.
//////////////////////////////////////////////////////////////////////

#pragma once

class CMInputList
{
public:
	CStringArray m_key;
	CStringArray m_cmd;
	CStringArray m_val;
	CStringArray m_abs;
	CMInputList();
	void Add(CString key, CString cmd, CString val, CString abs = _T(""));
	bool GetAt(int i, CString &key, CString &cmd, CString &val, CString &abs);
	int GetSize();
};

class CMKeyList
{
public:
	CStringArray m_keyName;
	CStringArray m_keyInfo;
	CMKeyList();
	void Add(CString name, CString info);
	int GetKeyInfo(CString name);
	bool GetKeyName(CString info, CString &name);
};
