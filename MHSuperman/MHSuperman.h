// MHSuperman.h : main header file for the MHSuperman DLL
//

#pragma once

#define WIN32_LEAN_AND_MEAN

extern HANDLE				hCurrentProcess;
extern HMODULE				hCurrentModule;

void FuckNexon(void);
#ifndef _USE_MFC
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved);
#else

// MFC DLL Sample.h : main header file for the MFC DLL Sample DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCDLLSampleApp
// See MFC DLL Sample.cpp for the implementation of this class
//

class CMHSuperman : public CWinApp
{
public:
	CMHSuperman();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

#endif