// MHSuperman.cpp : Defines the initialization routines for the DLL.
//

#include "Constructs.h"
#ifndef _USE_MFC
	#include <Windows.h>
#else
	#include "stdafx.h"
#endif
#include "VinHacks.h"
#include "MHSuperman.h"
#include "MHWalker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE				hCurrentProcess;
HMODULE				hCurrentModule;

#ifndef PUBLIC
void FuckNexon(void) {
	MessageBox(0, "That's right, I said \"FUCK NEXON!\"", "Get it?", 0);
}
#endif

#ifdef TEST
void main(void)
{
	HackThread();
}
#else

#ifndef _USE_MFC
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason) //'switch' to dwReason, could use if's instead
	{
	case DLL_PROCESS_ATTACH: //we 'attached' to the process
		DisableThreadLibraryCalls(hModule); //Disable calls to dllmain for DLL_THREAD_ATTACH and DLL_THREAD_DETACH
		hCurrentModule = hModule;
		hCurrentProcess = GetCurrentProcess();
		GetAllInterfaces();
		CreateHackThread(); //Create a thread that runs our HackThread function
		break; //break out of the switch statement
	}
	return TRUE; //success
}
#else

BEGIN_MESSAGE_MAP(CMHSuperman, CWinApp)
END_MESSAGE_MAP()

#if _MSC_VER >= 1300    // for VC 7.0
  // from ATL 7.0 sources
  #ifndef _delayimp_h
  extern "C" IMAGE_DOS_HEADER __ImageBase;
  #endif
#endif

HMODULE GetCurrentModule()
{
#if _MSC_VER < 1300    // earlier than .NET compiler (VC 6.0)

  // Here's a trick that will get you the handle of the module
  // you're running in without any a-priori knowledge:
  // http://www.dotnet247.com/247reference/msgs/13/65259.aspx

  MEMORY_BASIC_INFORMATION mbi;
  static int dummy;
  VirtualQuery( &dummy, &mbi, sizeof(mbi) );

  return reinterpret_cast<HMODULE>(mbi.AllocationBase);

#else    // VC 7.0

  // from ATL 7.0 sources

  return reinterpret_cast<HMODULE>(&__ImageBase);
#endif
}

// CMFCDLLSampleApp construction

CMHSuperman::CMHSuperman()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	//::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HackThread, 0, 0, 0);

	hCurrentModule = GetCurrentModule();
	hCurrentProcess = GetCurrentProcess();

	CreateHackThread();
}


// The one and only CMFCDLLSampleApp object

CMHSuperman theApp;


// CMFCDLLSampleApp initialization

BOOL CMHSuperman::InitInstance()
{

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		//AfxMessageBox(_T"MHSuperman Init Failed.", IDOK);
		MessageBox(0, "MHSuperman Init failed.", 0, 0);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	//CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	//SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	return TRUE;
}

#endif
#endif




