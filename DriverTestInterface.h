// DriverTestInterface.h: interface for the CDriverTestInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRIVERTESTINTERFACE_H__950CE285_B2D9_4C24_A50D_D359AEC12A97__INCLUDED_)
#define AFX_DRIVERTESTINTERFACE_H__950CE285_B2D9_4C24_A50D_D359AEC12A97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Interface Layer
#include "DriverTestInterfaceTCP.h"

// Message
#define _STX		"<<"
#define _ETX		">>"
#define _MTX		"%"
#define _STDONE		" DONE"
#define _STERROR	" ERROR"
#define _STOK		" OK"


#define _CMTX		","

// Coordnation, Tray
#define _MaxCol		50
#define _MaxRow		50

// Self Software Parameter
#define _ModelName	"3111"

// Log
#define _RemoteRawLog	"ProtocolRawLog.log"
#define _RemoteLog		"ProtocolLog.log"

//
typedef struct tagRemoteCommand {
	int m_iRemoteCommandID;
	CString m_csRemoteCommandName;
	CString m_csRemoteFunction;
} tagRemoteCommand;

typedef struct tagRemoteCommandList{
	CArray< tagRemoteCommand, tagRemoteCommand > m_RemoteCommand;
} tagRemoteCommandList;

typedef struct tagRemoteLotInfo {
	int iFiled;
	CString csLotInfo;
} tagRemoteLotInfo;

// �R�O
typedef struct tagTestProtocol
{
	int site;				// site 1, igone
	CString csSite;			// site 1, igone
	CString cmd;			// tempetature, coordnation
	CString parameter;		//
} tagTestProtocol;

// Rotator �Ҧ�
enum RotatorMode {
	enRotatorModeN				= 0,	// -90
	enRotatorModeP				= 1,	// +90
	enRotatorModeZ				= 2,	// 0
	enRotatorModeU				= 3,	// 180
};

// Lot ���
enum LotField {
	enLotFieldLotNo				= 0,
	enLotFieldMachineNo			= 1,
	enLotFieldOperatorID		= 2,
	enLotFieldDeviceID			= 3,
	enLotFieldProgramID			= 4,
};

// Tray ����
enum RemoteTrayMode {
	enCmdTray1					= 0,	// Tray1
	enCmdTray2					= 1,	// Tray2
};

// �^�_�R�O
enum RemoteReturnCmd
{
	enReturnCodeConnect					= 0,
	enReturnCodeDisconnect				= 1,
	enReturnVersion						= 2,
	enReturnGetTemp						= 3,
	enReturnGetSetTemp					= 4,
	enReturnSetTemp						= 5,
	enReturnEnableTemp					= 6,
	enReturnGetStatus					= 7,
	enReturnEnableRotator				= 8,
	enReturnChangeRotatorStatus			= 9,
	enReturnChangeRotator				= 10,
	enReturnSetCoordnation				= 11,
	enReturnGetCoordnation				= 12,
	enReturnCCDLogIC					= 13,
	enReturnErrMessage					= 14,
	enReturnAutoSkip					= 15,
	enReturnGetAutoSkip					= 16,
	enReturnGetTraySpec					= 17,
	enReturnSetCoordnationGo			= 18,
	enReturnSetCoordnationDone			= 19,
	enReturnSetCoordnationReturn		= 20,
	enReturnSetCoordnationReturnDone	= 21,
	enReturnSetCoordnationClearGo		= 22,
	enReturnGetAirPressure				= 23,
	enReturnSetAirPressure				= 24,
	enReturnSetState					= 25,
	enReturnGetState					= 26,
	enReturnGetHelp						= 27,
	enReturnSetStateInitial				= 28,
	enReturnSetStateStart				= 29,
	enReturnSetStateStop				= 30,
	enReturnSetStateRetry				= 31,
	enReturnSetStateSkip				= 32,
	enReturnSetStateReset				= 33,
	enReturnSetStateOneCycle			= 34,
	enReturnSetStateErrorCtrl			= 35,
	enReturnSetError					= 36,
	enReturnSetCoordnationGoError		= 37,
	enReturnSetCoordnationReturnError	= 38,
	enReturnSetRunMode					= 39,
	enReturnGetRunMode					= 40,
	enReturnSetTsVacc					= 41,
	enReturnGetTsVacc					= 42,
	enReturnSetLotDone					= 43,
	enReturnSetNewLot					= 44,
	enReturnGetLotNo					= 45,
	enReturnSetLotNo					= 46,
	enReturnGetMachineNo				= 47,
	enReturnSetMachineNo				= 48,
	enReturnGetOperationID				= 49,
	enReturnSetOperationID				= 50,
	enReturnGetDeviceID					= 51,
	enReturnSetDeviceID					= 52,
	enReturnGetProgramID				= 53,
	enReturnSetProgramID				= 54,
};

