
// SmartFilmUI.cpp : 实现文件
//

#include "stdafx.h"
#include "SmartFilm.h"
#include "SmartFilmUI.h"
#include "afxdialogex.h"

CString  g_strProXmlPath;        //透射稿默认模板
CString  g_strDocXmlPath;        //反射稿默认模板
CString  g_strEditInfo;
CString  m_strHDRImg;
CString  g_strIniPath;
std::vector<CString> g_vcRes;
int g_nGrayValue[18][2]={{169,42}, {100,32}, {106,33}, {112,34}, {119,35}, {125,36}, {131,37}, {137,38}, {144,39}, {150,40},{156,41}, {162,42}, {169,43}, {175,44}, {181,45}, {187,46}, {194,47}, {200,48}};
HWND g_hMainHwnd;

extern CSmartFilmApp theApp;
extern HWND g_hCtrHwnd;


//加载调焦dll
typedef long(*pcamInitCameraLib)(); pcamInitCameraLib  camInitCameraLib;           //初始化
typedef long(*pcamGetDevCount)(long&); pcamGetDevCount camGetDevCount;             //摄像头个数
typedef long(*pcamGetDevPid)(long, char*); pcamGetDevPid camGetDevPid;             //PID
typedef long(*pcamGetDevVid)(long, char*); pcamGetDevVid camGetDevVid;             //VID
typedef char*(*pcamGetDevName)(long); pcamGetDevName   camGetDevName;              //获取设备名称
typedef long(*pcamSetFocusValue)(long, long); pcamSetFocusValue camSetFocusValue;  //设置焦点值

// CSmartFilmUI 对话框

IMPLEMENT_DYNAMIC(CSmartFilmUI, CDialogEx)

CSmartFilmUI::CSmartFilmUI(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSmartFilmUI::IDD, pParent)
{

}

CSmartFilmUI::~CSmartFilmUI()
{
}

void CSmartFilmUI::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UDS_VIDEOCTRL1, m_conOCX);
	DDX_Control(pDX, IDC_TAB_CTRL, m_conTab);
	DDX_Control(pDX, IDC_LIST_IMAGE, m_conListCtrl);
	DDX_Control(pDX, IDC_STA_PIC, m_conPicCtrl);
}


BEGIN_MESSAGE_MAP(CSmartFilmUI, CDialogEx)
	ON_WM_CLOSE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CTRL, &CSmartFilmUI::OnSelchangeTabCtrl)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_MESSAGE(WM_SCANSET, &CSmartFilmUI::OnScanset)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_IMAGE, &CSmartFilmUI::OnDblclkListImage)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_IMAGE, &CSmartFilmUI::OnRclickListImage)
	ON_COMMAND(ID_32768, &CSmartFilmUI::On32768Delte)
	ON_COMMAND(ID_32769, &CSmartFilmUI::On32769Property)
	ON_MESSAGE(WM_IMGPROCESS, &CSmartFilmUI::OnImgprocess)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_MESSAGE(WM_THREADOVER, &CSmartFilmUI::OnThreadover)
	ON_MESSAGE(WM_THREADDETECT, &CSmartFilmUI::OnThreaddetect)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_IMAGE, &CSmartFilmUI::OnItemchangedListImage)
END_MESSAGE_MAP()


// CSmartFilmUI 消息处理程序


BOOL CSmartFilmUI::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/*1、变量初始化*/
	m_strConfigDoc = _T(""); 
	m_strXmlDoc    = _T("");     
	m_strThumbDoc  = _T("");  
	m_strCVDoc     = _T("");     
	m_strIniPath   = _T("");   
	m_strXmlPath   = _T("");   
	m_strDevPID    = _T("");
	m_strDevVID    = _T("");
	m_strDevCode   = _T("");
	m_strMyCode1   = _T("thefirstdevice");
	m_strLastTem   = _T("");
	m_strNameDivide= _T("");
	m_strNamePre1  = _T("");
	m_strNamePre2  = _T("");
	m_strNamePre3  = _T("");
	m_strSaveDoc   = _T("");
	m_strWaterColor = _T("");
	m_strWaterInfo = _T("");
	m_strTabImg = _T("");
	m_strCurImgPath = _T("");
	

	m_nLastRes = 0;
	m_nLastImgType = 0;
	m_nLastPreRotate = 0;
	m_nLastMergeMode = 0;
	m_nLastWaterMark = 0;
	m_nNameMode = 0;
	m_nNameDate = 0;
	m_nNameTime = 0;
	m_nNameBegin = 0;
	m_nNameBegin2 = 0;
	m_nViewMode = 0;
	m_nLowLight = 0;
	m_nHigLight = 0;
	m_nVidoeMode = 0;
	m_nFocusValue = 0;
	m_nIniTime = 0;
	m_nWaterMark = 0;
	m_nWaterSite = 0;
	m_nWaterSize = 0;
	m_nWaterFont = 0;
	m_nWaterMode = 0;
	m_nInterpolateReso = 0;
	m_nImageCount = 0;
	m_nPrcsIndex = -1;
	m_nThumbWidth = 160;
	m_nThumbHeight = 130;
	m_nLastBrit = 0;
	m_nLastCtst = 0;
	m_nLastCGama = 0;
	m_nLineMode = 1;
	m_nAngleCount = 0;
	m_nNoteCount = 0;
	m_refLineColor= 255;
	m_nArrowLen   = 35;
	m_nArrowAngle = 30;
	m_nLineWidth  = 5;

	m_fPI = 3.1415926;


	m_lReturnCode  = -1;
	m_lLeftSite = 0;       //裁切框坐标
	m_lTopSite = 0;
	m_lRightSite = 0;
	m_lBottomSite = 0;
	m_nRSlcIndex = -1;

	m_BShowTips = FALSE;
	m_BSaveFmt = FALSE;
	m_BCtrl = TRUE;
	m_BShowPicCtrl = FALSE;
	m_BPaintLine = FALSE;
	m_BOriSize = FALSE;
	m_BSelectTab = FALSE;
	m_BLButtonDown = FALSE;
	m_BSlcRect = FALSE;
	m_BLabel = FALSE;
	m_BSlcRected = FALSE;
	m_BBold = FALSE;
	m_BItalic = FALSE;
	m_nFontSize   =120;
	m_strFont     = _T("宋体");


	g_hMainHwnd = this->m_hWnd;

	pWnd = GetDlgItem(IDC_STA_PIC);

	/*2、目录已经文件路径*/
	//配置文件目录
	CFileFind     tem_fileFind;
	m_strConfigDoc  = Self_GetMyDocument();
	m_strConfigDoc += _T("\\");
	m_strConfigDoc += _T("UDSXRayDataOcx");
	if (!tem_fileFind.FindFile(m_strConfigDoc))
	{
		CreateDirectory(m_strConfigDoc, NULL);
	}
	
	//xml模板目录
	m_strXmlDoc  = m_strConfigDoc;
	m_strXmlDoc += _T("\\");
	m_strXmlDoc += _T("xml");
	if (!tem_fileFind.FindFile(m_strXmlDoc))
	{
		CreateDirectory(m_strXmlDoc, NULL);
	}
	g_strProXmlPath = m_strXmlDoc;
	g_strProXmlPath += _T("\\");
	g_strProXmlPath += _T("透射稿默认.xml");

	g_strDocXmlPath  = m_strXmlDoc;
	g_strDocXmlPath += _T("\\");
	g_strDocXmlPath += _T("反射稿默认.xml");

	//拍照buffer目录
	m_strThumbDoc  = m_strConfigDoc;
	m_strThumbDoc += _T("\\");
	m_strThumbDoc += _T("ThumbBuffer");
	if (!tem_fileFind.FindFile(m_strThumbDoc))
	{
		CreateDirectory(m_strThumbDoc, NULL);
	}

	//图像处理目录
	m_strCVDoc  = m_strConfigDoc;
	m_strCVDoc += _T("\\");
	m_strCVDoc += _T("CVBuffer");
	if (!tem_fileFind.FindFile(m_strCVDoc))
	{
		CreateDirectory(m_strCVDoc, NULL);
	}

	//Ini文件路径
	m_strIniPath  = m_strConfigDoc;
	m_strIniPath += _T("\\");
	m_strIniPath += _T("BaseConfig.ini");	
	g_strIniPath  = m_strIniPath;
	CString tem_strIniPath = Self_GetOCXPath();
	tem_strIniPath += _T("BaseConfig.ini");
	MessageBox(tem_strIniPath);
	MessageBox(m_strIniPath);
	CopyFile(tem_strIniPath, m_strIniPath, TRUE);
//	CopyFile(_T("BaseConfig.ini"), m_strIniPath, TRUE);

	//config文件路径
	m_strXmlPath  = m_strConfigDoc;
	m_strXmlPath += _T("\\");
	m_strXmlPath += _T("config.xml");
	CString tem_strCfgPath = Self_GetOCXPath();
	tem_strCfgPath += _T("config.xml");
	CopyFile(tem_strCfgPath, m_strXmlPath, TRUE);
//	CopyFile(_T("config.xml"), m_strXmlPath, TRUE);

	/*3、摄像头初始化,并启动设备*/
	m_lReturnCode = m_conOCX.Initial();
	int tem_nDevNum = m_conOCX.GetDeviceCount();
	int tem_nDevIndex = -1;
	Self_FindCamera(m_strXmlPath);
	for (int i=0; i<tem_nDevNum; i++)
	{
		CString  tem_strDevID = m_conOCX.GetDevDisplayName(i);

		int      tem_nPID     = tem_strDevID.Find(m_strDevPID);
		int      tem_nVID     = tem_strDevID.Find(m_strDevVID);
		if (tem_nPID!=-1 && tem_nVID!=-1 && m_strDevCode==m_strMyCode1)
		{
			tem_nDevIndex = i;
			break;
		}
	}
	if (tem_nDevIndex == -1)
	{
		MessageBox(_T("未发现设备"), _T("UDS"), MB_OK);
		CDialog::OnOK();
		return FALSE;
	}
	m_lReturnCode = m_conOCX.StartRun(tem_nDevIndex);

	/*4、读取配置文件并设置Camera*/
	Self_ReadIni(m_strIniPath);
	Self_ReadWaterIni(m_strIniPath);

	/*5、Camera相关设置*/
	//1)、分辨率设置
	int  tem_nResNum = m_conOCX.GetResCount();
	m_nInterpolateReso = tem_nResNum;
	for (int i=0; i<tem_nResNum; i++)
	{
		CString tem_strResolution = m_conOCX.GetResolution(i);
		//判断分辨率是否<500W,小于500W则直接过滤
		if (Self_FilterRes(tem_strResolution))
		{
			g_vcRes.push_back(tem_strResolution);
		}	
	}
	g_vcRes.push_back(_T("4480×3360"));

	if (m_nLastRes == m_nInterpolateReso)
	{
		//获取最大分辨率索引，并设置为最大分辨率
		int  tem_nMaxIndex = Self_GetSpyRes(1);
		m_conOCX.SetResolution(tem_nMaxIndex);
	}
	else
	{
		//设置为上次使用的分辨率
		m_conOCX.SetResolution(m_nLastRes);
	}
	//2)、设置旋转方向
	switch (m_nLastPreRotate)
	{
	case 0:
		break;
	case 1:
		m_conOCX.RotatedVideo(1);
		break;
	case 2:
		m_conOCX.RotatedVideo(2);
		break;
	case 3:
		m_conOCX.RotatedVideo(3);
		break;
	default:
		break;
	}
	//3)、色彩类型
	m_conOCX.SetColorMode(2);
	//4)、导出Camera模板
	if (!PathFileExists(g_strProXmlPath))
	{
		Self_EnsureItems();
	}
	if (!PathFileExists(g_strDocXmlPath))
	{
		Self_EnsureItems2();     //导出反射稿默认模板
	}
	//5)、加载Camera模板
	if (m_strLastTem == _T("透射稿"))
	{
		Self_ReadXml(g_strProXmlPath);
	} 
	else
	{
		Self_ReadXml(g_strDocXmlPath);
	}

	/*6、Tab设置*/
	m_conTab.InsertItem(0, _T("图像获取"));
	m_conTab.InsertItem(1, _T("图像处理"));

	m_dlgGet.Create(IDD_DLG_GETIMG, GetDlgItem(IDC_TAB_CTRL));
	m_dlgPro.Create(IDD_DLG_PROIMG, GetDlgItem(IDC_TAB_CTRL));

	m_dlgGet.ShowWindow(TRUE);
	m_dlgPro.ShowWindow(FALSE);

	m_conTab.SetCurSel(0);

	GetDlgItem(IDC_STA_PIC)->ShowWindow(SW_HIDE);

	/*7、读取文件格式*/
	switch(m_nLastImgType)
	{
	case 0:
		m_strFileFormat = _T(".bmp");
		break;
	case 1:
		m_strFileFormat = _T(".jpg");
		break;
	case 2:
		m_strFileFormat = _T(".png");
		break;
	case 3:
		m_strFileFormat = _T(".tif");
		break;
	case 4:
		m_strFileFormat = _T(".pdf");
		break;
	case 5:
		m_strFileFormat = _T(".dcm");
		break;
	default:
		m_strFileFormat = _T(".jpg");
		break;
	}

	/*8、默认保存目录不存在则保存至桌面*/
	if (!PathFileExists(m_strSaveDoc))
	{
		//不存在，获取桌面路径，并修改默认路径参数
		TCHAR MyDir[_MAX_PATH];  
		SHGetSpecialFolderPath(this->GetSafeHwnd(),MyDir,CSIDL_DESKTOP,0);
		m_strSaveDoc  = MyDir;
		m_strSaveDoc += _T("\\");
	}
	::WritePrivateProfileString(_T("BaseSet"), _T("SaveDoc"), m_strSaveDoc, m_strIniPath);

	/*9、设置Camera焦点*/
	CString tem_strOCXDir = Self_GetOCXPath();
	tem_strOCXDir += _T("CmCapture.dll");
 	m_hDllInst = LoadLibrary(tem_strOCXDir);
	if (m_hDllInst)
	{
		//1、加载dll函数---------------------------------------------------------------------
		camInitCameraLib = (pcamInitCameraLib)GetProcAddress(m_hDllInst, "camInitCameraLib");
		camGetDevPid = (pcamGetDevPid)GetProcAddress(m_hDllInst, "camGetDevPid");
		camGetDevVid = (pcamGetDevVid)GetProcAddress(m_hDllInst, "camGetDevVid");
		camGetDevCount = (pcamGetDevCount)GetProcAddress(m_hDllInst, "camGetDevCount");
		camGetDevName = (pcamGetDevName)GetProcAddress(m_hDllInst, "camGetDevName");
		camSetFocusValue = (pcamSetFocusValue)GetProcAddress(m_hDllInst, "camSetFocusValue");

		//2、获取当前设备索引-----------------------------------------------------------------
		int tem_nRC = -1;
		tem_nRC = camInitCameraLib();
		for (int i=0; i<tem_nDevNum; i++)
		{
			char* tem_cCamName = camGetDevName(i);
			CString tem_strCamName(tem_cCamName);
			if (tem_strCamName.Find(_T("Document Scanner")) != -1)
			{
				m_nDevIndex = i;
				break;
			}
		}
		tem_nRC = camSetFocusValue(m_nDevIndex, m_nFocusValue);
	}

	/*10、设置拍照延时*/
	if (m_nIniTime == 0)
	{
		m_nIntervalTime = Self_GetIntervalTime();
	} 
	else
	{
		m_nIntervalTime = m_nIniTime*1000;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CSmartFilmUI::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//鼠标在哪，将焦点给谁，很方便——————————————————————————
	//对于SliderCtrl——Release消息，则需要考虑屏蔽鼠标滚轮消息
/*	if (pMsg->message == WM_MOUSEHWHEEL || pMsg->message == WM_MOUSEWHEEL)
	{
		POINT   tem_CurPos;
		GetCursorPos(&tem_CurPos);
		pMsg->hwnd = ::WindowFromPoint(tem_CurPos);
	}
	*/

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSmartFilmUI::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void CSmartFilmUI::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (::IsWindow(GetDlgItem(IDC_TAB_CTRL)->GetSafeHwnd()))
	{
		if (IsIconic())
		{
			return;
		}
		//1、布局三大控件------------------------------------------------------------------------------------
		CClientDC  dc(this);
		//1)、将Tab预留3.2 inch，将List预留2.5 inch
		int tem_nCellWidth = dc.GetDeviceCaps(LOGPIXELSX);
		int tem_nCellHeight = dc.GetDeviceCaps(LOGPIXELSY);
		int tem_nTabWidth = (int)((tem_nCellWidth*1.0)*3.2-32);  
		int tem_nListWidth = (int)((tem_nCellWidth*1.0)*2.5-32); 

		//2)、界面模式+OCX尺寸决定布局
		CRect  tem_rcClient;
		GetClientRect(&tem_rcClient);
		if (m_nUIMode == 0)
		{
			//左中右
			if (tem_rcClient.Width()>(tem_nTabWidth+tem_nListWidth+20))
			{
				int tem_nCx = 5;
				int tem_nCy = 5;
				int tem_nWidth = tem_nTabWidth;
				int tem_nHeight = tem_rcClient.Height()-10;
				GetDlgItem(IDC_TAB_CTRL)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				GetDlgItem(IDC_TAB_CTRL)->ShowWindow(TRUE);

				tem_nCx = 5+tem_nTabWidth+5;
				tem_nCy = 5;
				tem_nWidth = tem_rcClient.Width()-tem_nTabWidth-tem_nListWidth-20;
				tem_nHeight = tem_rcClient.Height()-10;
				if (m_BShowPicCtrl)
				{
					GetDlgItem(IDC_STA_PIC)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
					GetDlgItem(IDC_STA_PIC)->ShowWindow(TRUE);
				}
				else
				{
					GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
					GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(TRUE);
				}
				tem_nCx = tem_rcClient.Width()-tem_nListWidth-5;
				tem_nCy = 5;
				tem_nWidth = tem_nListWidth;
				tem_nHeight = tem_rcClient.Height()-10;
				GetDlgItem(IDC_LIST_IMAGE)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				GetDlgItem(IDC_LIST_IMAGE)->ShowWindow(TRUE);
			} 
			else
			{
				int tem_nCx = 0;
				int tem_nCy = 5;
				int tem_nWidth = tem_rcClient.Width()/3;
				int tem_nHeight = tem_rcClient.Height()-10;
				GetDlgItem(IDC_TAB_CTRL)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				GetDlgItem(IDC_TAB_CTRL)->ShowWindow(TRUE);

				tem_nCx = tem_rcClient.Width()/3;
				tem_nCy = 5;
				tem_nWidth = tem_rcClient.Width()/3;
				tem_nHeight = tem_rcClient.Height()-10;
				if (m_BShowPicCtrl)
				{
					GetDlgItem(IDC_STA_PIC)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
					GetDlgItem(IDC_STA_PIC)->ShowWindow(TRUE);
				}
				else
				{
					GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
					GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(TRUE);
				}
				tem_nCx = tem_rcClient.Width()*2/3;
				tem_nCy = 5;
				tem_nWidth = tem_rcClient.Width()/3;
				tem_nHeight = tem_rcClient.Height()-10;
				GetDlgItem(IDC_LIST_IMAGE)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				GetDlgItem(IDC_LIST_IMAGE)->ShowWindow(TRUE);
			}
		} 
		else if(m_nUIMode == 1)
		{
			//中
			int tem_nCx = 5;
			int tem_nCy = 5;
			int tem_nWidth = tem_rcClient.Width()-10;
			int tem_nHeight = tem_rcClient.Height()-10;
			GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
			GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(TRUE);

			GetDlgItem(IDC_TAB_CTRL)->ShowWindow(FALSE);
			GetDlgItem(IDC_LIST_IMAGE)->ShowWindow(FALSE);
		}
		else if (m_nUIMode == 2)
		{
			//左中
			if (tem_rcClient.Width()>(tem_nTabWidth+15))
			{
				int tem_nCx = 5;
				int tem_nCy = 5;
				int tem_nWidth = tem_nTabWidth;
				int tem_nHeight = tem_rcClient.Height()-10;
				GetDlgItem(IDC_TAB_CTRL)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				GetDlgItem(IDC_TAB_CTRL)->ShowWindow(TRUE);

				tem_nCx = 5+tem_nTabWidth+5;
				tem_nCy = 5;
				tem_nWidth = tem_rcClient.Width()-tem_nTabWidth-15;
				tem_nHeight = tem_rcClient.Height()-10;
				if (m_BShowPicCtrl)
				{
					GetDlgItem(IDC_STA_PIC)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
					GetDlgItem(IDC_STA_PIC)->ShowWindow(TRUE);
				}
				else
				{
					GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
					GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(TRUE);
				}

				GetDlgItem(IDC_LIST_IMAGE)->ShowWindow(FALSE);
			} 
			else
			{
				int tem_nCx = 0;
				int tem_nCy = 5;
				int tem_nWidth = tem_rcClient.Width()/2;
				int tem_nHeight = tem_rcClient.Height()-10;
				GetDlgItem(IDC_TAB_CTRL)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				GetDlgItem(IDC_TAB_CTRL)->ShowWindow(TRUE);

				tem_nCx = tem_rcClient.Width()/2;
				tem_nCy = 5;
				tem_nWidth = tem_rcClient.Width()/2;
				tem_nHeight = tem_rcClient.Height()-10;
				if (m_BShowPicCtrl)
				{
					GetDlgItem(IDC_STA_PIC)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
					GetDlgItem(IDC_STA_PIC)->ShowWindow(TRUE);
				}
				else
				{
					GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
					GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(TRUE);
				}

				GetDlgItem(IDC_LIST_IMAGE)->ShowWindow(FALSE);
			}

		}
		else if (m_nUIMode == 3)
		{
			//右中
			if (tem_rcClient.Width()>(tem_nListWidth+15))
			{
				int tem_nCx = tem_rcClient.Width()-tem_nListWidth-5;
				int tem_nCy = 5;
				int tem_nWidth = tem_nListWidth;
				int tem_nHeight = tem_rcClient.Height()-10;
				GetDlgItem(IDC_LIST_IMAGE)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				GetDlgItem(IDC_LIST_IMAGE)->ShowWindow(TRUE);

				tem_nCx = 5;
				tem_nCy = 5;
				tem_nWidth = tem_rcClient.Width()-tem_nListWidth-15;
				tem_nHeight = tem_rcClient.Height()-10;
				GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(TRUE);

				GetDlgItem(IDC_TAB_CTRL)->ShowWindow(FALSE);
			} 
			else
			{
				int tem_nCx = 0;
				int tem_nCy = 5;
				int tem_nWidth = tem_rcClient.Width()/2;
				int tem_nHeight = tem_rcClient.Height()-10;
				GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(TRUE);

				tem_nCx = tem_rcClient.Width()/2;
				tem_nCy = 5;
				tem_nWidth = tem_rcClient.Width()/2;
				tem_nHeight = tem_rcClient.Height()-10;
				GetDlgItem(IDC_LIST_IMAGE)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				GetDlgItem(IDC_LIST_IMAGE)->ShowWindow(TRUE);

				GetDlgItem(IDC_TAB_CTRL)->ShowWindow(FALSE);
			}

		}

		//2、布局TabCtrl内控件-------------------------------------------------------------------------------
		CRect  tem_rcTab;
		m_conTab.GetClientRect(&tem_rcTab);
		tem_rcTab.top += 20;
		tem_rcTab.left = 2;

		m_dlgGet.MoveWindow(&tem_rcTab);
		m_dlgPro.MoveWindow(&tem_rcTab);
	}
}


void CSmartFilmUI::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//1、释放UDS_Video_OCX
	m_conOCX.StopRun();
	m_conOCX.Uninitial();

	//2、设置灯箱
	Self_SetRelay1();


	CDialogEx::OnClose();
}


CString CSmartFilmUI::Self_GetMyDocument(void)
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


void CSmartFilmUI::Self_CopyFiles()
{
	CString tem_strIniPath = Self_GetOCXPath();
	CString tem_strCfgPath = tem_strIniPath;
	tem_strIniPath += _T("BaseConfig.ini");
	tem_strCfgPath += _T("config.xml");
	CopyFile(tem_strIniPath, m_strIniPath, TRUE);
	CopyFile(tem_strCfgPath, m_strXmlPath, TRUE);
}


CString CSmartFilmUI::Self_GetOCXPath(void)
{
	TCHAR   sDrive[_MAX_DRIVE]; 
	TCHAR   sDir[_MAX_DIR]; 
	TCHAR   sFilename[_MAX_FNAME], Filename[_MAX_FNAME]; 
	TCHAR   sExt[_MAX_EXT]; 
	CString tem_strOCXPath;
	// Get the Authorized Serial No. in the UdsSmartScan1.dll in the directory of the OCX
	int nLen = GetModuleFileName(AfxGetInstanceHandle(), Filename, _MAX_PATH);
	if (nLen < 3)
		return false;
	_tsplitpath(theApp.m_pszHelpFilePath, sDrive, sDir, sFilename, sExt); 
	CString homeDir(CString(sDrive) + CString(sDir)); 
	nLen = homeDir.GetLength();
	if (nLen < 3)
		return false;
	if (homeDir.GetAt(nLen-1) != _T('\\')) 
		homeDir += _T('\\'); 

	tem_strOCXPath = homeDir;
	return tem_strOCXPath;
}


BOOL CSmartFilmUI::Self_FindCamera(CString xmlpath)
{
	const char*       tem_cInfo;
	CStringA    tem_straXmlPath(xmlpath);
	const char* tem_cXmlPath = tem_straXmlPath.GetString();

	//加载xml文件
	TiXmlDocument   tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);

	//根节点
	TiXmlElement*    tem_xmlRootElt = tem_xmlDoc.RootElement();

	TiXmlElement*    tem_xmlChildElt= tem_xmlRootElt->FirstChildElement();
	tem_cInfo = tem_xmlChildElt->Value();

	TiXmlAttribute*  tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_cInfo = tem_xmlChildAtb->Value();
	m_strDevPID = tem_cInfo;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_cInfo       = tem_xmlChildAtb->Value();
	m_strDevVID = tem_cInfo;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_cInfo   = tem_xmlChildAtb->Value();
	m_strDevCode= tem_cInfo;

	return TRUE;
}


