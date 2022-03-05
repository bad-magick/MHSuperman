// combo_box.hpp

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


#ifndef JT07022008_events_combo_box_HPP_DEFINED
#define JT07022008_events_combo_box_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/events/detail/fwd.hpp"
#include "egui/controls/detail/fwd.hpp"

namespace egui { namespace handle_events {

struct combo_box::ev::sel_change   : event_module_base {
};
struct combo_box::ev::focus   : event_module_base {
    void init_event();
    /// if true, we received focus, otherwise, we lost it
    read_only<bool> received;
};
struct combo_box::ev::edit_change   : event_module_base {
};
struct combo_box::ev::edit_update   : event_module_base {
};
struct combo_box::ev::drop_down   : event_module_base {
    void init_event();
    /// if true, it's dropped, if false, it's closed
    read_only<bool> dropped;
};
/*
struct combo_box::ev::sel_end   : event_module_base {
    read_only<bool> ok;
};
*/
}}

#endif

