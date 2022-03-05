// controls_tooltip.hpp

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


#ifndef JT07022008_controls_tooltip_HPP_DEFINED
#define JT07022008_controls_tooltip_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"

namespace egui { 
    
namespace types {
    
    /** 
    \brief Allows manipulating the properties of an area/control within a certain tooltip control, 
    also know as a "tool".
    */
    struct tooltip_area {
        tooltip_area (const wnd<> & w) ;
        tooltip_area(const window_top * w) ;
        tooltip_area(const wnd<> & parent, const wnd<> & h) ;
        tooltip_area(const wnd<> & w, unsigned short id, const rectangle & r);
    private:
        void compute_from_handle(wnd_id_type h) ;
    public:
        wnd_id_type hwnd;
        void* id;
        rectangle rect; // in case it's a rectangular area in the hwnd
    };


    /** 
        @brief possible values for the tooltip title

        @sa tooltip::title
    */
    struct tooltip_title {
        enum type {
            none = 0,
            info = 1,
            warning = 2,
            error = 3
        };
    };

}


namespace ctrl {

struct tooltip : control_base, handle_events::tooltip {
//    using handle_events:: tooltip::events;
    typedef types::tooltip_area area;
    tooltip();
    ~tooltip();
    static string class_name();
    static types::int64 default_style() ;

/**
activates or deactivates a tooltip control
*/
property::w<bool> active;

/**
adds a tool to be monitored by this tooltip control
*/
void add_tool( area h);
/**
deletes a tool
*/
void del_tool( area h);

/**
gets/sets the width and height of a tooltip control
*/
property_one_arg::r<types::size, area> size;

/**
gets/sets the initial delay time (the time the mouse should be still, before showing the tooltip)
*/
property::rw<int> initial_delay_time;
/**
gets/sets the popup time (the time the tooltip is shown, if the mouse is within the tool)
*/
property::rw<int> popup_delay_time;
/**
gets/sets the reshow time (the time it takes the tooltip to be shown again, once it disappeared)
*/
property::rw<int> reshow_delay_time;

/**
get/set the top, left, bottom, and right margins set for a tooltip control.

Each margin is the distance, in pixels, between the tooltip control border 
and the text contained within the tooltip control. 

*/
property::rw<rectangle> margins;
/**
gets/sets the max width of the control

if a text defs::string exceeds the maximum width, the tooltip control breaks the text into 
multiple lines, using spaces to determine line breaks
*/
property::rw<int> max_width;
/**
gets/sets the background color
*/
property::rw<color> bg_color;
/**
gets/sets the text color
*/
property::rw<color> text_color;
/**
returns the number of tools this tooltip control manages
*/
property::r<int> tool_count;

/**
gets/sets the tip text for a tool
*/
property_one_arg::rw<string, area> tip_text;
/**
gets/sets the rectangle the tooltip will monitor, for a given tool
*/
property_one_arg::rw<rectangle, area> rect;

/**
pops (hides) the tooltip text, if it's shown
*/
void pop();

/**
relays an event to the tooltip
*/
void relay_event(const egui::ev::base & event);

void title(const string & str, types::tooltip_title::type t = types::tooltip_title::none );
/**
forces the tooltip to be redrawn.
*/
void update();

private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;

};

}}

#endif

