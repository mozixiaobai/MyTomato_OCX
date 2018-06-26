#pragma once
#define WM_CAPTUREOVER WM_USER+1010
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

	//��ʼ������¼�---------------------------------------------------
	void InitOver(void)
	{
		FireEvent(eventidInitOver, EVENT_PARAM(VTS_NONE));
	}
	//��������¼�-----------------------------------------------------
	void CaptureOver(BSTR _filepath)
	{
		FireEvent(eventidCaptureOver, EVENT_PARAM(VTS_BSTR), _filepath);
	}
public:
	CSmartFilmUI m_dlgUI;
	

protected:
	/**
	*  @brief  OCX��ʼ��
	*  @param[in] _uimode ѡ��UI����,0-�����ң�1-�У�2-���У�3-����
	*  @param[out]
	*  @param[ret] 0-�ɹ�
	*/
	LONG Init(LONG _uimode);

	/**
	*  @brief  OCXж��
	*  @param[in] 
	*  @param[out]
	*  @param[ret] 0-�ɹ�
	*/
	LONG UnInit(void);

	/**
	*  @brief  ����ͼ��ֱ���
	*  @param[in] �ֱ���������0-2592*1944��1-3264*2448��2-4032*3024��3-4480*3360
	*  @param[out]
	*  @param[ret] 0-�ɹ�
	*/
	LONG SetResolution(LONG _index);

	
	/**
	*  @brief  ����ͼ���ʽ
	*  @param[in] ͼ���ʽ������0-bmp��1-jpg��2-png��3-tif��4-pdf��5-dcm��
	*  @param[out]
	*  @param[ret] 0-�ɹ�
	*/
	LONG SetFormat(LONG _index);

	/**
	*  @brief  �������ȶԱȶ�
	*  @param[in] �趨ֵ
	*  @param[in] _mode=0,���ȵ��ڣ�_mode=1,�Աȶȵ���
	*  @param[out]
	*  @param[ret] 0-�ɹ�
	*/
	LONG SetBriCst(LONG _value, LONG _mode);

	/**
	*  @brief  ���ý���ֵ
	*  @param[in] �趨ֵ[0, 255]
	*  @param[out]
	*  @param[ret] 0-�ɹ�
	*/
	LONG SetFocus(LONG _value);

	/**
	*  @brief  ���õ�������
	*  @param[in] �趨ֵ[0, 100]
	*  @param[out]
	*  @param[ret] 0-�ɹ�
	*/
	LONG SetLight(LONG _value);

	/**
	*  @brief  ������ʱ
	*  @param[in] �趨ֵ����λm
	*  @param[out]
	*  @param[ret] 0-�ɹ�
	*/
	LONG SetDelay(LONG _value);

	/**
	*  @brief �Զ���ȡ��ʱ
	*  @param[in] 
	*  @param[out]
	*  @param[ret] ��ʱʱ�䣬��λms
	*/
	LONG AutoDelay(void);

	/**
	*  @brief �趨��ת����
	*  @param[in] _index,0-0�ȣ�1-90�ȣ�2-180�ȣ�3-270��
	*  @param[out]
	*  @param[ret] 0-�ɹ�
	*/
	LONG SetRotate(LONG _index);

	/**
	*  @brief �ָ�ģ�����
	*  @param[in] 
	*  @param[out]
	*  @param[ret] 0-�ɹ�
	*/
	LONG ResetParamers(void);

	/**
	*  @brief ����Ŀ¼
	*  @param[in] 
	*  @param[out]
	*  @param[ret] 
	*/
	void SetSaveDir(BSTR _dir);

	/**
	*  @brief ��������
	*  @param[in] _mode,0-�ֶ����У�2-Ԥ��ģʽ
	*  @param[out]
	*  @param[ret] 0-�ɹ�
	*/
	LONG SetRectMode(LONG _mode);

	/**
	*  @brief ����
	*  @param[in] _mode,0-�����ģ�1-���ܶȣ�2-������
	*  @param[out]
	*  @param[ret] 0-�ɹ�
	*/
	LONG CaptureImage(BSTR _imgname, LONG _mode=0);

	/**
	*  @brief ˮӡ����
	*  @param[in] _mode,0-�رգ�1-����
	*  @param[in] _site,0-���Ͻǣ�1-���½ǣ�2-���Ͻǣ�3-���½ǣ�4-����
	*  @param[in] _size��0-10,1-20,2-30,3-40,4-50,5-70,6-90,7-120,8-150,9-200
	*  @param[in] _font��0-Arial,1-Calibri,2-Times New Roman,3-��,4-��,5-����,6-��,7-��,8-΢���ź�,9-����
	*  @param[in] _color,R|G|B|,��255|0|0|
	*  @param[in] _info,ˮӡ��Ϣ
	*  @param[in] _type,0-����ˮӡ��1-ʱ��ˮӡ
	*  @param[out]
	*  @param[ret] 0-�ɹ�
	*/
	LONG SetWaterMark(LONG _mode, LONG _site, LONG _size, LONG _font, BSTR _color, BSTR _info, LONG _type);

	/**
	*  @brief ���������Ϣ
	*  @param[in] 
	*  @param[out]
	*  @param[ret] 
	*/
	afx_msg LRESULT OnCaptureover(WPARAM wParam, LPARAM lParam);
};

