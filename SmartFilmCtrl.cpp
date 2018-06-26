// SmartFilmCtrl.cpp : CSmartFilmCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "SmartFilm.h"
#include "SmartFilmCtrl.h"
#include "SmartFilmPropPage.h"
#include "afxdialogex.h"

extern HWND g_hMainHwnd;
HWND g_hCtrHwnd;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CSmartFilmCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(CSmartFilmCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_MESSAGE(WM_CAPTUREOVER, &CSmartFilmCtrl::OnCaptureover)
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CSmartFilmCtrl, COleControl)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "Init", dispidInit, Init, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "UnInit", dispidUnInit, UnInit, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "SetResolution", dispidSetResolution, SetResolution, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "SetFormat", dispidSetFormat, SetFormat, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "SetBriCst", dispidSetBriCst, SetBriCst, VT_I4, VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "SetFocus", dispidSetFocus, SetFocus, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "SetLight", dispidSetLight, SetLight, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "SetDelay", dispidSetDelay, SetDelay, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "AutoDelay", dispidAutoDelay, AutoDelay, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "SetRotate", dispidSetRotate, SetRotate, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "ResetParamers", dispidResetParamers, ResetParamers, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "SetSaveDir", dispidSetSaveDir, SetSaveDir, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "SetRectMode", dispidSetRectMode, SetRectMode, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "CaptureImage", dispidCaptureImage, CaptureImage, VT_I4, VTS_BSTR VTS_I4)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "SetWaterMark", dispidSetWaterMark, SetWaterMark, VT_I4, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_I4)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CSmartFilmCtrl, COleControl)
	EVENT_CUSTOM_ID("InitOver", eventidInitOver, InitOver, VTS_NONE)
	EVENT_CUSTOM_ID("CaptureOver", eventidCaptureOver, CaptureOver, VTS_BSTR)
END_EVENT_MAP()

//Implementation of IObjectSafety自己添加部分-------------------------------
BEGIN_INTERFACE_MAP(CSmartFilmCtrl, COleControl)
	INTERFACE_PART(CSmartFilmCtrl, IID_IObjectSafety, ObjectSafety)
END_INTERFACE_MAP()
//-------------------------------------------------------------------------


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
	CRect tem_rcUI;
	GetClientRect(&tem_rcUI);
	m_dlgUI.ShowWindow(SW_SHOW);
	m_dlgUI.MoveWindow(&tem_rcUI, TRUE);
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


int CSmartFilmCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_dlgUI.m_hWnd=m_hWnd;
	m_dlgUI.Create(IDD_DLG_UI, this);
	InitOver();
	g_hCtrHwnd = this->m_hWnd;

	return 0;
}

// Implementation of IObjectSafety自己添加部分---------------------------
STDMETHODIMP CSmartFilmCtrl::XObjectSafety::GetInterfaceSafetyOptions(
	REFIID riid,
	DWORD __RPC_FAR *pdwSupportedOptions,
	DWORD __RPC_FAR *pdwEnabledOptions)
{
	METHOD_PROLOGUE_EX(CSmartFilmCtrl, ObjectSafety)

		if (!pdwSupportedOptions || !pdwEnabledOptions)
		{
			return E_POINTER;
		}

		*pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
		*pdwEnabledOptions = 0;

		if (NULL == pThis->GetInterface(&riid))
		{
			TRACE("Requested interface is not supported.\n");
			return E_NOINTERFACE;
		}

		// What interface is being checked out anyhow?
		OLECHAR szGUID[39];
		int i = StringFromGUID2(riid, szGUID, 39);

		if (riid == IID_IDispatch)
		{
			// Client wants to know if object is safe for scripting
			*pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER;
			return S_OK;
		}
		else if (riid == IID_IPersistPropertyBag
			|| riid == IID_IPersistStreamInit
			|| riid == IID_IPersistStorage
			|| riid == IID_IPersistMemory)
		{
			// Those are the persistence interfaces COleControl derived controls support
			// as indicated in AFXCTL.H
			// Client wants to know if object is safe for initializing from persistent data
			*pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA;
			return S_OK;
		}
		else
		{
			// Find out what interface this is, and decide what options to enable
			TRACE("We didn't account for the safety of this interface, and it's one we support...\n");
			return E_NOINTERFACE;
		}
}