// �]�w���A
enum RemoteSetState
{
	enSetStateInitial					= 0,
	enSetStateStart						= 1,
	enSetStateStop						= 2,
	enSetStateOneCycle					= 3,
	enSetStateReset						= 4,
	enSetStateRetry						= 5,
	enSetStateSkip						= 6,
};

// �]�w���A
enum RemoteCommandSetStatus
{
	enRemoteCommandStatusOK				= 0,
	enRemoteCommandStatusError			= 1,
	enRemoteCommandStatusInitial		= 2,
	enRemoteCommandStatusGo				= 3,
};

class CDriverTestInterface  
{
private:
	HANDLE	m_hComm;

	bool m_bInSocket;			// �O�_�b Socket ��, ��ܱ��U�Ӫ����~�u��� Tester �߰�, ����D�ʵo�X
	bool m_bReturnError;		// �O�_�o�͹L���~, �p�G�O��ܤU�� Start �O�_�k, �������� return

public:

	// �إ߳B�z�R�O
	void InitTestInterfaceExcute();

	// 1.0Ao
	// TCP/IP
	CDriverTestInterfaceTCP	m_TesterInterfaceTcp;
	bool OpenTCP(int iPort);
	void CloseTCP();
	void GetEthernet(CString &csEthernetIP, CString &csEthernetPort);
	void CloseReadTCP();
	void CloseWriteTCP();
	CArray< CString, CString > m_SendTCPCmd;

	//
	// �إ߳s�u
	void InitTestInterfaceTCP();	

	//
	// TCP ���쪺�T�����|���s�b�o
	CString csTCPBuffer;
	void ReadTCP();
	void WriteTCP();

	// ���������
	HANDLE hProcessWriteTCP;
	HANDLE hProcessReadTCP;

	static UINT ThreadTestInterfaceWriteTCP(LPVOID p);
	static UINT ThreadTestInterfaceReadTCP(LPVOID p);

	// 1.0Ap
	HANDLE hProcessExcute;
	void CloseExcute();
	static UINT ThreadTestInterfaceExcute(LPVOID p);

public:
	
	struct tagRemoteReturnCmd {
		CString csConnect;
		CString csDisconnect;
		CString csVersion;
	} m_RemoteReturnCmd;
	
	struct tagRemoteCoord {
		int iCol;
		int iRow;
		int iTray;
	} m_RemoteTray;
	
public:
	CString CommandRun(tagTestProtocol  telegram);//
	tagRemoteCommandList m_RemoteCommandList;

public:
	CDriverTestInterface();
	virtual ~CDriverTestInterface();

	// Debug
	void RemoteCommMsgCmd(CString csMsg = _T(""));				// �e�X
	void RemoteRawMsg(CString csMsg = _T(""));					// ����
	void RemoteSendMsdCmd(CString csMsg = _T(""));				// 
	void RemoteCommAddBuffer(CString csSimBuffer = _T(""));		//
	CString m_csSimBuffer;
	
	//
	CArray< tagTestProtocol, tagTestProtocol > m_ReviceCmd;
	CArray< CString, CString > m_SendCmd;

	// �إ� Link
	bool Open(int iPort, int iBaudRate = 9600); // 115200
	bool SetOpen(HANDLE m_hCommOther);

	// ���o��T
	int m_iBaudRate;
	void GetBaudRate(int &BaudRate);

	// �إߩR�O
	void InitCommandSetup();

	// Ū�g�R�O
	void Read();
	void AddReadCmd(tagTestProtocol tagReadCmd);
	void Write();
	void AddReplyCmd(CString csReplyCmd, bool bAddCommand = true);

	// ����R�O
	void ProcessCommand();

