// controls_list.hpp

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


#ifndef JT07022008_controls_list_HPP_DEFINED
#define JT07022008_controls_list_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#ifndef BUILDING_EGUI
#include "egui/events/list.hpp"
#endif

namespace egui { 

namespace types {

    struct list_image {
        enum type {
            normal = 0,
            small,
            state
        };
    };

    struct list_item {
        list_item() : state(0), image_index(0), indent(0) {}
        /// see list_item_state::type
        int state;
        int image_index;
        int indent;
        string text;
    };

    struct list_style {
        enum type {
            grid_lines = 1,
            sub_item_images = 2, 
            check_boxes = 4,
            track_select = 8,
            header_drag_drop = 16,   
            full_row_select = 32, 
            one_click_activate = 64, 
            double_click_activate = 128, 
            flat_scroll_bar = 0x00000100,
            regional = 0x00000200,
            info_tip = 0x00000400,
            underline_hot = 0x00000800,    
            underline_cold = 0x00001000,    
            multi_work_areas = 0x00002000,   
            label_tip = 0x00004000       ,
            border_select = 0x00008000
        };
    };
    struct list_view {
        enum type {
            icon = 0,
            list = 3,
            report = 1,
            small_icon = 2
        };
    };
    struct list_column {
        list_column() : width(0), original_index(0), image_index(0), cur_index(0) {}
        int width;
        int original_index;
        int image_index;
        int cur_index;
        string text;
    };
}

namespace ctrl {

struct list : control_base, handle_events::list {
    using handle_events:: list::events;
    using handle_events:: list::events_type;
    typedef handle_events:: list::ev ev;

    list();
    ~list();
    static string class_name();
    static types::int64 default_style() ;

/** 
gets/setsthe background color
*/
property::rw<color> bg_color;
/** 
gets/sets the text color
*/
property::rw<color> text_color;
/** 
gets/sets the text background color 
*/
property::rw<color> text_bg_color;

/** 
gets/sets the images */
property_one_arg::rw<temporary_image_list, types::list_image::type, types::list_image> images;
/** 
gets/sets the number of items
*/
property::rw<int> item_count;

property_one_arg::rw<types::list_item, int> item;
void insert_item(const types::list_item &it, int idx);
/** 
deletes an item
*/
void del_item(int idx);
/** 
deletes all items
*/
void del_all_items();

/** 
gets/sets the position of an item
*/
property_one_arg::rw<point, int> item_pos;

/** 
gets/sets the exact width, in pixels, of the specified defs::string (using the current list control's
font)
*/
int string_width(const string & text);

/** 
gets/sets the width of a column (for report or list view)
*/
property_one_arg::rw<int, int> col_width;

property::r<int> first_visible;
/** 
returns the number of selected items
*/
property::r<int> sel_count;
/** 
returns the number of columns
*/
property::r<int> col_count;

typedef std::vector<int> order_array;
/** 
gets/sets the current left-to-right order of columns 
*/
property::rw<order_array> colum_orders;

property::r< wnd<> > header;

property_one_arg::rw< types::list_item_state::type, int, types::list_item_state> state;
/** 
gets/sets the current selected item
*/
property::rw< int> sel;

/** 
gets/sets list-control specific extended style 
*/
property::rw< types::list_style::type, types::list_item_state> list_style; // FIXME i think this is wrong

/** 
checks/unchecks this item (for list-controls with check-boxes)
*/
property_one_arg::rw<bool, int> check;

/** 
returns the list control's view type 
*/
property::rw<types::list_view::type, types::list_view> view_type;

property_one_arg::rw<types::list_column, int> col;
void insert_col(const types::list_column & col, int idx);
/** 
deletes a column
*/
void del_col(int idx);

void ensure_visible(int idx, bool partially_ok = false);
/** 
scrolls 
*/
void scroll(size sz);
/** 
updates an item.

If the control has the auto_arrange style, it causes it to be arranged

*/
void update_item(int idx);

types::list_item sub_item(int idx, int sub_idx) const;
void sub_item(int idx, int sub_idx, const types::list_item & val);


    // FIXME item_rect, count_per_page
private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
    copy_events<window_top> m_copy_events;
};

}}

#endif

