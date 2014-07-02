// ThTester.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ThTester.h"

//
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThTester

IMPLEMENT_DYNCREATE(CThTester, CWinThread)

CThTester::CThTester()
{
	m_bStatus = enIdle;
	m_iRunError = enCodeRunOK;
	m_bInitialized = false;
	m_bInitialRequest = false;

	// Tester Log default value
	TesterLog.csCode = "";
	TesterLog.iBin = -1;
	TesterLog.iSetTemperature  = -1;
	TesterLog.iBooking = -1;
	TesterLog.iTray = -1;
	TesterLog.iPF = -1;

	//
	m_bSeralOpen = false;

	m_bIsWaitSendStartDelay = false;
}

CThTester::~CThTester()
{
	if( m_YieldLimit != NULL )
		delete m_YieldLimit;

	TRACE("~CThTester\n");
}
bool CThTester::InitTcpip()
{
	bool bTcpipOK = true;

	return bTcpipOK;
}
bool  CThTester::CloseRs232()
{
	bool bRs232CloseOK = true;

	m_Interface.Close();

	return bRs232CloseOK;
}
bool CThTester::InitRs232()
{
	bool bRs232InitOK = false;
	bool bRun = false;
	if( m.m_InterfaceEnable.m_bEnableRs232 == 1 )
	{		
		bRun = m_Interface.Open( 
			m.m_HandlerComPort.iPortTester, 
			1, "", "", 1, 0, 0 );
		
		m_bSeralOpen = bRun;
		
		if(!m_bSeralOpen)
		{
			CString csMsg = _T("");
			csMsg.Format("Tester Open Fail.(RS232)");
			f.DMsg.DMsg( csMsg + _DMsgMark, false );

#ifdef _Demo
			bRs232InitOK = true;
#else
			if( m.Setting.m_bEnableProgramInitialStart == 1 )
			{
			}
			else
				AfxMessageBox( csMsg );

			bRs232InitOK = false;
#endif
		}
		else
		{	
			CString csMsg = _T("");
			csMsg.Format("Tester Open Success.(RS232)");
			f.DMsg.DMsg( csMsg );

			bRs232InitOK = true;
		}
	}
	else
	{
		// No Enable Rs232
		bRs232InitOK = true;
	}

	return bRs232InitOK;
}
bool CThTester::Init()
{
	// 1.0Ah
#ifdef _Demo

	// 1.0 An
//	return true;

	// 1.0Ao
	return true;
#endif

	bool bInitOK = true;
	bool bRs232InitOK = false;
	bool bTcpipInitOK = false;

	// Rs232
	bRs232InitOK = InitRs232();
	bTcpipInitOK = InitTcpip();

	if( bRs232InitOK && bTcpipInitOK )
		bInitOK = true;
	else
		bInitOK = false;

	return bInitOK;
}
BOOL CThTester::InitInstance()
{
	if( !Init() )
	{
		return TRUE;
	}

	//
	InitValue();

	f.IncraseThreadCount();
	m.ThStatus.TesterCtrl.times = 1;
	while(m.Info.bRunning)
	{
		m.ThStatus.TesterCtrl.times++;
		Running();
		Sleep(_Wait);
	}
	f.ReduceThreadCount();
	f.m_Log.AddLogEvent( "Thread Tester Finish" );

	return TRUE;
}

void CThTester::InitialStart()
{
	m_bInitialRequest = true;
}

void CThTester::Initialize()
{
	m_bInitialized = false;
	m.MotorStatus.Tester = "Initialing.";

	//
	FTSetWaitSendStartDelay( false );

	m.MotorStatus.Tester = "Tester OK.";
	m.MotorStatus.TesterInitialed = true;
	m.InterLock.TesterEnd = true;
	m_bInitialized = true;
}

