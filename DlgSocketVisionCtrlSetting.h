#if !defined(AFX_DLGSOCKETVISIONCTRLSETTING_H__804ADD05_FFA3_49EA_916A_69CA1E19CB26__INCLUDED_)
#define AFX_DLGSOCKETVISIONCTRLSETTING_H__804ADD05_FFA3_49EA_916A_69CA1E19CB26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSocketVisionCtrlSetting.h : header file
//

#include "CtrlVisionAlignment.h"
#include "CtrlVisionMatch.h"
//
#include "ViewSockImage.h"
#include "ViewSockTrackerImage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketVisionCtrlSetting dialog

class CDlgSocketVisionCtrlSetting : public CDialog
{
// Construction
public:
	// Image
	CViewSockTrackerImage	*pViewMainImage;
	CViewSockImage			*pViewGrabImage;
	CViewSockImage			*pViewPatternImage;
	
	CCtrlVisionAlignment	m_VisionUse; // image 
	//
	CCtrlVisionMatch		m_VisionMatch;

	void InitImage();
	void InitLib();

public:
	CDlgSocketVisionCtrlSetting(CWnd* pParent = NULL);   // standard constructor

public:
	void InitValue();
	void InitResult();

	CToolTipCtrl m_ToolTip;
	void InitTips();

public:
	void GetInitValue();
	//
	// Show Window
	double m_WindowWidth;
	double m_WindowHeight;
	CRect m_RectMainWindow;

	// Sub Grab Window
	double m_SubWindowWidth;
	double m_SubWindowHeight;
	CRect m_SubRectMainWindow;

	// Sub Pattern Window
	double m_PatternWindowWidth;
	double m_PatternWindowHeight;
	CRect m_PatternRectMainWindow;	

///////////////////////////////////////////////////
	//
	// File Folder
	CArray <CString, CString > m_FileDictory;

	
	void GetSettingFolder();							// �����ثe���ؿ�
	void UpdataSettingList();							// ��s�ɮת����			
	// 
	void SelectDefault(CString csFileFolder);			// �]�w�w�]���ɮ�
	void SelectDefaultPos(int iPos);					// �]�w�w�]���ɮ�(�ھڦ�m)

	//
	void LoadSettingImage(CString csFileFolder);		// ���J����
	void LoadSettingInfo(CString csFileFolder);			// ���J�]�w�Ѽ�
	void SaveSettingInfo(CString csFileFolder);			// �x�s���
	void CopyGrabImage(CString csFileFolder);			// �ƻs�̫�@��������ɮר�]�w�ɸ�Ƨ�
	void ReplaceFolder(CString csFileFolder);			// �����]�w�ɪ��ѼƩM����
	void CreateNewFolder(CString csFileFolder);			// �إ߷s����Ƨ�, �åB��̫�@��������ɮ׶K��s����Ƨ�
	void ReplaceFolderSave(CString csFileFolder);		// �����]�w�ɪ��Ѽ�
	void UpdataSettingSelect(CString NewName);			// �ھڳ]�w�ɦW, ��ܤU�Կ��
	bool IsSettingFileEmpty();							// �T�{������ɮ�
	bool IsSettingFileLastOne();						// �T�{�O�_�O�̫�@���ɮ�
	bool IsSettingFileExist(CString csFileName);		// �T�{�o�ӳ]�w��, �O�_�w�g�s�b
	void DeleteOldFolder( CString csFileFolder);		// �R���o�ӳ]�w��, �R���Ϥ�, �R���Ѽ���
	
	CString GetSettingFileName();						// ���^�ثe����Ƨ��W�� (���ެO�諸�٬O��J�� )
	CRect GetPatternInfo();								// ���o�ɮת���T ( Info.txt )
	
	//
	double GetSettingScore(CString csFileFolder);		// ���^�ثe�]�w�ɪ��Ѽ�
	void MatchResult(double dResult, double dScore);	// ��ܤ�ﵲ�G

	//
	void ReDrawMainImage(CString csFileFolder);			// ���e�ثe���D�e��
	void ReDrawPatternImage(CString csFileFolder);		// ���e�ثe��Pattern�e��
	void ReDrawGrabImage();								// ���e�ثe��Grab�e�� ( Grab.bmp )

	//
	void ReDrawCamGrabImage();							// ������, ��s�e��
	void ReDrawCamGrabPatternImahe();					// ������, ��sPattern

	//
	void UpdataPatternInfo();							// ����CView��ROI��m�ç�s�e���ƾ�

	//
	void CaptureLockUI(bool bEnable);					// ��������q�e��
	void CameraCapture();								// ����

	//
	typedef struct tagInfoParameter {	
		int iX;			// Left
		int iY;			// Top
		int iWidth;		// Right
		int iHeight;	// Bottom
		double dScore;
	} tagInfoParameter;
///////////////////////////////////////////////////
	// 
	void Message(CString csMsg = _T("") );
///////////////////////////////////////////////////
	// 
	void ChangeFileFolder();							// ����ɮ�
	void ChangeFileFolderOther();
	void FunctionCreate();
	void FunctionDelete();
	void FunctionSave();
	void FunctionTest();

// Dialog Data
	//{{AFX_DATA(CDlgSocketVisionCtrlSetting)
	enum { IDD = IDD_DLG_SOCKETVISION_CTL_SETTING };
	CStatic	m_wndGrabImage;
	CStatic	m_wndPatternImage;
	CStatic	m_wndImage;
	CColorFontStatic	m_wndTestScore;
	int		m_iMatchROIX;
	int		m_iMatchROIY;
	int		m_iMatchWidth;
	int		m_iMatchHeight;
	double	m_dMatchMinScore;	
	CEdit	m_wndInfoROIY;
	CEdit	m_wndInfoROIX;
	CEdit	m_wndInfoWidth;
	CEdit	m_wndInfoHeight;
	CComboBox	m_listFileFolder;
	CButtonST	m_btnPatternTest;
	CButtonST	m_btnCapture;
	CButtonST	m_btnPatternSave;
	CButtonST	m_btnClassDelete;
	CButtonST	m_btnClassCreate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSocketVisionCtrlSetting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgSocketVisionCtrlSetting)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSocketvisionCapture();
	afx_msg void OnSocketvisionCreate();
	afx_msg void OnSocketvisionDelete();
	afx_msg void OnSocketvisionSave();
	afx_msg void OnSocketvisionTest();
	afx_msg void OnSelchangeSocketvisionClass();
	afx_msg LRESULT OnPosInfo(WPARAM p, LPARAM l);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSOCKETVISIONCTRLSETTING_H__804ADD05_FFA3_49EA_916A_69CA1E19CB26__INCLUDED_)
