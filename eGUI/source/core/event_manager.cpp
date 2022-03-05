// event_manager.cpp

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
#include "egui/core/detail/building_egui/event_manager.hpp"
#include "egui/core/detail/window_manager.hpp"
#include <boost/foreach.hpp>
#include <sstream>
#include "egui/core/detail/log.hpp"

#ifdef _MSC_VER
#pragma warning ( disable : 4244)
#endif

namespace egui { namespace detail {

    // FIXME this needs to be process dependent (must be prefixed by process id)
    UINT g_wm_menu_command = ::RegisterWindowMessage( GUI_STR("egui_menu"));
    UINT g_new_event = ::RegisterWindowMessage( GUI_STR("egui_new_event"));

namespace {

    LRESULT dialog_result(HWND h, UINT msg, LRESULT result, bool was_processed) {
	    switch (msg) {
        case WM_COMPAREITEM:
        case WM_VKEYTOITEM:
        case WM_CHARTOITEM:
        case WM_INITDIALOG:
        case WM_QUERYDRAGICON:
        case WM_CTLCOLORMSGBOX:
        case WM_CTLCOLOREDIT:
        case WM_CTLCOLORLISTBOX:
        case WM_CTLCOLORBTN:
        case WM_CTLCOLORDLG:
        case WM_CTLCOLORSCROLLBAR:
        case WM_CTLCOLORSTATIC:
            // return directly
            return result;
        }
            // return in DWL_MSGRESULT
        #ifdef _MSC_VER
        #pragma warning(push)
        #pragma warning (disable : 4244) //: 'argument' : conversion from 'LRESULT' to 'LONG', possible loss of data
        #endif
        ::SetWindowLongPtr( h, DWLP_MSGRESULT, result);
        #ifdef _MSC_VER
        #pragma warning(pop)
        #endif
        return was_processed ? TRUE : FALSE;
    }

