// TrayFile.cpp: implementation of the CTrayFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrayFile.h"

#include "Deer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrayFile::CTrayFile()
{
	m_Row = 0;		// Tray data �� Row ��
	m_Col = 0;		// Tray data �� Col ��
	m_TraySize = 0; // Tray data Row * Col,�@��Tra��IC�ƶq

	m_iNext = -1;
	m_iNow = -1;

	m_MeA = 0;
	m_MeB = 0;

	m_Coordinate = "";

	m_Chip = -1;
}

CTrayFile::~CTrayFile()
{
	if( m_TrayStatus != NULL )
	{
		delete m_TrayStatus;
		m_TrayStatus = NULL;
	}

	// Check Auto Skip
	if( m_TrayStatusAutoSkip != NULL )
	{
		delete m_TrayStatusAutoSkip;
		m_TrayStatusAutoSkip;
	}
	// Convert Booking
	if( m_ChipTrayArray != NULL )
	{
		delete m_ChipTrayArray;
		m_ChipTrayArray = NULL;
	}

	if( m_ChipTrayArrayStatus != NULL )
	{
		delete m_ChipTrayArrayStatus;
		m_ChipTrayArrayStatus = NULL;
	}
}
// Chip Tray
void CTrayFile::SetChipMode(int Chip)		
{
	m_Chip = Chip;
}
CPoint CTrayFile::GetIndex()		
{
	// ����y��, �� Tray Map �ɮץ�
	int iNo = m_iNow;

	// Chip Tray
	if( m_Chip )
	{
		iNo = GetChipTrayPosition( m_iNow );
	}
	
	CPoint p;
	int m_iRowL = -1; // �� y ����
	int m_iColL = -1; // �� x ����		

	m_iColL = iNo % m_TraySpec.Column;		// For C
	m_iRowL = iNo / m_TraySpec.Column;		// For D

	p.x = m_iColL + 1;
	p.y = m_iRowL + 1;

	// Debug
	CString d;
	d.Format("Tray Map %dD . %dC", m_iRowL, m_iColL );
	f.CWinMessage( d, theApp.enDArm );

	return p;
}
CPoint CTrayFile::GetIndex(int iNo)		
{
	// ����y��, �� Tray Map �ɮץ�
	
	CPoint p;
	int m_iRowL = -1; // �� y ����
	int m_iColL = -1; // �� x ����		

	m_iColL = iNo % m_TraySpec.Column;		// For C
	m_iRowL = iNo / m_TraySpec.Column;		// For D

	p.x = m_iColL + 1;
	p.y = m_iRowL + 1;

	// Debug
	CString d;
	d.Format("Tray Map %dD . %dC", m_iRowL, m_iColL );
	f.CWinMessage( d, theApp.enDArm );

	return p;
}

