#pragma once
#define WM_SCANSET WM_USER+1001


// CUDSGetImg 对话框

class CUDSGetImg : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSGetImg)

public:
	CUDSGetImg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSGetImg();

// 对话框数据
	enum { IDD = IDD_DLG_GETIMG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CWnd*      m_pParentWnd;
	HWND       m_hParentWnd;

	int m_nLastRes;
	int m_nLastImgType;
	int m_nLastPreRotate;
	int m_nLastMergeMode;
	int m_nLastWaterMark;
	int m_nViewMode;
	int m_nFocusValue;
	int m_nComputer;


	long m_lLeftSite;
	long m_lTopSite;
	long m_lRightSite;
	long m_lBottomSite;



	CString m_strIniPath;
	CString m_strTemDoc;
	CString m_strLastTem;
	CString m_strSaveDoc;


	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCustomdrawSlidAbright(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSlidAcontrast(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSlidAfocus(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSlidAlight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSlidAdelay(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangeCmbAres();
	afx_msg void OnSelchangeCmbAformat();
	afx_msg void OnRadio0();
	afx_msg void OnRadio90();
	afx_msg void OnRadio180();
	afx_msg void OnRadio270();
	afx_msg void OnClickedChekAlevel();
	afx_msg void OnClickedChekAvertical();
	afx_msg void OnClickedChekAwater();
	CString Self_GetMyDocument(void);
	void Self_ReadIni(CString inipath);
};
