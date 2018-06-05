#pragma once

// SmartFilmPropPage.h : CSmartFilmPropPage 属性页类的声明。


// CSmartFilmPropPage : 有关实现的信息，请参阅 SmartFilmPropPage.cpp。

class CSmartFilmPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CSmartFilmPropPage)
	DECLARE_OLECREATE_EX(CSmartFilmPropPage)

// 构造函数
public:
	CSmartFilmPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_SMARTFILM };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

