// SocketVision.h: interface for the CSocketVision class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETVISION_H__382B1AAF_D173_4875_94A1_0EBBA9254063__INCLUDED_)
#define AFX_SOCKETVISION_H__382B1AAF_D173_4875_94A1_0EBBA9254063__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//
#include "CameraDS.h"

//
#include "Easy.h"
#include "EMatch.h"
#include "EImage.h"

// �۾��̤j�ƶq
#define _MaxCam			10	// �]�j�@�I, �קK�Q�H���J�Ӧh Cam, �y�����..
#define _CAMERA_WIDTH	640
#define _CAMERA_HEIGHT	480

class CSocketVision  
{
public:
	CSocketVision();
	virtual ~CSocketVision();

	//
	struct tagMatch{
		double Score;
		bool GrabOK;
		EImageC24 PatternImageColor;
		EROIC24 PatternROIColor;
		bool bLearn;
		EROIC24 SourceROI;
		CRect rect;
		double MinScore;
		bool Pass;
		CString MatchResult;
		CString File;
		bool IsGrabOK;
	} m_Match[_MaxCam];

	// Caram List
	CArray <CString, CString> m_CaramList;					// �x�s�۾��C�� Array
	bool m_bIsCameraReady[_MaxCam];							// �Ψ��x�s�O�_���g�Q��l�ƹL
	int m_iCameraID[_MaxCam];
	CCameraDS m_Camera[_MaxCam];							// �۾��� class ( DirectShow )
	int m_iCameraOpenCount;									// �ثe�}��ĴX��۾�
	bool m_bCameraLive;										// �O�_�b Live
	bool m_MediaControlUse[_MaxCam];

	char *m_pCapturImageData[_MaxCam];						// �x�s�۾����

	// File Path
	CString m_csPatternPath;								// �]�w�ɮ׸��|
	CString m_csInfoPath;
	void SetPath(CString PatternPath, CString csInfoPath );

	// Function
	int UpdateCameraList();									// ���o�ثe�w�g���W�� Camera �C��
	void GetCameraList(CArray <CString, CString> &array );	// ���~���i�H���o�C��
	int m_iCameraUseID;
	bool CameraInitial(int iUserID,int iCameraID);			// ��w���l��
	bool Open(int iCameraID);
	
	//
	char *m_CaptureFrame;
	char* GatImagePtr(int iID,char * pImageData);
	bool CameraGrab(int iUserID);
	void DrawWindow(int iUserID,LPVOID hWndShowPage,int iWindowID);

	//IplImage m_CaptureFrame;
	EImageC24 SourceImage[_MaxCam];

	// ���o�v��..
	EImageC24 GetGrabImage(int iUserID);

	//
	EROIC24 SourceROI;

	//
	double GrabMatch(int site);
	void MatchCheck(tagMatch *pMatch,EImageC24 *pSourceImage);

	//
	EMatch MatchObj;

	//
	void SetMatchPattern(int iUser,CString FilePath, CRect rect, double MinScore);

	//
	bool GetMatchGrabOK(int iUserID);
};

#endif // !defined(AFX_SOCKETVISION_H__382B1AAF_D173_4875_94A1_0EBBA9254063__INCLUDED_)
