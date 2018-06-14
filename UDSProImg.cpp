// UDSProImg.cpp : 实现文件
//

#include "stdafx.h"
#include "SmartFilm.h"
#include "UDSProImg.h"
#include "afxdialogex.h"


extern HWND g_hMainHwnd;

// CUDSProImg 对话框

IMPLEMENT_DYNAMIC(CUDSProImg, CDialogEx)

CUDSProImg::CUDSProImg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSProImg::IDD, pParent)
{

	m_staBrit = 0;
	m_staCtst = 0;
	m_staGama = 0.0f;
}

CUDSProImg::~CUDSProImg()
{
}

void CUDSProImg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLID_BBRI, m_slidCBright);
	DDX_Control(pDX, IDC_SLID_BCONTRAST, m_slidCContrst);
	DDX_Control(pDX, IDC_SLID_BGAMA, m_slidCGama);
	DDX_Text(pDX, IDC_STA_BBRIV, m_staBrit);
	DDX_Text(pDX, IDC_STA_BCONTRASTV, m_staCtst);
	DDX_Text(pDX, IDC_STA_BGAMAV, m_staGama);
	DDX_Control(pDX, IDC_CMB_BLINEWIDTH, m_conLineWidth);
	DDX_Control(pDX, IDC_MFCCOLOR_BCOLOR, m_conColor);
	DDX_Control(pDX, IDC_CMB_BFONTSIZE, m_conFontSize);
	DDX_Control(pDX, IDC_CMB_CFONT, m_conFont);
}


BEGIN_MESSAGE_MAP(CUDSProImg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_BSAVE, &CUDSProImg::OnBnClickedBtnBsave)
	ON_BN_CLICKED(IDC_BTN_BBACKOUT, &CUDSProImg::OnBnClickedBtnBbackout)
	ON_BN_CLICKED(IDC_BTN_BREST, &CUDSProImg::OnBnClickedBtnBrest)
	ON_BN_CLICKED(IDC_BTN_BFITSCREEN, &CUDSProImg::OnBnClickedBtnBfitscreen)
	ON_BN_CLICKED(IDC_BTN_BORISIZE, &CUDSProImg::OnBnClickedBtnBorisize)
	ON_BN_CLICKED(IDC_BTN_BLROTATE, &CUDSProImg::OnBnClickedBtnBlrotate)
	ON_BN_CLICKED(IDC_BTN_BRROTATE, &CUDSProImg::OnBnClickedBtnBrrotate)
	ON_BN_CLICKED(IDC_BTN_BROTATE180, &CUDSProImg::OnBnClickedBtnBrotate180)
	ON_BN_CLICKED(IDC_BTN_BLMIRRO, &CUDSProImg::OnBnClickedBtnBlmirro)
	ON_BN_CLICKED(IDC_BTN_BVMIRRO, &CUDSProImg::OnBnClickedBtnBvmirro)
	ON_BN_CLICKED(IDC_BTN_BROTATESELF, &CUDSProImg::OnBnClickedBtnBrotateself)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_BBRI, &CUDSProImg::OnCustomdrawSlidBbri)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLID_BBRI, &CUDSProImg::OnReleasedcaptureSlidBbri)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_BCONTRAST, &CUDSProImg::OnCustomdrawSlidBcontrast)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLID_BCONTRAST, &CUDSProImg::OnReleasedcaptureSlidBcontrast)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_BGAMA, &CUDSProImg::OnCustomdrawSlidBgama)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLID_BGAMA, &CUDSProImg::OnReleasedcaptureSlidBgama)
	ON_BN_CLICKED(IDC_BTN_BMARKIT, &CUDSProImg::OnBnClickedBtnBmarkit)
	ON_BN_CLICKED(IDC_BTN_BARROW, &CUDSProImg::OnBnClickedBtnBarrow)
	ON_BN_CLICKED(IDC_BTN_BTEXT, &CUDSProImg::OnBnClickedBtnBtext)
	ON_BN_CLICKED(IDC_BTN_BCROP, &CUDSProImg::OnBnClickedBtnBcrop)
	ON_BN_CLICKED(IDC_BTN_BINVERT, &CUDSProImg::OnBnClickedBtnBinvert)
	ON_BN_CLICKED(IDC_BTN_BSHARP, &CUDSProImg::OnBnClickedBtnBsharp)
	ON_BN_CLICKED(IDC_BTN_SURE, &CUDSProImg::OnBnClickedBtnSure)
	ON_BN_CLICKED(IDC_BTN_UNSURE, &CUDSProImg::OnBnClickedBtnUnsure)
