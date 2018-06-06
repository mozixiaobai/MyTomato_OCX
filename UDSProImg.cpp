// UDSProImg.cpp : 实现文件
//

#include "stdafx.h"
#include "SmartFilm.h"
#include "UDSProImg.h"
#include "afxdialogex.h"


// CUDSProImg 对话框

IMPLEMENT_DYNAMIC(CUDSProImg, CDialogEx)

CUDSProImg::CUDSProImg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSProImg::IDD, pParent)
{

}

CUDSProImg::~CUDSProImg()
{
}

void CUDSProImg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUDSProImg, CDialogEx)
END_MESSAGE_MAP()


// CUDSProImg 消息处理程序
