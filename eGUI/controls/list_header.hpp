// controls_list_header.hpp

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


#ifndef JT07022008_controls_list_header_HPP_DEFINED
#define JT07022008_controls_list_header_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#ifndef BUILDING_EGUI
#include "egui/events/list_header.hpp"
#endif

namespace egui { 

namespace types {
    struct list_header_item {
        int width;
        string text;
        int image_index;
        int column_index;

        // FIXME fmt
    };
}

namespace ctrl {

struct list_header : control_base, handle_events::list_header {
    using handle_events:: list_header::events;
    using handle_events:: list_header::events_type;
    typedef handle_events:: list_header::ev ev;

    list_header();
    ~list_header();
    static string class_name();
    static types::int64 default_style() ;

property::r<int> item_count;
/** 
gets/sets the images */
property::rw<temporary_image_list> images;

typedef std::vector<int> order_array;
/** 
gets/sets the current left-to-right order of items in a header control
*/
property::rw<order_array> colum_orders;

property_one_arg::rw<types::list_header_item, int> item;
void insert_item(const types::list_header_item &val, int idx);
void del_item(int idx);


private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
    copy_events<window_top> m_copy_events;
};

}}

#endif

