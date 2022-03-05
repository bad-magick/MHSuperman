// slider.cpp

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

#include "stdafx_controls.h"
#include "egui/core/wnd.hpp"
#include "egui/controls/slider.hpp"
#include "egui/core/detail/window_manager.hpp"

namespace egui { namespace ctrl {


struct slider::impl {
    slider * self;

    impl(slider * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    typedef wnd<> wnd_type ;

    int get_line_size() const { 
        return (int)send_win32_event( self, TBM_GETLINESIZE);
    }
    void set_line_size(const int & val) {
        send_win32_event( self, TBM_SETLINESIZE, 0, val);
    }
    int get_page_size() const { 
        return (int)send_win32_event( self, TBM_GETPAGESIZE);
    }
    void set_page_size(const int & val) {
        send_win32_event( self, TBM_SETPAGESIZE, 0, val);
    }
    int get_min_val() const { 
        return (int)send_win32_event( self, TBM_GETRANGEMIN);
    }
    void set_min_val(const int & val) {
        send_win32_event( self, TBM_SETRANGEMIN, true, val);
    }
    int get_max_val() const { 
        return (int)send_win32_event( self, TBM_GETRANGEMAX);
    }
    void set_max_val(const int & val) {
        send_win32_event( self, TBM_SETRANGEMAX, true, val);
    }
    int get_sel_start() const { 
        return (int)send_win32_event( self, TBM_GETSELSTART);
    }
    void set_sel_start(const int & sel) {
        send_win32_event( self, TBM_SETSELSTART, true, sel);
    }
    int get_sel_end() const { 
        return (int)send_win32_event( self, TBM_GETSELEND);
    }
    void set_sel_end(const int & sel) {
        send_win32_event( self, TBM_SETSELEND, true, sel);
    }
    int get_pos() const { 
        return (int)send_win32_event( self, TBM_GETPOS);
    }
    void set_pos(const int & val) {
        send_win32_event( self, TBM_SETPOS, true, val);
    }
    void set_tick_freq(const int & val) {
        send_win32_event( self, TBM_SETTICFREQ, val);
    }

    wnd_type  get_left_buddy() const { 
        return detail::window_manager::inst().create_window_from_id( (HWND)send_win32_event( self, TBM_GETBUDDY, TRUE));
    }
    void set_left_buddy(const wnd_type  & val) {
        send_win32_event( self, TBM_SETBUDDY, TRUE, egui::raw_hwnd(val) );
    }
    wnd_type  get_right_buddy() const { 
        return detail::window_manager::inst().create_window_from_id( (HWND)send_win32_event( self, TBM_GETBUDDY, FALSE));
    }
    void set_right_buddy(const wnd_type  & val) {
        send_win32_event( self, TBM_SETBUDDY, FALSE, egui::raw_hwnd(val) );
    }
    wnd_type  get_above_buddy() const { 
        return get_left_buddy(); 
    }
    void set_above_buddy(const wnd_type  & val) {
        set_left_buddy(val);
    }
    wnd_type  get_below_buddy() const { 
        return get_right_buddy(); 
    }
    void set_below_buddy(const wnd_type  & val) {
        set_right_buddy(val);
    }

};

#define self this
string slider:: class_name() { return GUI_STR("msctls_trackbar32"); }
types::int64  slider::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = 0;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

slider::slider() : m_impl(new slider::impl(this) ) {
    detail::init_property( page_size, m_impl.get(), &impl::get_page_size, &impl::set_page_size);
    detail::init_property( min_val, m_impl.get(), &impl::get_min_val, &impl::set_min_val);
    detail::init_property( max_val, m_impl.get(), &impl::get_max_val, &impl::set_max_val);
    detail::init_property( sel_start, m_impl.get(), &impl::get_sel_start, &impl::set_sel_start);
    detail::init_property( sel_end, m_impl.get(), &impl::get_sel_end, &impl::set_sel_end);
    detail::init_property( pos, m_impl.get(), &impl::get_pos, &impl::set_pos);
    detail::init_property( tick_freq, m_impl.get(), &impl::set_tick_freq);
    detail::init_property( left_buddy, m_impl.get(), &impl::get_left_buddy, &impl::set_left_buddy);
    detail::init_property( right_buddy, m_impl.get(), &impl::get_right_buddy, &impl::set_right_buddy);
    detail::init_property( above_buddy, m_impl.get(), &impl::get_above_buddy, &impl::set_above_buddy);
    detail::init_property( below_buddy, m_impl.get(), &impl::get_below_buddy, &impl::set_below_buddy);
    detail::init_property( line_size, m_impl.get(), &impl::get_line_size, &impl::set_line_size);
}
slider::~slider() {
}





void slider::clear_sel() { 
    send_win32_event( self, TBM_CLEARSEL, true);
}
void slider::clear_ticks() { 
    send_win32_event( self, TBM_CLEARTICS, true);
}

}}

// End of file
