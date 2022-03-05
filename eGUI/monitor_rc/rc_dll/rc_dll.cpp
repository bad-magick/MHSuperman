// rc_dll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "rc_dll.h"
#include "path_to_monitor.h"

bool has_templates(fs::path path) {
    try {
        for ( fs::directory_iterator b(path),e; b != e; ++b)
            if ( b->leaf() == "egui_templates")
                return true;
    }
    catch(...) {}
    return false;
}

void init(HMODULE hModule) {
    char name[2048];
    ::GetModuleFileName(hModule, name, 2048);

    fs::path path = fs::path(name).branch_path();
    // look for templates up the directory tree
    while ( !has_templates (path) && (path != path.branch_path()))
        path = path.branch_path();
    if ( !has_templates(path ))
        path = fs::system_complete(".");

    if ( has_templates(path))
        path = path / "egui_templates";

    set_path_to_templates(path.string());
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: init(hModule); break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

