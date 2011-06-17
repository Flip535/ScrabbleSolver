
// ScrabbleSolver.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CScrabbleSolverApp:
// See ScrabbleSolver.cpp for the implementation of this class
//

class CScrabbleSolverApp : public CWinAppEx
{
public:
	CScrabbleSolverApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

protected:
	ULONG_PTR m_gdiplusToken;
public:
	virtual int ExitInstance();
};

extern CScrabbleSolverApp theApp;