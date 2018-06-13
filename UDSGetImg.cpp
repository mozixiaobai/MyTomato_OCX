// UDSGetImg.cpp : 实现文件
//

#include "stdafx.h"
#include "SmartFilm.h"
#include "UDSGetImg.h"
#include "afxdialogex.h"


extern CString  g_strProXmlPath;
extern CString  g_strDocXmlPath;        
extern std::vector<CString> g_vcRes;
extern HWND g_hMainHwnd;

// CUDSGetImg 对话框

IMPLEMENT_DYNAMIC(CUDSGetImg, CDialogEx)

CUDSGetImg::CUDSGetImg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSGetImg::IDD, pParent)
{

	m_staComputerD = _T("");
}

CUDSGetImg::~CUDSGetImg()
{
}

void CUDSGetImg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLID_ABRIGHT, m_slidABright);
	DDX_Control(pDX, IDC_SLID_ACONTRAST, m_slidAContrast);
	DDX_Control(pDX, IDC_SLID_ALIGHT, m_slidALightBox);
	DDX_Control(pDX, IDC_CMB_ARES, m_conResolution);
	DDX_Control(pDX, IDC_CMB_AFORMAT, m_conImgType);
	DDX_Control(pDX, IDC_SLID_AFOCUS, m_slidAdjFocus);
	DDX_Control(pDX, IDC_SLID_ADELAY, m_slidComputer);
	DDX_Text(pDX, IDC_STA_ADELAYV, m_staComputerD);
	DDX_Control(pDX, IDC_EDIT_SHOWINFO, m_conEditInfo);
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
	ON_BN_CLICKED(IDC_BTN_HDR, &CUDSGetImg::OnBnClickedBtnHdr)
	ON_BN_CLICKED(IDC_BTN_DEFAULT, &CUDSGetImg::OnBnClickedBtnDefault)
	ON_BN_CLICKED(IDC_BTN_DIR, &CUDSGetImg::OnBnClickedBtnDir)
	ON_BN_CLICKED(IDC_BTN_WATER, &CUDSGetImg::OnBnClickedBtnWater)
	ON_BN_CLICKED(IDC_BTN_NAME, &CUDSGetImg::OnBnClickedBtnName)
	ON_COMMAND(IDC_RADIO_MANUAL, &CUDSGetImg::OnRadioManual)
	ON_COMMAND(IDC_RADIO_SCAN, &CUDSGetImg::OnRadioScan)
	ON_BN_CLICKED(IDC_BTN_LDR, &CUDSGetImg::OnBnClickedBtnLdr)
	ON_BN_CLICKED(IDC_BTN_CAP, &CUDSGetImg::OnBnClickedBtnCap)
	ON_BN_CLICKED(IDC_CHK_ADELAY, &CUDSGetImg::OnClickedChkAdelay)
END_MESSAGE_MAP()


// CUDSGetImg 消息处理程序


