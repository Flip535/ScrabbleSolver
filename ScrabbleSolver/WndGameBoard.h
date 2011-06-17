#pragma once
#include "CGdiPlusBitmap.h"
#include "GameBoard.h"


// WndGameBoard

class CWndGameBoard : public CWnd
{
	DECLARE_DYNAMIC(CWndGameBoard)

public:
	CWndGameBoard(int rows, int cols, DWORD id);
	virtual ~CWndGameBoard();

protected:
	BOOL RegisterWndClass();
	DECLARE_MESSAGE_MAP()
	int m_rows;
	int m_cols;
	CPoint m_spotPos;
	CGdiPlusBitmap m_gameBoardImg;
	CPtrArray m_arrRects;
	CGameBoard m_gameBoard;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


#define WNDGAMEBOARD _T("WndGameBoard")

