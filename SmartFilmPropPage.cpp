// SmartFilmPropPage.cpp : CSmartFilmPropPage 属性页类的实现。

#include "stdafx.h"
#include "SmartFilm.h"
#include "SmartFilmPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CSmartFilmPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CSmartFilmPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CSmartFilmPropPage, "SMARTFILM.SmartFilmPropPage.1",
	0xdd8e05a1, 0x87bf, 0x4bd9, 0x83, 0xc6, 0x47, 0x6c, 0x10, 0x39, 0x2, 0xd4)



// CSmartFilmPropPage::CSmartFilmPropPageFactory::UpdateRegistry -
// 添加或移除 CSmartFilmPropPage 的系统注册表项

BOOL CSmartFilmPropPage::CSmartFilmPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SMARTFILM_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CSmartFilmPropPage::CSmartFilmPropPage - 构造函数

CSmartFilmPropPage::CSmartFilmPropPage() :
	COlePropertyPage(IDD, IDS_SMARTFILM_PPG_CAPTION)
{
}



// CSmartFilmPropPage::DoDataExchange - 在页和属性间移动数据

void CSmartFilmPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CSmartFilmPropPage 消息处理程序
