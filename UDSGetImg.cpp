// UDSGetImg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SmartFilm.h"
#include "UDSGetImg.h"
#include "afxdialogex.h"


// CUDSGetImg �Ի���

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


// CUDSGetImg ��Ϣ�������


BOOL CUDSGetImg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_pParentWnd = GetParentOwner();
	m_hParentWnd = m_pParentWnd->m_hWnd;


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

	//4����������ģʽ
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


//SliderCtrl�ؼ�-------------------------------------------------------------------
void CUDSGetImg::OnCustomdrawSlidAbright(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CUDSGetImg::OnCustomdrawSlidAcontrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CUDSGetImg::OnCustomdrawSlidAfocus(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CUDSGetImg::OnCustomdrawSlidAlight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CUDSGetImg::OnCustomdrawSlidAdelay(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


//Comboboc�ؼ�----------------------------------------------------------------------
void CUDSGetImg::OnSelchangeCmbAres()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CUDSGetImg::OnSelchangeCmbAformat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


//��Ƶ����---------------------------------------------------------------------------
void CUDSGetImg::OnRadio0()
{
	// TODO: �ڴ���������������
	MessageBox(_T(""));
}


void CUDSGetImg::OnRadio90()
{
	// TODO: �ڴ���������������
}


void CUDSGetImg::OnRadio180()
{
	// TODO: �ڴ���������������
}


void CUDSGetImg::OnRadio270()
{
	// TODO: �ڴ���������������
}


//�ϲ��Լ�ˮӡ------------------------------------------------------------------------
void CUDSGetImg::OnClickedChekAlevel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CUDSGetImg::OnClickedChekAvertical()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CUDSGetImg::OnClickedChekAwater()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