BOOL CUDSGetImg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

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

	//4、设置拍摄模式，以及slider初始化
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

		Self_SetSlider(g_strProXmlPath);
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

		Self_SetSlider(g_strDocXmlPath);
	}

	//5、分辨率、图像格式初始化
	int tem_nResIndex = 0;
	std::vector<CString>::iterator  item_res;
	for (item_res=g_vcRes.begin(); item_res!=g_vcRes.end(); item_res++, tem_nResIndex++)
	{
		m_conResolution.InsertString(tem_nResIndex, *item_res);
	}
	m_conResolution.SetCurSel(m_nLastRes);

	m_conImgType.InsertString(0, _T("bmp"));
	m_conImgType.InsertString(1, _T("jpg"));
	m_conImgType.InsertString(2, _T("png"));
	m_conImgType.InsertString(3, _T("tif"));
	m_conImgType.InsertString(4, _T("pdf"));
	m_conImgType.InsertString(5, _T("dcm"));
	m_conImgType.SetCurSel(m_nLastImgType);

	//6、radio初始化
	switch(m_nLastPreRotate)
	{
	case 0:
		((CButton*)GetDlgItem(IDC_RADIO_0))->SetCheck(TRUE);

		break;
	case 1:
		((CButton*)GetDlgItem(IDC_RADIO_90))->SetCheck(TRUE);
		break;
	case 2:
		((CButton*)GetDlgItem(IDC_RADIO_180))->SetCheck(TRUE);
		break;
	case 3:
		((CButton*)GetDlgItem(IDC_RADIO_270))->SetCheck(TRUE);
		break;
	default:
		((CButton*)GetDlgItem(IDC_RADIO_0))->SetCheck(TRUE);
		break;
	}

	//7、合并方式、水印初始化
	switch(m_nLastMergeMode)
	{
	case 0:
		((CButton*)GetDlgItem(IDC_CHEK_ALEVEL))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHEK_AVERTICAL))->SetCheck(FALSE);
		break;
	case 1:
		((CButton*)GetDlgItem(IDC_CHEK_ALEVEL))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHEK_AVERTICAL))->SetCheck(FALSE);
		break;
	case 2:
		((CButton*)GetDlgItem(IDC_CHEK_ALEVEL))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHEK_AVERTICAL))->SetCheck(TRUE);
		break;
	default:
		((CButton*)GetDlgItem(IDC_CHEK_ALEVEL))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHEK_AVERTICAL))->SetCheck(FALSE);
		break;
	}

	if (m_nLastWaterMark==1)
	{
		((CButton*)GetDlgItem(IDC_CHEK_AWATER))->SetCheck(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHEK_AWATER))->SetCheck(FALSE);
	}

	//8、EditCtrl初始化

	//9、框选模式初始化
	if (m_nViewMode == 0)
	{
		((CButton*)GetDlgItem(IDC_RADIO_MANUAL))->SetCheck(TRUE);
	} 
	else if(m_nViewMode == 1)
	{
		((CButton*)GetDlgItem(IDC_RADIO_MANUAL))->SetCheck(TRUE);
	}
	else if (m_nViewMode == 2)
	{
		((CButton*)GetDlgItem(IDC_RADIO_MANUAL))->SetCheck(FALSE);
	}
	else if (m_nViewMode == 3)
	{
		((CButton*)GetDlgItem(IDC_RADIO_MANUAL))->SetCheck(FALSE);
	}

	//10、调焦控件初始化
	m_slidAdjFocus.SetRange(0, 255, TRUE);
	m_slidAdjFocus.SetPageSize(1);
	m_slidAdjFocus.SetPos(m_nFocusValue);

	//11、电脑性能初始化
	m_slidComputer.SetRange(1, 20, TRUE);
	if (m_nComputer == 0)
	{
		//先将区域设置为全区
		m_slidComputer.SetPos(10);
		m_slidComputer.SetPageSize(1);
		((CButton*)GetDlgItem(IDC_CHK_ADELAY))->SetCheck(TRUE);
		GetDlgItem(IDC_SLID_ADELAY)->EnableWindow(FALSE);		

		m_staComputerD = _T("10");
		UpdateData(FALSE);
		//再将区域恢复为固定
	} 
	else
	{
		m_slidComputer.SetPos(m_nComputer);
		m_slidComputer.SetPageSize(1);
		((CButton*)GetDlgItem(IDC_CHK_ADELAY))->SetCheck(FALSE);
		GetDlgItem(IDC_SLID_ADELAY)->EnableWindow(TRUE);
		m_staComputerD.Format(_T("%d"), m_nComputer);
		UpdateData(FALSE);
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

//Some Functions------------------------------------------------------------------
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


void CUDSGetImg::Self_SetSlider(CString xmlpath)
{
	int              tem_nAuto     = 0;
	int              tem_nSetValue = 0;
	int              tem_nMaxValue = 0;
	int              tem_nMinValue = 0;
	const char*      tem_cInfo;

	CStringA    tem_straXmlPath(xmlpath);
	const char* tem_cXmlPath = tem_straXmlPath.GetString();

	TiXmlDocument    tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);


	TiXmlElement*    tem_xmlRootElt = tem_xmlDoc.RootElement();
	TiXmlElement*    tem_xmlChildElt= tem_xmlRootElt->FirstChildElement();
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	TiXmlAttribute*  tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMaxValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMinValue  = tem_xmlChildAtb->IntValue();

	m_slidABright.SetRange(tem_nMinValue, tem_nMaxValue);
	m_slidABright.SetPos(tem_nSetValue);
	m_slidABright.SetPageSize(1);
	CString tem_strSetValue = _T("");
	tem_strSetValue.Format(_T("%d"), tem_nSetValue);
	GetDlgItem(IDC_STA_ABRIGHTV)->SetWindowText(tem_strSetValue);
	m_slidABright.EnableWindow(TRUE);


	for(int i=0; i<10; i++)
	{
		tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	}
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMaxValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMinValue  = tem_xmlChildAtb->IntValue();

	m_slidAContrast.SetRange(tem_nMinValue, tem_nMaxValue);
	m_slidAContrast.SetPos(tem_nSetValue);
	m_slidAContrast.SetPageSize(1);
	tem_strSetValue.Format(_T("%d"), tem_nSetValue);
	GetDlgItem(IDC_STA_ACONTRASTV)->SetWindowText(tem_strSetValue);
	m_slidAContrast.EnableWindow(TRUE);

	for(int i=0; i<5; i++)
	{
		tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	}
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMaxValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMinValue  = tem_xmlChildAtb->IntValue();

	m_slidALightBox.SetRange(tem_nMinValue, tem_nMaxValue);
	m_slidALightBox.SetPos(tem_nSetValue);
	m_slidALightBox.SetPageSize(1);
	tem_strSetValue.Format(_T("%d"), tem_nSetValue);
	GetDlgItem(IDC_STA_ALIGHTV)->SetWindowText(tem_strSetValue);

	//灰阶-----------------------------------------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//HDR开关
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//合并方式
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//灯箱偏移
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//延时
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//灰阶
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//反射稿开关
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	if (tem_xmlChildAtb->IntValue() == 0)
	{
		//反射稿关闭，透射稿必打开
		m_BDocMode = FALSE;
		m_nViewMode = 0;
	}
	else
	{
		//反射稿打开
		m_BDocMode = TRUE;
		m_nViewMode = 3;
	}

	//图像分辨率
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();

	//图像格式
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
}


