// controls_button.hpp

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


#ifndef JT07022008_controls_button_HPP_DEFINED
#define JT07022008_controls_button_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#ifndef BUILDING_EGUI
#include "egui/events/button.hpp"
#endif

namespace egui { 

namespace types {
    struct button_state {
        button_state() : is_checked(false), has_focus(false), is_indeterminate(false), is_pushed(false) {}
        bool is_checked;
        bool has_focus;
        bool is_indeterminate;
        bool is_pushed; 
    };

}
namespace ctrl {

struct button : control_base , handle_events::button {
    using handle_events:: button::events;
    using handle_events:: button::events_type;
    typedef handle_events:: button::ev ev;


    button();
    ~button();

    static string class_name();
    static types::int64 default_style() ;
    /*
    struct style {
        enum type {
            push_button = 0 ,
            default_ ,
            check_box ,
            auto_check_box ,
            radio_button ,
            three_state ,
            auto_three_state , 
            group_box,
            user_button,
            auto_radio_button,
            push_box,
            owner_draw
        };
    };
    */

/// get/set the state of this button
property::rw< types::button_state> state;

/** 
simulates a button's click
*/
void click();

private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
    copy_events<window_top> m_copy_events;
};

}}

#endif

