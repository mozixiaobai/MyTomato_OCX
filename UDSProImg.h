#pragma once
#define WM_IMGPROCESS WM_USER+1002


#include <vector>

// CUDSProImg 对话框

class CUDSProImg : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSProImg)

public:
	CUDSProImg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSProImg();

// 对话框数据
	enum { IDD = IDD_DLG_PROIMG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:


	int m_nBrit;
	int m_nCtst;
	int m_nSatr;
	int m_nGama;


	int m_nOperation;   
	int m_nFontSize;
	int m_nNote;              //标注标示位， 0-关闭，1-画框、画箭头，2-标注
	int m_nLineWidth;       

	BOOL m_BBold;
	BOOL m_BItalic;

	CString m_strFont;
	CString m_strInfo;

	CSliderCtrl m_slidCBright;
	CSliderCtrl m_slidCContrst;
	CSliderCtrl m_slidCGama;

	COLORREF m_clrLineColor;  


	virtual BOOL OnInitDialog();
	
	int m_staBrit;
	int m_staCtst;
	float m_staGama;
	void Self_SetCtrl(int index);
	CComboBox m_conLineWidth;
	CMFCColorButton m_conColor;
	CComboBox m_conFontSize;
	CComboBox m_conFont;
	afx_msg void OnBnClickedBtnBsave();
	afx_msg void OnBnClickedBtnBbackout();
	afx_msg void OnBnClickedBtnBrest();
	afx_msg void OnBnClickedBtnBfitscreen();
	afx_msg void OnBnClickedBtnBorisize();
	afx_msg void OnBnClickedBtnBlrotate();
	afx_msg void OnBnClickedBtnBrrotate();
	afx_msg void OnBnClickedBtnBrotate180();
	afx_msg void OnBnClickedBtnBlmirro();
	afx_msg void OnBnClickedBtnBvmirro();
	afx_msg void OnBnClickedBtnBrotateself();
	afx_msg void OnCustomdrawSlidBbri(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnReleasedcaptureSlidBbri(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSlidBcontrast(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnReleasedcaptureSlidBcontrast(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSlidBgama(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnReleasedcaptureSlidBgama(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnBmarkit();
	afx_msg void OnBnClickedBtnBarrow();
	afx_msg void OnBnClickedBtnBtext();
	afx_msg void OnBnClickedBtnBcrop();
	afx_msg void OnBnClickedBtnBinvert();
	afx_msg void OnBnClickedBtnBsharp();
	void Self_ResetSlider(int mode);
	BOOL Self_DisableCtrl(int index);
	afx_msg void OnBnClickedBtnSure();
	afx_msg void OnBnClickedBtnUnsure();
};