bool CThTester::IsInitialError()
{
	if( m.Info.iStatus == theApp.enUninitial )
		return false;
	if( m_iRunError != enCodeRunOK )
		return false;

	return true;
}
void CThTester::Running()
{
	if( m_bInitialRequest )
	{
		f.CWinMessage( "Tester:enInitialize R", theApp.enDTester );
		m_bInitialRequest = false;
		m_bStatus = enInitialize;
	}
	// Initial Tester Just for fun.

	m.ThStatus.TesterCtrl.line = m_bStatus;
	switch(m_bStatus)
	{			
	case enInitialize:
		Initialize();
		NextStatus();
		break;
	case enIdle:
		NextStatus();
		break;

	///////////////////////////////
	// Cycle 
	case enTestStart:			// Start Testing
		{
			// ���յ{�Ƕi�J�I

			//
			RepeatTrayCurrentTestIC();
		}
		NextStatus();
		break;
	///////////////////////////////
	// SLT
	case enSLTTestStart:		// SLT Test Start
		{
			InitTestStartTime();
			ResetTestTime();
			SLTShowTesting();
		}
		NextStatus();
		break;
	case enSLTTesting:			// SLT Testing 
		{
			SLTTesting();
		}
		NextStatus();
		break;
	case enSLTTestEnd:			// SLT Test End
		{
			UpdateTestedIC();
			//
			ResetFinalTestTime();
			SLTResultInfo();
			//
			RepeatTrayCurrentTestICClear();
		}
		NextStatus();
		break;
	///////////////////////////////
	// FT
	case enFTTestStart:			// FT Test Start
		{
			InitTestStartTime();
			ResetTestTime();
		}
		NextStatus();
		break;
	case enFTTesting:			// FT Testing
		{
			if(m.m_TestInterface.GetRemoteMode())
				FTTestingRemoteMode();
			else
				FTTesting();
		}
		NextStatus();
		break;
	case enFTTestEnd:			// FT Test End
		{
			UpdateTestedIC();
			//
			ResetFinalTestTime();
			FTResultInfo();	
			//
			RepeatTrayCurrentTestICClear();
		}
		NextStatus();
		break;
	default:
		CheckRestart();
		break;
	}
}
void CThTester::CheckRestart()
{

}
////////////////////////////////////////////////////////////////
// SLT
void CThTester::SLTShowTesting()
{	
	// Show Testing.
	CString csRunPageInfo = _T("");
	csRunPageInfo.Format("%s", "Testing" );
	m.Page.Run.m_wndTesting.SetWindowText( csRunPageInfo );
}
void CThTester::SLTResultInfo()
{
	// Show Code.
	CString csRunPageInfo = _T("");
	csRunPageInfo.Format("%s", theApp.m_tTester.TesterLog.csCode );
	m.Page.Run.m_wndTesting.SetWindowText( csRunPageInfo );

	// Show Code Color
	COLORREF color = f.GetCategoryColor(  theApp.m_tTester.TesterLog.csCode );
	m.Page.Run.m_wndTesting.SetNewBkColor( color );
	
	// Show Yield Control..
	m.Page.Run.m_ContinueFail.Add(color);
}
////////////////////////////////////////////////////////////////
// FT
bool CThTester::FTGetWaitSendStartDelay()
{
	return m_bIsWaitSendStartDelay;
}
void CThTester::FTSetWaitSendStartDelay( bool bIsWait )
{
	m_bIsWaitSendStartDelay = bIsWait;
}
bool CThTester::WaitSendStartDelay(double dSecs)
{	
	long m_ltime = dSecs * 1000;

	// Show Send Start Delay.
	CString csRunPageInfo = _T("");
	long m_lStart = ::GetTickCount();
	while(1)
	{
		long m_lNow = ::GetTickCount();
		long m_lDiff = m_lNow - m_lStart;
		double m_dSpendSecs = m_lDiff / 1000.;
		
		csRunPageInfo.Format("%s - %5.2f", "Send Start Delay", m_dSpendSecs );
		m.Page.Run.m_wndTesting.SetWindowText( csRunPageInfo );

		if( m_lDiff > m_ltime )
			return true;
		else if( f.IsPause() )
			return false;
		else if( !m.Info.bRunning )
			return false;

		Sleep(250);
	}

	// final
	csRunPageInfo.Format("%s - %5.2f", "Send Start Delay", dSecs );
	m.Page.Run.m_wndTesting.SetWindowText( csRunPageInfo );
}
void CThTester::FTShowSendStartDelay()
{
	// Show Send Start Delay.
	CString csRunPageInfo = _T("");
	csRunPageInfo.Format("%s", "Send Start Delay" );
	m.Page.Run.m_wndTesting.SetWindowText( csRunPageInfo );
}
void CThTester::FTShowTesting()
{
	// Show Testing.
	CString csRunPageInfo = _T("");
	csRunPageInfo.Format("%s", "Testing" );
	m.Page.Run.m_wndTesting.SetWindowText( csRunPageInfo );
}
void CThTester::FTTesting()
{
	CString csCode = _T("");
	TesterLog.csCode = csCode;

	// Clear error flag
	TesterLog.bError = false;

	if( m.Site.iRunMode == theApp.enOnLine )
	{
		CString csTestCode = _T("");
		if( m.m_TestSetting.m_TestType == theApp.enRS232 )		// �b�o�̳B�z RS232 ���q�T
		{
			int iStack = -1;				// Hardware Bin
			CString csBin = RS232Testing();	// �b Testing �̭����� EOT �åB�� Bin
			csTestCode = csBin;				
			TesterLog.csCode = csTestCode;
			TesterLog.iPF = GetPassFailValue( csTestCode );
		}
		else if( m.m_TestSetting.m_TestType == theApp.enTCP )
		{		
			int iStack = -1;				// Hardware Bin
			CString csBin = TcpTesting();	// �b Testing �̭����� EOT �åB�� Bin
			csTestCode = csBin;				// �� Tcp ���R���� Code �K�����յ��G
			TesterLog.csCode = csTestCode;
			TesterLog.iPF = GetPassFailValue( csTestCode );
		}
		else if( m.m_TestSetting.m_TestType == theApp.enTTL )	// �b�o�̳B�z TTL ���q�T
		{			
		}
		else if( m.m_TestSetting.m_TestType == theApp.enGPIB )
		{
		
		}
	}
	else if( m.Site.iRunMode == theApp.enOffLine )
	{
		// Demo Test Time
		WaitForDummyTest( m.Site.dDemoTestTime * 1000. );

		//
		csCode.Format("%d", m.Site.iSiteDummyBinForCatorgy );
		TesterLog.csCode = csCode;
	}
	else if( m.Site.iRunMode == theApp.enDemo )
	{	
		// Demo Test Time
		WaitForDummyTest( m.Site.dDemoTestTime * 1000. );

		//
		csCode.Format("%d", m.Site.iSiteDummyBinForCatorgy );
		TesterLog.csCode = csCode;
	}
	else
		; // Never be here.
}
void CThTester::FTResultInfo()
{
	// Show Code.
	CString csRunPageInfo = _T("");
	csRunPageInfo.Format("%s", theApp.m_tTester.TesterLog.csCode );
	m.Page.Run.m_wndTesting.SetWindowText( csRunPageInfo );

	// Show Code Color
	COLORREF color = f.GetCategoryColor(  theApp.m_tTester.TesterLog.csCode );
	m.Page.Run.m_wndTesting.SetNewBkColor( color );
	
	// Show Yield Control..
	m.Page.Run.m_ContinueFail.Add(color);
}
CString CThTester::SLTTcpIpTesting()
{
	CString csCode = _T("");




	return csCode;
}
void CThTester::SLTTesting()
{
	CString csCode = _T("");
	TesterLog.csCode = csCode;

	if( m.Site.iRunMode == theApp.enOnLine )
	{
		csCode.Format("%d", 0 );
		TesterLog.csCode = csCode;		
	}
	else if( m.Site.iRunMode == theApp.enOffLine )
	{
		csCode.Format("%d", 0 );
		TesterLog.csCode = csCode;
	}
	else if( m.Site.iRunMode == theApp.enDemo )
	{	
		// Demo Test Time
		WaitForDummyTest( m.Site.dDemoTestTime * 1000. );

		//
		csCode.Format("%d", m.Site.iSiteDummyBinForCatorgy );
		TesterLog.csCode = csCode;
	}
	else
		; // Never be here.
}
CString CThTester::TcpTesting()
{
	CString csManualMsg = _T("");

	// �o�̬O�� Cycle Tcp �I�s�Ϊ�
	CString csTcpBin = "-1";

	// Start�e Delay
	bool bIsPause = true;	// defaul for ok
	if( !FTGetWaitSendStartDelay() )
	{
		bIsPause = WaitSendStartDelay( m.m_InterfaceSetting.m_dSendStartDleay );
		FTSetWaitSendStartDelay( true );
	}

	// ��� Testing
	FTShowTesting();

	// ���e�X Start	
	CString csStart = _T("");
	csStart =  m.m_TcpipInterfaceSetting.m_csCmdHeader + 
		m.m_TcpipInterfaceSetting.m_csCmdReady + 
		m.m_TcpipInterfaceSetting.m_csCmdTailHeader;
	
	m.m_InterfaceTcp.SendTelegram( csStart );
	csManualMsg.Format("S: %s", csStart);
	ManualTestMessage( csManualMsg );

	
	int iStartTime = ::GetTickCount();
	while(1)
	{		
		if( m.m_TcpValue.gettcpstartRev )
		{
			m.m_TcpValue.gettcpstartRev = false;

			CString csTcpReady = m.m_TcpValue.tcpReady;
			csManualMsg.Format("R: %s", csTcpReady);
			ManualTestMessage( csManualMsg );
		}
		// wait for bin code get ok
		else if( m.m_TcpValue.gettcpBin )
		{
			m.m_TcpValue.gettcpBin = false;
			csTcpBin = m.m_TcpValue.tcpBin;

			//
			CString csTcpSource = _T("");
			csTcpSource = m.m_TcpValue.tcpBinSource;
			csManualMsg.Format("R: %s", csTcpSource);
			ManualTestMessage( csManualMsg );

			m.m_TcpValue.tcpBin = "";
			m.m_TcpValue.tcpBinSource = "";
			break;
		}
		else if ( (::GetTickCount() - iStartTime) >= ( m.m_TcpipInterfaceSetting.m_dCmdTimeout * 1000) )
		{
			m.m_TcpValue.tcpBin = "Timeout";
			csTcpBin = m.m_TcpValue.tcpBin;
			m.m_TcpValue.tcpBin = "";

			//
			m.m_TcpValue.gettcpstartRev = false;

			//
			csManualMsg.Format("Timeout");
			ManualTestMessage( csManualMsg );

			break;
		}
		else if(!m.Info.bRunning) 
		{			
			break;
			// �{���������F,�קK�{���d���b�o��
		}

		Sleep(1);
	}
	
	//
	csManualMsg.Format("Test end");
	ManualTestMessage( csManualMsg );

	m.m_TcpValue.gettcpBin = false;
	m.m_TcpValue.gettcpstart = false;
	m.m_TcpValue.tcpBin = "";

	return csTcpBin;
}
// 1.0Af
void CThTester::RemoteFunction(CString csRemoteCommand)
{

}
// 1.0Af
void CThTester::RepeatTrayCurrentTestICClear()
{
	CString csCurrentTestIC = _T("");
	csCurrentTestIC = "--";
	m.Page.Run.m_wndCurrentRepeatTrayStatus.SetWindowText( csCurrentTestIC );
}
void CThTester::RepeatTrayCurrentTestIC()
{
	CString csCurrentTestIC = _T("");

	// Tray
	CString csTray = _T("");
	if( TesterLog.iTray == theApp.enTray1 )
		csTray = "Tray1";
	else
		csTray = "Tray2";

	// IC
	CString csICLocation = _T("");
	int iBooking = TesterLog.iBooking;
	int iX = iBooking / m.TraySpec.Column;
	int iY = iBooking % m.TraySpec.Column;
	iX = iX+1;
	iY = iY+1;
	csICLocation.Format("(%d, %d)", iX, iY);

	// Show Information
	csCurrentTestIC.Format("%s, %s", csTray, csICLocation );
	m.Page.Run.m_wndCurrentRepeatTrayStatus.SetWindowText( csCurrentTestIC );
}
int CThTester::GetPassFailValue(CString csBin)
{
	/*
		iPF return 0 = Fail
		iPF return 1 = Pass
	*/

	int iPF = -1;

	//
	csBin.TrimLeft();
	csBin.TrimRight();

	//
	bool bOK = false;
	int iSize = m.BinMap.GetSize();
	for(int i=0;i<iSize;i++)
	{
		CString csCode = _T("");
		csCode = m.BinMap.GetAt(i).code;
		int iPassFail = m.BinMap.GetAt(i).pass;

		// find the code in BinMap
		if( csBin == csCode )
		{
			iPF = iPassFail;
			i = iSize;
			bOK = true;
		}
	}

	if(!bOK)
		iPF = 0;

	return iPF;
}

