#pragma once


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
};
