// MAudioPage.cpp : implementation file
//

#include "stdafx.h"
#include "meditor2.h"
#include "MAudioPage.h"
#include "MConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMAudioPage dialog


CMAudioPage::CMAudioPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMAudioPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMAudioPage)
	m_dvdsub = FALSE;
	m_ass = FALSE;
	m_audio_delay = _T("0");
	m_sub_delay = _T("0");
	m_sub_error = _T("8");
	m_volume = _T("60");
	m_volnorm = _T("100");
	m_volnorm_s = 0;
	m_volume_s = 60;
	m_font = _T("");
	m_font2 = _T("");
	m_size_s = _T("");
	m_color = _T("");
	m_bcolor = _T("");
	m_subpos = _T("90");
	m_slang = _T("zh,ch,tw");
	m_subcp = _T("GBK,BIG5,UTF-8,UTF-16");
	//}}AFX_DATA_INIT
}


void CMAudioPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMAudioPage)
	DDX_Control(pDX, IDC_COMBO_AUTOSCALE, m_autoscale);
	DDX_Control(pDX, IDC_COMBO_ALIGN, m_align);
	DDX_Control(pDX, IDC_COMBO_FUZZINESS, m_fuzziness);
	DDX_Control(pDX, IDC_COMBO_BCOLOR, m_bcolor_c);
	DDX_Control(pDX, IDC_COMBO_COLOR, m_color_c);
	DDX_Control(pDX, IDC_COMBO_CHANNELS, m_channels);
	DDX_Control(pDX, IDC_COMBO_F2, m_font2_c);
	DDX_Control(pDX, IDC_COMBO_F1, m_font_c);
	DDX_Control(pDX, IDC_SLIDER_VOLNORM, m_volnorm_c);
	DDX_Control(pDX, IDC_COMBO_SIZE, m_size);
	DDX_Control(pDX, IDC_COMBO_AUDIO, m_audio);
	DDX_Check(pDX, IDC_CHECK_DVDSUB, m_dvdsub);
	DDX_Check(pDX, IDC_CHECK_ASS, m_ass);
	DDX_Text(pDX, IDC_EDIT_AUDIODELAY, m_audio_delay);
	DDV_MaxChars(pDX, m_audio_delay, 9);
	DDX_Text(pDX, IDC_EDIT_SUBDELAY, m_sub_delay);
	DDV_MaxChars(pDX, m_sub_delay, 9);
	DDX_Text(pDX, IDC_EDIT_ERROR, m_sub_error);
	DDV_MaxChars(pDX, m_sub_error, 3);
	DDX_Text(pDX, IDC_EDIT_VOLUME, m_volume);
	DDV_MaxChars(pDX, m_volume, 3);
	DDX_Text(pDX, IDC_EDIT_VOLNORM, m_volnorm);
	DDV_MaxChars(pDX, m_volnorm, 4);
	DDX_Slider(pDX, IDC_SLIDER_VOLNORM, m_volnorm_s);
	DDX_Slider(pDX, IDC_SLIDER_VOLUME, m_volume_s);
	DDX_CBString(pDX, IDC_COMBO_F1, m_font);
	DDX_CBString(pDX, IDC_COMBO_F2, m_font2);
	DDX_CBString(pDX, IDC_COMBO_SIZE, m_size_s);
	DDV_MaxChars(pDX, m_size_s, 3);
	DDX_CBString(pDX, IDC_COMBO_COLOR, m_color);
	DDX_CBString(pDX, IDC_COMBO_BCOLOR, m_bcolor);
	DDX_Text(pDX, IDC_EDIT_SUBPOS, m_subpos);
	DDV_MaxChars(pDX, m_subpos, 3);
	DDX_Text(pDX, IDC_EDIT_SLANG, m_slang);
	DDX_Text(pDX, IDC_EDIT_SUBCP, m_subcp);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LIST_AUDIO, m_List);
}


BEGIN_MESSAGE_MAP(CMAudioPage, CDialog)
	//{{AFX_MSG_MAP(CMAudioPage)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VOLUME, OnReleasedcaptureSliderVolume)
	ON_EN_CHANGE(IDC_EDIT_VOLUME, OnChangeEditVolume)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VOLNORM, OnReleasedcaptureSliderVolnorm)
	ON_EN_CHANGE(IDC_EDIT_VOLNORM, OnChangeEditVolnorm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMAudioPage message handlers

enum Filters
{
	adv_af,
	volnormal,
	resample,
	equalizer
};


int CMAudioPage::m_nColWidths[5] = { 5, 15, 20, 50};	// sixty-fourths
// InitListCtrl
void CMAudioPage::InitListCtrl(CXListCtrl * pList)
{
	ASSERT(pList);
	if (!pList)
		return;

	// set column width according to window rect
	CRect rect;
	pList->GetWindowRect(&rect);

	int w = rect.Width() - 2;

	TCHAR *	lpszHeaders[] = { _T("ʹ��"),_T("�˾���"), _T("ѡ��"), _T("�˾�˵��"), NULL };
	int i;
	int total_cx = 0;
	LV_COLUMN lvcolumn;
	memset(&lvcolumn, 0, sizeof(lvcolumn));

	w = w - ::GetSystemMetrics(SM_CXVSCROLL);	// width of vertical scroll bar

	// add columns
	for (i = 0; ; i++)
	{
		if (lpszHeaders[i] == NULL)
			break;

		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_CENTER;
		lvcolumn.pszText = lpszHeaders[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = (lpszHeaders[i+1] == NULL) ? w - total_cx - 2 : (w * m_nColWidths[i]) / 64;
		total_cx += lvcolumn.cx;
		pList->InsertColumn(i, &lvcolumn);
	}

	// iterate through header items and attach the image list
	HDITEM hditem;

	for (i = 0; i < pList->m_HeaderCtrl.GetItemCount(); i++)
	{
		hditem.mask = HDI_IMAGE | HDI_FORMAT;
		pList->m_HeaderCtrl.GetItem(i, &hditem);
		hditem.fmt |=  HDF_IMAGE;
		hditem.iImage = XHEADERCTRL_NO_IMAGE;
		pList->m_HeaderCtrl.SetItem(i, &hditem);
	}

	memset(&lvcolumn, 0, sizeof(lvcolumn));

	// set the format again - must do this twice or first column does not get set
	for (i = 0; ; i++)
	{
		if (lpszHeaders[i] == NULL)
			break;

		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM;
		lvcolumn.fmt = LVCFMT_CENTER;
		lvcolumn.iSubItem = i;
		pList->SetColumn(i, &lvcolumn);
	}
}

///////////////////////////////////////////////////////////////////////////////
// FillListCtrl
void CMAudioPage::FillListCtrl(CXListCtrl * pList)
{
	// a list of some more of my favorite things

	pList->LockWindowUpdate();
	pList->DeleteAllItems();

	// insert the items and subitems into the list
	m_adv_af.RemoveAll();
	m_volnormal.RemoveAll();
	m_equalizer.RemoveAll();
	m_resample.RemoveAll();

	m_adv_af.Add(_T("�������Զ�ѡ��"));	
	m_adv_af.Add(_T("�����Ż�"));
	m_adv_af.Add(_T("�ٶ��Ż�"));

	m_volnormal.Add(_T("������ƽ������"));
	m_volnormal.Add(_T("������ƽ������"));

	m_resample.Add(_T("8kHz �Զ�"));
	m_resample.Add(_T("8kHz ���Բ�ֵ,����Ʒ�ʵ�"));
	m_resample.Add(_T("8kHz �������������������"));
	m_resample.Add(_T("8kHz ����������鸡�㴦��"));
	m_resample.Add(_T("16kHz �Զ�"));
	m_resample.Add(_T("16kHz ���Բ�ֵ,����Ʒ�ʵ�"));
	m_resample.Add(_T("16kHz �������������������"));
	m_resample.Add(_T("16kHz ����������鸡�㴦��"));
	m_resample.Add(_T("22.05kHz �Զ�"));
	m_resample.Add(_T("22.05kHz ���Բ�ֵ,����Ʒ�ʵ�"));
	m_resample.Add(_T("22.05kHz �������������������"));
	m_resample.Add(_T("22.05kHz ����������鸡�㴦��"));
	m_resample.Add(_T("32kHz �Զ�"));
	m_resample.Add(_T("32kHz ���Բ�ֵ,����Ʒ�ʵ�"));
	m_resample.Add(_T("32kHz �������������������"));
	m_resample.Add(_T("32kHz ����������鸡�㴦��"));
	m_resample.Add(_T("44.1kHz �Զ�"));
	m_resample.Add(_T("44.1kHz ���Բ�ֵ,����Ʒ�ʵ�"));
	m_resample.Add(_T("44.1kHz �������������������"));
	m_resample.Add(_T("44.1kHz ����������鸡�㴦��"));
	m_resample.Add(_T("48kHz �Զ�"));
	m_resample.Add(_T("48kHz ���Բ�ֵ,����Ʒ�ʵ�"));
	m_resample.Add(_T("48kHz �������������������"));
	m_resample.Add(_T("48kHz ����������鸡�㴦��"));
	m_resample.Add(_T("64kHz �Զ�"));
	m_resample.Add(_T("64kHz ���Բ�ֵ,����Ʒ�ʵ�"));
	m_resample.Add(_T("64kHz �������������������"));
	m_resample.Add(_T("64kHz ����������鸡�㴦��"));
	m_resample.Add(_T("96kHz �Զ�"));
	m_resample.Add(_T("96kHz ���Բ�ֵ,����Ʒ�ʵ�"));
	m_resample.Add(_T("96kHz �������������������"));
	m_resample.Add(_T("96kHz ����������鸡�㴦��"));


	pList->InsertItem(adv_af, _T(""));
	pList->SetCheckbox(adv_af, 0, 0);
	pList->SetItemText(adv_af, 1, _T("�߼���Ƶ������"));
	pList->SetComboBox(adv_af, 2, TRUE,  &m_adv_af,  5,  2,  FALSE);
	pList->SetItemText(adv_af, 3, _T("�Ż���Ƶ�طž��Ȼ��ٶ�"));

	pList->InsertItem(volnormal, _T(""));
	pList->SetCheckbox(volnormal, 0, 0);
	pList->SetItemText(volnormal, 1, _T("����������"));
	pList->SetComboBox(volnormal, 2, TRUE,  &m_volnormal,  5,  0,  FALSE);
	pList->SetItemText(volnormal, 3, _T("û��ʧ����������"));

	
	pList->InsertItem(resample, _T(""));
	pList->SetCheckbox(resample, 0, 0);
	pList->SetItemText(resample, 1, _T("��Ƶ�ز���"));
	pList->SetComboBox(resample, 2, TRUE,  &m_resample,  5,  16,  FALSE);
	pList->SetItemText(resample, 3, _T("�ı���Ƶ���Ĳ���(��/Ƶ)��"));

	
	pList->InsertItem(equalizer, _T(""));
	pList->SetCheckbox(equalizer, 0, 0);
	pList->SetItemText(equalizer, 1, _T("10����8�Ⱦ�����"));
	pList->SetItemText(equalizer, 2, _T("0:0:0:0:0:0:0:0:0:0"));
	pList->SetEdit(equalizer, 2);
	//.SetComboBox(equalizer, 2, TRUE,  &m_equalizer,  5,  0,  FALSE);
	pList->SetItemText(equalizer, 3, _T("��Ƶ�ʲ��ε�����ֱ�(-12~12)"));


	pList->UnlockWindowUpdate();	// ***** unlock window updates *****
}

void CMAudioPage::OnReleasedcaptureSliderVolume(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_volume.Format(_T("%d"),m_volume_s);
	UpdateData(FALSE);
	*pResult = 0;
}

void CMAudioPage::OnChangeEditVolume() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int x = _ttoi(m_volume);
	if(x >= 0 && x <= 100)
		m_volume_s = x;
	else if(x < 0)
		m_volume_s = 0;
	else
		m_volume_s = 100;
	UpdateData(FALSE);
}

void CMAudioPage::OnChangeEditVolnorm() 
{
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int x = _ttoi(m_volnorm);
	if(x >= 100 && x <= 1000)
		m_volnorm_s = x/10;
	else if(x < 100)
		m_volnorm_s = 10;
	else
		m_volnorm_s = 100;
	UpdateData(FALSE);
}

void CMAudioPage::OnReleasedcaptureSliderVolnorm(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_volnorm.Format(_T("%d"),m_volnorm_s * 10);
	UpdateData(FALSE);
	*pResult = 0;
}

BOOL CMAudioPage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	InitListCtrl(&m_List);
	FillListCtrl(&m_List);

	m_volnorm_c.SetRange(10,100);
	
	m_audio.AddString(_T("DirectSound (�Ƽ�)"));
	m_audio.AddString(_T("Win32 WaveOut"));
	m_audio.AddString(_T("�����Ƶ��PCM/Wave�ļ�"));
	m_audio.AddString(_T("����Ƶ���"));
	m_audio.SetCurSel(dsound);

	m_fuzziness.AddString(_T("��ȷƥ��"));
	m_fuzziness.AddString(_T("���а������Ƶ���Ļ"));
	m_fuzziness.AddString(_T("��ǰĿ¼��������Ļ"));
	m_fuzziness.SetCurSel(name);

	m_align.AddString(_T("��������"));
	m_align.AddString(_T("�������"));
	m_align.AddString(_T("�ײ�����"));
	m_align.SetCurSel(center);

	m_autoscale.AddString(_T("���Զ�����"));
	m_autoscale.AddString(_T("�߶ȳɱ���"));
	m_autoscale.AddString(_T("��ȳɱ���"));
	m_autoscale.AddString(_T("�Խ��߳ɱ���"));
	m_autoscale.SetCurSel(diagonal);

	m_size.AddString(_T("2"));
	m_size.AddString(_T("2.5"));
	m_size.AddString(_T("3"));
	m_size.AddString(_T("3.5"));
	m_size.AddString(_T("4"));
	m_size.AddString(_T("4.5"));
	m_size.AddString(_T("5"));
	m_size_s = _T("3");
	
	m_color_c.AddString(_T("Ĭ����ɫ"));
	m_color_c.AddString(_T("ffffff00"));
	m_color_c.AddString(_T("ff000000"));
	m_color_c.AddString(_T("00ff0000"));
	m_color_c.AddString(_T("0000ff00"));
	m_color_c.AddString(_T("ffffff50"));

	m_bcolor_c.AddString(_T("Ĭ����ɫ"));
	m_bcolor_c.AddString(_T("ffffff00"));
	m_bcolor_c.AddString(_T("ff000000"));
	m_bcolor_c.AddString(_T("00ff0000"));
	m_bcolor_c.AddString(_T("0000ff00"));
	m_bcolor_c.AddString(_T("00000050"));

	m_bcolor = _T("Ĭ����ɫ");
	m_color = _T("Ĭ����ɫ");

	m_channels.AddString(_T("Ĭ��"));
	m_channels.AddString(_T("2.0����"));
	m_channels.AddString(_T("4.0����"));
	m_channels.AddString(_T("5.1����"));
	m_channels.SetCurSel(ch_auto);

	TCHAR szCurPath[MAX_PATH + 1];
	::GetCurrentDirectory(MAX_PATH,szCurPath);

	TCHAR szFontPath[MAX_PATH + 1];
	SHGetSpecialFolderPath(NULL, szFontPath , CSIDL_FONTS , FALSE);

	::SetCurrentDirectory(szFontPath);

	CFileFind finder;
	if(finder.FindFile(_T("*.ttf"),0))
	{
		while(finder.FindNextFile())
		{
			m_font_c.AddString(finder.GetFileName());
			m_font2_c.AddString(finder.GetFileName());
		}
		CString str = finder.GetFileName();
		if(str.GetLength() > 1)
		{
			m_font_c.AddString(str);
			m_font2_c.AddString(str);
		}
	}
	if(finder.FindFile(_T("*.ttc"),0))
	{
		while(finder.FindNextFile())
		{
			m_font_c.AddString(finder.GetFileName());
			m_font2_c.AddString(finder.GetFileName());
		}
		CString str = finder.GetFileName();
		if(str.GetLength() > 1)
		{
			m_font_c.AddString(str);
			m_font2_c.AddString(str);
		}
	}
	::SetCurrentDirectory(szCurPath);
	m_font2_c.AddString(_T(""));
	m_font = _T("simhei.ttf");

	InitFromConfig();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMAudioPage::SetNormal()
{
	m_ass = TRUE;
	m_dvdsub = TRUE;
	m_volnorm_s = 150;
	m_volnorm = _T("150");
	m_size_s = _T("3");
	m_bcolor = _T("Ĭ����ɫ");
	m_color = _T("Ĭ����ɫ");
	m_audio_delay = _T("0");
	m_sub_delay = _T("0");
	m_sub_error = _T("8");
	m_volume = _T("60");
	m_volume_s = 60;
	m_subpos = _T("90");
	m_slang = _T("zh,ch,tw");
	m_subcp = _T("GBK,BIG-5,CP932,CP949,UTF-8,UTF-16");
	m_audio.SetCurSel(dsound);
	m_fuzziness.SetCurSel(name);
	m_align.SetCurSel(center);
	m_autoscale.SetCurSel(diagonal);
	m_channels.SetCurSel(ch_auto);
	m_List.SetCheckbox(equalizer, 0, 0);
	m_List.SetItemText(equalizer, 2,_T("0:0:0:0:0:0:0:0:0:0"));
	m_List.SetCheckbox(resample, 0, 0);
	m_List.SetComboBox(resample, 2, TRUE,  &m_resample,  8,  16,  FALSE);
	m_List.SetCheckbox(adv_af, 0, 0);
	m_List.SetComboBox(adv_af, 2, TRUE,  &m_adv_af,  5,  0,  FALSE);
	m_List.SetCheckbox(volnormal, 0, 1);
	m_List.SetComboBox(volnormal, 2, TRUE,  &m_volnormal,  5,  0,  FALSE);
}

void CMAudioPage::SetHigh()
{
	SetNormal();
}

void CMAudioPage::SetLower()
{
	SetNormal();
	m_ass = FALSE;
	m_dvdsub = FALSE;
	m_volnorm_s = 100;
	m_volnorm = _T("100");
	m_List.SetCheckbox(volnormal, 0, 0);
	m_List.SetCheckbox(adv_af, 0, 1);
}

void CMAudioPage::InitFromConfig()
{
	if(!m_cfg)
		return;
	int value_i;
	bool value_b;
	double value_d;
	CString value_s;
	CString value_sub;
	m_List.LockWindowUpdate();

	m_cfg->GetValue_Boolean(_T("softvol"),value_b);
	if(m_cfg->GetValue_Boolean(_T("ass"),value_b))
	{
		if(value_b)
			m_ass = TRUE;
		else
			m_ass = FALSE;
	}
	if(m_cfg->GetValue_Integer(_T("spuaa"),value_i))
	{
		if(value_i  == 4)
			m_dvdsub = TRUE;
		else
			m_dvdsub = FALSE;
	}
	if(m_cfg->GetValue_Integer(_T("softvol-max"),value_i))
	{
		if(value_i > 100 && value_i < 1000)
		{
			m_volnorm_s = value_i  / 10;
			m_volnorm.Format(_T("%d"),value_i);
		}
		else
		{
			m_volnorm_s = 100;
			m_volnorm = _T("100");
		}
	}
	if(m_cfg->GetValue_Integer(_T("sub-ignore-errors"),value_i))
	{
		if(value_i >= 0 && value_i <= 500)
			m_sub_error.Format(_T("%d"),value_i);
	}
	if(m_cfg->GetValue_Integer(_T("sub-fuzziness"),value_i))
		m_fuzziness.SetCurSel(value_i);
	if(m_cfg->GetValue_Integer(_T("spualign"),value_i))
		m_align.SetCurSel(value_i);
	if(m_cfg->GetValue_Integer(_T("subalign"),value_i))
		m_align.SetCurSel(value_i);
	if(m_cfg->GetValue_Integer(_T("subfont-autoscale"),value_i))
		m_autoscale.SetCurSel(value_i);
	if(m_cfg->GetValue_Integer(_T("subpos"),value_i))
	{
		if(value_i >= 0 && value_i <= 100)
			m_subpos.Format(_T("%d"),value_i);
	}
	if(m_cfg->GetValue_Double(_T("delay"),value_d))
	{
		m_audio_delay.Format(_T("%0.3f"),value_d);
	}
	if(m_cfg->GetValue_Double(_T("subdelay"),value_d))
	{
		m_sub_delay.Format(_T("%0.3f"),value_d);
	}
	if(m_cfg->GetValue_Integer(_T("Volume"),value_i,true))
	{
		if(value_i >= 0 && value_i <= 100)
		{
			m_volume_s = value_i;
			m_volume.Format(_T("%d"),value_i);
		}
	}
	if(m_cfg->GetValue_Integer(_T("channels"),value_i))
	{
		switch (value_i)
		{
		case 2:
			m_channels.SetCurSel(ch_2);
			break;
		case 4:
			m_channels.SetCurSel(ch_4);
			break;
		case 6:
			m_channels.SetCurSel(ch_6);
			break;
		default:
			m_channels.SetCurSel(ch_auto);
		}
	}
	if(m_cfg->GetValue_String(_T("subfont"),value_s))
	{
		value_s.TrimLeft(_T('"'));
		value_s.TrimRight(_T('"'));

		int first = value_s.Find(_T(","));
		if( first > 0)
		{
			m_font = value_s.Left(first);
			m_font2 = value_s.Right(value_s.GetLength() - first - 1);
		}
		else
			m_font = value_s;
	}
	if(m_cfg->GetValue_String(_T("ass-color"),value_s))
		m_color = value_s;
	if(m_cfg->GetValue_String(_T("ass-border-color"),value_s))
		m_bcolor = value_s;
	if(m_cfg->GetValue_String(_T("slang"),value_s))
		m_slang = value_s;
	if(m_cfg->GetValue_String(_T("subcp"),value_s))
		m_subcp = value_s;
	if(m_cfg->GetValue_String(_T("ao"),value_s))
	{
		if(value_s == _T("win32"))
			m_audio.SetCurSel(win32);
		else if(value_s == _T("pcm"))
			m_audio.SetCurSel(pcm);
		else if(value_s == _T("null"))
			m_audio.SetCurSel(ao_null);
		else
			m_audio.SetCurSel(dsound);
	}
	if(m_cfg->GetValue_String(_T("subfont-text-scale"),value_s))
	{
		m_size_s = value_s;
	}
	if(m_cfg->GetValue_String(_T("af"),value_s))
	{
		if(m_cfg->GetSubValue(value_s,_T("equalizer"), value_sub))
		{
			m_List.SetCheckbox(equalizer, 0, 1);
			m_List.SetItemText(equalizer, 2,value_sub);
		}
		if(m_cfg->HaveSubValue(value_s,_T("volnorm")))
		{
			m_List.SetCheckbox(volnormal, 0, 1);
			if(m_cfg->GetSubValue(value_s,_T("volnorm"), value_sub))
			{
				if(value_sub == _T("2"))
					m_List.SetComboBox(volnormal, 2, TRUE,  &m_volnormal,  5,  1,  FALSE);
			}
		}
		if(m_cfg->GetSubValue(value_s,_T("resample"), value_sub,1))
		{
			m_List.SetCheckbox(resample, 0, 1);
			int type = 0, rp = 16;
			if(m_cfg->GetSubValue(value_s,_T("resample"), value_sub,3))
			{
				if(value_sub  == _T("0"))
					type = 1;
				else if(value_sub  == _T("2"))
					type = 3;
				else
					type = 2;
			}
			if(value_sub  == _T("8000"))
				rp = 0;
			else if(value_sub  == _T("16000"))
				rp = 4;
			else if(value_sub  == _T("22050"))
				rp = 8;
			else if(value_sub  == _T("32000"))
				rp = 12;
			else if(value_sub  == _T("48000"))
				rp = 20;
			else if(value_sub  == _T("64000"))
				rp = 24;
			else if(value_sub  == _T("96000"))
				rp = 28;
			else
				rp = 16;
			rp += type;
			m_List.SetComboBox(resample, 2, TRUE,  &m_resample,  8,  rp,  FALSE);
		}
	}
	if(m_cfg->GetValue_String(_T("af-adv"),value_s))
	{
		if(m_cfg->GetSubValue(value_s,_T("force"), value_sub))
		{
			m_List.SetCheckbox(adv_af, 0, 1);
			if(value_sub == _T("2"))
				m_List.SetComboBox(adv_af, 2, TRUE,  &m_adv_af,  5,  2,  FALSE);
			else if(value_sub == _T("1"))
				m_List.SetComboBox(adv_af, 2, TRUE,  &m_adv_af,  5,  1,  FALSE);
			else
				m_List.SetComboBox(adv_af, 2, TRUE,  &m_adv_af,  5,  0,  FALSE);
		}
	}
	m_List.UnlockWindowUpdate();
	UpdateData(FALSE);
}

void CMAudioPage::SaveConfig()
{
	if(!m_cfg)
		return;
	UpdateData(TRUE);
	
	m_List.LockWindowUpdate();
	
	int vao = m_audio.GetCurSel();
	switch (vao)
	{
	case win32:
		m_cfg->SetValue(_T("ao") ,_T("win32") );
		break;
	case pcm:
		m_cfg->SetValue(_T("ao") ,_T("pcm") );
		break;
	case ao_null:
		m_cfg->SetValue(_T("ao") ,_T("null") );
		break;
	default:
		m_cfg->SetValue(_T("ao") ,_T("dsound") );
	}
	
	int vchannels = m_channels.GetCurSel();
	switch (vchannels)
	{
	case ch_2:
		m_cfg->SetValue(_T("channels") ,_T("2") );
		break;
	case ch_4:
		m_cfg->SetValue(_T("channels") ,_T("4") );
		break;
	case ch_6:
		m_cfg->SetValue(_T("channels") ,_T("6") );
		break;
	default:
		m_cfg->RemoveValue(_T("channels"));
	}
	
	if(m_ass)
		m_cfg->SetValue(_T("ass"),_T("yes"));
	else
		m_cfg->RemoveValue(_T("ass"));
	
	if(m_dvdsub)
		m_cfg->SetValue(_T("spuaa"),_T("4"));
	else
		m_cfg->RemoveValue(_T("spuaa"));
	
	
	if(m_volnorm_s > 10 && m_volnorm_s <= 100)
	{
		m_cfg->SetValue(_T("softvol"), _T("yes"));
		m_volnorm.Format(_T("%d"),m_volnorm_s * 10);
		m_cfg->SetValue(_T("softvol-max"), m_volnorm);
	}
	else
	{
		m_cfg->RemoveValue(_T("softvol"));
		m_cfg->RemoveValue(_T("softvol-max"));
	}
	
	int vsub_error = _ttoi(m_sub_error);
	if(vsub_error > 0 && vsub_error <= 500)
		m_cfg->SetValue(_T("sub-ignore-errors"), m_sub_error);
	else
		m_cfg->RemoveValue(_T("sub-ignore-errors"));
	
	int vsubpos = _ttoi(m_subpos);
	if(vsubpos >= 0 && vsubpos <= 100)
		m_cfg->SetValue(_T("subpos"), m_subpos);
	else
		m_cfg->RemoveValue(_T("subpos"));
	
	if(m_volume_s >= 0 && m_volume_s <= 100)
	{
		m_volume.Format(_T("%d"),m_volume_s);
		m_cfg->SetValue(_T("Volume"), m_volume,true, ex_status);
	}
	else
		m_cfg->SetValue(_T("Volume"), _T("60"),true, ex_status);
	
	if(StringToDouble(m_audio_delay) != 0.0)
		m_cfg->SetValue(_T("delay"), m_audio_delay);
	else
		m_cfg->RemoveValue(_T("delay"));
	
	if(StringToDouble(m_sub_delay) != 0.0)
		m_cfg->SetValue(_T("subdelay"), m_sub_delay);
	else
		m_cfg->RemoveValue(_T("subdelay"));
	
	if(m_font2 == _T(""))
		m_cfg->SetValue(_T("subfont"), _T("\"") + m_font + _T("\""));
	else
		m_cfg->SetValue(_T("subfont"), _T("\"") + m_font + _T(",") + m_font2 +  _T("\""));
	
	if(m_size_s != _T(""))
		m_cfg->SetValue(_T("subfont-text-scale"),  m_size_s );
	else
		m_cfg->RemoveValue(_T("subfont-text-scale"));
		
	if(m_color != _T("Ĭ����ɫ"))
		m_cfg->SetValue(_T("ass-color"),  m_color );
	else
		m_cfg->RemoveValue(_T("ass-color"));
	
	if(m_bcolor != _T("Ĭ����ɫ"))
		m_cfg->SetValue(_T("ass-border-color"),  m_bcolor );
	else
		m_cfg->RemoveValue(_T("ass-border-color"));
	
	if(m_slang != _T(""))
		m_cfg->SetValue(_T("slang"),  m_slang );
	else
		m_cfg->RemoveValue(_T("slang"));
	
	if(m_subcp != _T(""))
		m_cfg->SetValue(_T("subcp"),  m_subcp );
	else
		m_cfg->SetValue(_T("subcp"),  _T("GBK,BIG-5,CP932,CP949,UTF-8,UTF-16") );

	int vautoscale = m_autoscale.GetCurSel();
	switch (vautoscale)
	{
	case 0:
		m_cfg->SetValue(_T("subfont-autoscale") ,_T("0") );
		break;
	case 1:
		m_cfg->SetValue(_T("subfont-autoscale") ,_T("1") );
		break;
	case 2:
		m_cfg->SetValue(_T("subfont-autoscale") ,_T("2") );
		break;
	default:
		m_cfg->SetValue(_T("subfont-autoscale") ,_T("3") );
	}
	
	int vfuzziness = m_fuzziness.GetCurSel();
	switch (vfuzziness)
	{
	case 0:
		m_cfg->SetValue(_T("sub-fuzziness") ,_T("0") );
		break;
	case 2:
		m_cfg->SetValue(_T("sub-fuzziness") ,_T("2") );
		break;
	default:
		m_cfg->SetValue(_T("sub-fuzziness") ,_T("1") );
	}
	
	int valign = m_align.GetCurSel();
	switch (valign)
	{
	case 0:
		m_cfg->SetValue(_T("subalign") ,_T("0") );
		m_cfg->SetValue(_T("spualign") ,_T("0") );
		break;
	case 2:
		m_cfg->SetValue(_T("subalign") ,_T("2") );
		m_cfg->SetValue(_T("spualign") ,_T("2") );
		break;
	default:
		m_cfg->SetValue(_T("subalign") ,_T("1") );
		m_cfg->SetValue(_T("spualign") ,_T("1") );
	}
	if(m_List.GetCheckbox(adv_af, 0))
	{
		CString str = m_List.GetItemText(adv_af, 2);
		if(str == _T("�������Զ�ѡ��"))
			m_cfg->SetValue(_T("af-adv"), _T("force=0"));
		else if(str == _T("�����Ż�"))
			m_cfg->SetValue(_T("af-adv"), _T("force=1"));
		else
			m_cfg->SetValue(_T("af-adv"), _T("force=2"));
	}
	else
		m_cfg->RemoveValue(_T("af-adv"));
	
	CString af_str = _T("");
	if(m_List.GetCheckbox(volnormal, 0))
	{
		CString str= m_List.GetItemText(volnormal, 2);
		if(str == _T("������ƽ������"))
			af_str +=  _T("volnorm=2,");
		else
			af_str +=  _T("volnorm,");
	}
	if(m_List.GetCheckbox(equalizer, 0))
	{
		CString str= m_List.GetItemText(equalizer, 2);
		str.TrimLeft(_T(" "));
		str.TrimRight(_T(" "));
		if(str != _T(""))
			af_str +=  _T("equalizer=") + str  +  _T(",");
	}
	if(m_List.GetCheckbox(resample, 0))
	{
		CString str= m_List.GetItemText(resample, 2);
		if(str == _T("8kHz �Զ�"))
			af_str +=  _T("resample=8000,");
		else if(str == _T("8kHz ���Բ�ֵ,����Ʒ�ʵ�"))
			af_str +=  _T("resample=8000:1:0,");
		else if(str == _T("8kHz �������������������"))
			af_str +=  _T("resample=8000:1:1,");
		else if(str == _T("8kHz ����������鸡�㴦��"))
			af_str +=  _T("resample=8000:1:2,");
		else if(str == _T("16kHz �Զ�"))
			af_str +=  _T("resample=16000,");
		else if(str == _T("16kHz ���Բ�ֵ,����Ʒ�ʵ�"))
			af_str +=  _T("resample=16000:1:0,");
		else if(str == _T("16kHz �������������������"))
			af_str +=  _T("resample=16000:1:1,");
		else if(str == _T("16kHz ����������鸡�㴦��"))
			af_str +=  _T("resample=16000:1:2,");
		else if(str == _T("22.05kHz �Զ�"))
			af_str +=  _T("resample=22050,");
		else if(str == _T("22.05kHz ���Բ�ֵ,����Ʒ�ʵ�"))
			af_str +=  _T("resample=22050:1:0,");
		else if(str == _T("22.05kHz �������������������"))
			af_str +=  _T("resample=22050:1:1,");
		else if(str == _T("22.05kHz ����������鸡�㴦��"))
			af_str +=  _T("resample=22050:1:2,");
		else if(str == _T("32kHz �Զ�"))
			af_str +=  _T("resample=32000,");
		else if(str == _T("32kHz ���Բ�ֵ,����Ʒ�ʵ�"))
			af_str +=  _T("resample=32000:1:0,");
		else if(str == _T("32kHz �������������������"))
			af_str +=  _T("resample=32000:1:1,");
		else if(str == _T("32kHz ����������鸡�㴦��"))
			af_str +=  _T("resample=32000:1:2,");
		else if(str == _T("44.1kHz ���Բ�ֵ,����Ʒ�ʵ�"))
			af_str +=  _T("resample=44100:1:0,");
		else if(str == _T("44.1kHz �������������������"))
			af_str +=  _T("resample=44100:1:1,");
		else if(str == _T("44.1kHz ����������鸡�㴦��"))
			af_str +=  _T("resample=44100:1:2,");
		else if(str == _T("48kHz �Զ�"))
			af_str +=  _T("resample=48000,");
		else if(str == _T("48kHz ���Բ�ֵ,����Ʒ�ʵ�"))
			af_str +=  _T("resample=48000:1:0,");
		else if(str == _T("48kHz �������������������"))
			af_str +=  _T("resample=48000:1:1,");
		else if(str == _T("48kHz ����������鸡�㴦��"))
			af_str +=  _T("resample=48000:1:2,");
		else if(str == _T("64kHz �Զ�"))
			af_str +=  _T("resample=64000,");
		else if(str == _T("64kHz ���Բ�ֵ,����Ʒ�ʵ�"))
			af_str +=  _T("resample=64000:1:0,");
		else if(str == _T("64kHz �������������������"))
			af_str +=  _T("resample=64000:1:1,");
		else if(str == _T("64kHz ����������鸡�㴦��"))
			af_str +=  _T("resample=64000:1:2,");
		else if(str == _T("96kHz �Զ�"))
			af_str +=  _T("resample=96000,");
		else if(str == _T("96kHz ���Բ�ֵ,����Ʒ�ʵ�"))
			af_str +=  _T("resample=96000:1:0,");
		else if(str == _T("96kHz �������������������"))
			af_str +=  _T("resample=96000:1:1,");
		else if(str == _T("96kHz ����������鸡�㴦��"))
			af_str +=  _T("resample=96000:1:2,");
		else
			af_str +=  _T("resample=44100,");
	}
	
	af_str.TrimRight(_T(","));
	if(af_str.GetLength() > 1)
		m_cfg->SetValue(_T("af"),  af_str);
	else
		m_cfg->RemoveValue(_T("af"));
	m_List.UnlockWindowUpdate();
}
	
BOOL CMAudioPage::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	switch(pMsg->message)
	{
	case   WM_KEYDOWN:
		switch(pMsg->wParam)
		{
		case   VK_RETURN:
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
