// window_base.cpp

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
#include "egui/core/detail/building_egui.hpp"
#include "egui/core/detail/window_manager.hpp"
#include "egui/core/detail/building_egui/event_manager.hpp"
#include "egui/core/win32/raw.hpp"
#include "egui/core/detail/util.hpp"
#include <boost/foreach.hpp>

namespace egui {



    namespace types {
        typedef scroll_bar_type scroll_bar;
    }

    /////////////////////////////////////////////////////////////////////
    // wnd_init

    wnd_init::wnd_init() : m_parent(0), m_style(0), m_style_set(false), m_text_set(false), m_rect_set(false), m_parent_set(false) {}
    wnd_init::wnd_init(types::int64 style) : m_parent(0), m_style(style), m_style_set(true), m_text_set(false), m_rect_set(false), m_parent_set(false) {}
    wnd_init::wnd_init(const rectangle & r) : m_parent(0), m_style(0), m_rect(r), m_style_set(false), m_text_set(false), m_rect_set(true), m_parent_set(false) {}
    wnd_init::wnd_init(const string & text) : m_parent(0), m_style(0), m_text(text), m_style_set(false), m_text_set(true), m_rect_set(false), m_parent_set(false) {}
    wnd_init::wnd_init(const char_ * text) : m_parent(0), m_style(0), m_text(text), m_style_set(false), m_text_set(true), m_rect_set(false), m_parent_set(false) {}
    wnd_init::wnd_init(const wnd<> & parent) : m_parent(0), m_style(0), m_style_set(false), m_text_set(false), m_rect_set(false), m_parent_set(true) {
        m_parent = get_hwnd(parent);
    }
    wnd_init::wnd_init(const window_top *parent) : m_parent(0), m_style(0), m_style_set(false), m_text_set(false), m_rect_set(false), m_parent_set(true) {
        m_parent = get_hwnd(parent);
    }

    wnd_init& wnd_init::style(types::int64 s) {
        m_style = s;
        m_style_set = true;
        return *this;
    }

    wnd_init& wnd_init::text(const string& t) {
        m_text = t;
        m_text_set = true;
        return *this;
    }

    wnd_init& wnd_init::rect(const rectangle & r) {
        m_rect = r;
        m_rect_set = true;
        return *this;
    }
    wnd_init& wnd_init::rect(int x, int y, int w, int h) {
        m_rect = rectangle(x,y,w,h);
        m_rect_set = true;
        return *this;
    }
    wnd_init& wnd_init::rect(point p, size s) {
        m_rect = rectangle(p,s);
        m_rect_set = true;
        return *this;
    }

    wnd_init& wnd_init::parent(const wnd<> & parent) {
        m_parent = get_hwnd(parent);
        m_parent_set = true;
        return *this;
    }

    void wnd_init::default_style(types::int64 def) const {
        m_style |= def;
    }


    /////////////////////////////////////////////////////////////////////


