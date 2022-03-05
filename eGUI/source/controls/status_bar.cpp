// status_bar.cpp

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
#include "egui/controls/status_bar.hpp"

namespace egui { namespace ctrl {


struct status_bar::impl {
    status_bar * self;

    impl(status_bar * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    typedef std::vector<int> width_array;

    int get_horiz_border() const { 
        return default_(); 
    }
    int get_vert_border() const { 
        return default_(); 
    }
    int get_spacing_border() const { 
        return default_(); 
    }

    bool get_simple() const { 
        return default_(); 
    }
    void set_simple(const bool & val) {
    }

    void set_bg_color(const color & val) {
    }
    void set_min_height(const int & val) {
    }

    width_array  get_pane_widths() const { 
        return default_(); 
    }
    void set_pane_widths(const width_array  & val) {
    }




    typedef types::icon icon;

    temporary_icon get_pane_icon(int val) const {
        return default_();
    }
    void set_pane_icon( int idx, const temporary_icon & val) {
    }

    string get_pane_text(int val) const {
        return default_();
    }
    void set_pane_text( int idx, const string & val) {
    }

    string get_pane_tip_text(int val) const {
        return default_();
    }
    void set_pane_tip_text( int idx, const string & val) {
    }


    rectangle get_pane_rect(int val) const {
        return default_();
    }



};

#define self this
string status_bar:: class_name() { return GUI_STR("msctls_statusbar32"); }
types::int64  status_bar::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = SBARS_SIZEGRIP | SBT_TOOLTIPS | SBARS_TOOLTIPS;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

status_bar::status_bar() : m_impl(new status_bar::impl(this) ) , m_copy_events(this)  {
    detail::init_property( horiz_border, m_impl.get(), &impl::get_horiz_border);
    detail::init_property( vert_border, m_impl.get(), &impl::get_vert_border);
    detail::init_property( spacing_border, m_impl.get(), &impl::get_spacing_border);
    detail::init_property( simple, m_impl.get(), &impl::get_simple, &impl::set_simple);
    detail::init_property( bg_color, m_impl.get(), &impl::set_bg_color);
    detail::init_property( min_height, m_impl.get(), &impl::set_min_height);
    detail::init_property( pane_widths, m_impl.get(), &impl::get_pane_widths, &impl::set_pane_widths);
    detail::init_property( pane_icon, m_impl.get(), &impl::get_pane_icon, &impl::set_pane_icon);
    detail::init_property( pane_text, m_impl.get(), &impl::get_pane_text, &impl::set_pane_text);
    detail::init_property( pane_tip_text, m_impl.get(), &impl::get_pane_tip_text, &impl::set_pane_tip_text);
    detail::init_property( pane_rect, m_impl.get(), &impl::get_pane_rect);
}
status_bar::~status_bar() {
}





}}

// End of file
