
// ScanerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Scaner.h"
#include "ScanerDlg.h"
#include "afxdialogex.h"
#include "string.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CScanerDlg dialog



CScanerDlg::CScanerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SCANER_DIALOG, pParent)
	, m_link(_T(""))
	
	, m_search(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScanerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LINK, m_link);
	DDX_Control(pDX, IDC_LIST, m_control);
	DDX_Text(pDX, IDC_CONTENT, m_search);
}

BEGIN_MESSAGE_MAP(CScanerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SCAN, &CScanerDlg::OnBnClickedScan)
END_MESSAGE_MAP()


// CScanerDlg message handlers

BOOL CScanerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	m_link = TEXT("C:\\");
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScanerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CScanerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CScanerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CScanerDlg::LockControls() {
	auto pEditBox = GetDlgItem(IDC_LINK);
	auto pButton = GetDlgItem(IDC_SCAN);
	pEditBox->EnableWindow(FALSE);
	pButton->EnableWindow(FALSE);
}

void CScanerDlg::UnlockControls() {
	auto pEditBox = GetDlgItem(IDC_LINK);
	auto pButton = GetDlgItem(IDC_SCAN);
	pEditBox->EnableWindow();
	pButton->EnableWindow();
}


void CScanerDlg::Recurse(LPCTSTR pstr)
{
	CFileFind finder;

	// build a string with wildcards
	CString strWildcard(pstr);
	strWildcard += _T("\\*.*");

	// start working for files
	BOOL bWorking = finder.FindFile(strWildcard);
	/*if (!bWorking) {
		// something's wrong, print the current error message
		TCHAR buf[256] = { 0 };
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			buf, sizeof(buf), NULL);
		AfxMessageBox(buf);
		return;
	}*/
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		char consider[100];
		// skip . and .. files; otherwise, we'd
		// recur infinitely!

		if (finder.IsDots())
			continue;

		// if it's a directory, recursively search it

		//if (finder.IsDirectory())
		else
		{

			CString str = finder.GetFilePath();
			m_control.AddString(_T("Scanned: ") + str);
			Recurse(str);
		}
	}

	finder.Close();
}

void CScanerDlg::OnBnClickedScan()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	LockControls();
	// clear current list box
	m_control.ResetContent();	
	UpdateData();
	Recurse(m_link);
	AfxMessageBox(_T("Scan completed"), MB_OK);
	UnlockControls();
	//AfxBeginThread(RecurseThreadProc, this);
}


/*void CScanerDlg::RecurseThreadProc(LPVOID Param) {
	// use param
	// there are no "this" pointer in static functions
	CScanerDlg* ourWnd = reinterpret_cast<CScanerDlg*>(Param);
	//UINT64 fib = RecursiveFibonacci(ourWnd->m_iOrdinal);
	Recurse(ourWnd->m_link);
	// post message back to UI thread
	// WM_COMPLETE here is a custom message, defined in our header file
	//ourWnd->PostMessageW(WM_COMPLETE, fib);
	return ;
}

/*afx_msg LRESULT CScanerDlg::OnComplete(WPARAM wParam, LPARAM lParam)
{
	// handle result
	CString res;
	res.Format(TEXT("Số Fibonacci thứ %d = %I64u"), m_iOrdinal, wParam);
	AfxMessageBox(res, MB_OK);
	auto pEditBox = this->GetDlgItem(IDC_EDIT1);
	pEditBox->EnableWindow();
	auto pButton = GetDlgItem(IDC_btnCalculate);
	pButton->EnableWindow();
	return 0;
}*/