    /** 
        Adds a specific module handle to the list of existing modules.
        Module handles are needed in order for the library to find form resources (by their unique IDs)

        You need to use this only if you're within a DLL, otherwise, for executables, the executable's module handle is automatically added
    */
    void add_module(void* module_name) {
        detail::window_manager::inst().add_win32_module( static_cast<HINSTANCE>(module_name) );
    }
    /** 
        Adds a specific module to the list of existing modules, given its DLL name (the path to this DLL.
        Module handles are needed in order for the library to find form resources (by their unique IDs)

        You need to use this only if you're within a DLL, otherwise, for executables, the executable's module handle is automatically added
    */
    void add_module(const char_ * module_name) {
        string m = module_name;
        add_module(m);
    }
    /** 
        Adds a specific module to the list of existing modules, given its DLL name (the path to this DLL.
        Module handles are needed in order for the library to find form resources (by their unique IDs)

        You need to use this only if you're within a DLL, otherwise, for executables, the executable's module handle is automatically added
    */
    void add_module(string module_name) {
        detail::str_replace( module_name, GUI_STR("/"), GUI_STR("\\"));
        void * module = ::GetModuleHandle( module_name.c_str() );
        add_module(module);
    }






const void* raw_hwnd(const wnd<> & w) {
    if ( w)
        return w->id->unique;
    else
        return 0;
}
const void* raw_hwnd(const window_top *w) {
    if ( w)
    return w->id->unique;
    else
        return 0;
}

HWND get_hwnd(const wnd<> & w) {
    if ( w)
        return static_cast<HWND> ( const_cast<void*>( w->id->unique) );
    else
        return 0;
}
HWND get_hwnd(const window_top *w) {
    if ( w)
        return static_cast<HWND> ( const_cast<void*>( w->id->unique) );
    else
        return 0;
}

types::int64 window_top::default_style() { 
    return types::style::child | types::style::visible | types::style::tab_stop; 
}

bool window_top::is_valid() const {
    scoped_lock lk(cs);
    return m_still_alive;
}

namespace {
    int win32_scroll_bar(types::scroll_bar::type scroll) {
        if ( scroll == scroll_bar::horiz) return SB_HORZ;
        if ( scroll == scroll_bar::vert) return SB_VERT;
        if ( scroll == scroll_bar::ctrl) return SB_CTL;
        assert(false);
        return 0;
    }
}

struct window_top::impl {
    window_top * self;
    HWND hwnd;

    impl(window_top * self) : self(self) {
        hwnd = static_cast<HWND>( const_cast<void*>( self->m_hwnd ));
    }

    HWND raw_hwnd() const {
        return static_cast<HWND>( const_cast<void*>( self->m_hwnd ));
    }


    string get_text() const { 
        int max_len = ::GetWindowTextLength( hwnd) + 1;
        string result;
        result.resize( max_len);
        int len = ::GetWindowText( hwnd, &*result.begin(),  max_len);
        result.resize( len);
        return result;
    }
    void set_text(const string& str) {
        ::SetWindowText( raw_hwnd(), str.c_str());
    }

    types::id get_id() const { return types::id(self->m_hwnd); }

    wnd<> get_parent() const { 
        return detail::window_manager::inst().create_window_from_id( ::GetParent( raw_hwnd() ) ) ; 
    }
    wnd<> get_next() const { 
        HWND h = ::GetWindow(raw_hwnd(), GW_HWNDNEXT);
        return detail::window_manager::inst().create_window_from_id( h ) ; 
    }
    wnd<> get_prev() const { 
        HWND h = ::GetWindow(raw_hwnd(), GW_HWNDPREV);
        return detail::window_manager::inst().create_window_from_id( h ) ; 
    }

    void set_shown(types::shown::type show) {
        switch ( show) {
            case types::shown::maximize: ::ShowWindow(raw_hwnd(), SW_MAXIMIZE); break;
            case types::shown::minimize: ::ShowWindow(raw_hwnd(), SW_MINIMIZE); break;
            case types::shown::normally: ::ShowWindow(raw_hwnd(), SW_SHOWNORMAL); break;
        }
    }

    bool get_visible() const { 
        return ::IsWindowVisible(raw_hwnd()) != 0;
    }
    void set_visible(bool b) {
        ::ShowWindow( raw_hwnd(), b ? SW_SHOW : SW_HIDE);
    }

    void set_redraw(bool b) {
        send_win32_event( self, WM_SETREDRAW, b);
    }

    int64 get_style() const { 
        DWORD s = (DWORD)::GetWindowLong(hwnd, GWL_STYLE);
        DWORD e = (DWORD)::GetWindowLong(hwnd, GWL_EXSTYLE);

        return (((int64)e) << 32) + s;
    }
    void set_style(int64 style) {
        DWORD s = (DWORD)(style & 0xFFFFFFFF);
        DWORD e = (DWORD)(style >> 32);
        
        ::SetWindowLong(hwnd, s, GWL_STYLE);
        ::SetWindowLong(hwnd, e, GWL_EXSTYLE);
        ::SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    }

