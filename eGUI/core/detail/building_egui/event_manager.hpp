// event_manager.hpp

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


#ifndef JT07022008_event_manager_HPP_DEFINED
#define JT07022008_event_manager_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef BUILDING_EGUI
#error Donot include this in client code
#endif

#include "egui/core/wnd.hpp"
#include <map>
#include "egui/core/detail/building_egui/wnd_msg.hpp"
#include "egui/core/detail/building_egui/wrap_events.hpp"

namespace egui { namespace detail {

// a command coming from a menu
extern UINT g_wm_menu_command ;
extern UINT g_new_event;

struct event_manager {
private:
    event_manager();
public:
    static event_manager& inst();

    LRESULT handle(HWND h, UINT msg, WPARAM wParam, LPARAM lParam, bool is_form_message);

    void add_wait_for(window_top * w, const ev::base & event);
    LRESULT send_win32_event(const wnd<> & dest, UINT msg, WPARAM w = 0, LPARAM l = 0);

    void send_new_event(egui::ev::new_event_base& evt, window_top * dest);

    WPARAM get_wparam(const ev::base & event) const { return (WPARAM)event.wparam; }
    LPARAM get_lparam(const ev::base & event) const { return (LPARAM)event.lparam; }

    void add_window_events(const window_event_coll &events);
    void add_call_on_event(const event_call_coll & call_on_event);
    void add_event_handlers_for_window(window_top * w);

    void register_new_event_handler(const std::type_info & event_type, new_event_caller_ptr caller) ;

private:
    void handle_wait_for(window_top* w, const ev::base & event);
    void del_wait_for(window_top* w);

    void pre_handle_event(ev::base & event);
    void post_handle_event(ev::base & event);

    bool call_event_handler(ev::base & event);

    void call_new_event_handler(window_top * w, ev::base & event);

private:
    typedef boost::shared_ptr<ev::base> event_ptr;
    event_ptr create_event_from_msg(wnd<> w, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    critical_section cs;
    typedef std::map<window_top*, UINT> wait_for_coll;
    // for a certain window - what are we waiting for?
    wait_for_coll m_wait_for;

    // events each window can receive
    // key (window type) -> all possible events it can receive
    window_event_coll m_events;

    // once the event is created, we know what handler to call
    event_call_coll m_call_on_event;

    // for new events, who to call
    typedef std::vector<new_event_caller_ptr> new_event_caller_ptr_array;
    typedef std::map<typeinfo_holder, new_event_caller_ptr_array> new_event_caller_ptr_coll;
    new_event_caller_ptr_coll m_new_event_handlers;

};

}

// helper
inline LRESULT send_win32_event(const wnd<> & dest, UINT msg, WPARAM w = 0, LPARAM l = 0) {
    return detail::event_manager::inst().send_win32_event(dest, msg, w, l);
}

inline LRESULT send_win32_event(const wnd<> & dest, UINT msg, WPARAM w, const void* l ) {
    return detail::event_manager::inst().send_win32_event(dest, msg, w, (LPARAM)l);
}

LRESULT send_win32_event(const wnd<> & dest, const wnd_msg & msg);

}

#endif

