// Parser3111.h: interface for the CParser3111 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSER3111_H__3AA6CB01_8F47_44DB_B6E6_3A1754D76B22__INCLUDED_)
#define AFX_PARSER3111_H__3AA6CB01_8F47_44DB_B6E6_3A1754D76B22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParser3111  
{
public:
	CString TestEvent();
	CString Location();
	CString ErrorMessage();
	CString SendEvent();
	CString GetSiteStatus();
	CString GetStatus();
	CString GetSiteSetTemp();
	CString SetSiteTemp(CString Temper);
	CString GetSiteTemp();
	CString SetTimeOut(CString time);
	CString GetTimeOut();
	CString SetRunMode(CString mode);
	CString GetRunMode();
	CString SendEventEnable(bool Enable);
	CString AutoSkip(bool enable);
	CString PurgeDevices();
	CString Retest(CString count);
	CString SetTestResult(CString msg, bool bReady = false);
	CString GetTestResult(CString &msg);
	CString OneCycle();
	CString Initial();
	CString Reset();
	CString StackUnload();
	CString TrayChange();
	CString Skip();
	CString Retry();
	CString Stop();
	CString LoadSetup(CString msg);
	CString GetVersion();
	CString Disconnect();
	CString Start();
	CString Connect();
	CParser3111();
	virtual ~CParser3111();

};

#endif // !defined(AFX_PARSER3111_H__3AA6CB01_8F47_44DB_B6E6_3A1754D76B22__INCLUDED_)