void CSmartFilmUI::Self_ReadIni(CString inipath)
{
	int     tem_nRead      = 0;
	CString tem_strRead    =_T("");
	CString tem_strIniPath = inipath;

	::GetPrivateProfileString(_T("BaseSet"), _T("Template"), _T("没有找到Template信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strLastTem = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("UIMode"), _T("没有找到UIMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nUIMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ResIndex"), _T("没有找到ResIndex信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	switch(tem_nRead)
	{
	case 0:
		m_nLastRes = 6;
		break;
	case 1:
		m_nLastRes = 7;
		break;
	case 2:
		m_nLastRes = 8;
		break;
	case 3:
		m_nLastRes = 9;
		break;
	default:
		m_nLastRes = 8;
		break;
	}
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

	::GetPrivateProfileString(_T("BaseSet"), _T("NameMode"), _T("没有找到NameMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameDate"), _T("没有找到NameDate信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameDate   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameTime"), _T("没有找到NameTime信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameTime   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameDivide"), _T("没有找到NameDivide信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNameDivide = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre1"), _T("没有找到NamePre1信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre1 = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre2"), _T("没有找到NamePre2信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre2 = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre3"), _T("没有找到NamePre3信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre3 = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin"), _T("没有找到NameBegin信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameBegin   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin2"), _T("没有找到NameBegin2信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameBegin2   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveDoc"), _T("没有找到主头SaveDoc信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strSaveDoc = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewMode"), _T("没有找到ViewMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead   = _ttoi(tem_strRead);
	m_nViewMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewLeft"), _T("没有找到ViewLeft信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead   = _ttoi(tem_strRead);
	m_lLeftSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewTop"), _T("没有找到ViewTop信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead  = _ttoi(tem_strRead);
	m_lTopSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewRight"), _T("没有找到ViewRight信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead    = _ttoi(tem_strRead);
	m_lRightSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewBottom"), _T("没有找到ViewBottom信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_lBottomSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveTips"), _T("没有找到SaveTips信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	if (tem_nRead == 0)
	{
		m_BShowTips = FALSE;
	}
	else
	{
		m_BShowTips = TRUE;
	}
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveFormat"), _T("没有找到SaveFormat信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	if (tem_nRead == 0)
	{
		m_BSaveFmt = FALSE;
	}
	else
	{
		m_BSaveFmt = TRUE;
	}
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("lowvalue"), _T("没有找到lowvalue信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nLowLight   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("higvalue"), _T("没有找到SaveFormat信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nHigLight   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("VidoeMode"), _T("没有找到VidoeMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nVidoeMode  = tem_nRead;
	tem_strRead.ReleaseBuffer();	

	::GetPrivateProfileString(_T("BaseSet"), _T("FocusValue"), _T("没有找到FocusValue信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nFocusValue = tem_nRead;
	tem_strRead.ReleaseBuffer();	

	::GetPrivateProfileString(_T("BaseSet"), _T("Computer"), _T("没有找到Computer=0信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nIniTime    = tem_nRead;
	tem_strRead.ReleaseBuffer();	
}


void CSmartFilmUI::Self_ReadWaterIni(CString inipath)
{
	int     tem_nRead      = 0;
	CString tem_strRead    =_T("");
	CString tem_strIniPath = inipath;

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterMark"), _T("没有找到WaterMark信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterMark = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterSite"), _T("没有找到主头WaterSite信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterSite = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterSize"), _T("没有找到主头WaterSize信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterSize = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterFont"), _T("没有找到主头WaterFont信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterFont = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterColor"), _T("没有找到主头WaterColor信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strWaterColor = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterInfo"), _T("没有找到主头WaterInfo信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strWaterInfo = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterMode"), _T("没有找到主头WaterMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterMode = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
}


BOOL CSmartFilmUI::Self_FilterRes(CString res)
{
	long       tem_lValue     = 0;
	BOOL       tem_BMark      = FALSE;
	CString tem_strResolution = res;
	int        tem_nFindIndex = tem_strResolution.Find('*');
	CString    tem_strFirst = tem_strResolution;
	CString    tem_strLast  = tem_strResolution;
	tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
	tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
	int        tem_nFirst   = _ttoi(tem_strFirst);
	int        tem_nLast    = _ttoi(tem_strLast);

	tem_lValue   = tem_nFirst*tem_nLast;
	if (tem_lValue>=5000000)
	{
		tem_BMark = TRUE;
	} 

	return tem_BMark;
}


int CSmartFilmUI::Self_GetSpyRes(int diyvalue)
{
	int     tem_nMaxIndex     = 0;
	long    tem_lValue1       = -1;
	long    tem_lValue2       = 10;
	long    tem_lMiddle       = 0;

	BOOL    tem_BMark         = TRUE;

	CString tem_strResolution = _T("");
	int    tem_nResCount = m_conOCX.GetResCount();  //设备分量率数量
	std::vector<int>  tem_vcResIndex;
	std::vector<int>  tem_vcResValue;

	tem_vcResIndex.clear();
	tem_vcResValue.clear();

	for (int i=0; i<tem_nResCount; i++)
	{

		tem_strResolution = m_conOCX.GetResolution(i);
		int        tem_nFindIndex = tem_strResolution.Find('*');
		CString    tem_strFirst = tem_strResolution;
		CString    tem_strLast  = tem_strResolution;
		tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
		tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
		int        tem_nFirst   = _ttoi(tem_strFirst);
		int        tem_nLast    = _ttoi(tem_strLast);

		tem_lValue1   = tem_nFirst*tem_nLast;
		tem_nMaxIndex = i;

		tem_vcResValue.push_back(tem_lValue1);
		tem_vcResIndex.push_back(i);
	}
	//对vector进行排序，同时索引对应相应的的值,由小到大
	for (int i=0; i<tem_vcResValue.size()-1; i++)
	{
		for (int j=0; j<tem_vcResValue.size()-i-1; j++)
		{
			if (tem_vcResValue[j]>tem_vcResValue[j+1])
			{
				int tem_nValue = tem_vcResValue[j];
				tem_vcResValue[j] = tem_vcResValue[j+1];
				tem_vcResValue[j+1] = tem_nValue;
				int tem_nIndex = tem_vcResIndex[j];
				tem_vcResIndex[j] = tem_vcResIndex[j+1];
				tem_vcResIndex[j+1] = tem_nIndex;
			}
		}
	}

	int  tem_nSecond = tem_vcResIndex.at(tem_vcResIndex.size()-diyvalue);

	return tem_nSecond;
}


void CSmartFilmUI::Self_EnsureItems(void)
{
	long       tem_lRC       = -1;    //返回值
	long       tem_lMark     = -1;    //是否支持
	long       tem_lAuto     = -1;    //自动调节
	long       tem_lCurVlaue = -1;    //当前值
	long       tem_lMaxValue = -1;    //最大值
	long       tem_lMinValue = -1;    //最小值

	CString    tem_strName   = _T("");  //属性名

	PROPERTY   tem_stcCamera;

	std::vector<PROPERTY>  tem_vcCamera;	

	//1、获取摄像头属性-----------------------------------------------------
	//指定模板参数
	//光圈
	tem_strName = _T("Iris");
	{

		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//亮度-
	tem_strName = _T("Bright");
	tem_lRC = m_conOCX.GetBrightnessRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetBrightness(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = -1;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//曝光-
	tem_strName = _T("Expos");
	tem_lRC = m_conOCX.GetExposureRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetExposure(&tem_lCurVlaue, &tem_lAuto);
		tem_lAuto = 0;
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = -10;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//焦点
	tem_strName = _T("Focus");
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//GAMA-
	tem_strName = _T("Gama");
	tem_lRC = m_conOCX.GetGammaRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetGamma(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 162;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//增益-
	tem_strName = _T("Gain");
	tem_lRC = m_conOCX.GetGainRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetGain(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 42;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//色调
	tem_strName = _T("Hue");
	tem_lRC = m_conOCX.GetHueRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetHue(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//全景-
	tem_strName = _T("Pan");
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//滚动
	tem_strName = _T("Roll");
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//倾斜-
	tem_strName = _T("Tilt");
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//缩放-
	tem_strName = _T("Zoom");
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//对比度-
	tem_strName = _T("Contrast");
	tem_lRC = m_conOCX.GetContrastRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetContrast(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 7;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//清晰度-
	tem_strName = _T("Sharp");
	tem_lRC = m_conOCX.GetSharpnessRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetSharpness(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 8;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//饱和度-
	tem_strName = _T("Satura");
	tem_lRC = m_conOCX.GetSaturationRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetSaturation(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//白平衡-
	tem_strName = _T("WhiteBlance");
	tem_lRC = m_conOCX.GetWhiteBalanceRange(&tem_lMinValue, &tem_lMaxValue);
//	tem_lRC = -1;
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetWhiteBalance(&tem_lCurVlaue, &tem_lAuto);
		tem_lAuto = 1;
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//逆光对比-
	tem_strName = _T("BackLight");
	tem_lRC = m_conOCX.GetBacklightComRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetBacklightCom(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//灯箱调节
	tem_strName = _T("LightBox");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 10;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//灰阶调节
	tem_strName = _T("GrayScale");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 11;
		tem_stcCamera.m_lMaxValue = 17;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//包围曝光开关--------------------------------------------------------------------
	tem_strName = _T("HDR");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//合并方式
	tem_strName = _T("MergeMode");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;       
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 1;           //1-水平合并，2-垂直合并
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//曝光偏移
	tem_strName = _T("LightBox2");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 50;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//延时调节
	tem_strName = _T("Delay");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 10;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//灰阶调节
	tem_strName = _T("HDRGRAY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 12;
		tem_stcCamera.m_lMaxValue = 17;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//---------------------------------------------------------------------------------
	//反射稿开关
	tem_strName = _T("Doc");
	{
		tem_lMark = 0;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//分辨率
	tem_strName = _T("Res");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 2;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//图像类型
	tem_strName = _T("Format");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 1;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//包围曝光小模板中逆光对比CheckBox选项
	tem_strName = _T("HDRBackLgt");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//LDR——低密度拍摄，小模板-----------------------------------
	//灯箱
	tem_strName = _T("LQUABGT");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 10;      //中间亮度——Cur
		tem_stcCamera.m_lMaxValue = 40;     //最大亮度——Max
		tem_stcCamera.m_lMinValue = 1;       //最小亮度——Min

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//灰阶调节
	tem_strName = _T("LQUAGRY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 11;      //Cur
		tem_stcCamera.m_lMaxValue = 11;      //Max
		tem_stcCamera.m_lMinValue = 11;      //Min

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//延时
	tem_strName = _T("LQUADLY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;          
		tem_stcCamera.m_lCurValue = 30;       //Cur
		tem_stcCamera.m_lMaxValue = 30;       //Max
		tem_stcCamera.m_lMinValue = 30;       //Min

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//逆光对比
	tem_strName = _T("LQUABCK");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//HDR——高密度拍摄，小模板-----------------------------------
	//灯箱
	tem_strName = _T("HQUABGT");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 10;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//灰阶调节
	tem_strName = _T("HQUAGRY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 11;
		tem_stcCamera.m_lMaxValue = 11;
		tem_stcCamera.m_lMinValue = 11;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//延时
	tem_strName = _T("HQUADLY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 30;
		tem_stcCamera.m_lMinValue = 30;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//逆光对比
	tem_strName = _T("HQUABCK");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//2、导出属性XML-------------------------------------------------------
	TiXmlDocument      tem_xmlDoc;

	TiXmlDeclaration*  tem_xmlDec = new TiXmlDeclaration("1.0", "", "");
    tem_xmlDoc.LinkEndChild(tem_xmlDec);

	TiXmlElement*      tem_xmlElt = new TiXmlElement("property");
	tem_xmlDoc.LinkEndChild(tem_xmlElt);

	std::vector<PROPERTY>::iterator iter;
	for (iter=tem_vcCamera.begin(); iter!=tem_vcCamera.end();iter++)
	{
		CString      tem_strPetName = iter->m_strName;
		CStringA     tem_straPetName(tem_strPetName);
		const char*  tem_pcPetName = tem_straPetName.GetString();

		TiXmlElement*  tem_xmlElent = new TiXmlElement(tem_pcPetName); 
		tem_xmlElt->LinkEndChild(tem_xmlElent);
		
		tem_xmlElent->SetAttribute("support", iter->m_lSuport);
		tem_xmlElent->SetAttribute("auto", iter->m_lAuto);
		tem_xmlElent->SetAttribute("cur",iter->m_lCurValue);
		tem_xmlElent->SetAttribute("max", iter->m_lMaxValue);
		tem_xmlElent->SetAttribute("min", iter->m_lMinValue);	
	}

	//3、保存XML-----------------------------------------------------------
	CStringA      tem_straPath(g_strProXmlPath);
	const char*   tem_pcPath = tem_straPath.GetString();
	tem_xmlDoc.SaveFile(tem_pcPath);
}


void CSmartFilmUI::Self_EnsureItems2(void)
{
	long       tem_lRC       = -1;    //返回值
	long       tem_lMark     = -1;    //是否支持
	long       tem_lAuto     = -1;    //自动调节
	long       tem_lCurVlaue = -1;    //当前值
	long       tem_lMaxValue = -1;    //最大值
	long       tem_lMinValue = -1;    //最小值

	CString    tem_strName   = _T("");  //属性名

	PROPERTY   tem_stcCamera;

	std::vector<PROPERTY>  tem_vcCamera;	

	//1、获取摄像头属性-----------------------------------------------------
	//指定模板参数
	//光圈
	tem_strName = _T("Iris");
	{

		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//亮度-
	tem_strName = _T("Bright");
	tem_lRC = m_conOCX.GetBrightnessRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetBrightness(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//曝光-
	tem_strName = _T("Expos");
	tem_lRC = m_conOCX.GetExposureRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetExposure(&tem_lCurVlaue, &tem_lAuto);
		tem_lAuto = 1;
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = -4;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//焦点
	tem_strName = _T("Focus");
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//GAMA-
	tem_strName = _T("Gama");
	tem_lRC = m_conOCX.GetGammaRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetGamma(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 150;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//增益-
	tem_strName = _T("Gain");
	tem_lRC = m_conOCX.GetGainRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetGain(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 40;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//色调
	tem_strName = _T("Hue");
	tem_lRC = m_conOCX.GetHueRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetHue(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//全景-
	tem_strName = _T("Pan");
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//滚动
	tem_strName = _T("Roll");
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//倾斜-
	tem_strName = _T("Tilt");
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//缩放-
	tem_strName = _T("Zoom");
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//对比度-
	tem_strName = _T("Contrast");
	tem_lRC = m_conOCX.GetContrastRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetContrast(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 10;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//清晰度-
	tem_strName = _T("Sharp");
	tem_lRC = m_conOCX.GetSharpnessRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetSharpness(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 8;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//饱和度-
	tem_strName = _T("Satura");
	tem_lRC = m_conOCX.GetSaturationRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetSaturation(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 3;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//白平衡-
	tem_strName = _T("WhiteBlance");
	tem_lRC = m_conOCX.GetWhiteBalanceRange(&tem_lMinValue, &tem_lMaxValue);
	//	tem_lRC = -1;
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetWhiteBalance(&tem_lCurVlaue, &tem_lAuto);
		tem_lAuto = 1;
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//逆光对比-
	tem_strName = _T("BackLight");
	tem_lRC = m_conOCX.GetBacklightComRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conOCX.GetBacklightCom(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//灯箱调节
	tem_strName = _T("LightBox");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//灰阶调节
	tem_strName = _T("GrayScale");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 9;
		tem_stcCamera.m_lMaxValue = 17;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//包围曝光开关--------------------------------------------------------------------
	tem_strName = _T("HDR");
	{
		tem_lMark = 0;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//合并方式
	tem_strName = _T("MergeMode");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;       
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;           //1-水平合并，2-垂直合并
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//曝光偏移
	tem_strName = _T("LightBox2");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 50;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//延时调节
	tem_strName = _T("Delay");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 10;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//灰阶调节
	tem_strName = _T("HDRGRAY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 12;
		tem_stcCamera.m_lMaxValue = 17;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//---------------------------------------------------------------------------------
	//反射稿开关
	tem_strName = _T("Doc");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 1;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//分辨率
	tem_strName = _T("Res");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 2;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//图像类型
	tem_strName = _T("Format");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 1;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//包围曝光小模板中逆光对比CheckBox选项
	tem_strName = _T("HDRBackLgt");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//LDR小模板_低密度-----------------------------------
	//灯箱
	tem_strName = _T("LQUABGT");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 10;
		tem_stcCamera.m_lMaxValue = 40;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//灰阶调节
	tem_strName = _T("LQUAGRY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 11;
		tem_stcCamera.m_lMaxValue = 11;
		tem_stcCamera.m_lMinValue = 11;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//延时1
	tem_strName = _T("LQUADLY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 30;
		tem_stcCamera.m_lMinValue = 30;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//逆光对比1
	tem_strName = _T("LQUABCK");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//HDR_高密度拍摄
	tem_strName = _T("HQUABGT");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 10;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//灰阶调节2
	tem_strName = _T("HQUAGRY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 11;
		tem_stcCamera.m_lMaxValue = 11;
		tem_stcCamera.m_lMinValue = 11;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//延时2
	tem_strName = _T("HQUADLY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 30;
		tem_stcCamera.m_lMinValue = 30;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//逆光对比2
	tem_strName = _T("HQUABCK");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}


	//2、导出属性XML-------------------------------------------------------
	TiXmlDocument      tem_xmlDoc;

	TiXmlDeclaration*  tem_xmlDec = new TiXmlDeclaration("1.0", "", "");
	tem_xmlDoc.LinkEndChild(tem_xmlDec);

	TiXmlElement*      tem_xmlElt = new TiXmlElement("property");
	tem_xmlDoc.LinkEndChild(tem_xmlElt);

	std::vector<PROPERTY>::iterator iter;
	for (iter=tem_vcCamera.begin(); iter!=tem_vcCamera.end();iter++)
	{
		CString      tem_strPetName = iter->m_strName;
		CStringA     tem_straPetName(tem_strPetName);
		const char*  tem_pcPetName = tem_straPetName.GetString();

		TiXmlElement*  tem_xmlElent = new TiXmlElement(tem_pcPetName); 
		tem_xmlElt->LinkEndChild(tem_xmlElent);

		tem_xmlElent->SetAttribute("support", iter->m_lSuport);
		tem_xmlElent->SetAttribute("auto", iter->m_lAuto);
		tem_xmlElent->SetAttribute("cur",iter->m_lCurValue);
		tem_xmlElent->SetAttribute("max", iter->m_lMaxValue);
		tem_xmlElent->SetAttribute("min", iter->m_lMinValue);	
	}

	//3、保存XML-----------------------------------------------------------
	CStringA      tem_straPath(g_strDocXmlPath);
	const char*   tem_pcPath = tem_straPath.GetString();
	tem_xmlDoc.SaveFile(tem_pcPath);
}


void CSmartFilmUI::Self_ReadXml(CString xmlpath)
{
	const char*       tem_cInfo;
	int         tem_nMark     = 0;
	int         tem_nAuto     = 0;
	int         tem_nSetValue = 0;

	CStringA    tem_straXmlPath(xmlpath);
	const char* tem_cXmlPath = tem_straXmlPath.GetString();

	//加载xml文件
	TiXmlDocument   tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);

	//根节点
	TiXmlElement*    tem_xmlRootElt = tem_xmlDoc.RootElement();
	
	//Iris节点
	TiXmlElement*    tem_xmlChildElt;
	tem_xmlChildElt = tem_xmlRootElt->FirstChildElement();
	tem_cInfo = tem_xmlChildElt->Value();
	TiXmlAttribute*  tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conOCX.SetIris(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastIris     = tem_nSetValue;
			m_conOCX.SetIris(tem_nSetValue, 0);
		}
	}

	//Bright节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conOCX.SetBrightness(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastBright   = tem_nSetValue;
			m_conOCX.SetBrightness(tem_nSetValue, 0);
		}
	}

	//Expos节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
//			m_conOCX.SetExposure(0, 1);
			m_conOCX.SetAutoExposure(1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastExpos    = tem_nSetValue;
			m_conOCX.SetExposure(tem_nSetValue, 0);
		}
	}

	//Focus节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conOCX.SetFocus(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastFocus    = tem_nSetValue;
			m_conOCX.SetFocus(tem_nSetValue, 0);
		}
	}

	//Gama节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
//			m_conOCX.SetGamma(0, 1);                //只读取不设置，修改为灰阶
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastGama     = tem_nSetValue;
//			m_conOCX.SetGamma(tem_nSetValue, 0);     //只读取不设置，修改为灰阶
		}
	}

	//Gain节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
//			m_conOCX.SetGain(0, 1);                    //只读取不设置，修改为灰阶
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastGain     = tem_nSetValue;
//			m_conOCX.SetGain(tem_nSetValue, 0);         //只读取不设置，修改为灰阶
		}
	}

	//Hue节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conOCX.SetHue(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastHue      = tem_nSetValue;
			m_conOCX.SetHue(tem_nSetValue, 0);
		}
	}

	//Pan节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conOCX.SetPan(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastPan      = tem_nSetValue;
			m_conOCX.SetPan(tem_nSetValue, 0);
		}
	}

	//Roll节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conOCX.SetRoll(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastRoll     = tem_nSetValue;
			m_conOCX.SetRoll(tem_nSetValue, 0);
		}
	}

	//Tilt节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conOCX.SetTilt(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastTilt     = tem_nSetValue;
			m_conOCX.SetTilt(tem_nSetValue, 0);
		}
	}

	//Zoom节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conOCX.SetZoom(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastZoom     = tem_nSetValue;
			m_conOCX.SetZoom(tem_nSetValue, 0);
		}
	}

	//Contrast节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conOCX.SetContrast(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastContrst  = tem_nSetValue;
			m_conOCX.SetContrast(tem_nSetValue, 0);
		}
	}

	//Sharp节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conOCX.SetSharpness(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastSharp    = tem_nSetValue;
			m_conOCX.SetSharpness(tem_nSetValue, 0);
		}
	}

	//Satura节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conOCX.SetSaturation(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastSatura   = tem_nSetValue;
			m_conOCX.SetSaturation(tem_nSetValue, 0);
		}
	}

	//WhiteBlance节点
	//将白平衡设为自动，并不可用
//	m_conOCX.SetWhiteBalance(0, 1);
	//根据实际情况设置白平衡
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conOCX.SetWhiteBalance(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastWhiteB   = tem_nSetValue;
			m_conOCX.SetWhiteBalance(tem_nSetValue, 0);
		}
	}
	

	//BackLight节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conOCX.SetBacklightCom(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastBackLight= tem_nSetValue;
//			m_conOCX.SetBacklightCom(tem_nSetValue, 0);
			//逆光对比调整至设置分辨率后面，否则设置分辨率会重置逆光对比
		}
	}

	//LightBox节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nSetValue   = tem_xmlChildAtb->IntValue();
		
		//设置灯箱
		if (tem_nSetValue>50)
		{
			Self_SetRelay100();
		} 
		else
		{
			Self_SetRelayZero();
		}		
		Self_SetRelayValue(tem_nSetValue);
	}

	//灰阶节点
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nSetValue   = tem_xmlChildAtb->IntValue();
		m_nLastGray     = tem_nSetValue;
		m_conOCX.SetGamma(g_nGrayValue[m_nLastGray][0], 0);     
		m_conOCX.SetGain(g_nGrayValue[m_nLastGray][1], 0);
	}
	
	//HDR开关
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		m_BHDR = TRUE;
	}
	else
	{
		m_BHDR = FALSE;
	}

	//合并方式
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	if (tem_nSetValue==1)
	{
		m_nHDRMerge = 1;    //左右合并
	} 
	else if(tem_nSetValue == 2)
	{
		m_nHDRMerge = 2;    //上下合并
	}
	else
	{
		m_nHDRMerge = 0;    //合并方式未打开，此时包围曝光关闭
	}


	//灯箱偏移
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();

	m_nHDRLight = tem_nSetValue;

	//延时
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHDRDelay     = tem_nSetValue;

	//灰阶
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHDRGray      = tem_nSetValue;

	//反射稿开关
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		m_BDOC = TRUE;
		//反射稿打开，预览模式可以随意设置
		m_nViewMode = 3;
	}
	else
	{
		m_BDOC = FALSE;
		//反射稿关闭，则透射稿必定打开，预览模式不可为3
		m_nViewMode = 0;
	}
	if (m_nViewMode == 0)
	{
		//手动裁切
		m_conOCX.ManualImageCrop(TRUE);
		m_conOCX.AdjuestImageCrop(FALSE);
		m_conOCX.SetMessage(1);
	}
	else if (m_nViewMode == 1)
	{
		//固定区域
		m_conOCX.ManualImageCrop(TRUE);
		m_conOCX.SetMessage(1);
		m_conOCX.SetRectValue(m_lLeftSite, m_lTopSite, m_lRightSite, m_lBottomSite);
		m_conOCX.SetMessage(0);
	}
	else if(m_nViewMode == 2)
	{
		//预览模式
		m_conOCX.ManualImageCrop(FALSE);
		m_conOCX.AdjuestImageCrop(FALSE);
	}
	else
	{
		//自动裁切
		m_conOCX.ManualImageCrop(FALSE);
		m_conOCX.AdjuestImageCrop(TRUE);
	}
	
	//图像分辨率
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	//设置分辨率后所有的设置重置一遍，应先设分辨率
	m_conOCX.SetGamma(g_nGrayValue[m_nLastGray][0], 0);     
	m_conOCX.SetGain(g_nGrayValue[m_nLastGray][1], 0);
	m_conOCX.SetBacklightCom(m_nLastBackLight, 0);
	

	//图像格式
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();

	//包围曝光——逆光对比
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHDRBackLgt   = tem_nSetValue;

	//LDR-----------------------------------------------------------
	//LLGT------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorLightL    = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigLightL    = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowLightL    = tem_nSetValue;

	//LGRY------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorGrayL     = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigGrayL     = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowGrayL     = tem_nSetValue;

	//LDLY------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorDelayL    = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigDelayL    = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowDelayL    = tem_nSetValue;

	//LBCK------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorBackLgtL  = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigBackLgtL  = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowBackLgtL  = tem_nSetValue;

	//HDR-----------------------------------------------------------
	//HLGT------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorLight     = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigLight     = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowLight     = tem_nSetValue;

	//HGRY------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorGray      = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigGray      = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowGray      = tem_nSetValue;

	//HDLY------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorDelay     = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigDelay     = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowDelay     = tem_nSetValue;

	//HBCK------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorBackLgt   = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigBackLgt   = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowBackLgt   = tem_nSetValue;
}


void CSmartFilmUI::Self_SetRelay100(void)
{
	int tem_nDeviceHandle;
	struct usb_relay_device_info *tem_pDeviceList;
	usb_relay_init();
	tem_pDeviceList = usb_relay_device_enumerate();
	if (tem_pDeviceList==0)
	{
		return;
	}
	tem_nDeviceHandle = usb_relay_device_open(tem_pDeviceList);

	for (int i=0; i<100; i++)
	{
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
	}

	m_nLastRelay = 100;

	usb_relay_device_close(tem_nDeviceHandle);
}


void CSmartFilmUI::Self_SetRelayZero(void)
{
	int tem_nDeviceHandle;
	struct usb_relay_device_info *tem_pDeviceList;
	usb_relay_init();
	tem_pDeviceList = usb_relay_device_enumerate();
	if (tem_pDeviceList==0)
	{
		return;
	}
	tem_nDeviceHandle = usb_relay_device_open(tem_pDeviceList);

	for (int i=0; i<100; i++)
	{
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
	}

	m_nLastRelay = 0;

	usb_relay_device_close(tem_nDeviceHandle);
}


void CSmartFilmUI::Self_SetRelayValue(int dstvalue)
{
	int     tem_nDstValue     = dstvalue;
	int     tem_nDeviceHandle = NULL;

	usb_relay_init();
	struct usb_relay_device_info *tem_pDeviceList;

	tem_pDeviceList = usb_relay_device_enumerate();
	if (tem_pDeviceList==0)
	{
		return;
	}
	tem_nDeviceHandle = usb_relay_device_open(tem_pDeviceList);

	if (tem_nDstValue>m_nLastRelay)
	{
		//调亮
		for (int i=0; i<tem_nDstValue-m_nLastRelay; i++)
		{
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
		}

	}
	else
	{
		//调暗
		for (int i=0; i<m_nLastRelay-tem_nDstValue; i++)
		{
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
		}

	}
	m_nLastRelay = dstvalue;
	usb_relay_device_close(tem_nDeviceHandle);
}


void CSmartFilmUI::Self_SetRelay1(void)
{
	int tem_nDeviceHandle;
	struct usb_relay_device_info *tem_pDeviceList;
	usb_relay_init();
	tem_pDeviceList = usb_relay_device_enumerate();
	if (tem_pDeviceList==0)
	{
		return;
	}
	tem_nDeviceHandle = usb_relay_device_open(tem_pDeviceList);

	for (int i=0; i<100; i++)
	{
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
	}
	//+1
	usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 1);
	usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 2);

	usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 1);
	usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 2);

	usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 1);
	usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 2);

	usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 1);
	usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 2);

	usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
	usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);



	m_nLastRelay = 1;

	usb_relay_device_close(tem_nDeviceHandle);
}


