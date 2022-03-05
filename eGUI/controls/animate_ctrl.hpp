// controls_animate.hpp

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


#ifndef JT07022008_controls_animate_HPP_DEFINED
#define JT07022008_controls_animate_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"

#ifndef BUILDING_EGUI
#include "egui/events/animate_ctrl.hpp"
#endif

namespace egui { namespace ctrl {

struct animate_ctrl : control_base, handle_events::animate_ctrl {
    using handle_events::animate_ctrl ::events;
    using handle_events::animate_ctrl ::events_type;
    typedef handle_events:: animate_ctrl ::ev ev;


    animate_ctrl();
    ~animate_ctrl();
    static string class_name();
    static types::int64 default_style() ;

/** 
opens the AVI having this resource ID
*/
void open(int avi_id);
/** 
opens the AVI having the given file name
*/
void open(const string & file_name);

/** 
plays the animation
@param from - the index of the frame to start
@param to - the index of the frame to end
@param repeat - how many times to replay 
*/
void play(unsigned from, unsigned to, unsigned repeat = 0);
/** 
stops the animation
*/
void stop();
/** 
closes the animation, if any
*/
void close();
/** 
seeks to a frame
*/
void seek(unsigned to);

private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;

    copy_events<window_top> m_copy_events;
};

}}

#endif

