
// MHInject.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMHInjectApp:
// See MHInject.cpp for the implementation of this class
//

class CMHInjectApp : public CWinApp
{
public:
	CMHInjectApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMHInjectApp theApp;