//消息函数*****************************************************************************
afx_msg LRESULT CSmartFilmUI::OnScanset(WPARAM wParam, LPARAM lParam)
{
	int tem_nOperation = (int)wParam;    //操作码
	int tem_nInfo      = (int)lParam;    //操作信息

	CString tem_strSlcDoc= _T("");
	CString tem_strImgName = _T("");
	CString tem_strValue = _T("");

	switch(tem_nOperation)
	{
	case 0:
		//预留项
		break;
	case 1:
		//亮度调节
		if (tem_nInfo!=m_nLastBright)
		{
			AdjustBriCst(tem_nInfo, 0);
		}
		break;
	case 2:
		//对比度调节
		if (tem_nInfo!=m_nLastContrst)
		{
			AdjustBriCst(tem_nInfo, 1);
		}
		break;
	case 3:
		//灯箱亮度调节
		if (tem_nInfo != m_nLastRelay)
		{
			AdjustLight(tem_nInfo);
		}
		break;
	case 4:
		//焦点调节
		if (tem_nInfo != m_nFocusValue)
		{
			AdjustFocus(tem_nInfo);
		}
		break;
	case 5:
		//调节延时
		if (tem_nInfo*1000 != m_nIntervalTime)
		{
			AdjustDelay(tem_nInfo);
		}
		break;
	case 6:
		//调节分辨率
		if (tem_nInfo != m_nLastRes)
		{
			AdjustRes(tem_nInfo);
		}
		break;
	case 7:
		//调节图像格式
		if (tem_nInfo != m_nLastImgType)
		{
			AdjustFormat(tem_nInfo);
		}
		break;
	case 8:
		//恢复默认参数
		Self_ReadXml(g_strProXmlPath);
		m_dlgGet.Self_ResetUI(g_strProXmlPath);
		break;
	case 9:
		//设置旋转方向
		if (tem_nInfo != m_nLastPreRotate)
		{
			AdjustRotate(tem_nInfo);
		}
		break;
	case 10:
		//设置合并方式
		if (tem_nInfo != m_nLastMergeMode)
		{
			m_nLastMergeMode = tem_nInfo;
		}
		break;
	case 11:
		//选择路径
		tem_strSlcDoc = Self_SlcSaveDoc(); 
		if (tem_strSlcDoc!=_T(""))
		{
			m_strSaveDoc = tem_strSlcDoc;
		}
		break;
	case 12:
		//水印开关
		if (tem_nInfo==1)
		{
			m_nWaterMark = 1;
		}
		else
		{
			m_nWaterMark = 0;
		}
		break;
	case 13:
		//打开水印设置界面
		if(IDOK == m_dlgWater.DoModal())
		{
			Self_ReadWaterIni(m_strIniPath);
		}
		break;
	case 14:
		//命名设置
		Self_ReadNameRule();
		break;
	case 15:
		//固定区域/浏览模式
		if (tem_nInfo==0)
		{
			/*
			//固定区域
			m_conOCX.ManualImageCrop(TRUE);
			m_conOCX.SetMessage(1);
			m_conOCX.SetRectValue(m_lLeftSite, m_lTopSite, m_lRightSite, m_lBottomSite);
			m_conOCX.SetMessage(0);
			*/
			//手动裁切
			m_conOCX.ManualImageCrop(TRUE);
			m_conOCX.AdjuestImageCrop(FALSE);
			m_conOCX.SetMessage(1);
		} 
		else if(tem_nInfo==2)
		{
			m_conOCX.ManualImageCrop(FALSE);
			m_conOCX.AdjuestImageCrop(FALSE);
		}
		break;
	case 16:
		//拍照
		if (tem_nInfo==0)
		{
			//高密度
			tem_strImgName  = Self_NamingFile(m_nImageCount);
			m_strCurImgName = tem_strImgName;
			m_nCurImgMode = 1;

			Self_CaptureImgHDRThread(m_strCurImgName, 1, 0);

			m_nPrcsIndex = -1;
		} 
		else if(tem_nInfo==1)
		{
			//低密度
			tem_strImgName  = Self_NamingFile(m_nImageCount);
			m_strCurImgName = tem_strImgName;
			m_nCurImgMode = 0;

			Self_CaptureImgHDRThread(m_strCurImgName, 0, 0);

			m_nPrcsIndex = -1;
		}
		else
		{
			//普通拍摄
			tem_strImgName  = Self_NamingFile(m_nImageCount);
			Self_CaptureImg(tem_strImgName);
			m_nPrcsIndex = -1;
		}
		break;
	case 17:
		//确认裁切框
		m_nViewMode = 1;
		m_conOCX.GetRectValue(&m_lLeftSite, &m_lTopSite, &m_lRightSite, &m_lBottomSite);
		m_conOCX.SetRectValue(m_lLeftSite, m_lTopSite, m_lRightSite, m_lBottomSite);
		m_conOCX.SetMessage(0);

		tem_strValue.Format(_T("%d"), m_lLeftSite);
		::WritePrivateProfileString(_T("BaseSet"), _T("ViewLeft"), tem_strValue, m_strIniPath);
		tem_strValue.ReleaseBuffer();

		tem_strValue.Format(_T("%d"), m_lTopSite);
		::WritePrivateProfileString(_T("BaseSet"), _T("ViewTop"), tem_strValue, m_strIniPath);
		tem_strValue.ReleaseBuffer();

		tem_strValue.Format(_T("%d"), m_lRightSite);
		::WritePrivateProfileString(_T("BaseSet"), _T("ViewRight"), tem_strValue, m_strIniPath);
		tem_strValue.ReleaseBuffer();

		tem_strValue.Format(_T("%d"), m_lBottomSite);
		::WritePrivateProfileString(_T("BaseSet"), _T("ViewBottom"), tem_strValue, m_strIniPath);
		tem_strValue.ReleaseBuffer();

		break;
	case 18:
		//开启或关闭自动测速
		if (tem_nInfo == 0)
		{
			m_nIntervalTime = Self_GetIntervalTime();
		} 
		else
		{
			//默认切换至手动调节时间隔为2秒
			m_nIntervalTime = tem_nInfo*1000;
			m_nIniTime = tem_nInfo;
		}

		break;

	}
	
	return 0;
}


afx_msg LRESULT CSmartFilmUI::OnImgprocess(WPARAM wParam, LPARAM lParam)
{
	int tem_nOperation = (int)wParam;    //操作码
	int tem_nInfo      = (int)lParam;    //操作信息
	CString  tem_strProcess = _T("");         //用于色彩平衡后重新加载图像
	std::string strTempData; 
	switch(tem_nOperation)
	{
	case 0:
		//保存
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		if (m_vcHistoryImg.size()>2)
		{
			//0)弹出保存格式对话款，选择保存格式

			//1)更新buffer图像信息
			m_strBufferImgPath = m_vcHistoryImg.back();
			//2)替换原文件
			CopyFile(m_strBufferImgPath, m_strFilesPath, FALSE);
			std::vector<CString>::iterator item;
			for (item=m_vcHistoryImg.begin()+1; item!=m_vcHistoryImg.end()-1; item++)
			{
				DeleteFile(*item);
			}

			{
				//保存为原格式，并更新视图以及其他信息

				//4)更新图像显示
				std::string strTempData = (CStringA)m_strBufferImgPath; 
				m_cvSrcImage.release();
				m_cvDstImage.release();
				m_cvLastImg.release();
				m_cvNextImg.release();
				m_cvSrcImage = imread(strTempData);
				Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
				//5)重置vector
				m_vcHistoryImg.clear();
				m_vcHistoryImg.push_back(m_strFilesPath);
				m_vcHistoryImg.push_back(m_strBufferImgPath);
				//6)更新变量
				m_BNoSaved  = FALSE;
				//7)更新缩略图
				Self_UpdateThumb(m_nPrcsIndex, m_strFilesPath);
			}
		}
		break;
	case 1:
		//撤销
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		if (m_vcHistoryImg.size()>2)
		{
			CString  tem_strNewImg = m_vcHistoryImg.back();
			//删除最后一张图像
			DeleteFile(tem_strNewImg);
			//删除vector最后一个元素
			m_vcHistoryImg.erase(m_vcHistoryImg.end()-1);
			//更新地址
			tem_strNewImg = m_vcHistoryImg.back();		
			std::string tem_sNewImg = (CStringA)tem_strNewImg; 
			m_cvSrcImage  = imread(tem_sNewImg);	//重新加载图像则需要重新计算区域，例如裁切后图像尺寸发生变化
			tem_strNewImg.ReleaseBuffer();

			Self_ClearPicCtrl();
			Self_ResetImageRect();
			Self_ResizeImage(pWnd, m_cvSrcImage);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);			
		}
		else if (m_vcHistoryImg.size()==2)
		{
			m_BNoSaved = FALSE;
		}
		break;
	case 2:
		//重置
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		if (m_vcHistoryImg.size()>2)
		{
			//1)重新加载图像
			std::string strTempData = (CStringA)m_strBufferImgPath; 
			m_cvSrcImage.release();
			m_cvDstImage.release();
			m_cvLastImg.release();
			m_cvNextImg.release();
			m_cvSrcImage = imread(strTempData);
			Self_ClearPicCtrl();
			Self_ResetImageRect();
			Self_ResizeImage(pWnd, m_cvSrcImage);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
			//2)删除其他缓存图像
			std::vector<CString>::iterator item;
			for (item=m_vcHistoryImg.begin()+2; item!=m_vcHistoryImg.end(); item++)
			{
				DeleteFile(*item);
			}
			//3)重置vector
			m_vcHistoryImg.clear();
			m_vcHistoryImg.push_back(m_strFilesPath);
			m_vcHistoryImg.push_back(m_strBufferImgPath);
			//4)更新变量
			m_BNoSaved  = FALSE;
		}
		break;
	case 3:
		//适应屏幕
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		Self_ClearPicCtrl();
		Self_ResetImageRect();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		break;
	case 4:
		//原始大小
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		//原方法：调用放大缩小函数，实现1:1原图显示
		// 		m_fCurRatio = 0.95;
		// 		Self_ZoomSize(m_cvSrcImage, m_fCurRatio, TRUE);
		// 		m_fCurRatio = 1.0;

		m_BOriSize = TRUE;
		BOOL tem_BRC; 
		if (m_fCurRatio<=0.95)
		{
			tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, TRUE);
			while (tem_BRC)
			{
				m_fCurRatio+=0.05;
				if (m_fCurRatio>=0.95)
				{
					m_BOriSize = FALSE;
					tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, TRUE);
					m_fCurRatio+=0.05;
					break;
				}
				tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, TRUE);
			}
		}
		else if (m_fCurRatio>=1.05)
		{
			tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, FALSE);
			while (tem_BRC)
			{
				m_fCurRatio-=0.05;
				if (m_fCurRatio<=1.05)
				{
					m_BOriSize = FALSE;
					tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, FALSE);
					m_fCurRatio-=0.05;
					break;
				}
				tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, FALSE);
			}
		}
		break;
	case 5:
		//左旋
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		m_BNoSaved = TRUE;
		m_cvSrcImage.copyTo(m_cvLastImg);
		m_cvDstImage = ImageRotate(m_cvSrcImage, 90);
		m_cvSrcImage = m_cvDstImage.clone();
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ClearPicCtrl();
		Self_ResetImageRect();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		break;
	case 6:
		//右旋
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		m_BNoSaved = TRUE;
		m_cvSrcImage.copyTo(m_cvLastImg);
		m_cvDstImage = ImageRotate(m_cvSrcImage, -90);
		m_cvSrcImage = m_cvDstImage.clone();
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ClearPicCtrl();
		Self_ResetImageRect();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		break;
	case 7:
		//180
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		m_BNoSaved = TRUE;
		m_cvSrcImage.copyTo(m_cvLastImg);
		m_cvDstImage = ImageRotate(m_cvSrcImage, 180);
		m_cvSrcImage = m_cvDstImage.clone();
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ResetImageRect();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		break;
	case 8:
		//水平镜像
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		m_BNoSaved = TRUE;
		m_cvSrcImage.copyTo(m_cvLastImg);
		m_cvDstImage = ImageMirror(m_cvSrcImage, TRUE);
		m_cvSrcImage = m_cvDstImage.clone();
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ResetImageRect();
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		break;
	case 9:
		//垂直镜像
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		m_BNoSaved = TRUE;
		m_cvSrcImage.copyTo(m_cvLastImg);
		m_cvDstImage = ImageMirror(m_cvSrcImage, FALSE);
		m_cvSrcImage = m_cvDstImage.clone();
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ResetImageRect();
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		break;
	case 10:
		//手动旋转
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		m_dlgPro.Self_DisableCtrl(2); 
		m_BNoSaved   = TRUE;
		m_BPaintLine = TRUE;
		Self_CreateLine();
		m_BSelectTab = TRUE;
	
		break;
	case 11:
		//亮度
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			//将亮度调节条置回原位

			m_dlgPro.Self_ResetSlider(0);
			break;
		}
		if (tem_nInfo!=m_nLastBrit)
		{
			m_dlgPro.Self_DisableCtrl(0);
			m_BNoSaved   = TRUE;
			m_nLastBrit  = tem_nInfo;
			m_cvSrcImage.copyTo(m_cvLastImg);
			m_cvDstImage = BrightAndContrast(m_cvSrcImage, m_nLastBrit, m_nLastCtst);
			Self_ShowMatImage2(m_cvDstImage, m_rcImageShow);
			m_BSelectTab = TRUE;
		}
		break;
	case 12:
		//对比度
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			m_dlgPro.Self_ResetSlider(1);
			break;
		}
		if (tem_nInfo!=m_nLastCtst)
		{
			m_dlgPro.Self_DisableCtrl(0);
			m_BNoSaved   = TRUE;
			m_nLastCtst  = tem_nInfo;
			m_cvSrcImage.copyTo(m_cvLastImg);
			m_cvDstImage = BrightAndContrast(m_cvSrcImage, m_nLastBrit, m_nLastCtst);
			Self_ShowMatImage2(m_cvDstImage, m_rcImageShow);
			m_BSelectTab = TRUE;
		}
		break;
	case 13:
		//Gama
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			m_dlgPro.Self_ResetSlider(2);
			break;
		}
		if (tem_nInfo!=m_nLastCGama)
		{
			if (tem_nInfo!=0)
			{
				m_dlgPro.Self_DisableCtrl(0);
				m_BNoSaved   = TRUE;
				m_nLastCGama  = tem_nInfo;
				m_cvSrcImage.copyTo(m_cvLastImg);
				m_cvDstImage = ImageGamma(m_cvSrcImage, m_nLastCGama);
				Self_ShowMatImage2(m_cvDstImage, m_rcImageShow);
				m_BSelectTab = TRUE;
			}
		}
		break;
	case 14:
		//画框
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败"), _T("UDS"), MB_OK);
			break;
		}
		m_dlgPro.Self_SetCtrl(1);
		m_dlgPro.Self_DisableCtrl(3); 

		m_nLineMode = 0;
		m_BNoSaved = TRUE;
		m_BLabel   = TRUE;
		Self_ResetImageRect();
		//重新加载图像
		Self_ClearPicCtrl();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		m_ptNoteSite.x = 0;
		m_ptNoteSite.y = 0;
		break;
	case 15:
		//画箭头
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败"), _T("UDS"), MB_OK);
			break;
		}
		m_dlgPro.Self_SetCtrl(1);
		m_dlgPro.Self_DisableCtrl(3); 
		m_nLineMode = 1;
		m_BNoSaved = TRUE;
		m_BLabel   = TRUE;
		Self_ResetImageRect();
		//重新加载图像
		Self_ClearPicCtrl();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		m_ptNoteSite.x = 0;
		m_ptNoteSite.y = 0;
		break;
	case 16:
		//文本
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败"), _T("UDS"), MB_OK);
			break;
		}
		m_dlgPro.Self_SetCtrl(2);
		m_dlgPro.Self_DisableCtrl(3);
		m_nLineMode = 3;
		m_BNoSaved = TRUE;
		m_BLabel   = TRUE;
		Self_ResetImageRect();
		//重新加载图像
		Self_ClearPicCtrl();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		break;
	case 17:
		//裁切
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		m_BNoSaved = TRUE;
		m_BSlcRect = TRUE;
		Self_ResetImageRect();
		//重新加载图像
		Self_ClearPicCtrl();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		break;
	case 18:
		//反色
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		m_cvSrcImage.copyTo(m_cvLastImg);
		ImageInvert(m_cvSrcImage);
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		m_BNoSaved = TRUE;
		m_cvLastImg.release();
		m_cvNextImg.release();
		m_cvDstImage.release();
		break;
	case 19:
		//锐化
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		m_cvSrcImage.copyTo(m_cvLastImg);
		m_cvDstImage = ImageSharp(m_cvSrcImage);
		m_cvSrcImage = m_cvDstImage.clone();
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		m_BNoSaved = TRUE;
		m_cvLastImg.release();
		m_cvNextImg.release();
		m_cvDstImage.release();
		break;
	case 20:
		//确定
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		switch(tem_nInfo)
		{
		case 11:
		case 12:
		case 13:
			m_cvDstImage.copyTo(m_cvNextImg);
			Self_SaveLastImg();

			//重新加载依次，否则可能出现黑屏
			tem_strProcess = m_vcHistoryImg.back();
			strTempData = (CStringA)tem_strProcess; 
			m_cvSrcImage = imread(strTempData);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
			m_BSelectTab = FALSE;
			break;
		case 10:
			if (m_nAngleCount!=0)
			{
				m_cvSrcImage = m_cvDstImage.clone();
			}
			Self_SaveLastImg();
			m_BPaintLine = FALSE;
			Self_CreateLine();
			m_nAngleCount = 0;
			m_BSelectTab = FALSE;
			break;
		case 14:
		case 15:
			m_cvDstImage.copyTo(m_cvNextImg);

			//重新加载依次，否则可能出现黑屏
			tem_strProcess = m_vcHistoryImg.back();
			strTempData = (CStringA)tem_strProcess; 
			m_cvSrcImage = imread(strTempData);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
			m_BLabel     = FALSE;
			m_nNoteCount = 0;
			m_ptNoteSite.x = 0;
			m_ptNoteSite.y = 0;
			break;
		case 16:
			m_cvDstImage.copyTo(m_cvNextImg);

			//重新加载依次，否则可能出现黑屏
			tem_strProcess = m_vcHistoryImg.back();
			strTempData = (CStringA)tem_strProcess; 
			m_cvSrcImage = imread(strTempData);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
			m_BLabel     = FALSE;
			m_nNoteCount = 0;
			break;
		}
		::SetFocus(m_hWnd);        //避免窗口无法响应OnMouseWheel消息
		break;
	case 21:
		//取消
		if (!m_cvSrcImage.data)
		{
			MessageBox(_T("加载图像失败！"));
			break;
		}
		if (tem_nInfo == 10)
		{
			//放弃旋转
			m_BPaintLine = FALSE;
			if (m_nAngleCount!=0)
			{
				m_cvSrcImage = m_cvLastImg.clone();
			}

			Self_ClearPicCtrl();
			Self_ResetImageRect();
			Self_ResizeImage(pWnd, m_cvSrcImage);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
			m_nAngleCount = 0;

			m_cvLastImg.release();
			m_cvNextImg.release();
		} 
		else if (tem_nInfo == 11 || tem_nInfo == 12 || tem_nInfo == 13)
		{
			//放弃色彩平衡
			m_cvSrcImage = m_cvLastImg.clone();
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);

			m_cvLastImg.release();
			m_cvNextImg.release();
		}
		else if (tem_nInfo == 14 || tem_nInfo ==15 || tem_nInfo == 16)
		{
			//放弃画框
			for (int i=0; i<m_nNoteCount&&m_vcHistoryImg.size()>2; i++)
			{
				CString  tem_strNewImg = m_vcHistoryImg.back();
				//删除最后一张图像
				DeleteFile(tem_strNewImg);
				//删除vector最后一个元素
				m_vcHistoryImg.erase(m_vcHistoryImg.end()-1);	 
			}
			tem_strProcess = m_vcHistoryImg.back();
			strTempData = (CStringA)tem_strProcess; 
			m_cvSrcImage = imread(strTempData);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);

			m_cvLastImg.release();
			m_cvNextImg.release();
			m_BLabel     = FALSE;
			m_nNoteCount = 0;
		}
		::SetFocus(m_hWnd);        //避免窗口无法响应OnMouseWheel消息
		m_BSelectTab = FALSE;
		m_ptNoteSite.x = 0;
		m_ptNoteSite.y = 0;
		break;
	case 22:
		//设置线宽
		m_nLineWidth = tem_nInfo;
		break;
	case 23:
		//设置颜色
		m_refLineColor = tem_nInfo;
		break;
	case 24:
		//添加文本
		m_cvSrcImage.copyTo(m_cvLastImg);
		m_cvDstImage = Self_AddText(m_cvSrcImage, m_rcImageShow, m_rcImageCrop, g_strEditInfo, m_refLineColor, m_strFont, m_nFontSize, m_BBold, m_BItalic);
		m_nNoteCount++;
		m_cvDstImage.copyTo(m_cvSrcImage);
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ResetImageRect();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		m_ptNoteSite.x = 0;
		m_ptNoteSite.y = 0;
		break;
	case 25:
		//加粗
		if (tem_nInfo == 0)
		{
			m_BBold = FALSE;
		}
		else
		{
			m_BBold = TRUE;
		}
		break;
	case 26:
		//斜体
		if (tem_nInfo == 0)
		{
			m_BItalic = FALSE;
		} 
		else
		{
			m_BItalic = TRUE;
		}
		break;
	case 27:
		//字体
		switch(tem_nInfo)
		{
		case 0:
			m_strFont = _T("Arial");
			break;
		case 1:
			m_strFont = _T("Calibri");
			break;
		case 2:
			m_strFont = _T("Times New Roman");
			break;
		case 3:
			m_strFont = _T("宋体");
			break;
		case 4:
			m_strFont = _T("楷体");
			break;
		case 5:
			m_strFont = _T("仿宋");
			break;
		case 6:
			m_strFont = _T("黑体");
			break;
		case 7:
			m_strFont = _T("隶书");
			break;
		case 8:
			m_strFont = _T("微软雅黑");
			break;
		case 9:
			m_strFont = _T("新宋体");
			break;
		}
		break;
	case 28:
		//字体大小
		m_nFontSize = tem_nInfo;
		break;
	}
	
	
	
	return 0;
}


//控件方法*****************************************************************************

void CSmartFilmUI::OnSelchangeTabCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CRect  tem_rcTab;
	m_conTab.GetClientRect(&tem_rcTab);
	tem_rcTab.top     += 22;
	tem_rcTab.left += 2;
	
	CRect rtlbl; 
	int  tem_nCursel = m_conTab.GetCurSel();
	switch(tem_nCursel)
	{
	case 0:
		m_dlgGet.ShowWindow(TRUE);
		m_dlgPro.ShowWindow(FALSE);
		GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STA_PIC)->ShowWindow(SW_HIDE);
		::SendMessage(this->m_hWnd, WM_SIZE, 0, 0);
		Self_EnsureSave();
		Self_ShowOcxCtrl();
		break;
	case 1:
		m_dlgGet.ShowWindow(FALSE);
		m_dlgPro.ShowWindow(TRUE);
		GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_PIC)->ShowWindow(SW_NORMAL);
		::SendMessage(this->m_hWnd, WM_SIZE, 0, 0);
		Self_ShowPicCtrl();
		break;
	default:
		break;
	}
	*pResult = 0;
}


//调节方法*****************************************************************************
//调节亮度、对比度--------------------------------------------------
int CSmartFilmUI::AdjustBriCst(int _value, int _mode)
{
	int tem_nCurValue = _value;
	long tem_nMax = 0;
	long tem_nMin = 0;
	int tem_nRC = 0;
	if (_mode==0)
	{
		m_conOCX.GetBrightnessRange(&tem_nMin, &tem_nMax);
		//亮度调节
		if (tem_nCurValue<tem_nMin)
		{
			tem_nCurValue = tem_nMin;
		}
		else if (tem_nCurValue>tem_nMax)
		{
			tem_nCurValue = tem_nMax;
		}
		tem_nRC = m_conOCX.SetBrightness(tem_nCurValue, 0);
		m_nLastBright = tem_nCurValue;
	} 
	else if(_mode==1)
	{
		m_conOCX.GetContrastRange(&tem_nMin, &tem_nMax);
		//对比度调节
		if (tem_nCurValue<tem_nMin)
		{
			tem_nCurValue = tem_nMin;
		}
		else if (tem_nCurValue>tem_nMax)
		{
			tem_nCurValue = tem_nMax;
		}
		tem_nRC = m_conOCX.SetContrast(tem_nCurValue, 0);
		m_nLastContrst = tem_nCurValue;
	}
	return tem_nRC;
}


//调节焦点---------------------------------------------------------
int CSmartFilmUI::AdjustFocus(int _focus)
{
	int tem_nCurValue = _focus;
	int tem_nRC = 0;
	if (tem_nCurValue<0)
	{
		tem_nCurValue = 0;
	}
	else if(tem_nCurValue>255)
	{
		tem_nCurValue = 255;
	}
	tem_nRC = camSetFocusValue(m_nDevIndex, tem_nCurValue);
	m_nFocusValue = _focus;

	return tem_nRC;
}


//调节灯箱亮度------------------------------------------------------
int CSmartFilmUI::AdjustLight(int _light)
{
	int tem_nCurValue = _light;
	int tem_nRC = 0;
	Self_SetRelayValue(_light);
	m_nLastRelay = _light;
	return _light;
}


//调节延时---------------------------------------------------------
int CSmartFilmUI::AdjustDelay(int _delay)
{
	m_nIntervalTime = _delay*1000;
	CString tem_strInfo = _T("");
	tem_strInfo.Format(_T("%d"), _delay);
	::WritePrivateProfileString(_T("BaseSet"), _T("Computer"), tem_strInfo, m_strIniPath); 
	return m_nIntervalTime;
}


//自动获取延时------------------------------------------------------
int CSmartFilmUI::Self_GetIntervalTime(void)
{
	std::vector<CString> tem_vcBuffers;
	//预览模式
	m_conOCX.ManualImageCrop(FALSE);
	m_conOCX.AdjuestImageCrop(FALSE);

	int tem_nCapCount = 0;
	/*a、拍摄首张图像*/


	/*b、调节灯箱亮度*/
	AdjustRelay(50, 10);
	DWORD tem_DBegin = GetTickCount();
	double tem_dLastGray = 0.0, tem_dNextGray = 5.0, tem_dMidGray=0.0;
	/*c、拍摄第一幅图像*/
	CString tem_strLast = m_strThumbDoc;
	tem_strLast += _T("\\CountTime_1.jpg");

	m_conOCX.CaptureImage(tem_strLast);
	tem_vcBuffers.push_back(tem_strLast);
	if(PathFileExists(tem_strLast))
	{
		tem_nCapCount++;
		tem_dLastGray = Self_GetAvgGray(tem_strLast);
	}

	while(abs(tem_dNextGray-tem_dLastGray)>=3)
	{
		CString tem_strNext = m_strThumbDoc;
		CString str;
		str.Format(_T("%d"), tem_nCapCount);
		tem_strNext += _T("\\CountTime_2_");
		tem_strNext += str;
		tem_strNext += _T(".jpg");
		/*d、拍摄下一幅图像*/
		m_conOCX.CaptureImage(tem_strNext);
		tem_vcBuffers.push_back(tem_strNext);
		if(PathFileExists(tem_strNext))
		{
			tem_nCapCount++;
			tem_dNextGray = Self_GetAvgGray(tem_strNext);
		}

		if (abs(tem_dNextGray-tem_dLastGray)<3)
		{
			break;
		} 
		else
		{
			tem_dLastGray = tem_dNextGray;
			tem_dNextGray = 0;
		}
	}
	DWORD tem_DEnd = GetTickCount();
	/*e、求平均时长*/
	int tem_nAvgTime = 2000;
	if (tem_nCapCount!=0)
	{
		tem_nAvgTime = (int)(tem_DEnd-tem_DBegin)/tem_nCapCount;
	}

	/*f、删除缓存图像，恢复灯箱亮度*/
	std::vector<CString>::iterator tem_it;
	for (tem_it = tem_vcBuffers.begin(); tem_it != tem_vcBuffers.end(); tem_it++)
	{
		::DeleteFile(*tem_it);
	}

	AdjustRelay(10, 50);

	if (m_BDOC)
	{
		//恢复为自动裁切
		m_conOCX.ManualImageCrop(FALSE);
		m_conOCX.AdjuestImageCrop(TRUE);
	} 
	else
	{
		//恢复为固定区域
		m_conOCX.ManualImageCrop(TRUE);
		m_conOCX.AdjuestImageCrop(FALSE);
		m_conOCX.SetMessage(1);
// 		m_conOCX.SetRectValue(m_lLeftSite, m_lTopSite, m_lRightSite, m_lBottomSite);
// 		m_conOCX.SetMessage(0);
	}


	return tem_nAvgTime;
}


void CSmartFilmUI::AdjustRelay(int value, int src)
{
	int tem_nDeviceHandle;
	struct usb_relay_device_info *tem_pDeviceList;
	usb_relay_init();
	tem_pDeviceList = usb_relay_device_enumerate();
	if (tem_pDeviceList==0)
	{
		return;
	}
	tem_nDeviceHandle = usb_relay_device_open(tem_pDeviceList);

	if (value>src)
	{
		for (int i=0; i<(value-src); i++)
		{
			//调亮--------------------------------------------------------
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
		}	
	} 
	else
	{
		for (int i=0; i<(src-value); i++)
		{
			//调暗---------------------------------------------------------
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
		}
	}
	usb_relay_device_close(tem_nDeviceHandle);	
}


double CSmartFilmUI::Self_GetAvgGray(CString imgpath)
{


	return 0;
}


//调节分辨率--------------------------------------------------------
int CSmartFilmUI::AdjustRes(int _index)
{
	int tem_nCurValue = 0;
	int tem_nRC = 0;
	switch(_index)
	{
	case 0:
		tem_nCurValue = 6;
		break;
	case 1:
		tem_nCurValue = 7;
		break;
	case 2:
		tem_nCurValue = 8;
		break;
	case 3:
		tem_nCurValue = 9;
		break;
	default:
		tem_nCurValue = 8;
		break;
	}
	if (tem_nCurValue == m_nInterpolateReso)
	{
		int tem_nMaxIndex = Self_GetSpyRes(1);
		tem_nRC = m_conOCX.SetResolutionPro(tem_nMaxIndex, m_nVidoeMode);
		m_nLastRes = tem_nCurValue;
	} 
	else
	{
		tem_nRC = m_conOCX.SetResolutionPro(tem_nCurValue, m_nVidoeMode);
		m_nLastRes = tem_nCurValue;
	}
	//重新设置灰阶
	m_conOCX.SetGamma(g_nGrayValue[m_nLastGray][0], 0);     
	m_conOCX.SetGain(g_nGrayValue[m_nLastGray][1], 0);
	m_conOCX.SetBacklightCom(m_nLastBackLight, 0);

	CString tem_strCurSel = _T("");
	tem_strCurSel.Format(_T("%d"), _index);
	::WritePrivateProfileString(_T("BaseSet"), _T("ResIndex"), tem_strCurSel, m_strIniPath); 
	return tem_nRC;
}


