#pragma once


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
};
