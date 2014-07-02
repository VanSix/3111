// DlgTrayFileChipTray.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTrayFileChipTray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayFileChipTray dialog


CDlgTrayFileChipTray::CDlgTrayFileChipTray(CString csFile, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrayFileChipTray::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTrayFileChipTray)
	m_dSubA = 0.0;
	m_dSubB = 0.0;
	m_dSubC = 0.0;
	m_dSubChipA = 0.0;
	m_dSubChipB = 0.0;
	m_dSubChipC = 0.0;
	m_dSubChipD = 0.0;
	m_lSubChipColumn = 0;
	m_lSubChipRow = 0;
	m_lSubColumn = 0;
	m_dSubD = 0.0;
	m_lSubRow = 0;
	m_bUseFixTray = FALSE;
	m_bUseInput = FALSE;
	m_bUseOutput = FALSE;
	//}}AFX_DATA_INIT

	m_csFile = csFile;

	m_TraySpec = m.TraySpec;

	m_fChange = false;
}


void CDlgTrayFileChipTray::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrayFileChipTray)
	DDX_Control(pDX, IDC_FILE,	m_wndFile);
	DDX_Control(pDX, IDCANCEL,	m_btnCancel);
	DDX_Control(pDX, IDOK,		m_btnOK);

	DDX_Text(pDX, IDC_SUB_COLUMN,	m_lSubColumn);
	DDX_Text(pDX, IDC_SUB_ROW,		m_lSubRow);
	DDX_Text(pDX, IDC_SUB_A,		m_dSubA);
	DDX_Text(pDX, IDC_SUB_B,		m_dSubB);
	DDX_Text(pDX, IDC_SUB_C,		m_dSubC);
	DDX_Text(pDX, IDC_SUB_D,		m_dSubD);


	DDX_Text(pDX, IDC_SUB_CHIP_COLUMN,	m_lSubChipColumn);
	DDX_Text(pDX, IDC_SUB_CHIP_ROW,		m_lSubChipRow);
	DDX_Text(pDX, IDC_SUB_CHIP_A,		m_dSubChipA);
	DDX_Text(pDX, IDC_SUB_CHIP_B,		m_dSubChipB);
	DDX_Text(pDX, IDC_SUB_CHIP_C,		m_dSubChipC);
	DDX_Text(pDX, IDC_SUB_CHIP_D,		m_dSubChipD);


	DDX_Check(pDX, IDC_USE_FIX_TRAY,		m_bUseFixTray);
	DDX_Check(pDX, IDC_USE_INPUT_STACK,		m_bUseInput);
	DDX_Check(pDX, IDC_USE_OUTPUT_STACK,	m_bUseOutput);
	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_SUB_COLUMN,	m_TraySpec.m_SubTrayColumn );
	DDX_Text(pDX, IDC_SUB_ROW,		m_TraySpec.m_SubTrayRow );
	DDX_Text(pDX, IDC_SUB_A,		m_TraySpec.m_SubTrayA );
	DDX_Text(pDX, IDC_SUB_B,		m_TraySpec.m_SubTrayB );
	DDX_Text(pDX, IDC_SUB_C,		m_TraySpec.m_SubTrayC );
	DDX_Text(pDX, IDC_SUB_D,		m_TraySpec.m_SubTrayD );


	DDX_Text(pDX, IDC_SUB_CHIP_COLUMN,	m_TraySpec.m_SubChipTrayColumn );
	DDX_Text(pDX, IDC_SUB_CHIP_ROW,		m_TraySpec.m_SubChipTrayRow );
	DDX_Text(pDX, IDC_SUB_CHIP_A,		m_TraySpec.m_SubChipTrayA );
	DDX_Text(pDX, IDC_SUB_CHIP_B,		m_TraySpec.m_SubChipTrayB );
	DDX_Text(pDX, IDC_SUB_CHIP_C,		m_TraySpec.m_SubChipTrayC );
	DDX_Text(pDX, IDC_SUB_CHIP_D,		m_TraySpec.m_SubChipTrayD );


	DDX_Check(pDX, IDC_USE_FIX_TRAY,		m_TraySpec.m_FixUseChipTray );
	DDX_Check(pDX, IDC_USE_INPUT_STACK,		m_TraySpec.m_InputUseChipTray );
	DDX_Check(pDX, IDC_USE_OUTPUT_STACK,	m_TraySpec.m_OutputUseChipTray );
}


