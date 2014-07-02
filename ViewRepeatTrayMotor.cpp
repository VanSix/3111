// ViewRepeatTrayMotor.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ViewRepeatTrayMotor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewRepeatTrayMotor

IMPLEMENT_DYNCREATE(CViewRepeatTrayMotor, CView)

CViewRepeatTrayMotor::CViewRepeatTrayMotor()
{
	m_iChip = false;
	m_iType = -1;

	m_Brush[0].CreateSolidBrush( RGB(0, 255, 0) );			// Green / Moving.	
	m_Brush[1].CreateSolidBrush( RGB( 255, 0, 0) );			// Red / Booking.	
	m_Brush[2].CreateSolidBrush( RGB( 255, 255, 0) );		// Yellow / OK.	
	m_Brush[3].CreateSolidBrush( RGB( 255, 255, 255) );		// Spec test
	m_Brush[4].CreateSolidBrush( RGB(0, 0, 128) );			// PreHeater
	m_Brush[5].CreateSolidBrush( RGB(128, 128, 128) );		// Dark Blue PreHeater Soak Done
	m_Brush[6].CreateSolidBrush( RGB(192, 0, 0) );			// Gray PreHeater Booking
	m_Brush[7].CreateSolidBrush( RGB(255, 255, 128) );		// Brow PreHeater Moving	// Light Yellow PreHeater OK
	m_Brush[8].CreateSolidBrush( RGB(64, 0, 64) );			// Disable PreHeater Wait Soak	
	m_Brush[9].CreateSolidBrush( RGB(0, 255, 0) );
	m_Brush[10].CreateSolidBrush( RGB(119, 255, 119) );
}

CViewRepeatTrayMotor::~CViewRepeatTrayMotor()
{
}


BEGIN_MESSAGE_MAP(CViewRepeatTrayMotor, CView)
	//{{AFX_MSG_MAP(CViewRepeatTrayMotor)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewRepeatTrayMotor drawing

