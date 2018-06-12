// UDSWaterMark.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SmartFilm.h"
#include "UDSWaterMark.h"
#include "afxdialogex.h"


// CUDSWaterMark �Ի���

IMPLEMENT_DYNAMIC(CUDSWaterMark, CDialogEx)

CUDSWaterMark::CUDSWaterMark(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSWaterMark::IDD, pParent)
{

	m_editValue = _T("");
}

CUDSWaterMark::~CUDSWaterMark()
{
}

void CUDSWaterMark::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM_SITE, m_conSite);
	DDX_Control(pDX, IDC_COM_SIZE, m_conSize);
	DDX_Control(pDX, IDC_COM_FONT, m_conFont);
	DDX_Control(pDX, IDC_COLOR_MFCCTRL, m_conMFCColor);
	DDX_Text(pDX, IDC_EDIT_INFO, m_editValue);
}


BEGIN_MESSAGE_MAP(CUDSWaterMark, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_WATERTIME, &CUDSWaterMark::OnClickedChkWatertime)
	ON_CBN_SELCHANGE(IDC_COM_SITE, &CUDSWaterMark::OnSelchangeComSite)
	ON_CBN_SELCHANGE(IDC_COM_SIZE, &CUDSWaterMark::OnSelchangeComSize)
	ON_CBN_SELCHANGE(IDC_COM_FONT, &CUDSWaterMark::OnSelchangeComFont)
	ON_BN_CLICKED(IDC_COLOR_MFCCTRL, &CUDSWaterMark::OnClickedColorMfcctrl)
	ON_BN_CLICKED(IDOK, &CUDSWaterMark::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUDSWaterMark::OnBnClickedCancel)
END_MESSAGE_MAP()


// CUDSWaterMark ��Ϣ�������


BOOL CUDSWaterMark::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/***************************
	*
	* 1��������ʼ��
	* 2��ˮӡλ��
	* 3��ˮӡ��С
	* 4��ˮӡ����
	* 5��ˮӡ��ɫ
	* 6����ȡ�����ļ�
	* 7���趨�ؼ���Ӧֵ
	* 9���������Գ�ʼ��
	*
	****************************/

	/*1��������ʼ��*/
	m_nRedValue   = 255;
	m_nGreenValue = 0;
	m_nBlueValue  = 0;

	m_strInipath  = Self_GetMyDocument();
	m_strInipath += _T("\\");
	m_strInipath += _T("UDSXRayDataOcx");
	m_strInipath += _T("\\");
	m_strInipath += _T("BaseConfig.ini");

	/*2��ˮӡλ��*/
	m_conSite.InsertString(0, _T("���Ͻ�"));
	m_conSite.InsertString(1, _T("���½�"));
	m_conSite.InsertString(2, _T("���Ͻ�"));
	m_conSite.InsertString(3, _T("���½�"));
	m_conSite.InsertString(4, _T("����"));

	/*3��ˮӡ��С*/
	m_conSize.InsertString(0, _T("10"));
	m_conSize.InsertString(1, _T("20"));
	m_conSize.InsertString(2, _T("30"));
	m_conSize.InsertString(3, _T("40"));
	m_conSize.InsertString(4, _T("50"));
	m_conSize.InsertString(5, _T("70"));
	m_conSize.InsertString(6, _T("90"));
	m_conSize.InsertString(7, _T("120"));
	m_conSize.InsertString(8, _T("150"));
	m_conSize.InsertString(9, _T("200"));

	/*4��ˮӡ����*/
	m_conFont.InsertString(0, _T("Arial"));
	m_conFont.InsertString(1, _T("Calibri"));
	m_conFont.InsertString(2, _T("Times New Roman"));
	m_conFont.InsertString(3, _T("����"));
	m_conFont.InsertString(4, _T("����"));
	m_conFont.InsertString(5, _T("����"));
	m_conFont.InsertString(6, _T("����"));
	m_conFont.InsertString(7, _T("����"));
	m_conFont.InsertString(8, _T("΢���ź�"));
	m_conFont.InsertString(9, _T("������"));

	/*6����ȡ�����ļ�*/
	Self_ReadWaterIni(m_strInipath);

	/*7�����ÿؼ�Ĭ����*/
	m_conSite.SetCurSel(m_nWaterSite);
	m_conSize.SetCurSel(m_nWaterSize);
	m_conFont.SetCurSel(m_nWaterFont);

	/*5��ˮӡ��ɫ*/
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


	COLORREF    tem_clrColor = RGB(m_nRedValue, m_nGreenValue, m_nBlueValue);
	m_conMFCColor.SetColor(tem_clrColor);
	m_conMFCColor.SetColumnsNumber(5);

	m_editValue = m_strWaterInfo;
	UpdateData(FALSE);

	/*8��Checkbox��ʼ��*/
	if (m_nWaterMode==1)
	{
		((CButton*)GetDlgItem(IDC_CHK_WATERTIME))->SetCheck(TRUE);
		GetDlgItem(IDC_EDIT_INFO)->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_WATERTIME))->SetCheck(FALSE);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


