// handle_event_base.hpp

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


#ifndef JT07022008_handle_event_base_HPP_DEFINED
#define JT07022008_handle_event_base_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace egui { 


namespace handle_events {
    struct window_top {
        struct ev {
            // the events
            struct move;
            struct size;
            struct activate;
            struct enable;
            struct set_redraw;
            struct close;
            struct quit;
            struct show;
            struct set_cursor;
            struct help;
            struct timer;
            struct horiz_scroll;
            struct vert_scroll;
            struct enter_idle;
            struct sizing;
            struct moving;

            struct paint;
            struct erase_bg;
            struct key_press;
            struct char_;
            struct set_focus;
            struct kill_focus;
            struct mouse_move;
            struct mouse_click;
            struct mouse_double_click;
            struct menu;

            typedef egui::ev::base notify;
        };

        // the handlers
        virtual void on_move( ev::move & ) {}
        virtual void on_size( ev::size & ) {}
        virtual void on_activate( ev::activate & ) {}
        virtual void on_enable( ev::enable & ) {}
        virtual void on_set_redraw( ev::set_redraw & ) {}
        virtual void on_close( ev::close & ) {}
        virtual void on_quit( ev::quit & ) {}
        virtual void on_show( ev::show & ) {}
        virtual void on_set_cursor( ev::set_cursor & ) {}
        virtual void on_help( ev::help & ) {}
        virtual void on_timer( ev::timer & ) {}
        virtual void on_horiz_scroll( ev::horiz_scroll & ) {}
        virtual void on_vert_scroll( ev::vert_scroll & ) {}
        virtual void on_enter_idle( ev::enter_idle & ) {}
        virtual void on_sizing( ev::sizing & ) {}
        virtual void on_moving( ev::moving & ) {}

        virtual void on_paint( ev::paint & ) {}
        virtual void on_erase_bg( ev::erase_bg & ) {}
        virtual void on_key_press( ev::key_press & ) {}
        virtual void on_char_( ev::char_ & ) {}
        virtual void on_set_focus( ev::set_focus & ) {}
        virtual void on_kill_focus( ev::kill_focus & ) {}
        virtual void on_mouse_move( ev::mouse_move & ) {}
        virtual void on_mouse_click( ev::mouse_click & ) {}
        virtual void on_mouse_double_click( ev::mouse_double_click & ) {}
        virtual void on_menu_command(ev::menu&) {}
        virtual void on_notify(ev::notify&) {}

        struct events_type {
            event_handler < ev::move  > on_move;
            event_handler < ev::size  > on_size;
            event_handler < ev::activate  > on_activate;
            event_handler < ev::enable  > on_enable;
            event_handler < ev::set_redraw  > on_set_redraw;
            event_handler < ev::close  > on_close;
            event_handler < ev::quit  > on_quit;
            event_handler < ev::show  > on_show;
            event_handler < ev::set_cursor  > on_set_cursor;
            event_handler < ev::help  > on_help;
            event_handler < ev::timer  > on_timer;
            event_handler < ev::horiz_scroll  > on_horiz_scroll;
            event_handler < ev::vert_scroll  > on_vert_scroll;
            event_handler < ev::enter_idle  > on_enter_idle;
            event_handler < ev::sizing  > on_sizing;
            event_handler < ev::moving  > on_moving;
            event_handler < ev::paint  >  on_paint;
            event_handler < ev::erase_bg  > on_erase_bg;
            event_handler < ev::key_press  > on_key_press;
            event_handler < ev::char_  > on_char_;
            event_handler < ev::set_focus  > on_set_focus;
            event_handler < ev::kill_focus  > on_kill_focus;
            event_handler < ev::mouse_move  > on_mouse_move;
            event_handler < ev::mouse_click  > on_mouse_click;
            event_handler < ev::mouse_double_click  > on_mouse_double_click;
            event_handler < ev::menu> on_menu_command;
            event_handler < ev::notify> on_notify;
        } events;
    };

}}



#endif

