#pragma once
#define WM_CAPTUREOVER WM_USER+1010
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
		eventidCaptureOver = 2L,
		dispidSetWaterMark = 15L,
		dispidCaptureImage = 14L,
		dispidSetRectMode = 13L,
		dispidSetSaveDir = 12L,
		dispidResetParamers = 11L,
		dispidSetRotate = 10L,
		dispidAutoDelay = 9L,
		dispidSetDelay = 8L,
		dispidSetLight = 7L,
		dispidSetFocus = 6L,
		dispidSetBriCst = 5L,
		dispidSetFormat = 4L,
		dispidSetResolution = 3L,
		dispidUnInit = 2L,
		dispidInit = 1L,
		eventidInitOver = 1L
	};


	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	
protected:

	//初始化完成事件---------------------------------------------------
	void InitOver(void)
	{
		FireEvent(eventidInitOver, EVENT_PARAM(VTS_NONE));
	}
	//拍摄完成事件-----------------------------------------------------
	void CaptureOver(BSTR _filepath)
	{
		FireEvent(eventidCaptureOver, EVENT_PARAM(VTS_BSTR), _filepath);
	}
public:
	CSmartFilmUI m_dlgUI;
	

protected:
	/**
	*  @brief  OCX初始化
	*  @param[in] _uimode 选择UI类型,0-左中右；1-中；2-左中；3-右中
	*  @param[out]
	*  @param[ret] 0-成功
	*/
	LONG Init(LONG _uimode);

	/**
	*  @brief  OCX卸载
	*  @param[in] 
	*  @param[out]
	*  @param[ret] 0-成功
	*/
	LONG UnInit(void);

	/**
	*  @brief  设置图像分辨率
	*  @param[in] 分辨率索引；0-2592*1944；1-3264*2448；2-4032*3024；3-4480*3360
	*  @param[out]
	*  @param[ret] 0-成功
	*/
	LONG SetResolution(LONG _index);

	
	/**
	*  @brief  设置图像格式
	*  @param[in] 图像格式索引；0-bmp；1-jpg；2-png；3-tif；4-pdf；5-dcm；
	*  @param[out]
	*  @param[ret] 0-成功
	*/
	LONG SetFormat(LONG _index);

	/**
	*  @brief  设置亮度对比度
	*  @param[in] 设定值
	*  @param[in] _mode=0,亮度调节；_mode=1,对比度调节
	*  @param[out]
	*  @param[ret] 0-成功
	*/
	LONG SetBriCst(LONG _value, LONG _mode);

	/**
	*  @brief  设置焦点值
	*  @param[in] 设定值[0, 255]
	*  @param[out]
	*  @param[ret] 0-成功
	*/
	LONG SetFocus(LONG _value);

	/**
	*  @brief  设置灯箱亮度
	*  @param[in] 设定值[0, 100]
	*  @param[out]
	*  @param[ret] 0-成功
	*/
	LONG SetLight(LONG _value);

	/**
	*  @brief  设置延时
	*  @param[in] 设定值，单位m
	*  @param[out]
	*  @param[ret] 0-成功
	*/
	LONG SetDelay(LONG _value);

	/**
	*  @brief 自动获取延时
	*  @param[in] 
	*  @param[out]
	*  @param[ret] 延时时间，单位ms
	*/
	LONG AutoDelay(void);

	/**
	*  @brief 设定旋转方向
	*  @param[in] _index,0-0度；1-90度；2-180度；3-270度
	*  @param[out]
	*  @param[ret] 0-成功
	*/
	LONG SetRotate(LONG _index);

	/**
	*  @brief 恢复模板参数
	*  @param[in] 
	*  @param[out]
	*  @param[ret] 0-成功
	*/
	LONG ResetParamers(void);

	/**
	*  @brief 设置目录
	*  @param[in] 
	*  @param[out]
	*  @param[ret] 
	*/
	void SetSaveDir(BSTR _dir);

	/**
	*  @brief 设置区域
	*  @param[in] _mode,0-手动裁切；2-预览模式
	*  @param[out]
	*  @param[ret] 0-成功
	*/
	LONG SetRectMode(LONG _mode);

	/**
	*  @brief 拍照
	*  @param[in] _mode,0-快速拍；1-高密度；2-快速拍
	*  @param[out]
	*  @param[ret] 0-成功
	*/
	LONG CaptureImage(BSTR _imgname, LONG _mode=0);

	/**
	*  @brief 水印设置
	*  @param[in] _mode,0-关闭，1-开启
	*  @param[in] _site,0-左上角，1-左下角，2-右上角，3-右下角，4-居中
	*  @param[in] _size，0-10,1-20,2-30,3-40,4-50,5-70,6-90,7-120,8-150,9-200
	*  @param[in] _font，0-Arial,1-Calibri,2-Times New Roman,3-宋,4-楷,5-仿宋,6-黑,7-隶,8-微软雅黑,9-新宋
	*  @param[in] _color,R|G|B|,如255|0|0|
	*  @param[in] _info,水印信息
	*  @param[in] _type,0-文字水印；1-时间水印
	*  @param[out]
	*  @param[ret] 0-成功
	*/
	LONG SetWaterMark(LONG _mode, LONG _site, LONG _size, LONG _font, BSTR _color, BSTR _info, LONG _type);

	/**
	*  @brief 拍摄完成消息
	*  @param[in] 
	*  @param[out]
	*  @param[ret] 
	*/
	afx_msg LRESULT OnCaptureover(WPARAM wParam, LPARAM lParam);
};

