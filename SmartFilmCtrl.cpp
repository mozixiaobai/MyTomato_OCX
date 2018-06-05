// SmartFilmCtrl.cpp : CSmartFilmCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "SmartFilm.h"
#include "SmartFilmCtrl.h"
#include "SmartFilmPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CSmartFilmCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(CSmartFilmCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CSmartFilmCtrl, COleControl)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CSmartFilmCtrl, COleControl)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CSmartFilmCtrl, 1)
	PROPPAGEID(CSmartFilmPropPage::guid)
END_PROPPAGEIDS(CSmartFilmCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CSmartFilmCtrl, "SMARTFILM.SmartFilmCtrl.1",
	0xb5e7a217, 0xbc72, 0x41d1, 0x96, 0x4b, 0xf4, 0x2d, 0xba, 0x83, 0x1, 0xb5)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CSmartFilmCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID IID_DSmartFilm = { 0xF343D629, 0x5863, 0x4806, { 0xBA, 0x82, 0x4, 0xDD, 0x7D, 0x83, 0xDD, 0x5D } };
const IID IID_DSmartFilmEvents = { 0xA2E3D85, 0x99D0, 0x44EF, { 0xA4, 0x91, 0xD5, 0xA2, 0x2C, 0x31, 0x23, 0xDE } };


// 控件类型信息

static const DWORD _dwSmartFilmOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CSmartFilmCtrl, IDS_SMARTFILM, _dwSmartFilmOleMisc)



// CSmartFilmCtrl::CSmartFilmCtrlFactory::UpdateRegistry -
// 添加或移除 CSmartFilmCtrl 的系统注册表项

BOOL CSmartFilmCtrl::CSmartFilmCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_SMARTFILM,
			IDB_SMARTFILM,
			afxRegApartmentThreading,
			_dwSmartFilmOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CSmartFilmCtrl::CSmartFilmCtrl - 构造函数

CSmartFilmCtrl::CSmartFilmCtrl()
{
	InitializeIIDs(&IID_DSmartFilm, &IID_DSmartFilmEvents);
	// TODO: 在此初始化控件的实例数据。
}



// CSmartFilmCtrl::~CSmartFilmCtrl - 析构函数

CSmartFilmCtrl::~CSmartFilmCtrl()
{
	// TODO: 在此清理控件的实例数据。
}



// CSmartFilmCtrl::OnDraw - 绘图函数

void CSmartFilmCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CSmartFilmCtrl::DoPropExchange - 持久性支持

void CSmartFilmCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}



// CSmartFilmCtrl::OnResetState - 将控件重置为默认状态

void CSmartFilmCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// CSmartFilmCtrl::AboutBox - 向用户显示“关于”框

void CSmartFilmCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_SMARTFILM);
	dlgAbout.DoModal();
}



// CSmartFilmCtrl 消息处理程序
