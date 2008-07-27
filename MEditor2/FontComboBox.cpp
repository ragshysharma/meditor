#include "stdafx.h"
#include "FontComboBox.h"
//#include   <functional>   
#include   <algorithm>

#ifndef   NTM_PS_OPENTYPE
#define   NTM_PS_OPENTYPE                0x00020000
#endif
#ifndef   NTM_TT_OPENTYPE
#define   NTM_TT_OPENTYPE                0x00040000
#endif
#ifndef   PS_OPENTYPE_FONTTYPE
#define   PS_OPENTYPE_FONTTYPE      0x10000
#define   TT_OPENTYPE_FONTTYPE      0x20000
#define   TYPE1_FONTTYPE                   0x40000
#endif

#define           FNTIMG_XSIZE             20
#define           FNTIMG_X                 20
#define           FNTIMG_Y                 12

BEGIN_MESSAGE_MAP(CFontComboBox, CComboBox)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CFontComboBox::FillFontList()
{
	//��������DC������ö��ϵͳ��������Ϣ
	CDC* pDesktopDC = GetDesktopWindow()->GetWindowDC();       //ȡDC
	HDC hdc = pDesktopDC->GetSafeHdc();
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfCharSet = DEFAULT_CHARSET;
	::EnumFontFamilies(hdc,NULL, (FONTENUMPROC)EnumFontProc,(LPARAM)this);
	GetDesktopWindow()->ReleaseDC(pDesktopDC);      //�ͷ�DC
	//����STL�㷨�����Զ���Ķ�������
	//std::sort(m_pFontVec.begin(), m_pFontVec.end(), CFontComboBox::CompareFontName);
	InitStorage(300, LF_FACESIZE);
	//�����������Ƶ���Ͽ�
	for(UINT N=0; N<m_pFontVec.size(); ++N)
	{
		CString fontname = m_pFontVec[N]->GetFontName();
		if (fontname.Find(_T("@")) != 0)
			AddString(fontname);
	}
	//����COMDLG32.DLL
	HMODULE hModule = ::LoadLibraryEx(_T("COMDLG32.DLL"), NULL,
		DONT_RESOLVE_DLL_REFERENCES);
	ASSERT (hModule != NULL);
	//���سɹ�������DLL�м�������ͼƬ
	m_FontBmp = (HBITMAP)::LoadImage(hModule, MAKEINTRESOURCE(38), 
		IMAGE_BITMAP, 100, 24, LR_DEFAULTCOLOR);
	ASSERT(m_FontBmp != NULL);
	::FreeLibrary(hModule);
}

bool CFontComboBox::CompareFontName(const CFontInfo *pInfo1, const CFontInfo *pInfo2)
{
	if (pInfo1->GetFontName() != pInfo2->GetFontName())
		return false;
	return true;
}

int CFontComboBox::EnumFontProc(ENUMLOGFONTEX *lpelfe,
								NEWTEXTMETRICEX *lpntme,
								DWORD FontType,
								LPARAM lParam)
{
	CFontComboBox *pThis = reinterpret_cast<CFontComboBox*>(lParam);
	CFontInfo *pInfo = new CFontInfo;
	pInfo->SetFontType(FontType);
	pInfo->SetFontName(lpelfe->elfLogFont.lfFaceName);
	DWORD dwFontType = FontType;
	if (FontType & TRUETYPE_FONTTYPE)
	{
		DWORD dwFontFlags = lpntme->ntmTm.ntmFlags;
		if (dwFontFlags & NTM_PS_OPENTYPE)
			dwFontType |= PS_OPENTYPE_FONTTYPE;
		else
			dwFontType |=0;
		if (dwFontFlags & NTM_TT_OPENTYPE)
			dwFontType |= TT_OPENTYPE_FONTTYPE;
		else
			dwFontType |=0;
		dwFontType |= (dwFontFlags & NTM_TYPE1 ? TYPE1_FONTTYPE : 0);
	}
	switch(dwFontType & 0x70007)
	{
	case (TRUETYPE_FONTTYPE | PS_OPENTYPE_FONTTYPE):
	case (TRUETYPE_FONTTYPE | TT_OPENTYPE_FONTTYPE):
	case (TRUETYPE_FONTTYPE | TYPE1_FONTTYPE):
		pInfo->SetImage(3); break;
	case RASTER_FONTTYPE:
	case DEVICE_FONTTYPE:
	case NULL:
		pInfo->SetImage(0XFF); break;
	case TRUETYPE_FONTTYPE:
	default:
		pInfo->SetImage(0); break;
	}
	pThis->m_pFontVec.push_back(pInfo);
	return TRUE;
}

