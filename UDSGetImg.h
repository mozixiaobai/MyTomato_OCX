#pragma once
#define WM_SCANSET WM_USER+1001

#include "tinyxml.h"
#include <vector>


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

	int m_nLastRes;
	int m_nLastImgType;
	int m_nLastPreRotate;
	int m_nLastMergeMode;
	int m_nLastWaterMark;
	int m_nViewMode;
	int m_nFocusValue;
	int m_nComputer;
	int m_nLastBright;
	int m_nLastContrast;
	int m_nLastLightBox;


	long m_lLeftSite;
	long m_lTopSite;
	long m_lRightSite;
	long m_lBottomSite;


	BOOL m_BDocMode;


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
	void Self_SetSlider(CString xmlpath);
	CSliderCtrl m_slidABright;
	CSliderCtrl m_slidAContrast;
	CSliderCtrl m_slidALightBox;
	CComboBox m_conResolution;
	CComboBox m_conImgType;
	CSliderCtrl m_slidAdjFocus;
	CSliderCtrl m_slidComputer;
	CString m_staComputerD;
	afx_msg void OnBnClickedBtnHdr();
	afx_msg void OnBnClickedBtnDefault();
	void Self_ResetUI(CString xmlpath);
	afx_msg void OnBnClickedBtnDir();
	afx_msg void OnBnClickedBtnWater();
	afx_msg void OnBnClickedBtnName();
	afx_msg void OnRadioManual();
	afx_msg void OnRadioScan();
	afx_msg void OnBnClickedBtnLdr();
	afx_msg void OnBnClickedBtnCap();
};
