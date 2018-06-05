#pragma once
#include "uds_videoctrl1.h"
#include "tinyxml.h"


// CSmartFilmUI 对话框

class CSmartFilmUI : public CDialogEx
{
	DECLARE_DYNAMIC(CSmartFilmUI)

public:
	CSmartFilmUI(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSmartFilmUI();

// 对话框数据
	enum { IDD = IDD_DLG_UI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strConfigDoc;  //配置文件目录
	CString m_strXmlDoc;     //xml模板目录
	CString m_strThumbDoc;   //图像buffer目录
	CString m_strCVDoc;      //图像处理目录
	CString m_strIniPath;    //Ini路径
	CString m_strXmlPath;    //Xml路径
	CString m_strDevPID;
	CString m_strDevVID;
	CString m_strDevCode;
	CString m_strMyCode1;
	CString m_strLastTem;
	CString m_strNameDivide;
	CString m_strNamePre1;
	CString m_strNamePre2;
	CString m_strNamePre3;
	CString m_strSaveDoc;
	CString m_strWaterColor;
	CString m_strWaterInfo;


	int m_lReturnCode;       //返回码
	int m_nLastRes;
	int m_nLastImgType;
	int m_nLastPreRotate;
	int m_nLastMergeMode;
	int m_nLastWaterMark;
	int m_nNameMode;
	int m_nNameDate;
	int m_nNameTime;
	int m_nNameBegin;
	int m_nNameBegin2;
	int m_nViewMode;
	int m_nLowLight;
	int m_nHigLight;
	int m_nVidoeMode;
	int m_nFocusValue;
	int m_nIniTime;
	int m_nWaterMark;
	int m_nWaterSite;
	int m_nWaterSize;
	int m_nWaterFont;
	int m_nWaterMode;

	long m_lLeftSite;       //裁切框坐标
	long m_lTopSite;
	long m_lRightSite;
	long m_lBottomSite;

	BOOL m_BShowTips;
	BOOL m_BSaveFmt;
	





	CUds_videoctrl1 m_conOCX;
	virtual BOOL OnInitDialog();
	CString Self_GetMyDocument(void);
	BOOL Self_FindCamera(CString xmlpath);
	void Self_ReadIni(CString inipath);
	void Self_ReadWaterIni(CString inipath);
};