CPoint CTrayFile::GetCoordinateLocation(int iNo)		
{
	// ����y��
	// �o�̬O�� Location In / Location Out �\��ϥ�
	// ���O�ڭ̻ݭn�Ҽ{ Chip Tray �� feature 
	// �ҥH�ڭ̪����� GetCoordinateCustomRemote ���{��, ���O���F�קK�V�c, ���� Function
	CPoint p;
	
	if( m_Chip )
	{
		int m_iSubRowL = -1;	// �� y ���� For D
		int m_iSubColL = -1;	// �� x ���� For C

		int m_iChipRowL = -1;	// �� y ���� For D
		int m_iChipColL = -1;	// �� x ���� For C
		//

		int SubTrayColumn	= m_TraySpec.m_SubTrayColumn; 
		int ChipTrayColumn	= m_TraySpec.m_SubChipTrayColumn;
		int TotalValue = SubTrayColumn * ChipTrayColumn;

		int TotalForD = -1;
		int TotalForC = -1;

		TotalForD = iNo / TotalValue;	// ����
		TotalForC = iNo % TotalValue;	// ���l��

		m_iSubRowL	= TotalForD / ChipTrayColumn;	// ���o Sub D	���ܤ�
		m_iChipRowL = TotalForD % ChipTrayColumn;	// ���o Chip D	���ܤ�

		m_iSubColL	= TotalForC / ChipTrayColumn;	// ���o Sub C	���ܤ�
		m_iChipColL	= TotalForC % ChipTrayColumn;	// ���o Chip C	���ܤ�

		p.x = m_Align.x + 
			(( m_TraySpec.m_SubTrayA * m_Gear.x ) + ( m_TraySpec.m_SubChipTrayA * m_Gear.x ) + ( m_MeA )) +
			(  m_TraySpec.m_SubTrayC*(m_iSubColL ) * m_Gear.x ) + 
			(  m_TraySpec.m_SubChipTrayC*(m_iChipColL) * m_Gear.x );
		p.y = m_Align.y +
			(( m_TraySpec.m_SubTrayB * m_Gear.y ) + ( m_TraySpec.m_SubChipTrayB * m_Gear.y ) + ( m_MeB )) +
			(  m_TraySpec.m_SubTrayD*(m_iSubRowL ) * m_Gear.y ) + 
			(  m_TraySpec.m_SubChipTrayD*(m_iChipRowL) * m_Gear.y );
	}
	else
	{		
		int m_iRowL = -1; // �� y ����
		int m_iColL = -1; // �� x ����
		
		m_iColL = iNo % m_TraySpec.Column;		// For C
		m_iRowL = iNo / m_TraySpec.Column;		// For D
		
		p.x = m_Align.x + (( m_TraySpec.A * m_Gear.x ) + ( m_TraySpec.C*(m_iColL) * m_Gear.x )) + ( m_MeA );	
		p.y = m_Align.y + (( m_TraySpec.B * m_Gear.y ) + ( m_TraySpec.D*(m_iRowL) * m_Gear.y )) + ( m_MeB );
		
		// Debug
		CString d;
		d.Format("%dD . %dC", m_iRowL, m_iColL );
		f.CWinMessage( d, theApp.enDArm );	
	}

	return p;
}

CPoint CTrayFile::GetCoordinateCustomRemote(int iNo)
{
	// �p�G�O Custom Remote Control
	// ����, �N���ݭn�ഫ�}�C.
	// ���O���s�g�@�Ӥ���n�Ϥ��{�b�O���O Remote Control

	CPoint p;
	
	if( m_Chip )
	{
		int m_iSubRowL = -1;	// �� y ���� For D
		int m_iSubColL = -1;	// �� x ���� For C

		int m_iChipRowL = -1;	// �� y ���� For D
		int m_iChipColL = -1;	// �� x ���� For C
		//

		int SubTrayColumn	= m_TraySpec.m_SubTrayColumn; 
		int ChipTrayColumn	= m_TraySpec.m_SubChipTrayColumn;
		int TotalValue = SubTrayColumn * ChipTrayColumn;

		int TotalForD = -1;
		int TotalForC = -1;

		TotalForD = iNo / TotalValue;	// ����
		TotalForC = iNo % TotalValue;	// ���l��

		m_iSubRowL	= TotalForD / ChipTrayColumn;	// ���o Sub D	���ܤ�
		m_iChipRowL = TotalForD % ChipTrayColumn;	// ���o Chip D	���ܤ�

		m_iSubColL	= TotalForC / ChipTrayColumn;	// ���o Sub C	���ܤ�
		m_iChipColL	= TotalForC % ChipTrayColumn;	// ���o Chip C	���ܤ�

		p.x = m_Align.x + 
			(( m_TraySpec.m_SubTrayA * m_Gear.x ) + ( m_TraySpec.m_SubChipTrayA * m_Gear.x ) + ( m_MeA )) +
			(  m_TraySpec.m_SubTrayC*(m_iSubColL ) * m_Gear.x ) + 
			(  m_TraySpec.m_SubChipTrayC*(m_iChipColL) * m_Gear.x );
		p.y = m_Align.y +
			(( m_TraySpec.m_SubTrayB * m_Gear.y ) + ( m_TraySpec.m_SubChipTrayB * m_Gear.y ) + ( m_MeB )) +
			(  m_TraySpec.m_SubTrayD*(m_iSubRowL ) * m_Gear.y ) + 
			(  m_TraySpec.m_SubChipTrayD*(m_iChipRowL) * m_Gear.y );

	}
	else
	{		
		int m_iRowL = -1; // �� y ����
		int m_iColL = -1; // �� x ����
		
		m_iColL = iNo % m_TraySpec.Column;		// For C
		m_iRowL = iNo / m_TraySpec.Column;		// For D
		
		p.x = m_Align.x + (( m_TraySpec.A * m_Gear.x ) + ( m_TraySpec.C*(m_iColL) * m_Gear.x )) + ( m_MeA );	
		p.y = m_Align.y + (( m_TraySpec.B * m_Gear.y ) + ( m_TraySpec.D*(m_iRowL) * m_Gear.y )) + ( m_MeB );
		
		// Debug
		CString d;
		d.Format("%dD . %dC", m_iRowL, m_iColL );
		f.CWinMessage( d, theApp.enDArm );	
	}

	return p;
}

