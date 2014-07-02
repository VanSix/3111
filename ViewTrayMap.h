#if !defined(AFX_VIEWTRAYMAP_H__6BAE8EC5_A451_4501_9241_504BCF9D5527__INCLUDED_)
#define AFX_VIEWTRAYMAP_H__6BAE8EC5_A451_4501_9241_504BCF9D5527__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewTrayMap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewTrayMap view

class CViewTrayMap : public CView
{
public:
	CViewTrayMap();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewTrayMap)

	virtual ~CViewTrayMap();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:

// Attributes
public:
	CBrush	m_Brush[1];

	CFont font;

	// FT
	void SetTrayID( int ID);						// �]�w�ثe�o�Ӫ���O�����@�� Output ��
	void SetTrayBrush( int ID);						// �w�]���P�����󦳤��P�� Brush, �ҥH�]�w ID ������i�H�M�w�n�έ��@�� Brush

	bool m_bBrush;									// �O�_�ѥ~���]�w�L�C��
	COLORREF m_crColor;								// �~�����C��
	void SetTrayBrush(COLORREF crColor);			// ���~���h�]�w�C�� (�@�� Output �@�Ӧۭq���C��, 3160 �����k)

	void SetTrayBrush( bool bBin, int ID );			// �]�w �Y�@�� ID�O�_�n�ѥ~�����J�ɮ�
	bool m_bBinColor;								// OnDraw �O�_�� FT���Ҧ�
	COLORREF nBkColor;
	CBrush	m_BinBrush[_Tray_Bin];					// �~���ɮץΪ� Brush FT 1~16 Bin Using..
	int ChangeBrush(CString Code);					// �� Bin Code �ӨM�w�C��	
	void SetBinColor(int bin, COLORREF crColor );	// �]�w�C�@�� Bin�@���C��
	COLORREF iBinColor[_Tray_Bin];					// �x�s�C��

	// SLT
	bool m_bCustomColor;							// �O�_���o�ӼҦ�
	bool SetCustomColor(CString csCode, COLORREF crColor);			// �~�����J Catoregy Color
	void ClearCsutomColor();						// �M���ɮ�
	COLORREF GetCustomColor(CString csCode);		// �� Code �h Mapping Color
	CArray<CString, CString> m_BinCode;
	CArray<long, long> m_BinColor;
	CBrush	m_BinCustomBrush[1];
	CString GetColorList();							// ���~���ݤ@�UŪ�i�Ӫ��ɮ�
	int iCustomColorSize;
 
	// Page
	int iTray; // ���@�� TrayMap �n���.

	int m_iTrayNo[4];

	int m_iPage;						// ��U����, �Ĥ@���O 0. �ĤG�� 1,2,3,.....
	int m_iPageCount;					// �ثe�w�g���X��
	void ChangePageUp();				// ����W�@��
	void ChangePageDown();				// ����U�@��
	void ChangePage(int Page);			// �j����������
	void ChangePageCount(int count);	// �W�[�ثe����
	int	 GetNowPage();					// �^�Ƿ�U����
	int	 GetPageCount();				// �^�Ǥw�g���X��

	void ResetPage();					// ���]���� (�]���R���F.)

	void SaveAsBmp(CString filename);

	// �]�w�� Chip Tray Mode 
	void SetChipMode(int Chip);	// 0 is not chip / 1 is chip tray
	int	 m_iChip;

	// �]�w�O�_�� Repeat Tray
	enum TrayMapMode {
		enTrayMapModeNone		= 0, // None
		enTrayMapModeInOutCtrl	= 1, // Input / Output Ctrl
	};
	int m_iRepeatMode;
	void SetRepeatTray(int iMode);	// 0 is normal, 1 is input/output ctrl



// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewTrayMap)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewTrayMap)
//	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWTRAYMAP_H__6BAE8EC5_A451_4501_9241_504BCF9D5527__INCLUDED_)
