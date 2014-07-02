// CtrlVisionMatch.h: interface for the CCtrlVisionMatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTRLVISIONMATCH_H__AA5BC3E1_FA5D_403E_B219_BCCDFC2C980C__INCLUDED_)
#define AFX_CTRLVISIONMATCH_H__AA5BC3E1_FA5D_403E_B219_BCCDFC2C980C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CtrlVisionAlignment.h"

class CCtrlVisionMatch  
{
public:
	CCtrlVisionMatch();
	virtual ~CCtrlVisionMatch();

public:
	CCtrlVisionAlignment	m_VisionCtrl;

public:
	// Debug
	void Message(CString csMsg = _T("") );

	// Info
	long lPatternHx;
	long lPatternWx;
	//
	CRect RectROI;
	bool SetPattern(CString csPattern);												// ���J��諸�ѷ���
	bool SetSubPattern(CString csPattern, CRect ROI);								// ���J��諸�ѷ���, �N�ѷ��ɦs���p��
	bool SetSubInspect(CString csInspect, CRect ROI,
		CString csSourceName, CString csSubName);									// ���J�������ɮ�, �N�����ɦs���p��
	bool SetTraining();																// �إߤ��ҫ�
	bool SetMatch(double &dMatchResult);											// ���
	double MatchCheck(int iUserID, CString csPatternPath, CString csGrabPath,
		CString csSourceName, CString csSubName, CRect rect /*ROI*/ );				// ���
};

#endif // !defined(AFX_CTRLVISIONMATCH_H__AA5BC3E1_FA5D_403E_B219_BCCDFC2C980C__INCLUDED_)