    typedef std::vector<HWND> hwnd_array;
    BOOL CALLBACK enum_wnd(HWND hwnd, LPARAM lParam) {
        hwnd_array *a = reinterpret_cast<hwnd_array*>(lParam);
        a->push_back(hwnd);
        return true;
    }
    void find_descendant_windows( hwnd_array & children, HWND h) {
        assert (h);
        ::EnumChildWindows( h, &enum_wnd, reinterpret_cast<LPARAM>(&children));
    }

}



event_manager::event_manager() {
}
event_manager& event_manager::inst() {
    static event_manager e;
    return e;
}


LRESULT event_manager::handle(HWND h, UINT msg, WPARAM wParam, LPARAM lParam, bool is_form_message) {
    wnd<> w = window_manager::inst().existing_window_from_id(h);
    if ( w) {
        event_ptr event = create_event_from_msg(w, msg, wParam, lParam);
        pre_handle_event(*event);
        if ( event->handled != ev::handled_fully)
            w->do_on_any_event( *event);
        post_handle_event(*event);
        handle_wait_for(w.m_window, *event);

        event->before_handle();
        bool have_called_at_least_one_handler = call_event_handler( *event) ;
        event->after_handle();
        if ( have_called_at_least_one_handler && !event->do_default_processing) {
            // event was handled
            if ( is_form_message)
                return (LRESULT)dialog_result(h, msg, event->result, !event->do_default_processing);
            else
                return event->result;
        }
        else {
            // do default processing
            window_internal_info info = window_manager::inst().internal_info(h);
            if ( info.old_wnd_proc)
                return CallWindowProc( info.old_wnd_proc, h, msg, wParam, lParam);
            else if ( info.old_dlg_proc) {
                LRESULT result = CallWindowProc( reinterpret_cast<WNDPROC>(info.old_dlg_proc), h, msg, wParam, lParam);
                return result;
                //return dialog_result(h, msg, result, true);
            }
            // no other procs to call
            if ( is_form_message)
                return dialog_result(h, msg, 0, false);
            else
                return ::DefWindowProc(h, msg, wParam, lParam);
        }

    }
    else {
        // there's no window for this handle (yet) - do default
        if ( is_form_message)
            return dialog_result(h, msg, 0, false);
        else
            return ::DefWindowProc(h, msg, wParam, lParam);
    }
    return 0;
}


/** 
    Marks this window as waiting for a certain event - that is, we're in wait_for() a certain event
*/
void event_manager::add_wait_for(window_top * w, const ev::base & event) {
    { scoped_lock lk(w->cs);
    w->m_is_waiting = true;
    }

    { scoped_lock lk(cs);
      m_wait_for[ w ] = event.windows_msg;
    }
}

void event_manager::del_wait_for(window_top* w) {
    { scoped_lock lk(w->cs);
    w->m_is_waiting = false;
    }

    scoped_lock lk(cs);
    m_wait_for.erase(w);
}

void event_manager::handle_wait_for(window_top* w, const ev::base & event) {
    unsigned long wm = 0;
    { scoped_lock lk(cs);
      wm = m_wait_for[w];
    }
    // note: when receiving Destroy - that's the last message - no matter what the user is waiting for, 
    //       we're exiting
    if ( (wm > 0 && event.windows_msg == wm) || event.windows_msg == WM_DESTROY) 
        del_wait_for(w);

    if ( event.windows_msg == WM_DESTROY) {
        // when waiting for an event and we close the parent window:
        // ALL children + descendants need to "stop waiting"
        hwnd_array children;
        find_descendant_windows(children, get_hwnd(w));
        BOOST_FOREACH(HWND h, children)
            if ( wnd<> w = window_manager::inst().existing_window_from_id(h))
                del_wait_for( w.m_window);
    }

}

void event_manager::pre_handle_event(ev::base & event) {
}
void event_manager::post_handle_event(ev::base & event) {
    if ( event.windows_msg == WM_SYSCOMMAND)
        if ( event.wparam == SC_CLOSE)
            if ( event.destination)
                if ( event.destination->can_close())
                    ::DestroyWindow( get_hwnd(event.destination) );
}

LRESULT event_manager::send_win32_event(const wnd<> & dest, UINT msg, WPARAM w, LPARAM l) {
    return ::SendMessage( get_hwnd(dest), msg, w, l);
}
} // namspace detail
LRESULT send_win32_event(const wnd<> & dest, const wnd_msg & msg) {
    return send_win32_event( dest, msg.msg, msg.wparam, msg.lparam);
}
namespace detail {

void event_manager::add_window_events(const window_event_coll &events) {
    scoped_lock lk(cs);
    for ( window_event_coll::const_iterator b = events.begin(), e = events.end(); b != e; ++b) {
        window_events & we = m_events[ b->first ];

        for ( window_events::creator_coll::const_iterator b_c = b->second.events.begin(), e_c = b->second.events.end(); b_c != e_c; ++b_c)
            we.events[ b_c->first ] = b_c->second;

        for ( window_events::creator_coll::const_iterator b_n = b->second.notifications.begin(), e_n = b->second.notifications.end(); b_n != e_n; ++b_n)
            we.notifications[ b_n->first ] = b_n->second;

        we.handlers.insert( we.handlers.end(), b->second.handlers.begin(), b->second.handlers.end() );
    }
}

void event_manager::add_call_on_event(const event_call_coll & call_on_event) {
    scoped_lock lk(cs);
    for ( event_call_coll::const_iterator b = call_on_event.begin(), e = call_on_event.end(); b != e; ++b)
        m_call_on_event.insert( std::make_pair(b->first, b->second) );
}

void event_manager::add_event_handlers_for_window(window_top * w) {
    scoped_lock lk(cs);
    for ( window_event_coll::const_iterator b = m_events.begin(), e = m_events.end(); b != e; ++b) 
        if ( b->first.matches_wnd(w)) {
            // add all the handlers for this window
            BOOST_FOREACH(add_default_event_handler_ptr add, b->second.handlers)
                add->add_event_handler(w);
        }
}

void event_manager::register_new_event_handler(const std::type_info & event_type, new_event_caller_ptr caller) {
    scoped_lock lk(cs);
    m_new_event_handlers[ event_type ].push_back(caller);
}

namespace {
    bool is_notification(UINT msg) {
        return msg == WM_COMMAND || msg == WM_NOTIFY;
    }

    int wm_command_code( WPARAM wParam) {
        return HIWORD(wParam);
    }
    int wm_notify_code( LPARAM lParam) {
        NMHDR * header = (NMHDR*)lParam;
        int code = header->code;
        return code;
    }

    int notify_code( UINT msg, WPARAM wParam, LPARAM lParam) {
        if ( msg == WM_COMMAND)
            return wm_command_code(wParam);
        else if ( msg == WM_NOTIFY)
            return wm_notify_code(lParam);
        assert(false);
        return 0;
    }