void CFontComboBox::OnDropdown()
{
	int nNumEntries = GetCount();
	int nWidth = 0;
	CString str;
	CClientDC dc(this);
	int nSave = dc.SaveDC();
	dc.SelectObject(GetFont());
	int nScrollWidth = ::GetSystemMetrics(SM_CXVSCROLL);      //ȡ���������
	for (int i = 0; i < nNumEntries; i++)
	{
		GetLBText(i, str);
		int nLength = dc.GetTextExtent(str).cx + nScrollWidth;
		nWidth = max(nWidth, nLength);
	}
	nWidth += dc.GetTextExtent(_T("0")).cx;
	dc.RestoreDC(nSave);
	if (!m_pFontVec.empty())
		SetDroppedWidth(nWidth + FNTIMG_XSIZE);                 //���ÿ��ֵ
}

void CFontComboBox::OnDestroy()
{
	for (UINT i=0; i<m_pFontVec.size(); ++i)
		delete m_pFontVec[i];
	m_pFontVec.erase(m_pFontVec.begin(), m_pFontVec.end());
	CComboBox::OnDestroy();
}

void CFontComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	int height;
	CWindowDC dc(NULL);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	height = tm.tmHeight - tm.tmInternalLeading;
	lpMeasureItemStruct->itemHeight = height - 1;
}

void CFontComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct->CtlType == ODT_COMBOBOX);
	CString strText;
	//�жϵ�ǰ���������������Ƿ�Ϊ��
	int nIndex = lpDrawItemStruct->itemID;
	if (GetLBTextLen(nIndex) < 0)
		return ;
	GetLBText(nIndex, strText);
	ASSERT(!strText.IsEmpty());
	int nImage = 0;
	//��������ֵ��m_pFontVec�õ�����ͼ������
	if (!m_pFontVec.empty())
		nImage = m_pFontVec[nIndex]->GetImage();
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	COLORREF crOldTextColor = dc.GetTextColor();
	COLORREF crOldBkColor = dc.GetBkColor();
	//���Item����ѡ�񽹵㡢״̬�£���ϵͳ����ɫ�ı��ı��ͱ���ɫ
	if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
		(lpDrawItemStruct->itemState & ODS_SELECTED))
	{
		dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
	}
	else
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);
	CRect     rItem(lpDrawItemStruct->rcItem);
	CRect     rText(rItem);
	CRect     rBmp(&rItem);
	if(m_FontBmp)
	{
		//����Item������Ԥ��ͼ����ͼλ��
		rBmp.top +=  (rBmp.Height() - FNTIMG_Y) / 2;
		rBmp.bottom = rBmp.top + FNTIMG_Y + 1;
		rText.left += FNTIMG_X;
		if (nImage != (int)0XFF)
		{
			int x,y;
			x = nImage * FNTIMG_X;   //����Ԥ��ͼ���ͼ���Դͼ�ľ��δ�С
			y = FNTIMG_Y;
			CDC mdc;
			mdc.CreateCompatibleDC(&dc);
			CBitmap* pOldBmp = mdc.SelectObject(CBitmap::FromHandle(m_FontBmp));
			COLORREF clrTransparent = mdc.GetPixel(0, y);
			//����TransparentBlt����͸����ͼ���˺�����Ҫ����MsImg32.Lib�ļ�
			::TransparentBlt (dc.GetSafeHdc(),rBmp.left, rBmp.top, FNTIMG_X, FNTIMG_Y,  
				mdc, x, y, FNTIMG_X, FNTIMG_Y, clrTransparent);
		}
	}
	else
		rText.left += 10;
	//rText������������������λ����Ҫ����ͼƬ�Ŀ��
	dc.DrawText(strText, rText, DT_LEFT|DT_SINGLELINE|DT_VCENTER);
	dc.SetTextColor(crOldTextColor);
	dc.SetBkColor(crOldBkColor);
	dc.Detach();
} 