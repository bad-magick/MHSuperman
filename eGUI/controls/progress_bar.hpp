// controls_progress_bar.hpp

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


#ifndef JT07022008_controls_progress_bar_HPP_DEFINED
#define JT07022008_controls_progress_bar_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#ifndef BUILDING_EGUI
#include "egui/events/progress_bar.hpp"
#endif

namespace egui { namespace ctrl {

struct progress_bar : control_base, handle_events::progress_bar {
//    using handle_events:: progress_bar::events;
    progress_bar();
    ~progress_bar();
    static string class_name();
    static types::int64 default_style() ;

/** 
gets/sets the min limit of the progress bar
*/
property::rw<int> min_val;
/** 
gets/sets the max limit of the progress bar
*/
property::rw<int> max_val;
/** 
gets/sets the current position within a progress bar
*/
property::rw<int> pos;
/** 
specifies the step increment for the progress bar. This is 
the amount by which the progress bar increases its current position whenever you step_it. 
By default, it's set to 10
*/
property::w<int> step;
/** 
gets/sets the bar's color
*/
property::rw<types::color> bar_color;
/** 
gets/sets the bar's background color
*/
property::rw<types::color> bg_color;

/** 
steps through the bar
\sa step
*/
void step_it();

private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
};

}}

#endif

