// PreheaterFile.h: interface for the CPreheaterFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PREHEATERFILE_H__D3AC3ACF_F5C1_4361_A7AA_421F7C741D7C__INCLUDED_)
#define AFX_PREHEATERFILE_H__D3AC3ACF_F5C1_4361_A7AA_421F7C741D7C__INCLUDED_

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

typedef struct tagPreheater{
	int Status;
} tagPreheater;

class CPreheaterFile  
{
public:
	CPreheaterFile();
	virtual ~CPreheaterFile();

	// add new function
	void SetSpec(tagTraySpec TraySpec);	// �� Tray data, A, B, C, D.. Tray �L��ƶǶi��.
	void SetMe(int A, int B );			// ����c�~�t�Ƕi��
	void SetAlign(tagXYZ Align);		// �� Alignment ��ƶǶi��.
	void SetGear(tagXYZ Gear);			// �� Gear Ration ��ƶǶi��
	void SetCoordinate(CString csFile);
	void SetSoak(long SoakTime);		// �]�w SoakTime �H�έ��s�]�w iNext �M iCount.
	int	 GetiNext();
	int	 GetiCount();

	tagTraySpec m_TraySpec;				// Tray data, A, B, C, D...��m. ��� mm
	tagXYZ		m_Align;				// Arm XYZ Alignment ��m.. ��� Motor Pulse.
	tagXYZ		m_Gear;					// Arm XYZ �� Gear Ration.. ���. ���v	
	int			m_MeA;					// ���c�Ѽ� ���I�P A
	int			m_MeB;					// ���c�Ѽ� ���I�P B
	CString		m_Coordinate;			

	BOOL ClearBuffer();
	long GetRemainSoakTime();
	void SetSoakTime(long time);
	CPoint GetCoordinate(int iNo);
	void OutputDone();
	void InputDone();
	BOOL OutputLocationQuery();
	BOOL InputLocationQuery();
	void Save();
	void Load();
	void LoadFile();
	
	enum Status {enEOF = -1, enEmpty = 0, enBooking = 1, enMoving = 2, enOK = 3};
	
	// ���� Dut ����m
	int	Convert( int iNo );

protected:

	long m_iSoakTime; // in sec
	long m_iNext;
	long m_iCount;
	COleDateTime m_Time[_MaxPreHeaterDevice]; // max 200 device can put in preheater
};

#endif // !defined(AFX_PREHEATERFILE_H__D3AC3ACF_F5C1_4361_A7AA_421F7C741D7C__INCLUDED_)
