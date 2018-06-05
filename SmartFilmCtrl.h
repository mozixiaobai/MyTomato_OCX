#pragma once
#include "SmartFilmUI.h"
#include <objsafe.h>  //IObjectSafe��ȫ��ʼ���ӿ�


// SmartFilmCtrl.h : CSmartFilmCtrl ActiveX �ؼ����������


// CSmartFilmCtrl : �й�ʵ�ֵ���Ϣ������� SmartFilmCtrl.cpp��

class CSmartFilmCtrl : public COleControl
{
	DECLARE_DYNCREATE(CSmartFilmCtrl)

// ���캯��
public:
	CSmartFilmCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CSmartFilmCtrl();

	DECLARE_OLECREATE_EX(CSmartFilmCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CSmartFilmCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CSmartFilmCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CSmartFilmCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()
	
	//Implementation of IObjectSafety�Լ���Ӳ���-------------------------------
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(ObjectSafety, IObjectSafety)
		STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD __RPC_FAR *pdwSupportedOptions, DWORD __RPC_FAR *pdwEnabledOptions);
		STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);
	END_INTERFACE_PART(ObjectSafety)
	//--------------------------------------------------------------------------
	
// ���Ⱥ��¼� ID
public:
	enum {
		eventidInitOver = 1L
	};


	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	CSmartFilmUI m_dlgUI;
	int Init(void);
protected:

	void InitOver(void)
	{
		FireEvent(eventidInitOver, EVENT_PARAM(VTS_NONE));
	}
};

