#pragma once


using namespace std;


// CUDSWaterMark �Ի���

class CUDSWaterMark : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSWaterMark)

public:
	CUDSWaterMark(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSWaterMark();

// �Ի�������
	enum { IDD = IDD_DLG_WATERMARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int        m_nRedValue;
	int        m_nGreenValue;
	int        m_nBlueValue;
	int        m_nWaterSite;
	int        m_nWaterSize;
	int        m_nWaterFont;
	int        m_nWaterMode;      //ʱ��ˮӡ

	CString    m_strInipath;
	CString    m_strWaterColor;
	CString    m_strWaterInfo;    //ˮӡ��Ϣ

	CComboBox m_conSite;
	CComboBox m_conSize;
	CComboBox m_conFont;
	CMFCColorButton m_conMFCColor;
	CString m_editValue;
	virtual BOOL OnInitDialog();
	CString Self_GetMyDocument(void);
	void Self_ReadWaterIni(CString inipath);
	afx_msg void OnClickedChkWatertime();
	afx_msg void OnSelchangeComSite();
	afx_msg void OnSelchangeComSize();
	afx_msg void OnSelchangeComFont();
	afx_msg void OnClickedColorMfcctrl();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
