// SmartFilmCtrl.cpp : CSmartFilmCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "SmartFilm.h"
#include "SmartFilmCtrl.h"
#include "SmartFilmPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CSmartFilmCtrl, COleControl)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CSmartFilmCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CSmartFilmCtrl, COleControl)
	DISP_FUNCTION_ID(CSmartFilmCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CSmartFilmCtrl, COleControl)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CSmartFilmCtrl, 1)
	PROPPAGEID(CSmartFilmPropPage::guid)
END_PROPPAGEIDS(CSmartFilmCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CSmartFilmCtrl, "SMARTFILM.SmartFilmCtrl.1",
	0xb5e7a217, 0xbc72, 0x41d1, 0x96, 0x4b, 0xf4, 0x2d, 0xba, 0x83, 0x1, 0xb5)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CSmartFilmCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID IID_DSmartFilm = { 0xF343D629, 0x5863, 0x4806, { 0xBA, 0x82, 0x4, 0xDD, 0x7D, 0x83, 0xDD, 0x5D } };
const IID IID_DSmartFilmEvents = { 0xA2E3D85, 0x99D0, 0x44EF, { 0xA4, 0x91, 0xD5, 0xA2, 0x2C, 0x31, 0x23, 0xDE } };


// �ؼ�������Ϣ

static const DWORD _dwSmartFilmOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CSmartFilmCtrl, IDS_SMARTFILM, _dwSmartFilmOleMisc)



// CSmartFilmCtrl::CSmartFilmCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CSmartFilmCtrl ��ϵͳע�����

BOOL CSmartFilmCtrl::CSmartFilmCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

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



// CSmartFilmCtrl::CSmartFilmCtrl - ���캯��

CSmartFilmCtrl::CSmartFilmCtrl()
{
	InitializeIIDs(&IID_DSmartFilm, &IID_DSmartFilmEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}



// CSmartFilmCtrl::~CSmartFilmCtrl - ��������

CSmartFilmCtrl::~CSmartFilmCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
}



// CSmartFilmCtrl::OnDraw - ��ͼ����

void CSmartFilmCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CSmartFilmCtrl::DoPropExchange - �־���֧��

void CSmartFilmCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// CSmartFilmCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CSmartFilmCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CSmartFilmCtrl::AboutBox - ���û���ʾ�����ڡ���

void CSmartFilmCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_SMARTFILM);
	dlgAbout.DoModal();
}



// CSmartFilmCtrl ��Ϣ�������
