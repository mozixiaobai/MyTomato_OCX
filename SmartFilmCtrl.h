#pragma once

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

// ���Ⱥ��¼� ID
public:
	enum {
	};
};

