// Roman IntegerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Roman Integer.h"
#include "Roman IntegerDlg.h"
#include ".\roman integerdlg.h"
#include "RomanInt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CRomanIntegerDlg dialog



CRomanIntegerDlg::CRomanIntegerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRomanIntegerDlg::IDD, pParent)
	, m_nEnteredInteger(0)
	, m_szDisplayedRoman(_T(""))
	, m_DisplayInteger(0)
	, m_szEnteredRoman(_T(""))
	, m_szTime(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRomanIntegerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IntegerEnter, m_nEnteredInteger);
	DDV_MinMaxInt(pDX, m_nEnteredInteger, 1, 268435456);
	DDX_Text(pDX, IDC_RomanDisplay, m_szDisplayedRoman);
	DDX_Text(pDX, IDC_IntegerDisplay, m_DisplayInteger);
	DDX_Text(pDX, IDC_RomanEnter, m_szEnteredRoman);
	DDX_Text(pDX, IDC_TIME, m_szTime);
}

BEGIN_MESSAGE_MAP(CRomanIntegerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ConvertRoman, OnBnClickedConvertRoman)
	ON_BN_CLICKED(IDC_ConvertInteger, OnBnClickedConvertinteger)
	ON_EN_UPDATE(IDC_TIME, OnEnUpdateTime)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CRomanIntegerDlg message handlers

BOOL CRomanIntegerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_nEnteredInteger = 1;
	m_szDisplayedRoman = "I";
	m_DisplayInteger = 1;
	m_szEnteredRoman = "I";
	UpdateData(false);
	
	SetTimer(0, 1000, NULL);
	OnEnUpdateTime();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRomanIntegerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRomanIntegerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRomanIntegerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRomanIntegerDlg::OnBnClickedConvertRoman()
{
	UpdateData(true);
	m_RomanInt.setRoman(m_nEnteredInteger);
	m_szDisplayedRoman = m_RomanInt.getRoman();
	UpdateData(false);
}

void CRomanIntegerDlg::OnBnClickedConvertinteger()
{
	UpdateData(true);
	if(!m_RomanInt.setRoman(m_szEnteredRoman))
		MessageBox("Invalid Roman Numeral", "Input Error");
	m_DisplayInteger = m_RomanInt.getIntValue();
	if( m_DisplayInteger == -1 )
	{
		// Error with the Roman Num
		MessageBox("Invalid Roman Numeral");
	}
	else
	{
		UpdateData(false);
	}
}
void CRomanIntegerDlg::OnEnUpdateTime()
{
	// Update current variables so that they don't get erased when we update the clock
	UpdateData(true);

	// Grab the time
	CTime currTime = CTime::GetCurrentTime();
	CRomanInt currHour(currTime.GetHour());
	CRomanInt currMin(currTime.GetMinute());
	CRomanInt currSec(currTime.GetSecond());

	// Splice the times together into a CString with : seperators
	CString temp = currHour.getRoman();
	temp.Append(":");
	temp.Append(currMin.getRoman());
	temp.Append(":");
	temp.Append(currSec.getRoman());

	// Set the time variable to temp
	m_szTime = temp;

	// Update the screen
	UpdateData(false);
}

void CRomanIntegerDlg::OnTimer(UINT nIDEvent)
{
	OnEnUpdateTime();
}