CString CThTester::RS232Testing()
{
	CString csManualMsg = _T("");

	// �o�̬O�� Cycle RS232 �I�s�Ϊ�
	CString csRS232Bin = "-1";

	// Start�e Delay
	bool bIsPause = true;	// defaul for ok
	if( !FTGetWaitSendStartDelay() )
	{
		bIsPause = WaitSendStartDelay( m.m_InterfaceSetting.m_dSendStartDleay );
		FTSetWaitSendStartDelay( true );
	}

	// ��� Testing
	FTShowTesting();

	// ���e�X Start
	CString csStart = "";
	csStart =  m.m_InterfaceSetting.m_csCmdHeader + 
		m.m_InterfaceSetting.m_csCmdReady + 
		m.m_InterfaceSetting.m_csCmdTailHeader;
	
	SendTelegram( csStart );
	csManualMsg.Format("Sed Sot: %s ", csStart);
	ManualTestMessage( csManualMsg );
	f.MessageCommunicationInfo( _DSend + csStart );
	
	// ���b�o�̨��R�O.
	CString csCommand = "";
#ifdef _Demo
	m_bSeralOpen = true;
#endif
	if( m_bSeralOpen )
	{
		int iStartTime = ::GetTickCount();
		while(1)	
		{
			char buff[1000] = {0};
			int read;
			read = m_Interface.GetString(buff);
			
			if(read > 0)
			{
				for(int i=0; i<read; i++)
					csCommand += buff[i];	// �o���

				csManualMsg.Format("Recv: %s", csCommand);
				ManualTestMessage( csManualMsg );

				f.CommLog( csManualMsg );
				f.MessageCommunicationInfo( _DRecv + csCommand );
			}

			int iStart = csCommand.Find( m.m_InterfaceSetting.m_csCmdHeader );			  // <<
			int iEnd = csCommand.Find(	m.m_InterfaceSetting.m_csCmdTailHeader, iStart);  // >>

			if (iStart == -1 || iEnd == -1) 
			{
				// �S�����.
				csManualMsg.Format("Recv: %s", csCommand);
				ManualTestMessage( csManualMsg );
			}	
			else
			{
				// �����N�B�z
				// �b�o�̳B�z�R�O	
				int HeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
				int TailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
	
				// ���o�u�����R�O
				CString csResult = "";
				csResult = csCommand.Mid(iStart + HeaderLength, iEnd - TailHeaderLength);
				
				// �B�z�R�O
				if( csResult == m.m_InterfaceSetting.m_csCmdStart )
				{
					// ���� Start
					// �e�X Go �����վ��}�l����.		
					CString csGo = "";
					csGo =  m.m_InterfaceSetting.m_csCmdHeader + 
						m.m_InterfaceSetting.m_csCmdGo + 
						m.m_InterfaceSetting.m_csCmdTailHeader;
					SendTelegram( csGo );					
					// ���e�X Start

					csManualMsg.Format("Send Go: %s", csGo);
					ManualTestMessage( csManualMsg );
					f.MessageCommunicationInfo( _DSend + csGo );

					// �� Start �M��
					int iHeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
					int iTailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
					int iStartLength = m.m_InterfaceSetting.m_csCmdStart.GetLength();
				
					int tLength = iHeaderLength + iTailHeaderLength + iStartLength;
					csCommand.Delete(0, tLength);
				}
				else if(0)
				{
				
				}
				else	
				{
					
					// ���� Bin Code = 
					// �B�z Bin Code
					CString c = "";
					c = csResult;
					
					int ic = c.Find( m.m_InterfaceSetting.m_csCmdBin, 0 );
					if( ic == -1 )
					{
						// ���O Bin Code. �o�O�L�ĩR�O
						
						//
						int iRemote1 = c.Find( "Remote:Temperature:Set=", 0 );
						int iRemote2 = c.Find( "Remote:Temperature:Meas?", 0 );
						int iRemote3 = c.Find( "Remote:Coord?", 0 );
						int iRemote4 = c.Find( "Remote:Temperature:Set?", 0 );
						
						if( iRemote1 != -1 )
						{
							CString csTempCommand = _T("");
							csTempCommand = "Remote:Temperature:Set=";
							CString csTemperature = _T("");
							int iTotalSize = c.GetLength();
							int iCommandSize = csTempCommand.GetLength();
							int iTemperatureSize = iTotalSize - iCommandSize;
							csTemperature = c.Right( iTemperatureSize );							
							
							double dNewTemperature = atof( csTemperature );
							if( dNewTemperature <= _MaxHeaterTemp && dNewTemperature >= _MinHeaterTemp )
							{
								CString csMsg = _T("");
								csMsg.Format( "Change Temperature To: %5.2f", dNewTemperature );
								f.MessageCommunicationInfo( _DRecv + csMsg );
								
								//
								long m_WestID = 0;
								m.m_DriveWest.AddCmd( m_WestID+1, enSV, dNewTemperature );
							}
							
							//
							int iHeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
							int iTailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
							int iRemote = c.GetLength();
							int tLength = iHeaderLength + iTailHeaderLength + iRemote;
							csCommand.Delete(0, tLength );
						}
						else if( iRemote2 != -1 )
						{
							// �^���ūשR�O (PV)
							double dPV[_MaxWestDevice];
							double dSV[_MaxWestDevice];
							m.m_DriveWest.GetValue( dPV, dSV );
							if( dPV[m.m_HandlerComPort.iPortWestHeaterID ] != _Device_Error )
							{
								CString csPV = _T("");
								CString csSV = _T("");
								csPV.Format("%5.2f", dPV[m.m_HandlerComPort.iPortWestHeaterID ] );
								csSV.Format("%5.2f", dSV[m.m_HandlerComPort.iPortWestHeaterID ] );
								
								//
								CString csTemperatureAck = "";
								csTemperatureAck =  m.m_InterfaceSetting.m_csCmdHeader + 
									csPV + 
									m.m_InterfaceSetting.m_csCmdTailHeader;
								SendTelegram( csTemperatureAck );
								
								//
								CString csMsg = _T("");
								csMsg.Format( "Feedback Temperature Is: %s", csTemperatureAck );
								f.MessageCommunicationInfo( _DSend + csMsg );
							}
							
							//
							int iHeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
							int iTailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
							int iRemote = c.GetLength();
							int tLength = iHeaderLength + iTailHeaderLength + iRemote;
							csCommand.Delete(0, tLength );
						}
						else if( iRemote3 != -1 )
						{
							// �^���y�ЩR�O
							CString csCoord = _T("");
							int iBooking = theApp.m_tTester.TesterLog.iBooking;
							int iTray = theApp.m_tTester.TesterLog.iTray; // 0->Tray1, 1->Tray2
							
							int iX = 0;
							int iY = 0;
							if( iBooking == -1 )
							{
								// Manual Testing
								iX = 0;
								iY = 0;
							}
							else
							{
								// Online 
								iX = iBooking / m.TraySpec.Column;
								iY = iBooking % m.TraySpec.Column;
								iX = iX+1;
								iY = iY+1;
							}
							csCoord.Format("%d:%d:%d", iTray, iX, iY );
							
							//
							CString csCoordAck = "";
							csCoordAck =  m.m_InterfaceSetting.m_csCmdHeader + 
								csCoord + 
								m.m_InterfaceSetting.m_csCmdTailHeader;
							SendTelegram( csCoordAck );
							
							//
							CString csMsg = _T("");
							csMsg.Format("Feedback Coord: %s", csCoordAck );
							f.MessageCommunicationInfo( _DSend + csMsg );
							
							//
							int iHeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
							int iTailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
							int iRemote = c.GetLength();
							int tLength = iHeaderLength + iTailHeaderLength + iRemote;
							csCommand.Delete(0, tLength );
						}
						else if( iRemote4 != -1 )
						{
							// �^���ūשR�O (SV)
							double dPV[_MaxWestDevice];
							double dSV[_MaxWestDevice];
							m.m_DriveWest.GetValue( dPV, dSV );
							
							CString csPV = _T("");
							CString csSV = _T("");
							csPV.Format("%5.2f", dPV[m.m_HandlerComPort.iPortWestHeaterID ] );
							csSV.Format("%5.2f", dSV[m.m_HandlerComPort.iPortWestHeaterID ] );
							
							//
							CString csTemperatureAck = "";
							csTemperatureAck =  m.m_InterfaceSetting.m_csCmdHeader + 
								csSV + 
								m.m_InterfaceSetting.m_csCmdTailHeader;
							SendTelegram( csTemperatureAck );
							//
							CString csMsg = _T("");
							csMsg.Format( "Feedback Temperature Is: %s", csTemperatureAck );
							f.MessageCommunicationInfo( _DSend + csMsg );
							
							//
							int iHeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
							int iTailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
							int iRemote = c.GetLength();
							int tLength = iHeaderLength + iTailHeaderLength + iRemote;
							csCommand.Delete(0, tLength );
						}
						else
						{
							//
							//
							int iHeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
							int iTailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
							int iRemote = c.GetLength();
							int tLength = iHeaderLength + iTailHeaderLength + iRemote;
							csCommand.Delete(0, tLength );
						}
					}
					else
					{
						// �o�O Bin Code �}�l�B�z�� Bin
						int iBinCodeHeaderLebgth = m.m_InterfaceSetting.m_csCmdBin.GetLength();
						int iBinCodeStart = csResult.Find( m.m_InterfaceSetting.m_csCmdBin, 0 );
						CString c;
						
						// ���o Bin Code ���_�l�I / �����S���N�q					
						// �� Bin Code Header ����. �ѤU���N�O Bin Code.
						CString code;
						code = csResult;
						code.Delete(0, iBinCodeHeaderLebgth );
						
						f.CommLog( code );
						
						csManualMsg.Format("Bin Value: %s", code);
						ManualTestMessage( csManualMsg );
						
						int iHeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
						int iTailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
						int iBinCodeLength = csResult.GetLength();
						int tLength = iHeaderLength + iTailHeaderLength + iBinCodeLength;
						csCommand.Delete(0, tLength );
						// ��B�z�L���R�O�q�r�ꤤ�R��
						
						csRS232Bin = code;
						// ���o Bin						
						
						break;
						// �o�� Bin Code �� break ���}�{��
					}
				}
			}
			

			// Timeout ����
			if ( (::GetTickCount() - iStartTime) >= ( m.m_InterfaceSetting.m_dCmdTimeout * 1000) )
			{
				f.CommLog("RS232 Timeout.!");
				csRS232Bin = "Timeout";
				//
				csManualMsg.Format("Timeout");
				ManualTestMessage( csManualMsg );
				break;
				// Timeout �� break ���}�{��		
			}
			else if(!m.Info.bRunning) 
			{
				break;
				// �{���������F, break ���}�{��
			}

			// �Y�ɧ�s�ɶ�
			UpdateTestTime(TestStartTime, TestOldTime);

			Sleep(1);
		}			
	}
	else
	{
		csRS232Bin = "";// Open RS232 Fail.!
		csManualMsg.Format("Com Port[%d] Fail", m.m_HandlerComPort.iPortTester );
		ManualTestMessage( csManualMsg );
	}

	csCommand = "";
	// �o�� Bin ��Ҧ��R�O���ᱼ.

	if( csCommand != "" )
	{
		// ��ᱼ���R�O�O�_��
	}
	csCommand = "";
	// �o�� Bin ��Ҧ��R�O���ᱼ.

	csManualMsg.Format("Test end");
	ManualTestMessage( csManualMsg );

	return csRS232Bin;
}
/*
CString CThTester::RS232Testing()
{
	CString csManualMsg = _T("");

	// �o�̬O�� Cycle RS232 �I�s�Ϊ�
	CString csRS232Bin = "-1";

	// Start�e Delay
	bool bIsPause = true;	// defaul for ok
	if( !FTGetWaitSendStartDelay() )
	{
		bIsPause = WaitSendStartDelay( m.m_InterfaceSetting.m_dSendStartDleay );
		FTSetWaitSendStartDelay( true );
	}

	// ��� Testing
	FTShowTesting();

	// ���e�X Start
	CString csStart = "";
	csStart =  m.m_InterfaceSetting.m_csCmdHeader + 
		m.m_InterfaceSetting.m_csCmdReady + 
		m.m_InterfaceSetting.m_csCmdTailHeader;
	
	SendTelegram( csStart );
	csManualMsg.Format("Sed Sot: %s ", csStart);
	ManualTestMessage( csManualMsg );
	f.MessageCommunicationInfo( _DSend + csStart );
	
	// ���b�o�̨��R�O.
	CString csCommand = "";
#ifdef _Demo
	m_bSeralOpen = true;
#endif
	if( m_bSeralOpen )
	{
		int iStartTime = ::GetTickCount();
		while(1)	
		{
			char buff[1000] = {0};
			int read;
			read = m_Interface.GetString(buff);
			
			if(read > 0)
			{
				for(int i=0; i<read; i++)
					csCommand += buff[i];	// �o���

				csManualMsg.Format("Recv: %s", csCommand);
				ManualTestMessage( csManualMsg );

				f.CommLog( csManualMsg );
				f.MessageCommunicationInfo( _DRecv + csCommand );
			}

#ifdef _Demo
			csCommand = "<<Remote!Coord>>";
#endif

			int iStart = csCommand.Find( m.m_InterfaceSetting.m_csCmdHeader );			  // <<
			int iEnd = csCommand.Find(	m.m_InterfaceSetting.m_csCmdTailHeader, iStart);  // >>

			if (iStart == -1 || iEnd == -1) 
			{
				// �S�����.
				csManualMsg.Format("Recv: %s", csCommand);
				ManualTestMessage( csManualMsg );
			}	
			else
			{
				// �����N�B�z
				// �b�o�̳B�z�R�O	
				int HeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
				int TailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
	
				// ���o�u�����R�O
				CString csResult = "";
				csResult = csCommand.Mid(iStart + HeaderLength, iEnd - TailHeaderLength);
				
				// �B�z�R�O
				if( csResult == m.m_InterfaceSetting.m_csCmdStart )
				{
					// ���� Start
					// �e�X Go �����վ��}�l����.		
					CString csGo = "";
					csGo =  m.m_InterfaceSetting.m_csCmdHeader + 
						m.m_InterfaceSetting.m_csCmdGo + 
						m.m_InterfaceSetting.m_csCmdTailHeader;
					SendTelegram( csGo );					
					// ���e�X Start

					csManualMsg.Format("Send Go: %s", csGo);
					ManualTestMessage( csManualMsg );
					f.MessageCommunicationInfo( _DSend + csGo );

					// �� Start �M��
					int iHeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
					int iTailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
					int iStartLength = m.m_InterfaceSetting.m_csCmdStart.GetLength();
				
					int tLength = iHeaderLength + iTailHeaderLength + iStartLength;
					csCommand.Delete(0, tLength);
				}
				else if(0)
				{
				
				}
				else	
				{
					// ���� Bin Code = 
					// �B�z Bin Code
					CString c = "";
					c = csResult;
					int ic = c.Find( m.m_InterfaceSetting.m_csCmdBin, 0 );
					if( ic == -1 )
					{
						// ���O Bin Code. �o�O�L�ĩR�O

						//
						int iRemote1 = c.Find( "Remote!Temperature=", 0 );
						int iRemote2 = c.Find( "Remote!Temperature?", 0 );
						int iRemote3 = c.Find( "Remote!Coord?", 0 );
						if( iRemote1 != -1 )
						{
							CString csTempCommand = _T("");
							csTempCommand = "Remote!Temperature=";
							CString csTemperature = _T("");
							int iTotalSize = c.GetLength();
							int iCommandSize = csTempCommand.GetLength();
							int iTemperatureSize = iTotalSize - iCommandSize;
							csTemperature = c.Right( iTemperatureSize );							

							double dNewTemperature = atof( csTemperature );
							if( dNewTemperature <= _MaxHeaterTemp && dNewTemperature >= _MinHeaterTemp )
							{
								CString csMsg = _T("");
								csMsg.Format( "Change Temperature To: %5.2f", dNewTemperature );
								f.MessageCommunicationInfo( _DRecv + csMsg );

								//
								long m_WestID = 0;
								m.m_DriveWest.AddCmd( m_WestID+1, enSV, dNewTemperature );
							}

							//
							int iHeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
							int iTailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
							int iRemote = c.GetLength();
							int tLength = iHeaderLength + iTailHeaderLength + iRemote;
							csCommand.Delete(0, tLength );
						}
						else if( iRemote2 != -1 )
						{
							// �^���ūשR�O
							double dPV[_MaxWestDevice];
							double dSV[_MaxWestDevice];
							m.m_DriveWest.GetValue( dPV, dSV );
							if( dPV[m.m_HandlerComPort.iPortWestHeaterID ] != _Device_Error )
							{
								CString csPV = _T("");
								CString csSV = _T("");
								csPV.Format("%5.2f", dPV[m.m_HandlerComPort.iPortWestHeaterID ] );
								csSV.Format("%5.2f", dSV[m.m_HandlerComPort.iPortWestHeaterID ] );

								//
								CString csTemperatureAck = "";
								csTemperatureAck =  m.m_InterfaceSetting.m_csCmdHeader + 
									csPV + 
									m.m_InterfaceSetting.m_csCmdTailHeader;
								SendTelegram( csTemperatureAck );

								//
								CString csMsg = _T("");
								csMsg.Format( "Feedback Temperature Is: %s", csTemperatureAck );
								f.MessageCommunicationInfo( _DSend + csMsg );
							}

							//
							int iHeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
							int iTailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
							int iRemote = c.GetLength();
							int tLength = iHeaderLength + iTailHeaderLength + iRemote;
							csCommand.Delete(0, tLength );
						}
						else if( iRemote3 != -1 )
						{
							// �^���y�ЩR�O
							CString csCoord = _T("");
							int iBooking = theApp.m_tTester.TesterLog.iBooking;
							int iTray = theApp.m_tTester.TesterLog.iTray; // 0->Tray1, 1->Tray2

							int iX = 0;
							int iY = 0;
							if( iBooking == -1 )
							{
								// Manual Testing
								iX = 0;
								iY = 0;
							}
							else
							{
								// Online 
								iX = iBooking / m.TraySpec.Column;
								iY = iBooking % m.TraySpec.Column;
								iX = iX+1;
								iY = iY+1;
							}
							csCoord.Format("%d:%d:%d", iTray, iX, iY );

							//
							CString csCoordAck = "";
							csCoordAck =  m.m_InterfaceSetting.m_csCmdHeader + 
								csCoord + 
								m.m_InterfaceSetting.m_csCmdTailHeader;
							SendTelegram( csCoordAck );

							//
							CString csMsg = _T("");
							csMsg.Format("Feedback Coord: %s", csCoordAck );
							f.MessageCommunicationInfo( _DSend + csMsg );
						}

						//
						int iHeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
						int iTailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
						int iRemote = c.GetLength();
						int tLength = iHeaderLength + iTailHeaderLength + iRemote;
						csCommand.Delete(0, tLength );					
					}
					else
					{
						// �o�O Bin Code �}�l�B�z�� Bin
						int iBinCodeHeaderLebgth = m.m_InterfaceSetting.m_csCmdBin.GetLength();
						int iBinCodeStart = csResult.Find( m.m_InterfaceSetting.m_csCmdBin, 0 );
						CString c;

						// ���o Bin Code ���_�l�I / �����S���N�q					
						// �� Bin Code Header ����. �ѤU���N�O Bin Code.
						CString code;
						code = csResult;
						code.Delete(0, iBinCodeHeaderLebgth );

						f.CommLog( code );

						csManualMsg.Format("Bin Value: %s", code);
						ManualTestMessage( csManualMsg );

						int iHeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
						int iTailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
						int iBinCodeLength = csResult.GetLength();
						int tLength = iHeaderLength + iTailHeaderLength + iBinCodeLength;
						csCommand.Delete(0, tLength );
						// ��B�z�L���R�O�q�r�ꤤ�R��

						csRS232Bin = code;
						// ���o Bin
						
						break;
						// �o�� Bin Code �� break ���}�{��
					}
				}
			}

			// Timeout ����
			if ( (::GetTickCount() - iStartTime) >= ( m.m_InterfaceSetting.m_dCmdTimeout * 1000) )
			{
				f.CommLog("RS232 Timeout.!");
				csRS232Bin = "Timeout";
				//
				csManualMsg.Format("Timeout");
				ManualTestMessage( csManualMsg );
				break;
				// Timeout �� break ���}�{��		
			}
			else if(!m.Info.bRunning) 
			{
				break;
				// �{���������F, break ���}�{��
			}

			// �Y�ɧ�s�ɶ�
			UpdateTestTime(TestStartTime, TestOldTime);

			Sleep(1);
		}			
	}
	else
	{
		csRS232Bin = "";// Open RS232 Fail.!
		csManualMsg.Format("Com Port[%d] Fail", m.m_HandlerComPort.iPortTester );
		ManualTestMessage( csManualMsg );
	}

	csCommand = "";
	// �o�� Bin ��Ҧ��R�O���ᱼ.

	if( csCommand != "" )
	{
		// ��ᱼ���R�O�O�_��
	}
	csCommand = "";
	// �o�� Bin ��Ҧ��R�O���ᱼ.

	csManualMsg.Format("Test end");
	ManualTestMessage( csManualMsg );

	return csRS232Bin;
}
*/
// 1.0Af
// Remove this function and re-build new one
/*
CString CThTester::RS232Testing()
{
	CString csManualMsg = _T("");

	// �o�̬O�� Cycle RS232 �I�s�Ϊ�
	CString csRS232Bin = "-1";

	// Start�e Delay
	bool bIsPause = true;	// defaul for ok
	if( !FTGetWaitSendStartDelay() )
	{
		bIsPause = WaitSendStartDelay( m.m_InterfaceSetting.m_dSendStartDleay );
		FTSetWaitSendStartDelay( true );
	}

	// ��� Testing
	FTShowTesting();

	// ���e�X Start
	CString csStart = "";
	csStart =  m.m_InterfaceSetting.m_csCmdHeader + 
		m.m_InterfaceSetting.m_csCmdReady + 
		m.m_InterfaceSetting.m_csCmdTailHeader;
	
	SendTelegram( csStart );
	csManualMsg.Format("Sed Sot: %s ", csStart);
	ManualTestMessage( csManualMsg );
	f.MessageCommunicationInfo( _DSend + csStart );
	
	// ���b�o�̨��R�O.
	CString csCommand = "";
#ifdef _Demo
	m_bSeralOpen = true;
#endif
	if( m_bSeralOpen )
	{
		int iStartTime = ::GetTickCount();
		while(1)	
		{
			char buff[1000] = {0};
			int read;
			read = m_Interface.GetString(buff);			
			if(read > 0)
			{
				for(int i=0; i<read; i++)
					csCommand += buff[i];	// �o���

				csManualMsg.Format("Recv: %s", csCommand);
				ManualTestMessage( csManualMsg );

				f.CommLog( csManualMsg );
				f.MessageCommunicationInfo( _DRecv + csCommand );
			}
			
			int iStart = csCommand.Find( m.m_InterfaceSetting.m_csCmdHeader );			  // <<
			int iEnd = csCommand.Find(	m.m_InterfaceSetting.m_csCmdTailHeader, iStart); // >>

			if (iStart == -1 || iEnd == -1) 
			{
				// �S�����.
				csManualMsg.Format("Recv: %s", csCommand);
				ManualTestMessage( csManualMsg );
			}	
			else
			{
				// �����N�B�z
				// �b�o�̳B�z�R�O	
				int HeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
				int TailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
	
				// ���o�u�����R�O
				CString csResult = "";
				csResult = csCommand.Mid(iStart + HeaderLength, iEnd - TailHeaderLength);
				
				// �B�z�R�O
				if( csResult == m.m_InterfaceSetting.m_csCmdStart )
				{
					// ���� Start
					// �e�X Go �����վ��}�l����.		
					CString csGo = "";
					csGo =  m.m_InterfaceSetting.m_csCmdHeader + 
						m.m_InterfaceSetting.m_csCmdGo + 
						m.m_InterfaceSetting.m_csCmdTailHeader;
					SendTelegram( csGo );					
					// ���e�X Start

					csManualMsg.Format("Send Go: %s", csGo);
					ManualTestMessage( csManualMsg );
					f.MessageCommunicationInfo( _DSend + csGo );

					// �� Start �M��
					int iHeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
					int iTailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
					int iStartLength = m.m_InterfaceSetting.m_csCmdStart.GetLength();
				
					int tLength = iHeaderLength + iTailHeaderLength + iStartLength;
					csCommand.Delete(0, tLength);
				}
				else	
				{
					// ���� Bin Code = 
					// �B�z Bin Code
					CString c = "";
					c = csResult;
					int ic = c.Find( m.m_InterfaceSetting.m_csCmdBin, 0 );
					if( ic == -1 )
					{
						// ���O Bin Code. �o�O�L�ĩR�O
					}
					else
					{
						// �o�O Bin Code �}�l�B�z�� Bin
						int iBinCodeHeaderLebgth = m.m_InterfaceSetting.m_csCmdBin.GetLength();
						int iBinCodeStart = csResult.Find( m.m_InterfaceSetting.m_csCmdBin, 0 );
						CString c;

						// ���o Bin Code ���_�l�I / �����S���N�q					
						// �� Bin Code Header ����. �ѤU���N�O Bin Code.
						CString code;
						code = csResult;
						code.Delete(0, iBinCodeHeaderLebgth );

						f.CommLog( code );

						csManualMsg.Format("Bin Value: %s", code);
						ManualTestMessage( csManualMsg );

						int iHeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
						int iTailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
						int iBinCodeLength = csResult.GetLength();
						int tLength = iHeaderLength + iTailHeaderLength + iBinCodeLength;
						csCommand.Delete(0, tLength );
						// ��B�z�L���R�O�q�r�ꤤ�R��

						csRS232Bin = code;
						// ���o Bin
						
						break;
						// �o�� Bin Code �� break ���}�{��
					}
				}
			}

			// Timeout ����
			if ( (::GetTickCount() - iStartTime) >= ( m.m_InterfaceSetting.m_dCmdTimeout * 1000) )
			{
				f.CommLog("RS232 Timeout.!");
				csRS232Bin = "Timeout";
				//
				csManualMsg.Format("Timeout");
				ManualTestMessage( csManualMsg );
				break;
				// Timeout �� break ���}�{��		
			}
			else if(!m.Info.bRunning) 
			{
				break;
				// �{���������F, break ���}�{��
			}

			// �Y�ɧ�s�ɶ�
			UpdateTestTime(TestStartTime, TestOldTime);

			Sleep(1);
		}			
	}
	else
	{
		csRS232Bin = "";// Open RS232 Fail.!
		csManualMsg.Format("Com Port[%d] Fail", m.m_HandlerComPort.iPortTester );
		ManualTestMessage( csManualMsg );
	}

	csCommand = "";
	// �o�� Bin ��Ҧ��R�O���ᱼ.

	if( csCommand != "" )
	{
		// ��ᱼ���R�O�O�_��
	}
	csCommand = "";
	// �o�� Bin ��Ҧ��R�O���ᱼ.

	csManualMsg.Format("Test end");
	ManualTestMessage( csManualMsg );

	return csRS232Bin;
}
*/
void CThTester::SendTelegram(CString cs)
{
	if(cs.GetLength() > 0 )
		m_Interface.WriteString(cs.GetBuffer(0), cs.GetLength());
}
bool CThTester::InitValue()
{
	ReSizeYieldLimit( m.YieldSetting.iYieldWindow );	// Init Yield Control
	return true;
}