    rectangle get_full_rect() const { 
        HWND parent = ::GetParent( raw_hwnd());
        RECT result;
        ::GetWindowRect( raw_hwnd(), &result);
        ::MapWindowPoints(0, parent, reinterpret_cast<LPPOINT>(&result), 2);
        return win32::from(result) ; 
    }
    void set_full_rect(const rectangle &r) {
        ::MoveWindow( raw_hwnd(), r.start.x, r.start.y, r.size.width, r.size.height, TRUE);
    }
    rectangle get_client_rect() const { 
        RECT result;
        ::GetClientRect( raw_hwnd(), &result);
        return win32::from(result) ; 
    }
    void set_client_rect(const rectangle &r) {
        rectangle old_rect = self->client_rect;
        int diff_x = r.size.width - old_rect.size.width;
        int diff_y = r.size.height - old_rect.size.height;
        rectangle full_rect = self->full_rect;
        full_rect.size.width += diff_x;
        full_rect.size.height += diff_y;
        self->full_rect = full_rect;
    }

    types::scroll_info get_scroll_info(types::scroll_bar::type scroll) const { 
        SCROLLINFO info = { sizeof(SCROLLINFO), 0 };
        info.fMask = SIF_ALL;
        ::GetScrollInfo( raw_hwnd(), win32_scroll_bar(scroll), &info);

        types::scroll_info result;
        EGUI_FROM_WIN32(result, info, min_pos, nMin);
        EGUI_FROM_WIN32(result, info, max_pos, nMax);
        EGUI_FROM_WIN32(result, info, page_size, nPage);
        EGUI_FROM_WIN32(result, info, pos, nPos);
        EGUI_FROM_WIN32(result, info, track_pos, nTrackPos );
        return result;
    }
    void set_scroll_info(types::scroll_bar::type scroll, const types::scroll_info & egui) {
        SCROLLINFO info = { sizeof(SCROLLINFO), 0 };
        info.fMask = SIF_ALL;

        EGUI_TO_WIN32(egui, info, min_pos, nMin);
        EGUI_TO_WIN32(egui, info, max_pos, nMax);
        EGUI_TO_WIN32(egui, info, page_size, nPage);
        EGUI_TO_WIN32(egui, info, pos, nPos);
        EGUI_TO_WIN32(egui, info, track_pos, nTrackPos );
        ::SetScrollInfo( raw_hwnd(), win32_scroll_bar(scroll), &info, TRUE);
    }

    void set_show_scroll(types::scroll_bar::type scroll, bool show) {
        ::ShowScrollBar(raw_hwnd(), win32_scroll_bar(scroll), show);
    }

    void set_enable_scroll(types::scroll_bar::type scroll, bool show) {
        ::EnableScrollBar( raw_hwnd(), win32_scroll_bar(scroll), (show ? ESB_ENABLE_BOTH : ESB_DISABLE_BOTH));
    }

    wnd<> get_top_child_wnd() const { 
        HWND h = ::GetTopWindow(raw_hwnd());
        return detail::window_manager::inst().create_window_from_id( h ) ; 
    }

    int64 get_thread_id() const {  
	    DWORD dwProcessID;
	    return ::GetWindowThreadProcessId(raw_hwnd(), &dwProcessID);
    }
    int64 get_process_id() const { 
	    DWORD dwProcessID;
	    ::GetWindowThreadProcessId(raw_hwnd(), &dwProcessID);
	    return dwProcessID;
    }

    bool get_enabled() const {  
        return ::IsWindowEnabled( raw_hwnd() ) != 0;
    }
    void set_enabled(bool b) {
        ::EnableWindow( raw_hwnd(), b);
    }