void CViewRepeatTrayMotor::SetType(int type)
{
	m_iType = type;
}
void CViewRepeatTrayMotor::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here

	CBitmap bmp;
	CDC		dcMemory;

	CRect rect;
	GetClientRect(rect);
	// Complete wrong. It will get dialog rect

	CClientDC dc(this);
	dcMemory.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	dcMemory.SelectObject(&bmp);


	// Draw Tray
	int iColumn = -1;
	int	iRow = -1;
	int iSize = -1;
	if( m_iChip == 1 )
	{
		// Chip Tray
		// �� Sub Tray �ӭp�⦳�h�� IC
		iColumn = m.TraySpec.m_SubTrayColumn * m.TraySpec.m_SubChipTrayColumn;
		iRow = m.TraySpec.m_SubTrayRow * m.TraySpec.m_SubChipTrayRow;
		iSize = iColumn * iRow;
	}
	else
	{
		iColumn = m.TraySpec.Column;
		iRow = m.TraySpec.Row;	
		iSize = m.TraySpec.Column * m.TraySpec.Row;	
		// Tray
	}

	////////////////////////////////////////////////////////////////
	// CView Tray ���]�w��
	long	LeftSide =	m.Setting.m_dTraySpecLeftSide;		// ������ CStatic �����Z.
	long	TopSide =	m.Setting.m_dTraySpecTopSide;		// �W���� CStatic �����Z.
	int		ICSide =	m.Setting.m_dTraySpecICSide;		// IC �b��l�̭�. ����C��P��ت��Z��.
	
	////////////////////////////////////////////////////////////////
	if(iColumn <=0 || iRow <=0) 
		return;

	long iXPitch = rect.Width()  / iColumn;
	long iYPitch = rect.Height() / iRow;
	// Tray 

	CRect rectH;
	GetWindowRect(rectH);

	// Chip Tray
	CRect	rectHChipTray;
	GetWindowRect(rectHChipTray);


	/////////////////////////////////////////////////
	// Tray 1 Status
	if( m_iType == 0 )
	{
		if( m_iChip == 1 )
		{
			// ���̤j�����e
			long right =	(long)(iColumn)*iXPitch;
			long bottom =	(long)(iRow)*iYPitch;	

			int iSubColumn  = -1;
			int iSubRow		= -1;
			iSubColumn = m.TraySpec.m_SubTrayColumn;
			iSubRow	   = m.TraySpec.m_SubTrayRow;
			CPen penChip;
			penChip.CreatePen(PS_SOLID, 1, RGB( 255, 153, 0   ) );	
			// �]�w Chip Tray �~�ت��C��
			CPen* pOldPen = dcMemory.SelectObject(&penChip);
			double iXPitch = /*rectHChipTray.Width()*/right		/	iSubColumn;
			double iYPitch = /*rectHChipTray.Height()*/bottom	/	iSubRow;

			for(int i=0; i<iSubColumn; i++)
			{
				for(int j=0; j<iSubRow; j++)
				{
					rectHChipTray.left		= (long)((i)*iXPitch);
					rectHChipTray.right		= (long)(i+1)*iXPitch;
					rectHChipTray.top		= (long)(j)*iYPitch;
					rectHChipTray.bottom	= (long)(j+1)*iYPitch;
					dcMemory.Rectangle(&rectHChipTray);
					// �e Chip Tray Map ����l
				}
			}
			dcMemory.SelectObject(pOldPen);
			// �e��. �_�� CPen �]�w�C��(�¦�)
		}

		for(int i=0; i<iColumn; i++)
		{
			for(int j=0; j<iRow; j++)
			{
				rectH.left =	(long)((i)*(iXPitch)) + LeftSide;
				rectH.right =	(long)(i+1)*iXPitch;
				rectH.top =		(long)((j)*(iYPitch)) + TopSide;
				rectH.bottom =	(long)(j+1)*iYPitch;				
				dcMemory.Rectangle(&rectH);
				// �e Motor Map ����l
			}
		}
		
		// Draw Output Device
		for(i=0; i<iSize;i++)
		{	
			CPoint p;
			
			int m_iColL = i % iColumn;		
			int m_iRowL = i / iColumn;		
	
			p.x = m_iColL + 1;
			p.y = m_iRowL + 1;
		
			// Col = 8 Row = 15
			// x �O �� Col �l��
			// y �O ��	
						
			rectH.left =	(int)((p.x-1)*iXPitch) + LeftSide	+ ICSide;
			rectH.right =	(int)((p.x)*iXPitch)	- ICSide;
			rectH.top =		(int)((p.y-1)*iYPitch) + TopSide		+ ICSide;
			rectH.bottom =	(int)((p.y)*iYPitch)	- ICSide;
			// Draw 
			
			if(  theApp.m_Tray1.TrayiNoGetStatus(i) == enMoving )
				dcMemory.FillRect(&rectH, &m_Brush[0]);		
			else if ( theApp.m_Tray1.TrayiNoGetStatus(i) == enBooking )
				dcMemory.FillRect(&rectH, &m_Brush[1]);
			else if ( theApp.m_Tray1.TrayiNoGetStatus(i) == enOK )
			{
				if( theApp.m_Tray1.TrayiNoGetStatusAuto(i) == enOK )
					dcMemory.FillRect(&rectH, &m_Brush[10]);	// �o�O AutoSkip ����m, ��ܨS�� IC
				else
					dcMemory.FillRect(&rectH, &m_Brush[9]);		// 
			}
			else if ( theApp.m_Tray1.TrayiNoGetStatus(i) == enEmpty )
				dcMemory.FillRect(&rectH, &m_Brush[3]);		
			else
				;
			// Color.!
			
			// Note : �Ъ`�N, �b pos �̭��x�s���O�y���I (x,y). 
			// ���W���O�Ĥ@��, �k��O�ĤG��
			// �Ĥ@���O (1,1). �ĤG���O (2.1) �ĤT���O (3.1) �H������.
		}
	}


	/////////////////////////////////////////////////
	// Tray 2 Status
	if( m_iType == 1 )
	{
		if( m_iChip == 1 )
		{
			// ���̤j�����e
			long right =	(long)(iColumn)*iXPitch;
			long bottom =	(long)(iRow)*iYPitch;	

			int iSubColumn  = -1;
			int iSubRow		= -1;
			iSubColumn = m.TraySpec.m_SubTrayColumn;
			iSubRow	   = m.TraySpec.m_SubTrayRow;
			CPen penChip;
			penChip.CreatePen(PS_SOLID, 1, RGB( 255, 153, 0   ) );	
			// �]�w Chip Tray �~�ت��C��
			CPen* pOldPen = dcMemory.SelectObject(&penChip);
			double iXPitch = /*rectHChipTray.Width()*/right		/	iSubColumn;
			double iYPitch = /*rectHChipTray.Height()*/bottom	/	iSubRow;

			for(int i=0; i<iSubColumn; i++)
			{
				for(int j=0; j<iSubRow; j++)
				{
					rectHChipTray.left		= (long)((i)*iXPitch);
					rectHChipTray.right		= (long)(i+1)*iXPitch;
					rectHChipTray.top		= (long)(j)*iYPitch;
					rectHChipTray.bottom	= (long)(j+1)*iYPitch;
					dcMemory.Rectangle(&rectHChipTray);
					// �e Chip Tray Map ����l
				}
			}
			dcMemory.SelectObject(pOldPen);
			// �e��. �_�� CPen �]�w�C��(�¦�)
		}

		for(int i=0; i<iColumn; i++)
		{
			for(int j=0; j<iRow; j++)
			{
				rectH.left =	(long)((i)*(iXPitch)) + LeftSide;
				rectH.right =	(long)(i+1)*iXPitch;
				rectH.top =		(long)((j)*(iYPitch)) + TopSide;
				rectH.bottom =	(long)(j+1)*iYPitch;				
				dcMemory.Rectangle(&rectH);
				// �e Motor Map ����l
			}
		}
		
		// Draw Output Device
		for(i=0; i<iSize;i++)
		{	
			CPoint p;
			
			int m_iColL = i % iColumn;		
			int m_iRowL = i / iColumn;		
	
			p.x = m_iColL + 1;
			p.y = m_iRowL + 1;
		
			// Col = 8 Row = 15
			// x �O �� Col �l��
			// y �O ��	
						
			rectH.left =	(int)((p.x-1)*iXPitch) + LeftSide	+ ICSide;
			rectH.right =	(int)((p.x)*iXPitch)	- ICSide;
			rectH.top =		(int)((p.y-1)*iYPitch) + TopSide		+ ICSide;
			rectH.bottom =	(int)((p.y)*iYPitch)	- ICSide;
			// Draw 
			
			if(  theApp.m_Tray2.TrayiNoGetStatus(i) == enMoving )
				dcMemory.FillRect(&rectH, &m_Brush[0]);		
			else if ( theApp.m_Tray2.TrayiNoGetStatus(i) == enBooking )
				dcMemory.FillRect(&rectH, &m_Brush[1]);
			else if ( theApp.m_Tray2.TrayiNoGetStatus(i) == enOK )
			{
				if( theApp.m_Tray2.TrayiNoGetStatusAuto(i) == enOK )
					dcMemory.FillRect(&rectH, &m_Brush[10]);	// �o�O AutoSkip ����m, ��ܨS�� IC
				else
					dcMemory.FillRect(&rectH, &m_Brush[9]);		// 
			}
			else if ( theApp.m_Tray2.TrayiNoGetStatus(i) == enEmpty )
				dcMemory.FillRect(&rectH, &m_Brush[3]);		
			else
				;
			// Color.!
			
			// Note : �Ъ`�N, �b pos �̭��x�s���O�y���I (x,y). 
			// ���W���O�Ĥ@��, �k��O�ĤG��
			// �Ĥ@���O (1,1). �ĤG���O (2.1) �ĤT���O (3.1) �H������.
		}
	}


	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemory, 0, 0, SRCCOPY);
	ReleaseDC(&dcMemory);
}

/////////////////////////////////////////////////////////////////////////////
// CViewRepeatTrayMotor diagnostics

#ifdef _DEBUG
void CViewRepeatTrayMotor::AssertValid() const
{
	CView::AssertValid();
}

void CViewRepeatTrayMotor::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewRepeatTrayMotor message handlers
