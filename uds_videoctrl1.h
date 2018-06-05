#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CUds_videoctrl1 包装类

class CUds_videoctrl1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CUds_videoctrl1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xCA859805, 0xA3CE, 0x4594, { 0xB0, 0x19, 0xBC, 0xBB, 0xE7, 0xF6, 0x1E, 0x1 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:


// 操作
public:

// _DUDS_Video

// Functions
//

	long Initial()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void Uninitial()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long GetDeviceCount()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString GetDeviceName(long index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, index);
		return result;
	}
	long StartRun(long index)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, index);
		return result;
	}
	CString GetResolution(long index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, index);
		return result;
	}
	long SetResolution(long index)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, index);
		return result;
	}
	long GetResCount()
	{
		long result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long CaptureImage(LPCTSTR fileName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, fileName);
		return result;
	}
	long StopRun()
	{
		long result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetCurResoIndex()
	{
		long result;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetCurResolution(long * width, long * height)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, width, height);
		return result;
	}
	long AdjuestImageCrop(long bCrop)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bCrop);
		return result;
	}
	long SetColorMode(long type)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms, type);
		return result;
	}
	long RotatedVideo(long type)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, type);
		return result;
	}
	CString CaptureBase64()
	{
		CString result;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long SetAutoExposure(long bOpen)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bOpen);
		return result;
	}
	long GetExposureRange(long * eMin, long * eMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, parms, eMin, eMax);
		return result;
	}
	long GetExposure(long * value, long * bAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, bAuto);
		return result;
	}
	long SetExposure(long value, long bAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, bAuto);
		return result;
	}
	CString HTTPUpload(LPCTSTR url, LPCTSTR fileName, long bDel)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, url, fileName, bDel);
		return result;
	}
	long ShowVideoInfo(long bShow)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bShow);
		return result;
	}
	long CapturePDF(LPCTSTR fileName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms, fileName);
		return result;
	}
	long ManualImageCrop(long bCrop)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bCrop);
		return result;
	}
	long CaptureBarcode(LPCTSTR foldPath, long fileType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, parms, foldPath, fileType);
		return result;
	}
	long AutomaticCapture(LPCTSTR foldPath, long fileType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, foldPath, fileType);
		return result;
	}
	long SetAutomaticSensitiveness(long value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value);
		return result;
	}
	long StartRunEx(long index, long width, long height)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, index, width, height);
		return result;
	}
	long StartSubCamera(long index)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, index);
		return result;
	}
	void StopSubCamera()
	{
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long SetSubResolution(long index)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, index);
		return result;
	}
	long GetSubCurReso(long * width, long * height)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_I4, (void*)&result, parms, width, height);
		return result;
	}
	long GetSubResoCount()
	{
		long result;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString GetSubReso(long index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, index);
		return result;
	}
	long CaptureSubCam(LPCTSTR imgName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_I4, (void*)&result, parms, imgName);
		return result;
	}
	long CaptureTwoCam(LPCTSTR imgName, long capType, long capParam)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, parms, imgName, capType, capParam);
		return result;
	}
	long GetSubCurResoIndex()
	{
		long result;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetJpegQuality(long quality)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, parms, quality);
	}
	long SetImageDPI(long dpi)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_I4, (void*)&result, parms, dpi);
		return result;
	}
	CString CorrectionDPI()
	{
		CString result;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long CaptureCombine(LPCTSTR fileName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_I4, (void*)&result, parms, fileName);
		return result;
	}
	long StartRecord(long index, LPCTSTR fileName, long width, long height, long bitRate, long fps)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, index, fileName, width, height, bitRate, fps);
		return result;
	}
	long StopRecord()
	{
		long result;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long UseImageDPI(BOOL bOpen)
	{
		long result;
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bOpen);
		return result;
	}
	CString GetDevDisplayName(long devIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, devIndex);
		return result;
	}
	long ShowPorpertiesWindow(BOOL bMainCam)
	{
		long result;
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bMainCam);
		return result;
	}
	long GetBrightnessRange(long * bMin, long * bMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bMin, bMax);
		return result;
	}
	long GetBrightness(long * value, long * bAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, bAuto);
		return result;
	}
	long SetBrightness(long value, long bAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, bAuto);
		return result;
	}
	long StartRunByPIDVID(LPCTSTR VID, LPCTSTR PID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_I4, (void*)&result, parms, VID, PID);
		return result;
	}
	CString GetDeviceSn()
	{
		CString result;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long GetContrastRange(long * cMin, long * cMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_I4, (void*)&result, parms, cMin, cMax);
		return result;
	}
	long GetContrast(long * value, long * cAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, cAuto);
		return result;
	}
	long SetContrast(long value, long cAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x36, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, cAuto);
		return result;
	}
	long GetHueRange(long * hMin, long * hMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x37, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMin, hMax);
		return result;
	}
	long GetHue(long * value, long * hAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, hAuto);
		return result;
	}
	long SetHue(long value, long hAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, hAuto);
		return result;
	}
	long GetSaturationRange(long * sMin, long * sMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, sMin, sMax);
		return result;
	}
	long GetSaturation(long * value, long * sAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, sAuto);
		return result;
	}
	long SetSaturation(long value, long sAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, sAuto);
		return result;
	}
	long GetSharpnessRange(long * shMin, long * shMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x3d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, shMin, shMax);
		return result;
	}
	long GetSharpness(long * value, long * shAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, shAuto);
		return result;
	}
	long SetSharpness(long value, long shAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, shAuto);
		return result;
	}
	long GetGammaRange(long * rMin, long * rMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x40, DISPATCH_METHOD, VT_I4, (void*)&result, parms, rMin, rMax);
		return result;
	}
	long GetGamma(long * value, long * gAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x41, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, gAuto);
		return result;
	}
	long SetGamma(long value, long gAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x42, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, gAuto);
		return result;
	}
	long GetWhiteBalanceRange(long * baMin, long * baMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x43, DISPATCH_METHOD, VT_I4, (void*)&result, parms, baMin, baMax);
		return result;
	}
	long GetWhiteBalance(long * value, long * baAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x44, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, baAuto);
		return result;
	}
	long SetWhiteBalance(long value, long baAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x45, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, baAuto);
		return result;
	}
	long GetBacklightComRange(long * bcMin, long * bcMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x46, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bcMin, bcMax);
		return result;
	}
	long GetBacklightCom(long * value, long * bcAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x47, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, bcAuto);
		return result;
	}
	long SetBacklightCom(long value, long bcAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x48, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, bcAuto);
		return result;
	}
	long GetGainRange(long * gMin, long * gMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x49, DISPATCH_METHOD, VT_I4, (void*)&result, parms, gMin, gMax);
		return result;
	}
	long GetGain(long * value, long * gAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x4a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, gAuto);
		return result;
	}
	long SetGain(long value, long gAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x4b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, gAuto);
		return result;
	}
	long GetPanRange(long * pMin, long * pMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x4c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pMin, pMax);
		return result;
	}
	long GetPan(long * value, long * pAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x4d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, pAuto);
		return result;
	}
	long SetPan(long value, long pAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x4e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, pAuto);
		return result;
	}
	long GetTiltRange(long * tMin, long * tMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x4f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, tMin, tMax);
		return result;
	}
	long GetTilt(long * value, long * cAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x50, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, cAuto);
		return result;
	}
	long SetTilt(long value, long tAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x51, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, tAuto);
		return result;
	}
	long GetRollRange(long * rMin, long * rMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x52, DISPATCH_METHOD, VT_I4, (void*)&result, parms, rMin, rMax);
		return result;
	}
	long GetRoll(long * value, long * rAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x53, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, rAuto);
		return result;
	}
	long SetRoll(long value, long rAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x54, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, rAuto);
		return result;
	}
	long GetZoomRange(long * zMin, long * zMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x55, DISPATCH_METHOD, VT_I4, (void*)&result, parms, zMin, zMax);
		return result;
	}
	long GetZoom(long * value, long * zAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x56, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, zAuto);
		return result;
	}
	long SetZoom(long value, long zAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x57, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, zAuto);
		return result;
	}
	long GetIrisRange(long * rMin, long * rMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x58, DISPATCH_METHOD, VT_I4, (void*)&result, parms, rMin, rMax);
		return result;
	}
	long GetIris(long * value, long * iAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x59, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, iAuto);
		return result;
	}
	long SetIris(long value, long iAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x5a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, iAuto);
		return result;
	}
	long GetFocusRange(long * fMin, long * fMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x5b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, fMin, fMax);
		return result;
	}
	long GetFocus(long * value, long * fAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x5c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, fAuto);
		return result;
	}
	long SetFocus(long value, long fAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x5d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, fAuto);
		return result;
	}
	long ShowVideoPorpertiesWindow(BOOL bMainCam)
	{
		long result;
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x5e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bMainCam);
		return result;
	}
	long StartRecordEx(LPCTSTR fileName, long bitRate, long fps)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x5f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, fileName, bitRate, fps);
		return result;
	}
	long GetColorERange(long * cMin, long * cMax)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x60, DISPATCH_METHOD, VT_I4, (void*)&result, parms, cMin, cMax);
		return result;
	}
	long GetColorE(long * value, long * cAuto)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x61, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, cAuto);
		return result;
	}
	long SetColorE(long value, long cAuto)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x62, DISPATCH_METHOD, VT_I4, (void*)&result, parms, value, cAuto);
		return result;
	}
	long GetAudioDevCount()
	{
		long result;
		InvokeHelper(0x63, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString GetAudioDevName(long index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x64, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, index);
		return result;
	}
	long StartRecordWithAudio(long vidIndex, long audIndex, LPCTSTR fileName, long width, long height, long bitRate, long fps)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x65, DISPATCH_METHOD, VT_I4, (void*)&result, parms, vidIndex, audIndex, fileName, width, height, bitRate, fps);
		return result;
	}
	CString GetDeviceSnEx(long devIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x66, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, devIndex);
		return result;
	}
	long SelectDevice(long index)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x67, DISPATCH_METHOD, VT_I4, (void*)&result, parms, index);
		return result;
	}
	long SetResolutionEx(long width, long height)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x68, DISPATCH_METHOD, VT_I4, (void*)&result, parms, width, height);
		return result;
	}
	CString GetResobyIndexEx(long index, long * width, long * height)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x69, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, index, width, height);
		return result;
	}
	long GetImageDPI()
	{
		long result;
		InvokeHelper(0x6a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString UploadFileHttp(LPCTSTR filePath, LPCTSTR url)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x6b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, filePath, url);
		return result;
	}
	CString UploadFileFtp(LPCTSTR locFilePath, LPCTSTR ftpFileName, LPCTSTR ip, LPCTSTR us, LPCTSTR ps, LPCTSTR port)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x6c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, locFilePath, ftpFileName, ip, us, ps, port);
		return result;
	}
	long SetHttpPostString(LPCTSTR key, LPCTSTR valu)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x6d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, key, valu);
		return result;
	}
	CString ImageToBase64(LPCTSTR fileName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x6e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, fileName);
		return result;
	}
	CString CaptureImageAndBase64(LPCTSTR fileName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x6f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, fileName);
		return result;
	}
	void ZoomIn()
	{
		InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ZoomOut()
	{
		InvokeHelper(0x71, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ReturnOrigin()
	{
		InvokeHelper(0x72, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString PlayVideo(LPCTSTR fileName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x73, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, fileName);
		return result;
	}
	long StartRunP(long index)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x74, DISPATCH_METHOD, VT_I4, (void*)&result, parms, index);
		return result;
	}
	long CaptureCombineEx(LPCTSTR fileName, long m_iCombineType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x75, DISPATCH_METHOD, VT_I4, (void*)&result, parms, fileName, m_iCombineType);
		return result;
	}
	long ImageCombine(LPCTSTR filename1, LPCTSTR filename2, LPCTSTR comfilename, long m_iCombineType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x76, DISPATCH_METHOD, VT_I4, (void*)&result, parms, filename1, filename2, comfilename, m_iCombineType);
		return result;
	}
	CString GetAudioDisplayName(long index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x77, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, index);
		return result;
	}
	long SetSubCameraLocation(long location)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x78, DISPATCH_METHOD, VT_I4, (void*)&result, parms, location);
		return result;
	}
	long ImagesCombinePdf(LPCTSTR filenames, LPCTSTR comfilename)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x79, DISPATCH_METHOD, VT_I4, (void*)&result, parms, filenames, comfilename);
		return result;
	}
	long CaptureDICOM(LPCTSTR fileName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, fileName);
		return result;
	}
	long ImagetoDicom(LPCTSTR imagefile, LPCTSTR dicomfile)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x7b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, imagefile, dicomfile);
		return result;
	}
	long DicomtoImage(LPCTSTR dicomfile, LPCTSTR imagefile)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x7c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, dicomfile, imagefile);
		return result;
	}
	long FilesCombineZip(LPCTSTR filenames, LPCTSTR comfilename)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x7d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, filenames, comfilename);
		return result;
	}
	long UpZip(LPCTSTR zipname, LPCTSTR foldername)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x7e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, zipname, foldername);
		return result;
	}
	CString QrCode(LPCTSTR fileName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, fileName);
		return result;
	}
	long PdfToImage(LPCTSTR pdfname, long format, LPCTSTR pre)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR ;
		InvokeHelper(0x80, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pdfname, format, pre);
		return result;
	}
	CString OcrRecognize(LPCTSTR fileName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x81, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, fileName);
		return result;
	}
	CString BarCode(LPCTSTR fileName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x82, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, fileName);
		return result;
	}
	CString BarCodeWithType(LPCTSTR fileName, long type)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x83, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, fileName, type);
		return result;
	}
	long GetRectValue(long * left, long * top, long * right, long * bottom)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x84, DISPATCH_METHOD, VT_I4, (void*)&result, parms, left, top, right, bottom);
		return result;
	}
	long SetRectValue(long left, long top, long right, long bottom)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x85, DISPATCH_METHOD, VT_I4, (void*)&result, parms, left, top, right, bottom);
		return result;
	}
	long SetMessage(long m_b)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x86, DISPATCH_METHOD, VT_I4, (void*)&result, parms, m_b);
		return result;
	}
	long RefreshRect()
	{
		long result;
		InvokeHelper(0x87, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	double SingleVarifyImage(LPCTSTR filename1, LPCTSTR filename2)
	{
		double result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x88, DISPATCH_METHOD, VT_R8, (void*)&result, parms, filename1, filename2);
		return result;
	}
	long SetDisPlayInfo(long width, long height, double ratio)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 ;
		InvokeHelper(0x89, DISPATCH_METHOD, VT_I4, (void*)&result, parms, width, height, ratio);
		return result;
	}
	CString OcrRecognizeEx(LPCTSTR imagefile, LPCTSTR txtfile)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x8a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, imagefile, txtfile);
		return result;
	}
	long SetWaterMark(LPCTSTR watertext, LPCTSTR waterfont, long position, long fontsize, long rvalue, long gvalue, long bvalue, long sapceing, long open)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x8b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, watertext, waterfont, position, fontsize, rvalue, gvalue, bvalue, sapceing, open);
		return result;
	}
	CString OcrRecognizePro(LPCTSTR fileName, long mode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x8c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, fileName, mode);
		return result;
	}
	void DeleteFileEx(LPCTSTR fileName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, fileName);
	}
	long SetDocOptimize(long bOpen)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bOpen);
		return result;
	}
	long SetSubResolutionEx(long index, long guid)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x8f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, index, guid);
		return result;
	}
	long SetResolutionPro(long index, long guid)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x90, DISPATCH_METHOD, VT_I4, (void*)&result, parms, index, guid);
		return result;
	}

// Properties
//



};