//调节图像格式------------------------------------------------------
int CSmartFilmUI::AdjustFormat(int _index)
{
	switch(_index)
	{
	case 0:
		m_strFileFormat = _T(".bmp");
		break;
	case 1:
		m_strFileFormat = _T(".jpg");
		break;
	case 2:
		m_strFileFormat = _T(".png");
		break;
	case 3:
		m_strFileFormat = _T(".tif");
		break;
	case 4:
		m_strFileFormat = _T(".pdf");
		break;
	case 5:
		m_strFileFormat = _T(".dcm");
		break;
	default:
		m_strFileFormat = _T(".jpg");
		break;
	}
	m_nLastImgType = _index;

	CString tem_strCurSel = _T("");
	tem_strCurSel.Format(_T("%d"), m_nLastImgType);
	::WritePrivateProfileString(_T("BaseSet"), _T("ImgType"), tem_strCurSel, m_strIniPath); 

	return 0;
}


//设置视频方向------------------------------------------------------
int CSmartFilmUI::AdjustRotate(int _rotate)
{
	int tem_nCurValue = _rotate;
	int tem_nRC = 0;
	switch(tem_nCurValue)
	{
	case 0:
		tem_nRC = m_conOCX.RotatedVideo(0);
		break;
	case 1:
		tem_nRC = m_conOCX.RotatedVideo(1);
		break;
	case 2:
		tem_nRC = m_conOCX.RotatedVideo(2);
		break;
	case 3:
		tem_nRC = m_conOCX.RotatedVideo(3);
		break;
	default:
		tem_nRC = m_conOCX.RotatedVideo(0);
		break;
	}
	m_nLastPreRotate = tem_nCurValue;
	return tem_nRC;
}


//设置合并方向------------------------------------------------------
int CSmartFilmUI::AdjustMerge(int _merge)
{
	//0-不合并，1-左右合并，2-上下合并
	m_nLastMergeMode = _merge;
	return m_nLastMergeMode;
}


//设置水印----------------------------------------------------------
int CSmartFilmUI::AdjustWater(int _water, CString _info)
{
	//0-不添加水印，1-添加水印，_info水印内容
	m_nWaterMark = _water;
	return m_nWaterMark;
}


CString CSmartFilmUI::Self_SlcSaveDoc(void)
{
	CString    tem_strSltPath;
	wchar_t    tem_crSltPath[MAX_PATH]; //Unicode使用wchar_t型_t

	ZeroMemory(tem_crSltPath, sizeof(tem_crSltPath));
	BROWSEINFO   m_broseinfo;
	m_broseinfo.hwndOwner = m_hWnd;
	m_broseinfo.pidlRoot  = NULL;
	m_broseinfo.pszDisplayName = tem_crSltPath;
	m_broseinfo.lpszTitle = _T("选择保存目录"); 
	m_broseinfo.ulFlags   = 0;
	m_broseinfo.lpfn      = NULL;
	m_broseinfo.lParam    = 0;
	m_broseinfo.iImage    = 0;
	LPITEMIDLIST   lp = SHBrowseForFolder(&m_broseinfo);
	if (lp&&SHGetPathFromIDList(lp, tem_crSltPath))
	{
		tem_strSltPath.Format(_T("%s"), tem_crSltPath);
		//		m_strDefaultPath = tem_strSltPath;
		//注意后面的\\---------------------------------------------------------------------------------------

		//如果是C、D盘，最后一位自带“\”不用添加
		CString  tem_strLast = tem_strSltPath;
		tem_strLast = tem_strLast.Right(1);
		if (tem_strLast != _T("\\"))
		{
			tem_strSltPath += _T("\\");
		}
		::WritePrivateProfileString(_T("BaseSet"), _T("SaveDoc"), tem_strSltPath, m_strIniPath);
	} 
	return tem_strSltPath;
}


void CSmartFilmUI::Slef_ChangeSavePath(CString savedir)
{
	m_strSaveDoc = savedir;
	::WritePrivateProfileString(_T("BaseSet"), _T("SaveDoc"), savedir, m_strIniPath);
}


