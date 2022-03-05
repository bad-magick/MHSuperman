// main.cpp

// Easy GUI Library
//
// Copyright (C) 2008 John Torjo (see http://torjo.com/contact/ for email)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.
//
// You can find the latest version of this library at http://www.torjo.com/egui/


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <tchar.h>
#include "egui/main/main.hpp"


int APIENTRY _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR    lpCmdLine, int       nCmdShow)
{
    try {
        egui::main_args args;
        args.command_line = lpCmdLine;
        egui::main( args) ;
    }
    catch(...) {}
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    using namespace egui;
    main_args args;
    args.command_line = ::GetCommandLine();
	switch (ul_reason_for_call)
	{
    case DLL_PROCESS_ATTACH:    args.reason = main_args::process_attach; break;
	case DLL_THREAD_ATTACH:     args.reason = main_args::thread_attach; break;
	case DLL_THREAD_DETACH:     args.reason = main_args::thread_detach; break;
	case DLL_PROCESS_DETACH:    args.reason = main_args::process_detach; break;
		break;
	}
    try {
        egui::main( args) ;
    }
    catch(...) {}
    return TRUE;
}

// End of file
