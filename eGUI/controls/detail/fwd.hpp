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


#ifndef JT07022008_ctrl_fwd_HPP_DEFINED
#define JT07022008_ctrl_fwd_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once

#ifndef BUILDING_EGUI
    #ifndef NDEBUG
    //debug
    #ifdef UNICODE
    #pragma comment (lib, "egui_controls_dbg_u.lib" )
    #else
    #pragma comment (lib, "egui_controls_dbg.lib" )
    #endif

    #else
    //release
    #ifdef UNICODE
    #pragma comment (lib, "egui_controls_u.lib" )
    #else
    #pragma comment (lib, "egui_controls.lib" )
    #endif
    #endif
#endif

#endif

#include "egui/core/wnd.hpp"
#include "egui/controls/detail/handle_event_base.hpp"

namespace egui { 

namespace types {

    struct list_item_state {
        enum type {
            //! item has focus
            focused = 0x0001,
            //! selected. Appearance of a selected item depends on whether it has the focus 
            selected = 0x0002,
            //! marked for a cut-and-paste operation
            cut = 0x0004               ,
            //! it's highlighted as a drag-and-drop target.
            drop_highlight= 0x0008,
            glow = 0x00010         ,
            activating = 0x00020,
            //! mask to retrieve the item's overlay image idx
            overlay_mask = 0x000F00,
        };
    };

    typedef void* tree_item_id;

    struct tree_expand {
        enum type {
            collapse = 1, 
            expand,
            toggle,
            expand_partial = 0x4000,
            collapse_reset = 0x8000
        };
    };
}

namespace ctrl {

struct control_base : window_base {
    control_base();
};

/** 
    helper to make sure the event handlers from the base class match those from the derived class

    For instance
    wnd<animate_ctrl> a = ...;
    wnd<> w = a;

    a->events.on_timer must point to the same handlers as w->events.on_timer
*/
template<class base> struct copy_events {
    template<class window> copy_events(window * w) {
        typedef base::events_type ev;

        base* b = w;
        ev & dest_events = w->events;
        // note : copy from base to derived; it should not be done from derived to base
        //        since that base might have a base of its own and we need all event handlers for event X
        //        to point to the same thing
        dest_events = b->events ;
    }
};

}


using namespace ctrl;


}

FORCE_CALL_BEFORE_MAIN(init_ctrl_controls)


#endif

