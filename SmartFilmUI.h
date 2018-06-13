#pragma once
#define WM_SCANSET WM_USER+1001
#define WM_IMGPROCESS WM_USER+1002


#include "uds_videoctrl1.h"
#include "tinyxml.h"
#include "UDSGetImg.h"
#include "UDSProImg.h"
#include "UDSWaterMark.h"
#include "UDSNameSet.h"
#include "ximage.h"
#include "IMAGEAndDCM.h"    //JPGתDCM��
#include "pdflib.h"
#include "pdflib.hpp"
#include "Shellapi.h"
#include "cv.h"
#include "opencv2/photo.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "CvvImage.h"      //ATL��cvvImageͬʱ������CImage
#include <vector>

using namespace cv;
using namespace pdflib;


typedef struct tagPROPERTY
{
	CString   m_strName;
	long      m_lSuport;
	long      m_lAuto;
	long      m_lCurValue;
	long      m_lMaxValue;
	long      m_lMinValue;
}PROPERTY;


// CSmartFilmUI �Ի���

class CSmartFilmUI : public CDialogEx
{
	DECLARE_DYNAMIC(CSmartFilmUI)

public:
	CSmartFilmUI(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSmartFilmUI();

// �Ի�������
	enum { IDD = IDD_DLG_UI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CUDSGetImg m_dlgGet;
	CUDSProImg m_dlgPro;
	CUDSWaterMark m_dlgWater;
	CUDSNameSet m_dlgName;

	CString m_strConfigDoc;  //�����ļ�Ŀ¼
	CString m_strXmlDoc;     //xmlģ��Ŀ¼
	CString m_strThumbDoc;   //ͼ��bufferĿ¼
	CString m_strCVDoc;      //ͼ����Ŀ¼
	CString m_strIniPath;    //Ini·��
	CString m_strXmlPath;    //Xml·��
	CString m_strDevPID;
	CString m_strDevVID;
	CString m_strDevCode;
	CString m_strMyCode1;
	CString m_strLastTem;
	CString m_strNameDivide;
	CString m_strNamePre1;
	CString m_strNamePre2;
	CString m_strNamePre3;
	CString m_strSaveDoc;
	CString m_strWaterColor;
	CString m_strWaterInfo;
	CString m_strFileFormat;
	CString m_strTabImg;       //Tab�ؼ��л�ʱ����ʾͼ��
	CString m_strFilesPath;
	CString m_strBufferImgPath;


	int m_lReturnCode;       //������
	int m_nUIMode;
	int m_nLastRes;
	int m_nLastImgType;
	int m_nLastPreRotate;
	int m_nLastMergeMode;
	int m_nLastWaterMark;
	int m_nNameMode;
	int m_nNameDate;
	int m_nNameTime;
	int m_nNameBegin;
	int m_nNameBegin2;
	int m_nViewMode;
	int m_nLowLight;
	int m_nHigLight;
//	int m_nVidoeMode;
//	int m_nFocusValue;
	int m_nRedValue;
	int m_nGreenValue;
	int m_nBlueValue;
	int m_nIniTime;
	int m_nWaterMark;
	int m_nWaterSite;
	int m_nWaterSize;
	int m_nWaterFont;
	int m_nWaterMode;
	int m_nInterpolateReso;
	int m_nLastIris;
	int m_nLastBright;
	int m_nLastExpos;
	int m_nLastFocus;
	int m_nLastGama;
	int m_nLastGain;
	int m_nLastHue;
	int m_nLastPan;
	int m_nLastRoll;
	int m_nLastTilt;
	int m_nLastZoom;
	int m_nLastContrst;
	int m_nLastSharp;
	int m_nLastSatura;
	int m_nLastWhiteB;
	int m_nLastBackLight;
	int m_nLastGray;
	int m_nHDRDelay;
	int m_nHDRGray;
	int m_nHDRBackLgt;
	int m_nNorLightL;
	int m_nHigLightL;
	int m_nLowLightL;
	int m_nNorGrayL;
	int m_nHigGrayL;
	int m_nLowGrayL;
	int m_nNorDelayL;
	int m_nHigDelayL;
	int m_nLowDelayL;
	int m_nNorBackLgtL;
	int m_nHigBackLgtL;
	int m_nLowBackLgtL;
	int m_nNorLight;
	int m_nNorGray;
	int m_nHigGray;
	int m_nLowGray;
	int m_nNorDelay;
	int m_nHigDelay;
	int m_nLowDelay;
	int m_nNorBackLgt;
	int m_nHigBackLgt;
	int m_nLowBackLgt;
	int m_nLastRelay;
	int m_nIntervalTime;
	int m_nImageCount;     //���ռ���
	int m_nPrcsIndex;
	int m_nThumbWidth;    
	int m_nThumbHeight;
	int m_nRSlcIndex;      //�Ҽ�ѡ������


	long m_lLeftSite;       //���п�����
	long m_lTopSite;
	long m_lRightSite;
	long m_lBottomSite;


	BOOL m_BShowTips;
	BOOL m_BSaveFmt;
	BOOL m_BHDR;
	BOOL m_nHDRMerge;
	BOOL m_nHDRLight;
	BOOL m_BDOC;
	BOOL m_BCtrl;
	BOOL m_BShowPicCtrl;
	BOOL m_BPaintLine;
	BOOL m_BNoSaved;              //�Ƿ񱣴�


	Mat m_cvSrcImage;
	Mat m_cvDstImage;
	Mat m_cvLastImg;
	Mat m_cvNextImg;
	Mat m_cvTipsImg;          //��ʾ��Ϣͼ��


	CRect m_rcPicRect;          //Picture�ؼ�����
	CRect m_rcImageShow;        //ͼ����ʾ���꣬�����Picture�ؼ�
	CRect m_rcImageCrop;        //ͼ���ѡ���꣬�����Picture�ؼ�
	CRect m_rcImageRect;        //��Ҫ��ʾ��ͼ��rect


	int m_nDrawX;             //ͼ�����ź�������
	int m_nDrawY;
	int m_nImageBright;       //ͼ������
	int m_nImageContrast;     //ͼ��Աȶ�
	int m_nOffsetX, m_nOffsetY;
	int m_nShowWidth;         //��ʼ����ʾ���
	int m_nShowHeight;        //��ʼ����ʾ�߶�

	float      m_fCurRatio;           //��ǰ���ű���
	float      m_fPI;                  //Բ���ʳ���

	
	std::vector<CString> m_vcImgName;         //ͼ����    
	std::vector<CString> m_vcThumbPath;       //����ͼ·��
	std::vector<CString> m_vcFilePath;        //�����ļ�·��
	std::vector<CString> m_vcHistoryImg;


	CImageList m_imagelist;

	CMenu m_ListMenu;

	//����
	int       m_nVidoeMode;        //MJPG/YUY2
	int       m_nFocusValue;       //��ǰ����ֵ
	int       m_nDevIndex;         //��ǰ���豸����
	HINSTANCE m_hDllInst;          //���ص���dll     



	CUds_videoctrl1 m_conOCX;
	virtual BOOL OnInitDialog();
	CString Self_GetMyDocument(void);
	BOOL Self_FindCamera(CString xmlpath);
	void Self_ReadIni(CString inipath);
	void Self_ReadWaterIni(CString inipath);
	BOOL Self_FilterRes(CString res);
	int Self_GetSpyRes(int diyvalue);
	void Self_EnsureItems(void);
	void Self_EnsureItems2(void);
	void Self_ReadXml(CString xmlpath);
	void Self_SetRelay100(void);
	void Self_SetRelayZero(void);
	void Self_SetRelayValue(int dstvalue);
	afx_msg void OnClose();
	void Self_SetRelay1(void);
	CTabCtrl m_conTab;
	CListCtrl m_conListCtrl;
	afx_msg void OnSelchangeTabCtrl(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CString Self_GetOCXPath(void);
	int AdjustBriCst(int _value, int _mode);
	int AdjustFocus(int _focus);
	int AdjustLight(int _light);
	int AdjustRes(int _index);
	int AdjustFormat(int _index);
	int AdjustRotate(int _rotate);
	int AdjustMerge(int _merge);
	int AdjustWater(int _water, CString _info);
protected:
	afx_msg LRESULT OnScanset(WPARAM wParam, LPARAM lParam);
public:
	int AdjustDelay(int _delay);
	int Self_GetIntervalTime(void);
	void AdjustRelay(int value, int src);
	double Self_GetAvgGray(CString imgpath);
	CString Self_SlcSaveDoc(void);
	void Slef_ChangeSavePath(CString savedir);
	void Self_ReadNameRule(void);
	void Self_CaptureImg(CString imgname);
	CString Self_NamingFile(int count);
	CString Self_InterPolateImage(CString srcImage, CString dstImage, int index);
	void Self_AddWaterMark(CString imgpath);
	CString Self_CreateThumb(CString srcimg, CString dstimg);
	int GetTypeFromFileName(LPCTSTR pstr);
	int Self_GetFontSize(int index);
	CString Self_GetFontName(int index);
	BOOL ThumbaiList(int thumbwidth, int thumbheight);
	CString Self_GetTimeInfo(void);
	int Self_GetFontWidth(LOGFONT text, CString textinfo);
	CString Self_GetPDFFromImg(CString imgpath, CString pdfpath);
	afx_msg void OnDblclkListImage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickListImage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void On32768Delte();
	afx_msg void On32769Property();
	void Self_ShowImgInfo(CString imgpath);
	void Self_ShowOcxCtrl(void);
	void Self_ShowPicCtrl(void);
	void Self_CVShowImage(CString imgpath);
	void Self_ResetImageRect(void);
	void Self_ResizeImage(CWnd* pWnd, Mat srcImg);
	void Self_ShowMatImage2(Mat img, CRect rect);
	void Self_CVShowTipImage(CString imgpath);
	BOOL Self_EnsureSave(void);
	void Self_UpdateThumb(int index, CString imgpath);
	void Self_ReplaceImage(int thumbwidth, int thumbheight, int item);
	void Self_ClearPicCtrl(void);
	CStatic m_conPicCtrl;
};
