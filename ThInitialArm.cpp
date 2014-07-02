// ThInitialArm.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ThInitialArm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThInitialArm

IMPLEMENT_DYNCREATE(CThInitialArm, CWinThread)

CThInitialArm::CThInitialArm()
{
	m_bStatus = enIdle;
	m_iRunError = enCodeRunOK;
	m_bInitialized = false;
	m_bInitialRequest = false;
}

CThInitialArm::~CThInitialArm()
{
	TRACE("~CThInitialArm\n");
}

BOOL CThInitialArm::InitInstance()
{
	f.IncraseThreadCount();
	while(m.Info.bRunning)
	{
		Running();
		Sleep(_Wait);
	}
	f.ReduceThreadCount();
	f.m_Log.AddLogEvent( "Thread Initial Arm Finish" );

	return TRUE;
}

void CThInitialArm::Running()
{
	if(!m_bInitialized && m.Info.iStatus != theApp.enInitial)
	{
		m_bStatus = enIdle;
		return;
	}
	// If Handler status is Uninitial. We force it to return and keep m_bStatus in enIdle.
	// Notes : In Thread Monitior. Uninitial will always be enIdle
	
	if( m_bInitialRequest )
	{
		m_bInitialRequest = false;
		m_bStatus = enInitialize;
	}
	// Note: This CThThread only for initial Stack.!!!

	switch(m_bStatus)
	{			
	case enInitialize:	
		{
			long oldXInPos = m.m_Motor.ArmX.InPosRange;

			Initialize();

			m.m_Motor.ArmX.InPosRange = oldXInPos;

		}
		NextStatus();
		break;
	case enIdle:		
		NextStatus();
		break;

	default:
		CheckRestart();
		break;
	}
}
void CThInitialArm::CheckRestart()
{
	// initialize
	if(m.Info.iStatus == theApp.enInitial)
		return;

	if( m.Info.iStatus == theApp.enCycle || 
		m.Info.iStatus == theApp.enOneCycle ||
		m.Info.iStatus == theApp.enManual || 
		m.Info.iStatus == theApp.enOverride )
		m_bStatus = m_bStatus & 0xfff0;
}
void CThInitialArm::NextStatus()
{
	if( f.IsPause())
		m_bStatus = m_bStatus | 0x1;

	switch(m_bStatus)
	{			
	case enInitialize:
		m_bStatus = enIdle;	// After Initial Go to enIdle and Wait next time ButtonInitial();
		break;
	case enIdle:
		m_bStatus = enIdle;
		break;
	}

	if(f.IsPause())
	{
		if(m_bStatus != enIdle)
			m_bStatus = m_bStatus | 0x1;
		return;
	}
}
bool CThInitialArm::IsPause()
{
	if((m_bStatus & 0x1) || m_bStatus == enIdle)
		return true;
	else
		return false;
}
void CThInitialArm::InitialStart()
{
	m_bInitialRequest = true;
}
void CThInitialArm::ShuttleInitialFinalHome()
{
	m.OutSet.Shuttle = false;
}
void CThInitialArm::ShuttleInitialHome()
{
	m.OutSet.Shuttle = false;	
	if( m.InStatus.ShuttlePLmt == _ShuttlePLmtOn )
	{
		m.OutSet.Shuttle = true;
	}
}
void CThInitialArm::Initialize()
{
	// 1.0Aj
	// Bypass Initial
#ifdef _Demo

	// Arm X
	m.InterLock.InitialArmXEnd = true;
	m.MotorStatus.ArmXInitialed = true;
	m.MotorStatus.ArmX = _T("Arm X OK.");
	m_bInitialized = true;
	
	return;
#endif

	m_bInitialized = false;
	m.MotorStatus.ArmX = _T("Initialing, Wait for TS OK.");
	f.CWinMessage( "Arm:Arm X Initial Start", theApp.enDArm );

	long oldXInPos = m.m_Motor.ArmX.InPosRange;
	m.m_Motor.ArmX.InPosRange = _InitialInPosRange;

	////// Initial Process
	// Arm X
	while(1)
	{
		// Test Site Up ����, �i�H�}�l Arm XY Initial 
		if( m.InitialInterLock.InitialArmZUpOK )
			break;
		// �ϥΪ̫��U Stop  ���� Initial
		else if( f.IsPause() )
			break;
		// �{���������F
		if( !m.Info.bRunning  )		
			return;
		else
			; // ���ݱ���F��	
	}

	// Shuttle �^�� Home
	ShuttleInitialHome();

	// �ϥΪ̫��U Stop, �N���� return
	// If not Initial. return this function. User want to stop.
	if( m.Info.iStatus != theApp.enInitial )
		return;

	// Arm Z �w���F, �}�l��
	m.MotorStatus.ArmX = _T("Arm X Initialing.");

	// ���J�Ʋ��t��, �ƨ� sensor ����h
	f.Motor.LoadDriftSpeed( &m.m_Motor.ArmX );
	m_iRunError = f.Motor.MotorMovetopPLimt( m.m_Motor.ArmX, _InitialArmXTimeout );
	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.ArmX ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;
	m.MotorStatus.ArmX = "Move to Lmt.";	/* �Ĥ@�����ʨ� sensor ���\ */

	// �M�� Encoder
	f.Wait( _WaitLmt );
	f.Motor.MotorClearCount( &m.m_Motor.ArmX );
	f.Wait( _WaitLmt );

	// ���J�j���t�� ���X sensor
	f.Motor.LoadSearchSpeed( &m.m_Motor.ArmX );
	m_iRunError = f.Motor.MotorRunAnyway( &m.m_Motor.ArmX, ( _InitialXHome * m.m_Ratio.X_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.ArmX ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;
	m.MotorStatus.ArmX = "Search Home OK.";	/* �Ĥ@�����} sensor ���\ */

	//
	m.MotorStatus.ArmX = "Move to Lmt.";
	f.Motor.LoadSearchSpeed( &m.m_Motor.ArmX );
	m_iRunError = f.Motor.MotorMovetopPLimt( m.m_Motor.ArmX, _InitialArmXTimeout );
	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.ArmX ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;
	m.MotorStatus.ArmX = "Move to Lmt OK.";	/* �ĤG�����ʨ� sensor ���\ */
	
	//
	f.Wait( _ClearCountWait );
	f.Motor.MotorClearCount( &m.m_Motor.ArmX );
	f.Wait( _ClearCountWait );
	m_iRunError = f.Motor.MotorRunAnyway( &m.m_Motor.ArmX, ( _InitialXHome * m.m_Ratio.X_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
	if( m.Info.iStatus != theApp.enInitial )
		return;
	f.Wait( _ClearCountWait );
	f.Motor.MotorClearCount( &m.m_Motor.ArmX );
	// ���}  _InitialZHome mm �Z��, �קK�^ Home Overheat

	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.ArmX ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;
	m.MotorStatus.ArmX = "Search Home OK.";	/* �ĤG�����} sensor ���\ */

	f.Wait( _ClearCountWait );
	f.Motor.MotorClearCount( &m.m_Motor.ArmX );
	f.Wait( _ClearCountWait );
	// ���}  _InitialZHome mm �Z��, �קK�^ Home Overheat

	// Shuttle Home
	ShuttleInitialFinalHome();

	/* Arm X ���ʨ�ݩR��m */
	
	//

	//!
	m.InterLock.InitialArmXEnd = true;
	m.MotorStatus.ArmXInitialed = true;
	m.MotorStatus.ArmX = _T("Arm X OK.");
	m_bInitialized = true;

	f.CWinMessage( "Arm:Arm X OK", theApp.enDArm );
}
bool CThInitialArm::IsInitialError(long err, long id)
{
	if(err != enCodeRunOK)
	{
		f.Motor.MotorStop( &m.m_Motor.ArmX  );
		f.Motor.MotorStop( &m.m_Motor.ArmY  );
		f.Motor.MotorStop( &m.m_Motor.ArmZ  );

		// stop all motor 
		m_bStatus = enIdle;
		m.MotorStatus.ArmX = "Cancel.";
		m.MotorStatus.ArmY = "Cancel.";
		m.MotorStatus.ArmZ = "Cancel.";
		m.Err.Arm.Code = err;
		// Set error 

		return true;
	}
	return false;
}
int CThInitialArm::ExitInstance()
{
	TRACE("CThInitialArm\n");
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThInitialArm, CWinThread)
	//{{AFX_MSG_MAP(CThInitialArm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThInitialArm message handlers
