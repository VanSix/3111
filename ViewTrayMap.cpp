// ViewTrayMap.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ViewTrayMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTrayMap

IMPLEMENT_DYNCREATE(CViewTrayMap, CView)

CViewTrayMap::CViewTrayMap()
{		
	font.CreatePointFont(60, "Arial");

	// TrayMpa Page
	iTray = -1; // default is -1, if no set TrayID. return it.
	m_iPage = 1;
	m_iPageCount = 0;

	// FT
	m_bBrush = false;
	m_bBinColor = false;

	// SLT
	m_bCustomColor = false;
	iCustomColorSize = 0;
	m_BinCustomBrush[0].CreateSolidBrush( ST_GRAY );

	// Chip Tray
	m_iChip = -1;

	//
	nBkColor = RGB(255, 255, 255);

	//
	m_iRepeatMode = enTrayMapModeNone;
}

CViewTrayMap::~CViewTrayMap()
{
}


BEGIN_MESSAGE_MAP(CViewTrayMap, CView)
	//{{AFX_MSG_MAP(CViewTrayMap)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTrayMap drawing
void CViewTrayMap::SetRepeatTray(int iMode)
{
	// 0 is normal
	// 1 is input/output ctrl

	m_iRepeatMode = iMode;
}
bool CViewTrayMap::SetCustomColor(CString csCode, COLORREF crColor)			
{	
	if( csCode == "" || crColor <= 0 )
		return false;

	m_bCustomColor = true;
	m_BinCode.Add( csCode );
	m_BinColor.Add( crColor );

	iCustomColorSize++;

	return true;
}
void CViewTrayMap::ClearCsutomColor()			
{
	m_bCustomColor = false;
	m_BinCode.RemoveAll();
	m_BinColor.RemoveAll();

	iCustomColorSize = 0;
}
COLORREF CViewTrayMap::GetCustomColor(CString csCode)
{
	// �� Code �h Mapping Color
	COLORREF color = ST_GRAY;;
	
	int iSize = m_BinCode.GetSize();
	int iCodeNumber = -1;
	for(int i=0;i<iSize;i++)
	{
		CString csRefCode = _T("");
		csRefCode = m_BinCode.GetAt(i);

		if( csRefCode == csCode )
			iCodeNumber = i;
	}

	int ibound = 0;
	ibound = m_BinColor.GetUpperBound();
	if( iCodeNumber > ibound )
		; // Gray
	else if ( iCodeNumber == -1 )
		; // Gray // can not find code to mapping color.
	else
		color = m_BinColor.GetAt( iCodeNumber );

	return color;
}
CString CViewTrayMap::GetColorList()							
{
	// ���~���ݤ@�U�Q�s�W���ɮ�
	CString csList = _T("");
	
	int iSize = m_BinCode.GetSize();
	for(int i=0;i<iSize;i++)
	{
		CString csMsg = _T("");		
		csMsg.Format( "Code: %s, Color: %d\r\n", m_BinCode.GetAt(i), m_BinColor.GetAt(i) );
		csList += csMsg;
	}

	return csList;
} 
/////////////////////////////////////////////////////////////////////////////
// Change Page.
void CViewTrayMap::ChangePageUp()
{
	if( m_iPage > m_iPageCount - 1)
		return;

	// ����W�@��
	m_iPage++;
}
void CViewTrayMap::ChangePageDown()
{
	if( m_iPage == 1 )
		return;

	// ����U�@��
	m_iPage--;
}
void CViewTrayMap::ChangePage(int Page)
{
	if( Page < 1 )
		return;

	if( Page > m_iPageCount - 1)
		return;

	// �j����������
	m_iPage = Page;
}
int	CViewTrayMap::GetNowPage()
{
	// �^�Ƿ�U����
	return m_iPage;
}
void CViewTrayMap::ChangePageCount(int count)
{
	// �W�[�ثe����
	m_iPageCount = count;
}
int CViewTrayMap::GetPageCount()	
{
	// �^�Ǥw�g���X��
	return m_iPageCount;
}
/////////////////////////////////////////////////////////////////////////////
void CViewTrayMap::SetChipMode(int Chip)
{
	m_iChip = Chip;
}
void CViewTrayMap::SetTrayID(int ID)
{
	if( ID < 0 )
		iTray = -1;
	else
		iTray = ID;
	// set Tray ID
}
void CViewTrayMap::SetTrayBrush(COLORREF crColor)
{
	m_bBrush = true;
	m_Brush[0].CreateSolidBrush( crColor );
}
void CViewTrayMap::SetBinColor(int bin, COLORREF crColor )
{
	iBinColor[bin] = crColor;
}
void CViewTrayMap::SetTrayBrush( bool bBin, int ID )
{
	// �קK�]�w�����D, �����w�]��
	if( ID == 0 )
		m_Brush[0].CreateSolidBrush( RGB(0, 255, 0) );	
	else if(ID == 1)
		m_Brush[0].CreateSolidBrush( RGB( 255, 0, 0) );	
	else if(ID == 2)
		m_Brush[0].CreateSolidBrush( RGB( 255, 255, 0) );
	else if(ID == 3)
		m_Brush[0].CreateSolidBrush( RGB( 255, 128, 0) );
	else
		m_Brush[0].CreateSolidBrush( RGB(166, 202, 240) );

	m_bBinColor = true;
	for(int i=0;i<_Tray_Bin;i++)
		m_BinBrush[i].CreateSolidBrush( iBinColor[i] );
	// �ѥ~���ɮ׸��J TrayMap.color
}
void CViewTrayMap::SetTrayBrush(int ID)
{
	if( ID == 0 )
		m_Brush[0].CreateSolidBrush( RGB(0, 255, 0) );	
	else if(ID == 1)
		m_Brush[0].CreateSolidBrush( RGB( 255, 0, 0) );	
	else if(ID == 2)
		m_Brush[0].CreateSolidBrush( RGB( 255, 255, 0) );
	else if(ID == 3)
		m_Brush[0].CreateSolidBrush( RGB( 255, 128, 0) );
	else
		m_Brush[0].CreateSolidBrush( RGB(166, 202, 240) );
}