STDMETHODIMP CSmartFilmCtrl::XObjectSafety::SetInterfaceSafetyOptions(
	REFIID riid,
	DWORD dwOptionSetMask,
	DWORD dwEnabledOptions)
{
	METHOD_PROLOGUE_EX(CSmartFilmCtrl, ObjectSafety)

		OLECHAR szGUID[39];
	// What is this interface anyway?
	// We can do a quick lookup in the registry under HKEY_CLASSES_ROOT\Interface
	int i = StringFromGUID2(riid, szGUID, 39);

	if (0 == dwOptionSetMask && 0 == dwEnabledOptions)
	{
		// the control certainly supports NO requests through the specified interface
		// so it's safe to return S_OK even if the interface isn't supported.
		return S_OK;
	}

	// Do we support the specified interface?
	if (NULL == pThis->GetInterface(&riid))
	{
		TRACE1("%s is not support.\n", szGUID);
		return E_FAIL;
	}


	if (riid == IID_IDispatch)
	{
		TRACE("Client asking if it's safe to call through IDispatch.\n");
		TRACE("In other words, is the control safe for scripting?\n");
		if (INTERFACESAFE_FOR_UNTRUSTED_CALLER == dwOptionSetMask && INTERFACESAFE_FOR_UNTRUSTED_CALLER == dwEnabledOptions)
		{
			return S_OK;
		}
		else
		{
			return E_FAIL;
		}
	}
	else if (riid == IID_IPersistPropertyBag
		|| riid == IID_IPersistStreamInit
		|| riid == IID_IPersistStorage
		|| riid == IID_IPersistMemory)
	{
		TRACE("Client asking if it's safe to call through IPersist*.\n");
		TRACE("In other words, is the control safe for initializing from persistent data?\n");

		if (INTERFACESAFE_FOR_UNTRUSTED_DATA == dwOptionSetMask && INTERFACESAFE_FOR_UNTRUSTED_DATA == dwEnabledOptions)
		{
			return NOERROR;
		}
		else
		{
			return E_FAIL;
		}
	}
	else
	{
		TRACE1("We didn't account for the safety of %s, and it's one we support...\n", szGUID);
		return E_FAIL;
	}
}

STDMETHODIMP_(ULONG) CSmartFilmCtrl::XObjectSafety::AddRef()
{
	METHOD_PROLOGUE_EX_(CSmartFilmCtrl, ObjectSafety)
		return (ULONG)pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CSmartFilmCtrl::XObjectSafety::Release()
{
	METHOD_PROLOGUE_EX_(CSmartFilmCtrl, ObjectSafety)
		return (ULONG)pThis->ExternalRelease();
}

STDMETHODIMP CSmartFilmCtrl::XObjectSafety::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(CSmartFilmCtrl, ObjectSafety)
		return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

// ------------------------------------------------------------------------




LONG CSmartFilmCtrl::Init(LONG _uimode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	m_dlgUI.m_nUIMode = _uimode;
	::SendMessage(g_hMainHwnd, WM_SIZE, 0, 0);

	return 0;
}


LONG CSmartFilmCtrl::UnInit(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	m_dlgUI.StopRun();

	return 0;
}


LONG CSmartFilmCtrl::SetResolution(LONG _index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	long rc = m_dlgUI.AdjustRes(_index);

	return rc;
}


LONG CSmartFilmCtrl::SetFormat(LONG _index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	long rc = m_dlgUI.AdjustFormat(_index);

	return rc;
}


LONG CSmartFilmCtrl::SetBriCst(LONG _value, LONG _mode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
    long rc = m_dlgUI.AdjustBriCst(_value, _mode);

	return rc;
}


LONG CSmartFilmCtrl::SetFocus(LONG _value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	long rc = m_dlgUI.AdjustFocus(_value);

	return rc;
}


LONG CSmartFilmCtrl::SetLight(LONG _value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	long rc = m_dlgUI.AdjustLight(_value);

	return rc;
}


LONG CSmartFilmCtrl::SetDelay(LONG _value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	long rc = m_dlgUI.AdjustDelay(_value);

	return rc;
}


LONG CSmartFilmCtrl::AutoDelay(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	long rc = m_dlgUI.Self_GetIntervalTime();

	return rc;
}


LONG CSmartFilmCtrl::SetRotate(LONG _index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	long rc = m_dlgUI.AdjustRotate(_index);

	return rc;
}


LONG CSmartFilmCtrl::ResetParamers(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	m_dlgUI.Self_ResetParamers();

	return 0;
}


void CSmartFilmCtrl::SetSaveDir(BSTR _dir)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	m_dlgUI.Self_SetSaveDir(_dir);
}


LONG CSmartFilmCtrl::SetRectMode(LONG _mode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	long rc = m_dlgUI.Self_SetRectMode(_mode);

	return rc;
}


LONG CSmartFilmCtrl::CaptureImage(BSTR _imgname, LONG _mode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	m_dlgUI.Self_CaptureImage(_imgname, _mode);	
	
	return 0;
}


LONG CSmartFilmCtrl::SetWaterMark(LONG _mode, LONG _site, LONG _size, LONG _font, BSTR _color, BSTR _info, LONG _type)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	m_dlgUI.Self_SetWaterMark(_mode, _site, _size, _font, _color, _info, _type);

	return 0;
}


afx_msg LRESULT CSmartFilmCtrl::OnCaptureover(WPARAM wParam, LPARAM lParam)
{
	CString tem_strCurFilePath = m_dlgUI.m_strCurImgPath;
	BSTR tem_bstrCurFilePath = tem_strCurFilePath.AllocSysString();
	SysFreeString(tem_bstrCurFilePath);
	CaptureOver(tem_bstrCurFilePath);
	return 0;
}
