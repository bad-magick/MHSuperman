// fwd.hpp

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


#ifndef JT07022008_events_fwd_HPP_DEFINED
#define JT07022008_events_fwd_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once

#ifndef BUILDING_EGUI
    #ifndef NDEBUG
    //debug
    #ifdef UNICODE
    #pragma comment (lib, "egui_events_dbg_u.lib" )
    #else
    #pragma comment (lib, "egui_events_dbg.lib" )
    #endif

    #else
    //release
    #ifdef UNICODE
    #pragma comment (lib, "egui_events_u.lib" )
    #else
    #pragma comment (lib, "egui_events.lib" )
    #endif
    #endif
#endif

#endif

#include <vector>
#include "egui/core/wnd.hpp"
#include "egui/events/detail/event_base.hpp"

namespace egui { 

    namespace ev { namespace converters {
        template<class type> struct read_only;
    }}

    namespace handle_events {
        typedef ::egui::ev::event_module_base event_module_base;
        namespace converters = egui::ev::converters;

        using egui::ev::read_only;
}}


namespace egui { 

FORCE_CALL_BEFORE_MAIN(init_events)

}

#endif

