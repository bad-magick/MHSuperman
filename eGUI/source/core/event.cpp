// event.cpp

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

#include "stdafx_core.h"
#include "egui/core/wnd.hpp"


namespace egui {

namespace detail {
    void set_windows_msg(ev::base& event, unsigned long wm) {
        event.windows_msg = wm;
    }
    unsigned long get_windows_msg(const ev::base & event) {
        return event.windows_msg;
    }
}


event_handler_base ::event_handler_base () : m_funcs(new func_array) {
}
event_handler_base::event_handler_base(const event_handler_base & other) : m_funcs(other.m_funcs) {}


void event_handler_base ::operator()(window_top & w, egui::ev::base & event) {
    for ( func_array::iterator b = m_funcs->begin(), e = m_funcs->end(); b != e; ++b) {
        (**b)(w, event);
        if ( event.handled == ev::handled_fully)
            return;
    }
}




namespace ev {

base::base() 
    : handled(handled_partially)
    , result(0)
    , windows_msg(0)
    , wparam(0)
    , lparam(0) 
    , do_default_processing(false)
    {
}

destroy::destroy(wnd<> w) {
    destination = w;
    egui::detail::set_windows_msg(*this, WM_DESTROY);
}

void base::before_handle() {}
void base::after_handle() {}



}}

// End of file