BEGIN_MESSAGE_MAP(CDlgTrayFileChipTray, CDialog)
	//{{AFX_MSG_MAP(CDlgTrayFileChipTray)
	ON_BN_CLICKED(IDC_USE_INPUT_STACK, OnUseInputStack)
	ON_BN_CLICKED(IDC_USE_OUTPUT_STACK, OnUseOutputStack)
	ON_BN_CLICKED(IDC_USE_FIX_TRAY, OnUseFixTray)
	ON_EN_CHANGE(IDC_SUB_A, OnChangeSubA)
	ON_EN_CHANGE(IDC_SUB_B, OnChangeSubB)
	ON_EN_CHANGE(IDC_SUB_C, OnChangeSubC)
	ON_EN_CHANGE(IDC_SUB_D, OnChangeSubD)
	ON_EN_CHANGE(IDC_SUB_COLUMN, OnChangeSubColumn)
	ON_EN_CHANGE(IDC_SUB_CHIP_A, OnChangeSubChipA)
	ON_EN_CHANGE(IDC_SUB_CHIP_B, OnChangeSubChipB)
	ON_EN_CHANGE(IDC_SUB_CHIP_C, OnChangeSubChipC)
	ON_EN_CHANGE(IDC_SUB_CHIP_D, OnChangeSubChipD)
	ON_EN_CHANGE(IDC_SUB_CHIP_COLUMN, OnChangeSubChipColumn)
	ON_EN_CHANGE(IDC_SUB_CHIP_ROW, OnChangeSubChipRow)
	ON_BN_CLICKED(IDC_CONVERT, OnConvert)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayFileChipTray message handlers

void CDlgTrayFileChipTray::OnOK() 
{
	if( !f.CheckEnaleChange() )
		return;

	// ��ǤJ�Ӫ��ɦW���ɮת��]�w�g�J�����ɮ�
	SaveTraySpec();

	// ��ثe���ɮצAŪ�X�Ӥ@��. �]�����i��Ƕi�Ӫ��ɦW�N�O�ثe�ϥΪ�
	f.LoadTraySpec();

	// Chip Tray
	theApp.m_InputTray.SetChipMode(	m.TraySpec.m_InputUseChipTray );
	theApp.m_OutputTray.SetChipMode( m.TraySpec.m_OutputUseChipTray );

	// Chip Tray / Repeat Tray
	theApp.m_Tray1.SetChipMode(	m.TraySpec.m_InputUseChipTray );
	theApp.m_Tray2.SetChipMode(	m.TraySpec.m_OutputUseChipTray );

	// Set TraySpec
	theApp.m_InputTray.SetSpec(	m.TraySpec );
	theApp.m_OutputTray.SetSpec( m.TraySpec );

	// Set Tray Spec
	theApp.m_Tray1.SetSpec(	m.TraySpec );
	theApp.m_Tray2.SetSpec(	m.TraySpec );

	// Set Me
	theApp.m_InputTray.SetMe( ( _Stack_A * m.m_Ratio.Y_GearRation ), ( _Stack_B * m.m_Ratio.X_GearRation ));
	theApp.m_OutputTray.SetMe( ( _Stack_A * m.m_Ratio.Y_GearRation ), ( _Stack_B * m.m_Ratio.X_GearRation ));

	// Set Me / Repeat Tray
	theApp.m_Tray1.SetMe( ( _Stack_A * m.m_Ratio.Y_GearRation ), ( _Stack_B * m.m_Ratio.X_GearRation ));
	theApp.m_Tray2.SetMe( ( _Stack_A * m.m_Ratio.Y_GearRation ), ( _Stack_B * m.m_Ratio.X_GearRation ));

	CDialog::OnOK();
}

void CDlgTrayFileChipTray::OnCancel() 
{
	if( m_fChange )
	{
		if(IDYES != AfxMessageBox("Data is modified. Save?\n",
			MB_YESNO|MB_ICONEXCLAMATION))
		{
			// ���x�s
		}
		else
		{
			// �x�s�ɮ�
			OnOK();
		}
	}

	CDialog::OnCancel();
}

