// controls_list_box.hpp

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


#ifndef JT07022008_controls_list_box_HPP_DEFINED
#define JT07022008_controls_list_box_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#ifndef BUILDING_EGUI
#include "egui/events/list_box.hpp"
#endif

namespace egui { namespace ctrl {

struct list_box : control_base, handle_events::list_box {
    using handle_events:: list_box::events;
    using handle_events:: list_box::events_type;
    typedef handle_events:: list_box::ev ev;


    static string class_name();
    static types::int64 default_style() ;
    list_box();
    ~list_box();

/// returns the number of items
property::rw<int> item_count;
/** 
get/set the current selection
*/
property::rw<int> sel;
/** 
get/set the first visible item
*/
property::rw<int> first_visible;
/** 
gets/sets the width, in pixels, by which the list box can be scrolled horizontally (the scrollable width). 
Aplicable only if the control has a horizontal scroll bar.
*/
property::rw<int> horizontal_extent;

property_one_arg::rw<bool, int> multi_sel;
property::r<int> sel_count;

property::rw<int> focused_item;

string item_text(int idx) const;

void del_all_items();
/** 
adds an item at the end
*/
void add_item(const string & str);
/** 
adds an item.

If the list is sorted, the string is inserted into the list, and the list is sorted. 
Otherwise, the string is added to the end of the list. 
*/
void add_sorted_item(const string & str);
/** 
deletes an item
*/
void del_item(int idx);
/** 
inserts an item
*/
void insert_item(int idx, const string & str);

/** 
finds a defs::string that begins with 'str'. It returns the index at which it was found,
or -1 otherwise.
*/
int find_str(const string & str, int idx_after = -1);
/** 
finds a defs::string that begins with 'str'. If found, it selects it and
it returns its index. Otherwise, does nothing and returns -1.
*/
int find_str_exact(const string & str, int idx_start = -1);
/** 
finds a defs::string that begins with 'str'. If found, it selects it and
it returns its index. Otherwise, does nothing and returns -1.
*/
int select_str(const string & str, int idx_after = -1);


private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
    copy_events<window_top> m_copy_events;
};

}}

#endif

