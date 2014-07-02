// ViewTrayMotor.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "ViewTrayMotor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTrayMotor

IMPLEMENT_DYNCREATE(CViewTrayMotor, CView)

CViewTrayMotor::CViewTrayMotor()
{
	m_iType = -1;
	m_Brush[0].CreateSolidBrush( RGB(0, 255, 0) );
	// Green / Moving.
	m_Brush[1].CreateSolidBrush( RGB( 255, 0, 0) );	
	// Red / Booking.
	m_Brush[2].CreateSolidBrush( RGB( 255, 255, 0) );
	// Yellow / OK.
	m_Brush[3].CreateSolidBrush( RGB( 255, 255, 255) );
	// Spec test

	// PreHeater
	m_Brush[4].CreateSolidBrush( RGB(0, 0, 128) );
	// Dark Blue PreHeater Soak Done
	m_Brush[5].CreateSolidBrush( RGB(128, 128, 128) );
	// Gray PreHeater Booking
	m_Brush[6].CreateSolidBrush( RGB(192, 0, 0) );
	// Brow PreHeater Moving
	m_Brush[7].CreateSolidBrush( RGB(255, 255, 128) );
	// Light Yellow PreHeater OK

	m_Brush[8].CreateSolidBrush( RGB(64, 0, 64) );
	// Disable PreHeater Wait Soak

	m_Brush[9].CreateSolidBrush( RGB(0, 255, 0) );
	m_Brush[10].CreateSolidBrush( RGB(119, 255, 119) );

	//
	m_iChip = -1;

	// 
	Lock = -1;	

	//
	Show = -1;
}

CViewTrayMotor::~CViewTrayMotor()
{

}

BEGIN_MESSAGE_MAP(CViewTrayMotor, CView)
	//{{AFX_MSG_MAP(CViewTrayMotor)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTrayMotor drawing

void CViewTrayMotor::SetChipMode(int Chip)
{
	m_iChip = Chip;
}
void CViewTrayMotor::SetType(int Type)
{
	m_iType = Type;
	// Note : -1 .	It is no setting. 
	// Note : 0 .	It is Input
	// Note : 1 .	It is Output 1

}