CPoint CTrayFile::GetCoordinate(int iNo)
{
	// Chip Tray ����
	if( m_Chip )
		iNo = GetChipTrayPosition( iNo );
	// �o�̭n�ഫ Booking ���ƭ�, �H�ŦX���񪬺A

	CPoint p;
	
	if( m_Chip )
	{
		int m_iSubRowL = -1;	// �� y ���� For D
		int m_iSubColL = -1;	// �� x ���� For C

		int m_iChipRowL = -1;	// �� y ���� For D
		int m_iChipColL = -1;	// �� x ���� For C
		//

		int SubTrayColumn	= m_TraySpec.m_SubTrayColumn; 
		int ChipTrayColumn	= m_TraySpec.m_SubChipTrayColumn;
		int TotalValue = SubTrayColumn * ChipTrayColumn;

		int TotalForD = -1;
		int TotalForC = -1;

		TotalForD = iNo / TotalValue;	// ����
		TotalForC = iNo % TotalValue;	// ���l��

		m_iSubRowL	= TotalForD / ChipTrayColumn;	// ���o Sub D	���ܤ�
		m_iChipRowL = TotalForD % ChipTrayColumn;	// ���o Chip D	���ܤ�

		m_iSubColL	= TotalForC / ChipTrayColumn;	// ���o Sub C	���ܤ�
		m_iChipColL	= TotalForC % ChipTrayColumn;	// ���o Chip C	���ܤ�

		p.x = m_Align.x + 
			(( m_TraySpec.m_SubTrayA * m_Gear.x ) + ( m_TraySpec.m_SubChipTrayA * m_Gear.x ) + ( m_MeA )) +
			(  m_TraySpec.m_SubTrayC*(m_iSubColL ) * m_Gear.x ) + 
			(  m_TraySpec.m_SubChipTrayC*(m_iChipColL) * m_Gear.x );
		p.y = m_Align.y +
			(( m_TraySpec.m_SubTrayB * m_Gear.y ) + ( m_TraySpec.m_SubChipTrayB * m_Gear.y ) + ( m_MeB )) +
			(  m_TraySpec.m_SubTrayD*(m_iSubRowL ) * m_Gear.y ) + 
			(  m_TraySpec.m_SubChipTrayD*(m_iChipRowL) * m_Gear.y );

	}
	else
	{		
		int m_iRowL = -1; // �� y ����
		int m_iColL = -1; // �� x ����
		
		m_iColL = iNo % m_TraySpec.Column;		// For C
		m_iRowL = iNo / m_TraySpec.Column;		// For D
		
		p.x = m_Align.x + (( m_TraySpec.A * m_Gear.x ) + ( m_TraySpec.C*(m_iColL) * m_Gear.x )) + ( m_MeA );	
		p.y = m_Align.y + (( m_TraySpec.B * m_Gear.y ) + ( m_TraySpec.D*(m_iRowL) * m_Gear.y )) + ( m_MeB );
		
		// Debug
		CString d;
		d.Format("%dD . %dC", m_iRowL, m_iColL );
		f.CWinMessage( d, theApp.enDArm );		

	}

	return p;
}
void CTrayFile::SetSpec(tagTraySpec TraySpec)
{
	m_TraySpec = TraySpec;

	// Chip Tray
	if( m_Chip )
	{
		// �p�G�O Chip Tray Mode �N�n�ק� Column �P Row
		// �]���n������� Chip tray �X�_�ӷ�@�O�@�Ӥj�� Tray
		m_TraySpec.Row = m_TraySpec.m_SubTrayRow * m_TraySpec.m_SubChipTrayRow;
		m_TraySpec.Column = m_TraySpec.m_SubTrayColumn * m_TraySpec.m_SubChipTrayColumn;
	}

	// Note : �� Tray Spec �Ƕi�Ӫ��ɭ�, �� Tray Size �Ƕi��.
	// m_TraySize �O��� Tray �i�H�\��IC�ƶq
	m_Row = m_TraySpec.Row;
	m_Col = m_TraySpec.Column;

	m_TraySize = ( m_Row * m_Col );
	TrayStatusResize(); // ���s�w�q Tray Size

	// Convert 
	if( m_Chip )
	{
		ConvertChipTray();
		// �����ഫ�Ϊ��}�C
	}
}

