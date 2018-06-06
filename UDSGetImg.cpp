// UDSGetImg.cpp : 实现文件
//

#include "stdafx.h"
#include "SmartFilm.h"
#include "UDSGetImg.h"
#include "afxdialogex.h"


// CUDSGetImg 对话框

IMPLEMENT_DYNAMIC(CUDSGetImg, CDialogEx)

CUDSGetImg::CUDSGetImg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSGetImg::IDD, pParent)
{

}

CUDSGetImg::~CUDSGetImg()
{
}

void CUDSGetImg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUDSGetImg, CDialogEx)
END_MESSAGE_MAP()


// CUDSGetImg 消息处理程序
