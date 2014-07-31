// TrayFile.h: interface for the CTrayFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAYFILE_H__68F611BA_E0F9_4082_973D_BF2D0080FB45__INCLUDED_)
#define AFX_TRAYFILE_H__68F611BA_E0F9_4082_973D_BF2D0080FB45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Member.h" 
//#include "Define.h" 
// Because We need 
// #1: tagTratSpec struct
// #2: tag XYZ struct

#include <cmath>
#include <afxmt.h>
// avoid crash in status array.

typedef struct tagTray{
	int Status;
} tagTray;

class CTrayFile  
{
public:
	BOOL SemiAuto(int Coord);
	CTrayFile();
	virtual ~CTrayFile();

	tagTraySpec m_TraySpec;				// Tray data, A, B, C, D...��m. ��� mm
	tagXYZ		m_Align;				// Arm XYZ Alignment ��m.. ��� Motor Pulse.
	tagXYZ		m_Gear;					// Arm XYZ �� Gear Ration.. ���. ���v	

	int m_Row;							// Tray data �� Row ��
	int m_Col;							// Tray data �� Col ��
	int m_TraySize;						// Tray data Row * Col,�@��Tra��IC�ƶq

	int m_MeA;							// ���c�Ѽ� ���I�P A
	int m_MeB;							// ���c�Ѽ� ���I�P B

	void SetSpec(tagTraySpec TraySpec);	// �� Tray data, A, B, C, D.. Tray �L��ƶǶi��.
	void SetMe(int A, int B );			// ����c�~�t�Ƕi��
	void SetAlign(tagXYZ Align);		// �� Alignment ��ƶǶi��.
	void SetGear(tagXYZ Gear);			// �� Gear Ration ��ƶǶi��

	// Chip Tray
	void SetChipMode(int Chip);
	int	m_Chip;	// 1 ��ܨϥ� Chip Tray, 0 ��ܨS���ϥ� Chip Tray

	// �ŧi�@�� TrayStatus. �}�C�j�p�O Tray Size.
	int *m_TrayStatus;
	void TrayStatusResize();	// ���� TraySpec �Ƕi�ӫ�. Resize �}�C�j�p.

	// Terence / Denny �Ʊ�i�H���ϥΪ̪��D�O�_�O Auto Skip �����A
	int *m_TrayStatusAutoSkip;
	int TrayiNoGetStatusAuto(int iNo);
	void TrayiNoGetStatusSetAuto();

	// �B��Ϊ��\��
	enum Status 
	{
		enEOF		=-1,	// 
		enEmpty		= 0,	// �Ӧ�m�O�ť�.
		enBooking	= 1,	// ���b�g�J���.
		enMoving	= 3,	// ���b���ʤ�.
		enOK		= 4		// �Q����.�άO�Q�\��
	};	

	// �]�w Tray �L���A
	void SetFull();					// �ڭ̱N���A�����]�� enEmpty, �q iNext�]Size�[1
	void ChangeTray();				// �ڭ̱N���A�����]�� enEmpty, �q iNext Dut#1
	BOOL LocationQuery();			// �T�{�o�� Tray �O�_�٦� IC
	int	 LocationBooking();			// ���m�]�� enBooking. ��ǳƭn�񪺦�m�]�� Booking.
	BOOL LocationMove();			// ���m�]�� enMoving, �⥿�b���ʪ���m�]�� Moving.
	BOOL LocationMove(int DeiNo);	// ��S�w��m�]�� enMoving, �⥿�b���ʪ���m�]�� Moving.
	CPoint GetCoordinate(int iNo);	// ����y��
	CPoint GetIndex();				// ����y��, �� Tray Map �ɮץ�
	CPoint GetIndex(int iNo);		// ����y��, �� Tray Map �ɮץ�
	BOOL LocationDone();

	BOOL LocationDone(int DeiNo);
	// Debug using.

	BOOL GetStatus(int *pTray, int iSize);
	BOOL SetStatus(int *pTray, int iSize);

	int TrayiNoGetStatus(int iNo);

	int m_iNext;	// �U�@�ӥi�H���Ω񪺦�m IC (Input�O������m. Output�O�񪺦�m)
	int m_iNow;		// �ثe���b���Ω�(Input�O������m. Output�O�񪺦�m)

	// Note : �p�GInput�MOutput�O�P�@�ӫh�n�ŧi�⦸
	
	// #1: ���@�ӷs�� Tray. ���N���A�����]�� enEmpty, ��ܦ� IC. ���O�٨S���}�l�O�� void SetFull();	
	// #2: �T�{�o�� Tray �٦��S�� IC. �O�_�٦s�b enUnBook. BOOL LocationQuery();
	// #3: ��ǳƭn���� IC �n��, �M��]�� enBooking.
	// #4: ���o��m��, MotorRun �]�� Moving.
	// #5: �����IC�Ω�IC LocationDone �]�� enOK �ç�U�@�� m_iNext+1

	CString		m_Coordinate;			// Coordinate �ɮצ�m
	void SetCoordinate(CString csFile);	// �]�w�ɮצ�m
	void SaveLocation();				// �O���ثe����m
	void SetLocation();					// �]�w�ثe����m
	BOOL SetLocationStatus();			// ���s�]�w���A (�ھ� iNow �M iNext )

	BOOL LocationAllDone();				// ���m�����]�� enOK
	void LotDoneSetFull();				// ���m�����]�� enEmpty

	BOOL Check();

	// Chip Tray Convert
	void ConvertChipTray();
	int GetChipTrayPosition( int iBooking );
	int *m_ChipTrayArray;						// �ΨӬ����ഫ�}�C��
	int	*m_ChipTrayArrayStatus;					// �ΨӬ����ഫ�}�C�����A
	CPoint GetCoordinateCustomRemote(int iNo);	// ����y��

	// Location In / Location Out 
	CPoint GetCoordinateLocation(int iNo);		// ����y��


};

#endif // !defined(AFX_TRAYFILE_H__68F611BA_E0F9_4082_973D_BF2D0080FB45__INCLUDED_)
