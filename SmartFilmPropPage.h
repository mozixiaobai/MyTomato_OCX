#pragma once

// SmartFilmPropPage.h : CSmartFilmPropPage ����ҳ���������


// CSmartFilmPropPage : �й�ʵ�ֵ���Ϣ������� SmartFilmPropPage.cpp��

class CSmartFilmPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CSmartFilmPropPage)
	DECLARE_OLECREATE_EX(CSmartFilmPropPage)

// ���캯��
public:
	CSmartFilmPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_SMARTFILM };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