CString CUDSWaterMark::Self_GetMyDocument(void)
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


void CUDSWaterMark::Self_ReadWaterIni(CString inipath)
{
	int     tem_nRead      = 0;
	CString tem_strRead    =_T("");
	CString tem_strIniPath = inipath;

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


void CUDSWaterMark::OnClickedChkWatertime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_WATERTIME))
	{
		GetDlgItem(IDC_EDIT_INFO)->EnableWindow(FALSE);
		m_nWaterMode = 1;
	}
	else
	{
		GetDlgItem(IDC_EDIT_INFO)->EnableWindow(TRUE);
		m_nWaterMode = 0;
	}
}


void CUDSWaterMark::OnSelchangeComSite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int   tem_nCurSel = m_conSite.GetCurSel();
	m_nWaterSite = tem_nCurSel;
}


void CUDSWaterMark::OnSelchangeComSize()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int   tem_nCurSel = m_conSize.GetCurSel();
	m_nWaterSize = tem_nCurSel;
}


void CUDSWaterMark::OnSelchangeComFont()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int    tem_nCurSel = m_conFont.GetCurSel();
	m_nWaterFont = tem_nCurSel;
}


void CUDSWaterMark::OnClickedColorMfcctrl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	COLORREF  tem_clrCurColor;
	tem_clrCurColor = m_conMFCColor.GetColor();

	m_nRedValue   = GetRValue(tem_clrCurColor);
	m_nGreenValue = GetGValue(tem_clrCurColor);
	m_nBlueValue  = GetBValue(tem_clrCurColor);

	CString  tem_strColor;
	tem_strColor.Format(_T("%d"), m_nRedValue);
	m_strWaterColor  = tem_strColor;
	m_strWaterColor += _T("|");

	tem_strColor.Format(_T("%d"), m_nGreenValue);
	m_strWaterColor += tem_strColor;
	m_strWaterColor += _T("|");

	tem_strColor.Format(_T("%d"), m_nBlueValue);
	m_strWaterColor += tem_strColor;
	m_strWaterColor += _T("|");
}


void CUDSWaterMark::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int      tem_nWrite   = 0;
	CString  tem_strWrite = _T("");

	tem_nWrite = m_nWaterSite;
	tem_strWrite.Format(_T("%d"), tem_nWrite);
	::WritePrivateProfileString(_T("BaseSet"), _T("WaterSite"), tem_strWrite, m_strInipath);

	tem_nWrite = m_nWaterSize;
	tem_strWrite.Format(_T("%d"), tem_nWrite);
	::WritePrivateProfileString(_T("BaseSet"), _T("WaterSize"), tem_strWrite, m_strInipath);

	tem_nWrite = m_nWaterFont;
	tem_strWrite.Format(_T("%d"), tem_nWrite);
	::WritePrivateProfileString(_T("BaseSet"), _T("WaterFont"), tem_strWrite, m_strInipath);

	tem_strWrite = m_strWaterColor;
	::WritePrivateProfileString(_T("BaseSet"), _T("WaterColor"), tem_strWrite, m_strInipath);

	tem_strWrite = m_editValue;
	::WritePrivateProfileString(_T("BaseSet"), _T("WaterInfo"), tem_strWrite, m_strInipath);

	tem_nWrite = m_nWaterMode;
	tem_strWrite.Format(_T("%d"), tem_nWrite);
	::WritePrivateProfileString(_T("BaseSet"), _T("WaterMode"), tem_strWrite, m_strInipath);

	CDialogEx::OnOK();
}


void CUDSWaterMark::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