END_MESSAGE_MAP()


// CUDSProImg 消息处理程序


BOOL CUDSProImg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/**************************
	*
	* 1、变量初始化
	* 2、slider ctrl初始化
	* 3、static初始化
	* 4、button
	* 5、界面美化
	* 6、窗口语言初始化
	* 7、标注界面初始化
	* 8、标注参数初始化
	*
	**************************/
	
	/*1、变量初始化*/
	m_nBrit = 0;
	m_nCtst = 0;
	m_nSatr = 0;
	m_nGama = 0;
	m_nOperation = 0;

	/*2、slider ctrl初始化*/
	m_slidCBright.SetRange(-100, 100, TRUE);
	m_slidCBright.SetPos(0);
	m_slidCBright.SetPageSize(1);

	m_slidCContrst.SetRange(-100, 100, TRUE);
	m_slidCContrst.SetPos(0);
	m_slidCContrst.SetPageSize(1);

	m_slidCGama.SetRange(20, 400, TRUE);
	m_slidCGama.SetPos(100);
	m_slidCGama.SetPageSize(1);

	/*3、static初始化*/
	m_staBrit = 0;
	m_staCtst = 0;
	m_staGama = 0;
	UpdateData(FALSE);

	/*4、button*/
	GetDlgItem(IDC_BTN_SURE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_UNSURE)->EnableWindow(FALSE);

	/*7、标注界面初始化*/
	Self_SetCtrl(0);

	/*8、标注参数初始化*/
	m_nNote      = 0;
	m_nLineWidth = 5;
	m_conLineWidth.InsertString(0, _T("2"));
	m_conLineWidth.InsertString(1, _T("3"));
	m_conLineWidth.InsertString(2, _T("5"));
	m_conLineWidth.InsertString(3, _T("7"));
	m_conLineWidth.InsertString(4, _T("10"));
	m_conLineWidth.InsertString(5, _T("12"));
	m_conLineWidth.InsertString(6, _T("14"));
	m_conLineWidth.InsertString(7, _T("16"));
	m_conLineWidth.InsertString(8, _T("18"));
	m_conLineWidth.InsertString(9, _T("20"));
	m_conLineWidth.InsertString(10, _T("25"));
	m_conLineWidth.InsertString(11, _T("30"));
	m_conLineWidth.SetCurSel(2);

	m_clrLineColor = 255;
	m_conColor.SetColor(m_clrLineColor);
	m_conColor.SetColumnsNumber(3);

	m_nFontSize = 120;
	m_conFontSize.InsertString(0, _T("10"));
	m_conFontSize.InsertString(1, _T("20"));
	m_conFontSize.InsertString(2, _T("30"));
	m_conFontSize.InsertString(3, _T("40"));
	m_conFontSize.InsertString(4, _T("50"));
	m_conFontSize.InsertString(5, _T("70"));
	m_conFontSize.InsertString(6, _T("90"));
	m_conFontSize.InsertString(7, _T("120"));
	m_conFontSize.InsertString(8, _T("150"));
	m_conFontSize.InsertString(9, _T("200"));
	m_conFontSize.SetCurSel(7);

	m_strFont = _T("宋体");
	m_conFont.InsertString(0, _T("Arial"));
	m_conFont.InsertString(1, _T("Calibri"));
	m_conFont.InsertString(2, _T("Times New Roman"));
	m_conFont.InsertString(3, _T("宋体"));
	m_conFont.InsertString(4, _T("楷体"));
	m_conFont.InsertString(5, _T("仿宋"));
	m_conFont.InsertString(6, _T("黑体"));
	m_conFont.InsertString(7, _T("隶书"));
	m_conFont.InsertString(8, _T("微软雅黑"));
	m_conFont.InsertString(9, _T("新宋体"));
	m_conFont.SetCurSel(3);

	m_BBold = FALSE;
	((CButton*)GetDlgItem(IDC_CHK_BBOLD))->SetCheck(m_BBold);

	m_BItalic = FALSE;
	((CButton*)GetDlgItem(IDC_CHK_BITALIC))->SetCheck(m_BItalic);

	m_strInfo = _T("");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CUDSProImg::Self_SetCtrl(int index)
{
	if (index == 0)
	{
		GetDlgItem(IDC_STA_BLINEWIDTH)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_CMB_BLINEWIDTH)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STA_CFONT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMB_CFONT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STA_BLINEWIDTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_BLINEWIDTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_STA_BLINECOLOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_MFCCOLOR_BCOLOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_STA_BFONTSIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_BFONTSIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_BBOLD)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_BITALIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_STA_BTEXTINFO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_BTEXTINFO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BADDTEXT)->EnableWindow(FALSE);	
		GetDlgItem(IDC_BTN_BBACKUP2)->EnableWindow(FALSE);

	}
	else if (index == 1)
	{
		GetDlgItem(IDC_STA_BLINEWIDTH)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_CMB_BLINEWIDTH)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_STA_CFONT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMB_CFONT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMB_CFONT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_BLINEWIDTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_MFCCOLOR_BCOLOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_BFONTSIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_BBOLD)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_BITALIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_BTEXTINFO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BADDTEXT)->EnableWindow(FALSE);	

		CRect  tem_rcRect;
		GetDlgItem(IDC_STA_BLINEWIDTH)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BLINECOLOR)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);	

		GetDlgItem(IDC_STA_BFONTSIZE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BTEXTINFO)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);
	}
	else if (index == 2)
	{
		GetDlgItem(IDC_STA_BLINEWIDTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMB_BLINEWIDTH)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STA_CFONT)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_CMB_CFONT)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_CMB_BLINEWIDTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_CFONT)->EnableWindow(TRUE);
		GetDlgItem(IDC_MFCCOLOR_BCOLOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_BFONTSIZE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_BBOLD)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_BITALIC)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_BTEXTINFO)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_BADDTEXT)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_BBACKUP2)->EnableWindow(TRUE);

		CRect  tem_rcRect;
		GetDlgItem(IDC_STA_CFONT)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BLINECOLOR)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BFONTSIZE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BTEXTINFO)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);
	}
}


