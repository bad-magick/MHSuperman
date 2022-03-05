// controls_tab.hpp

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


#ifndef JT07022008_controls_tab_HPP_DEFINED
#define JT07022008_controls_tab_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#ifndef BUILDING_EGUI
#include "egui/events/tab.hpp"
#endif

namespace egui { 

namespace types {
    struct tab_item {
        tab_item(const string & text = string(), int image_index = 0) : text(text), image_index(image_index), is_pressed(false), is_highlighted(false) {}
        string text;
        int image_index;
        bool is_pressed;
        bool is_highlighted;
    };

    struct tab_style {
        enum type {
            flat_separators = 1,
            register_drop = 2
        };
    };
}

namespace ctrl {

struct tab : control_base, handle_events::tab {
    using handle_events:: tab::events;
    using handle_events:: tab::events_type;
    typedef handle_events:: tab::ev ev;

    tab();
    ~tab();
    static string class_name();
    static types::int64 default_style() ;


/** 
gets/sets the image list for this control
*/
property::rw<temporary_image_list> images;
/** 
returns the number of items
*/
property::r<int> count;

/** 
gets/sets an item's details 
*/
property_one_arg::rw<types::tab_item, int> item;
/** 
returns the bounding rectangle for a certain tab in this tab control
*/
rectangle item_rect(int idx) const;

/** 
gets/sets the current selected tab
*/
property::rw<int> sel;

/** 
Sets the width and height of tabs in this control
*/
property_one_arg::w<size, int> item_size;
/** 
set the amount of padding around each tab's icon and label in a tab control
*/
property::w<size> item_padding;

/** 
returns the number of rows in a tab control (for multi-line tabs)
*/
property::r<int> row_count;

/** 
gets/sets the tab that has the focus
*/
property::rw<int> focused_item;

/** 
set the minimum width of items in a tab control
*/
property::w<int> min_item_width;
property::rw<types::tab_style::type,types::tab_style> tab_style;

void insert_item(types::tab_item it, int idx);
void del_item(int idx);
void del_all_items();

/** 
deselects all tabs
*/
void deselect_all(bool exclude_focus = true);
/** 
 sets the highlight state of a tab item
 */
void highlight_item(int idx, bool do_highlight = true);


private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
    copy_events<window_top> m_copy_events;
};

}}

#endif

