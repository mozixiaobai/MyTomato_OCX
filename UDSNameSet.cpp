// UDSNameSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SmartFilm.h"
#include "UDSNameSet.h"
#include "afxdialogex.h"


// CUDSNameSet �Ի���

IMPLEMENT_DYNAMIC(CUDSNameSet, CDialogEx)

CUDSNameSet::CUDSNameSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSNameSet::IDD, pParent)
{

	m_EditDivide = _T("");
	m_EditPre1 = _T("");
	m_EditPre2 = _T("");
	m_EditPre3 = _T("");
	m_EditBegin = _T("");
}

CUDSNameSet::~CUDSNameSet()
{
}

void CUDSNameSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_DATE, m_conComDate);
	DDX_Control(pDX, IDC_CMB_TIME, m_conComTime);
	DDX_Text(pDX, IDC_EDIT_DIVITION, m_EditDivide);
	DDX_Text(pDX, IDC_EDIT_PRE1, m_EditPre1);
	//  DDX_Control(pDX, IDC_EDIT_PRE2, m_EditPre2);
	//  DDX_Control(pDX, IDC_EDIT_PRE3, m_EditPre3);
	DDX_Text(pDX, IDC_EDIT_PRE4, m_EditBegin);
	DDX_Text(pDX, IDC_EDIT_PRE2, m_EditPre2);
	DDX_Text(pDX, IDC_EDIT_PRE3, m_EditPre3);
}


BEGIN_MESSAGE_MAP(CUDSNameSet, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_ORDER, &CUDSNameSet::OnClickedChkOrder)
	ON_BN_CLICKED(IDC_CHK_TIME, &CUDSNameSet::OnClickedChkTime)
	ON_BN_CLICKED(IDC_CHK_COSTOM, &CUDSNameSet::OnClickedChkCostom)
	ON_EN_CHANGE(IDC_EDIT_PRE1, &CUDSNameSet::OnChangeEditPre1)
	ON_EN_CHANGE(IDC_EDIT_PRE2, &CUDSNameSet::OnChangeEditPre2)
	ON_EN_CHANGE(IDC_EDIT_PRE3, &CUDSNameSet::OnChangeEditPre3)
	ON_BN_CLICKED(IDOK, &CUDSNameSet::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUDSNameSet::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_RESETORDER, &CUDSNameSet::OnBnClickedBtnResetorder)
END_MESSAGE_MAP()


// CUDSNameSet ��Ϣ�������


BOOL CUDSNameSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/*****************************
	* 
	* 1����ȡ�����ļ�
	* 2��Checkbox��ʼ��
	* 3��Comobox��Edit��ʼ��
	* 4����ʼ��
	* 5���������Գ�ʼ��
	*
	*****************************/

	/*0��������ʼ��*/
	m_BClear = FALSE;

	/*1����ȡ�����ļ�*/
	m_strIniPath = Self_GetIniPath();
	Self_ReadIni(m_strIniPath);

	/*2��CheckBox*/
	switch(m_nNmaeMode)
	{
	case 0:
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(FALSE);
		Self_SetCtrl(0);
		break;
	case 1:
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(FALSE);
		Self_SetCtrl(1);
		break;
	case 2:
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(TRUE);
		Self_SetCtrl(2);
		break;
	default:
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(FALSE);
		Self_SetCtrl(0);
		break;
	}

	/*3��Comobox��Edit��ʼ��*/
	m_conComDate.ResetContent();
	m_conComDate.InsertString(0, _T("������"));
	m_conComDate.InsertString(1, _T("��.��.��"));
	m_conComDate.InsertString(2, _T("��-��-��"));
	m_conComDate.InsertString(3, _T("��_��_��"));

	m_conComTime.ResetContent();
	m_conComTime.InsertString(0, _T("ʱ�������"));
	m_conComTime.InsertString(1, _T("ʱ.��.��.����"));
	m_conComTime.InsertString(2, _T("ʱ-��-��-����"));
	m_conComTime.InsertString(3, _T("ʱ_��_��_����"));

	if (m_nNameDate>=0 && m_nNameDate<=3)
	{
		m_conComDate.SetCurSel(m_nNameDate);
	}
	else
	{
		m_conComDate.SetCurSel(0);
	}

	if (m_nNameTime>=0 && m_nNameTime<=3)
	{
		m_conComTime.SetCurSel(m_nNameTime);
	}
	else
	{
		m_conComTime.SetCurSel(0);
	}

	m_EditDivide = m_strNameDivide;
	m_EditPre1   = m_strNamePre1;
	m_EditPre2   = m_strNamePre2;
	m_EditPre3   = m_strNamePre3;

	m_EditBegin.Format(_T("%04d"), m_nNameBegin);
	UpdateData(FALSE);

	CString   tem_strNameRule = _T("ע��");
	tem_strNameRule += _T("�����ַ����ܱ�ʾ�ļ��� < > / \\ | : \" * ?");
	GetDlgItem(IDC_STA_NAMERULE)->SetWindowText(tem_strNameRule);



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