void CSmartFilmUI::Self_ReadNameRule(void)
{
	if (IDOK == m_dlgName.DoModal())
	{
		//重读配置文件
		int     tem_nRead   = 0;
		CString tem_strRead = _T("");
		::GetPrivateProfileString(_T("BaseSet"), _T("NameMode"), _T("没有找到NameMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nRead = _ttoi(tem_strRead);
		m_nNameMode = tem_nRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameDate"), _T("没有找到NameDate信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nRead = _ttoi(tem_strRead);
		m_nNameDate   = tem_nRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameTime"), _T("没有找到NameTime信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nRead = _ttoi(tem_strRead);
		m_nNameTime   = tem_nRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameDivide"), _T("没有找到NameDivide信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		m_strNameDivide = tem_strRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NamePre1"), _T("没有找到NamePre1信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		m_strNamePre1 = tem_strRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NamePre2"), _T("没有找到NamePre2信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		m_strNamePre2 = tem_strRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NamePre3"), _T("没有找到NamePre3信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		m_strNamePre3 = tem_strRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin"), _T("没有找到NameBegin信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nRead = _ttoi(tem_strRead);
		m_nNameBegin   = tem_nRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin2"), _T("没有找到NameBegin2信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nRead = _ttoi(tem_strRead);
		m_nNameBegin2   = tem_nRead;
		tem_strRead.ReleaseBuffer();

		m_nImageCount = 0;
	}
}


CString CSmartFilmUI::Self_NamingFile(int count)
{
	int       tem_nOffset      = count;
	int       tem_nOffset1     = count+1;

	CString   tem_strCount     = _T("");
	CString   tem_strBegin     = _T("");

	SYSTEMTIME   tem_stDateTime;
	CString      tem_strDate = _T("");
	CString      tem_strTime = _T("");
	CString      tem_strDivide = _T("");


	CString   tem_strOrderName = _T("IMG_");   //次序命名
	CString   tem_strTimeName  = _T("");       //时间命名
	CString   tem_strCustomName= _T("");       //自定义名
	CString   tem_strValue     = _T("");       //写入配置文件

	CString   tem_strNewName   = _T("");       //返回名称

	switch(m_nNameMode)
	{
	case 0:
		//次序命名
		tem_nOffset += m_nNameBegin2;
		//把当前的计数值写入ini配置文件
		tem_strValue.Format(_T("%d"), tem_nOffset+1);
		::WritePrivateProfileString(_T("BaseSet"), _T("NameBegin2"), tem_strValue, m_strIniPath);
		tem_strCount.Format(_T("%04d"), tem_nOffset);
		tem_strOrderName += tem_strCount;
		tem_strNewName    = tem_strOrderName;	
		break;
	case 1:
		//时间命名
		GetLocalTime(&tem_stDateTime);
		if (m_nNameDate == 0)
		{
			tem_strDate.Format(_T("%d%02d%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
		} 
		else if (m_nNameDate == 1)
		{
			tem_strDate.Format(_T("%d.%02d.%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
		} 
		else if (m_nNameDate == 2)
		{
			tem_strDate.Format(_T("%d-%02d-%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
		} 
		else if (m_nNameDate == 3)
		{
			tem_strDate.Format(_T("%d_%02d_%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
		} 
		else
		{
			tem_strDate.Format(_T("%d%02d%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
		}

		//毫秒保留前两位
		tem_stDateTime.wMilliseconds = (unsigned short)tem_stDateTime.wMilliseconds/10;
		if (m_nNameTime == 0)
		{
			tem_strTime.Format(_T("%02d%02d%02d%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond, tem_stDateTime.wMilliseconds);
		} 
		else if (m_nNameTime == 1)
		{
			tem_strTime.Format(_T("%02d.%02d.%02d.%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond, tem_stDateTime.wMilliseconds);
		} 
		else if (m_nNameTime == 2)
		{
			tem_strTime.Format(_T("%02d-%02d-%02d-%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond, tem_stDateTime.wMilliseconds);
		} 
		else if (m_nNameTime == 3)
		{
			tem_strTime.Format(_T("%02d_%02d_%02d_%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond, tem_stDateTime.wMilliseconds);
		} 
		else
		{
			tem_strTime.Format(_T("%02d%02d%02d%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond, tem_stDateTime.wMilliseconds);
		}
		tem_strTimeName  = tem_strDate;
		tem_strTimeName += m_strNameDivide;
		tem_strTimeName += tem_strTime;
		tem_strNewName   = tem_strTimeName;

		break;
	case 2:
		//自定义命名

		tem_nOffset += m_nNameBegin;
		//把当前的计数值写入ini配置文件
		tem_strValue.Format(_T("%d"), tem_nOffset+1);
		::WritePrivateProfileString(_T("BaseSet"), _T("NameBegin"), tem_strValue, m_strIniPath);

		tem_strBegin.Format(_T("%04d"), tem_nOffset);
		tem_strCustomName  = m_strNamePre1;
		tem_strCustomName += m_strNamePre2;
		tem_strCustomName += m_strNamePre3;
		tem_strCustomName += tem_strBegin;
		tem_strNewName     = tem_strCustomName;
		break;
	default:
		tem_strCount.Format(_T("%04d"), count);
		tem_strOrderName += tem_strCount;
		tem_strNewName    = tem_strOrderName;
		break;
	}

	return tem_strNewName;
}


void CSmartFilmUI::Self_CaptureImg(CString imgname)
{
	BOOL       tem_BFirst       = TRUE;
	CString    tem_strImgName   = imgname;
	CString    tem_strThumbPath = m_strThumbDoc;
	CString    tem_strFilePath  = m_strSaveDoc;
	CString    tem_strPdfImg    = m_strThumbDoc;      //用于PDF合并拍照
	CString    tem_strDcmImg    = m_strThumbDoc;      //用于dcm单拍，以及合并拍照

	CString    tem_strInterImg  = m_strThumbDoc;      //插值原图保存路径

	tem_strThumbPath += _T("\\~");
	tem_strThumbPath += imgname;
	tem_strThumbPath += _T(".jpg");

	tem_strFilePath  += imgname;
	tem_strFilePath  += m_strFileFormat;
	m_strCurImgPath   = tem_strFilePath;

	tem_strPdfImg += _T("\\~~");
	tem_strPdfImg += imgname;
	tem_strPdfImg += _T(".jpg");

	tem_strDcmImg += _T("\\~~");
	tem_strDcmImg += imgname;
	tem_strDcmImg += _T(".jpg");

	tem_strInterImg += _T("\\~~~");
	tem_strInterImg += imgname;
	tem_strInterImg += _T(".jpg");


	if (m_nLastMergeMode == 1)
	{
		if (m_nLastImgType>=0 && m_nLastImgType<4)
		{
			for (int i=0; i<2; i++)
			{
				if (m_nLastRes==m_nInterpolateReso)
				{
					//将原图保存至缓存目录
					m_conOCX.CaptureCombineEx(tem_strInterImg, 1);

					//图像插值
					Self_InterPolateImage(tem_strInterImg, tem_strFilePath, 0);
					::DeleteFile(tem_strInterImg);
				} 
				else
				{
					m_conOCX.CaptureCombineEx(tem_strFilePath, 1);
				}
				
				
				if (m_nWaterMark == 1)
				{
					Self_AddWaterMark(tem_strFilePath);
				}
				if (tem_BFirst)
				{
					MessageBox(_T("点击确定，完成第二章拍摄！"), _T("紫图UDS"), MB_OK);
					tem_BFirst = FALSE;
				}
			}
			if (m_nUIMode == 0 || m_nUIMode == 3)
			{
				Self_CreateThumb(tem_strFilePath, tem_strThumbPath);
				m_vcImgName.push_back(tem_strImgName);
				m_vcThumbPath.push_back(tem_strThumbPath);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			}
			
			m_vcFilePath.push_back(tem_strFilePath);
			
		} 
		else if (m_nLastImgType == 4)
		{
			for (int i=0; i<2; i++)
			{
				if (m_nLastRes==m_nInterpolateReso)
				{
					//将原图保存至缓存目录
					m_conOCX.CaptureCombineEx(tem_strInterImg, 1);
					
					//图像插值
					Self_InterPolateImage(tem_strInterImg, tem_strPdfImg, 0);
					::DeleteFile(tem_strInterImg);
				} 
				else
				{
					m_conOCX.CaptureCombineEx(tem_strPdfImg, 1);
				}
				
				if (m_nWaterMark == 1)
				{
					Self_AddWaterMark(tem_strPdfImg);
				}
				if (tem_BFirst)
				{
					MessageBox(_T("点击确定，完成第二章拍摄！"), _T("紫图UDS"), MB_OK);
					tem_BFirst = FALSE;
				}
			}
			if (m_nUIMode == 0 || m_nUIMode == 3)
			{
				Self_CreateThumb(tem_strPdfImg, tem_strThumbPath);
				m_vcImgName.push_back(tem_strImgName);
				m_vcThumbPath.push_back(tem_strThumbPath);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			}
			Self_GetPDFFromImg(tem_strPdfImg, tem_strFilePath);
			m_vcFilePath.push_back(tem_strFilePath);
			DeleteFile(tem_strPdfImg);			
		}
		else if (m_nLastImgType == 5)
		{
			for (int i=0; i<2; i++)
			{
				if (m_nLastRes==m_nInterpolateReso)
				{
					//将原图保存至缓存目录
					m_conOCX.CaptureCombineEx(tem_strInterImg, 1);

					//图像插值
					Self_InterPolateImage(tem_strInterImg, tem_strDcmImg, 0);
					::DeleteFile(tem_strInterImg);
				} 
				else
				{
					m_conOCX.CaptureCombineEx(tem_strDcmImg, 1);
				}
				
				
				if (m_nWaterMark == 1)
				{
					Self_AddWaterMark(tem_strDcmImg);
				}
				if (tem_BFirst)
				{
					MessageBox(_T("点击确定，完成第二章拍摄！"), _T("紫图UDS"), MB_OK);
					tem_BFirst = FALSE;
				}
			}
			if (m_nUIMode == 0 || m_nUIMode == 3)
			{
				Self_CreateThumb(tem_strDcmImg , tem_strThumbPath);
				m_vcImgName.push_back(tem_strImgName);
				m_vcThumbPath.push_back(tem_strThumbPath);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			}
			
			//生成dcm图像
			char*  tem_cName  = NULL;
			char*  tem_cId    = NULL;
			char*  tem_cBirth = NULL;
			char*  tem_cSex   = NULL;
			char*  tem_cDName = NULL;
			char*  tem_cDate  = NULL;
			char*  tem_cTime  = NULL;

			IMAGEAndDCM*   tem_dcm = new IMAGEAndDCM;
			tem_dcm->Set(tem_cName, tem_cId, tem_cBirth, tem_cSex, tem_cDName, tem_cDate, tem_cTime);

			USES_CONVERSION;  
			char*   tem_cSrc = T2A(tem_strDcmImg);
			char*   tem_cDst = T2A(tem_strFilePath);
			tem_dcm->SaveIMAGEtoDCM(tem_cSrc, tem_cDst);
			m_vcFilePath.push_back(tem_strFilePath);
			DeleteFile(tem_strDcmImg);
		}
			
	}
	else if (m_nLastMergeMode==2)
	{
		if (m_nLastImgType>=0 && m_nLastImgType<4)
		{
			for (int i=0; i<2; i++)
			{
				if (m_nLastRes==m_nInterpolateReso)
				{
					//将原图保存至缓存目录
					m_conOCX.CaptureCombineEx(tem_strInterImg, 0);

					//图像插值
					Self_InterPolateImage(tem_strInterImg, tem_strFilePath, 0);
					::DeleteFile(tem_strInterImg);
				} 
				else
				{
					m_conOCX.CaptureCombineEx(tem_strFilePath, 0);
				}
				
				if (m_nWaterMark == 1)
				{
					Self_AddWaterMark(tem_strFilePath);
				}
				if (tem_BFirst)
				{
					MessageBox(_T("点击确定，完成第二章拍摄！"), _T("紫图UDS"), MB_OK);
					tem_BFirst = FALSE;
				}
			}
			if (m_nUIMode == 0 || m_nUIMode == 3)
			{
				Self_CreateThumb(tem_strFilePath, tem_strThumbPath);
				m_vcImgName.push_back(tem_strImgName);
				m_vcThumbPath.push_back(tem_strThumbPath);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			}
			m_vcFilePath.push_back(tem_strFilePath);	
		} 
		else if (m_nLastImgType == 4)
		{
			for (int i=0; i<2; i++)
			{
				if (m_nLastRes==m_nInterpolateReso)
				{
					//将原图保存至缓存目录
					m_conOCX.CaptureCombineEx(tem_strInterImg, 0);

					//图像插值
					Self_InterPolateImage(tem_strInterImg, tem_strPdfImg, 0);
					::DeleteFile(tem_strInterImg);
				} 
				else
				{
					m_conOCX.CaptureCombineEx(tem_strPdfImg, 0);
				}
				
				if (m_nWaterMark == 1)
				{
					Self_AddWaterMark(tem_strPdfImg);
				}
				if (tem_BFirst)
				{
					MessageBox(_T("点击确定，完成第二章拍摄！"), _T("紫图UDS"), MB_OK);
					tem_BFirst = FALSE;
				}
			}
			if (m_nUIMode == 0 || m_nUIMode == 3)
			{
				Self_CreateThumb(tem_strPdfImg, tem_strThumbPath);
				m_vcImgName.push_back(tem_strImgName);
				m_vcThumbPath.push_back(tem_strThumbPath);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			}
			Self_GetPDFFromImg(tem_strPdfImg, tem_strFilePath);
			m_vcFilePath.push_back(tem_strFilePath);
			DeleteFile(tem_strPdfImg);			
		}
		else if (m_nLastImgType == 5)
		{
			for (int i=0; i<2; i++)
			{
				if (m_nLastRes==m_nInterpolateReso)
				{
					//将原图保存至缓存目录
					m_conOCX.CaptureCombineEx(tem_strInterImg, 0);

					//图像插值
					Self_InterPolateImage(tem_strInterImg, tem_strDcmImg, 0);
					::DeleteFile(tem_strInterImg);
				} 
				else
				{
					m_conOCX.CaptureCombineEx(tem_strDcmImg, 0);
				}
				
				if (m_nWaterMark == 1)
				{
					Self_AddWaterMark(tem_strDcmImg);
				}
				if (tem_BFirst)
				{
					MessageBox(_T("点击确定，完成第二章拍摄！"), _T("紫图UDS"), MB_OK);
					tem_BFirst = FALSE;
				}
			}
			if (m_nUIMode == 0 || m_nUIMode == 3)
			{
				Self_CreateThumb(tem_strDcmImg , tem_strThumbPath);
				m_vcImgName.push_back(tem_strImgName);
				m_vcThumbPath.push_back(tem_strThumbPath);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			}
			//生成dcm图像
			char*  tem_cName  = NULL;
			char*  tem_cId    = NULL;
			char*  tem_cBirth = NULL;
			char*  tem_cSex   = NULL;
			char*  tem_cDName = NULL;
			char*  tem_cDate  = NULL;
			char*  tem_cTime  = NULL;

			IMAGEAndDCM*   tem_dcm = new IMAGEAndDCM;
			tem_dcm->Set(tem_cName, tem_cId, tem_cBirth, tem_cSex, tem_cDName, tem_cDate, tem_cTime);

			USES_CONVERSION;  
			char*   tem_cSrc = T2A(tem_strDcmImg);
			char*   tem_cDst = T2A(tem_strFilePath);
			tem_dcm->SaveIMAGEtoDCM(tem_cSrc, tem_cDst);
			m_vcFilePath.push_back(tem_strFilePath);
			DeleteFile(tem_strDcmImg);
		}
	}
	else
	{
		if (m_nLastImgType>=0 && m_nLastImgType<4)
		{
			//普通拍照	
			if (m_nLastRes==m_nInterpolateReso)
			{
				//将原图保存至缓存目录
				m_conOCX.CaptureImage(tem_strInterImg);

				//图像插值
				Self_InterPolateImage(tem_strInterImg, tem_strFilePath, 0);
				::DeleteFile(tem_strInterImg);
			} 
			else
			{
				m_conOCX.CaptureImage(tem_strFilePath);
			}
			
			if (m_nWaterMark == 1)
			{
				Self_AddWaterMark(tem_strFilePath);
			}
			if (m_nUIMode == 0 || m_nUIMode == 3)
			{
				Self_CreateThumb(tem_strFilePath, tem_strThumbPath);
				m_vcImgName.push_back(tem_strImgName);
				m_vcThumbPath.push_back(tem_strThumbPath);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			}
			m_vcFilePath.push_back(tem_strFilePath);
			
		}
		else if (m_nLastImgType == 4)
		{
			//pdf拍照
			/*流程一：OCX自带pdf拍照，但无法添加自定义水印*/
			/*
			m_conOCX.CapturePDF(tem_strFilePath);
			Self_GetImgFromPDF(tem_strFilePath, tem_strThumbPath);
			m_vcImgName.push_back(tem_strImgName);
			m_vcThumbPath.push_back(tem_strThumbPath);
			m_vcFilePath.push_back(tem_strFilePath);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			*/

			/*流程二：拍摄普通图像再转换为pdf文件*/
			//拍摄图像保存至缓存目录
			if (m_nLastRes==m_nInterpolateReso)
			{
				//将原图保存至缓存目录
				m_conOCX.CaptureImage(tem_strInterImg);

				//图像插值
				Self_InterPolateImage(tem_strInterImg, tem_strDcmImg, 0);
				::DeleteFile(tem_strInterImg);
			} 
			else
			{
				m_conOCX.CaptureImage(tem_strDcmImg);	
			}

			if (m_nWaterMark == 1)
			{
				Self_AddWaterMark(tem_strDcmImg);
			}
			//获取缩略图
			if (m_nUIMode == 0 || m_nUIMode == 3)
			{
				Self_CreateThumb(tem_strDcmImg , tem_strThumbPath);
				m_vcImgName.push_back(tem_strImgName);
				m_vcThumbPath.push_back(tem_strThumbPath);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			}
			//获取pdf文件
			Self_GetPDFFromImg(tem_strDcmImg, tem_strFilePath);
			m_vcFilePath.push_back(tem_strFilePath);
			DeleteFile(tem_strDcmImg);
		}
		else if (m_nLastImgType == 5)
		{
			//dcm拍照
			if (m_nLastRes==m_nInterpolateReso)
			{
				//将原图保存至缓存目录
				m_conOCX.CaptureImage(tem_strInterImg);
				//图像插值
				Self_InterPolateImage(tem_strInterImg, tem_strDcmImg, 0);
				::DeleteFile(tem_strInterImg);
			} 
			else
			{
				m_conOCX.CaptureImage(tem_strDcmImg);	
			}
			
			if (m_nWaterMark == 1)
			{
				Self_AddWaterMark(tem_strDcmImg);
			}
			if (m_nUIMode == 0 || m_nUIMode == 3)
			{
				Self_CreateThumb(tem_strDcmImg , tem_strThumbPath);
				m_vcImgName.push_back(tem_strImgName);
				m_vcThumbPath.push_back(tem_strThumbPath);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			}
			//生成dcm图像
			char*  tem_cName  = NULL;
			char*  tem_cId    = NULL;
			char*  tem_cBirth = NULL;
			char*  tem_cSex   = NULL;
			char*  tem_cDName = NULL;
			char*  tem_cDate  = NULL;
			char*  tem_cTime  = NULL;

			IMAGEAndDCM*   tem_dcm = new IMAGEAndDCM;
			tem_dcm->Set(tem_cName, tem_cId, tem_cBirth, tem_cSex, tem_cDName, tem_cDate, tem_cTime);

			USES_CONVERSION;  
			char*   tem_cSrc = T2A(tem_strDcmImg);
			char*   tem_cDst = T2A(tem_strFilePath);
			tem_dcm->SaveIMAGEtoDCM(tem_cSrc, tem_cDst);
			m_vcFilePath.push_back(tem_strFilePath);
			DeleteFile(tem_strDcmImg);
		}
	}
	if (m_nUIMode==0 ||m_nUIMode==3)
	{
		Self_ShowImgInfo(tem_strFilePath);
	}
	
	m_nImageCount++;
	//如果拍摄模式为<透射稿>则校准灯箱
	if (!m_BDOC)
	{
		int tem_nSave = m_nLastRelay;
		Self_SetRelayZero();
		m_nLastRelay = tem_nSave;
		AdjustRelay(m_nLastRelay, 0);
	}
}


CString CSmartFilmUI::Self_InterPolateImage(CString srcImage, CString dstImage, int index)
{
	int       tem_nInterpolateIndex = index;
	int       tem_nGoalResoW        = 0;          //目标分辨率
	int       tem_nGoalResoH        = 0;
	float     tem_fRateW            = 0;          //转换率宽
	float     tem_fRateH            = 0;

	long*     tem_lWidth;
	tem_lWidth  = new long;
	long*     tem_lHeight;  
	tem_lHeight = new long;
	float     tem_fWidth;
	float     tem_fHeight;

	CString   tem_strSrcImage       = srcImage;     //原图路径
	CString   tem_strDstImage       = dstImage;     //目标图路径

	CxImage   tem_cxSrcImage;
	tem_cxSrcImage.Load(tem_strSrcImage);
	m_conOCX.GetCurResolution(tem_lWidth, tem_lHeight);
	tem_fWidth  = *tem_lWidth;
	tem_fHeight = *tem_lHeight;


	tem_fRateW = 4480/(4032*1.0);
	tem_fRateH = 3360/(3024*1.0);


	tem_nGoalResoW = (int)(tem_cxSrcImage.GetWidth()*tem_fRateW );
	tem_nGoalResoH = (int)(tem_cxSrcImage.GetHeight()*tem_fRateH);

	tem_cxSrcImage.Resample(tem_nGoalResoW, tem_nGoalResoH);

	//判断图像格式
	int      tem_nFormat   = -1;
	CString  tem_strFormat = _T("");
	tem_strFormat = srcImage;
	tem_nFormat = tem_strFormat.ReverseFind('.');
	tem_strFormat = tem_strFormat.Mid(tem_nFormat+1);
	tem_strFormat.MakeLower();
	if (tem_strFormat == _T("bmp"))
	{
		tem_cxSrcImage.Save(tem_strDstImage, CXIMAGE_FORMAT_BMP);
	}
	else if (tem_strFormat == _T("jpg"))
	{
		tem_cxSrcImage.SetJpegQuality(100);
		tem_cxSrcImage.Save(tem_strDstImage, CXIMAGE_FORMAT_JPG);
	}
	else if (tem_strFormat == _T("tif"))
	{
		tem_cxSrcImage.Save(tem_strDstImage, CXIMAGE_FORMAT_TIF);
	}
	else if (tem_strFormat == _T("png"))
	{
		tem_cxSrcImage.SetJpegQuality(50);
		tem_cxSrcImage.Save(tem_strDstImage, CXIMAGE_FORMAT_PNG);
	}

	tem_cxSrcImage.Destroy();

	return tem_strDstImage;
}


void CSmartFilmUI::Self_AddWaterMark(CString imgpath)
{
	//1、获取水印格式信息
	int       tem_nSite;
	int       tem_nOffSetX;   //水印坐标
	int       tem_nOffSetY; 
	int       tem_nSize   = Self_GetFontSize(m_nWaterSize);
	int       tem_nStrWidth;
	CString   tem_strFont = Self_GetFontName(m_nWaterFont);
	CString   tem_strInfo = _T("");

	CxImage*  tem_pImage;
	tem_pImage = new CxImage;
	tem_pImage->Load(imgpath, CMAX_IMAGE_FORMATS);
	tem_pImage->IncreaseBpp(24);

	CxImage::CXTEXTINFO WMTxtInfo;                  // 授权文字水印
	tem_pImage->InitTextInfo( &WMTxtInfo );
	_stprintf(WMTxtInfo.lfont.lfFaceName, tem_strFont);
	WMTxtInfo.lfont.lfCharSet = GB2312_CHARSET;
	WMTxtInfo.lfont.lfHeight = tem_nSize;
//	WMTxtInfo.lfont.lfWeight = 20;
	WMTxtInfo.lfont.lfItalic = 0;
	WMTxtInfo.lfont.lfUnderline = 0;


	int      tem_nFind;
	CString  tem_strRead;
	CString  tem_strSinColor[3];
	CString  tem_strWaterColor = m_strWaterColor;
	tem_nFind = tem_strWaterColor.Find('|');
	int i=0;
	while (tem_nFind != -1)
	{
		tem_strRead = tem_strWaterColor.Mid(0, tem_nFind);
		tem_strSinColor[i]= tem_strRead;
		tem_strWaterColor = tem_strWaterColor.Mid(tem_nFind+1);
		tem_nFind  = tem_strWaterColor.Find('|');
		i++;
	}
	m_nRedValue   = _ttoi(tem_strSinColor[0]);
	m_nGreenValue = _ttoi(tem_strSinColor[1]);
	m_nBlueValue  = _ttoi(tem_strSinColor[2]);
	WMTxtInfo.fcolor = RGB(m_nRedValue, m_nGreenValue, m_nBlueValue);
	WMTxtInfo.opaque = 0;                        //背景
	WMTxtInfo.b_opacity = (float)(1);            //透明度
	WMTxtInfo.b_round = (BYTE)10;
	
	
	if (m_nWaterMode == 1)
	{
		//时间水印
		tem_strInfo = Self_GetTimeInfo();
	} 
	else
	{
		//文字水印
		tem_strInfo = m_strWaterInfo;
	}
	
	//获取水印文本的像素尺寸
	tem_nStrWidth = Self_GetFontWidth(WMTxtInfo.lfont, tem_strInfo);

	if (tem_strFont == _T("Arial"))
	{
		//Arial
		tem_nStrWidth = (tem_nStrWidth/2 + tem_nStrWidth/12);   //15时中文刚好，但英文溢出
	}
	else if (tem_strFont == _T("Calibri"))
	{
		//Calibri
		tem_nStrWidth = (tem_nStrWidth/2 + tem_nStrWidth/4);    //10时中文刚好，但英文会出
	}
	else if (tem_strFont == _T("Times New Roman"))
	{
		//Times
		tem_nStrWidth = (tem_nStrWidth/2 + tem_nStrWidth/7);
	}
	else if (tem_strFont == _T("隶书"))
	{
		//隶书
		tem_nStrWidth = (tem_nStrWidth/2 + tem_nStrWidth/11);
	}
	else 
	{
		//宋体、楷体、仿宋、黑体、雅黑、新宋
		tem_nStrWidth = tem_nStrWidth/2;
	}	

	if (m_nWaterSite == 0)
	{
		//左上角
		tem_nOffSetX = 0;
		tem_nOffSetY = tem_nSize;
	}
	else if (m_nWaterSite == 1)
	{
		//左下角
		tem_nOffSetX = 0;
		tem_nOffSetY = tem_pImage->GetHeight();
	}
	else if (m_nWaterSite == 2)
	{
		//右上角
		tem_nOffSetX = tem_pImage->GetWidth()-tem_nStrWidth;
		tem_nOffSetY = tem_nSize;
	}
	else if (m_nWaterSite == 3)
	{
		//右下角
		tem_nOffSetX = tem_pImage->GetWidth()-tem_nStrWidth;
		tem_nOffSetY = tem_pImage->GetHeight();
	}
	else
	{
		//居中
		tem_nOffSetX = tem_pImage->GetWidth()/2;
		tem_nOffSetY = tem_pImage->GetHeight()/2;
	}
	
	_stprintf(WMTxtInfo.text, tem_strInfo);
	tem_pImage->DrawStringEx(0, tem_nOffSetX, tem_nOffSetY, &WMTxtInfo);

	//根据后缀判断文件类型
	CString     tem_strFormat;
	tem_strFormat = PathFindExtension(imgpath);
	tem_strFormat.MakeLower();
	if (tem_strFormat==_T(".bmp"))
	{
		tem_pImage->Save(imgpath, CXIMAGE_FORMAT_BMP);
	}
	else if (tem_strFormat==_T(".jpg"))
	{
		tem_pImage->Save(imgpath, CXIMAGE_FORMAT_JPG);
	}
	else if (tem_strFormat==_T(".png"))
	{
		tem_pImage->Save(imgpath, CXIMAGE_FORMAT_PNG);
	}
	else if (tem_strFormat==_T(".tif"))
	{
		tem_pImage->Save(imgpath, CXIMAGE_FORMAT_TIF);
	}
	delete tem_pImage;	
}


CString CSmartFilmUI::Self_CreateThumb(CString srcimg, CString dstimg)
{
	CString   tem_strSrcImg = srcimg;
	CString   tem_strDstImg = dstimg;

	int       tem_nImageType=GetTypeFromFileName(tem_strSrcImg);
	if(tem_nImageType==CXIMAGE_FORMAT_UNKNOWN)
	{
		return tem_strSrcImg;
	}
	CxImage*  tem_pImage;
	tem_pImage = new CxImage;
	tem_pImage->Load(tem_strSrcImg, tem_nImageType);
	if(tem_pImage->IsValid()==false)
	{
		return tem_strSrcImg;
	}
	if (tem_pImage->GetBpp()==1)
	{
		tem_pImage->IncreaseBpp(24);
	}
	int   cx = 160;
	int   cy = (int)160*tem_pImage->GetHeight()/tem_pImage->GetWidth();
	tem_pImage->Resample(cx, cy, 1, NULL);
	tem_pImage->Save(tem_strDstImg, CXIMAGE_FORMAT_JPG);

	delete tem_pImage;
	return tem_strDstImg;
}


int CSmartFilmUI::GetTypeFromFileName(LPCTSTR pstr)
{
	CString fileName(pstr);
	CString ext3=fileName.Right(3);
	CString ext4=fileName.Right(4);
#if CXIMAGE_SUPPORT_BMP
	if(ext3.CompareNoCase(_T("bmp"))==0)
		return CXIMAGE_FORMAT_BMP;
#endif

#if CXIMAGE_SUPPORT_GIF
	if(ext3.CompareNoCase(_T("gif"))==0)
		return CXIMAGE_FORMAT_GIF;
#endif

#if CXIMAGE_SUPPORT_JPG
	if(ext3.CompareNoCase(_T("jpg"))==0 || ext4.CompareNoCase(_T("jpeg"))==0)
		return CXIMAGE_FORMAT_JPG;
#endif

#if CXIMAGE_SUPPORT_PNG
	if(ext3.CompareNoCase(_T("png"))==0)
		return CXIMAGE_FORMAT_PNG;
#endif

#if CXIMAGE_SUPPORT_MNG
	if(ext3.CompareNoCase(_T("mng"))==0 || ext3.CompareNoCase(_T("jng"))==0 ||ext3.CompareNoCase(_T("png"))==0)
		return CXIMAGE_FORMAT_MNG;
#endif

#if CXIMAGE_SUPPORT_ICO
	if(ext3.CompareNoCase(_T("ico"))==0)
		return CXIMAGE_FORMAT_ICO;
#endif

#if CXIMAGE_SUPPORT_TIF
	if(ext3.CompareNoCase(_T("tif"))==0 || ext4.CompareNoCase(_T("tiff"))==0)
		return CXIMAGE_FORMAT_TIF;
#endif

#if CXIMAGE_SUPPORT_TGA
	if(ext3.CompareNoCase(_T("tga"))==0)
		return CXIMAGE_FORMAT_TGA;
#endif

#if CXIMAGE_SUPPORT_PCX
	if(ext3.CompareNoCase(_T("pcx"))==0)
		return CXIMAGE_FORMAT_PCX;
#endif

#if CXIMAGE_SUPPORT_WBMP
	if(ext4.CompareNoCase(_T("wbmp"))==0)
		return CXIMAGE_FORMAT_WBMP;
#endif

#if CXIMAGE_SUPPORT_WMF
	if(ext3.CompareNoCase(_T("wmf"))==0 || ext3.CompareNoCase(_T("emf"))==0)
		return CXIMAGE_FORMAT_WMF;
#endif

#if CXIMAGE_SUPPORT_J2K
	if(ext3.CompareNoCase(_T("j2k"))==0 || ext3.CompareNoCase(_T("jp2"))==0)
		return CXIMAGE_FORMAT_J2K;
#endif

#if CXIMAGE_SUPPORT_JBG
	if(ext3.CompareNoCase(_T("jbg"))==0)
		return CXIMAGE_FORMAT_JBG;
#endif

#if CXIMAGE_SUPPORT_JP2
	if(ext3.CompareNoCase(_T("j2k"))==0 || ext3.CompareNoCase(_T("jp2"))==0)
		return CXIMAGE_FORMAT_JP2;
#endif

#if CXIMAGE_SUPPORT_JPC
	if(ext3.CompareNoCase(_T("j2c"))==0 || ext3.CompareNoCase(_T("jpc"))==0)
		return CXIMAGE_FORMAT_JPC;
#endif

#if CXIMAGE_SUPPORT_PGX
	if(ext3.CompareNoCase(_T("pgx"))==0)
		return CXIMAGE_FORMAT_PGX;
#endif

#if CXIMAGE_SUPPORT_PNM
	if(ext3.CompareNoCase(_T("pnm"))==0 || ext3.CompareNoCase(_T("pgm"))==0 || ext3.CompareNoCase(_T("ppm"))==0)
		return CXIMAGE_FORMAT_PNM;
#endif

#if CXIMAGE_SUPPORT_RAS
	if(ext3.CompareNoCase(_T("ras"))==0)
		return CXIMAGE_FORMAT_RAS;
#endif

	return CXIMAGE_FORMAT_UNKNOWN;
}


int CSmartFilmUI::Self_GetFontSize(int index)
{
	int tem_nFontSize = 0;
	switch (index)
	{
	case 0:
		tem_nFontSize = 10;
		break;
	case 1:
		tem_nFontSize = 20;
		break;
	case 2:
		tem_nFontSize = 30;
		break;
	case 3:
		tem_nFontSize = 40;
		break;
	case 4:
		tem_nFontSize = 50;
		break;
	case 5:
		tem_nFontSize = 70;
		break;
	case 6:
		tem_nFontSize = 90;
		break;
	case 7:
		tem_nFontSize = 120;
		break;
	case 8:
		tem_nFontSize = 150;
		break;
	case 9:
		tem_nFontSize = 200;
		break;
	default:
		tem_nFontSize = 20;
		break;
	}
	return tem_nFontSize;
}


CString CSmartFilmUI::Self_GetFontName(int index)
{
	CString   tem_strFontName = _T("");
	switch(index)
	{
	case 0:
		tem_strFontName = _T("Arial");
		break;
	case 1:
		tem_strFontName = _T("Calibri");
		break;
	case 2:
		tem_strFontName = _T("Times New Roman");
		break;
	case 3:
		tem_strFontName = _T("宋体");
		break;
	case 4:
		tem_strFontName = _T("楷体");
		break;
	case 5:
		tem_strFontName = _T("仿宋");
		break;
	case 6:
		tem_strFontName = _T("黑体");
		break;
	case 7:
		tem_strFontName = _T("隶书");
		break;
	case 8:
		tem_strFontName = _T("微软雅黑");
		break;
	case 9:
		tem_strFontName = _T("新宋体");
		break;
	default:
		tem_strFontName = _T("宋体");
		break;
	}
	return tem_strFontName;
}


BOOL CSmartFilmUI::ThumbaiList(int thumbwidth, int thumbheight)
{
	int          m_nImageIndex= 0;
	DWORD  dwStyle;
	//CImageList初始化
	m_imagelist.Create(thumbwidth,thumbheight,ILC_COLOR24,0,1);

	//ListCtrl初始化
	dwStyle = m_conListCtrl.GetExtendedStyle();
	dwStyle=dwStyle|LVS_SHOWSELALWAYS|LVS_ALIGNTOP|LVS_ICON|LVS_AUTOARRANGE;
	m_conListCtrl.SetExtendedStyle(dwStyle);
	m_conListCtrl.SetImageList(&m_imagelist,LVSIL_NORMAL);
	for(int i=0;i<m_imagelist.GetImageCount();i++)
	{
		m_imagelist.Remove(i);
	}
	m_conListCtrl.DeleteAllItems();
	m_imagelist.SetImageCount(m_vcImgName.size()); 

	wchar_t path[MAX_PATH]; 
	std::vector<CString>::iterator iter1;
	std::vector<CString>::iterator iter2;
	m_conListCtrl.SetRedraw(false);
	m_nImageIndex = 0;
	m_conListCtrl.SetTextBkColor(RGB(255,255,255));
	m_conListCtrl.SetTextColor(RGB(0, 0, 0));
	for(iter1=m_vcImgName.begin();iter1!=m_vcImgName.end();iter1++,m_nImageIndex++)
	{
		m_conListCtrl.InsertItem(m_nImageIndex,*iter1,m_nImageIndex);
	}
	m_conListCtrl.SetRedraw(true);
	m_conListCtrl.Invalidate();

	HBRUSH hBrushBorder    =::CreateSolidBrush(RGB(220,220,220));
	HBRUSH hBrushBkground  =::CreateSolidBrush(RGB(255,255,255));



	RECT rcBorder;
	rcBorder.left=rcBorder.top  =0;
	rcBorder.right              =thumbwidth;
	rcBorder.bottom             =thumbheight;

	float fRatio=(float)thumbheight/thumbwidth; 

	int XDest,YDest,nDestWidth,nDestHeight;
	m_nImageIndex=0;

	for(iter2=m_vcThumbPath.begin();iter2!=m_vcThumbPath.end();iter2++,m_nImageIndex++)
	{
		_stprintf(path,*iter2);
		int nImageType=GetTypeFromFileName(path);
		if(nImageType==CXIMAGE_FORMAT_UNKNOWN)
			continue;
		CxImage image;
		image.Load(path, nImageType);
		if(image.IsValid()==false)
			continue;
		float fImgRatio=(float)image.GetHeight()/image.GetWidth();  
		if(fImgRatio>fRatio)
		{
			nDestWidth=(int)thumbheight/fImgRatio;   
			XDest=(thumbwidth-nDestWidth)/2;
			YDest=0;
			nDestHeight=thumbheight;
		}
		else
		{
			XDest=0;
			nDestWidth=thumbwidth;
			nDestHeight=(int)thumbwidth*fImgRatio;  
			YDest=(thumbheight-nDestHeight)/2;
		}

		CClientDC cdc(this);
		HDC hDC=::CreateCompatibleDC(cdc.m_hDC);
		HBITMAP bm=CreateCompatibleBitmap(cdc.m_hDC,thumbwidth,thumbheight);
		HBITMAP pOldBitmapImage=(HBITMAP)SelectObject(hDC,bm);

		::FillRect(hDC,&rcBorder,hBrushBkground);
		image.Stretch(hDC,XDest,YDest,nDestWidth,nDestHeight);
		::FrameRect(hDC,&rcBorder,hBrushBorder);
		SelectObject(hDC,pOldBitmapImage);
		CBitmap bitmap;
		bitmap.Attach(bm);
		m_imagelist.Replace(m_nImageIndex,&bitmap,NULL);
		m_conListCtrl.RedrawItems(m_nImageIndex,m_nImageIndex);

		DeleteDC(hDC);
		DeleteObject(bm);
	}
	DeleteObject(hBrushBorder);
	DeleteObject(hBrushBkground);
	int tem_nCount = m_conListCtrl.GetItemCount();
	if (tem_nCount>0)
	{

		m_conListCtrl.EnsureVisible(tem_nCount-1, FALSE);
	}
	m_conListCtrl.Invalidate();

	return TRUE;
}


CString CSmartFilmUI::Self_GetTimeInfo(void)
{
	SYSTEMTIME   tem_stDateTime;
	CString      tem_strDate = _T("");
	CString      tem_strTime = _T("");
	CString      tem_strTimeName  = _T("");       //时间命名

	GetLocalTime(&tem_stDateTime);
	tem_strDate.Format(_T("%d-%02d-%02d "), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
	tem_strTime.Format(_T("%02d:%02d:%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond);

	tem_strTimeName  = tem_strDate;
	tem_strTimeName += tem_strTime;

	return tem_strTimeName;
	return CString();
}


int CSmartFilmUI::Self_GetFontWidth(LOGFONT text, CString textinfo)
{
	CFont     tem_fontInput;
	LOGFONT   tem_fontInfo;

	memset(&tem_fontInfo, 0, sizeof(LOGFONT));
	tem_fontInfo.lfHeight = text.lfHeight;
	_stprintf(tem_fontInfo.lfFaceName, text.lfFaceName);
	VERIFY(tem_fontInput.CreateFontIndirect(&tem_fontInfo));

	CClientDC  tem_dc(this);
	CFont* def_font = tem_dc.SelectObject(&tem_fontInput);
	CSize  sztext = tem_dc.GetTextExtent(textinfo);
	int    tem_nStrLength = sztext.cx;

	tem_dc.SelectObject(def_font);
	tem_fontInput.DeleteObject();

	return tem_nStrLength;
}


CString CSmartFilmUI::Self_GetPDFFromImg(CString imgpath, CString pdfpath)
{
	
	CString   tem_strInputPath  = imgpath;     //导入图像路径
	CString   tem_strOutputPath = pdfpath;     //导出PDF路径


	//导出PDF--------
	int       doc, page, image, code, pagenum=2;
	wstring    outfile;
	outfile = tem_strOutputPath.GetBuffer(0);
	tem_strOutputPath.ReleaseBuffer();
	PDFlib*    pPdf;
	pPdf = new PDFlib;
	try
	{
		//		pPdf->set_parameter("License", "w700602-009100-731090-Y6WPH2-5SE4A2");
		pPdf->set_parameter(_T("nodemostamp"), _T("false"));
		pPdf->set_parameter(_T("errorpolicy"), _T("return"));
		//		pPdf->set_parameter(_T("hypertextencoding"), _T("host"));

		code = pPdf->begin_document(outfile, _T(""));
		if (code == -1)
		{
			return tem_strInputPath;
		}
		//设置PDF属性信息******************************************************
		pPdf->set_info(_T("Creator"), _T("SmartScan"));   
		pPdf->set_info(_T("Author"), _T("UDS"));   
		pPdf->set_info(_T("Title"), _T("UDSPDF")); 
		pPdf->set_info(_T("Subject"), _T("扫描文档"));

		//图片导入***********************************************************
		{

			wstring sFilePath(tem_strInputPath.GetBuffer());
			image = pPdf->load_image(_T("auto"), sFilePath, _T(""));
			pPdf->begin_page_ext(10, 10, _T(""));
			pPdf->fit_image(image, 0, 0, _T("adjustpage dpi=0"));  //导入图像
			pPdf->close_image(image);
			pPdf->end_page_ext(_T(""));
		}		
		pPdf->end_document(_T(""));	
	}
	catch (PDFlib::Exception e)
	{
		int     num=-1;
		wstring  str;
		CString str2, str3;
		str = e.get_errmsg();
		num = e.get_errnum();
		str2 = str.c_str();
		str3.Format(_T("%d"), num);
	}

	return tem_strOutputPath;	
}


void CSmartFilmUI::OnDblclkListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int  tem_nListIndex = pNMItemActivate->iItem;
	if (tem_nListIndex>=0 && tem_nListIndex<m_conListCtrl.GetItemCount())
	{
		CString   tem_strSlcPath = m_vcFilePath[tem_nListIndex];
		ShellExecute(NULL, _T("open"), tem_strSlcPath, NULL, NULL, SW_SHOWNORMAL);
	}
	*pResult = 0;
}


//右键菜单-TrackPopupMenu闪退，暂时取消-----------------------------------------------
void CSmartFilmUI::OnRclickListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	/*
	m_nRSlcIndex = pNMItemActivate->iItem;
	if (m_nRSlcIndex>=0 && m_nRSlcIndex<m_conListCtrl.GetItemCount())
	{
		CPoint  tem_ptRight;
		GetCursorPos(&tem_ptRight);
		CMenu*    pPopup = m_ListMenu.GetSubMenu(0);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN, tem_ptRight.x, tem_ptRight.y, this);
	}
	*/

	*pResult = 0;
}


void CSmartFilmUI::On32768Delte()
{
	// TODO: 在此添加命令处理程序代码
}


void CSmartFilmUI::On32769Property()
{
	// TODO: 在此添加命令处理程序代码
}
//----------------------------------------------------------------------------------

void CSmartFilmUI::Self_ShowImgInfo(CString imgpath)
{
	CString      tem_strFileByte;
	CString      tem_strImageInfo  = _T("图像大小：");

	CFile        tem_FileImg;
	ULONGLONG    tem_ullSize;

	if (tem_FileImg.Open(imgpath, CFile::modeRead))
	{
		tem_ullSize = tem_FileImg.GetLength();
		if (tem_ullSize>1024)
		{
			//转换为kb显示
			tem_ullSize = tem_ullSize/1024;
			tem_strFileByte.Format(_T("%I64d"), tem_ullSize);
			tem_strImageInfo += tem_strFileByte;
			tem_strImageInfo += _T("kb");

		}
		else
		{
			//使用字节表示
			tem_strFileByte.Format(_T("%I64d"), tem_ullSize);
			tem_strImageInfo += tem_strFileByte;
			tem_strImageInfo += _T("b");
		}
		m_dlgGet.Self_ShowImgInfo(tem_strImageInfo);
	}	
}


void CSmartFilmUI::Self_ShowOcxCtrl(void)
{
	if (m_BShowPicCtrl)
	{
		Self_ClearPicCtrl();
		GetDlgItem(IDC_STA_PIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(TRUE);
		m_BShowPicCtrl = FALSE;
		::SendMessage(g_hMainHwnd, WM_SIZE, 0, 0);
	}
}


void CSmartFilmUI::Self_ShowPicCtrl(void)
{
	if (m_vcFilePath.size() == 0)
	{
		return;
	}
	BOOL    tem_BMark        = FALSE;
	CString tem_strImgPath   = _T("");
	CString tem_strDstPath   = m_strCVDoc;
	CString tem_strImgFormat = _T("");
	if (m_nPrcsIndex == -1)
	{
		for (int i=m_vcFilePath.size()-1; i>=0; i--)
		{
			m_nPrcsIndex   = i;
			tem_strImgPath = m_vcFilePath[i];
			//判断是否为图像文件
			tem_strImgFormat = PathFindExtension(tem_strImgPath);
			tem_strImgFormat.MakeLower();
			if (tem_strImgFormat != _T(".pdf") && tem_strImgFormat != _T(".dcm"))
			{
				tem_BMark = TRUE;
				//显示图像


				//取消原高亮选项
				//高亮该项缩略图
				m_conListCtrl.SetFocus();
				int tem_nLastItem = m_conListCtrl.GetSelectedColumn();
				m_conListCtrl.SetItemState(m_conListCtrl.SetSelectionMark(tem_nLastItem),0,LVIS_SELECTED); 
				m_conListCtrl.SetItemState(i, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
				break;
			}
		}
	}

	else
	{
		tem_strImgPath = m_vcFilePath[m_nPrcsIndex];
		//判断是否为图像文件
		tem_strImgFormat = PathFindExtension(tem_strImgPath);
		tem_strImgFormat.MakeLower();
		if (tem_strImgFormat != _T(".pdf") && tem_strImgFormat != _T(".dcm"))
		{
			tem_BMark = TRUE;
		}
		else
		{
			tem_BMark = FALSE;
		}
	}
	
	if (!tem_BMark)
	{
		//没有图像格式文件
		m_nPrcsIndex = -1;
		m_strTabImg = _T("");

		GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_PIC)->ShowWindow(SW_NORMAL);
		m_BShowPicCtrl = TRUE;

		::SendMessage(g_hMainHwnd, WM_SIZE, 0, 0);

		//显示提示信息	
		Self_CVShowTipImage(_T("res\\tips.jpg"));

		return;
	}

	GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STA_PIC)->ShowWindow(SW_NORMAL);
	m_BShowPicCtrl = TRUE;
	::SendMessage(g_hMainHwnd, WM_SIZE, 0, 0);
	m_strTabImg = tem_strImgPath;
	Self_CVShowImage(tem_strImgPath);
}


void CSmartFilmUI::Self_CVShowImage(CString imgpath)
{
	m_vcHistoryImg.clear();
	CString tem_strImgPath   = imgpath;
	CString tem_strDstPath   = m_strCVDoc;
	CString tem_strFileName  = _T("");

	tem_strFileName = PathFindFileName(tem_strImgPath);
	tem_strDstPath += _T("\\");
	tem_strDstPath += tem_strFileName;

	CopyFile(tem_strImgPath, tem_strDstPath, FALSE);

	m_strFilesPath     = tem_strImgPath;
	m_strBufferImgPath = tem_strDstPath;

	m_vcHistoryImg.push_back(tem_strImgPath);
	m_vcHistoryImg.push_back(tem_strDstPath);
	std::string strTempData = (CStringA)tem_strDstPath;
	m_cvSrcImage = imread(strTempData);
	if (!m_cvSrcImage.data)
	{
		MessageBox(_T("加载图像失败！"), _T("UDS"), MB_OK);
	}

	Self_ResetImageRect();
	Self_ResizeImage(GetDlgItem(IDC_STA_PIC), m_cvSrcImage);
	Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
}


void CSmartFilmUI::Self_ResetImageRect(void)
{
	if (!m_BPaintLine)
	{
		m_rcImageRect.left     = 0;
		m_rcImageRect.top      = 0;
		m_rcImageRect.right    = m_cvSrcImage.cols;
		m_rcImageRect.bottom   = m_cvSrcImage.rows;
	}
	else
	{
		m_rcImageRect.left     = 0;
		m_rcImageRect.top      = 0;
		m_rcImageRect.right    = m_cvDstImage.cols;
		m_rcImageRect.bottom   = m_cvDstImage.rows;
	}
}


void CSmartFilmUI::Self_ResizeImage(CWnd* pWnd, Mat srcImg)
{
	float m_ratio;
	float m_i_w, m_i_h, m_p_w, m_p_h;
	pWnd->GetClientRect(&m_rcPicRect);
	m_i_w = (float)srcImg.cols;          //图像宽、高
	m_i_h = (float)srcImg.rows;
	m_p_w = (float)m_rcPicRect.right;    //控件宽、高
	m_p_h = (float)m_rcPicRect.bottom;
	if (srcImg.cols<=m_rcPicRect.right && srcImg.rows<=m_rcPicRect.bottom)
	{
		//图像尺寸<=边框尺寸
		m_nDrawX           = ((m_rcPicRect.right-m_rcPicRect.left)-srcImg.cols)/2;
		m_nDrawY           = ((m_rcPicRect.bottom-m_rcPicRect.top)-srcImg.rows)/2;
		m_rcPicRect.right  = srcImg.cols;
		m_rcPicRect.bottom = srcImg.rows;
		m_fCurRatio        = 1;
	}
	else if ((srcImg.cols*m_rcPicRect.bottom)>(srcImg.rows*m_rcPicRect.right))
	{
		//图像教宽，按照图像宽进行缩放
		int  tem_nPicHeight = m_rcPicRect.bottom - m_rcPicRect.top;
		m_ratio = m_p_w/m_i_w;
		m_rcPicRect.bottom = (int)(srcImg.rows*m_ratio);
		m_nDrawX = 0;
		m_nDrawY = (tem_nPicHeight - m_rcPicRect.bottom)/2;
		m_fCurRatio = m_ratio;
	}
	else if ((srcImg.cols*m_rcPicRect.bottom)<(srcImg.rows*m_rcPicRect.right))
	{
		//图像教高，按照图像高进行缩放
		int  tem_nPicWidth = m_rcPicRect.right - m_rcPicRect.left;
		m_ratio = m_p_h/m_i_h;
		m_rcPicRect.right = (int)(srcImg.cols*m_ratio);
		m_nDrawX = (tem_nPicWidth - m_rcPicRect.right)/2;
		m_nDrawY = 0;
		m_fCurRatio = m_ratio;
	}
	else
	{
		//尺寸比例相同，按宽或高缩放均可
		m_nDrawY = 0;
		m_nDrawY = 0;
		m_ratio = m_p_h/m_i_h;
		m_rcPicRect.right = (int)(srcImg.cols*m_ratio);
		m_rcPicRect.bottom = (int)(srcImg.rows*m_ratio);
		m_fCurRatio = m_ratio;
	}
	m_rcImageShow.left   = m_nDrawX;
	m_rcImageShow.top    = m_nDrawY;
	m_rcImageShow.right  = m_rcPicRect.right+m_nDrawX;
	m_rcImageShow.bottom = m_rcPicRect.bottom+m_nDrawY;
	m_nShowWidth  = m_rcPicRect.right;
	m_nShowHeight = m_rcPicRect.bottom;
}


void CSmartFilmUI::Self_ShowMatImage2(Mat img, CRect rect)
{
	IplImage  tem_iplImage(img);
	CDC*   tem_pDC = GetDlgItem(IDC_STA_PIC)->GetDC();
	HDC    tem_hDC = tem_pDC->GetSafeHdc();

	CvvImage    tem_cvMidImage;
	tem_cvMidImage.CopyOf(&tem_iplImage, tem_iplImage.nChannels);
	tem_cvMidImage.DrawToHDC(tem_hDC, &m_rcImageShow, &m_rcImageRect);
	ReleaseDC(tem_pDC);
	tem_cvMidImage.Destroy();
}


void CSmartFilmUI::Self_CVShowTipImage(CString imgpath)
{
	CString tem_strImgPath   = imgpath;

	std::string strTempData = (CStringA)tem_strImgPath;
	m_cvTipsImg = imread(strTempData);

	m_rcImageRect.left     = 0;
	m_rcImageRect.top      = 0;
	m_rcImageRect.right    = m_cvTipsImg.cols;
	m_rcImageRect.bottom   = m_cvTipsImg.rows;

	Self_ResizeImage(GetDlgItem(IDC_STA_PIC), m_cvTipsImg);
	Self_ShowMatImage2(m_cvTipsImg, m_rcImageShow);
	m_cvSrcImage.release();
	m_cvDstImage.release();	
}


BOOL CSmartFilmUI::Self_EnsureSave(void)
{
	//确定图像处理是否保存
	if (m_vcFilePath.size()==0)
	{
		return FALSE;
	}
	if (m_vcHistoryImg.size()>2)
	{
		if (m_BNoSaved)
		{
			int tem_nClose = MessageBox(_T("修改尚未保存！是否保存？"), _T("保存"), MB_YESNO);
			if (tem_nClose == 6)
			{
				//确定保存
				CString tem_strNewImgPath = m_vcHistoryImg.back();
				CopyFile(tem_strNewImgPath, m_strFilesPath, FALSE);
				m_BNoSaved = FALSE;
				Self_UpdateThumb(m_nPrcsIndex, m_strFilesPath);
			}
			//无论是否保存修改都要清除缓存图像
			std::vector<CString>::iterator  item;
			for (item=m_vcHistoryImg.begin()+1; item!=m_vcHistoryImg.end(); item++)
			{
				DeleteFile(*item);
			}
		}
	}
	else if (m_vcHistoryImg.size()==2)
	{
		//删除缓存图像
		DeleteFile(m_vcHistoryImg[1]);
	}

	m_vcHistoryImg.clear();

	return TRUE;
}


void CSmartFilmUI::Self_UpdateThumb(int index, CString imgpath)
{
	if (index==-1)
	{
		return;
	}
	CString tem_strThumbPath = m_vcThumbPath[index];
	Self_CreateThumb(imgpath, tem_strThumbPath);
	Self_ReplaceImage(m_nThumbWidth, m_nThumbHeight, index);
}


void CSmartFilmUI::Self_ReplaceImage(int thumbwidth, int thumbheight, int item)
{
	CString    tem_strItemName = m_vcImgName[item];      //地址和名称对应vector中存放的文件的真实索引
	CString    tem_strItemPath = m_vcFilePath[item];
	m_conListCtrl.SetItemText(item, 0, tem_strItemName);

	HBRUSH hBrushBorder    =::CreateSolidBrush(RGB(220, 220, 220));
	HBRUSH hBrushBkground  =::CreateSolidBrush(RGB(255, 255, 255));   
	float fRatio=(float)thumbheight/thumbwidth; 
	RECT rcBorder;
	rcBorder.left=rcBorder.top  =0;
	rcBorder.right              =thumbwidth;
	rcBorder.bottom             =thumbheight;

	int XDest,YDest,nDestWidth,nDestHeight;
	CxImage    image; 
	int nImageType=GetTypeFromFileName(tem_strItemPath);
	image.Load(tem_strItemPath, nImageType);
	float fImgRatio=(float)image.GetHeight()/image.GetWidth();  
	if(fImgRatio>fRatio)
	{
		nDestWidth=(int)thumbheight/fImgRatio;   
		XDest=(thumbwidth-nDestWidth)/2;
		YDest=0;
		nDestHeight=thumbheight;
	}
	else
	{
		XDest=0;
		nDestWidth=thumbwidth;
		nDestHeight=(int)thumbwidth*fImgRatio;  
		YDest=(thumbheight-nDestHeight)/2;
	}

	CClientDC cdc(this);
	HDC hDC=::CreateCompatibleDC(cdc.m_hDC);
	HBITMAP bm=CreateCompatibleBitmap(cdc.m_hDC,thumbwidth,thumbheight);
	HBITMAP pOldBitmapImage=(HBITMAP)SelectObject(hDC,bm);

	::FillRect(hDC,&rcBorder,hBrushBkground);
	image.Stretch(hDC,XDest,YDest,nDestWidth,nDestHeight);
	::FrameRect(hDC,&rcBorder,hBrushBorder);
	SelectObject(hDC,pOldBitmapImage);
	CBitmap bitmap;
	bitmap.Attach(bm);
	m_imagelist.Replace(item,&bitmap,NULL);
	m_conListCtrl.RedrawItems(item, item);           //ListCtrl重绘对应当前页面中Item的索引
	DeleteDC(hDC);
	DeleteObject(bm);

	DeleteObject(hBrushBorder);
	DeleteObject(hBrushBkground);	
}


void CSmartFilmUI::Self_ClearPicCtrl(void)
{
	CRect    tem_rcPicCtrl;
	GetDlgItem(IDC_STA_PIC)->GetWindowRect(&tem_rcPicCtrl);
	ScreenToClient(&tem_rcPicCtrl);
	CWnd*  tem_pWnd = NULL;
	CDC*   tem_pDc  = NULL;
	tem_pWnd = GetDlgItem(IDC_STA_PIC);

	tem_pDc = tem_pWnd->GetDC();
	tem_pDc->FillSolidRect(0, 0, tem_rcPicCtrl.right-tem_rcPicCtrl.left, tem_rcPicCtrl.bottom-tem_rcPicCtrl.top,RGB(72,77,91));
	m_conPicCtrl.SetBitmap(NULL);
}



BOOL CSmartFilmUI::Self_ZoomSize(Mat src, float ratio, bool zoommark)
{
	int tem_nImageWidth  = src.cols;   //图像原始尺寸
	int tem_nImageHeight = src.rows;

	int tem_nThumbWidth  = 0;          //放大、缩小后缩略图尺寸
	int tem_nThumbHeight = 0;

	CRect   tem_rcPicRect; 
	GetDlgItem(IDC_STA_PIC)->GetWindowRect(&tem_rcPicRect);
	ScreenToClient(&tem_rcPicRect);


	float   tem_fCurRatio = ratio;

	int     tem_nDrawX, tem_nDrawY, tem_nDrawW, tem_nDrawH;   //映射起点以及宽高

	if (zoommark)
	{
		//放大************************************
		tem_fCurRatio += 0.05;        //一次放大5%
	}
	else
	{
		//缩小************************************
		tem_fCurRatio -= 0.05;        //一次缩小5%
	}
	if (tem_fCurRatio>=2.0)
	{
		tem_fCurRatio=2.0;
		return FALSE;
	}
	else if (tem_fCurRatio<=0.05)
	{
		tem_fCurRatio=0.05;
		return FALSE;
	}

	//放大后缩略图尺寸
	tem_nThumbWidth  = (int)(tem_fCurRatio*tem_nImageWidth);
	tem_nThumbHeight = (int)(tem_fCurRatio*tem_nImageHeight);
	//1)放大后缩略图尺寸<picture控件尺寸
	if (tem_nThumbWidth<tem_rcPicRect.Width() && tem_nThumbHeight<tem_rcPicRect.Height())
	{
		//picture显示区域
		tem_nDrawX           = (tem_rcPicRect.Width()-tem_nThumbWidth)/2;
		tem_nDrawY           = (tem_rcPicRect.Height()-tem_nThumbHeight)/2;
		tem_nDrawW           = tem_nThumbWidth;
		tem_nDrawH           = tem_nThumbHeight;
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//图像显示区域
		m_rcImageRect.left     = 0;
		m_rcImageRect.top      = 0;
		m_rcImageRect.right    = m_cvSrcImage.cols;
		m_rcImageRect.bottom   = m_cvSrcImage.rows;
	}
	//2)放大后缩略图宽<picture宽，且缩略图高>picture高
	else if (tem_nThumbWidth<tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
	{
		//picture显示区域
		tem_nDrawX           = (tem_rcPicRect.Width()-tem_nThumbWidth)/2;
		tem_nDrawY           = 0;
		tem_nDrawW           = tem_nThumbWidth;
		tem_nDrawH           = tem_rcPicRect.Height();
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//图像显示区域
		m_rcImageRect.left     = 0;
		m_rcImageRect.right    = m_cvSrcImage.cols;

		//源图显示区域的的真实高m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);
		m_rcImageRect.top      = (m_cvSrcImage.rows-m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight))/2;
		m_rcImageRect.bottom   = m_rcImageRect.top+m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);

	}
	//3)放大后缩略图宽>picture宽，且缩略图高<picture高
	else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight<tem_rcPicRect.Height())
	{
		//picture显示区域
		tem_nDrawX           = 0;
		tem_nDrawY           = (tem_rcPicRect.Height()-tem_nThumbHeight)/2;
		tem_nDrawW           = tem_rcPicRect.Width();
		tem_nDrawH           = tem_nThumbHeight;
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//图像显示区域

		m_rcImageRect.top      = 0;
		m_rcImageRect.bottom   = m_cvSrcImage.rows;
		//源图显示区域的真是宽m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth)
		m_rcImageRect.left     = (m_cvSrcImage.cols-m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth))/2;
		m_rcImageRect.right    = m_rcImageRect.left+m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);	

	}
	//4）放大后缩略图宽>picture宽，且缩略图高>picture高
	else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
	{
		//picture显示区域
		tem_nDrawX           = 0;
		tem_nDrawY           = 0;
		tem_nDrawW           = tem_rcPicRect.Width();
		tem_nDrawH           = tem_rcPicRect.Height();
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;

		//图像显示区域
		m_rcImageRect.left     = (m_cvSrcImage.cols-m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth))/2;
		m_rcImageRect.top      = (m_cvSrcImage.rows-m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight))/2;;
		m_rcImageRect.right    = m_rcImageRect.left+m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);
		m_rcImageRect.bottom   = m_rcImageRect.top+m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);


	}
	//该判断仅用于1:1显示标志位
	if (!m_BOriSize)    
	{
		if (zoommark)
		{
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		}
		else
		{
			Self_ClearPicCtrl();
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		}
	}

	return TRUE;
}


Mat CSmartFilmUI::ImageRotate(Mat img, int angle)
{
	int     tem_nDegree = angle;
	double  tem_dAngle  = tem_nDegree*CV_PI/180;
	double  a = sin(tem_dAngle), b = cos(tem_dAngle);
	int     tem_nWidth = img.cols;
	int     tem_nHeight= img.rows;
	int     m_width_rotate = int(tem_nHeight *fabs(a)+ tem_nWidth *fabs(b));
	int     m_height_rotate= int(tem_nWidth *fabs(a)+tem_nHeight *fabs(b));
	float   map[6];
	Mat     m_map_matrix(2,3,CV_32F, map);

	CvPoint2D32f center = cvPoint2D32f(tem_nWidth / 2, tem_nHeight / 2);  
	CvMat map_matrix2 = m_map_matrix;  
	cv2DRotationMatrix(center, tem_nDegree, 1.0, &map_matrix2); 
	map[2] += (m_width_rotate - tem_nWidth)/2;
	map[5] += (m_height_rotate - tem_nHeight)/2;

	Mat    tem_cvMidImage;
	tem_cvMidImage.create(cv::Size(m_width_rotate, m_height_rotate), img.type());
	warpAffine(img, tem_cvMidImage, m_map_matrix, cv::Size( m_width_rotate, m_height_rotate),1,0,0);
	return tem_cvMidImage;
}


void CSmartFilmUI::Self_SaveLastImg(void)
{
	//拿到缓存目录
	CString   tem_strFileName = m_strCVDoc;

	//获取文件后缀
	CString   tem_strFileFormat = PathFindExtension(m_strFilesPath);

	//获取当前时间精确到毫秒
	SYSTEMTIME   tem_stDateTime;
	CString      tem_strDate = _T("");
	CString      tem_strTime = _T("");
	GetLocalTime(&tem_stDateTime);
	tem_strDate.Format(_T("%d%02d%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
	tem_strTime.Format(_T("%02d%02d%02d%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond, tem_stDateTime.wMilliseconds); 

	//输出新的文件名
	tem_strFileName += _T("\\");
	tem_strFileName += tem_strDate;
	tem_strFileName += tem_strTime;
	tem_strFileName += tem_strFileFormat;

	//保存图像
	std::string tem_sFilePath = (CStringA)tem_strFileName; 
	imwrite(tem_sFilePath, m_cvNextImg);
	m_vcHistoryImg.push_back(tem_strFileName);
}


Mat CSmartFilmUI::ImageMirror(Mat img, bool mirrormark)
{
	Mat  tem_cvMidImg;
	tem_cvMidImg.create(img.size(), img.type());
	Mat  map_x;
	Mat  map_y;
	map_x.create(img.size(), CV_32FC1);
	map_y.create(img.size(), CV_32FC1);
	if (mirrormark)
	{
		//水平镜像
		for (int i=0; i<img.rows; ++i)
		{
			for (int j=0; j<img.cols; ++j)
			{
				map_x.at<float>(i,j) = (float)(img.cols-j);
				map_y.at<float>(i,j) = (float)i;		
			}
		}
		remap(img, tem_cvMidImg, map_x, map_y, CV_INTER_LINEAR);
	}
	else
	{
		//垂直镜像
		for (int i=0; i<img.rows; i++)
		{
			for (int j=0; j<img.cols; j++)
			{
				map_x.at<float>(i,j) = (float)j;
				map_y.at<float>(i,j) = (float)(img.rows-i);		
			}
		}
		remap(img, tem_cvMidImg, map_x, map_y,CV_INTER_LINEAR);
	}
	return tem_cvMidImg;
}


Mat CSmartFilmUI::ImageInvert(Mat img)
{
	int    tem_nImgWidth  = img.cols;
	int    tem_nImgHeight = img.rows;
	int    tem_nImgStep   = img.step;;
	int    tem_nImgChannel= img.channels();
	uchar* tem_ucImgDate  = (uchar*)img.data;

	for (int i=0; i<tem_nImgHeight; i++)
	{
		for (int j=0; j<tem_nImgWidth; j++)
		{
			for (int k=0; k<tem_nImgChannel; k++)
			{
				tem_ucImgDate[i*tem_nImgStep+j*tem_nImgChannel+k]= 255-tem_ucImgDate[i*tem_nImgStep+j*tem_nImgChannel+k];
			}
		}
	}
	return img;
}


Mat CSmartFilmUI::ImageSharp(Mat img)
{
	Mat   kernel(3, 3, CV_32F, Scalar(0));
	/*算子1
	kernel.at<float>(0,0) = 0;    kernel.at<float>(0,1) = -1.0; kernel.at<float>(0,2) = 0;
	kernel.at<float>(1,0) = -1.0; kernel.at<float>(1,1) = 5.0;  kernel.at<float>(1,2) = -1.0;
	kernel.at<float>(2,0) = 0;    kernel.at<float>(2,1) = -1.0; kernel.at<float>(2,2) = 0;
	*/


	/*算子2
	kernel.at<float>(0,0) = 1.0; kernel.at<float>(0,1) = 1.0;  kernel.at<float>(0,2) = 1.0;
	kernel.at<float>(1,0) = 1.0; kernel.at<float>(1,1) = -8.0; kernel.at<float>(1,2) = 1.0;
	kernel.at<float>(2,0) = 1.0; kernel.at<float>(2,1) = 1.0;  kernel.at<float>(2,2) = 1.0;
	*/

	kernel.at<float>(0,0) = -1.0/7; kernel.at<float>(0,1) = -2.0/7;  kernel.at<float>(0,2) = -1.0/7;
	kernel.at<float>(1,0) = -2.0/7; kernel.at<float>(1,1) = 19.0/7;   kernel.at<float>(1,2) = -2.0/7;
	kernel.at<float>(2,0) = -1.0/7; kernel.at<float>(2,1) = -2.0/7;  kernel.at<float>(2,2) = -1.0/7;

	Mat    tem_cvMidImage;
	tem_cvMidImage.create(img.size(), img.type());
	filter2D(img, tem_cvMidImage, img.depth(), kernel);    //depth参数为-1时，生成图像与原图保持一致。
	
	return tem_cvMidImage;
}


Mat CSmartFilmUI::BrightAndContrast(Mat img, int bright, int contrast)
{
	Mat   tem_cvMidImage = img.clone();
	Mat   tem_cvDstImage;
	tem_cvDstImage = Mat::zeros(img.size(), img.type());

	if (tem_cvMidImage.channels()==3)
	{
		for (int y=0; y<tem_cvMidImage.rows; y++)
		{
			for (int x=0; x<tem_cvMidImage.cols; x++)
			{
				for (int c=0; c<3; c++)
				{
					tem_cvDstImage.at<Vec3b>(y,x)[c] = saturate_cast<uchar>((contrast*0.01+1)*(tem_cvMidImage.at<Vec3b>(y,x)[c])+bright);
				}
			}
		}
	}
	else if (tem_cvMidImage.channels()==1)
	{
		//灰度、黑白单通道图像
		for (int y=0; y<tem_cvMidImage.rows; y++)
		{
			for (int x=0; x<tem_cvMidImage.cols; x++)
			{
				tem_cvDstImage.at<uchar>(y,x) = saturate_cast<uchar>((contrast*0.01+1)*(tem_cvMidImage.at<uchar>(y,x))+bright);
			}
		}
	}

	return tem_cvDstImage;
}


Mat CSmartFilmUI::ImageGamma(Mat img, int gama)
{
	float  tem_fGama = (float)gama*1.0/100;
	Mat    tem_cvMidImage = img.clone();
	//建立查表文件LUT
	unsigned char LUT[256];
	for (int i=0; i<256; i++)
	{
		//Gamma变换表达式
		LUT[i] = saturate_cast<uchar>(pow((float)(i/255.0), tem_fGama) * 255.0f);
	}

	//判断图像通道数量
	if (tem_cvMidImage.channels() == 1)
	{
		MatIterator_<uchar> iterator = tem_cvMidImage.begin<uchar>();
		MatIterator_<uchar> iteratorEnd = tem_cvMidImage.end<uchar>();
		for (; iterator!=iteratorEnd;iterator++)
		{
			*iterator = LUT[(*iterator)];
		}
	} 
	else
	{
		//三通道 时对每个通道单独处理
		MatIterator_<Vec3b> iterator = tem_cvMidImage.begin<Vec3b>();
		MatIterator_<Vec3b> iteratorEnd = tem_cvMidImage.end<Vec3b>();
		for ( ; iterator!=iteratorEnd; iterator++)
		{
			(*iterator)[0] = LUT[((*iterator)[0])];
			(*iterator)[1] = LUT[((*iterator)[1])];
			(*iterator)[2] = LUT[((*iterator)[2])];
		}
	}

	return tem_cvMidImage;
}


void CSmartFilmUI::Self_CreateLine(void)
{
	CRect  tem_rcPicCtrl;
	m_conPicCtrl.GetClientRect(&tem_rcPicCtrl);

	HDC    hdc = ::GetDC(m_conPicCtrl.GetSafeHwnd());
	SetROP2(hdc, R2_NOTXORPEN);

	HPEN   hpen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	SelectObject(hdc, hpen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));

	MoveToEx(hdc, tem_rcPicCtrl.left, tem_rcPicCtrl.Height()/2, NULL);
	LineTo(hdc, tem_rcPicCtrl.right, tem_rcPicCtrl.Height()/2);

	MoveToEx(hdc, tem_rcPicCtrl.Width()/2, tem_rcPicCtrl.top, NULL);
	LineTo(hdc, tem_rcPicCtrl.Width()/2, tem_rcPicCtrl.bottom);

	::DeleteObject(hpen);
}


void CSmartFilmUI::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ClientToScreen(&point);

	if (m_BPaintLine)
	{
		//记录画线起点
		CRect tem_rcPic = m_rcImageShow;
		//将picture控件区域修改为图像区域
		m_conPicCtrl.ClientToScreen(tem_rcPic);
		if(tem_rcPic.PtInRect(point))
		{
			m_BLButtonDown = TRUE;
			SetCapture();
			SetCursor(LoadCursor(NULL,IDC_UPARROW));
			m_conPicCtrl.ScreenToClient(&point);
			m_ptOri = point;
			m_ptEnd = point;
		}
	}
	else if (m_BSlcRect)
	{
		//选区**********************************
		CRect tem_rcPic;
		m_conPicCtrl.GetClientRect(tem_rcPic);
		m_conPicCtrl.ClientToScreen(tem_rcPic);
		if(tem_rcPic.PtInRect(point))
		{
			m_BLButtonDown = TRUE;
			SetCapture();
			m_conPicCtrl.ScreenToClient(&point);
			m_ptOri = point;
			m_ptEnd = point;
		}
	}
	else if (m_BLabel)
	{
		CRect tem_rcPic;
		m_conPicCtrl.GetClientRect(tem_rcPic);
		m_conPicCtrl.ClientToScreen(tem_rcPic);
		if(tem_rcPic.PtInRect(point))
		{
			m_BLButtonDown = TRUE;
			SetCapture();
			m_conPicCtrl.ScreenToClient(&point);
			m_ptOri = point;
			m_ptEnd = point;
		}
	}
	else
	{
		//拖动***********************************
		m_BLButtonDown = TRUE;
		ClientToScreen(m_rcImageShow);
		if (m_rcImageShow.PtInRect(point))
		{
			SetCapture();
			SetCursor(LoadCursor(NULL,IDC_HAND));
			m_ptDragOri = point;       //拖动起点
			m_ptDragEnd = point;
		}
		ScreenToClient(m_rcImageShow);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CSmartFilmUI::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_BLButtonDown)
	{
		if (m_BPaintLine)
		{
			BOOL     tem_BOrientation = TRUE;   //旋转方向标志位，默认顺时针
			double   tem_dRadian = 0;     //弧度
			int      tem_nAngle  = 0;     //角度
			m_BLButtonDown = FALSE;
			ReleaseCapture();
			SetCursor(LoadCursor(NULL,IDC_ARROW));	

			//根据坐标点求出旋转直线与X轴正向夹角
			if (m_ptOri == m_ptEnd)
			{
				//未画线，无夹角
				tem_nAngle = 0;
				tem_BOrientation = TRUE;

			}
			else if (m_ptOri.x==m_ptEnd.x && m_ptOri.y!=m_ptEnd.y)
			{
				//夹角为90度，垂直方向
				tem_nAngle = 90;
				//从上到下为顺，从下到上为逆
				if (m_ptOri.y<m_ptEnd.y)
				{
					tem_BOrientation = TRUE;
				} 
				else
				{
					tem_BOrientation = FALSE;
				}

			}
			else if (m_ptOri.y==m_ptEnd.y && m_ptOri.x!=m_ptEnd.x)
			{
				//夹角为0度，水平方向
				tem_nAngle = 0;
				tem_BOrientation = TRUE;
			}
			else
			{
				//求夹角
				int   tem_nLineWidth  = abs(m_ptOri.x-m_ptEnd.x);
				int   tem_nLineHeight = abs(m_ptOri.y-m_ptEnd.y);
				tem_dRadian = atan(tem_nLineHeight*1.0/tem_nLineWidth);
				tem_nAngle  = (tem_dRadian*180/m_fPI);
				if (m_ptOri.x<m_ptEnd.x)
				{
					tem_BOrientation = TRUE;
				} 
				else
				{
					tem_BOrientation = FALSE;
				}
			}
			if (tem_BOrientation)
			{
				tem_nAngle *= -1;
			} 
			
			//旋转图像
			m_nAngleCount += tem_nAngle;
			m_cvDstImage = ImageRotate(m_cvSrcImage, m_nAngleCount);
			//更新视图
			m_cvLastImg = m_cvSrcImage.clone();
			m_cvNextImg = m_cvDstImage.clone();

			Self_ClearPicCtrl();
			Self_ResetImageRect();
			Self_ResizeImage(pWnd, m_cvNextImg);
			Self_ShowMatImage2(m_cvNextImg, m_rcImageShow);
			Self_CreateLine();		
			
		}
		else if (m_BSlcRect)
		{
			m_BLButtonDown = FALSE;
			m_BSlcRect     = FALSE;
			m_BSlcRected   = TRUE;
			ReleaseCapture();

			//考虑鼠标从左上、左下、右上、右下四种方向画选取
			if (m_ptOri.x<m_ptEnd.x)
			{
				m_rcImageCrop.left = m_ptOri.x;
				m_rcImageCrop.right= m_ptEnd.x;
			}
			else
			{
				m_rcImageCrop.left = m_ptEnd.x;
				m_rcImageCrop.right= m_ptOri.x;
			}
			if (m_ptOri.y<m_ptEnd.y)
			{
				m_rcImageCrop.top  = m_ptOri.y;
				m_rcImageCrop.bottom=m_ptEnd.y;
			}
			else
			{
				m_rcImageCrop.top  = m_ptEnd.y;
				m_rcImageCrop.bottom=m_ptOri.y;
			}

			m_cvSrcImage.copyTo(m_cvLastImg);
			m_cvDstImage = Self_CropImage(m_cvSrcImage, m_rcImageShow, m_rcImageCrop);
			m_cvDstImage.copyTo(m_cvSrcImage);
			m_cvSrcImage.copyTo(m_cvNextImg);
			Self_ResetImageRect();
			Self_ResizeImage(pWnd, m_cvSrcImage);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
			Self_SaveLastImg();
			m_BSlcRect   = FALSE;
			m_BSlcRected = FALSE;
		}
		else if (m_BLabel)
		{
				m_BLButtonDown = FALSE;
//				m_BLabel       = FALSE;
				ReleaseCapture();

			if (m_nLineMode == 0)
			{
				//考虑鼠标从左上、左下、右上、右下四种方向画选取
				if (m_ptOri.x<m_ptEnd.x)
				{
					m_rcImageCrop.left = m_ptOri.x;
					m_rcImageCrop.right= m_ptEnd.x;
				}
				else
				{
					m_rcImageCrop.left = m_ptEnd.x;
					m_rcImageCrop.right= m_ptOri.x;
				}
				if (m_ptOri.y<m_ptEnd.y)
				{
					m_rcImageCrop.top  = m_ptOri.y;
					m_rcImageCrop.bottom=m_ptEnd.y;
				}
				else
				{
					m_rcImageCrop.top  = m_ptEnd.y;
					m_rcImageCrop.bottom=m_ptOri.y;
				}
				//起始点坐标——m_pOri;  终点坐标——m_pEnd;
				m_cvSrcImage.copyTo(m_cvLastImg);
				m_cvDstImage = Self_DrawRetangle(m_cvSrcImage, m_rcImageShow, m_rcImageCrop, m_nLineWidth, m_refLineColor);
				m_nNoteCount++;

				m_cvDstImage.copyTo(m_cvSrcImage);
				m_cvSrcImage.copyTo(m_cvNextImg);
				Self_ResetImageRect();
				Self_ResizeImage(pWnd, m_cvSrcImage);
				Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
				Self_SaveLastImg();

				
			} 
			else if (m_nLineMode == 1)
			{
				m_rcImageCrop.left  = m_ptOri.x;
				m_rcImageCrop.top   = m_ptOri.y;
				m_rcImageCrop.right = m_ptEnd.x;
				m_rcImageCrop.bottom= m_ptEnd.y;
				
				m_cvSrcImage.copyTo(m_cvLastImg);

				m_cvDstImage = Self_DrawArrow(m_cvSrcImage, m_rcImageShow, m_rcImageCrop, m_nLineWidth, m_refLineColor);
				m_nNoteCount++;

				m_cvDstImage.copyTo(m_cvSrcImage);
				m_cvSrcImage.copyTo(m_cvNextImg);
				Self_ResetImageRect();
				Self_ResizeImage(pWnd, m_cvSrcImage);
				Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
				Self_SaveLastImg();

			}		
			else if (m_nLineMode == 3)
			{
				//画一小段标记线
				m_ptEnd.x = m_ptOri.x;
				m_ptOri.y = m_ptOri.y - 30;

				HDC hdc=::GetDC(m_conPicCtrl.GetSafeHwnd());
//				SetROP2(hdc,R2_COPYPEN);          
				SetROP2(hdc,R2_NOTXORPEN); 
				HPEN hpen;
				hpen=CreatePen(PS_SOLID, m_nLineWidth/2+1, m_refLineColor);
				SelectObject(hdc,hpen);
				SelectObject(hdc,GetStockObject(NULL_BRUSH));

				MoveToEx(hdc, m_ptOri.x, m_ptOri.y, NULL);
				LineTo(hdc, m_ptEnd.x, m_ptEnd.y);

				::DeleteObject(hpen);

				m_rcImageCrop.left  = m_ptOri.x;
				m_rcImageCrop.top   = m_ptOri.y;

				if (m_ptNoteSite.x!=0 || m_ptNoteSite.y!=0)
				{
					MoveToEx(hdc, m_ptNoteSite.x, m_ptNoteSite.y, NULL);
					LineTo(hdc, m_ptNoteSite.x, m_ptNoteSite.y + 30);
				}
				m_ptNoteSite = m_ptOri;
			}
		}
		else
		{
			m_BLButtonDown = FALSE;
			ReleaseCapture();
			SetCursor(LoadCursor(NULL,IDC_ARROW));	
			
		}

	}
	
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CSmartFilmUI::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_BLButtonDown)
	{
		if (m_BPaintLine)
		{
			//画线函数
			ClientToScreen(&point);		
			CRect tem_rcPic;
			m_conPicCtrl.GetClientRect(tem_rcPic);
			m_conPicCtrl.ClientToScreen(tem_rcPic);
			if(tem_rcPic.PtInRect(point))
			{
				m_conPicCtrl.ScreenToClient(&point);			
				HDC hdc=::GetDC(m_conPicCtrl.GetSafeHwnd());
				SetROP2(hdc,R2_NOTXORPEN);          
				HPEN hpen;
				hpen=CreatePen(PS_SOLID,2,RGB(255,0,0));
				SelectObject(hdc,hpen);
				SelectObject(hdc,GetStockObject(NULL_BRUSH));

				MoveToEx(hdc, m_ptOri.x, m_ptOri.y, NULL);
				LineTo(hdc, m_ptEnd.x, m_ptEnd.y);
				m_ptEnd = point;
				MoveToEx(hdc, m_ptOri.x, m_ptOri.y, NULL);
				LineTo(hdc, m_ptEnd.x, m_ptEnd.y);

				::DeleteObject(hpen);
			}

		}
		else if (m_BSlcRect)
		{
			ClientToScreen(&point);		
			CRect tem_rcPic;
			m_conPicCtrl.GetClientRect(tem_rcPic);
			m_conPicCtrl.ClientToScreen(tem_rcPic);
			if(tem_rcPic.PtInRect(point))
			{
				m_conPicCtrl.ScreenToClient(&point);			
				HDC hdc=::GetDC(m_conPicCtrl.GetSafeHwnd());
				SetROP2(hdc,R2_NOTXORPEN);          
				HPEN hpen;
				hpen=CreatePen(PS_SOLID,2,RGB(255,0,0));
				SelectObject(hdc,hpen);
				SelectObject(hdc,GetStockObject(NULL_BRUSH));
				::Rectangle(hdc, m_ptOri.x, m_ptOri.y, m_ptEnd.x, m_ptEnd.y); 
				m_ptEnd = point;
				::Rectangle(hdc, m_ptOri.x, m_ptOri.y, m_ptEnd.x, m_ptEnd.y); 
				::DeleteObject(hpen);
			}
		}
		else if(m_BLabel)
		{
			if (m_nLineMode == 0)
			{
				ClientToScreen(&point);		
				CRect tem_rcPic;
				m_conPicCtrl.GetClientRect(tem_rcPic);
				m_conPicCtrl.ClientToScreen(tem_rcPic);
				if(tem_rcPic.PtInRect(point))
				{
					m_conPicCtrl.ScreenToClient(&point);			
					HDC hdc=::GetDC(m_conPicCtrl.GetSafeHwnd());
					SetROP2(hdc,R2_NOTXORPEN);   
					HPEN hpen;
					hpen=CreatePen(PS_SOLID, m_nLineWidth/2+1, m_refLineColor);
					SelectObject(hdc,hpen);
					SelectObject(hdc,GetStockObject(NULL_BRUSH));
					::Rectangle(hdc, m_ptOri.x, m_ptOri.y, m_ptEnd.x, m_ptEnd.y); 
					m_ptEnd = point;
					::Rectangle(hdc, m_ptOri.x, m_ptOri.y, m_ptEnd.x, m_ptEnd.y); 
					::DeleteObject(hpen);
				}
			} 
			else if(m_nLineMode==1)
			{
				//画线函数
				ClientToScreen(&point);		
				CRect tem_rcPic;
				m_conPicCtrl.GetClientRect(tem_rcPic);
				m_conPicCtrl.ClientToScreen(tem_rcPic);
				if(tem_rcPic.PtInRect(point))
				{
					m_conPicCtrl.ScreenToClient(&point);			
					HDC hdc=::GetDC(m_conPicCtrl.GetSafeHwnd());
					SetROP2(hdc,R2_NOTXORPEN);          
					HPEN hpen;
					hpen=CreatePen(PS_SOLID, m_nLineWidth/2+1, m_refLineColor);
					SelectObject(hdc,hpen);
					SelectObject(hdc,GetStockObject(NULL_BRUSH));

					MoveToEx(hdc, m_ptOri.x, m_ptOri.y, NULL);
					LineTo(hdc, m_ptEnd.x, m_ptEnd.y);
					m_ptEnd = point;
					MoveToEx(hdc, m_ptOri.x, m_ptOri.y, NULL);
					LineTo(hdc, m_ptEnd.x, m_ptEnd.y);

					::DeleteObject(hpen);
				}
			}
			else if (m_nLineMode==2)
			{
				//随意画
				m_conPicCtrl.ScreenToClient(&point);			
				HDC hdc=::GetDC(m_conPicCtrl.GetSafeHwnd());
				SetROP2(hdc,R2_COPYPEN);          
				HPEN hpen;
				hpen=CreatePen(PS_SOLID, m_nLineWidth/2+1, m_refLineColor);
				SelectObject(hdc,hpen);
				SelectObject(hdc,GetStockObject(NULL_BRUSH));

				m_ptEnd = point;
				MoveToEx(hdc, m_ptOri.x, m_ptOri.y, NULL);
				LineTo(hdc, m_ptEnd.x, m_ptEnd.y);
				m_ptOri = point;



				::DeleteObject(hpen);
			}
		}
		else
		{			
			ClientToScreen(&point);	
			m_ptDragEnd = point;

			int tem_nDragSpeed = 5;   //控制拖动速度，数值越大拖动越慢
			int tem_nOffSetX = m_ptDragEnd.x-m_ptDragOri.x;
			int tem_nOffSetY = m_ptDragEnd.y-m_ptDragOri.y;
			//拖动重绘
			int tem_nImageWidth  = m_cvSrcImage.cols;   //图像原始尺寸
			int tem_nImageHeight = m_cvSrcImage.rows;

			int tem_nThumbWidth  = 0;          //放大、缩小后缩略图尺寸
			int tem_nThumbHeight = 0;

			CRect   tem_rcPicRect; 
			GetDlgItem(IDC_STA_PIC)->GetWindowRect(&tem_rcPicRect);
			ScreenToClient(&tem_rcPicRect);


			float   tem_fCurRatio = m_fCurRatio;

			int     tem_nDrawX, tem_nDrawY, tem_nDrawW, tem_nDrawH;   //映射起点以及宽高

			//放大后缩略图尺寸
			tem_nThumbWidth  = (int)(tem_fCurRatio*tem_nImageWidth);
			tem_nThumbHeight = (int)(tem_fCurRatio*tem_nImageHeight);
			//1)缩放图尺寸<picture控件尺寸*****************************
			//不能拖动

			//2)缩放图宽<picture宽，且缩放图高>picture高
			if (tem_nThumbWidth<tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
			{
				//图像显示区域
				m_rcImageRect.left     = 0;
				m_rcImageRect.right    = m_cvSrcImage.cols;

				//源图显示区域的的真实高m_cvSrcImage.rows*(tem_nOffSetY*1.0/tem_nThumbHeight);
				m_rcImageRect.top     += (int)(m_cvSrcImage.rows*(tem_nOffSetY*1.0/tem_nThumbHeight))/tem_nDragSpeed;
				m_rcImageRect.bottom  += (int)(m_cvSrcImage.rows*(tem_nOffSetY*1.0/tem_nThumbHeight))/tem_nDragSpeed;
				if (m_rcImageRect.top<=0)
				{
					m_rcImageRect.top    = 0;
					m_rcImageRect.bottom = m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);
				}
				if (m_rcImageRect.bottom>=m_cvSrcImage.rows)
				{
					m_rcImageRect.bottom = m_cvSrcImage.rows;
					m_rcImageRect.top    = m_cvSrcImage.rows - m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);
				}
			}
			//3)缩放图宽>picctrl宽，且缩放图高<picctrl高
			else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight<tem_rcPicRect.Height())
			{
				//图像显示区域

				m_rcImageRect.top      = 0;
				m_rcImageRect.bottom   = m_cvSrcImage.rows;
				//源图显示区域的真是宽m_cvSrcImage.cols*(tem_nOffSetX*1.0/tem_nThumbWidth)

				m_rcImageRect.left    -= (int)(m_cvSrcImage.cols*(tem_nOffSetX*1.0/tem_nThumbWidth))/tem_nDragSpeed;
				m_rcImageRect.right   -= (int)(m_cvSrcImage.cols*(tem_nOffSetX*1.0/tem_nThumbWidth))/tem_nDragSpeed;	
				if (m_rcImageRect.left<=0)
				{
					m_rcImageRect.left  = 0;
					m_rcImageRect.right = m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);
				}
				if (m_rcImageRect.right>=m_cvSrcImage.cols)
				{
					m_rcImageRect.right = m_cvSrcImage.cols;
					m_rcImageRect.left  = m_cvSrcImage.cols - m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);
				}
			}
			//4)缩放图宽>picctrl宽，且缩放图高>picctrl高
			else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
			{
				//图像显示区域

				m_rcImageRect.top     += (int)(m_cvSrcImage.rows*(tem_nOffSetY*1.0/tem_nThumbHeight))/tem_nDragSpeed;
				m_rcImageRect.bottom  += (int)(m_cvSrcImage.rows*(tem_nOffSetY*1.0/tem_nThumbHeight))/tem_nDragSpeed;
				if (m_rcImageRect.top<=0)
				{
					m_rcImageRect.top    = 0;
					m_rcImageRect.bottom = m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);
				}
				if (m_rcImageRect.bottom>=m_cvSrcImage.rows)
				{
					m_rcImageRect.bottom = m_cvSrcImage.rows;
					m_rcImageRect.top    = m_cvSrcImage.rows - m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);
				}

				m_rcImageRect.left    -= (int)(m_cvSrcImage.cols*(tem_nOffSetX*1.0/tem_nThumbWidth))/tem_nDragSpeed;
				m_rcImageRect.right   -= (int)(m_cvSrcImage.cols*(tem_nOffSetX*1.0/tem_nThumbWidth))/tem_nDragSpeed;	
				if (m_rcImageRect.left<=0)
				{
					m_rcImageRect.left  = 0;
					m_rcImageRect.right = m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);
				}
				if (m_rcImageRect.right>=m_cvSrcImage.cols)
				{
					m_rcImageRect.right = m_cvSrcImage.cols;
					m_rcImageRect.left  = m_cvSrcImage.cols - m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);
				}
			}

			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);

		}

	}

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CSmartFilmUI::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	BOOL      tem_BRC;
	CPoint    tem_ptCurPoint = pt;
	if (zDelta>0)
	{
		//放大
		tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, TRUE);
		if(tem_BRC)
		{
			m_fCurRatio+=0.05;
		}

	}
	else
	{
		//缩小
		tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, FALSE);
		if(tem_BRC)
		{
			m_fCurRatio-=0.05;
		}

	}
	if (m_BPaintLine)
	{
		Self_CreateLine();
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


Mat CSmartFilmUI::Self_CropImage(Mat img, CRect showRect, CRect cropRect)
{
	CRect   tem_rcShow = showRect;
	CRect   tem_rcCrop = cropRect;

	if (tem_rcCrop.left==tem_rcCrop.right || tem_rcCrop.top==tem_rcCrop.bottom)
	{
		return img;
	}

	//起点超出图像
	if (tem_rcCrop.left<tem_rcShow.left)
	{
		tem_rcCrop.left=tem_rcShow.left;
	}
	if (tem_rcCrop.top<tem_rcShow.top)
	{
		tem_rcCrop.top=tem_rcShow.top;
	}
	if (tem_rcCrop.right>tem_rcShow.right)
	{
		tem_rcCrop.right=tem_rcShow.right;
	}
	if (tem_rcCrop.bottom>tem_rcShow.bottom)
	{
		tem_rcCrop.bottom=tem_rcShow.bottom;
	}

	int    tem_nCropWidth  = tem_rcCrop.right-tem_rcCrop.left;    //裁切显示宽度
	int    tem_nCropHeight = tem_rcCrop.bottom-tem_rcCrop.top;    //裁切显示高度
	int    tem_nShowWidth  = tem_rcShow.right-tem_rcShow.left;    //显示宽度
	int    tem_nShowHeight = tem_rcShow.bottom-tem_rcShow.top;    //显示高度

	float  tem_fXPropertion     = (tem_rcCrop.left-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);   //起点坐标比例
	float  tem_fYPropertion     = (tem_rcCrop.top-tem_rcShow.top)*1.0/(tem_rcShow.bottom-tem_rcShow.top);
	float  tem_fWidthPropertion = tem_nCropWidth*1.0/tem_nShowWidth;          //裁切区域对显示区域的占比
	float  tem_fHeightPropertion= tem_nCropHeight*1.0/tem_nShowHeight;

	int    tem_nDstWidth   = img.cols* tem_fWidthPropertion;
	int    tem_nDstHeith   = img.rows*tem_fHeightPropertion;

	int    tem_nDstLeft    = img.cols*tem_fXPropertion;
	int    tem_nDstTop     = img.rows*tem_fYPropertion;

	CvRect  tem_crcDst;
	tem_crcDst.x   = tem_nDstLeft;
	tem_crcDst.y   = tem_nDstTop;
	tem_crcDst.width  = tem_nDstWidth;
	tem_crcDst.height =tem_nDstHeith;

	Self_ClearPicCtrl();

	if (m_BSlcRected)
	{
	}
	Mat    tem_cvMidImage(img, tem_crcDst);

	//终点超出图像
	return tem_cvMidImage;
}


Mat CSmartFilmUI::Self_DrawRetangle(Mat img, CRect showRect, CRect cropRect, int linewidth, COLORREF linecolor)
{
	CRect   tem_rcShow = showRect;
	CRect   tem_rcCrop = cropRect;

	if (tem_rcCrop.left==tem_rcCrop.right || tem_rcCrop.top==tem_rcCrop.bottom)
	{
		return img;
	}

	//起点超出图像
	if (tem_rcCrop.left<tem_rcShow.left)
	{
		tem_rcCrop.left=tem_rcShow.left;
	}
	if (tem_rcCrop.top<tem_rcShow.top)
	{
		tem_rcCrop.top=tem_rcShow.top;
	}
	if (tem_rcCrop.right>tem_rcShow.right)
	{
		tem_rcCrop.right=tem_rcShow.right;
	}
	if (tem_rcCrop.bottom>tem_rcShow.bottom)
	{
		tem_rcCrop.bottom=tem_rcShow.bottom;
	}

	int    tem_nCropWidth  = tem_rcCrop.right-tem_rcCrop.left;    //裁切显示宽度
	int    tem_nCropHeight = tem_rcCrop.bottom-tem_rcCrop.top;    //裁切显示高度
	int    tem_nShowWidth  = tem_rcShow.right-tem_rcShow.left;    //显示宽度
	int    tem_nShowHeight = tem_rcShow.bottom-tem_rcShow.top;    //显示高度

	float  tem_fXPropertion     = (tem_rcCrop.left-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);   //起点坐标比例
	float  tem_fYPropertion     = (tem_rcCrop.top-tem_rcShow.top)*1.0/(tem_rcShow.bottom-tem_rcShow.top);
	float  tem_fWidthPropertion = tem_nCropWidth*1.0/tem_nShowWidth;          //裁切区域对显示区域的占比
	float  tem_fHeightPropertion= tem_nCropHeight*1.0/tem_nShowHeight;

	int    tem_nDstWidth   = img.cols* tem_fWidthPropertion;
	int    tem_nDstHeith   = img.rows*tem_fHeightPropertion;

	int    tem_nDstLeft    = img.cols*tem_fXPropertion;
	int    tem_nDstTop     = img.rows*tem_fYPropertion;

	CvRect  tem_crcDst;
	tem_crcDst.x      = tem_nDstLeft;
	tem_crcDst.y      = tem_nDstTop;
	tem_crcDst.width  = tem_nDstWidth;
	tem_crcDst.height =tem_nDstHeith;

	Self_ClearPicCtrl();

	if (m_BSlcRected)
	{
	}
	Mat    tem_cvMidImage(img);
	//获取画框颜色
	int  tem_nRed   = GetRValue(linecolor);
	int  tem_nGreen = GetGValue(linecolor);
	int  tem_nBlue  = GetBValue(linecolor);
	rectangle(tem_cvMidImage, tem_crcDst, Scalar(tem_nBlue, tem_nGreen, tem_nRed), linewidth, 8, 0);

	//终点超出图像
	return tem_cvMidImage;
}


Mat CSmartFilmUI::Self_DrawArrow(Mat img, CRect showRect, CRect cropRect, int linewidth, COLORREF linecolor)
{
	CRect   tem_rcShow = showRect;
	CRect   tem_rcCrop = cropRect;
	int    tem_nCropWidth  = tem_rcCrop.right-tem_rcCrop.left;    //裁切显示宽度
	int    tem_nCropHeight = tem_rcCrop.bottom-tem_rcCrop.top;    //裁切显示高度
	int    tem_nShowWidth  = tem_rcShow.right-tem_rcShow.left;    //显示宽度
	int    tem_nShowHeight = tem_rcShow.bottom-tem_rcShow.top;    //显示高度

	if (tem_rcCrop.left==tem_rcCrop.right || tem_rcCrop.top==tem_rcCrop.bottom)
	{
		return img;
	}

	float  tem_fXPropertion     = (tem_rcCrop.left-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);   //起点坐标比例
	float  tem_fYPropertion     = (tem_rcCrop.top-tem_rcShow.top)*1.0/(tem_rcShow.bottom-tem_rcShow.top);
	int    tem_nDstWidth   = img.cols* tem_fXPropertion;
	int    tem_nDstHeith   = img.rows*tem_fYPropertion;
	cv::Point  tem_ptNewOri(tem_nDstWidth, tem_nDstHeith);

	tem_fXPropertion     = (tem_rcCrop.right-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);         //终点坐标比例
	tem_fYPropertion     = (tem_rcCrop.bottom-tem_rcShow.top)*1.0/(tem_rcShow.bottom-tem_rcShow.top);
	tem_nDstWidth   = img.cols* tem_fXPropertion;
	tem_nDstHeith   = img.rows*tem_fYPropertion;
	cv::Point  tem_ptNewEnd(tem_nDstWidth, tem_nDstHeith);


	Self_ClearPicCtrl();

	Mat    tem_cvMidImage(img);
	int  tem_nRed   = GetRValue(linecolor);
	int  tem_nGreen = GetGValue(linecolor);
	int  tem_nBlue  = GetBValue(linecolor);


	tem_cvMidImage = drawArrow(img, tem_ptNewOri, tem_ptNewEnd, m_nArrowLen, m_nArrowAngle, Scalar(tem_nBlue, tem_nGreen, tem_nRed), m_nLineWidth, CV_AA);

	return tem_cvMidImage;
}


Mat CSmartFilmUI::drawArrow(Mat img, cv::Point pStart, cv::Point pEnd, int len , int alpha , cv::Scalar& color, int thickness , int lineType)
{
	const double tem_PI = 3.1415926;

	cv::Point arrow;
	double angle = atan2((double)(pStart.y - pEnd.y), (double)(pStart.x - pEnd.x));
	line(img, pStart, pEnd, color, thickness, lineType);

	//计算箭角边的另一端的端点位置（上面的还是下面的要看箭头的指向，也就是pStart和pEnd的位置） 
	arrow.x = pEnd.x + len * cos(angle + tem_PI * alpha / 180);
	arrow.y = pEnd.y + len * sin(angle + tem_PI * alpha / 180);
	line(img, pEnd, arrow, color, thickness, lineType);

	arrow.x = pEnd.x + len * cos(angle - tem_PI * alpha / 180);
	arrow.y = pEnd.y + len * sin(angle - tem_PI * alpha / 180);
	line(img, pEnd, arrow, color, thickness, lineType);

	return img;
}


Mat CSmartFilmUI::Self_AddText(Mat src, CRect showRect, CRect cropRect, CString textinfo, COLORREF color, CString font, int fontsize, bool bold, bool italic)
{
	CRect   tem_rcShow = showRect;
	CRect   tem_rcCrop = cropRect;
	int    tem_nCropWidth  = tem_rcCrop.right-tem_rcCrop.left;    //裁切显示宽度
	int    tem_nCropHeight = tem_rcCrop.bottom-tem_rcCrop.top;    //裁切显示高度
	int    tem_nShowWidth  = tem_rcShow.right-tem_rcShow.left;    //显示宽度
	int    tem_nShowHeight = tem_rcShow.bottom-tem_rcShow.top;    //显示高度

	float  tem_fXPropertion     = (tem_rcCrop.left-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);   //起点坐标比例
	float  tem_fYPropertion     = (tem_rcCrop.top-tem_rcShow.top)*1.0/(tem_rcShow.bottom-tem_rcShow.top);
	int    tem_nDstWidth   = src.cols* tem_fXPropertion;
	int    tem_nDstHeith   = src.rows*tem_fYPropertion;


	wchar_t*    tem_wsInfo = textinfo.GetBuffer();                //内容
	int         tem_nRed   = GetRValue(color);                    //颜色
	int         tem_nGreen = GetGValue(color);
	int         tem_nBlue  = GetBValue(color);
	wchar_t*    tem_wsFont = m_strFont.GetBuffer();
	int         tem_nSize  = fontsize;


	int   iSize;
	char* pszMultiByte;
	char* pszFont;

	//返回接受字符串所需缓冲区的大小，已经包含字符结尾符'\0'
	iSize = WideCharToMultiByte(CP_ACP, 0, tem_wsInfo, -1, NULL, 0, NULL, NULL); 
	pszMultiByte = (char*)malloc(iSize*sizeof(char)); //不需要 pszMultiByte = (char*)malloc(iSize*sizeof(char)+1);
	WideCharToMultiByte(CP_ACP, 0, tem_wsInfo, -1, pszMultiByte, iSize, NULL, NULL);

	iSize = WideCharToMultiByte(CP_ACP, 0, tem_wsFont, -1, NULL, 0, NULL, NULL); 
	pszFont = (char*)malloc(iSize*sizeof(char)); //不需要 pszMultiByte = (char*)malloc(iSize*sizeof(char)+1);
	WideCharToMultiByte(CP_ACP, 0, tem_wsFont, -1, pszFont, iSize, NULL, NULL);

	putTextEx(src, pszMultiByte, cv::Point(tem_nDstWidth, tem_nDstHeith), Scalar(tem_nBlue, tem_nGreen, tem_nRed), tem_nSize, pszFont, m_BItalic, false, m_BBold);    //Scalar(B, G, R)

	return src;
}


void CSmartFilmUI::putTextEx(Mat& dst, const char* str, cv::Point org, Scalar color, int fontSize, const char* fn, bool italic, bool underline, bool bold)
{
	CV_Assert(dst.data != 0 && (dst.channels() == 1 || dst.channels() == 3));

	int x, y, r, b;
	if (org.x > dst.cols || org.y > dst.rows) return;
	x = org.x < 0 ? -org.x : 0;
	y = org.y < 0 ? -org.y : 0;

	LOGFONTA lf;
	lf.lfHeight = -fontSize;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	//	lf.lfWeight = 5;                      //重量即为粗细0~1000，正常情况为400，加粗为700
	if (bold)
	{
		lf.lfWeight = 700;
	}
	else
	{
		lf.lfWeight = 400;
	}

	lf.lfItalic = italic;   //斜体
	lf.lfUnderline = underline; //下划线
	lf.lfStrikeOut = 0;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfOutPrecision = 0;
	lf.lfClipPrecision = 0;
	lf.lfQuality = PROOF_QUALITY;
	lf.lfPitchAndFamily = 0;
	strcpy_s(lf.lfFaceName, fn);

	HFONT hf = CreateFontIndirectA(&lf);
	HDC hDC = CreateCompatibleDC(0);
	HFONT hOldFont = (HFONT)SelectObject(hDC, hf);

	int strBaseW = 0, strBaseH = 0;
	int singleRow = 0;
	char buf[1 << 12];
	strcpy_s(buf, str);
	char *bufT[1 << 12];  // 这个用于分隔字符串后剩余的字符，可能会超出。
	//处理多行
	{
		int nnh = 0;
		int cw, ch;

		const char* ln = strtok_s(buf, "\n",bufT);
		while (ln != 0)
		{
			GetStringSize(hDC, ln, &cw, &ch);
			strBaseW = max(strBaseW, cw);
			strBaseH = max(strBaseH, ch);

			ln = strtok_s(0, "\n",bufT);
			nnh++;
		}
		singleRow = strBaseH;
		strBaseH *= nnh;
	}

	if (org.x + strBaseW < 0 || org.y + strBaseH < 0)
	{
		SelectObject(hDC, hOldFont);
		DeleteObject(hf);
		DeleteObject(hDC);
		return;
	}

	r = org.x + strBaseW > dst.cols ? dst.cols - org.x - 1 : strBaseW - 1;
	b = org.y + strBaseH > dst.rows ? dst.rows - org.y - 1 : strBaseH - 1;
	org.x = org.x < 0 ? 0 : org.x;
	org.y = org.y < 0 ? 0 : org.y;

	BITMAPINFO bmp = { 0 };
	BITMAPINFOHEADER& bih = bmp.bmiHeader;
	int strDrawLineStep = strBaseW * 3 % 4 == 0 ? strBaseW * 3 : (strBaseW * 3 + 4 - ((strBaseW * 3) % 4));

	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = strBaseW;
	bih.biHeight = strBaseH;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = BI_RGB;
	bih.biSizeImage = strBaseH * strDrawLineStep;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	void* pDibData = 0;
	HBITMAP hBmp = CreateDIBSection(hDC, &bmp, DIB_RGB_COLORS, &pDibData, 0, 0);

	CV_Assert(pDibData != 0);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hDC, hBmp);

	//color.val[2], color.val[1], color.val[0]
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, 0);
	//SetStretchBltMode(hDC, COLORONCOLOR);

	strcpy_s(buf, str);
	const char* ln = strtok_s(buf, "\n",bufT);
	int outTextY = 0;
	while (ln != 0)
	{
		TextOutA(hDC, 0, outTextY, ln, strlen(ln));
		outTextY += singleRow;
		ln = strtok_s(0, "\n",bufT);
	}
	uchar* dstData = (uchar*)dst.data;
	int dstStep = dst.step / sizeof(dstData[0]);
	unsigned char* pImg = (unsigned char*)dst.data + org.x * dst.channels() + org.y * dstStep;
	unsigned char* pStr = (unsigned char*)pDibData + x * 3;
	for (int tty = y; tty <= b; ++tty)
	{
		unsigned char* subImg = pImg + (tty - y) * dstStep;
		unsigned char* subStr = pStr + (strBaseH - tty - 1) * strDrawLineStep;
		for (int ttx = x; ttx <= r; ++ttx)
		{
			for (int n = 0; n < dst.channels(); ++n){
				double vtxt = subStr[n] / 255.0;
				int cvv = vtxt * color.val[n] + (1 - vtxt) * subImg[n];
				subImg[n] = cvv > 255 ? 255 : (cvv < 0 ? 0 : cvv);
			}

			subStr += 3;
			subImg += dst.channels();
		}
	}


	SelectObject(hDC, hOldBmp);
	SelectObject(hDC, hOldFont);
	DeleteObject(hf);
	DeleteObject(hBmp);
	DeleteDC(hDC);
}


void CSmartFilmUI::GetStringSize(HDC hDC, const char* str, int* w, int* h)
{
	SIZE size;
	GetTextExtentPoint32A(hDC, str, strlen(str), &size);
	if (w != 0) *w = size.cx;
	if (h != 0) *h = size.cy;
}


void CSmartFilmUI::StopRun(void)
{
	m_conOCX.StopRun();
	m_conOCX.Uninitial();
	FreeLibrary(m_hDllInst);

 	std::vector<CString>::iterator item;
	for (item=m_vcThumbPath.begin(); item!=m_vcThumbPath.end(); item++)
	{
		DeleteFile(*item);
	}
	
	if (m_vcHistoryImg.size()>2)
	{
		if (m_BNoSaved)
		{
			int tem_nClose = MessageBox(_T("修改尚未保存！是否保存？"), _T("保存"), MB_YESNO);
			if (tem_nClose == 6)
			{
				//确定保存
				CString tem_strNewImgPath = m_vcHistoryImg.back();
				CopyFile(tem_strNewImgPath, m_strFilesPath, FALSE);
			}
		}
	}
	if (m_vcHistoryImg.size()>1)
	{
		//逆向删除2后面的所有图像
		std::vector<CString>::iterator item2;
		for (item2=m_vcHistoryImg.begin()+1; item2!=m_vcHistoryImg.end(); item2++)
		{
			DeleteFile(*item2);
		}
	}
	
}


void CSmartFilmUI::Self_CaptureImgHDR(CString imgname, int mode)
{
	
	//文件命名---------------------------------------------------------------------------
	CString    tem_strLowImg    = m_strThumbDoc;      //欠曝图像
	tem_strLowImg              += _T("\\lbmd");
	tem_strLowImg              += imgname;

	CString    tem_strNorImg    = m_strThumbDoc;      //正常图像
	tem_strNorImg              += _T("\\nbmd");
	tem_strNorImg              += imgname;

	CString    tem_strHigImg    = m_strThumbDoc;      //过曝图像
	tem_strHigImg              += _T("\\hbmd");
	tem_strHigImg              += imgname;

	CString    tem_strHDRImg    = m_strThumbDoc;      //合成图像
	tem_strHDRImg              += _T("\\bmd");
	tem_strHDRImg              += imgname;

	CString    tem_strThumbPath = m_strThumbDoc;      //缩略图像
	tem_strThumbPath           += _T("\\~");
	tem_strThumbPath           += imgname;
	tem_strThumbPath           += _T(".jpg");

	CString    tem_strIntImg    = m_strThumbDoc;      //插值图像
	tem_strIntImg              += _T("\\~~~");
	tem_strIntImg              += imgname;

	CString    tem_strFilePath  = m_strSaveDoc;       //目标文件
	tem_strFilePath            += imgname;
	tem_strFilePath            += m_strFileFormat;
	
	if (m_nLastImgType>=0 && m_nLastImgType<3)
	{
		tem_strLowImg += m_strFileFormat;
		tem_strNorImg += m_strFileFormat;
		tem_strHigImg += m_strFileFormat;
		tem_strHDRImg += m_strFileFormat;
		tem_strIntImg += m_strFileFormat;
	} 
	else if(m_nLastImgType == 4 || m_nLastImgType == 5 ||m_nLastImgType == 3)  //3-tif,tif无法合成
	{
		tem_strLowImg += _T(".jpg");
		tem_strNorImg += _T(".jpg");
		tem_strHigImg += _T(".jpg");
		tem_strHDRImg += _T(".jpg");
		tem_strIntImg += _T(".jpg");
	}
	
	/*
	*     说明
	*   由于不同拍照间不需要再设置不同灰阶和逆光对比，因此将这两项设置注释，以提升效率
	*
	*/
	
	if (mode == 1)
	{
		if (m_nNorLight != m_nLastRelay)
		{
			//调节灯箱**********************************
			AdjustRelay(m_nNorLight, m_nLastRelay);
			Self_TimeDelay(m_nIntervalTime);
		}	
	} 
	else
	{
		if (m_nNorLightL != m_nLastRelay)
		{
			//调节灯箱**********************************
			AdjustRelay(m_nNorLightL, m_nLastRelay);
			Self_TimeDelay(m_nIntervalTime);
		}
	}
	m_conOCX.CaptureImage(tem_strNorImg);
	
	
	if (mode == 1)
	{
		//调节灯箱**********************************
		AdjustRelay(m_nLowLight, m_nNorLight);
		Self_TimeDelay(m_nIntervalTime);
	} 
	else
	{
		//调节灯箱**********************************
		AdjustRelay(m_nLowLightL, m_nNorLightL);
		Self_TimeDelay(m_nIntervalTime);
	}
	//拍照-------------------------------------
	m_conOCX.CaptureImage(tem_strLowImg);

	if (mode == 1)
	{
		//调节灯箱**********************************
		AdjustRelay(m_nHigLight, m_nLowLight);
		//调节灰阶----------------------------------
		Self_TimeDelay(m_nIntervalTime);
	} 
	else
	{
		//调节灯箱**********************************
		AdjustRelay(m_nHigLightL, m_nLowLightL);
		//调节灰阶----------------------------------
		Self_TimeDelay(m_nIntervalTime);
	}
	//拍照-------------------------------------
	m_conOCX.CaptureImage(tem_strHigImg);

	//恢复参数--------------------------------------------------------------------------
	if (mode == 1)
	{
		//先校准，再恢复---------------------------------
		int tem_nSave = m_nLastRelay;
		Self_SetRelayZero();
		m_nLastRelay = tem_nSave; 
		AdjustRelay(m_nLastRelay, 0);
	} 
	else
	{
		//先校准，再恢复---------------------------------
		int tem_nSave = m_nLastRelay;
		Self_SetRelayZero();
		m_nLastRelay = tem_nSave; 
		AdjustRelay(m_nLastRelay, 0);
	}

	
	

	/*将合成图像移至接收到下层返回消息处，在此处合成1、while不断检测文件有系统开销；2、检测的文件的速度快于子程序释放图像速度，没有下面延时可能内存异常*/
	/*
	//合成图像--------------------------------------------------------------------------
	if(PathFileExists(tem_strHDRImg))
	{
		::DeleteFile(tem_strHDRImg);
	}
//	Self_HDRMergeImgs(tem_strHigImg, tem_strNorImg, tem_strLowImg, tem_strHDRImg);   //方法一
//	Self_HDRMergeImgs3_1(tem_strHigImg, tem_strNorImg, tem_strLowImg, tem_strHDRImg, mode);  //方法二
	Self_HDRMergeImgEx(tem_strLowImg, tem_strNorImg, tem_strHigImg, tem_strHDRImg, mode, m_nLowLightL, m_nNorLightL, m_nHigLightL, m_nLowLight, m_nNorLight, m_nHigLight);
	//等待子程序生成完毕再继续-----------------------------------------------------------
	BOOL  tem_BComplted = TRUE;
	while(tem_BComplted)
	{
		//查询文件是否存在------------------
		if(PathFileExists(tem_strHDRImg))
		{
			break;
		}

	}
	Self_TimeDelay(300);
	//删除缓存图像----------------------------------------------------------------------
// 	::DeleteFile(tem_strHigImg);
// 	::DeleteFile(tem_strNorImg);
// 	::DeleteFile(tem_strLowImg);
	

	//是否需要添加水印-------------------------------------------------------------------
	if (m_nWaterMark == 1)
	{
		Self_AddWaterMark(tem_strHDRImg);
	}

	//创建缩略图------------------------------------------------------------------------
	Self_CreateThumb(tem_strHDRImg, tem_strThumbPath);

	//是否需要插值----------------------------------------------------------------------
	if (m_nLastRes==m_nInterpolateReso)
	{
		Self_InterPolateImage(tem_strHDRImg, tem_strIntImg, 0);
		::DeleteFile(tem_strHDRImg);
		tem_strHDRImg = tem_strIntImg;
	}

	//判断图像格式----------------------------------------------------------------------
	 if(m_nLastImgType == 4)
	 {
		 Self_GetPdfFromImg(tem_strHDRImg, tem_strFilePath);
	 }
	 else if (m_nLastImgType == 5)
	 {
		 char*  tem_cName  = NULL;
		 char*  tem_cId    = NULL;
		 char*  tem_cBirth = NULL;
		 char*  tem_cSex   = NULL;
		 char*  tem_cDName = NULL;
		 char*  tem_cDate  = NULL;
		 char*  tem_cTime  = NULL;

		 IMAGEAndDCM*   tem_dcm = new IMAGEAndDCM;
		 tem_dcm->Set(tem_cName, tem_cId, tem_cBirth, tem_cSex, tem_cDName, tem_cDate, tem_cTime);

		 USES_CONVERSION;  
		 char*   tem_cSrc = T2A(tem_strHDRImg);
		 char*   tem_cDst = T2A(tem_strFilePath);
		 tem_dcm->SaveIMAGEtoDCM(tem_cSrc, tem_cDst);
	 }
	 else if (m_nLastImgType == 3)
	 {
		 //将jpg图像转为tif图像
		 CxImage tem_cxJPG;
		 tem_cxJPG.Load(tem_strHDRImg, CMAX_IMAGE_FORMATS);
		 tem_cxJPG.SetCodecOption(5, CXIMAGE_FORMAT_TIF);
		 tem_cxJPG.Save(tem_strFilePath, CXIMAGE_FORMAT_TIF);	 
	 }
	 else
	 {
		 CopyFile(tem_strHDRImg, tem_strFilePath, FALSE);
	 }
//	 ::DeleteFile(tem_strHDRImg);
	
	 m_vcImgName.push_back(imgname);
	 m_vcThumbPath.push_back(tem_strThumbPath);
	 m_vcFilePath.push_back(tem_strFilePath);
	 ThumbaiList(m_nThumbWidth, m_nThumbHeight);

	 Self_ShowImgInfo(tem_strFilePath);
	 m_nImageCount++;
	 MessageBox(_T("Over"));
	 */
}

#include "MMsystem.h"   //延时函数,精度毫秒
#pragma comment(lib, "winmm.lib")
void CSmartFilmUI::Self_TimeDelay(int time_ms)
{
	DWORD    tem_dTimeBegin = timeGetTime();
	DWORD    tem_dTimeEnd   = 0;
	do 
	{
		tem_dTimeEnd = timeGetTime();
	} while (tem_dTimeEnd-tem_dTimeBegin<=time_ms);
}


void CSmartFilmUI::Self_CaptureImgHDRThread(CString imgname, int mode , int ex)
{
	//文件命名---------------------------------------------------------------------------
	CString    tem_strLowImg    = m_strThumbDoc;      //欠曝图像
	tem_strLowImg              += _T("\\lbmd");
	tem_strLowImg              += imgname;

	CString    tem_strNorImg    = m_strThumbDoc;      //正常图像
	tem_strNorImg              += _T("\\nbmd");
	tem_strNorImg              += imgname;

	CString    tem_strHigImg    = m_strThumbDoc;      //过曝图像
	tem_strHigImg              += _T("\\hbmd");
	tem_strHigImg              += imgname;

	CString    tem_strHDRImg    = m_strThumbDoc;      //合成图像
	tem_strHDRImg              += _T("\\bmd");
	tem_strHDRImg              += imgname;

	CString    tem_strThumbPath = m_strThumbDoc;      //缩略图像
	tem_strThumbPath           += _T("\\~");
	tem_strThumbPath           += imgname;
	tem_strThumbPath           += _T(".jpg");

	CString    tem_strIntImg    = m_strThumbDoc;      //插值图像
	tem_strIntImg              += _T("\\~~~");
	tem_strIntImg              += imgname;

	CString    tem_strFilePath  = m_strSaveDoc;       //目标文件
	tem_strFilePath            += imgname;
	tem_strFilePath            += m_strFileFormat;
	m_strCurImgPath             = tem_strFilePath;
	
	if (m_nLastImgType>=0 && m_nLastImgType<3)
	{
		tem_strLowImg += m_strFileFormat;
		tem_strNorImg += m_strFileFormat;
		tem_strHigImg += m_strFileFormat;
		tem_strHDRImg += m_strFileFormat;
		tem_strIntImg += m_strFileFormat;
	} 
	else if(m_nLastImgType == 4 || m_nLastImgType == 5 ||m_nLastImgType == 3)  //3-tif,tif无法合成
	{
		tem_strLowImg += _T(".jpg");
		tem_strNorImg += _T(".jpg");
		tem_strHigImg += _T(".jpg");
		tem_strHDRImg += _T(".jpg");
		tem_strIntImg += _T(".jpg");
	}
	/*
	*     说明
	*   由于不同拍照间不需要再设置不同灰阶和逆光对比，因此将这两项设置注释，以提升效率
	*
	*/
	if (ex == 0)
	{
		m_vcSomeStrInfo.clear();
		if (m_nUIMode == 0 || m_nUIMode == 3)
		{
			m_dlgGet.Self_HideCtrls(1);
		}
		
		if (mode == 1)
		{
			if (m_nNorLight != m_nLastRelay)
			{
				//调节灯箱**********************************
				AdjustRelay(m_nNorLight, m_nLastRelay);
				stcThreadInfo.hWnd = this->m_hWnd;
				stcThreadInfo.time = m_nIntervalTime;
				stcThreadInfo.mode = 1;
				hThreadHandle = AfxBeginThread(ThreadDelay, &stcThreadInfo, THREAD_PRIORITY_NORMAL, 0, NULL);
			}	
			else
			{
				//亮度=10，不需要延时
				stcThreadInfo.hWnd = this->m_hWnd;
				stcThreadInfo.time = 0;
				stcThreadInfo.mode = 1;
				hThreadHandle = AfxBeginThread(ThreadDelay, &stcThreadInfo, THREAD_PRIORITY_NORMAL, 0, NULL);
			}
		} 
		else
		{
			if (m_nNorLightL != m_nLastRelay)
			{
				//调节灯箱**********************************
				AdjustRelay(m_nNorLightL, m_nLastRelay);
				stcThreadInfo.hWnd = this->m_hWnd;
				stcThreadInfo.time = m_nIntervalTime;
				stcThreadInfo.mode = 1;
				hThreadHandle = AfxBeginThread(ThreadDelay, &stcThreadInfo, THREAD_PRIORITY_NORMAL, 0, NULL);
			}
			else
			{
				//亮度=10，不需要延时
				stcThreadInfo.hWnd = this->m_hWnd;
				stcThreadInfo.time = 0;
				stcThreadInfo.mode = 1;
				hThreadHandle = AfxBeginThread(ThreadDelay, &stcThreadInfo, THREAD_PRIORITY_NORMAL, 0, NULL);
			}
		}
	}
	else if (ex == 1)
	{
		m_conOCX.CaptureImage(tem_strNorImg);
		if (m_nUIMode == 0 || m_nUIMode == 3)
		{
			m_dlgGet.Self_HideCtrls(2);
		}
		
		if (mode == 1)
		{
			//调节灯箱**********************************
			AdjustRelay(m_nLowLight, m_nNorLight);
		} 
		else
		{
			//调节灯箱**********************************
			AdjustRelay(m_nLowLightL, m_nNorLightL);
		}
		stcThreadInfo.hWnd = this->m_hWnd;
		stcThreadInfo.time = m_nIntervalTime;
		stcThreadInfo.mode = 2;
		hThreadHandle = AfxBeginThread(ThreadDelay, &stcThreadInfo, THREAD_PRIORITY_NORMAL, 0, NULL);
	}
	else if (ex == 2)
	{
		m_conOCX.CaptureImage(tem_strLowImg);
		if (m_nUIMode == 0 || m_nUIMode == 3)
		{
			m_dlgGet.Self_HideCtrls(3);
		}
		
		if (mode == 1)
		{
			//调节灯箱**********************************
			AdjustRelay(m_nHigLight, m_nLowLight);
		} 
		else
		{
			//调节灯箱**********************************
			AdjustRelay(m_nHigLightL, m_nLowLightL);
		}
		stcThreadInfo.hWnd = this->m_hWnd;
		stcThreadInfo.time = m_nIntervalTime;
		stcThreadInfo.mode = 3;
		hThreadHandle = AfxBeginThread(ThreadDelay, &stcThreadInfo, THREAD_PRIORITY_NORMAL, 0, NULL);
	}
	else if (ex == 3)
	{
		m_conOCX.CaptureImage(tem_strHigImg);
		if (m_nUIMode == 0 || m_nUIMode == 3)
		{
			m_dlgGet.Self_HideCtrls(4);
		}
		

		//恢复参数--------------------------------------------------------------------------
		if (mode == 1)
		{
			//先校准，再恢复---------------------------------
			int tem_nSave = m_nLastRelay;
			Self_SetRelayZero();
			m_nLastRelay = tem_nSave; 
			AdjustRelay(m_nLastRelay, 0);
		} 
		else
		{
			//先校准，再恢复---------------------------------
			int tem_nSave = m_nLastRelay;
			Self_SetRelayZero();
			m_nLastRelay = tem_nSave; 
			AdjustRelay(m_nLastRelay, 0);
		}
		m_nImageCount++;
		m_strHDRImg = tem_strHDRImg;
		Self_HDRMergeImgEx(tem_strLowImg, tem_strNorImg, tem_strHigImg, tem_strHDRImg, mode, m_nLowLightL, m_nNorLightL, m_nHigLightL, m_nLowLight, m_nNorLight, m_nHigLight);
		if (m_nUIMode == 0 || m_nUIMode == 3)
		{
			m_dlgGet.Self_HideCtrls(6);
		}
		

//		m_nHdrMergeMode = mode;
		m_vcSomeStrInfo.push_back(tem_strLowImg);
		m_vcSomeStrInfo.push_back(tem_strNorImg);
		m_vcSomeStrInfo.push_back(tem_strHigImg);
		m_vcSomeStrInfo.push_back(tem_strHDRImg);
		m_vcSomeStrInfo.push_back(tem_strThumbPath);
		m_vcSomeStrInfo.push_back(tem_strIntImg);
		m_vcSomeStrInfo.push_back(tem_strFilePath);
		m_vcSomeStrInfo.push_back(imgname);

		//开启线程，检测HDR图像是否已经生成，生成则发送消息，删除缓存
		hThreadHandle2 = AfxBeginThread(ThreadDetect,  &stcThreadInfo, THREAD_PRIORITY_NORMAL, 0, NULL);
	}
}


void CSmartFilmUI::Self_HDRMergeImgEx(CString LowImg, CString NorImg, CString HigImg, CString OutImg, int mode, int lowlight_L, int norlight_L, int higlight_L, int lowlight_H, int norlight_H, int higlight_H)
{
	CString tem_strSendInfo = _T("");
	tem_strSendInfo  = LowImg; tem_strSendInfo += _T("#$");
	tem_strSendInfo += NorImg; tem_strSendInfo += _T("#$");
	tem_strSendInfo += HigImg; tem_strSendInfo += _T("#$");
	tem_strSendInfo += OutImg; tem_strSendInfo += _T("#$");

	CString tem_strMid = _T("");
	tem_strMid.Format(_T("%d"), mode); tem_strSendInfo += tem_strMid; tem_strSendInfo += _T("#$");

	tem_strMid.Format(_T("%d"), lowlight_L); tem_strSendInfo += tem_strMid; tem_strSendInfo += _T("#$");
	tem_strMid.Format(_T("%d"), norlight_L); tem_strSendInfo += tem_strMid; tem_strSendInfo += _T("#$");
	tem_strMid.Format(_T("%d"), higlight_L); tem_strSendInfo += tem_strMid; tem_strSendInfo += _T("#$");

	tem_strMid.Format(_T("%d"), lowlight_H); tem_strSendInfo += tem_strMid; tem_strSendInfo += _T("#$");
	tem_strMid.Format(_T("%d"), norlight_H); tem_strSendInfo += tem_strMid; tem_strSendInfo += _T("#$");
	tem_strMid.Format(_T("%d"), higlight_H); tem_strSendInfo += tem_strMid; 

	CString  tem_strAllInfo = _T("\"");
	tem_strAllInfo += tem_strSendInfo;
	tem_strAllInfo += _T("\"");
	CString tem_strOcxPath = Self_GetOCXPath();
	tem_strOcxPath += _T("UDSGenerateIt.exe");

	ShellExecute(NULL, _T("open"), tem_strOcxPath, tem_strAllInfo, NULL, SW_SHOWNORMAL);
}


#include "MMsystem.h"   //延时函数,精度毫秒
#pragma comment(lib, "winmm.lib")
UINT ThreadDelay(LPVOID lpParam)  
{
	ThreadInfo* tem_pInfo = (ThreadInfo*)lpParam;
	HWND tem_hWnd = tem_pInfo->hWnd;
	int tem_nTime = tem_pInfo->time;
	int tem_nMode = tem_pInfo->mode;

	DWORD tem_nBegin = timeGetTime();
	DWORD tem_nEnd = 0;
	do 
	{
		tem_nEnd = timeGetTime();
	} while (tem_nEnd-tem_nBegin<=tem_nTime);
	::PostMessage(tem_hWnd, WM_THREADOVER, 0, tem_nMode);

	return 0;
}

UINT ThreadDetect(LPVOID lpParam)
{
	ThreadInfo* tem_pInfo = (ThreadInfo*)lpParam;
	HWND tem_hWnd = tem_pInfo->hWnd;
	BOOL tem_BExist = FALSE;
	CString tem_strInfo = _T("");
	do 
	{
		::GetPrivateProfileString(_T("BaseSet"), _T("TalkCode"), _T("没有找到TalkCode信息"), tem_strInfo.GetBuffer(MAX_PATH), MAX_PATH, g_strIniPath);
	} while (tem_strInfo != _T("3"));
	
	/*
	do 
	{
		tem_BExist = PathFileExists(m_strHDRImg);
	} while (!tem_BExist);
	*/
	::PostMessage(tem_hWnd, WM_THREADDETECT, 0, 0);
	return 0;
}

afx_msg LRESULT CSmartFilmUI::OnThreadover(WPARAM wParam, LPARAM lParam)
{
	int tem_nInfo = (int)lParam;
	Self_CaptureImgHDRThread(m_strCurImgName, m_nCurImgMode, tem_nInfo);
	return 0;
}


afx_msg LRESULT CSmartFilmUI::OnThreaddetect(WPARAM wParam, LPARAM lParam)
{
	if (m_nUIMode == 0 || m_nUIMode == 3)
	{
		m_dlgGet.Self_HideCtrls(9);
	}
	
	CString tem_strLowImg    = m_vcSomeStrInfo[0];
	CString tem_strNorImg    = m_vcSomeStrInfo[1];
	CString tem_strHigImg    = m_vcSomeStrInfo[2];
	CString tem_strHDRImg    = m_vcSomeStrInfo[3];
	CString tem_strThumbPath = m_vcSomeStrInfo[4];
	CString tem_strIntImg    = m_vcSomeStrInfo[5];
	CString tem_strFilePath  = m_vcSomeStrInfo[6];
	CString imgname          = m_vcSomeStrInfo[7];

	//等待子程序生成完毕再继续-----------------------------------------------------------
	//删除缓存图像----------------------------------------------------------------------
	::DeleteFile(tem_strHigImg);
	::DeleteFile(tem_strNorImg);
	::DeleteFile(tem_strLowImg);

	//是否需要添加水印-------------------------------------------------------------------
	if (m_nWaterMark == 1)
	{
		Self_AddWaterMark(tem_strHDRImg);
	}

	//创建缩略图------------------------------------------------------------------------
	if (m_nUIMode == 0 || m_nUIMode == 3)
	{
		Self_CreateThumb(tem_strHDRImg, tem_strThumbPath);
	}
	

	//是否需要插值----------------------------------------------------------------------
	if (m_nLastRes==m_nInterpolateReso)
	{
		Self_InterPolateImage(tem_strHDRImg, tem_strIntImg, 0);
		::DeleteFile(tem_strHDRImg);
		tem_strHDRImg = tem_strIntImg;
	}

	//判断图像格式----------------------------------------------------------------------
	if(m_nLastImgType == 4)
	{
		Self_GetPDFFromImg(tem_strHDRImg, tem_strFilePath);
	}
	else if (m_nLastImgType == 5)
	{
		char*  tem_cName  = NULL;
		char*  tem_cId    = NULL;
		char*  tem_cBirth = NULL;
		char*  tem_cSex   = NULL;
		char*  tem_cDName = NULL;
		char*  tem_cDate  = NULL;
		char*  tem_cTime  = NULL;

		IMAGEAndDCM*   tem_dcm = new IMAGEAndDCM;
		tem_dcm->Set(tem_cName, tem_cId, tem_cBirth, tem_cSex, tem_cDName, tem_cDate, tem_cTime);

		USES_CONVERSION;  
		char*   tem_cSrc = T2A(tem_strHDRImg);
		char*   tem_cDst = T2A(tem_strFilePath);
		tem_dcm->SaveIMAGEtoDCM(tem_cSrc, tem_cDst);

		delete tem_dcm;

	}
	else if (m_nLastImgType == 3)
	{
		//将jpg图像转为tif图像
		CxImage tem_cxJPG;
		tem_cxJPG.Load(tem_strHDRImg, CMAX_IMAGE_FORMATS);
		tem_cxJPG.SetCodecOption(5, CXIMAGE_FORMAT_TIF);
		tem_cxJPG.Save(tem_strFilePath, CXIMAGE_FORMAT_TIF);	 
	}
	else
	{
		CopyFile(tem_strHDRImg, tem_strFilePath, FALSE);
	}
	::DeleteFile(tem_strHDRImg);
	if (m_nUIMode == 0 || m_nUIMode == 3)
	{
		m_dlgGet.Self_HideCtrls(10);
		m_vcImgName.push_back(imgname);
		m_vcThumbPath.push_back(tem_strThumbPath);
		ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		Self_ShowImgInfo(tem_strFilePath);
	}
	
	m_vcFilePath.push_back(tem_strFilePath);
	
//	m_nImageCount++;
	m_vcSomeStrInfo.clear();

	//拍摄完成-------------------------------
	if (m_nUIMode == 0 || m_nUIMode == 3)
	{
		m_dlgGet.Self_HideCtrls(0);
	}
	::WritePrivateProfileString(_T("BaseSet"), _T("TalkCode"), _T("0"), g_strIniPath);
	::PostMessage(g_hCtrHwnd, WM_CAPTUREOVER, 0, 0);
	return 0;
}



void CSmartFilmUI::Self_ResetParamers(void)
{
	Self_ReadXml(g_strProXmlPath);
}


void CSmartFilmUI::Self_SetSaveDir(CString dir)
{
	m_strSaveDoc = dir;	
}


int CSmartFilmUI::Self_SetRectMode(int mode)
{
	int tem_nRC = 0;
	if (mode==0)
	{
		//手动裁切
		tem_nRC = m_conOCX.ManualImageCrop(TRUE);
		tem_nRC = m_conOCX.AdjuestImageCrop(FALSE);
		m_conOCX.SetMessage(1);
	} 
	else if(mode==2)
	{
		tem_nRC = m_conOCX.ManualImageCrop(FALSE);
		tem_nRC = m_conOCX.AdjuestImageCrop(FALSE);
	}
	return tem_nRC;
}


int CSmartFilmUI::Self_CaptureImage(CString imgname, int mode)
{
	if(mode == 0)
	{
		//普通拍摄
		Self_CaptureImg(imgname);
		m_nPrcsIndex = -1;
		::PostMessage(g_hCtrHwnd, WM_CAPTUREOVER, 0, 0);
	}
	else if (mode == 1)
	{
		//高密度
		m_strCurImgName = imgname;
		m_nCurImgMode = 1;
		Self_CaptureImgHDRThread(imgname, 1, 0);

		m_nPrcsIndex = -1;
	} 
	else if(mode == 2)
	{
		//低密度
		m_strCurImgName = imgname;
		m_nCurImgMode = 0;

		Self_CaptureImgHDRThread(imgname, 0, 0);

		m_nPrcsIndex = -1;
	}
	
	return 0;
}


int CSmartFilmUI::Self_SetWaterMark(LONG _mode, LONG _site, LONG _size, LONG _font, CString _color, CString _info, LONG _type)
{
	m_nWaterMark = _mode;

	m_nWaterSite = _site;

	m_nWaterSize = _size;

	m_nWaterFont = _font;

	m_strWaterColor = _color;

	m_strWaterInfo = _info;

	m_nWaterMode = _type;

	return 0;
}


void CSmartFilmUI::OnItemchangedListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMLV->uChanged==LVIF_STATE)
	{
		if (pNMLV->uNewState & LVIS_SELECTED)
		{
			if (m_BShowPicCtrl)
			{
				int  tem_nListIndex = pNMLV->iItem;
				if (tem_nListIndex>=0 && tem_nListIndex<m_conListCtrl.GetItemCount())
				{
					//判断图像是否保存
					if (m_vcHistoryImg.size()>2)
					{
						if (m_BNoSaved)
						{
							int tem_nClose = MessageBox(_T("修改尚未保存！是否保存？"), _T("保存"), MB_YESNO);
							if (tem_nClose == 6)
							{
								//确定保存
								CString tem_strNewImgPath = m_vcHistoryImg.back();
								CopyFile(tem_strNewImgPath, m_strFilesPath, FALSE);
								m_BNoSaved = FALSE;
								Self_UpdateThumb(m_nPrcsIndex, m_strFilesPath);
							}					
						}
					}
					//删除缓存图像
					if (m_vcHistoryImg.size()>1)
					{
						std::vector<CString>::iterator item;
						for (item=m_vcHistoryImg.begin()+1; item!=m_vcHistoryImg.end(); item++)
						{
							DeleteFile(*item);
						}
						m_vcHistoryImg.clear();				
					}			

					//重新加载图像		
					m_nPrcsIndex = tem_nListIndex;
					CString  tem_strImgPath = m_vcFilePath[tem_nListIndex];
					CString  tem_strImgFormat = PathFindExtension(tem_strImgPath);
					if (tem_strImgFormat != _T(".pdf") && tem_strImgFormat != _T(".dcm"))
					{		
						Self_ClearPicCtrl();
						Self_CVShowImage(tem_strImgPath);	
					}
					else
					{
						//选择非图像文件，清空picture控件
						m_nPrcsIndex = -1;
						Self_ClearPicCtrl();
						//显示提示信息
						Self_CVShowTipImage(_T("res\\tips.jpg"));
						//清空当前图像
					}	
				}
			}
			else
			{
				int  tem_nListIndex = pNMLV->iItem;
				if (tem_nListIndex>=0 && tem_nListIndex<m_conListCtrl.GetItemCount())
				{
					m_nPrcsIndex = tem_nListIndex;
				}
			}
		}
	}

	*pResult = 0;
}
