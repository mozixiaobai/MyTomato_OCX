// UDSGetImg.cpp : 实现文件
//

#include "stdafx.h"
#include "SmartFilm.h"
#include "UDSGetImg.h"
#include "afxdialogex.h"


// CUDSGetImg 对话框

IMPLEMENT_DYNAMIC(CUDSGetImg, CDialogEx)

CUDSGetImg::CUDSGetImg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSGetImg::IDD, pParent)
{

}

CUDSGetImg::~CUDSGetImg()
{
}

void CUDSGetImg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUDSGetImg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_ABRIGHT, &CUDSGetImg::OnCustomdrawSlidAbright)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_ACONTRAST, &CUDSGetImg::OnCustomdrawSlidAcontrast)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_AFOCUS, &CUDSGetImg::OnCustomdrawSlidAfocus)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_ALIGHT, &CUDSGetImg::OnCustomdrawSlidAlight)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_ADELAY, &CUDSGetImg::OnCustomdrawSlidAdelay)
	ON_CBN_SELCHANGE(IDC_CMB_ARES, &CUDSGetImg::OnSelchangeCmbAres)
	ON_CBN_SELCHANGE(IDC_CMB_AFORMAT, &CUDSGetImg::OnSelchangeCmbAformat)
	ON_COMMAND(IDC_RADIO_0, &CUDSGetImg::OnRadio0)
	ON_COMMAND(IDC_RADIO_90, &CUDSGetImg::OnRadio90)
	ON_COMMAND(IDC_RADIO_180, &CUDSGetImg::OnRadio180)
	ON_COMMAND(IDC_RADIO_270, &CUDSGetImg::OnRadio270)
	ON_BN_CLICKED(IDC_CHEK_ALEVEL, &CUDSGetImg::OnClickedChekAlevel)
	ON_BN_CLICKED(IDC_CHEK_AVERTICAL, &CUDSGetImg::OnClickedChekAvertical)
	ON_BN_CLICKED(IDC_CHEK_AWATER, &CUDSGetImg::OnClickedChekAwater)
END_MESSAGE_MAP()


// CUDSGetImg 消息处理程序


BOOL CUDSGetImg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_pParentWnd = GetParentOwner();
	m_hParentWnd = m_pParentWnd->m_hWnd;


	//2、获取配置文件路径
	m_strIniPath  = Self_GetMyDocument();
	m_strIniPath += _T("\\");
	m_strIniPath += _T("UDSXRayDataOcx");
	m_strIniPath += _T("\\");
	m_strTemDoc   = m_strIniPath;
	m_strTemDoc  += _T("xml");
	m_strIniPath += _T("BaseConfig.ini");

	//3、读取配置文件
	Self_ReadIni(m_strIniPath);

	//4、设置拍摄模式
	if (m_strLastTem==_T("透射稿"))
	{
		GetDlgItem(IDC_SLID_ABRIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLID_ACONTRAST)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLID_AFOCUS)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLID_ALIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLID_ADELAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_ADELAY)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_HDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_LDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_CAP)->EnableWindow(TRUE);
	} 
	else
	{
		GetDlgItem(IDC_SLID_ABRIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLID_ACONTRAST)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLID_AFOCUS)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLID_ALIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLID_ADELAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_ADELAY)->EnableWindow(FALSE);

		GetDlgItem(IDC_BTN_HDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_LDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_CAP)->EnableWindow(TRUE);
	}




	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CUDSGetImg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void CUDSGetImg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}


CString CUDSGetImg::Self_GetMyDocument(void)
{
	CString        tem_strMyDocument = _T("");
	TCHAR          tem_cMyDocument[MAX_PATH] = {0};
	LPITEMIDLIST   tem_Pid = NULL;
	SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &tem_Pid);
	if (tem_Pid && SHGetPathFromIDList(tem_Pid, tem_cMyDocument))
	{
		tem_strMyDocument = tem_cMyDocument;
		return tem_strMyDocument;
	}
	return tem_strMyDocument;
}


void CUDSGetImg::Self_ReadIni(CString inipath)
{
	int     tem_nRead      = 0;
	CString tem_strRead    =_T("");
	CString tem_strIniPath = inipath;

	::GetPrivateProfileString(_T("BaseSet"), _T("Template"), _T("没有找到Template信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strLastTem = tem_strRead;
	tem_nRead = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ResIndex"), _T("没有找到ResIndex信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastRes = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ImgType"), _T("没有找到ImgType信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastImgType = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("PreRotate"), _T("没有找到PreRotate信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastPreRotate = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("MergeMode"), _T("没有找到MergeMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastMergeMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterMark"), _T("没有找到WaterMark信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastWaterMark = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveDoc"), _T("没有找到主头SaveDoc信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strSaveDoc = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewMode"), _T("没有找到ViewMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead   = _ttoi(tem_strRead);
	m_nViewMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewLeft"), _T("没有找到ViewLeft信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead   = _ttoi(tem_strRead);
	m_lLeftSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewTop"), _T("没有找到ViewTop信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead  = _ttoi(tem_strRead);
	m_lTopSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewRight"), _T("没有找到ViewRight信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead    = _ttoi(tem_strRead);
	m_lRightSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewBottom"), _T("没有找到ViewBottom信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_lBottomSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("FocusValue"), _T("没有找到FocusValue信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nFocusValue = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("Computer"), _T("没有找到Computer信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nComputer = tem_nRead;
	tem_strRead.ReleaseBuffer();
}


//SliderCtrl控件-------------------------------------------------------------------
void CUDSGetImg::OnCustomdrawSlidAbright(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CUDSGetImg::OnCustomdrawSlidAcontrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CUDSGetImg::OnCustomdrawSlidAfocus(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CUDSGetImg::OnCustomdrawSlidAlight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CUDSGetImg::OnCustomdrawSlidAdelay(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


//Comboboc控件----------------------------------------------------------------------
void CUDSGetImg::OnSelchangeCmbAres()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CUDSGetImg::OnSelchangeCmbAformat()
{
	// TODO: 在此添加控件通知处理程序代码
}


//视频方向---------------------------------------------------------------------------
void CUDSGetImg::OnRadio0()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(_T(""));
}


void CUDSGetImg::OnRadio90()
{
	// TODO: 在此添加命令处理程序代码
}


void CUDSGetImg::OnRadio180()
{
	// TODO: 在此添加命令处理程序代码
}


void CUDSGetImg::OnRadio270()
{
	// TODO: 在此添加命令处理程序代码
}


//合并以及水印------------------------------------------------------------------------
void CUDSGetImg::OnClickedChekAlevel()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CUDSGetImg::OnClickedChekAvertical()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CUDSGetImg::OnClickedChekAwater()
{
	// TODO: 在此添加控件通知处理程序代码
}

