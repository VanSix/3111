#if !defined(AFX_VIEWTRAYMOTOR_H__6BA11849_5C96_4A43_A179_115DE8D1FE47__INCLUDED_)
#define AFX_VIEWTRAYMOTOR_H__6BA11849_5C96_4A43_A179_115DE8D1FE47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewTrayMotor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewTrayMotor view

#include "TrayFile.h"

class CViewTrayMotor : public CView
{

public:
	enum Status 
	{
		enEOF		= -1,	// 
		enEmpty		= 0,	// �Ӧ�m�O�ť�.
		enBooking	= 1,	// ���b�g�J���.
		enUnBook	= 2,	// �� IC ���O�S������.
		enMoving	= 3,	// ���b���ʤ�.
		enOK		= 4,	// 

		// For Pick 
		enSoakDone		= 5,	// ��� Soak Time OK. �i�H����
		enSoakBooking	= 6,	// ���b�g�J���.		
		enSoakMoving	= 7,	// ���b���ʤ�.
		enSoakOK		= 8,	// ��� Soak Time OK. �ӥB�Q�������\
		enWaitSoak		= 9,	// ��ܳQ���w�L�ɶ�.���� Soak Time
	};	

protected:


// Attributes
public:
	CViewTrayMotor();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewTrayMotor)

	virtual ~CViewTrayMotor();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void SetType(int Type);
	int m_iType;
	CBrush	m_Brush[11];	// 
	
	// 
	void SetChipMode(int Chip);	// 0 is not chip / 1 is chip tray
	int	 m_iChip;

	// 
	void LockPick();
	void UnLockPick();
	int  Lock;	// 1 = Lock , 0 = Unlock
	
	// 
	void ShowValue();
	int	 Show;	// 1 = Show, 0 = No Show

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewTrayMotor)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
protected:
	//{{AFX_MSG(CViewTrayMotor)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWTRAYMOTOR_H__6BA11849_5C96_4A43_A179_115DE8D1FE47__INCLUDED_)