void CTrayFile::SetMe(int A, int B )
{
	// �o�̷|�����c�~�t, ���p����I�ɧ���c�~�t�]��i�h.
	m_MeA = A;
	m_MeB = B;
}

void CTrayFile::TrayStatusResize()
{
	// �����D������|�o���g �����ª� delete ��
	if( m_TrayStatus != NULL )
	{
		delete m_TrayStatus;
		m_TrayStatus = NULL;
	}

	// Check Auto Skip
	if( m_TrayStatusAutoSkip != NULL )
	{
		delete m_TrayStatusAutoSkip;
		m_TrayStatusAutoSkip = NULL;
	}

	// Convert Chip Tray
	if( m_ChipTrayArray != NULL )
	{
		delete m_ChipTrayArray;
		m_ChipTrayArray = NULL;
	}
	// Convert Chip Tray
	if( m_ChipTrayArrayStatus != NULL )
	{
		delete m_ChipTrayArrayStatus;
		m_ChipTrayArrayStatus = NULL;
	}

	m_TrayStatus = new int[m_TraySize];

	// Auto Skip
	m_TrayStatusAutoSkip = new int[m_TraySize];

	// Convert Chip Tray
	m_ChipTrayArray = new int[m_TraySize];
	m_ChipTrayArrayStatus = new int[m_TraySize];
	
	for(int i = 0; i<m_TraySize; i++ )
	{
		m_TrayStatus[i] = enEmpty;
		// �ڭ̫ŧi�@�� Tray �� Spec ���ɭ�. ���N���]�w�� enEmpty
		
		// Check Auto Skip
		m_TrayStatusAutoSkip[i] = enEmpty;

		// Convert Chip Tray
		m_ChipTrayArray[i] = -1;
		m_ChipTrayArrayStatus[i] = enEmpty;
	}	
}

void CTrayFile::SetAlign(tagXYZ Align)
{
	m_Align = Align;
}
void CTrayFile::SetGear(tagXYZ Gear)
{
	m_Gear = Gear;
}

int CTrayFile::TrayiNoGetStatus(int iNo)
{
	// Chip
	if( m_Chip )
		return m_ChipTrayArrayStatus[iNo];

	return m_TrayStatus[iNo];
}

// Check Auto Skip
int CTrayFile::TrayiNoGetStatusAuto(int iNo)
{
	return m_TrayStatusAutoSkip[iNo];
}
// Check Auto Skip
void CTrayFile::TrayiNoGetStatusSetAuto()
{
	m_TrayStatusAutoSkip[m_iNow] = enOK;
}

