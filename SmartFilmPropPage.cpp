// SmartFilmPropPage.cpp : CSmartFilmPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "SmartFilm.h"
#include "SmartFilmPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CSmartFilmPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CSmartFilmPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CSmartFilmPropPage, "SMARTFILM.SmartFilmPropPage.1",
	0xdd8e05a1, 0x87bf, 0x4bd9, 0x83, 0xc6, 0x47, 0x6c, 0x10, 0x39, 0x2, 0xd4)



// CSmartFilmPropPage::CSmartFilmPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CSmartFilmPropPage ��ϵͳע�����

BOOL CSmartFilmPropPage::CSmartFilmPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SMARTFILM_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CSmartFilmPropPage::CSmartFilmPropPage - ���캯��

CSmartFilmPropPage::CSmartFilmPropPage() :
	COlePropertyPage(IDD, IDS_SMARTFILM_PPG_CAPTION)
{
}



// CSmartFilmPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CSmartFilmPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CSmartFilmPropPage ��Ϣ�������
