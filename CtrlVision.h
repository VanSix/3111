// CtrlVision.h: interface for the CCtrlVision class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTRLVISION_H__C18B56E6_E8EB_4B79_A731_17BA8A94EBE5__INCLUDED_)
#define AFX_CTRLVISION_H__C18B56E6_E8EB_4B79_A731_17BA8A94EBE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//
#include "CameraDS.h"

// �۾��̤j�ƶq
#define _MaxCam			10	// �]�j�@�I, �קK�Q�H���J�Ӧh Cam, �y�����..
#define _CAMERA_WIDTH	640
#define _CAMERA_HEIGHT	480

class CCtrlVision  
{
public:
	CCtrlVision();
	virtual ~CCtrlVision();

	// Caram List
	CArray <CString, CString> m_CaramList;					// �x�s�۾��C�� Array
	bool m_bIsCameraReady[_MaxCam];							// �Ψ��x�s�O�_���g�Q��l�ƹL
	int m_iCameraID[_MaxCam];
	CCameraDS m_Camera[_MaxCam];							// �۾��� class ( DirectShow )
	int m_iCameraOpenCount;									// �ثe�}��ĴX��۾�
	bool m_bCameraLive;										// �O�_�b Live
	bool m_MediaControlUse[_MaxCam];

public:
	// Function
	int UpdateCameraList();									// ���o�ثe�w�g���W�� Camera �C��
	void GetCameraList(CArray <CString, CString> &array );	// ���~���i�H���o�C��

	//
	bool Open(int iCameraID);
	int m_iCameraUseID;
	bool CameraInitial(int iUserID,int iCameraID);

public:
	char *m_pCapturImageData[_MaxCam];						// �x�s�۾����

	char *m_CaptureFrame;
	bool CameraGrab(int iUserID);							// ����
	bool CameraGrabSave(int iUserID, CString csFilePath);	// �����ӥB�x�s

public:

	bool SaveImage(char* szPathName, void* lpBits, int w, int h);
	HBITMAP *m_pBitmap;
	HBITMAP* GetBitmap();
	void Draw(HDC hDC,CRect rect,char* pBuffer);
	void DrawWindow(int iUserID,LPVOID hWndShowPage,int iWindowID);
	
	// GDIPlus
	/*
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	Status SaveFile(Bitmap* pImage, const wchar_t* pFileName);
	void ConvertFile(CString csSourceBmp, CString csDestionJpg);

	CString GetStatusValue(Status status);
	void VisionMessage(CString csMsg);
	*/
};

#endif // !defined(AFX_CTRLVISION_H__C18B56E6_E8EB_4B79_A731_17BA8A94EBE5__INCLUDED_)