int CViewTrayMap::ChangeBrush(CString Code )
{
	if( m_bBinColor )
	{		
		if( Code == "0" )
			return 0;
		else if( Code == "1" )
			return 1;
		else if( Code == "2" )
			return 2;
		else if( Code == "3" )
			return 3;
		else if( Code == "4" )
			return 4;
		else if( Code == "5" )
			return 5;
		else if( Code == "6" )
			return 6;
		else if( Code == "7" )
			return 7;
		else if( Code == "8" )
			return 8;
		else if( Code == "9" )
			return 9;
		else if( Code == "10" )
			return 10;
		else if( Code == "11" )
			return 11;
		else if( Code == "12" )
			return 12;
		else if( Code == "13" )
			return 13;
		else if( Code == "14" )
			return 14;
		else if( Code == "15" )
			return 15;
		else if( Code == "16" )
			return 16;
		else
			return 0;
	}
	else
		return 0;
}

// 1.0An
// Remove this and re-build new one
/*
void CViewTrayMap::OnDraw(CDC* pDC)
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
	dcMemory.FillRect(rect, &CBrush(RGB(0, 0, 255)));
	dcMemory.FillRect(rect, &CBrush( nBkColor ));

	//
	int	iStackNow = 0;
	int OldPos = 0;

	// If Programer no set tray ID. return it. Do not do anything.
	if( iTray == -1 )
		return;

	// Draw Tray
	int iColumn = -1;
	int iRow = -1;
	if( m_iChip )
	{
		iColumn = m.TraySpec.m_SubTrayColumn * m.TraySpec.m_SubChipTrayColumn;
		iRow = m.TraySpec.m_SubTrayRow * m.TraySpec.m_SubChipTrayRow;
	}
	else
	{
		iColumn = m.TraySpec.Column;
		iRow = m.TraySpec.Row;
	}

	////////////////////////////////////////////////////////////////
	// CView Tray ���]�w��
	double LeftSide		= m.Setting.m_dTraySpecLeftSide;		// ������ CStatic �����Z.
	double TopSide		= m.Setting.m_dTraySpecTopSide;			// �W���� CStatic �����Z.
	int e = iTray;												// �ثe�o�� CView ����ܨ��@�� OutputTrayMap.
	int ICSide			= m.Setting.m_dTraySpecICSide;			// IC �b��l�̭�. ����C��P��ت��Z��.

	int ICTextTopSide	= m.Setting.m_dTraySpecTextUpSide;		// IC ��ܰT��T�� TextOut ���Z��.�L�ե�
	int ICTextLeftSide	= m.Setting.m_dTraySpecTextLeftSide;	// IC ��ܰT��T�� TextOut ���Z��.�L�ե�
	int nBkColor		= m.Setting.m_iTraySpecBkColor;	
	dcMemory.FillRect(rect, &CBrush( nBkColor ));

	// ����r�i�H�Q�ק�
	int ICTextSize = 60 + ( m.Setting.m_iTraySpecTextSize * 10 );
	int ICTextBreak = 8 + m.Setting.m_iTraySpecTextBreak;
	////////////////////////////////////////////////////////////////

	if(iColumn <=0 || iRow <=0) 
		return;

	dcMemory.SelectObject(&font);

	// �ܧ� Text Out �r��j�p.!
	////////////////////////////////////////////////////////////
	CFont front;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));			// clear out structure.
	lf.lfHeight = ICTextSize;                   // request a 12-pixel-height font
	strcpy(lf.lfFaceName, "Arial");	
//	CClientDC dc(this);
	CFont font;
	VERIFY(font.CreatePointFontIndirect(&lf, &dc));	
	dcMemory.SelectObject( &font );
	////////////////////////////////////////////////////////////
	
	// Chip
	// �p�G�O Chip Tray �w�]�����ƥ� 1 �}�l
	if( m_iChip )
		iStackNow = 1;

	double iXPitch = rect.Width()	/ iColumn;
	double iYPitch = rect.Height()	/ iRow;

	CRect rectH;
	dcMemory.SetTextAlign(TA_RIGHT);

	// Output 1
	for(int i=0; i<iColumn; i++)
	{
		for(int j=0; j<iRow; j++)
		{
			rectH.left =	(long)((i)*iXPitch) + LeftSide;
			rectH.right =	(long)(i+1)*iXPitch;
			rectH.top =		(long)(j)*iYPitch	+ TopSide;
			rectH.bottom =	(long)(j+1)*iYPitch;
			dcMemory.Rectangle(&rectH);
			// �e TrayFile ����l
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Draw Output 1 Device
	std::list<tagTrayMap>::iterator p = m.TrayMap[e].begin();
	for(i=0; i<m.TrayMap[e].size(); i++, p++)
	{		
		// TrayMap ����ܧ�
		// TrayMap ���޿��²��, �N�O �y�� y * column > �e�@���� y * column 
		// �N��ܻ��w�gŪ��e�@���� ����
		// ���O Chip Tray ���޿�ݭn�ܧ�
		if( m_iChip )
		{
			// �p�GŪ��̤j����, ��@�O����
			if( p->pos.x * p->pos.y == iColumn * iRow )
				iStackNow++;
		}
		else
		{
			if((p->pos.x + p->pos.y * iColumn) >= OldPos)
				iStackNow++;
		}

		OldPos = p->pos.x + p->pos.y * iColumn;
		if( iStackNow == m_iPage )
		{			
			rectH.left =	(long)((p->pos.x-1)*iXPitch)	+ LeftSide  + ICSide;
			rectH.right =	(long)((p->pos.x)*iXPitch)		- ICSide;
			rectH.top =		(long)((p->pos.y-1)*iYPitch)	+ TopSide	+ ICSide;
			rectH.bottom =	(long)((p->pos.y)*iYPitch)		- ICSide;

			CString csCode = "";
			csCode.Format("%s", p->code );
			
			if( m_bBinColor )
			{
				int iBrush = ChangeBrush( csCode );
				dcMemory.FillRect(&rectH, &m_BinBrush[iBrush]);		// �ۭq���C�� FT 1~16 Bin�@���Ҧ�
			}
			else if( m_bCustomColor )
			{
				COLORREF crcolor = ST_GRAY;
				crcolor = GetCustomColor( csCode );
				m_BinCustomBrush[0].DeleteObject();
				m_BinCustomBrush[0].CreateSolidBrush( crcolor );
				dcMemory.FillRect(&rectH, &m_BinCustomBrush[0]);	// �ۭq���C�� FT 1~16 Bin�@���Ҧ�
			}
			else
				dcMemory.FillRect(&rectH, &m_Brush[0]);				// �w�]���C�� �u��ܤ@���C�⪺�Ҧ�
			
			// Note : �Ъ`�N, �b pos �̭��x�s���O�y���I (x,y). 
			// ���W���O�Ĥ@��, �k��O�ĤG��
			// �Ĥ@���O (1,1). �ĤG���O (2.1) �ĤT���O (3.1) �H������.
			
			if( m.TrayMapSetting.bCode && !m.TrayMapSetting.bTemp )
			{
				CString csSite; // Whitch Information we want to show.
				csSite.Format("(%s)", p->code);
				if( csSite.GetLength() > ICTextBreak )
				{
					int s = ((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide;
					// �ĤG���b�������U 0.1 �� YPitch ���a��
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s - (0.5*s), 
						csSite.Left(8) );
					// �Ĥ@���b�������W 0.2 �� YPitch ���a��
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s + (0.2*s), 
						csSite.Right(csSite.GetLength()-8) );	
				}
				else
				{
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.8) + LeftSide + ICSide ) + ICTextLeftSide, 
						((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide, 
						csSite );
					// Note : �ڭ̧�r����ܦb��l���񤤶���m���U �M ���k ��ӶZ��.
					// ������m�� x ��0.8�Z��. y�� 0.1�Z��
				}
			}
			// Display Code.
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////
						
			if(  m.TrayMapSetting.bTemp && !m.TrayMapSetting.bCode)
			{
				CString csSite; // Whitch Information we want to show.
				csSite.Format("%.1f", p->temperature);
				if( csSite.GetLength() > ICTextBreak )
				{
					int s = ((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide;
					// �ĤG���b�������U 0.1 �� YPitch ���a��
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s - (0.5*s), 
						csSite.Left(8) );
					// �Ĥ@���b�������W 0.2 �� YPitch ���a��
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s + (0.2*s), 
						csSite.Right(csSite.GetLength()-8) );	
				}
				else
				{
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.4) + LeftSide + ICSide ) + ICTextLeftSide, 
						((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide, 
						csSite );
					// Note : �ڭ̧�r����ܦb��l���񤤶���m���U �M ���k ��ӶZ��.
					// ������m�� x ��0.8�Z��. y�� 0.1�Z��
				}
			}
			// Display Temp.
			
			if(  m.TrayMapSetting.bTemp && m.TrayMapSetting.bCode)
			{
				CString csSite; // Whitch Information we want to show.
				csSite.Format("%s(%.1f)", p->code, p->temperature);
				if( csSite.GetLength() > ICTextBreak )
				{
					int s = ((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide;
					// �ĤG���b�������U 0.1 �� YPitch ���a��
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.8) + LeftSide + ICSide ) + ICTextLeftSide, 
						s - (0.5*s), 
						csSite.Left(8) );
					// �Ĥ@���b�������W 0.2 �� YPitch ���a��
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.8) + LeftSide + ICSide ) + ICTextLeftSide, 
						s + (0.2*s), 
						csSite.Right(csSite.GetLength()-8) );	
				}
				else
				{
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.4) + LeftSide + ICSide ) + ICTextLeftSide, 
						((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide, 
						csSite );
					// Note : �ڭ̧�r����ܦb��l���񤤶���m���U �M ���k ��ӶZ��.
					// ������m�� x ��0.8�Z��. y�� 0.1�Z��
				}
			}
			// Display Temp and Code.
		}
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemory, 0, 0, SRCCOPY);
	ReleaseDC(&dcMemory);
}
*/
void CViewTrayMap::OnDraw(CDC* pDC)
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
	dcMemory.FillRect(rect, &CBrush(RGB(0, 0, 255)));
	dcMemory.FillRect(rect, &CBrush( nBkColor ));

	//
	int	iStackNow = 0;
	int OldPos = 0;

	// If Programer no set tray ID. return it. Do not do anything.
	if( iTray == -1 )
		return;

	// Draw Tray
	int iColumn = -1;
	int iRow = -1;
	if( m_iChip )
	{
		iColumn = m.TraySpec.m_SubTrayColumn * m.TraySpec.m_SubChipTrayColumn;
		iRow = m.TraySpec.m_SubTrayRow * m.TraySpec.m_SubChipTrayRow;
	}
	else
	{
		iColumn = m.TraySpec.Column;
		iRow = m.TraySpec.Row;
	}

	////////////////////////////////////////////////////////////////
	// CView Tray ���]�w��
	double LeftSide		= m.Setting.m_dTraySpecLeftSide;		// ������ CStatic �����Z.
	double TopSide		= m.Setting.m_dTraySpecTopSide;			// �W���� CStatic �����Z.
	int e = iTray;												// �ثe�o�� CView ����ܨ��@�� OutputTrayMap.
	int ICSide			= m.Setting.m_dTraySpecICSide;			// IC �b��l�̭�. ����C��P��ت��Z��.

	int ICTextTopSide	= m.Setting.m_dTraySpecTextUpSide;		// IC ��ܰT��T�� TextOut ���Z��.�L�ե�
	int ICTextLeftSide	= m.Setting.m_dTraySpecTextLeftSide;	// IC ��ܰT��T�� TextOut ���Z��.�L�ե�
	int nBkColor		= m.Setting.m_iTraySpecBkColor;	
	dcMemory.FillRect(rect, &CBrush( nBkColor ));

	// ����r�i�H�Q�ק�
	int ICTextSize = 60 + ( m.Setting.m_iTraySpecTextSize * 10 );
	int ICTextBreak = 8 + m.Setting.m_iTraySpecTextBreak;
	////////////////////////////////////////////////////////////////

	if(iColumn <=0 || iRow <=0) 
		return;

	dcMemory.SelectObject(&font);

	// �ܧ� Text Out �r��j�p.!
	////////////////////////////////////////////////////////////
	CFont front;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));			// clear out structure.
	lf.lfHeight = ICTextSize;                   // request a 12-pixel-height font
	strcpy(lf.lfFaceName, "Arial");	
