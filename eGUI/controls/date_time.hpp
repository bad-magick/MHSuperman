// controls_date_time.hpp

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


#ifndef JT07022008_controls_date_time_HPP_DEFINED
#define JT07022008_controls_date_time_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#include "egui/controls/month_cal.hpp"
#include <time.h>
#ifndef BUILDING_EGUI
#include "egui/events/date_time.hpp"
#endif

namespace egui { 
    
namespace ctrl {


struct date_time : control_base, handle_events::date_time {
    using handle_events::date_time ::events;
    using handle_events::date_time ::events_type;
    typedef handle_events:: date_time ::ev ev;


    date_time();
    ~date_time();

    static string class_name();
    static types::int64 default_style() ;

    /** 
    sets the format defs::string for showing the date

    - @c "d"   one-  or two-digit day.  
    - @c "dd"   two-digit day. Single-digit day values are preceded by a zero.  
    - @c "ddd"   three-character weekday abbreviation.  
    - @c "dddd"   full weekday name.  
    - @c "h"   one-  or two-digit hour in 12-hour format.  
    - @c "hh"   two-digit hour in 12-hour format. Single-digit values are preceded by a zero.  
    - @c "H"   one-  or two-digit hour in 24-hour format.  
    - @c "HH"   two-digit hour in 24-hour format. Single-digit values are preceded by a zero.  
    - @c "m"   one-  or two-digit minute.  
    - @c "mm"   two-digit minute. Single-digit values are preceded by a zero.  
    - @c "M"   one-  or two-digit month number.  
    - @c "MM"   two-digit month number. Single-digit values are preceded by a zero.  
    - @c "MMM"   three-character month abbreviation.  
    - @c "MMMM"   full month name.   
    -"t"   one-letter AM/PM abbreviation (that is, AM is displayed as "A").  
    - @c "tt"   two-letter AM/PM abbreviation (that is, AM is displayed as "AM").  
    - @c "yy"   last two digits of  year 
    - @c "yyyy"   full year

    */
    property::w<string> format;


/** 
get/set the color for a given portion of the control.
*/
property_one_arg::rw<types::color, types::month_cal_color::type, types::month_cal_color> color;
/// the date we're showing
property::rw<time_t> sel;

/// get/set the min date this control allows the user to manipulate
property::rw<time_t> min_time;
/// get/set the max date this control allows the user to manipulate
property::rw<time_t> max_time;
/// Returns the Month-calendar window, if any is shown on-screen
property::r< wnd<month_cal> > month_cal_ctrl;
/// gets/sets the font of the month-calendar window, if any is shown on-screen
property::rw<types::temporary_font> font;

private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
    copy_events<window_top> m_copy_events;
};

}}

#endif

