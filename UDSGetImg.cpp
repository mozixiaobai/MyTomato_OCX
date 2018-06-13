// UDSGetImg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SmartFilm.h"
#include "UDSGetImg.h"
#include "afxdialogex.h"


extern CString  g_strProXmlPath;
extern CString  g_strDocXmlPath;        
extern std::vector<CString> g_vcRes;
extern HWND g_hMainHwnd;

// CUDSGetImg �Ի���

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


// CUDSGetImg ��Ϣ�������


BOOL CUDSGetImg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//2����ȡ�����ļ�·��
	m_strIniPath  = Self_GetMyDocument();
	m_strIniPath += _T("\\");
	m_strIniPath += _T("UDSXRayDataOcx");
	m_strIniPath += _T("\\");
	m_strTemDoc   = m_strIniPath;
	m_strTemDoc  += _T("xml");
	m_strIniPath += _T("BaseConfig.ini");

	//3����ȡ�����ļ�
	Self_ReadIni(m_strIniPath);

	//4����������ģʽ���Լ�slider��ʼ��
	if (m_strLastTem==_T("͸���"))
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

	//5���ֱ��ʡ�ͼ���ʽ��ʼ��
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

	//6��radio��ʼ��
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

	//7���ϲ���ʽ��ˮӡ��ʼ��
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

	//8��EditCtrl��ʼ��

	//9����ѡģʽ��ʼ��
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

	//10�������ؼ���ʼ��
	m_slidAdjFocus.SetRange(0, 255, TRUE);
	m_slidAdjFocus.SetPageSize(1);
	m_slidAdjFocus.SetPos(m_nFocusValue);

	//11���������ܳ�ʼ��
	m_slidComputer.SetRange(1, 20, TRUE);
	if (m_nComputer == 0)
	{
		//�Ƚ���������Ϊȫ��
		m_slidComputer.SetPos(10);
		m_slidComputer.SetPageSize(1);
		((CButton*)GetDlgItem(IDC_CHK_ADELAY))->SetCheck(TRUE);
		GetDlgItem(IDC_SLID_ADELAY)->EnableWindow(FALSE);		

		m_staComputerD = _T("10");
		UpdateData(FALSE);
		//�ٽ�����ָ�Ϊ�̶�
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUDSGetImg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void CUDSGetImg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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

	::GetPrivateProfileString(_T("BaseSet"), _T("Template"), _T("û���ҵ�Template��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strLastTem = tem_strRead;
	tem_nRead = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ResIndex"), _T("û���ҵ�ResIndex��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastRes = tem_nRead;
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

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveDoc"), _T("û���ҵ���ͷSaveDoc��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strSaveDoc = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewMode"), _T("û���ҵ�ViewMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead   = _ttoi(tem_strRead);
	m_nViewMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewLeft"), _T("û���ҵ�ViewLeft��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead   = _ttoi(tem_strRead);
	m_lLeftSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewTop"), _T("û���ҵ�ViewTop��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead  = _ttoi(tem_strRead);
	m_lTopSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewRight"), _T("û���ҵ�ViewRight��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead    = _ttoi(tem_strRead);
	m_lRightSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewBottom"), _T("û���ҵ�ViewBottom��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_lBottomSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("FocusValue"), _T("û���ҵ�FocusValue��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nFocusValue = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("Computer"), _T("û���ҵ�Computer��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
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

	//�ҽ�-----------------------------------------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//HDR����
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//�ϲ���ʽ
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//����ƫ��
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//��ʱ
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//�ҽ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//����忪��
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	if (tem_xmlChildAtb->IntValue() == 0)
	{
		//�����رգ�͸���ش�
		m_BDocMode = FALSE;
		m_nViewMode = 0;
	}
	else
	{
		//������
		m_BDocMode = TRUE;
		m_nViewMode = 3;
	}

	//ͼ��ֱ���
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();

	//ͼ���ʽ
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
}


//SliderCtrl�ؼ�-------------------------------------------------------------------
void CUDSGetImg::OnCustomdrawSlidAbright(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


//Comboboc�ؼ�----------------------------------------------------------------------
void CUDSGetImg::OnSelchangeCmbAres()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Self_SetSlider(g_strProXmlPath);
	::SendMessage(g_hMainHwnd, WM_SCANSET, 8, 0);
}


//��Ƶ����---------------------------------------------------------------------------
void CUDSGetImg::OnRadio0()
{
	// TODO: �ڴ���������������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_0))
	{
		int     tem_nCurSel   = 0;
		::SendMessage(g_hMainHwnd, WM_SCANSET, 9, tem_nCurSel);
	} 
}


void CUDSGetImg::OnRadio90()
{
	// TODO: �ڴ���������������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_90))
	{
		int     tem_nCurSel   = 1;
		::SendMessage(g_hMainHwnd, WM_SCANSET, 9, tem_nCurSel);
	} 
}


void CUDSGetImg::OnRadio180()
{
	// TODO: �ڴ���������������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_180))
	{
		int     tem_nCurSel = 2;
		::SendMessage(g_hMainHwnd, WM_SCANSET, 9, tem_nCurSel);
	} 
}


void CUDSGetImg::OnRadio270()
{
	// TODO: �ڴ���������������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_270))
	{
		int     tem_nCurSel = 3;
		::SendMessage(g_hMainHwnd, WM_SCANSET, 9, tem_nCurSel);
	} 
}


//�ϲ��Լ�ˮӡ------------------------------------------------------------------------
void CUDSGetImg::OnClickedChekAlevel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ˮӡ����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(g_hMainHwnd, WM_SCANSET, 13, 0);
}


void CUDSGetImg::OnBnClickedBtnDir()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(g_hMainHwnd, WM_SCANSET, 11, 0);
}


void CUDSGetImg::OnBnClickedBtnName()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	//�ж�ģ����DOC�Ƿ���
	if (tem_nOpen)
	{
		//������
		m_BDocMode = TRUE;
		m_nViewMode = 3;
	}
	else
	{
		//�����رգ�͸���ش򿪣�Ԥ��ģʽ����Ϊ3
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


	//�ֱ���UI��ʼ��
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	m_conResolution.SetCurSel(tem_nSetValue);

	//ͼ���ʽUI��ʼ��
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(g_hMainHwnd, WM_SCANSET, 16, 0);
}



void CUDSGetImg::OnBnClickedBtnLdr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(g_hMainHwnd, WM_SCANSET, 16, 1);
}


void CUDSGetImg::OnBnClickedBtnCap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