//SliderCtrl控件-------------------------------------------------------------------
void CUDSGetImg::OnCustomdrawSlidAbright(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int tem_nCurSel = m_slidABright.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), tem_nCurSel);
	GetDlgItem(IDC_STA_ABRIGHTV)->SetWindowText(tem_strValue);

	::SendMessage(g_hMainHwnd, WM_SCANSET, 1, tem_nCurSel);
	m_nLastBright = tem_nCurSel;

	*pResult = 0;
}


void CUDSGetImg::OnCustomdrawSlidAcontrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int  tem_nCurSel = m_slidAContrast.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), tem_nCurSel);
	GetDlgItem(IDC_STA_ACONTRASTV)->SetWindowText(tem_strValue);

	::SendMessage(g_hMainHwnd, WM_SCANSET, 2, tem_nCurSel);
	m_nLastContrast = tem_nCurSel;

	*pResult = 0;
}


void CUDSGetImg::OnCustomdrawSlidAfocus(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int     tem_nCurSel = m_slidAdjFocus.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), tem_nCurSel);
	GetDlgItem(IDC_STA_AFOCUSV)->SetWindowText(tem_strValue);
	::SendMessage(g_hMainHwnd, WM_SCANSET, 4, tem_nCurSel);

	*pResult = 0;
}


void CUDSGetImg::OnCustomdrawSlidAlight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int     tem_nCurSel = m_slidALightBox.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), tem_nCurSel);
	GetDlgItem(IDC_STA_ALIGHTV)->SetWindowText(tem_strValue);
	::SendMessage(g_hMainHwnd, WM_SCANSET, 3, tem_nCurSel);
	m_nLastLightBox = tem_nCurSel;

	*pResult = 0;
}


void CUDSGetImg::OnCustomdrawSlidAdelay(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED != IsDlgButtonChecked(IDC_CHK_ADELAY))
	{
		int tem_nCurSel = m_slidComputer.GetPos();
		CString tem_strValue = _T("");
		tem_strValue.Format(_T("%d"), tem_nCurSel);
		GetDlgItem(IDC_STA_ADELAYV)->SetWindowText(tem_strValue);
		::SendMessage(g_hMainHwnd, WM_SCANSET, 5, tem_nCurSel);
		m_nComputer = tem_nCurSel;
	}

	*pResult = 0;
}


//Comboboc控件----------------------------------------------------------------------
void CUDSGetImg::OnSelchangeCmbAres()
{
	// TODO: 在此添加控件通知处理程序代码
	int tem_nCurSel = m_conResolution.GetCurSel();
	if (tem_nCurSel==m_nLastRes)
	{
		return;
	}
	::SendMessage(g_hMainHwnd, WM_SCANSET, 6, tem_nCurSel);
	m_nLastRes = tem_nCurSel;	
}


