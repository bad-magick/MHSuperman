// window_top.hpp

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


#ifndef JT07022008_events_window_top_HPP_DEFINED
#define JT07022008_events_window_top_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/events/detail/fwd.hpp"


namespace egui { namespace handle_events {

///////////////////////////////////////////////////////////////////////////////////////////////
// General

struct window_top::ev:: move : event_module_base { 
    // if you want to know where you are, use full_rect
    void init_event();
};

struct window_top::ev:: size : event_module_base { 
    // if you want to know where you are, use full_rect
    void init_event();
};

struct window_top::ev:: activate : event_module_base {
    void init_event();

    /// if true, by mouse - otherwise, unknown
    read_only<bool> by_mouse;
    /// true if we've activated this window, false otherwise
    read_only<bool> is_active;
    /// if true, focus was previously on another application
    read_only<bool> from_other_app;
};

struct window_top::ev:: enable : event_module_base { 
    enable();

    read_only<bool> enabled;
};

struct window_top::ev:: set_redraw : event_module_base {
    set_redraw();

    read_only<bool> redraw_state;
};

struct window_top::ev:: close : event_module_base { 
    void init_event();
};

struct window_top::ev:: quit : event_module_base { 
    void init_event();
};

struct window_top::ev:: show : event_module_base { 
    show();
    read_only<bool> shown;
};


struct window_top::ev:: set_cursor : event_module_base { 
    set_cursor();
};


struct window_top::ev:: help : event_module_base { 
    void init_event();
};

struct window_top::ev:: timer : event_module_base { 
    timer();
    read_only<int> id;
};

struct scroll_pos {
    enum type {
          line_up       = 0
        , line_down     
        , page_up       
        , page_down     
        , thumb_position
        , thumb_track   
        , top          
        , right        
        , end_scroll    

        , line_left     = 0
        , line_right    
        , page_left     
        , page_right    

        , left         = 6
        , bottom       
    };
};
struct window_top::ev:: horiz_scroll : event_module_base { 
    horiz_scroll();

    read_only<scroll_pos::type> scroll_pos;
    read_only<int> thumb_pos;
};

struct window_top::ev:: vert_scroll : event_module_base { 
    vert_scroll();

    read_only<scroll_pos::type> scroll_pos;
    read_only<int> thumb_pos;
};

struct window_top::ev:: enter_idle : event_module_base { 
    void init_event();
};

struct window_top::ev:: sizing : event_module_base { 
    void init_event();
};

struct window_top::ev:: moving : event_module_base { 
    void init_event();

};


///////////////////////////////////////////////////////////////////////////////////////////////
// Draw


/** paint event

    if you handle this event, set do_default_proessing to false
*/
struct window_top::ev:: paint : event_module_base {
    paint();

    enum type {
        paint_,
        print,
        print_client,
        sync_paint,
        nc_paint
    };

    read_only<type> paint_type;
};

/** erase background

    if you handle this event, set do_default_proessing to false
*/
struct window_top::ev:: erase_bg : event_module_base {
    void init_event();

    read_only<void *> dc;
    bool erase_done; // in/out
};

///////////////////////////////////////////////////////////////////////////////////////////////
// key

struct window_top::ev:: key_press : event_module_base {
    void init_event();

    /// if true, pressed; if false, de-pressed
    read_only<bool> pressed;
    read_only<int> key_code;
    /// if true, it's a system key
    read_only<bool> is_sys_key;
};

struct window_top::ev:: char_ : event_module_base {
    enum type {
        character,
        dead_char,
        sys_char,
        sys_dead_char
    };

    void init_event();

    read_only<int> char_code;
    read_only<type> char_type;
};

struct window_top::ev:: set_focus : event_module_base {
    void init_event();
};

struct window_top::ev:: kill_focus : event_module_base {
    void init_event();
};

///////////////////////////////////////////////////////////////////////////////////////////////
// mouse

struct window_top::ev:: mouse_move : event_module_base {
    void init_event();
};

struct window_top::ev:: mouse_click : event_module_base {
    enum type {
        left, 
        right,
        middle
    };

    void init_event();

    read_only<bool> down;
    read_only<bool> in_non_client_area;
    read_only<type> button_type;
};

struct window_top::ev:: mouse_double_click : event_module_base {
    enum type {
        left, 
        right,
        middle
    };

    void init_event();

    read_only<type> button_type;
    read_only<bool> in_non_client_area;
};


struct window_top::ev::menu : event_module_base {
    void init_event();
    int id;
};



///////////////////////////////////////////////////////////////////////////////////////////////
// 


}}

#endif

