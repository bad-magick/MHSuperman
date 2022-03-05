// controls_month_cal.hpp

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


#ifndef JT07022008_controls_month_cal_HPP_DEFINED
#define JT07022008_controls_month_cal_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#include <time.h>
#ifndef BUILDING_EGUI
#include "egui/events/month_cal.hpp"
#endif

namespace egui { 
    
namespace types {
    struct month_cal_color {
        enum type {
            // note: they match the values from commctrl.h
            bg = 0,
            text,
            title_bg,
            title_text,
            month,
            trailing_text 
        };
    };
}

namespace ctrl {

struct month_cal : control_base, handle_events::month_cal {
    using handle_events:: month_cal::events;
    using handle_events:: month_cal::events_type;
    typedef handle_events:: month_cal::ev ev;

    month_cal();
    ~month_cal();
    static string class_name();
    static types::int64 default_style() ;

/** 
gets/sets the calendar color

*/
property_one_arg::rw<color, types::month_cal_color::type, types::month_cal_color> color;
/// the date we're showing
property::rw<time_t> sel;
/** 
gets/sets
the first day of the week (0-Monday up to 6-Sun)*/
property::rw<int> first_day_of_week;
/// if true, uses locale to compute first day of week
property::r<bool> uses_locale;

/** 
gets/sets the maximum date range that can be selected in a month calendar control.
*/
property::rw<int> max_sel_count;

/** 
gets/sets the number of months that the control moves its display when the user clicks a scroll button
*/
property::rw<int> month_delta;

/// get/set the min date this control allows the user to manipulate
property::rw<time_t> min_time;
/// get/set the max date this control allows the user to manipulate
property::rw<time_t> max_time;

struct selection {
    time_t start, end;
    selection(time_t start = 0, time_t end = 0) : start(start), end(end) {}
};
/** 
gets/sets the upper and lower limits of the date range currently selected by the user
(in case the control allows multiple selection)
*/
property::rw<selection> sel_range;  
/** 
gets/sets the date specified as "today" for a month calendar control
*/
property::rw<time_t> today;

private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
    copy_events<window_top> m_copy_events;
};

}}

#endif