void CUDSGetImg::OnSelchangeCmbAformat()
{
	// TODO: 在此添加控件通知处理程序代码
	int tem_nCurSel = m_conImgType.GetCurSel();
	if (tem_nCurSel==m_nLastRes)
	{
		return;
	}
	::SendMessage(g_hMainHwnd, WM_SCANSET, 7, tem_nCurSel);
	m_nLastRes = tem_nCurSel;	
}


void CUDSGetImg::OnBnClickedBtnDefault()
{
	// TODO: 在此添加控件通知处理程序代码
	Self_SetSlider(g_strProXmlPath);
	::SendMessage(g_hMainHwnd, WM_SCANSET, 8, 0);
}


//视频方向---------------------------------------------------------------------------
void CUDSGetImg::OnRadio0()
{
	// TODO: 在此添加命令处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_0))
	{
		int     tem_nCurSel   = 0;
		::SendMessage(g_hMainHwnd, WM_SCANSET, 9, tem_nCurSel);
	} 
}


void CUDSGetImg::OnRadio90()
{
	// TODO: 在此添加命令处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_90))
	{
		int     tem_nCurSel   = 1;
		::SendMessage(g_hMainHwnd, WM_SCANSET, 9, tem_nCurSel);
	} 
}


void CUDSGetImg::OnRadio180()
{
	// TODO: 在此添加命令处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_180))
	{
		int     tem_nCurSel = 2;
		::SendMessage(g_hMainHwnd, WM_SCANSET, 9, tem_nCurSel);
	} 
}


void CUDSGetImg::OnRadio270()
{
	// TODO: 在此添加命令处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_270))
	{
		int     tem_nCurSel = 3;
		::SendMessage(g_hMainHwnd, WM_SCANSET, 9, tem_nCurSel);
	} 
}


//合并以及水印------------------------------------------------------------------------
void CUDSGetImg::OnClickedChekAlevel()
{
	// TODO: 在此添加控件通知处理程序代码
	int     tem_nCurSel   = 0;
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHEK_ALEVEL))
	{
		((CButton*)GetDlgItem(IDC_CHEK_AVERTICAL))->SetCheck(FALSE);
		tem_nCurSel = 1;
	}
	else
	{
		if (BST_CHECKED == IsDlgButtonChecked(IDC_CHEK_AVERTICAL))
		{
			tem_nCurSel = 2;
		}
		else
		{
			tem_nCurSel = 0;
		}
	}
	::SendMessage(g_hMainHwnd, WM_SCANSET, 10, tem_nCurSel);
}


void CUDSGetImg::OnClickedChekAvertical()
{
	// TODO: 在此添加控件通知处理程序代码
	int     tem_nCurSel   = 0;
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHEK_AVERTICAL))
	{
		((CButton*)GetDlgItem(IDC_CHEK_ALEVEL))->SetCheck(FALSE);
		tem_nCurSel = 2;
	}
	else
	{
		if (BST_CHECKED == IsDlgButtonChecked(IDC_CHEK_ALEVEL))
		{
			tem_nCurSel = 1;
		}
		else
		{
			tem_nCurSel = 0;
		}
	}
	::SendMessage(g_hMainHwnd, WM_SCANSET, 10, tem_nCurSel);
}


void CUDSGetImg::OnClickedChekAwater()
{
	// TODO: 在此添加控件通知处理程序代码
	//水印开关
	int tem_nCurSel   = 0;
	CString tem_strCurSel = _T("");
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHEK_AWATER))
	{
		tem_nCurSel = 1;
	} 
	else
	{
		tem_nCurSel = 0;
	}
	::SendMessage(g_hMainHwnd, WM_SCANSET, 12, tem_nCurSel);
	tem_strCurSel.Format(_T("%d"), tem_nCurSel);
	::WritePrivateProfileString(_T("BaseSet"), _T("WaterMark"), tem_strCurSel, m_strIniPath); 
}


void CUDSGetImg::OnBnClickedBtnWater()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_SCANSET, 13, 0);
}


void CUDSGetImg::OnBnClickedBtnDir()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_SCANSET, 11, 0);
}


