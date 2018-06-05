#pragma once
#include "SmartFilmUI.h"
#include <objsafe.h>  //IObjectSafe安全初始化接口


// SmartFilmCtrl.h : CSmartFilmCtrl ActiveX 控件类的声明。


// CSmartFilmCtrl : 有关实现的信息，请参阅 SmartFilmCtrl.cpp。

class CSmartFilmCtrl : public COleControl
{
	DECLARE_DYNCREATE(CSmartFilmCtrl)

// 构造函数
public:
	CSmartFilmCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CSmartFilmCtrl();

	DECLARE_OLECREATE_EX(CSmartFilmCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CSmartFilmCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CSmartFilmCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CSmartFilmCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()
	
	//Implementation of IObjectSafety自己添加部分-------------------------------
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(ObjectSafety, IObjectSafety)
		STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD __RPC_FAR *pdwSupportedOptions, DWORD __RPC_FAR *pdwEnabledOptions);
		STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);
	END_INTERFACE_PART(ObjectSafety)
	//--------------------------------------------------------------------------
	
// 调度和事件 ID
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