void CUDSProImg::OnBnClickedBtnBsave()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 0, 0);
}


void CUDSProImg::OnBnClickedBtnBbackout()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 1, 0);
}


void CUDSProImg::OnBnClickedBtnBrest()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 2, 0);
}


void CUDSProImg::OnBnClickedBtnBfitscreen()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 3, 0);
}


void CUDSProImg::OnBnClickedBtnBorisize()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 4, 0);
}


void CUDSProImg::OnBnClickedBtnBlrotate()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 5, 0);
}


void CUDSProImg::OnBnClickedBtnBrrotate()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 6, 0);
}


void CUDSProImg::OnBnClickedBtnBrotate180()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 7, 0);
}


void CUDSProImg::OnBnClickedBtnBlmirro()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 8, 0);
}


void CUDSProImg::OnBnClickedBtnBvmirro()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 9, 0);
}


void CUDSProImg::OnBnClickedBtnBrotateself()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 10, 0);
	m_nOperation = 10;
}


void CUDSProImg::OnCustomdrawSlidBbri(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nBrit   = m_slidCBright.GetPos();
	m_staBrit = m_nBrit;
	UpdateData(FALSE);

	*pResult = 0;
}


void CUDSProImg::OnReleasedcaptureSlidBbri(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 11, m_nBrit);
	m_nOperation = 11;

	*pResult = 0;
}


void CUDSProImg::OnCustomdrawSlidBcontrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nCtst   = m_slidCContrst.GetPos();
	m_staCtst = m_nCtst;
	UpdateData(FALSE);

	*pResult = 0;
}


void CUDSProImg::OnReleasedcaptureSlidBcontrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 12, m_nCtst);
	m_nOperation = 12;

	*pResult = 0;
}


void CUDSProImg::OnCustomdrawSlidBgama(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nGama   = m_slidCGama.GetPos();
	m_staGama = (float)m_nGama*1.0/100;
	UpdateData(FALSE);

	*pResult = 0;
}


void CUDSProImg::OnReleasedcaptureSlidBgama(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 13, m_nGama);
	m_nOperation = 13;

	*pResult = 0;
}


void CUDSProImg::OnBnClickedBtnBmarkit()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 14, 0);
	m_nOperation = 14;
}


void CUDSProImg::OnBnClickedBtnBarrow()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 15, 0);
	m_nOperation = 15;
}


void CUDSProImg::OnBnClickedBtnBtext()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 16, 0);
	m_nOperation = 16;
}


