// controls_status_bar.hpp

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


#ifndef JT07022008_controls_status_bar_HPP_DEFINED
#define JT07022008_controls_status_bar_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#ifndef BUILDING_EGUI
#include "egui/events/status_bar.hpp"
#endif

namespace egui { 

namespace types {
}
    
namespace ctrl {

struct status_bar : control_base, handle_events::status_bar {
    using handle_events:: status_bar::events;
    using handle_events:: status_bar::events_type;
    typedef handle_events:: status_bar::ev ev;

    status_bar();
    ~status_bar();
    static string class_name();
    static types::int64 default_style() ;

property::r<int> horiz_border;
property::r<int> vert_border;
property::r<int> spacing_border;


/** 
gets/sets the icon for this pane
*/
property_one_arg::rw<types::temporary_icon, int> pane_icon;
/** 
returns the bounding rectangle of a pane
*/
property_one_arg::r<rectangle, int> pane_rect;

/** 
gets/sets the text of a certain pane
*/
property_one_arg::rw<string, int> pane_text;
/** 
gets/sets the tooltip text of a certain pane
*/
property_one_arg::rw<string, int> pane_tip_text;

/** 
Sets or gets the "simple mode". 

In case a status bar is in simple mode, it will show only one pane.
And, you can set its text using the text property
*/
property::rw<bool> simple;

/** 
sets the status' background color
*/
property::w<color> bg_color;
/** 
sets the min height of the status' drawing area
*/
property::w<int> min_height;

/** 
gets/sets the width of each pane
*/
property::rw< std::vector<int> > pane_widths;

private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
    copy_events<window_top> m_copy_events;
};

}}

#endif