	// �����R�O
	void GetReturnCommand(tagTestProtocol msg, CString &csReturnCmd, int &iReturnCode, bool &bNeedReturn);
	void GetSendCommand(int iCode, CString &csSendCmd, CString csExtMsg = _T("") );
	bool GetReadyCommand(CString &csNoReadyReason );
	bool GetReadyReturnCommand(CString &csNoReturnReason );

	/*
	�p�G�n�ܧ�R�O�榡, �b GetReturnCommand �ܧ�^�_�R�O
						�b GetSendCommand �ܧ�D�ʳq���R�O
	*/

	// RS232 ���쪺�T�����|���s�b�o
	CString csBuffer;

	// �إ�/�P�Ѱ�
	bool InitTestInterface(int iPort);
	void CloseWrite();
	void CloseRead();
	bool Close();

	// ���������
	HANDLE hProcessWrite;
	HANDLE hProcessRead;

	// �����
	static UINT ThreadTestInterfaceWrite(LPVOID p);
	static UINT ThreadTestInterfaceRead(LPVOID p);

	//
	tagTestProtocol GetProtocol(CString &cs);

	//
	bool m_bRemoteMode;						// �O�_�� Remote Mode
	bool GetRemoteMode();					// �^�ǬO�_�� Remote Mode ( �O�_���s���W )
	void SetRemoteMode(bool bRemote);		// �]�w�O�_�� Remote Mode

	// �O�_�n�ǰe Event
	bool m_bRemoteSendEvent;


	// �O�_�b PurgeDevice
	bool m_bRemotePurgeDevices;


	// �O�_�n���� //�i�H�]�w����
	int m_bRemoteRetest;

public:

	// �O���q�T
	CString m_csLogPath;
	void SetLogPath(CString csPath = _T(""));
	CString GetLogPath();
	void LogRaw(CString csLog = _T(""));
	void Log(CString csLog = _T(""));

	// �O���ثe Interface Status
	int m_MachineStatus;									// 0 for normal ready status
	int m_MachineStatusCode;								// 0 for normal ready code

public:

	// �����M�ΩR�O(��������ʧ@/����)
	CString SetStatus(int iStatus, int iCode);				// �]�w �ثe�����A (Remote)
	CString GetStatus(int &iStatus, int &iCode);			// ���o �ثe�����A (Remote)
	CString GetStatusContent();								// ���o�ثe�t�Ϊ��A���y�z
	CString GetTempMaxMin(double &dMax, double &dMin );		// ���o�t�γ̰��̧C�ŭ���
	CString GetTorqueMaxMin(double &dMax, double &dMin);	// ���o�t�γ̰��̧C���O����
	CString GetProgramVersion();							// ���o����
	CString GetSiteTemp();									// ���o�ū�
	CString GetSiteSetTemp();								// ���o�]�w�ū�
	CString SetSiteTemp(double dTemp);						// �]�w�ū�
	CString EnableTemp(bool bEnable);						// �Ұʷū�
	CString GetSystemStatus();								// ���o�t�Ϊ��A
	CString EnableRotator(bool bEnable);					// �]�w�O�_�ϥ� Rotator
	CString SetRotator(int iDegree);						// �]�w Rotator ����
	CString GetRotator(int &iDegree);						// ���o Rotator ����
	CString SetErrorMessage(int iCode, CString csMsg);		// �]�w ErrorMessage (Code)
	CString EnableCCDLogIC(bool bEnable);					// �]�w�Ұ�CCD�O�� IC
	CString SetCoord(int iTray, int iX, int iY);			// �]�w Coordnation
	CString GetCoord(int &iTray, int &iX, int &iY);			// ���o Coordnation
	CString GetTraySpec(int &iCol, int &iRow);				// ���o TraySpec
	CString SetAutoSkip(bool bEnable);						// �]�w AutoSkip ���A
	CString GetAutoSkip(bool &bEnable);						// ���o Auto Skip ���A
	CString SetTsVacc(bool bEnable);						// �]�w Test Site vacc ���A
	CString GetTsVacc(bool &bEnable);						// ���o Test Site vacc ���A
	CString SetCoordnationDone();							// �]�w Coordnation ���\ (IC in socket)
	CString SetCoordnationReturnDone();						// �]�w�k�� IC ���\ (Error Skip �]�|�]�w)
	CString SetStateInitialDone();							// �]�w Initial Done
	CString SetStateRetryDone();							// �]�w Retry Done
	CString SetStateSkipDone();								// �]�w Skip Done
	CString SetStateStartDone();							// �]�w Start Done
	CString SetStateStopDone();								// �]�w Stop Done
	CString SetStateResetDone();							// �]�w Reset Done
	CString SetStateOneCycleDone();							// �]�w OneCycle Done
	CString SetStateErrorCtrlDone();						// �]�w ErrorCtrl Done
	CString SetStateError();								// �]�w Error
	CString SetAirPressure(double dAirPressure);			// �]�w Air Pressure �ƭ�
	CString GetAirPressure(double &dAirPressure);			// ���o Air Pressure �ƭ�
	CString GetHelpFile(CString &csHelpFile);				// ���o Help File �r��
	CString SetButtonInitial();								// �]�w Button Initial
	CString SetButtonStart();								// �]�w Button Start
	CString SetButtonStop();								// �]�w Button Stop
	CString SetButtonOneCycle();							// �]�w Button OneCycle
	CString SetButtonRetry();								// �]�w Button Retry 
	CString SetButtonSkip();								// �]�w Button Skip
	CString SetButtonReset();								// �]�w Button Reset
	CString SetRunMode(int iMode);							// �]�w Run Mode
	CString GetRunMode(int &iMode);							// ���o Run Mode
	CString SetLotInfo(int iLotField, CString csInfo);		// �]�w Lot Information
	CString GetLotInfo(int iLotFiled, CString &csInfo);		// ���o Lot Information
	