CString CUDSNameSet::Self_GetIniPath(void)
{
	CString        tem_strMyDocument = _T("");
	TCHAR          tem_cMyDocument[MAX_PATH] = {0};
	LPITEMIDLIST   tem_Pid = NULL;
	SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &tem_Pid);
	if (tem_Pid && SHGetPathFromIDList(tem_Pid, tem_cMyDocument))
	{
		tem_strMyDocument = tem_cMyDocument;
	}
	tem_strMyDocument += _T("\\");
	tem_strMyDocument += _T("UDSXRayDataOcx");
	tem_strMyDocument += _T("\\");
	tem_strMyDocument += _T("BaseConfig.ini");
	return tem_strMyDocument;
}


void CUDSNameSet::Self_ReadIni(CString inipath)
{
	int      tem_nNameInfo   = 0;
	CString  tem_strNameInfo = _T("");

	::GetPrivateProfileString(_T("BaseSet"), _T("NameMode"), _T("û���ҵ�NameMode��Ϣ"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nNameInfo = _ttoi(tem_strNameInfo);
	m_nNmaeMode   = tem_nNameInfo;
	tem_strNameInfo.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameDate"), _T("û���ҵ�NameDate��Ϣ"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nNameInfo = _ttoi(tem_strNameInfo);
	m_nNameDate   = tem_nNameInfo;
	tem_strNameInfo.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameTime"), _T("û���ҵ�NameTime��Ϣ"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nNameInfo = _ttoi(tem_strNameInfo);
	m_nNameTime   = tem_nNameInfo;
	tem_strNameInfo.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameDivide"), _T("û���ҵ�NameDivide��Ϣ"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNameDivide = tem_strNameInfo;
	tem_strNameInfo.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre1"), _T("û���ҵ�NamePre1��Ϣ"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre1 = tem_strNameInfo;
	tem_strNameInfo.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre2"), _T("û���ҵ�NamePre2��Ϣ"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre2 = tem_strNameInfo;
	tem_strNameInfo.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre3"), _T("û���ҵ�NamePre3��Ϣ"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre3 = tem_strNameInfo;
	tem_strNameInfo.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin"), _T("û���ҵ�NameBegin��Ϣ"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nNameInfo = _ttoi(tem_strNameInfo);
	m_nNameBegin   = tem_nNameInfo;
	tem_strNameInfo.ReleaseBuffer();
}


BOOL CUDSNameSet::Self_SetCtrl(int chkindex)
{
	GetDlgItem(IDC_CMB_DATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DIVITION)->EnableWindow(FALSE);
	GetDlgItem(IDC_CMB_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PRE1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PRE2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PRE3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PRE4)->EnableWindow(FALSE);
	switch(chkindex)
	{
	case 0:
		GetDlgItem(IDC_CMB_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DIVITION)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE4)->EnableWindow(FALSE);
		break;
	case 1:
		GetDlgItem(IDC_CMB_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DIVITION)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PRE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE4)->EnableWindow(FALSE);
		break;
	case 2:
		GetDlgItem(IDC_CMB_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DIVITION)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PRE2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PRE3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PRE4)->EnableWindow(TRUE);
		break;
	default:
		GetDlgItem(IDC_CMB_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DIVITION)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE4)->EnableWindow(FALSE);
		break;
	}
	return TRUE;
}


void CUDSNameSet::OnClickedChkOrder()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_ORDER))
	{
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(FALSE);
		Self_SetCtrl(0);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(FALSE);
		Self_SetCtrl(1);
	}
}


void CUDSNameSet::OnClickedChkTime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_TIME))
	{
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(FALSE);
		Self_SetCtrl(1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(TRUE);
		Self_SetCtrl(2);
	}
}


void CUDSNameSet::OnClickedChkCostom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_COSTOM))
	{
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(FALSE);
		Self_SetCtrl(2);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(FALSE);
		Self_SetCtrl(0);
	}
}


void CUDSNameSet::OnChangeEditPre1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_EditPre1.Find('/')>=0 || m_EditPre1.Find('\\')>=0 || m_EditPre1.Find('|')>=0 ||
		m_EditPre1.Find(':')>=0 || m_EditPre1.Find('\?')>=0 || m_EditPre1.Find('\"')>=0 ||
		m_EditPre1.Find('*')>=0 || m_EditPre1.Find('<')>=0 || m_EditPre1.Find('>')>=0)
	{
		int  tem_nEditSize = m_EditPre1.GetLength();
		m_EditPre1 = m_EditPre1.Left(tem_nEditSize-1);

		UpdateData(FALSE);
		if (m_EditPre1.GetLength()>0)
		{
			//����Edit�����ĩβ
			((CEdit*)GetDlgItem(IDC_EDIT_PRE1))->SetSel(m_EditPre1.GetLength(), m_EditPre1.GetLength());
		}
	}
}