    void set_capture(types::capture::type capture, bool val) {
        HWND h = raw_hwnd();
        if ( capture & types::capture::mouse) 
            if ( val)
                ::SetCapture(h);
            else
                ::ReleaseCapture();

        if ( capture & types::capture::keyboard) 
            if ( val)
                ::SetFocus(h);
            else
                ::SetFocus(0);
    }


};

property::r< wnd<> > window_top::active_wnd;
property::r< wnd<> > window_top::keyboard_focus_wnd;

namespace {
    wnd<> get_active_wnd() { 
        HWND h = ::GetActiveWindow();
        return detail::window_manager::inst().create_window_from_id( h ) ; 
    }
    wnd<> get_keyboard_focus_wnd() { 
        HWND h = ::GetFocus();
        return detail::window_manager::inst().create_window_from_id( h ) ; 
    }

    struct static_initer {
        static_initer() {
            detail::init_property( window_top::active_wnd, &get_active_wnd );
            detail::init_property( window_top::keyboard_focus_wnd, &get_keyboard_focus_wnd );
        }

    } s_;
}

string window_top::class_name() { return GUI_STR("static"); }

window_top::window_top(wnd_id_type hwnd, const wnd_init & init ) : m_still_alive(true), m_hwnd(hwnd), m_init(init), m_is_waiting(false) {
    // make sure we have active_wnd and keyboard_focus_wnd
    &s_;

    if ( !hwnd)
        throw exception( GUI_STR("invalid window creation - it should be created with new_"));

    m_impl = boost::shared_ptr<impl>( new impl(this) );

    detail::init_property( visible, m_impl.get(), &impl::get_visible, &impl::set_visible );

    detail::init_property( text, m_impl.get(), &impl::get_text , &impl::set_text);
    detail::init_property( id, m_impl.get(), &impl::get_id );
    detail::init_property( parent, m_impl.get(), &impl::get_parent );
    detail::init_property( next, m_impl.get(), &impl::get_next );
    detail::init_property( prev, m_impl.get(), &impl::get_prev );

    detail::init_property( shown, m_impl.get(), &impl::set_shown);
    detail::init_property( visible, m_impl.get(), &impl::get_visible , &impl::set_visible);
    detail::init_property( redraw, m_impl.get(), &impl::set_redraw);
    detail::init_property( style, m_impl.get(), &impl::get_style , &impl::set_style);
    detail::init_property( full_rect, m_impl.get(), &impl::get_full_rect , &impl::set_full_rect);
    detail::init_property( client_rect, m_impl.get(), &impl::get_client_rect , &impl::set_client_rect);

    detail::init_property( scroll_info, m_impl.get(), &impl::get_scroll_info , &impl::set_scroll_info);
    detail::init_property( show_scroll, m_impl.get(), &impl::set_show_scroll);
    detail::init_property( enable_scroll, m_impl.get(), &impl::set_enable_scroll);
    detail::init_property( top_child_wnd, m_impl.get(), &impl::get_top_child_wnd );
    detail::init_property( thread_id, m_impl.get(), &impl::get_thread_id );
    detail::init_property( process_id, m_impl.get(), &impl::get_process_id );
    detail::init_property( enabled, m_impl.get(), &impl::get_enabled , &impl::set_enabled);
    detail::init_property( capture, m_impl.get(), &impl::set_capture);

//    detail::init_property( xx, m_impl.get(), &impl::get_xx , &impl::set_xx);

    using namespace boost;
    events.on_notify += bind(mem_fn(&window_top::on_notify), this, _1);
}
window_top::~window_top() {
}



/** 
Sets a timer for this window. At the @c elapse_ms millisecs, this window
will receive an on_timer(), with the id set to @c event_id.
*/
void window_top::set_timer(int event_id, unsigned elapse) {
    ::SetTimer( get_hwnd(this), event_id, elapse, 0) ;
}
/** 
Kills the timer having this ID.
*/
void window_top::kill_timer(int event_id) {
    ::KillTimer( get_hwnd(this), event_id);
}

/// scrolls the window to that point
void window_top::do_scroll(size scroll_size) {
    ::ScrollWindowEx(get_hwnd(this), scroll_size.width, scroll_size.height, 0, 0, 0, 0, SW_INVALIDATE);

}

/** 
Brings this window to top of the Z order.
*/
void window_top::bring_to_top() {
    ::BringWindowToTop(get_hwnd(this));
}


/** 
Returns the child at the given point, or @c null_wnd  if there's no child at that point. <br>
The point is in client coordinates relative to your window.
*/
wnd<> window_top::child_from_point(point pnt) const {
    HWND h = ::ChildWindowFromPointEx(get_hwnd(this), win32::to(pnt), CWP_ALL);
    return detail::window_manager::inst().create_window_from_id( h ) ; 
}
/**
Flashes the window - one time. <br>
If invert is true, it will show the window "flashed".
If invert is false, it will show the window normally.

To implement flashing (multiple times), you should implement a timer,
and repeatidly call flash.
*/
void window_top::flash(bool invert) {
    ::FlashWindow(get_hwnd(this), invert);
}

/** 
    forces a repaint of the current window
*/
void window_top::do_redraw() {
    ::UpdateWindow(get_hwnd(this));
    ::RedrawWindow(get_hwnd(this), 0, 0, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}
/**
Brings the thread that created the specified window into the foreground and activates the window.
*/
void window_top::set_foreground() {
    ::SetForegroundWindow(get_hwnd(this));
}

void window_top::on_initialize() {

}

void window_top::do_on_any_event(egui::ev::base & event_arg ) {
    on_any_event_before(event_arg);
    { scoped_lock lk(cs);
      BOOST_FOREACH(on_any_event_func func, m_on_any_event)
          func(event_arg);
    }
    on_any_event_after(event_arg);
}
/** 
    Overridable function - any window can easily catch all events through this

    This is called @b before any event handlers this specific event might have

    @sa on_any_event_after
*/
void window_top::on_any_event_before(egui::ev::base & /* event_arg */) {
}

/** 
    Overridable function - any window can easily catch all events through this

    This is called @b after any event handlers this specific event might have

    @sa on_any_event_before
*/
void window_top::on_any_event_after(egui::ev::base & /* event_arg */) {
}


void window_top::register_on_any_event_handler(on_any_event_func func) {
    scoped_lock lk(cs);
    m_on_any_event.push_back(func);
}

namespace {
}

void window_top::wait_for( const egui::ev::base & to_wait_for) {
    detail::event_manager::inst().add_wait_for(this, to_wait_for);

    MSG msg;
    while( true ) {
        { scoped_lock lk(cs);
          if ( ! m_is_waiting)
              // we've reached the event we were waiting for
              break;
        }
        if ( ::PeekMessage( &msg, 0, 0, 0, PM_NOREMOVE) ) {
	        int res = ::GetMessage( &msg, 0, 0, 0);
            if ( res != -1) {
                ::TranslateMessage( &msg);
	            ::DispatchMessage( &msg);
            }
            else {
                // failure processing msg, lets get out
                break;
            }
        }
        else
            // no message yet
            SleepEx(1, TRUE); 
    }
}

/** 
    This is received when the user wants to close a window or a dialog, by pressing the "x" button on top-right, or pressing Escape (for dialogs)
*/
bool window_top::can_close() const {
    return true;
}

void window_top::send_new_event(egui::ev::new_event_base& evt) {
    detail::event_manager::inst().send_new_event(evt, this);
}

void window_top::register_event_handler_ptr(const std::type_info & event_type, new_event_caller_ptr caller) {
    detail::event_manager::inst().register_new_event_handler(event_type, caller);
}

void window_top::add_non_intrusive_handler_ptr(non_intrusive_handler_ptr p) {
    detail::window_manager::inst().add_non_intrusive_handler_ptr(p);
}


}
// End of file


