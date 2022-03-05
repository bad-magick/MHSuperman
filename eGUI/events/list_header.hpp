// list_header.hpp

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


#ifndef JT07022008_events_list_header_HPP_DEFINED
#define JT07022008_events_list_header_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/events/detail/fwd.hpp"
#include "egui/controls/detail/fwd.hpp"

namespace egui { namespace handle_events {

struct list_header::ev::drag   : event_module_base {
    void init_event();

    enum button {
        left = 0,
        right,
        middle
    };

    read_only<bool> start_of_drag;
    read_only<int> col_idx;
    read_only<button> dragged_with;
};  
struct list_header::ev::item_changing   : event_module_base {
    void init_event();

    read_only<int> col_idx;
    bool allow; // in/out
};
struct list_header::ev::item_changed   : event_module_base {
    void init_event();

    read_only<int> col_idx;
};
struct list_header::ev::item_click   : event_module_base {
    void init_event();

    read_only<int> col_idx;
    read_only<bool> double_click;
};
struct list_header::ev::divider_dbl_click   : event_module_base {
    void init_event();

    read_only<int> col_idx;
};
struct list_header::ev::right_click   : event_module_base {
};

}}

#endif