void CUDSNameSet::OnChangeEditPre2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_EditPre2.Find('/')>=0 || m_EditPre2.Find('\\')>=0 || m_EditPre2.Find('|')>=0 ||
		m_EditPre2.Find(':')>=0 || m_EditPre2.Find('\?')>=0 || m_EditPre2.Find('\"')>=0 ||
		m_EditPre2.Find('*')>=0 || m_EditPre2.Find('<')>=0 || m_EditPre2.Find('>')>=0)
	{
		int  tem_nEditSize = m_EditPre2.GetLength();
		m_EditPre2 = m_EditPre2.Left(tem_nEditSize-1);

		UpdateData(FALSE);
		if (m_EditPre2.GetLength()>0)
		{
			//����Edit�����ĩβ
			((CEdit*)GetDlgItem(IDC_EDIT_PRE2))->SetSel(m_EditPre2.GetLength(), m_EditPre2.GetLength());
		}
	}
}


void CUDSNameSet::OnChangeEditPre3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_EditPre3.Find('/')>=0 || m_EditPre3.Find('\\')>=0 || m_EditPre3.Find('|')>=0 ||
		m_EditPre3.Find(':')>=0 || m_EditPre3.Find('\?')>=0 || m_EditPre3.Find('\"')>=0 ||
		m_EditPre3.Find('*')>=0 || m_EditPre3.Find('<')>=0 || m_EditPre3.Find('>')>=0)
	{
		int  tem_nEditSize = m_EditPre3.GetLength();
		m_EditPre3 = m_EditPre3.Left(tem_nEditSize-1);

		UpdateData(FALSE);
		if (m_EditPre3.GetLength()>0)
		{
			//����Edit�����ĩβ
			((CEdit*)GetDlgItem(IDC_EDIT_PRE3))->SetSel(m_EditPre3.GetLength(), m_EditPre3.GetLength());
		}
	}
}


void CUDSNameSet::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString tem_strIniInfo = _T("");

	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_ORDER))
	{
		tem_strIniInfo = _T("0");
	} 
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_TIME))
	{
		tem_strIniInfo = _T("1");
	} 
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_COSTOM))
	{
		tem_strIniInfo = _T("2");
	} 
	else
	{
		tem_strIniInfo = _T("0");
	}
	::WritePrivateProfileString(_T("BaseSet"), _T("NameMode"), tem_strIniInfo, m_strIniPath);


	m_nNameDate = m_conComDate.GetCurSel();
	tem_strIniInfo.Format(_T("%d"), m_nNameDate);
	::WritePrivateProfileString(_T("BaseSet"), _T("NameDate"), tem_strIniInfo, m_strIniPath);

	m_nNameTime = m_conComTime.GetCurSel();
	tem_strIniInfo.Format(_T("%d"), m_nNameTime);
	::WritePrivateProfileString(_T("BaseSet"), _T("NameTime"), tem_strIniInfo, m_strIniPath);

	UpdateData(TRUE);

	::WritePrivateProfileString(_T("BaseSet"), _T("NameDivide"), m_EditDivide, m_strIniPath);
	::WritePrivateProfileString(_T("BaseSet"), _T("NamePre1"), m_EditPre1, m_strIniPath);
	::WritePrivateProfileString(_T("BaseSet"), _T("NamePre2"), m_EditPre2, m_strIniPath);
	::WritePrivateProfileString(_T("BaseSet"), _T("NamePre3"), m_EditPre3, m_strIniPath);

	m_nNameBegin = _ttoi(m_EditBegin);
	if (m_nNameBegin>=0 && m_nNameBegin<=9999)
	{
		::WritePrivateProfileString(_T("BaseSet"), _T("NameBegin"), m_EditBegin, m_strIniPath);
	}
	else
	{
		m_nNameBegin = 0;
		m_EditBegin  = _T("0");
		::WritePrivateProfileString(_T("BaseSet"), _T("NameBegin"), m_EditBegin, m_strIniPath);
	}

	if (m_BClear)
	{
		//�������ļ����������ʼλ��Ϊ1
		::WritePrivateProfileString(_T("BaseSet"), _T("NameBegin2"), _T("1"), m_strIniPath);

	}

	CDialogEx::OnOK();
}


void CUDSNameSet::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CUDSNameSet::OnBnClickedBtnResetorder()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_BClear = TRUE;
}