BOOL CDlgTrayFileChipTray::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	// ��ܥثe Chip Tray �O�ݩ���@�� Tray File ��
	CString csTrayFile;
	csTrayFile.Format("File : %s", m_csFile );
	m_wndFile.SetWindowText( csTrayFile );

	// �ھڶǶi�Ӫ��ɮצW��. ���J�۹����� Chip Tray �Ѽ�
	LoadTraySpec();	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTrayFileChipTray::SaveTraySpec() 
{
	CString csFile;
	CString FileName;

	// �ѥ~���Ƕi�Ӫ��ɮצW�� / Ū�J�۹������ɮ�
	FileName = m_csFile;

	if( FileName == "" )
	{
		AfxMessageBox("No File Name Error");
		return;
	}
	csFile = m.FilePath.TrayFilesPath + FileName + _SubFileName2;

	// ���檺�ƭȨ��^��
	UpdateData();

	// Sub Tray
	f.SaveSetting(csFile, "Sub Tray",		 "Sub Tray Column",		m_TraySpec.m_SubTrayColumn);
	f.SaveSetting(csFile, "Sub Tray",		 "Sub Tray Row",		m_TraySpec.m_SubTrayRow);
	f.SaveSetting(csFile, "Sub Tray",		 "Sub Tray A",			m_TraySpec.m_SubTrayA);
	f.SaveSetting(csFile, "Sub Tray",		 "Sub Tray B",			m_TraySpec.m_SubTrayB);
	f.SaveSetting(csFile, "Sub Tray",		 "Sub Tray C",			m_TraySpec.m_SubTrayC);
	f.SaveSetting(csFile, "Sub Tray",		 "Sub Tray D",			m_TraySpec.m_SubTrayD);

	// Chip Tray
	f.SaveSetting(csFile, "Chip Tray",		 "Chip Tray Column",	m_TraySpec.m_SubChipTrayColumn);
	f.SaveSetting(csFile, "Chip Tray",		 "Chip Tray Row",		m_TraySpec.m_SubChipTrayRow);
	f.SaveSetting(csFile, "Chip Tray",		 "Chip Tray A",			m_TraySpec.m_SubChipTrayA);
	f.SaveSetting(csFile, "Chip Tray",		 "Chip Tray B",			m_TraySpec.m_SubChipTrayB);
	f.SaveSetting(csFile, "Chip Tray",		 "Chip Tray C",			m_TraySpec.m_SubChipTrayC);
	f.SaveSetting(csFile, "Chip Tray",		 "Chip Tray D",			m_TraySpec.m_SubChipTrayD);

	// Chip Enable Function
	f.SaveSetting(csFile, "Chip Tray Enable",	"Chip Tray Input Enable",		m_TraySpec.m_InputUseChipTray);
	f.SaveSetting(csFile, "Chip Tray Enable",	"Chip Tray Output ENable",		m_TraySpec.m_OutputUseChipTray);
	f.SaveSetting(csFile, "Chip Tray Enable",	"Chip Tray Fix Enable",			m_TraySpec.m_FixUseChipTray);
}
void CDlgTrayFileChipTray::LoadTraySpec() 
{
	CString csFile;
	CString FileName;

	// �ѥ~���Ƕi�Ӫ��ɮצW�� / Ū�J�۹������ɮ�
	FileName = m_csFile;

	if( FileName == "" )
	{
		AfxMessageBox("No File Name Error");
		return;
	}
	csFile = m.FilePath.TrayFilesPath + FileName + _SubFileName2;

	// Sub Tray
	f.GetSetting(csFile, "Sub Tray",		 "Sub Tray Column",		m_TraySpec.m_SubTrayColumn);
	f.GetSetting(csFile, "Sub Tray",		 "Sub Tray Row",		m_TraySpec.m_SubTrayRow);
	f.GetSetting(csFile, "Sub Tray",		 "Sub Tray A",			m_TraySpec.m_SubTrayA);
	f.GetSetting(csFile, "Sub Tray",		 "Sub Tray B",			m_TraySpec.m_SubTrayB);
	f.GetSetting(csFile, "Sub Tray",		 "Sub Tray C",			m_TraySpec.m_SubTrayC);
	f.GetSetting(csFile, "Sub Tray",		 "Sub Tray D",			m_TraySpec.m_SubTrayD);

	// Chip Tray
	f.GetSetting(csFile, "Chip Tray",		 "Chip Tray Column",	m_TraySpec.m_SubChipTrayColumn);
	f.GetSetting(csFile, "Chip Tray",		 "Chip Tray Row",		m_TraySpec.m_SubChipTrayRow);
	f.GetSetting(csFile, "Chip Tray",		 "Chip Tray A",			m_TraySpec.m_SubChipTrayA);
	f.GetSetting(csFile, "Chip Tray",		 "Chip Tray B",			m_TraySpec.m_SubChipTrayB);
	f.GetSetting(csFile, "Chip Tray",		 "Chip Tray C",			m_TraySpec.m_SubChipTrayC);
	f.GetSetting(csFile, "Chip Tray",		 "Chip Tray D",			m_TraySpec.m_SubChipTrayD);

	// Chip Enable Function
	f.GetSetting(csFile, "Chip Tray Enable",	"Chip Tray Input Enable",		m_TraySpec.m_InputUseChipTray);
	f.GetSetting(csFile, "Chip Tray Enable",	"Chip Tray Output ENable",		m_TraySpec.m_OutputUseChipTray);
	f.GetSetting(csFile, "Chip Tray Enable",	"Chip Tray Fix Enable",			m_TraySpec.m_FixUseChipTray);
}