void CUDSGetImg::OnBnClickedBtnName()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_SCANSET, 14, 0);
}


void CUDSGetImg::Self_ResetUI(CString xmlpath)
{
	int              tem_nOpen     = 0;
	int              tem_nAuto     = 0;
	int              tem_nSetValue = 0;
	int              tem_nMaxValue = 0;
	int              tem_nMinValue = 0;
	const char*      tem_cInfo;

	CStringA    tem_straXmlPath(xmlpath);
	const char* tem_cXmlPath = tem_straXmlPath.GetString();

	TiXmlDocument    tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);


	TiXmlElement*    tem_xmlRootElt = tem_xmlDoc.RootElement();
	TiXmlElement*    tem_xmlChildElt= tem_xmlRootElt->FirstChildElement();
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	TiXmlAttribute*  tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMaxValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMinValue  = tem_xmlChildAtb->IntValue();


	for(int i=0; i<22; i++)
	{
		tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	}
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nOpen      = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto      = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMaxValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMinValue  = tem_xmlChildAtb->IntValue();

	//判断模板中DOC是否开启
	if (tem_nOpen)
	{
		//反射稿打开
		m_BDocMode = TRUE;
		m_nViewMode = 3;
	}
	else
	{
		//反射稿关闭，透射稿必打开，预览模式不能为3
		m_BDocMode = FALSE;
		m_nViewMode = 1;
	}

	if (m_nViewMode == 0)
	{
		((CButton*)GetDlgItem(IDC_RADIO_MANUAL))->SetCheck(TRUE);
	} 
	else if(m_nViewMode == 1)
	{
		((CButton*)GetDlgItem(IDC_RADIO_MANUAL))->SetCheck(TRUE);

	}
	else if (m_nViewMode == 2)
	{
		((CButton*)GetDlgItem(IDC_RADIO_MANUAL))->SetCheck(FALSE);
	}
	else if (m_nViewMode == 3)
	{
		((CButton*)GetDlgItem(IDC_RADIO_MANUAL))->SetCheck(FALSE);
	}


	//分辨率UI初始化
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	m_conResolution.SetCurSel(tem_nSetValue);

	//图像格式UI初始化
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	m_conImgType.SetCurSel(tem_nSetValue);
}


void CUDSGetImg::OnRadioManual()
{
	// TODO: 在此添加命令处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_MANUAL))
	{
		((CButton*)GetDlgItem(IDC_RADIO_MANUAL))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_SCAN))->SetCheck(FALSE);
		m_nViewMode = 1;
		::SendMessage(g_hMainHwnd, WM_SCANSET, 15, 0);
	}
}


void CUDSGetImg::OnRadioScan()
{
	// TODO: 在此添加命令处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_SCAN))
	{
		((CButton*)GetDlgItem(IDC_RADIO_MANUAL))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_SCAN))->SetCheck(TRUE);
		m_nViewMode = 1;
		::SendMessage(g_hMainHwnd, WM_SCANSET, 15, 2);
	}
}


void CUDSGetImg::OnBnClickedBtnHdr()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_SCANSET, 16, 0);
}



void CUDSGetImg::OnBnClickedBtnLdr()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_SCANSET, 16, 1);
}


void CUDSGetImg::OnBnClickedBtnCap()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(g_hMainHwnd, WM_SCANSET, 16, 2);
}


void CUDSGetImg::Self_ShowImgInfo(CString info)
{
	CString tem_strInfo = info;
	tem_strInfo += _T("\n");
	m_conEditInfo.SetSel(-1);
	m_conEditInfo.ReplaceSel(tem_strInfo);
}


void CUDSGetImg::OnClickedChkAdelay()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_ADELAY))
	{
		GetDlgItem(IDC_SLID_ADELAY)->EnableWindow(FALSE);
		::WritePrivateProfileString(_T("BaseSet"), _T("Computer"), _T("0"), m_strIniPath);
		::SendMessage(g_hMainHwnd, WM_SCANSET, 18, 0);
	}
	else
	{
		GetDlgItem(IDC_SLID_ADELAY)->EnableWindow(TRUE);
		m_slidComputer.SetPos(2);
		::WritePrivateProfileString(_T("BaseSet"), _T("Computer"), _T("2"), m_strIniPath);
		::SendMessage(g_hMainHwnd, WM_SCANSET, 18, 2);
	}
}
