// Roman IntegerDlg.h : header file
//

#pragma once
#include "romanint.h"


// CRomanIntegerDlg dialog
class CRomanIntegerDlg : public CDialog
{
// Construction
public:
	CRomanIntegerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ROMANINTEGER_DIALOG };

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
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedConvertRoman();
	afx_msg void OnBnClickedConvertinteger();

private:
	int m_nEnteredInteger;
	CString m_szDisplayedRoman;
	int m_DisplayInteger;
	CRomanInt m_RomanInt;
	CString m_szEnteredRoman;
public:
	afx_msg void OnEnUpdateTime();
	CString m_szTime;
	void CRomanIntegerDlg::OnTimer(UINT nIDEvent);
};