    int wm_command_id( WPARAM wParam) {
        return LOWORD(wParam);
    }
    int wm_notify_id( LPARAM lParam) {
        NMHDR * header = (NMHDR*)lParam;
        int id = header->idFrom;
        return id;
    }
    int notify_id( UINT msg, WPARAM wParam, LPARAM lParam) {
        if ( msg == WM_COMMAND)
            return wm_command_id(wParam);
        else if ( msg == WM_NOTIFY)
            return wm_notify_id(lParam);
        assert(false);
        return 0;
    }

}

void event_manager::call_new_event_handler(window_top * w, ev::base & event) {
    scoped_lock lk(cs);
    new_event_caller_ptr_array & handlers = m_new_event_handlers[ typeid(event) ];
    BOOST_FOREACH(const new_event_caller_ptr & handler, handlers)
        // if it can be casted to what the registered handler needs, it will be called
        handler->call(*w, event);
}

bool event_manager::call_event_handler(ev::base & event) {
    bool handled = true;
    window_top * w = event.destination.m_window;
    if ( is_notification(event.windows_msg))
        // note: we might not know the sender (that is, a window outside our scope)
        if ( event.sender)
            // first, reflect it back to self
            w = event.sender.m_window;

    scoped_lock lk(cs);
    event_call_coll ::iterator found = m_call_on_event.find( typeid(event) );
    if ( found != m_call_on_event.end()) {
        // found handler for this event
        found->second->call(w, event);
    }
    else if ( dynamic_cast<ev::new_event_base*>(&event))
        call_new_event_handler(w, event);
    else if ( dynamic_cast<ev::reflectable*>(&event) )
        w->events.on_notify(*w, event);
    else
        // unknown event - note that on_any_event has already been called
        handled = false;

    // all reflectable events are sent to parent as well
    bool reflectable = (is_notification(event.windows_msg) && event.sender) 
        || dynamic_cast<ev::reflectable*>(&event);
    if ( reflectable) {
        window_top * parent = w->parent->m_window;
        if ( parent)
            if ( event.handled == ev::handled_partially) {
                if ( dynamic_cast<ev::new_event_base*>(&event))
                    call_new_event_handler(parent, event);
                else
                    parent->events.on_notify(*parent, event);
            }
    }
    return true;
}




event_manager::event_ptr event_manager::create_event_from_msg(wnd<> w, UINT msg, WPARAM wParam, LPARAM lParam) {
    if ( msg == g_new_event) {
        // pointer to event is in lparam
        egui::ev::new_event_base * p = (egui::ev::new_event_base*)lParam;
        event_ptr real_event = p->shared_from_this();
        return real_event;
    }

    wnd<> event_generator;
    if ( is_notification(msg) ) {
        // notifications are sent to the parent, we need to find the window that generated the event
        int id = notify_id(msg, wParam, lParam);
        HWND child = ::GetDlgItem( get_hwnd(w), id);
        if ( child)
            event_generator = window_manager::inst().existing_window_from_id(child);

        if ( !event_generator)
            if ( msg == WM_COMMAND) {
                // it's a menu command for this window
                event_generator = w;
                msg = g_wm_menu_command;
            }
    }
    else
        event_generator = w;



    event_ptr result;
    {
    scoped_lock lk(cs);
    for ( window_event_coll::const_iterator b = m_events.begin(), e = m_events.end(); b != e; ++b) 
        if ( b->first.matches_wnd(event_generator)) {
            if ( is_notification(msg)) {
                int code = notify_code(msg, wParam, lParam);
                if ( b->second.notifications.find(code) != b->second.notifications.end()) {
                    result = b->second.notifications.find(code)->second->create();
                    break;
                }
            }
            else {
                if ( b->second.events.find(msg) != b->second.events.end()) {
                    result = b->second.events.find(msg)->second->create();
                    break;
                }
            }
        }
    }

    if ( !result)
    {
        // generic event - no creator for it
        result = event_ptr( new ev::base);
        result->do_default_processing = true;
    }

    result->destination = w;
    result->sender = event_generator;
    result->windows_msg = msg;
    result->wparam = wParam;
    result->lparam = lParam;

    LEGUI_ << GUI_STR("event ") << type_name(*result) << GUI_STR(" ") << msg  << GUI_STR(" ") << get_hwnd(w);
    return result;
}

void event_manager::send_new_event(egui::ev::new_event_base& evt, window_top * dest) {
    evt.destination = dest;
    // note: in case this is forwarded, the sender is already set
    if ( !evt.sender)
        evt.sender = dest;

    evt.windows_msg = g_new_event;
    evt.wparam = 0;
    evt.lparam = (types::int64)(&evt);
    send_win32_event( evt.destination, g_new_event, 0, evt.lparam);
}



}}

// End of file