	bool GetLotCreate();									// �T�{�O�_���إߤu��
	bool GetDoorStatus();									// �T�{�O�_���Q�}��
	bool GetEStopStatus();									// �T�{��氱��s
	bool GetSystemReady();									// �T�{�t�ηǳƦn
	bool GetSystemError();									// ���o�ثe�t�άO�_���~
	bool GetCoordnationReady();								// �T�{�w�g�]�w Coordnation
	bool GetTrayFileMatchNow();								// �T�{�̫�@�� TrayFileSpec Match
	bool GetCoordnationGoStatusReady();						// �T�{�ثe�����A
	bool GetAirPressureEnable();							// �T�{�O�_�Ұ� �q����һ�
	bool GetIOMonitorOpen();								// �T�{ IO Monitor �O�_�Q���}
	bool GetButtonStartStatus();							// �T�{ Panel Start �O�_�i�H�Q���U
	bool GetButtonStopStatus();								// �T�{ Panel Stop �O�_�i�H�Q���U
	bool GetButtonInitialStatus();							// �T�{ Panel Initial �O�_�i�H�Q���U
	bool GetButtonRetryStatus();							// �T�{ Panel Retry �O�_�i�H�Q���U
	bool GetButtonSkipStatus();								// �T�{ Panel Skip �O�_�i�H�Q���U
	bool GetButtonResetStatus();							// �T�{ Panel Reset �O�_�i�H�Q���U
	bool GetButtonOneCycleStatus();							// �T�{ Panel OneCycle �O�_�i�H�Q���U
	bool GetNewLot();										// �T�{�O�_�i�H�إ� New Lot
	bool GetLotDone();										// �T�{�O�_�i�H�إ� Lot Done
	
	// SetState
	bool SetState(int iState);								// �]�w�ثe�����A
	
	// Mission
	void RequestCoordnationMissionGo();						// �n�D Arm �}�l�������
	void RequestCoordnationMissionReturn();					// �n�D Ts �}�l�������
	void RequestCoordnationMissionClearGo();				// �n�D Arm �M������
	void RequestCoordnationMissionInitial();				// ��l�ưѼ�

	// Verify
	bool VerifyCoord(CString csCmd, tagRemoteCoord &t);		// ���R Coordnation
	void GetCurrentCoord(int &iTray, int &iCol, int &iRow);	// ���o�ثe�� Coordnation
	void ClearRemoteTray();									// �M���]�w

	bool VerifyLotInfo(CString csCmd, tagRemoteLotInfo &lot);
};

#endif // !defined(AFX_DRIVERTESTINTERFACE_H__950CE285_B2D9_4C24_A50D_D359AEC12A97__INCLUDED_)
