// SmartFilmUI.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SmartFilm.h"
#include "SmartFilmUI.h"
#include "afxdialogex.h"

CString  g_strProXmlPath;        //͸���Ĭ��ģ��
CString  g_strDocXmlPath;        //�����Ĭ��ģ��
std::vector<CString> g_vcRes;
int g_nGrayValue[18][2]={{169,42}, {100,32}, {106,33}, {112,34}, {119,35}, {125,36}, {131,37}, {137,38}, {144,39}, {150,40},{156,41}, {162,42}, {169,43}, {175,44}, {181,45}, {187,46}, {194,47}, {200,48}};


extern CSmartFilmApp theApp;


//���ص���dll
typedef long(*pcamInitCameraLib)(); pcamInitCameraLib  camInitCameraLib;           //��ʼ��
typedef long(*pcamGetDevCount)(long&); pcamGetDevCount camGetDevCount;             //����ͷ����
typedef long(*pcamGetDevPid)(long, char*); pcamGetDevPid camGetDevPid;             //PID
typedef long(*pcamGetDevVid)(long, char*); pcamGetDevVid camGetDevVid;             //VID
typedef char*(*pcamGetDevName)(long); pcamGetDevName   camGetDevName;              //��ȡ�豸����
typedef long(*pcamSetFocusValue)(long, long); pcamSetFocusValue camSetFocusValue;  //���ý���ֵ

// CSmartFilmUI �Ի���

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
}


BEGIN_MESSAGE_MAP(CSmartFilmUI, CDialogEx)
	ON_WM_CLOSE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CTRL, &CSmartFilmUI::OnSelchangeTabCtrl)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSmartFilmUI ��Ϣ�������


BOOL CSmartFilmUI::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	/*1��������ʼ��*/
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

	m_lReturnCode  = -1;
	m_lLeftSite = 0;       //���п�����
	m_lTopSite = 0;
	m_lRightSite = 0;
	m_lBottomSite = 0;

	m_BShowTips = FALSE;
	m_BSaveFmt = FALSE;

	

	/*2��Ŀ¼�Ѿ��ļ�·��*/
	//�����ļ�Ŀ¼
	CFileFind     tem_fileFind;
	m_strConfigDoc  = Self_GetMyDocument();
	m_strConfigDoc += _T("\\");
	m_strConfigDoc += _T("UDSXRayDataOcx");
	if (!tem_fileFind.FindFile(m_strConfigDoc))
	{
		CreateDirectory(m_strConfigDoc, NULL);
	}
	
	//xmlģ��Ŀ¼
	m_strXmlDoc  = m_strConfigDoc;
	m_strXmlDoc += _T("\\");
	m_strXmlDoc += _T("xml");
	if (!tem_fileFind.FindFile(m_strXmlDoc))
	{
		CreateDirectory(m_strXmlDoc, NULL);
	}
	g_strProXmlPath = m_strXmlDoc;
	g_strProXmlPath += _T("\\");
	g_strProXmlPath += _T("͸���Ĭ��.xml");

	g_strDocXmlPath  = m_strXmlDoc;
	g_strDocXmlPath += _T("\\");
	g_strDocXmlPath += _T("�����Ĭ��.xml");

	//����bufferĿ¼
	m_strThumbDoc  = m_strConfigDoc;
	m_strThumbDoc += _T("\\");
	m_strThumbDoc += _T("ThumbBuffer");
	if (!tem_fileFind.FindFile(m_strThumbDoc))
	{
		CreateDirectory(m_strThumbDoc, NULL);
	}

	//ͼ����Ŀ¼
	m_strCVDoc  = m_strConfigDoc;
	m_strCVDoc += _T("\\");
	m_strCVDoc += _T("CVBuffer");
	if (!tem_fileFind.FindFile(m_strCVDoc))
	{
		CreateDirectory(m_strCVDoc, NULL);
	}

	//Ini�ļ�·��
	m_strIniPath  = m_strConfigDoc;
	m_strIniPath += _T("\\");
	m_strIniPath += _T("BaseConfig.ini");	
	CopyFile(_T("BaseConfig.ini"), m_strIniPath, TRUE);

	//config�ļ�·��
	m_strXmlPath  = m_strConfigDoc;
	m_strXmlPath += _T("\\");
	m_strXmlPath += _T("config.xml");
	CopyFile(_T("config.xml"), m_strXmlPath, TRUE);

	/*3������ͷ��ʼ��,�������豸*/
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
		MessageBox(_T("δ�����豸"), _T("UDS"), MB_OK);
		CDialog::OnOK();
		return FALSE;
	}
	m_lReturnCode = m_conOCX.StartRun(tem_nDevIndex);

	/*4����ȡ�����ļ�������Camera*/
	Self_ReadIni(m_strIniPath);
	Self_ReadWaterIni(m_strIniPath);

	/*5��Camera�������*/
	//1)���ֱ�������
	int  tem_nResNum = m_conOCX.GetResCount();
	m_nInterpolateReso = tem_nResNum;
	for (int i=0; i<tem_nResNum; i++)
	{
		CString tem_strResolution = m_conOCX.GetResolution(i);
		//�жϷֱ����Ƿ�<500W,С��500W��ֱ�ӹ���
		if (Self_FilterRes(tem_strResolution))
		{
			g_vcRes.push_back(tem_strResolution);
		}	
	}
	g_vcRes.push_back(_T("4480��3360"));

	if (m_nLastRes == m_nInterpolateReso)
	{
		//��ȡ���ֱ���������������Ϊ���ֱ���
		int  tem_nMaxIndex = Self_GetSpyRes(1);
		m_conOCX.SetResolution(tem_nMaxIndex);
	}
	else
	{
		//����Ϊ�ϴ�ʹ�õķֱ���
		m_conOCX.SetResolution(m_nLastRes);
	}
	//2)��������ת����
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
	//3)��ɫ������
	m_conOCX.SetColorMode(2);
	//4)������Cameraģ��
	if (!PathFileExists(g_strProXmlPath))
	{
		Self_EnsureItems();
	}
	if (!PathFileExists(g_strDocXmlPath))
	{
		Self_EnsureItems2();     //���������Ĭ��ģ��
	}
	//5)������Cameraģ��
	if (m_strLastTem == _T("͸���"))
	{
		Self_ReadXml(g_strProXmlPath);
	} 
	else
	{
		Self_ReadXml(g_strDocXmlPath);
	}

	/*6��Tab����*/
	m_conTab.InsertItem(0, _T("ͼ���ȡ"));
	m_conTab.InsertItem(1, _T("ͼ����"));

	m_dlgGet.Create(IDD_DLG_GETIMG, GetDlgItem(IDC_TAB_CTRL));
	m_dlgPro.Create(IDD_DLG_PROIMG, GetDlgItem(IDC_TAB_CTRL));

	m_dlgGet.ShowWindow(TRUE);
	m_dlgPro.ShowWindow(FALSE);

	m_conTab.SetCurSel(0);

	/*7����ȡ�ļ���ʽ*/
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

	/*8��Ĭ�ϱ���Ŀ¼�������򱣴�������*/
	if (!PathFileExists(m_strSaveDoc))
	{
		//�����ڣ���ȡ����·�������޸�Ĭ��·������
		TCHAR MyDir[_MAX_PATH];  
		SHGetSpecialFolderPath(this->GetSafeHwnd(),MyDir,CSIDL_DESKTOP,0);
		m_strSaveDoc  = MyDir;
		m_strSaveDoc += _T("\\");
	}
	::WritePrivateProfileString(_T("BaseSet"), _T("SaveDoc"), m_strSaveDoc, m_strIniPath);

	/*9������Camera����*/
	CString tem_strOCXDir = Self_GetOCXPath();
	tem_strOCXDir += _T("CmCapture.dll");
 	m_hDllInst = LoadLibrary(_T("CmCapture.dll"));
	if (m_hDllInst)
	{
		//1������dll����---------------------------------------------------------------------
		camInitCameraLib = (pcamInitCameraLib)GetProcAddress(m_hDllInst, "camInitCameraLib");
		camGetDevPid = (pcamGetDevPid)GetProcAddress(m_hDllInst, "camGetDevPid");
		camGetDevVid = (pcamGetDevVid)GetProcAddress(m_hDllInst, "camGetDevVid");
		camGetDevCount = (pcamGetDevCount)GetProcAddress(m_hDllInst, "camGetDevCount");
		camGetDevName = (pcamGetDevName)GetProcAddress(m_hDllInst, "camGetDevName");
		camSetFocusValue = (pcamSetFocusValue)GetProcAddress(m_hDllInst, "camSetFocusValue");

		//2����ȡ��ǰ�豸����-----------------------------------------------------------------
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
		MessageBox(_T("SetFocus"));
	}
	else
	{
		MessageBox(_T("����dllʧ��"));
	}




	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CSmartFilmUI::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSmartFilmUI::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void CSmartFilmUI::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (::IsWindow(GetDlgItem(IDC_TAB_CTRL)->GetSafeHwnd()))
	{
		if (IsIconic())
		{
			return;
		}
		//1����������ؼ�------------------------------------------------------------------------------------
		CClientDC  dc(this);
		//1)����TabԤ��3.2 inch����ListԤ��2.5 inch
		int tem_nCellWidth = dc.GetDeviceCaps(LOGPIXELSX);
		int tem_nCellHeight = dc.GetDeviceCaps(LOGPIXELSY);
		int tem_nTabWidth = (int)((tem_nCellWidth*1.0)*3.2-32);  
		int tem_nListWidth = (int)((tem_nCellWidth*1.0)*2.5-32); 

		//2)������ģʽ+OCX�ߴ��������
		CRect  tem_rcClient;
		GetClientRect(&tem_rcClient);
		if (m_nUIMode == 0)
		{
			//������
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
				GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(TRUE);

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
				GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(TRUE);

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
			//��
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
			//����
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
				GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(TRUE);

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
				GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(TRUE);

				GetDlgItem(IDC_LIST_IMAGE)->ShowWindow(FALSE);
			}

		}
		else if (m_nUIMode == 3)
		{
			//����
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

		//2������TabCtrl�ڿؼ�-------------------------------------------------------------------------------
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//1���ͷ�UDS_Video_OCX
	m_conOCX.StopRun();
	m_conOCX.Uninitial();

	//2�����õ���
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

	//����xml�ļ�
	TiXmlDocument   tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);

	//���ڵ�
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

	::GetPrivateProfileString(_T("BaseSet"), _T("Template"), _T("û���ҵ�Template��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strLastTem = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("UIMode"), _T("û���ҵ�UIMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nUIMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ResIndex"), _T("û���ҵ�ResIndex��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
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

	::GetPrivateProfileString(_T("BaseSet"), _T("ImgType"), _T("û���ҵ�ImgType��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastImgType = tem_nRead;
	tem_strRead.ReleaseBuffer();


	::GetPrivateProfileString(_T("BaseSet"), _T("PreRotate"), _T("û���ҵ�PreRotate��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastPreRotate = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("MergeMode"), _T("û���ҵ�MergeMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastMergeMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterMark"), _T("û���ҵ�WaterMark��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastWaterMark = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameMode"), _T("û���ҵ�NameMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameDate"), _T("û���ҵ�NameDate��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameDate   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameTime"), _T("û���ҵ�NameTime��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameTime   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameDivide"), _T("û���ҵ�NameDivide��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNameDivide = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre1"), _T("û���ҵ�NamePre1��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre1 = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre2"), _T("û���ҵ�NamePre2��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre2 = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre3"), _T("û���ҵ�NamePre3��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre3 = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin"), _T("û���ҵ�NameBegin��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameBegin   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin2"), _T("û���ҵ�NameBegin2��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameBegin2   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveDoc"), _T("û���ҵ���ͷSaveDoc��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strSaveDoc = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewMode"), _T("û���ҵ�ViewMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead   = _ttoi(tem_strRead);
	m_nViewMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewLeft"), _T("û���ҵ�ViewLeft��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead   = _ttoi(tem_strRead);
	m_lLeftSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewTop"), _T("û���ҵ�ViewTop��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead  = _ttoi(tem_strRead);
	m_lTopSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewRight"), _T("û���ҵ�ViewRight��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead    = _ttoi(tem_strRead);
	m_lRightSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewBottom"), _T("û���ҵ�ViewBottom��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_lBottomSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveTips"), _T("û���ҵ�SaveTips��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveFormat"), _T("û���ҵ�SaveFormat��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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

	::GetPrivateProfileString(_T("BaseSet"), _T("lowvalue"), _T("û���ҵ�lowvalue��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nLowLight   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("higvalue"), _T("û���ҵ�SaveFormat��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nHigLight   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("VidoeMode"), _T("û���ҵ�VidoeMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nVidoeMode  = tem_nRead;
	tem_strRead.ReleaseBuffer();	

	::GetPrivateProfileString(_T("BaseSet"), _T("FocusValue"), _T("û���ҵ�FocusValue��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nFocusValue = tem_nRead;
	tem_strRead.ReleaseBuffer();	

	::GetPrivateProfileString(_T("BaseSet"), _T("Computer=0"), _T("û���ҵ�Computer=0��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nIniTime    = tem_nRead;
	tem_strRead.ReleaseBuffer();	
}


void CSmartFilmUI::Self_ReadWaterIni(CString inipath)
{
	int     tem_nRead      = 0;
	CString tem_strRead    =_T("");
	CString tem_strIniPath = inipath;

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterMark"), _T("û���ҵ�WaterMark��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterMark = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterSite"), _T("û���ҵ���ͷWaterSite��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterSite = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterSize"), _T("û���ҵ���ͷWaterSize��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterSize = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterFont"), _T("û���ҵ���ͷWaterFont��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterFont = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterColor"), _T("û���ҵ���ͷWaterColor��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strWaterColor = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterInfo"), _T("û���ҵ���ͷWaterInfo��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strWaterInfo = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterMode"), _T("û���ҵ���ͷWaterMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
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
	int    tem_nResCount = m_conOCX.GetResCount();  //�豸����������
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
	//��vector��������ͬʱ������Ӧ��Ӧ�ĵ�ֵ,��С����
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
	long       tem_lRC       = -1;    //����ֵ
	long       tem_lMark     = -1;    //�Ƿ�֧��
	long       tem_lAuto     = -1;    //�Զ�����
	long       tem_lCurVlaue = -1;    //��ǰֵ
	long       tem_lMaxValue = -1;    //���ֵ
	long       tem_lMinValue = -1;    //��Сֵ

	CString    tem_strName   = _T("");  //������

	PROPERTY   tem_stcCamera;

	std::vector<PROPERTY>  tem_vcCamera;	

	//1����ȡ����ͷ����-----------------------------------------------------
	//ָ��ģ�����
	//��Ȧ
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

	//����-
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

	//�ع�-
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

	//����
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

	//����-
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

	//ɫ��
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

	//ȫ��-
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

	//����
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

	//��б-
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

	//����-
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

	//�Աȶ�-
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

	//������-
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

	//���Ͷ�-
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

	//��ƽ��-
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

	//���Ա�-
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

	//�������
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

	//�ҽ׵���
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

	//��Χ�ع⿪��--------------------------------------------------------------------
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

	//�ϲ���ʽ
	tem_strName = _T("MergeMode");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;       
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 1;           //1-ˮƽ�ϲ���2-��ֱ�ϲ�
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ع�ƫ��
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

	//��ʱ����
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

	//�ҽ׵���
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
	//����忪��
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

	//�ֱ���
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

	//ͼ������
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

	//��Χ�ع�Сģ�������Ա�CheckBoxѡ��
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

	//LDR�������ܶ����㣬Сģ��-----------------------------------
	//����
	tem_strName = _T("LQUABGT");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 10;      //�м����ȡ���Cur
		tem_stcCamera.m_lMaxValue = 40;     //������ȡ���Max
		tem_stcCamera.m_lMinValue = 1;       //��С���ȡ���Min

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//�ҽ׵���
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
	//��ʱ
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
	//���Ա�
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
	//HDR�������ܶ����㣬Сģ��-----------------------------------
	//����
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
	//�ҽ׵���
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
	//��ʱ
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
	//���Ա�
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

	//2����������XML-------------------------------------------------------
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

	//3������XML-----------------------------------------------------------
	CStringA      tem_straPath(g_strProXmlPath);
	const char*   tem_pcPath = tem_straPath.GetString();
	tem_xmlDoc.SaveFile(tem_pcPath);
}


void CSmartFilmUI::Self_EnsureItems2(void)
{
	long       tem_lRC       = -1;    //����ֵ
	long       tem_lMark     = -1;    //�Ƿ�֧��
	long       tem_lAuto     = -1;    //�Զ�����
	long       tem_lCurVlaue = -1;    //��ǰֵ
	long       tem_lMaxValue = -1;    //���ֵ
	long       tem_lMinValue = -1;    //��Сֵ

	CString    tem_strName   = _T("");  //������

	PROPERTY   tem_stcCamera;

	std::vector<PROPERTY>  tem_vcCamera;	

	//1����ȡ����ͷ����-----------------------------------------------------
	//ָ��ģ�����
	//��Ȧ
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

	//����-
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

	//�ع�-
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

	//����
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

	//����-
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

	//ɫ��
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

	//ȫ��-
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

	//����
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

	//��б-
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

	//����-
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

	//�Աȶ�-
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

	//������-
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

	//���Ͷ�-
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

	//��ƽ��-
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

	//���Ա�-
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

	//�������
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

	//�ҽ׵���
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

	//��Χ�ع⿪��--------------------------------------------------------------------
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

	//�ϲ���ʽ
	tem_strName = _T("MergeMode");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;       
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;           //1-ˮƽ�ϲ���2-��ֱ�ϲ�
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ع�ƫ��
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

	//��ʱ����
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

	//�ҽ׵���
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
	//����忪��
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

	//�ֱ���
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

	//ͼ������
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

	//��Χ�ع�Сģ�������Ա�CheckBoxѡ��
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

	//LDRСģ��_���ܶ�-----------------------------------
	//����
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
	//�ҽ׵���
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
	//��ʱ1
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
	//���Ա�1
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

	//HDR_���ܶ�����
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
	//�ҽ׵���2
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
	//��ʱ2
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
	//���Ա�2
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


	//2����������XML-------------------------------------------------------
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

	//3������XML-----------------------------------------------------------
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

	//����xml�ļ�
	TiXmlDocument   tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);

	//���ڵ�
	TiXmlElement*    tem_xmlRootElt = tem_xmlDoc.RootElement();
	
	//Iris�ڵ�
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

	//Bright�ڵ�
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

	//Expos�ڵ�
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

	//Focus�ڵ�
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

	//Gama�ڵ�
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
//			m_conOCX.SetGamma(0, 1);                //ֻ��ȡ�����ã��޸�Ϊ�ҽ�
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastGama     = tem_nSetValue;
//			m_conOCX.SetGamma(tem_nSetValue, 0);     //ֻ��ȡ�����ã��޸�Ϊ�ҽ�
		}
	}

	//Gain�ڵ�
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
//			m_conOCX.SetGain(0, 1);                    //ֻ��ȡ�����ã��޸�Ϊ�ҽ�
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastGain     = tem_nSetValue;
//			m_conOCX.SetGain(tem_nSetValue, 0);         //ֻ��ȡ�����ã��޸�Ϊ�ҽ�
		}
	}

	//Hue�ڵ�
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

	//Pan�ڵ�
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

	//Roll�ڵ�
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

	//Tilt�ڵ�
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

	//Zoom�ڵ�
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

	//Contrast�ڵ�
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

	//Sharp�ڵ�
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

	//Satura�ڵ�
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

	//WhiteBlance�ڵ�
	//����ƽ����Ϊ�Զ�����������
//	m_conOCX.SetWhiteBalance(0, 1);
	//����ʵ��������ð�ƽ��
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
	

	//BackLight�ڵ�
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
			//���Աȵ��������÷ֱ��ʺ��棬�������÷ֱ��ʻ��������Ա�
		}
	}

	//LightBox�ڵ�
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
		
		//���õ���
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

	//�ҽ׽ڵ�
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
	
	//HDR����
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

	//�ϲ���ʽ
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
		m_nHDRMerge = 1;    //���Һϲ�
	} 
	else if(tem_nSetValue == 2)
	{
		m_nHDRMerge = 2;    //���ºϲ�
	}
	else
	{
		m_nHDRMerge = 0;    //�ϲ���ʽδ�򿪣���ʱ��Χ�ع�ر�
	}


	//����ƫ��
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();

	m_nHDRLight = tem_nSetValue;

	//��ʱ
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHDRDelay     = tem_nSetValue;

	//�ҽ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHDRGray      = tem_nSetValue;

	//����忪��
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		m_BDOC = TRUE;
		//�����򿪣�Ԥ��ģʽ������������
		m_nViewMode = 3;
	}
	else
	{
		m_BDOC = FALSE;
		//�����رգ���͸���ض��򿪣�Ԥ��ģʽ����Ϊ3
		m_nViewMode = 1;
	}
	if (m_nViewMode == 0)
	{
		//�ֶ�����
		m_conOCX.ManualImageCrop(TRUE);
		m_conOCX.SetMessage(1);
	}
	else if (m_nViewMode == 1)
	{
		//�̶�����
		m_conOCX.ManualImageCrop(TRUE);
		m_conOCX.SetMessage(1);
		m_conOCX.SetRectValue(m_lLeftSite, m_lTopSite, m_lRightSite, m_lBottomSite);
		m_conOCX.SetMessage(0);

	}
	else if(m_nViewMode == 2)
	{
		//Ԥ��ģʽ
		m_conOCX.ManualImageCrop(FALSE);
		m_conOCX.AdjuestImageCrop(FALSE);
	}
	else
	{
		//�Զ�����
		m_conOCX.ManualImageCrop(FALSE);
		m_conOCX.AdjuestImageCrop(TRUE);
	}
	
	//ͼ��ֱ���
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	//���÷ֱ��ʺ����е���������һ�飬Ӧ����ֱ���
	m_conOCX.SetGamma(g_nGrayValue[m_nLastGray][0], 0);     
	m_conOCX.SetGain(g_nGrayValue[m_nLastGray][1], 0);
	m_conOCX.SetBacklightCom(m_nLastBackLight, 0);
	

	//ͼ���ʽ
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();

	//��Χ�ع⡪�����Ա�
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
		//����
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
		//����
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

//�ؼ�����*****************************************************************************

void CSmartFilmUI::OnSelchangeTabCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		break;
	case 1:
		m_dlgGet.ShowWindow(FALSE);
		m_dlgPro.ShowWindow(TRUE);
		break;
	default:
		break;
	}
	*pResult = 0;
}


//���ڷ���*****************************************************************************
//�������ȡ��Աȶ�--------------------------------------------------
int CSmartFilmUI::AdjustBriCst(int _value, int _mode)
{
	int tem_nCurValue = _value;
	long tem_nMax = 0;
	long tem_nMin = 0;
	int tem_nRC = 0;
	if (_mode==0)
	{
		m_conOCX.GetBrightnessRange(&tem_nMin, &tem_nMax);
		//���ȵ���
		if (tem_nCurValue<tem_nMin)
		{
			tem_nCurValue = tem_nMin;
		}
		else if (tem_nCurValue>tem_nMax)
		{
			tem_nCurValue = tem_nMax;
		}
		tem_nRC = m_conOCX.SetBrightness(tem_nCurValue, 0);
	} 
	else if(_mode==1)
	{
		m_conOCX.GetContrastRange(&tem_nMin, &tem_nMax);
		//�Աȶȵ���
		if (tem_nCurValue<tem_nMin)
		{
			tem_nCurValue = tem_nMin;
		}
		else if (tem_nCurValue>tem_nMax)
		{
			tem_nCurValue = tem_nMax;
		}
		tem_nRC = m_conOCX.SetContrast(tem_nCurValue, 0);
	}
	return tem_nRC;
}


//���ڽ���---------------------------------------------------------
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

	return tem_nRC;
}


//���ڵ�������------------------------------------------------------
int CSmartFilmUI::AdjustLight(int _light)
{
	int tem_nCurValue = _light;
	int tem_nRC = 0;
	Self_SetRelayValue(_light);
	return _light;
}


//���ڷֱ���--------------------------------------------------------
int CSmartFilmUI::AdjustRes(int _index)
{
	int tem_nCurValue = 0;
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
		m_conOCX.SetResolutionPro(tem_nMaxIndex, m_nVidoeMode);
		m_nLastRes = tem_nCurValue;
	} 
	else
	{
		m_conOCX.SetResolutionPro(tem_nCurValue, m_nVidoeMode);
		m_nLastRes = tem_nCurValue;
	}
	//�������ûҽ�
	m_conOCX.SetGamma(g_nGrayValue[m_nLastGray][0], 0);     
	m_conOCX.SetGain(g_nGrayValue[m_nLastGray][1], 0);
	m_conOCX.SetBacklightCom(m_nLastBackLight, 0);
	return m_nLastRes;
}


//����ͼ���ʽ------------------------------------------------------
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
	return _index;
}


//������Ƶ����------------------------------------------------------
int CSmartFilmUI::AdjustRotate(int _rotate)
{
	int tem_nCurValue = _rotate;
	switch(tem_nCurValue)
	{
	case 0:
		m_conOCX.RotatedVideo(0);
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
		m_conOCX.RotatedVideo(0);
		break;
	}
	m_nLastPreRotate = tem_nCurValue;
	return m_nLastPreRotate;
}


//���úϲ�����------------------------------------------------------
int CSmartFilmUI::AdjustMerge(int _merge)
{
	//0-���ϲ���1-���Һϲ���2-���ºϲ�
	m_nLastMergeMode = _merge;
	return m_nLastMergeMode;
}


//����ˮӡ----------------------------------------------------------
int CSmartFilmUI::AdjustWater(int _water, CString _info)
{
	//0-�����ˮӡ��1-���ˮӡ��_infoˮӡ����
	m_nWaterMark = _water;
	return m_nWaterMark;
}
