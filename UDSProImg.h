#pragma once


// CUDSProImg �Ի���

class CUDSProImg : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSProImg)

public:
	CUDSProImg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSProImg();

// �Ի�������
	enum { IDD = IDD_DLG_PROIMG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