// Change
void CDlgTrayFileChipTray::OnUseInputStack() 
{
	m_fChange = true;	
}

void CDlgTrayFileChipTray::OnUseOutputStack() 
{
	m_fChange = true;
}

void CDlgTrayFileChipTray::OnUseFixTray() 
{
	m_fChange = true;
}

void CDlgTrayFileChipTray::OnChangeSubA() 
{
	m_fChange = true;	
}

void CDlgTrayFileChipTray::OnChangeSubB() 
{
	m_fChange = true;	
}

void CDlgTrayFileChipTray::OnChangeSubC() 
{
	m_fChange = true;	
}

void CDlgTrayFileChipTray::OnChangeSubD() 
{
	m_fChange = true;	
}

void CDlgTrayFileChipTray::OnChangeSubColumn() 
{
	m_fChange = true;	
}

void CDlgTrayFileChipTray::OnChangeSubChipA() 
{
	m_fChange = true;	
}

void CDlgTrayFileChipTray::OnChangeSubChipB() 
{
	m_fChange = true;	
}

void CDlgTrayFileChipTray::OnChangeSubChipC() 
{
	m_fChange = true;	
}

void CDlgTrayFileChipTray::OnChangeSubChipD() 
{
	m_fChange = true;	
}

void CDlgTrayFileChipTray::OnChangeSubChipColumn() 
{
	m_fChange = true;	
}

void CDlgTrayFileChipTray::OnChangeSubChipRow() 
{
	m_fChange = true;	
}

void CDlgTrayFileChipTray::OnConvert() 
{

#if 0
	int itotaltray = 
		( m_TraySpec.m_SubChipTrayColumn * m_TraySpec.m_SubTrayColumn ) * 
		( m_TraySpec.m_SubChipTrayRow * m_TraySpec.m_SubTrayRow );				// ��X�]�t Chip Tray ��� Tray �`�@���X�� IC

	int*ptrTray = new int[itotaltray];
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
			ptrTray[TrayArray] = ptrfsingle[r];
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
		ddf.Format("%d,", ptrTray[de]);
		cs = cs + ddf;
	}
	AfxMessageBox( cs );
*/

	delete [] ptrf;
	delete [] ptrfsingle;
	delete [] ptrtempf;
	// �R���}�C
	
	delete [] ptrTray;
	// �R���}�C
#endif
}


CPoint CDlgTrayFileChipTray::GetIndex(int iNo)		
{	
	CPoint p;
	int m_iRowL = -1; // �� y ����
	int m_iColL = -1; // �� x ����		

	m_iColL = iNo % ( m_TraySpec.m_SubChipTrayColumn * m_TraySpec.m_SubTrayColumn);		// For C
	m_iRowL = iNo / ( m_TraySpec.m_SubChipTrayColumn * m_TraySpec.m_SubTrayColumn);		// For D

	p.x = m_iColL + 1;
	p.y = m_iRowL + 1;

	// Debug
	CString d;
	d.Format("Tray Map %dD . %dC", m_iRowL, m_iColL );
	f.CWinMessage( d, theApp.enDArm );

	return p;
}
void CDlgTrayFileChipTray::ConvertChipTray()
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
int CDlgTrayFileChipTray::GetChipTrayPosition( int iBooking )
{
	int m_iIndex = -1;

	m_iIndex = m_ChipTrayArray[iBooking];

	return m_iIndex;
}

void CDlgTrayFileChipTray::OnDestroy() 
{
//	if( m_ChipTrayArray != NULL )
//		delete [] m_ChipTrayArray;
	CDialog::OnDestroy();	
}