///////////////////////////////////////////////////////////////////
// �B��Ϊ��\��
BOOL CTrayFile::LocationDone(int DeiNo)
{
	m_TrayStatus[DeiNo] = enOK;

	m_iNow = DeiNo;
	m_iNext = DeiNo + 1;

	SaveLocation();
	// �⪬�A�O�����r��

	return TRUE;
}

BOOL CTrayFile::LocationDone()
{
	m_iNext++;
	// �M���U�@�Ӧ�m+1
	// ����IC�Ω�nIC��~+1
	// �N�O��Arm Z�^Home OK��

	m_TrayStatus[m_iNow] = enOK; 

	// Chip Tray
	if( m_Chip )
	{
		int iNo = GetChipTrayPosition( m_iNow );
		m_ChipTrayArrayStatus[iNo] = enOK; 
	}

	SaveLocation();
	// �⪬�A�O�����r��

	return TRUE;
}

BOOL CTrayFile::LocationAllDone()
{
	m_iNow = m_TraySize - 1;
	m_iNext = m_TraySize;

	for(int i = 0; i<m_TraySize; i++ )
		m_TrayStatus[i] = enOK;	
	// �������m�]�����ϥιL enOK 

	// Convert Chip Tray
	if( m_Chip )
		m_ChipTrayArrayStatus[i] = enOK;	

	SaveLocation();
	// �⪬�A�O�����r��

	return TRUE;
}
BOOL CTrayFile::LocationMove()
{
	m_TrayStatus[m_iNow] = enMoving;

	// Chip Tray
	if( m_Chip )
	{
		int iNo = GetChipTrayPosition( m_iNow );
		m_ChipTrayArrayStatus[iNo] = enOK; 
	}

	return TRUE;
}
BOOL CTrayFile::LocationMove(int DeiNo)
{
	m_TrayStatus[DeiNo] = enMoving;
	return TRUE;
}

static CMutex MutexTrayFile;
BOOL CTrayFile::LocationQuery()
{
	CSingleLock Lock(&MutexTrayFile);
	Lock.Lock();

	if(m_TraySpec.Row <= 0 || m_TraySpec.Column <= 0)
	{
		Lock.Unlock();	// �n�O�o�Ѷ}��~���}
		return enEOF;
	// �S����J Row. Col. Return Tray �w�g����.
	}

	//
	bool bOk = false;
	for(int i = 0; i<m_TraySize; i++ )
	{
		if (m_TrayStatus[i] == enEmpty || m_TrayStatus[i] == enMoving )
		{
			m_iNext = i;
			bOk = true;
			break;
		}
	}	

	if( m_iNext == m_TraySize || !bOk )
	{
		Lock.Unlock();	// �n�O�o�Ѷ}��~���}
		return enEOF;
	}
	// �p�G�U�@�Ӧ�m���� m_TraySize , ��ܤw�g�����Ҧ���IC
	// �o�� Tray �w�g�S�� IC
	// �q�� Tray �w�g����.
	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////

	Lock.Unlock();

	return m_iNext;
}

BOOL CTrayFile::SemiAuto(int Coord)
{
	m_iNext = Coord;
	return m_iNext;
}


int	CTrayFile::LocationBooking()
{
	m_iNow = m_iNext;
	// ��ثe��m�]�n

	m_TrayStatus[m_iNow] = enBooking;
	// �N�n������m���]�� enBooking.

	// Chip Tray
	if( m_Chip )
	{
		int iNo = GetChipTrayPosition( m_iNow );
		m_ChipTrayArrayStatus[iNo] = enBooking; 
	}

	return m_iNow;
	// ��ثe��m�ǥX�h,�� GetCoordinate ���m.
}

