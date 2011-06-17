
// ScrabbleSolverDlg.h : header file
//

#pragma once
#include "WndGameBoard.h"

// CScrabbleSolverDlg dialog
class CScrabbleSolverDlg : public CDialog
{
// Construction
public:
	CScrabbleSolverDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SCRABBLESOLVER_DIALOG };

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
	CWndGameBoard m_gameBoard;
};
