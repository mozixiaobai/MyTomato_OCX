#pragma once


// CUDSGetImg �Ի���

class CUDSGetImg : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSGetImg)

public:
	CUDSGetImg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSGetImg();

// �Ի�������
	enum { IDD = IDD_DLG_GETIMG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