void CTrayFile::SetFull()
{
	for(int i = 0; i<m_TraySize; i++ )
	{
//		m_TrayStatus[i] = enEmpty;	
		m_TrayStatus[i] = enOK;
		// ���@�L�s�� Tray. IC �S�����չL, �ڭ̱N���A�����]�� enEmpty 

		// Chip Tray
		if( m_Chip )
			m_ChipTrayArrayStatus[i] = enOK;
	}

	m_iNext = m_TraySize;
	// �]�� full
}

void CTrayFile::ChangeTray()
{
	for(int i = 0; i<m_TraySize; i++ )
	{
		m_TrayStatus[i] = enEmpty;	
		// ���@�L�s�� Tray. IC �S�����չL, �ڭ̱N���A�����]�� enEmpty 

		// Check Auto Skip
		m_TrayStatusAutoSkip[i] = enEmpty;

		// Chip Tray
		if( m_Chip )
			m_ChipTrayArrayStatus[i] = enEmpty;
	}
	m_iNext = 0;
	m_iNow = 0;

	SaveLocation();
}
void CTrayFile::LotDoneSetFull()
{
	for(int i = 0; i<m_TraySize; i++ )
	{
		m_TrayStatus[i] = enOK;
		
		// Chip
		if( m_Chip )
			m_ChipTrayArrayStatus[i] = enOK;	
	}
	// LotDone �ڭ̱N���A�����]�� enEmpty 

	m_iNext = 0;
	m_iNow = 0;
	// �]�� full, ��ܤS�ݭn�q�Ĥ@�Ӧ�m�}�l. �]�N�O 0.
}
void CTrayFile::SetCoordinate(CString csFile)
{
	// �]�w�ɮצ�m
	m_Coordinate = csFile;
}
void CTrayFile::SaveLocation()		
{
	// �O���ثe����m
	if( m_Coordinate == "" )
		return;
	
	f.SaveSetting( m_Coordinate, "Coordinate", "iNow",	m_iNow );
	f.SaveSetting( m_Coordinate, "Coordinate", "iNext",	m_iNext );
}
void CTrayFile::SetLocation()		
{
	// �]�w�ثe����m
	int iiNow = 0;
	int iiNext = 0;

	f.GetSetting( m_Coordinate, "Coordinate", "iNow",	iiNow );
	f.GetSetting( m_Coordinate, "Coordinate", "iNext",	iiNext );

	if( iiNow == -1 || iiNext == -1 )
	{
		// ��ܨS��Ū���, �j���ܦ� 0 ��@�O SetFull
		iiNow = 0;
		iiNext = 0;
	}

	m_iNow = iiNow;
	m_iNext = iiNext;
}
BOOL CTrayFile::SetLocationStatus()
{
	// ���s�]�w���A (�ھ� iNow �M iNext )

	if(m_TraySpec.Row <= 0 || m_TraySpec.Column <= 0)
		return enEOF;
	// �S����J Row. Col. Return Tray �w�g����.

	for(int i = 0; i< m_iNext; i++ )
	{
		m_TrayStatus[i] = enOK;

		if( m_Chip )
		{
			int iNo = GetChipTrayPosition( i );
			m_ChipTrayArrayStatus[iNo] = enOK;
		}
	}
	// �ڭ̫ŧi�@�� Tray �� Spec ���ɭ�. ���N���]�w�� enEmpty

	return TRUE;
}

BOOL CTrayFile::GetStatus(int *pTray, int iSize)
{
	memcpy(pTray, m_TrayStatus, iSize * sizeof(int));

	return TRUE;
}

BOOL CTrayFile::SetStatus(int *pTray, int iSize)
{
	memcpy(m_TrayStatus, pTray, iSize * sizeof(int));

	// Chip Tray
	// �p�G���}�� Chip Tray ����, �p�G Input Tray ���ܧ󪬺A
	// �]�n�@�_��s���A
	if( m_Chip )
	{
		memcpy(m_ChipTrayArrayStatus, pTray, iSize * sizeof(int));
	}
	return TRUE;
}

