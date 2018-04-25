
// ScanerDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CScanerDlg dialog
class CScanerDlg : public CDialogEx
{
// Construction
public:
	CScanerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCANER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();


	void LockControls();
	void UnlockControls();
	DECLARE_MESSAGE_MAP()
public:

	CString m_link;
	afx_msg void OnBnClickedScan();
	void Recurse(LPCTSTR pstr);
	//static void RecurseThreadProc(LPVOID Param);
	CListBox m_control;
	//afx_msg void OnBnClickedButton1();
	//afx_msg void OnBnClickedBrowse();
	CString m_search;
};
