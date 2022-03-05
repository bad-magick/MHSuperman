// controls_slider.hpp

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


#ifndef JT07022008_controls_slider_HPP_DEFINED
#define JT07022008_controls_slider_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"

namespace egui { namespace ctrl {

struct slider : control_base, handle_events::slider {
//    using handle_events:: slider::events;
    slider();
    ~slider();
    static string class_name();
    static types::int64 default_style() ;

/** 
gets/sets the number of logical positions the slider moves in response to keyboard input from the arrow keys, 
such as the or keys. 

The logical positions are the integer increments in the control's range of minimum to maximum
*/
property::rw<int> line_size;
/** 
similar to slider::line_size, only that this is when the user presses keys as "Page Down", "Page Up"
*/
property::rw<int> page_size;
/** 
gets/sets the min position for a slider in this control
*/
property::rw<int> min_val;
/** 
gets/sets the max position for a slider in this control
*/
property::rw<int> max_val;
/** 
gets/sets the starting position of the current selection range 
*/
property::rw<int> sel_start;
/** 
gets/sets the end position of the current selection range 
*/
property::rw<int> sel_end;
/** 
gets/sets the position of the slider (it's within min_val and max_val)
*/
property::rw<int> pos;
/** 
Sets the interval frequency for tick marks
*/
property::w<int> tick_freq;

/** 
gets/sets the sliders' left buddy control
*/
property::rw< wnd<> > left_buddy;
/** 
gets/sets the sliders' right buddy control
*/
property::rw< wnd<> > right_buddy;
/** 
gets/sets the sliders' above buddy control
*/
property::rw< wnd<> > above_buddy;
/** 
gets/sets the sliders' below buddy control
*/
property::rw< wnd<> > below_buddy;

void clear_sel();
void clear_ticks();

private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
};

/** 
alias for slider control
*/
typedef slider track_bar; // alias

}}

#endif

