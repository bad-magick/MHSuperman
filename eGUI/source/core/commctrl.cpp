// commctrl.cpp

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

#include "stdafx_core.h"
#include "egui/core/wnd.hpp"
#include "shlwapi.h"

namespace egui { namespace detail {



namespace {
    // intializes standard controls - note: usually you don't need to call this directly, it's automatically called
    void do_init_controls( DWORD flags) {
        INITCOMMONCONTROLSEX iccx = { sizeof(INITCOMMONCONTROLSEX), flags };
        HMODULE comctl = LoadLibraryW(L"comctl32.dll");
        if(comctl) {
            typedef BOOL (__stdcall *init_func) (LPINITCOMMONCONTROLSEX);
            init_func func = (init_func)GetProcAddress(comctl, "InitCommonControlsEx");
            if ( func)
                func(&iccx);
            // note: we should not free the library, since we could be using it...
            // FreeLibrary(comctl);
        }
    }

    DLLVERSIONINFO get_comctrl_version() {
        HMODULE comctl = LoadLibraryW(L"comctl32.dll");
        if(comctl) {
            DLLGETVERSIONPROC proc = (DLLGETVERSIONPROC)GetProcAddress(comctl, "DllGetVersion");
            if ( proc) {
                DLLVERSIONINFO info = {0};
                info.cbSize = sizeof(DLLVERSIONINFO);
                proc(&info);
                return info;
            }
        }

        DLLVERSIONINFO invalid = {0};
        return invalid;
    }

    DLLVERSIONINFO comctrl_ver = get_comctrl_version();

}

void init_common_controls() {
    do_init_controls( ICC_ANIMATE_CLASS | ICC_BAR_CLASSES | ICC_COOL_CLASSES | ICC_LISTVIEW_CLASSES 
                   | ICC_DATE_CLASSES | ICC_HOTKEY_CLASS | ICC_INTERNET_CLASSES | ICC_UPDOWN_CLASS
        | ICC_PROGRESS_CLASS | ICC_TAB_CLASSES | ICC_TREEVIEW_CLASSES);
}

bool has_comctl_ver(UINT major, UINT minor) {
    if (comctrl_ver.dwMajorVersion != major) 
        return comctrl_ver.dwMajorVersion > major;

    // comctrl_ver.dwMajorVersion == major 
    return comctrl_ver.dwMinorVersion >= minor;
}

}}


// End of file
