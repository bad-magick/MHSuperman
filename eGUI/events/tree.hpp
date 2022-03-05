// tree.hpp

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


#ifndef JT07022008_events_tree_HPP_DEFINED
#define JT07022008_events_tree_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/events/detail/fwd.hpp"
#include "egui/controls/detail/fwd.hpp"

namespace egui { namespace handle_events {

typedef egui::types::tree_item_id tree_item_id;

struct tree::ev::single_expand   : event_module_base {
    void init_event();

    read_only<tree_item_id> item;
};
struct tree::ev::sel_changing   : event_module_base {
    void init_event();

    read_only<tree_item_id> old_item;
    read_only<tree_item_id> new_item;
    bool allow; // in/out
};
struct tree::ev::sel_changed   : event_module_base {
    void init_event();

    read_only<tree_item_id> old_item;
    read_only<tree_item_id> new_item;
};
struct tree::ev::item_expanding   : event_module_base {
    void init_event();

    read_only<types::tree_expand::type> expand_type;
    read_only<tree_item_id> item;
    bool allow; // in/out
};
struct tree::ev::item_expanded   : event_module_base {
    void init_event();

    read_only<int> expand_type;
    read_only<tree_item_id> item;
};
struct tree::ev::click   : event_module_base {
    void init_event();

    read_only<bool> left_click;
    read_only<bool> double_click;
};
struct tree::ev::focus   : event_module_base {
    void init_event();

    /// if true, we received focus, otherwise, we lost it
    read_only<bool> received;
};

}}

#endif

