#if !defined(AFX_VIEWREPEATTRAYMOTOR_H__3025BE2F_7B38_416C_93BC_164EFEB6F412__INCLUDED_)
#define AFX_VIEWREPEATTRAYMOTOR_H__3025BE2F_7B38_416C_93BC_164EFEB6F412__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewRepeatTrayMotor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewRepeatTrayMotor view

class CViewRepeatTrayMotor : public CView
{
public:	

	CViewRepeatTrayMotor();           // protected constructor used by dynamic creation
	virtual ~CViewRepeatTrayMotor();


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


	bool m_iChip;
	int m_iType;
	void SetType(int type);
	CBrush	m_Brush[11];

protected:
	DECLARE_DYNCREATE(CViewRepeatTrayMotor)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewRepeatTrayMotor)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewRepeatTrayMotor)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWREPEATTRAYMOTOR_H__3025BE2F_7B38_416C_93BC_164EFEB6F412__INCLUDED_)
