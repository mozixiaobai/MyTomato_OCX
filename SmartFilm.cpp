// SmartFilm.cpp : CSmartFilmApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "SmartFilm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSmartFilmApp theApp;

const GUID CDECL _tlid = { 0x83079A3C, 0x1F35, 0x465D, { 0x87, 0xE, 0x22, 0xF0, 0x12, 0x57, 0xA5, 0xB3 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CSmartFilmApp::InitInstance - DLL ��ʼ��

BOOL CSmartFilmApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CSmartFilmApp::ExitInstance - DLL ��ֹ

int CSmartFilmApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
