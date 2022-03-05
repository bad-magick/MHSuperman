// controls_spina.hpp

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


#ifndef JT07022008_controls_spina_HPP_DEFINED
#define JT07022008_controls_spina_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#ifndef BUILDING_EGUI
#include "egui/events/spin_button.hpp"
#endif

namespace egui { namespace ctrl {

struct spin_button : control_base, handle_events::spin_button {
    using handle_events:: spin_button::events;
    using handle_events:: spin_button::events_type;
    typedef handle_events:: spin_button::ev ev;

    spin_button();
    ~spin_button();
    static types::int64 default_style() ;
    static string class_name();

struct accel {
    /// Amount of elapsed time, in seconds, before the position change increment specified by nInc is used. 
    int sec;
    /// Position change increment to use after the time specified by sec elapses. 
    int increment;
};
typedef std::vector<accel> accel_array;

/** 
gets/sets a vector of accel values with acceleration information
*/
property::rw<accel_array> accels;
/** 
gets/sets the current radix base (that is, either base 10 or 16) 
*/
property::rw<int> radix_base;

/** 
gets/sets this spin's buddy control
*/
property::rw< wnd<> > buddy;
/** 
gets/sets the position of the spin-control
*/
property::rw<int> pos;

/** 
gets/sets the min. allowed value
*/
property::rw<int> min_val;
/** 
gets/sets the max. allowed value
*/
property::rw<int> max_val;


private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
    copy_events<window_top> m_copy_events;
};

/** 
alias for spin-button
*/
typedef spin_button updown; 

}}

#endif