//	CClientDC dc(this);
	CFont font;
	VERIFY(font.CreatePointFontIndirect(&lf, &dc));	
	dcMemory.SelectObject( &font );
	////////////////////////////////////////////////////////////
	
	// Chip
	// �p�G�O Chip Tray �w�]�����ƥ� 1 �}�l
	if( m_iChip )
		iStackNow = 1;

	double iXPitch = rect.Width()	/ iColumn;
	double iYPitch = rect.Height()	/ iRow;

	CRect rectH;
	dcMemory.SetTextAlign(TA_RIGHT);

	// Output 1
	for(int i=0; i<iColumn; i++)
	{
		for(int j=0; j<iRow; j++)
		{
			rectH.left =	(long)((i)*iXPitch) + LeftSide;
			rectH.right =	(long)(i+1)*iXPitch;
			rectH.top =		(long)(j)*iYPitch	+ TopSide;
			rectH.bottom =	(long)(j+1)*iYPitch;
			dcMemory.Rectangle(&rectH);
			// �e TrayFile ����l
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Draw Output 1 Device
	int iTrayMapSize = 0;
	std::list<tagTrayMap>::iterator p;
	if( m_iRepeatMode == enTrayMapModeNone )
	{
		p = m.TrayMap[e].begin();
		iTrayMapSize = m.TrayMap[e].size();
	}
	else if( m_iRepeatMode == enTrayMapModeInOutCtrl )
	{
		p = m.TrayMapRepeat[e].begin();
		iTrayMapSize = m.TrayMapRepeat[e].size();	
	}
	else
	{
		p = m.TrayMap[e].begin();
		iTrayMapSize = m.TrayMap[e].size();	
	}
	
	//
	for(i=0; i<iTrayMapSize; i++, p++)
	{		
		// TrayMap ����ܧ�
		// TrayMap ���޿��²��, �N�O �y�� y * column > �e�@���� y * column 
		// �N��ܻ��w�gŪ��e�@���� ����
		// ���O Chip Tray ���޿�ݭn�ܧ�
		if( m_iChip )
		{
			// �p�GŪ��̤j����, ��@�O����
			if( p->pos.x * p->pos.y == iColumn * iRow )
			{
				iStackNow++;
				m_iPageCount = iStackNow;
			}
		}
		else
		{
			if((p->pos.x + p->pos.y * iColumn) >= OldPos)
			{
				iStackNow++;
				m_iPageCount = iStackNow;
			}
		}

		OldPos = p->pos.x + p->pos.y * iColumn;
		if( iStackNow == m_iPage )
		{			
			rectH.left =	(long)((p->pos.x-1)*iXPitch)	+ LeftSide  + ICSide;
			rectH.right =	(long)((p->pos.x)*iXPitch)		- ICSide;
			rectH.top =		(long)((p->pos.y-1)*iYPitch)	+ TopSide	+ ICSide;
			rectH.bottom =	(long)((p->pos.y)*iYPitch)		- ICSide;

			CString csCode = "";
			csCode.Format("%s", p->code );
			
			if( m_bBinColor )
			{
				int iBrush = ChangeBrush( csCode );
				dcMemory.FillRect(&rectH, &m_BinBrush[iBrush]);		// �ۭq���C�� FT 1~16 Bin�@���Ҧ�
			}
			else if( m_bCustomColor )
			{
				COLORREF crcolor = ST_GRAY;
				crcolor = GetCustomColor( csCode );
				m_BinCustomBrush[0].DeleteObject();
				m_BinCustomBrush[0].CreateSolidBrush( crcolor );
				dcMemory.FillRect(&rectH, &m_BinCustomBrush[0]);	// �ۭq���C�� FT 1~16 Bin�@���Ҧ�
			}
			else
				dcMemory.FillRect(&rectH, &m_Brush[0]);				// �w�]���C�� �u��ܤ@���C�⪺�Ҧ�
			
			// Note : �Ъ`�N, �b pos �̭��x�s���O�y���I (x,y). 
			// ���W���O�Ĥ@��, �k��O�ĤG��
			// �Ĥ@���O (1,1). �ĤG���O (2.1) �ĤT���O (3.1) �H������.
			
			if( m.TrayMapSetting.bCode && !m.TrayMapSetting.bTemp )
			{
				CString csSite; // Whitch Information we want to show.
				csSite.Format("(%s)", p->code);
				if( csSite.GetLength() > ICTextBreak )
				{
					int s = ((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide;
					// �ĤG���b�������U 0.1 �� YPitch ���a��
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s - (0.5*s), 
						csSite.Left(8) );
					// �Ĥ@���b�������W 0.2 �� YPitch ���a��
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s + (0.2*s), 
						csSite.Right(csSite.GetLength()-8) );	
				}
				else
				{
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.8) + LeftSide + ICSide ) + ICTextLeftSide, 
						((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide, 
						csSite );
					// Note : �ڭ̧�r����ܦb��l���񤤶���m���U �M ���k ��ӶZ��.
					// ������m�� x ��0.8�Z��. y�� 0.1�Z��
				}
			}
			// Display Code.
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////
						
			if(  m.TrayMapSetting.bTemp && !m.TrayMapSetting.bCode)
			{
				CString csSite; // Whitch Information we want to show.
				csSite.Format("%.1f", p->temperature);
				if( csSite.GetLength() > ICTextBreak )
				{
					int s = ((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide;
					// �ĤG���b�������U 0.1 �� YPitch ���a��
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s - (0.5*s), 
						csSite.Left(8) );
					// �Ĥ@���b�������W 0.2 �� YPitch ���a��
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s + (0.2*s), 
						csSite.Right(csSite.GetLength()-8) );	
				}
				else
				{
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.4) + LeftSide + ICSide ) + ICTextLeftSide, 
						((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide, 
						csSite );
					// Note : �ڭ̧�r����ܦb��l���񤤶���m���U �M ���k ��ӶZ��.
					// ������m�� x ��0.8�Z��. y�� 0.1�Z��
				}
			}
			// Display Temp.
			
			if(  m.TrayMapSetting.bTemp && m.TrayMapSetting.bCode)
			{
				CString csSite; // Whitch Information we want to show.
				csSite.Format("%s(%.1f)", p->code, p->temperature);
				if( csSite.GetLength() > ICTextBreak )
				{
					int s = ((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide;
					// �ĤG���b�������U 0.1 �� YPitch ���a��
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.8) + LeftSide + ICSide ) + ICTextLeftSide, 
						s - (0.5*s), 
						csSite.Left(8) );
					// �Ĥ@���b�������W 0.2 �� YPitch ���a��
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.8) + LeftSide + ICSide ) + ICTextLeftSide, 
						s + (0.2*s), 
						csSite.Right(csSite.GetLength()-8) );	
				}
				else
				{
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.4) + LeftSide + ICSide ) + ICTextLeftSide, 
						((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide, 
						csSite );
					// Note : �ڭ̧�r����ܦb��l���񤤶���m���U �M ���k ��ӶZ��.
					// ������m�� x ��0.8�Z��. y�� 0.1�Z��
				}
			}
			// Display Temp and Code.
		}
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemory, 0, 0, SRCCOPY);
	ReleaseDC(&dcMemory);
}
void CViewTrayMap::SaveAsBmp(CString filename)   
{
	CRect clientRC;   
	this->GetClientRect(clientRC);   
	int iWidth = clientRC.Width();   
	int iHeight = clientRC.Height();   
	int iPixel = 32;   

	BITMAPINFO *lpbmih = new BITMAPINFO;   
	lpbmih->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);   
	lpbmih->bmiHeader.biWidth = iWidth;   
	lpbmih->bmiHeader.biHeight = iHeight;   
	lpbmih->bmiHeader.biPlanes = 1;   
	lpbmih->bmiHeader.biBitCount = iPixel;   
	lpbmih->bmiHeader.biCompression = BI_RGB;   
	lpbmih->bmiHeader.biSizeImage = 0;   
	lpbmih->bmiHeader.biXPelsPerMeter = 0;   
	lpbmih->bmiHeader.biYPelsPerMeter = 0;   
	lpbmih->bmiHeader.biClrUsed = 0;   
	lpbmih->bmiHeader.biClrImportant = 0;   

	HDC hdc,hdcMem;   
	HBITMAP hBitMap = NULL;   
	CBitmap *pBitMap = NULL;   
	CDC *pMemDC = NULL;   
	BYTE *pBits;   
	
	hdc = CreateIC(TEXT("DISPLAY"),NULL,NULL,NULL);   
	hdcMem = CreateCompatibleDC(hdc);   
	hBitMap = CreateDIBSection(hdcMem,lpbmih,DIB_PAL_COLORS,(void **)&pBits,NULL,0);   
	pBitMap = new CBitmap;   
	pBitMap->Attach(hBitMap);   
	pMemDC = new CDC;   
	pMemDC->Attach(hdcMem);   
	pMemDC->SelectObject(pBitMap);   
	//   
	CRect rc(0,0,iWidth,iHeight);   
	pMemDC->SetBkMode(TRANSPARENT);   

	OnDraw(pMemDC);   

	BITMAPFILEHEADER bmfh;   
	ZeroMemory(&bmfh,sizeof(BITMAPFILEHEADER));   
	*((char *)&bmfh.bfType) = 'B';   
	*(((char *)&bmfh.bfType) + 1) = 'M';   
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);   
	bmfh.bfSize = bmfh.bfOffBits + (iWidth * iHeight) * iPixel / 8;   
	
	TCHAR szBMPFileName[128];   
	int iBMPBytes = iWidth * iHeight * iPixel / 8;   
	strcpy(szBMPFileName,filename);   
	CFile file;   
	if(file.Open(szBMPFileName,CFile::modeWrite | CFile::modeCreate))   
	{   
		file.Write(&bmfh,sizeof(BITMAPFILEHEADER));   
		file.Write(&(lpbmih->bmiHeader),sizeof(BITMAPINFOHEADER));   
		file.Write(pBits,iBMPBytes);   
		file.Close();   
	}   
	
	pMemDC->DeleteDC();   
	delete pMemDC; pMemDC = NULL;   
	delete pBitMap; pBitMap = NULL;   
	delete lpbmih; lpbmih = NULL;   
}

void CViewTrayMap::ResetPage()
{
	// ���]���� (�]���R���F.)
	m_iPage = 0;						// ��U����, �Ĥ@���O 0. �ĤG�� 1,2,3,.....
	m_iPageCount = 0;					// �ثe�w�g���X��
}

/*
void CViewTrayMap::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CView::OnPaint() for painting messages
}
*/
void CViewTrayMap::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDocument* pDoc = GetDocument();

	CString cs;
	cs.Format("x = %d, y = %d", point.x, point.y );

	CView::OnLButtonDown(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////
// CViewTrayMap diagnostics

#ifdef _DEBUG
void CViewTrayMap::AssertValid() const
{
	CView::AssertValid();
}

void CViewTrayMap::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewTrayMap message handlers
