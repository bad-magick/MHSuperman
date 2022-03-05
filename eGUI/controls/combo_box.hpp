// controls_combo_box.hpp

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


#ifndef JT07022008_controls_combo_box_HPP_DEFINED
#define JT07022008_controls_combo_box_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#ifndef BUILDING_EGUI
#include "egui/events/combo_box.hpp"
#endif

namespace egui { namespace ctrl {

struct combo_box : control_base, handle_events::combo_box {
    using handle_events::combo_box ::events;
    using handle_events::combo_box ::events_type;
    typedef handle_events:: combo_box ::ev ev;


    combo_box();
    ~combo_box();
    static string class_name();
    static types::int64 default_style() ;

/// returns the number of items
property::r<int> item_count;
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

struct selection {
    int start, end;
    selection(int start = 0, int end = 0) : start(start), end(end) {}
};
/** 
get/set the selected text in the edit portion of the combo-box.
*/
property::rw<selection> edit_sel;
/// returns the text of an item within the combo
property_one_arg::r<string,int> item_text;
///get/set if the combo-box is dropped
property::rw<bool> is_dropped;
/// specifies the max. number of chars the user can enter
property::w<int> text_limit;

void del_all_items();

/** 
adds an item at the end
*/
void add_item(const string & str);
/** 
adds an item.

If the combo is sorted, the string is inserted into the list, and the list is sorted. 
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
/* finds the 'str' defs::string. It returns the index at which it was found,
or -1 otherwise.
*/
int find_str_exact(const string & str, int idx_start = -1);
/** 
finds a defs::string that begins with 'str'. If found, it selects it and
it returns its index. Otherwise, does nothing and returns -1.
*/
int select_str(const string & str, int idx_after = -1);

/** 
clears the current selection in a combo-box
*/
void clear();
/** 
does a "Cut"- to-clipboard
*/
void cut() ;
/** 
does a "copy" - to clipboard
*/
void copy() ;
/** 
does a "Paste" from clipboard
*/
void paste() ;

private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;

    copy_events<window_top> m_copy_events;
};

}}

#endif