void CThTester::ClearTesterLog()
{
	TesterLog.csCode = "";
	TesterLog.iBin = -1;
	TesterLog.iSetTemperature = -1;
	TesterLog.iBooking = -1;
	TesterLog.dTestTime = 0.0;
	TesterLog.bError = false;
	TesterLog.iTray = -1;
	TesterLog.iPF = -1;
	// Clear information.
}

void CThTester::NextStatus()
{

	// here for change status
	switch(m_bStatus)
	{
	case enInitialize:
		m_bStatus = enIdle;
		break;
	case enIdle:
		{
			if( m.InterLock.TestingGo )
			{
				m.InterLock.TestingGo	= false;
				m.InterLock.TestingOK	= false;
				m.InterLock.Testing		= true;

				m_bStatus = enTestStart;
			}
			else
				m_bStatus = enIdle;
		}
		break;
	///////////////////////////////
	// Cycle 
	case enTestStart:			// Start Testing
		f.CWinMessage( "Arm:enTestStart", theApp.enDTester );
		{
//			m_bStatus = enSLTTestStart;
			m_bStatus = enFTTestStart;
		}
		break;
	///////////////////////////////
	// SLT
	case enSLTTestStart:		// SLT Test Start
		f.CWinMessage( "Arm:enSLTTestStart", theApp.enDTester );
		{
			m_bStatus = enSLTTesting;
		}
		break;
	case enSLTTesting:			// SLT Testing 
		f.CWinMessage( "Arm:enSLTTesting", theApp.enDTester );
		{
			m_bStatus = enSLTTestEnd;
		}
		break;
	case enSLTTestEnd:			// SLT Test End
		f.CWinMessage( "Arm:enSLTTestEnd", theApp.enDTester );
		{
			m_bStatus = enIdle;

			//
			theApp.m_tInserter.TestSiteLog = theApp.m_tTester.TesterLog;
			theApp.m_tTester.ClearTesterLog();

			// Testi OK
			m.InterLock.TestingOK = true;
		}
		break;
	///////////////////////////////
	// FT
	case enFTTestStart:			// FT Test Start
		f.CWinMessage( "Arm:enFTTestStart", theApp.enDTester );
		{
			m_bStatus = enFTTesting;
		}
		break;
	case enFTTesting:			// FT Testing
		f.CWinMessage( "Arm:enFTTesting", theApp.enDTester );
		{
			m_bStatus = enFTTestEnd;
		}
		break;
	case enFTTestEnd:			// FT Test End
		f.CWinMessage( "Arm:enFTTestEnd", theApp.enDTester );
		{
			m_bStatus = enIdle;

			//
			theApp.m_tInserter.TestSiteLog = theApp.m_tTester.TesterLog;
			theApp.m_tTester.ClearTesterLog();

			// Testi OK
			m.InterLock.TestingOK = true;		
		}
		break;
	}
}

