#if !defined(AFX_COLORSTATIC_H__7E091024_5607_11D4_93E4_0080C8F8DDD9__INCLUDED_)
#define AFX_COLORSTATIC_H__7E091024_5607_11D4_93E4_0080C8F8DDD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorStatic.h : header file
//


//***********************************************//
// CColorFontStatic
//
//		Version:	1.7
//		Author:	Maxwell Chen
//		Date:		Jan. 07, 2002
//***********************************************//


/////////////////////////////////////////////////////////////////////
// MACRO
// #include "Define.h"
/////////////////////////////////////////////////////////////////////////////
// CColorFontStatic window

class CColorFontStatic : public CStatic
{
// Construction
public:
	CColorFontStatic();

protected:
	// Current colors
	COLORREF	m_clrText;
	COLORREF	m_clrBack;
	CBrush		m_brBack;
	// Initial color
	COLORREF	m_clrInitText;
	COLORREF	m_clrInitBack;
	COLORREF	m_clrInitFocus;

	int		m_FontSize;
	CString	m_FontFace;
	CFont	m_Font;
	unsigned int	m_Format;

	CString	m_Text;

	bool		m_bComplementColor;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorFontStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetWindowText(LPCTSTR lpszString );
	void SetComplementMode(bool bCmpMode = true)	{
		m_bComplementColor = bCmpMode;
	}

	// ����r ���e, �j�p, �r��, �ι���榡.
	void SetText(const CString& text, int size,
		const CString& face = "Times New Roman",
		unsigned int format = DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	// ����r.
	void CColorFontStatic::SetNewText(const CString &text);

	// ���ثe���C��, �M�ƥ�(���٭�)���C��. ������I�s�@��.
	// �]�ˤU�C InitTextColor() �M InitBkColor().
	void Initial(COLORREF clrText, COLORREF clrBackground,
		COLORREF clrFocus);
	void InitTextColor(COLORREF clrInit);
	void InitBkColor(COLORREF clrInit);

	// ���ثe���I���C�� (�Ȯɩ�).
	void SetNewBkColor(COLORREF clrBack);

	// ���ثe����r�C�� (�Ȯɩ�).
	void SetNewTextColor(COLORREF clrText);
	virtual ~CColorFontStatic();

	COLORREF	GetTextColor() { return m_clrText; }
	COLORREF GetBkColor() { return m_clrBack; }

	// Generated message map functions
protected:
	COLORREF _GetComplementColor(COLORREF& color);
	//{{AFX_MSG(CColorFontStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	COLORREF _GetInitBkColor();
	COLORREF _GetInitTextColor();
	void _SetInitBkColorValue();
	void _SetInitTextColorValue();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSTATIC_H__7E091024_5607_11D4_93E4_0080C8F8DDD9__INCLUDED_)