void CUDSProImg::OnBnClickedBtnBcrop()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 17, 0);
}


void CUDSProImg::OnBnClickedBtnBinvert()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 18, 0);
}


void CUDSProImg::OnBnClickedBtnBsharp()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 19, 0);
}


void CUDSProImg::Self_ResetSlider(int mode)
{
	if (mode == 0)
	{
		m_slidCBright.SetPos(0);
	} 
	else if (mode == 1)
	{
		m_slidCContrst.SetPos(0);
	} 
	else
	{
		m_slidCGama.SetPos(100);
	}
	GetDlgItem(IDC_BTN_SURE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_UNSURE)->ShowWindow(SW_HIDE);
}


BOOL CUDSProImg::Self_DisableCtrl(int index)
{
	switch(index)
	{
	case 0:
		GetDlgItem(IDC_BTN_BSAVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BBACKOUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BREST)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BFITSCREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BORISIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BLROTATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BRROTATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BROTATE180)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BLMIRRO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BVMIRRO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BROTATESELF)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BCROP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BINVERT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BSHARP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SURE)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_BTN_UNSURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_UNSURE)->ShowWindow(SW_NORMAL);

		//标注项控件状态
		GetDlgItem(IDC_BTN_BMARKIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BARROW)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BTEXT)->EnableWindow(FALSE);
		m_nNote = 0;
		Self_SetCtrl(m_nNote);
		break;
	case 1:
		GetDlgItem(IDC_BTN_BSAVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BBACKOUT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BREST)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BFITSCREEN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BORISIZE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BLROTATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BRROTATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BROTATE180)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BLMIRRO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BVMIRRO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BROTATESELF)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BCROP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BINVERT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BSHARP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SURE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SURE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_UNSURE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_UNSURE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLID_BBRI)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLID_BCONTRAST)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLID_BGAMA)->EnableWindow(TRUE);

		//标注项控件状态
		GetDlgItem(IDC_BTN_BMARKIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BARROW)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_BTEXT)->EnableWindow(TRUE);
		m_nNote = 0;
		Self_SetCtrl(m_nNote);
		break;
	case 2:
		GetDlgItem(IDC_BTN_BSAVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BBACKOUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BREST)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BFITSCREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BORISIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BLROTATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BRROTATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BROTATE180)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BLMIRRO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BVMIRRO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BROTATESELF)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BCROP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BINVERT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BSHARP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SURE)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_BTN_UNSURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_UNSURE)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_SLID_BBRI)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLID_BCONTRAST)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLID_BGAMA)->EnableWindow(FALSE);

		//标注项控件状态
		GetDlgItem(IDC_BTN_BMARKIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BARROW)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BTEXT)->EnableWindow(FALSE);
		m_nNote = 0;
		Self_SetCtrl(m_nNote);
		break;
	case 3:
		GetDlgItem(IDC_BTN_BSAVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BBACKOUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BREST)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BFITSCREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BORISIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BLROTATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BRROTATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BROTATE180)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BLMIRRO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BVMIRRO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BROTATESELF)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BCROP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BINVERT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BSHARP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SURE)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_BTN_UNSURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_UNSURE)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_SLID_BBRI)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLID_BCONTRAST)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLID_BGAMA)->EnableWindow(FALSE);
		break;
	}
	return 0;
}


void CUDSProImg::OnBnClickedBtnSure()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nOperation == 11 || m_nOperation == 12 || m_nOperation == 13)
	{
		m_slidCBright.SetPos(0);
		m_slidCContrst.SetPos(0);
		m_slidCGama.SetPos(100);
	}
	else if (m_nOperation == 14 || m_nOperation == 15 || m_nOperation == 16)
	{
		m_nNote = 0;
	}

	Self_DisableCtrl(1);
	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 20, m_nOperation);
}


void CUDSProImg::OnBnClickedBtnUnsure()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nOperation == 11 || m_nOperation == 12 || m_nOperation == 13)
	{
		m_slidCBright.SetPos(0);
		m_slidCContrst.SetPos(0);
		m_slidCGama.SetPos(100);
	}
	else if (m_nOperation == 14 || m_nOperation == 15 || m_nOperation == 16)
	{
		m_nNote = 0;
	}

	Self_DisableCtrl(1);

	::SendMessage(g_hMainHwnd, WM_IMGPROCESS, 21, m_nOperation);
}
