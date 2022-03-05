// list.hpp

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


#ifndef JT07022008_events_list_HPP_DEFINED
#define JT07022008_events_list_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/events/detail/fwd.hpp"
#include "egui/controls/detail/fwd.hpp"

namespace egui { namespace handle_events {

struct list::ev::item_changing   : event_module_base {
    void init_event();

    read_only<int> idx;
    read_only<int> sub_idx;
    read_only<types::list_item_state::type> old_state;
    read_only<types::list_item_state::type> new_state;
    bool allow; // in/out
};
struct list::ev::item_changed   : event_module_base {
    void init_event();

    read_only<int> idx;
    read_only<int> sub_idx;
    read_only<types::list_item_state::type> old_state;
    read_only<types::list_item_state::type> new_state;
};
struct list::ev::column_click   : event_module_base {
    void init_event();

    read_only<int> col_idx;
};
struct list::ev::drag   : event_module_base {
    void init_event();

    read_only<bool> dragged_with_left;
    read_only<int> idx;
};
struct list::ev::state_changed   : event_module_base {
    void init_event();

    read_only<int> first_idx;
    read_only<int> last_idx;
    read_only<types::list_item_state::type> old_state;
    read_only<types::list_item_state::type> new_state;
};
struct list::ev::hot_track   : event_module_base {
    void init_event();

    read_only<int> idx;
    read_only<int> sub_idx;
    bool allow; // in/out
};
struct list::ev::click   : event_module_base {
    void init_event();

    read_only<bool> left_click;
    read_only<bool> double_click;
};
struct list::ev::focus   : event_module_base {
    void init_event();

    /// if true, we received focus, otherwise, we lost it
    read_only<bool> received;
};

}}

#endif