void CViewTrayMotor::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();

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

	int iPreHeaterColumn =	m.TraySpec.PlateColumn;
	int iPreHeaterRow =		m.TraySpec.PlateRow;
	int iPreHeaterSize =	m.TraySpec.PlateColumn * m.TraySpec.PlateRow;
	// PreHeater

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

	long iPreHeaterXPitch = rect.Width()		/ iPreHeaterColumn;
	long iPreHeaterYPitch = rect.Height()		/ iPreHeaterRow;
	// PreHeater

	CRect rectH;
	GetWindowRect(rectH);

	// Chip Tray
	CRect	rectHChipTray;
	GetWindowRect(rectHChipTray);

	/////////////////////////////////////////////////
	// Input Tray Status. 
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
			
			if(  theApp.m_InputTray.TrayiNoGetStatus(i) == enMoving )
				dcMemory.FillRect(&rectH, &m_Brush[0]);		
			else if ( theApp.m_InputTray.TrayiNoGetStatus(i) == enBooking )
				dcMemory.FillRect(&rectH, &m_Brush[1]);
			else if ( theApp.m_InputTray.TrayiNoGetStatus(i) == enOK )
			{
				if( theApp.m_InputTray.TrayiNoGetStatusAuto(i) == enOK )
					dcMemory.FillRect(&rectH, &m_Brush[10]);	// �o�O AutoSkip ����m, ��ܨS�� IC
				else
					dcMemory.FillRect(&rectH, &m_Brush[9]);		// 
			}
			else if ( theApp.m_InputTray.TrayiNoGetStatus(i) == enEmpty )
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
	// Output Tray Status. 
	if( m_iType == 1 )
	{
		for(int i=0; i<iColumn; i++)
		{
			for(int j=0; j<iRow; j++)
			{
				rectH.left =	(long)((i)*iXPitch) + LeftSide;
				rectH.right =	(long)(i+1)*iXPitch;
				rectH.top =		(long)(j)*iYPitch	+ TopSide;
				rectH.bottom =	(long)(j+1)*iYPitch;
				dcMemory.Rectangle(&rectH);
				// �e Motor Map ����l
			}
		}
		
		// Draw Output Device
		for(i=0; i<iSize;i++)
		{	
			CPoint p;
			
			int m_iColL = i % iColumn;		// C
			int m_iRowL = i / iColumn;		// D
			
			p.x = m_iColL + 1;
			p.y = m_iRowL + 1;
						
			rectH.left =	(long)((p.x-1)*iXPitch) + LeftSide	+ ICSide;
			rectH.right =	(long)((p.x)*iXPitch)	- ICSide;
			rectH.top =		(long)((p.y-1)*iYPitch) + TopSide	+ ICSide;
			rectH.bottom =	(long)((p.y)*iYPitch)	- ICSide;
			// Draw 
			
			if( theApp.m_OutputTray.TrayiNoGetStatus(i) == enMoving )
				dcMemory.FillRect(&rectH, &m_Brush[0]);
			else if( theApp.m_OutputTray.TrayiNoGetStatus(i) == enBooking )
				dcMemory.FillRect(&rectH, &m_Brush[1]);
			else if( theApp.m_OutputTray.TrayiNoGetStatus(i) == enOK )
				dcMemory.FillRect(&rectH, &m_Brush[2]);
			else if( theApp.m_OutputTray.TrayiNoGetStatus(i) == enEmpty )
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
	// PreHeater Tray Status.  
	if( m_iType == 5 )
	{
		for(int i=0; i<iPreHeaterColumn; i++)
		{
			for(int j=0; j<iPreHeaterRow; j++)
			{
				rectH.left =	(long)((i)*iPreHeaterXPitch)	+ LeftSide;
				rectH.right =	(long)(i+1)*iPreHeaterXPitch;
				rectH.top =		(long)(j)*iPreHeaterYPitch		+ TopSide;
				rectH.bottom =	(long)(j+1)*iPreHeaterYPitch;
				dcMemory.Rectangle(&rectH);
				// �e Motor Map ����l
			}
		}
	
		int iNext = theApp.m_PreHeaterTray.GetiNext();
		int iCount = theApp.m_PreHeaterTray.GetiCount();

		bool bOK = false;
		int start = -1;
		int end	  = -1;
		int check = -1;
		if( iNext - iCount < 0 )
		{
			bOK = true;		// �W�L�d�� �S�q�Ĥ@�C�}�l��
			end = iCount - iNext;
			check = iPreHeaterSize - end - 1;
		}
		else 
		{
			bOK = false;	// �S���W�L�d��
			start = iNext - iCount + 1;
		}
		
		for(i=0; i<iPreHeaterSize;i++)
		{
			if(!bOK)
			{
				int c = i+1;
				if( c <= iNext && c > start )
				{
					// �u���b�Ĥ@�C. �S����d��
					CPoint p;
					int m_iColL = i % iPreHeaterColumn;		// Calc How many
					int m_iRowL = i / iPreHeaterColumn;
					p.x = m_iColL + 1;
					p.y = m_iRowL + 1;	
					rectH.left =	(long)((p.x-1)*iPreHeaterXPitch)	+ LeftSide	+ ICSide;
					rectH.right =	(long)((p.x)*iPreHeaterXPitch)		- ICSide;
					rectH.top =		(long)((p.y-1)*iPreHeaterYPitch)	+ TopSide	+ ICSide;
					rectH.bottom =	(long)((p.y)*iPreHeaterYPitch)		- ICSide;
					dcMemory.FillRect(&rectH, &m_Brush[5]);
				}
			}
			else
			{
				int c = i+1;
				if( c <= iNext )
				{
					CPoint p;
					int m_iColL = i % iPreHeaterColumn;		// Calc How many
					int m_iRowL = i / iPreHeaterColumn;
					p.x = m_iColL + 1;
					p.y = m_iRowL + 1;	
					rectH.left =	(long)((p.x-1)*iPreHeaterXPitch)	+ LeftSide	+ ICSide;
					rectH.right =	(long)((p.x)*iPreHeaterXPitch)		- ICSide;
					rectH.top =		(long)((p.y-1)*iPreHeaterYPitch)	+ TopSide	+ ICSide;
					rectH.bottom =	(long)((p.y)*iPreHeaterYPitch)		- ICSide;
					dcMemory.FillRect(&rectH, &m_Brush[5]);
				}
				if( check < c )
				{
					CPoint p;
					int m_iColL = i % iPreHeaterColumn;		// Calc How many
					int m_iRowL = i / iPreHeaterColumn;
					p.x = m_iColL + 1;
					p.y = m_iRowL + 1;	
					rectH.left =	(long)((p.x-1)*iPreHeaterXPitch)	+ LeftSide	+ ICSide;
					rectH.right =	(long)((p.x)*iPreHeaterXPitch)		- ICSide;
					rectH.top =		(long)((p.y-1)*iPreHeaterYPitch)	+ TopSide	+ ICSide;
					rectH.bottom =	(long)((p.y)*iPreHeaterYPitch)		- ICSide;
					dcMemory.FillRect(&rectH, &m_Brush[5]);
				}				 
			}
		}			
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	// Alignment Using. 
	// �o�̬O Pick / Place  ��ܦ�m�s�����Ѽ�
	if( m_iType == 91 )
	{
		if( m_iChip == 1 )
		{
			// ���̤j�����e
			long right =	(long)(iColumn)*iXPitch;
			long bottom =	(long)(iRow)*iYPitch;	
			// 

			int iSubColumn  = -1;
			int iSubRow		= -1;
			iSubColumn = m.TraySpec.m_SubTrayColumn;
			iSubRow	   = m.TraySpec.m_SubTrayRow;
			CPen penChip;
			penChip.CreatePen(PS_SOLID, 5, RGB( 255, 153, 0   ) );	
			// �]�w Chip Tray �~�ت��C��
			CPen* pOldPen = dcMemory.SelectObject(&penChip);
			double iXPitch = /*rectHChipTray.Width()*/	right /	 iSubColumn;
			double iYPitch = /*rectHChipTray.Height()*/	bottom / iSubRow;

			for(int i=0; i<iSubColumn; i++)
			{
				for(int j=0; j<iSubRow; j++)
				{
					rectHChipTray.left =	(long)((i)*iXPitch);
					rectHChipTray.right =	(long)(i+1)*iXPitch;
					rectHChipTray.top =		(long)(j)*iYPitch;
					rectHChipTray.bottom =	(long)(j+1)*iYPitch;
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
				rectH.left = (long)((i)*iXPitch);
				rectH.right = (long)(i+1)*iXPitch;
				rectH.top = (long)(j)*iYPitch;
				rectH.bottom = (long)(j+1)*iYPitch;
				dcMemory.SelectStockObject(NULL_BRUSH); // �خحI���z��
				dcMemory.Rectangle(&rectH);
				// �e Motor Map ����l
			}
		}

		// Draw Position
		for(i=0; i<iSize;i++)
		{
			CPoint p;			
			int m_iColL = i % iColumn;		// Calc How many
			int m_iRowL = i / iColumn;
			
			p.x = m_iColL + 1;
			p.y = m_iRowL + 1;
			
			rectH.left =	(long)((p.x-1)*iXPitch);
			rectH.right =	(long)((p.x)*iXPitch);
			rectH.top =		(long)((p.y-1)*iYPitch);
			rectH.bottom =	(long)((p.y)*iYPitch);
			// Draw 

			if( m.m_ArmBook == i )
				dcMemory.FillRect(&rectH, &m_Brush[0]);

			CString cs;
			cs.Format("%d", i);
			if( Show == 1)
			{
				dcMemory.TextOut( 
					((long)((p.x-1)*iXPitch) + (iXPitch*0.2) + LeftSide + ICSide ), 
					((long)((p.y-1)*iYPitch) + (iYPitch*0.02) + TopSide + ICSide ), 
					cs );
			}
		}
	}
//
	if( m_iType == 90 )
	{			
		for(int i=0; i<iPreHeaterColumn; i++)
		{
			for(int j=0; j<iPreHeaterRow; j++)
			{
				rectH.left =	(long)((i)*iPreHeaterXPitch);
				rectH.right =	(long)(i+1)*iPreHeaterXPitch;

				rectH.top =		(long)(j)*iPreHeaterYPitch;
				rectH.bottom =	(long)(j+1)*iPreHeaterYPitch;
				dcMemory.Rectangle(&rectH);
				// �e Motor Map ����l
			}
		}

		// Draw Position
		for(i=0; i<iPreHeaterSize;i++)
		{
			CPoint p;			
			int m_iColL = i % iPreHeaterColumn;		// Calc How many
			int m_iRowL = i / iPreHeaterColumn;
			
			p.x = m_iColL + 1;
			p.y = m_iRowL + 1;
			
			rectH.left =	(long)((p.x-1)*iPreHeaterXPitch);
			rectH.right =	(long)((p.x)*iPreHeaterXPitch);			
			rectH.top =		(long)((p.y-1)*iPreHeaterYPitch);
			rectH.bottom =	(long)((p.y)*iPreHeaterYPitch);
			// Draw 

			if( m.m_ArmBook == i )
				dcMemory.FillRect(&rectH, &m_Brush[0]);

			CString cs;
			cs.Format("%d", i);
			dcMemory.TextOut( 
				((long)((p.x-1)*iPreHeaterXPitch) + (iPreHeaterXPitch*0.2) + LeftSide + ICSide ), 
				((long)((p.y-1)*iPreHeaterYPitch) + (iPreHeaterYPitch*0.02) + TopSide + ICSide ), 
				cs );
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	if( m_iType == 89 )
	{

		int iSubColumn  = -1;
		int iSubRow		= -1;
		iSubColumn = m.TraySpec.m_SubTrayColumn;
		iSubRow	   = m.TraySpec.m_SubTrayRow;
		CPen penChip;
		penChip.CreatePen(PS_SOLID, 5, RGB( 255, 153, 0   ) );	
		// �]�w Chip Tray �~�ت��C��
		CPen* pOldPen = dcMemory.SelectObject(&penChip);
		double iXPitch = rectHChipTray.Width()	/ iSubColumn;
		double iYPitch = rectHChipTray.Height() / iSubRow;

		for(int i=0; i<iSubColumn; i++)
		{
			for(int j=0; j<iSubRow; j++)
			{
				rectHChipTray.left =	(long)((i)*iXPitch)	+ LeftSide;
				rectHChipTray.right =	(long)(i+1)*iXPitch;
				rectHChipTray.top =		(long)(j)*iYPitch	+ TopSide;
				rectHChipTray.bottom =	(long)(j+1)*iYPitch;
				dcMemory.Rectangle(&rectHChipTray);
				// �e Chip Tray Map ����l
			}
		}
		dcMemory.SelectObject(pOldPen);
		// �e��. �_�� CPen �]�w�C��(�¦�)

		// Draw Position
		int iSubColumnc	= m.TraySpec.m_SubTrayColumn;
		int iSubRowc	= m.TraySpec.m_SubTrayRow;
		int m_iChipTraySize = iSubColumnc * iSubRowc;
		for(i=0; i<m_iChipTraySize;i++)
		{
			CPoint p;			
			int m_iColL = i % iSubColumnc;		// Calc How many
			int m_iRowL = i / iSubColumnc;
			
			p.x = m_iColL + 1;
			p.y = m_iRowL + 1;
			
			rectHChipTray.left =	(long)((p.x-1)*iXPitch);
			rectHChipTray.right =	(long)((p.x)*iXPitch);
			rectHChipTray.top =		(long)((p.y-1)*iYPitch);
			rectHChipTray.bottom =	(long)((p.y)*iYPitch);
			// Draw 

			if( m.m_ArmChipTrayBook == i )
				dcMemory.FillRect(&rectHChipTray, &m_Brush[0]);
		}
	}

/////////////////////////////////////////////////

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemory, 0, 0, SRCCOPY);
	ReleaseDC(&dcMemory);
}

/////////////////////////////////////////////////////////////////////////////
// CViewTrayMotor diagnostics

#ifdef _DEBUG
void CViewTrayMotor::AssertValid() const
{
	CView::AssertValid();
}

void CViewTrayMotor::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewTrayMotor message handlers
void CViewTrayMotor::ShowValue()
{
	Show = 1;
}
void CViewTrayMotor::LockPick()
{
	// Lock the Tray Position
	Lock = 1;
}
void CViewTrayMotor::UnLockPick()
{
	// Unlock the Tray Position
	Lock = 0; 
}
void CViewTrayMotor::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDocument* pDoc = GetDocument();

	if( Lock )
	{
		// 
		// Lock the Tray Psoition
		return;
	}
	else if( Lock == -1 )
	{
		AfxMessageBox("oh, No setting Lock value.!");
	}

	m.m_ArmPosition.x = point.x;
	m.m_ArmPosition.y = point.y;
	
	if( m_iType == 91 )	// �@�몺 Tray
	{
		int iC = 0;
		int iD = 0;

		int iColumn = -1;
		int iRow	= -1;

		int iSubColumn = -1;
		int iSubRow	   = -1;

		// Chip Tray Remote Control
		if( m_iChip )
		{
			iColumn = m.TraySpec.m_SubChipTrayColumn * m.TraySpec.m_SubTrayColumn;
			iRow	= m.TraySpec.m_SubChipTrayRow 	 * m.TraySpec.m_SubTrayRow;
		}
		else
		{
			iColumn = m.TraySpec.Column;
			iRow = m.TraySpec.Row;
		}

		CRect rectH;
		GetWindowRect(rectH);
		double iXPitch = rectH.Width() / iColumn;
		double iYPitch = rectH.Height() / iRow;
		// �]�w���
		
		// check dut position
		// �ˬd�o�O���@��DUT��m
		for(int i=0; i<iColumn; i++)
		{
			for(int j=0; j<iRow; j++)
			{
				rectH.left = (long)((i)*iXPitch);	// �� x > Left
				rectH.right = (long)(i+1)*iXPitch;	// �� x < Right
				// Note : �j�� Left �p�� Right. �h��ܳo�O�I�쪺�d��		
				if( m.m_ArmPosition.x > rectH.left && m.m_ArmPosition.x < rectH.right )
					iC = i;
				// Note : �p�G���N��C���Ʀr�O�_��
				
				rectH.top = (long)(j)*iYPitch;
				rectH.bottom = (long)(j+1)*iYPitch;
				// Note : �j�� top �p�� botton. �h��ܳo�O�I�쪺�d��
				if( m.m_ArmPosition.y > rectH.top && m.m_ArmPosition.y < rectH.bottom )
					iD = j;
				// Note : �p�G���N��D���Ʀr�O�_��			
			}
		}		
		m.m_ArmBook = ( iColumn * iD ) + ( iC );

		this->Invalidate();
	}
	
	if( m_iType == 90 )	// PreHeater Plate
	{
		int iPreC = 0;
		int iPreD = 0;
		
		int iPreColumn = m.TraySpec.PlateColumn;
		int iPreRow = m.TraySpec.PlateRow;
		CRect rectH;
		GetWindowRect(rectH);
		double iXPitch = rectH.Width() / iPreColumn;
		double iYPitch = rectH.Height() / iPreRow;
		// �]�w���

		// check dut position
		// �ˬd�o�O���@��DUT��m
		for(int i=0; i<iPreColumn; i++)
		{
			for(int j=0; j<iPreRow; j++)
			{
				rectH.left = (long)((i)*iXPitch);	// �� x > Left
				rectH.right = (long)(i+1)*iXPitch;	// �� x < Right
				// Note : �j�� Left �p�� Right. �h��ܳo�O�I�쪺�d��		
				if( m.m_ArmPosition.x > rectH.left && m.m_ArmPosition.x < rectH.right )
					iPreC = i;
				// Note : �p�G���N��C���Ʀr�O�_��
				
				rectH.top = (long)(j)*iYPitch;
				rectH.bottom = (long)(j+1)*iYPitch;
				// Note : �j�� top �p�� botton. �h��ܳo�O�I�쪺�d��
				if( m.m_ArmPosition.y > rectH.top && m.m_ArmPosition.y < rectH.bottom )
					iPreD = j;
				// Note : �p�G���N��D���Ʀr�O�_��			
			}
		}		
		m.m_ArmBook = ( iPreColumn * iPreD ) + ( iPreC );

		this->Invalidate();
	}	

	if( m_iType == 89 )	// Chip Tray
	{
		int ixSubColumn = m.TraySpec.m_SubTrayColumn;
		int ixSubRow	   = m.TraySpec.m_SubTrayRow;
		int iSubC = 0;
		int iSubD = 0;

		CRect rectH;
		GetWindowRect(rectH);
		double iXPitch = rectH.Width()	/ ixSubColumn;
		double iYPitch = rectH.Height() / ixSubRow;

		// check dut position
		// �ˬd�o�O���@��DUT��m
		for(int i=0; i<ixSubColumn; i++)
		{
			for(int j=0; j<ixSubRow; j++)
			{
				rectH.left = (long)((i)*iXPitch);	// �� x > Left
				rectH.right = (long)(i+1)*iXPitch;	// �� x < Right
				// Note : �j�� Left �p�� Right. �h��ܳo�O�I�쪺�d��		
				if( m.m_ArmPosition.x > rectH.left && m.m_ArmPosition.x < rectH.right )
					iSubC = i;
				// Note : �p�G���N��C���Ʀr�O�_��
				
				rectH.top = (long)(j)*iYPitch;
				rectH.bottom = (long)(j+1)*iYPitch;
				// Note : �j�� top �p�� botton. �h��ܳo�O�I�쪺�d��
				if( m.m_ArmPosition.y > rectH.top && m.m_ArmPosition.y < rectH.bottom )
					iSubD = j;
				// Note : �p�G���N��D���Ʀr�O�_��			
			}
		}		
		m.m_ArmChipTrayBook = ( ixSubColumn * iSubD ) + ( iSubC );

		this->Invalidate();
	}

	
	CView::OnLButtonDown(nFlags, point);
}

void CViewTrayMotor::OnLButtonUp(UINT nFlags, CPoint point) 
{
	
	CView::OnLButtonUp(nFlags, point);
}
