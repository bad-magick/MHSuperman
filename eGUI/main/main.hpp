// egui_main.hpp

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


#ifndef JT07022008_egui_main_HPP_DEFINED
#define JT07022008_egui_main_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/core/detail/fwd.hpp"

#ifndef BUILDING_EGUI
    #ifndef NDEBUG
    //debug
    #ifdef UNICODE
    #pragma comment (lib, "egui_main_dbg_u.lib" )
    #else
    #pragma comment (lib, "egui_main_dbg.lib" )
    #endif

    #else
    //release
    #ifdef UNICODE
    #pragma comment (lib, "egui_main_u.lib" )
    #else
    #pragma comment (lib, "egui_main.lib" )
    #endif
    #endif
#endif


namespace egui {

struct main_args {
    main_args() : reason(not_a_dll) {}

    enum reason_type {
        not_a_dll = 0,
        process_attach ,
        process_detach,
        thread_detach,
        thread_attach
    };

    string command_line;
    // only used in dlls
    reason_type reason;
};

/** 
    Just in case you want an easy abstraction over WinMain - so that you don't need to deal with HINSTANCE, and other types like that.

    Basically, so that you don't need to include <windows.h> just so that you can define your main()

*/
void main(const main_args &args );

}

#endif

