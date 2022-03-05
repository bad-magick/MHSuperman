// progress_bar.cpp

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
#include "egui/controls/progress_bar.hpp"
#include "egui/core/win32/raw.hpp"

namespace egui { namespace ctrl {


struct progress_bar::impl {
    progress_bar * self;

    impl(progress_bar * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    typedef types::color color;

    void range(int min_, int max_) {
        send_win32_event( self, PBM_SETRANGE32, min_, max_);
    }



    int get_min_val() const { 
        PBRANGE r;
        send_win32_event( self, PBM_GETRANGE, TRUE, &r);
        return r.iLow;
    }
    void set_min_val(const int & val) {
        range( val, get_max_val());
    }
    int get_max_val() const { 
        PBRANGE r;
        send_win32_event( self, PBM_GETRANGE, FALSE, &r);
        return r.iHigh;
    }
    void set_max_val(const int & val) {
        range( get_min_val(), val);
    }
    int get_pos() const { 
        return (int)send_win32_event( self, PBM_GETPOS);
    }
    void set_pos(const int & val) {
        send_win32_event( self, PBM_SETPOS, val);
    }
    void set_step(const int & val) {
        send_win32_event( self, PBM_SETSTEP, val);
    }
    types:: color get_bar_color() const { 
        self->redraw = false;
        types::color c = win32::from((COLORREF)send_win32_event( self, PBM_SETBARCOLOR, 0));
        self->redraw = true;
        return c;
    }
    void set_bar_color(const types::color & col) {
        send_win32_event( self, PBM_SETBARCOLOR, 0, win32::to(col) );
    }
    types::color get_bg_color() const { 
        self->redraw = false;
        types::color c = win32::from((COLORREF)send_win32_event( self, PBM_SETBKCOLOR, 0));
        self->redraw = true;
        return c;
    }
    void set_bg_color(const types::color & val) {
        send_win32_event( self, PBM_SETBKCOLOR, 0, win32::to(val) );
    }

};

#define self this

string progress_bar:: class_name() { return GUI_STR("msctls_progress32"); }
types::int64  progress_bar::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = 0;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

progress_bar::progress_bar() : m_impl(new progress_bar::impl(this) ) {
    detail::init_property( max_val, m_impl.get(), &impl::get_max_val, &impl::set_max_val);
    detail::init_property( step, m_impl.get(), &impl::set_step);
    detail::init_property( pos, m_impl.get(), &impl::get_pos, &impl::set_pos);
    detail::init_property( bar_color, m_impl.get(), &impl::get_bar_color, &impl::set_bar_color);
    detail::init_property( bg_color, m_impl.get(), &impl::get_bg_color, &impl::set_bg_color);
    detail::init_property( min_val, m_impl.get(), &impl::get_min_val, &impl::set_min_val);
}
progress_bar::~progress_bar() {
}





void progress_bar::step_it() {
    send_win32_event( self, PBM_STEPIT);
}

}}

// End of file
