// SmartFilm.cpp : CSmartFilmApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "SmartFilm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSmartFilmApp theApp;

const GUID CDECL _tlid = { 0x83079A3C, 0x1F35, 0x465D, { 0x87, 0xE, 0x22, 0xF0, 0x12, 0x57, 0xA5, 0xB3 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CSmartFilmApp::InitInstance - DLL 初始化

BOOL CSmartFilmApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
		AfxOleInit();                       //6-1允许使用控件
		AfxEnableControlContainer();        //6-1允许控件本身作为容器
	}

	return bInit;
}



// CSmartFilmApp::ExitInstance - DLL 终止

int CSmartFilmApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