BOOL CTrayFile::Check()
{
	BOOL bOK = FALSE;
	for(int i = 0; i<m_TraySize; i++ )
	{
		if (m_TrayStatus[i] == enOK || m_TrayStatus[i] == enMoving )
		{
			bOK = TRUE;
			break;
		}
	}

	return bOK;
}

// Convert Booking 
void CTrayFile::ConvertChipTray()
{
	int itotaltray = 
		( m_TraySpec.m_SubChipTrayColumn * m_TraySpec.m_SubTrayColumn ) * 
		( m_TraySpec.m_SubChipTrayRow * m_TraySpec.m_SubTrayRow );				// ��X�]�t Chip Tray ��� Tray �`�@���X�� IC

	m_ChipTrayArray = new int[itotaltray];
	int TrayArray = 0;

	int InitialValue = 0;
	int ixxxsingletotal =  
		m_TraySpec.m_SubTrayColumn * ( m_TraySpec.m_SubChipTrayColumn * m_TraySpec.m_SubChipTrayRow );
	
	//////////////////////
	int total = m_TraySpec.m_SubChipTrayColumn * m_TraySpec.m_SubChipTrayRow;	// �@�� Chip Tray ���j�p
	int *ptrf = new int[total];													// Chip Tray �}�C
	//
	int isingletotal = total * m_TraySpec.m_SubTrayColumn;
	int *ptrtempf = new int[total];
	int *ptrfsingle = new int[isingletotal];
	//

	for( int ic = 0; ic < m_TraySpec.m_SubTrayRow; ic++ )
	{		
		InitialValue = ic * isingletotal;
		// �]�w��@ Column �� �_�l�ƭ�
	
		/////
		int iArray	= 0;
		int iBase	= 0;
//		for( int x = 0; x< m_TraySpec.m_SubChipTrayRow; x++  )
		for( int x = 0; x< m_TraySpec.m_SubChipTrayRow; x++  )
		{
			for( int y = 0; y<m_TraySpec.m_SubChipTrayColumn; y++ )
			{
				int c = iArray / m_TraySpec.m_SubChipTrayColumn;
				int d = c * m_TraySpec.m_SubChipTrayColumn * m_TraySpec.m_SubTrayColumn + InitialValue;

				ptrf[iArray] = d + iBase;
				iBase++;
				iArray++;
			}
			iBase = 0;
		}	
		// ���D�X�Ĥ@�L���ƦC
		// ptrf[iArray] �C�C�Ĥ@�L���}�C
		
		for( int d = 0; d < total; d++ )
		{
			ptrfsingle[d] = ptrf[d];
			ptrtempf[d] = ptrf[d];
		}
		
		int iCount = 0;
		for( int i = total; i < isingletotal ;i ++ )
		{	
			ptrfsingle[i]		= ptrtempf[iCount] + m_TraySpec.m_SubChipTrayColumn;
			ptrtempf[iCount]	= ptrfsingle[i];
			
			iCount ++;
			
			if( iCount == total )
				iCount = 0;
		}
		/*
		// Debug 
		CString cs = "";
		for(int de = 0; de<isingletotal;de++ )
		{
		CString dd = "";
		dd.Format("%d,", ptrfsingle[de]);
		cs = cs + dd;
		}
		AfxMessageBox( cs );
		*/
		///
		for( int r = 0; r < isingletotal; r++ )
		{
			m_ChipTrayArray[TrayArray] = ptrfsingle[r];
			TrayArray++;
		}
		// ��}�C���ƦC
	}
	
	// Debug 
/*
	CString cs;
	for( int de = 0; de< itotaltray; de++)
	{	
		CString ddf;
		ddf.Format("%d,", m_ChipTrayArray[de]);
		cs = cs + ddf;
	}
	AfxMessageBox( cs );
*/

	delete [] ptrf;
	delete [] ptrfsingle;
	delete [] ptrtempf;
	// �R���}�C
}

int CTrayFile::GetChipTrayPosition( int iBooking )
{
	int m_iIndex = -1;

	m_iIndex = m_ChipTrayArray[iBooking];

	return m_iIndex;
}

