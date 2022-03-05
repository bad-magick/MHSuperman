// controls_tree.hpp

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


#ifndef JT07022008_controls_tree_HPP_DEFINED
#define JT07022008_controls_tree_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#ifndef BUILDING_EGUI
#include "egui/events/tree.hpp"
#endif

namespace egui { 

namespace types {
    struct tree_item {
    };


    struct tree_state {
        enum type {
        };
    };
    struct tree_check_state {
        enum type {
        };
    };
    struct tree_style {
        enum type {
        };
    };
    struct tree_view {
        enum type {
        };
    };
    struct tree_column {
    };
}


namespace ctrl {

struct tree : control_base, handle_events::tree {
    using handle_events:: tree::events;
    using handle_events:: tree::events_type;
    typedef handle_events:: tree::ev ev;

    /// uniquely identifie a node
    typedef types::tree_item_id item_id;

    tree();
    ~tree();
    static string class_name();
    static types::int64 default_style() ;

/** 
reuturns the number of nodes
*/
property::r<int> count;
/** 
gets/sets the amount, in pixels, that child items are indented relative to their parent items
*/
property::rw<int> indent;
/** 
gets/sets an image list associated with the control:
*/
property::rw<temporary_image_list> images;

property_one_arg::rw<types::tree_item, item_id> item;
void insert_item(types::tree_item it, item_id parent, item_id after );
item_id add_item(item_id parent_item, const types::tree_item & info); // after last child
item_id add_root_item(const types::tree_item & info); 
void del_item(item_id id);
void del_all_items();

/** 
gest / sets the state of this item
*/
property_one_arg::rw<types::tree_state, item_id> state;

/** 
gets/sets the number of items that can be fully visible in the client window of a tree-view control.
*/
property::r<int> visible_count;

/** 
set/get whether an item is checked
*/
property_one_arg::rw<bool, item_id> check;
/** 
set/get the check state a certain item
*/
property_one_arg::rw<types::tree_check_state::type, item_id, types::tree_check_state> check_state;
/** 
gets/sets the text color
*/
property::rw<color> text_color;
/** 
gets/sets the background color
*/
property::rw<color> bg_color;
/** 
gets/sets the line color
*/
property::rw<color> line_color;
/** 
gets/sets the insert mark color
*/
property::rw<color> insertmark_color;

/** 
gets/sets the height of each tree item, in pixels.
*/
property::rw<int> item_height;
/** 
gets/sets the maximum scroll time for the control, in millis
*/
property::rw<int> scroll_time;

/** 
expands an item */
void expand(item_id h, types::tree_expand::type expand = types::tree_expand::expand );
/** 
collapses an item */
void collapse(item_id h);

/// returns first child of an item
item_id first_child(item_id h) const;
/// returns next sibling of an item
item_id next_sibling(item_id h) const;
/// returns prev sibling of an item
item_id prev_sibling(item_id h) const;
// note: not named "parent", to avoid confusion with window_base::parent()
item_id parent_item(item_id h) const;
/// returns next sibible item 
item_id next_visible(item_id h) const;
/// returns prev sibible item 
item_id prev_visible(item_id h) const;

property::r<item_id> root;
property::rw<item_id> first_visible;
property::rw<item_id> sel;
property::rw<item_id> drop_hilighted;

/** 
ensures that this item is visible
*/
void ensure_visible(item_id h);
/** 
returns the number of children this item has

Note; 
Don't use this within a looping-condition. Cache the value first, and then use it.

Example:

\code
for( int i = 0; i < children_count(h); ++i) { ... }  // **** BAD

int count = children_count(h);
for( int i = 0; i < count; ++i) { ... }  // **** GOOD
\endcode
*/
int children_count(item_id h) const;

private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
    copy_events<window_top> m_copy_events;
};


}}

#endif

