// scroll_bar.cpp

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
#include "egui/controls/scroll_bar.hpp"

namespace egui { namespace ctrl {


struct scroll_bar::impl {
    scroll_bar * self;

    impl(scroll_bar * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    typedef types::scroll_info info_type;

    info_type get_scroll_info() const { 
        wnd<> w = self;
        return w->scroll_info(types::scroll_bar_type::ctrl);
    }
    void set_scroll_info(const info_type & val) {
        wnd<> w = self;
        w->scroll_info(types::scroll_bar_type::ctrl) = val;
    }
    void set_enable(const bool & val) {
        EnableScrollBar(raw_hwnd(), SB_CTL, val);
    }
    void set_show(const bool & val) {
        ShowScrollBar(raw_hwnd(), SB_CTL, val);
    }

};

#define self this
string scroll_bar:: class_name() { return GUI_STR("scrollbar"); }
types::int64  scroll_bar::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = 0;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

scroll_bar::scroll_bar() : m_impl(new scroll_bar::impl(this) ) {
    detail::init_property( enable, m_impl.get(), &impl::set_enable);
    detail::init_property( show, m_impl.get(), &impl::set_show);
    detail::init_property( scroll_info, m_impl.get(), &impl::get_scroll_info, &impl::set_scroll_info);
}
scroll_bar::~scroll_bar() {
}





}}

// End of file