void CThTester::Wait(int msec)
{
	int iStart = 0;
	iStart = ::GetTickCount();
	while(1)
	{
		if((int)::GetTickCount() - iStart > msec)
			break;		
		if ( f.IsPause() )
			break;
		if (!m.Info.bRunning)
			break;

		Sleep(_Wait);
	}
}

void CThTester::ReSizeYieldLimit(int LimitSize)
{
	if( LimitSize <0 )
		return;
	
	if( m_YieldLimit != NULL )
	{
		delete m_YieldLimit;
		m_YieldLimit = NULL;
	}
	// �קK�����D, ���⥦ NULL �M��A delete

	m_YieldLimit = new int[LimitSize];

	for(int i = 0; i<LimitSize; i++ )
		m_YieldLimit[i] = -1;
}
void CThTester::UpdateTestedIC()
{
	m.UPH.ICTested++;
}
// �N���ծɶ��קאּ �Y�����
void CThTester::InitTestStartTime()	
{
	TestOldTime = 0;
	TestInOldTime = 0;
	TestStartTime = ::GetTickCount();	// ���}�l���ծɶ�
}
void CThTester::ResetFinalTestTime()	
{
	if( m.Site.iRunMode == theApp.enDemo || m.Site.iRunMode == theApp.enOffLine )
	{
		// ���ի�..�p�G�O Demo. OffLine �N����ծɶ���ܬ��]�w�ƭ�
		// ���M�Ȥ�|ı�o�ܩ_��...
		CString csTestTime;
		double TestTime = m.Site.dDemoTestTime;
		csTestTime.Format("%5.2f", TestTime );
		
		m.Page.Run.m_wndTestTime.SetWindowText( csTestTime );
	}
}
void CThTester::ResetTestTime()	
{								
	// ���իe�N���ղM�� 0 
	CString csTestTime = _T("");
	double TestTime = 0.0;
	csTestTime.Format("%5.2f", TestTime );

	m.Page.Run.m_wndTestTime.SetWindowText( csTestTime );
}
void CThTester::UpdateTestTime(int iStartTime, double iOldTime )
{	
	// �Y�ɴ��ծɶ�
	double TestTime = 0.0;
	TestTime = ((::GetTickCount() - iStartTime) / 1000. );
	TestOldTime = TestTime;
	TestInOldTime = TestInOldTime + ( TestTime - iOldTime );
	CString csTestTime;
	csTestTime.Format("%5.2f", TestTime );
	
	if( ( TestInOldTime ) > _UpdataTestTime )
	{
		TestInOldTime = 0;
		// Test Time ��ܰ{�{.
		CRect rct;
		m.Page.Run.m_wndTestTime.GetWindowRect( &rct );
		m.Page.Run.m_wndTestTime.InvalidateRect( rct , FALSE );
		m.Page.Run.m_wndTestTime.SetWindowText( csTestTime );		
	}
}
void CThTester::WaitForDummyTest(int mesc)
{
	int iStart = 0;
	iStart = ::GetTickCount();			// �Ψӭp��i���i�H���X�j�� ( �}�l�ɶ��M Dummy Test Time ��� )
	while(1)
	{
		if((int)::GetTickCount() - iStart > mesc)
			break;		
		if ( f.IsPause() )
			break;
		if (!m.Info.bRunning)
			break;

		// Demo / Offline �]�n�i�H�Y����ܴ��ծɶ�.!
		UpdateTestTime(TestStartTime, TestOldTime);

		Sleep(_Wait);
	}
}
void CThTester::ManualTestMessage(CString csMsg)
{
	CString cs = _T("");
	csMsg.TrimLeft();
	csMsg.TrimRight();
	cs = csMsg;
	if( theApp.m_DlgTesting->GetSafeHwnd() != NULL )
	{
		::SendMessage( theApp.m_DlgTesting->GetSafeHwnd(), 
			WM_MANUAL_TEST_MSG,  (WPARAM)&cs , (LPARAM)&cs );
	}
}
int CThTester::ExitInstance()
{
	TRACE("CThTester\n");
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThTester, CWinThread)
	//{{AFX_MSG_MAP(CThTester)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThTester message handlers

void CThTester::FTTestingRemoteMode()
{
	

	//SOT
	ps.SendEvent();

	// Clear TestResult
	ps.SetTestResult("");

	CString csCode = _T("");
	//TESTRESULT
	while(1)
	{
		if(m.m_rTestResilt.m_bResultReady)
		{
			ps.GetTestResult(csCode);
				break;

			//
			if( csCode != "" )
				break;
		}


		if(!m.Info.bRunning)
			break;
		
		Sleep(1);
	}

	TesterLog.csCode = csCode;
}
