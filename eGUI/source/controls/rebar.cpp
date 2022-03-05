// rebar.cpp

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
#include "egui/controls/rebar.hpp"

namespace egui { namespace ctrl {


struct rebar::impl {
    rebar * self;

    impl(rebar * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    typedef types::rebar_band rebar_band;
    typedef types::rebar_color_scheme scheme_type;
    typedef wnd<> wnd_type;


    int get_band_count() const { 
        return default_(); 
    }
    int get_bar_height() const { 
        return default_(); 
    }

    color get_bg_color() const { 
        return default_(); 
    }
    void set_bg_color(const color & val) {
    }
    color get_text_color() const { 
        return default_(); 
    }
    void set_text_color(const color & val) {
    }

    int get_row_count() const { 
        return default_(); 
    }

    rebar_band get_band() const { 
        return default_(); 
    }
    void set_band(const rebar_band & val) {
    }

    temporary_image_list get_images() const { 
        return default_(); 
    }
    void set_images(const temporary_image_list & val) {
    }

    void set_parent_wnd(const wnd_type & val) {
    }
    scheme_type get_color_scheme() const { 
        return default_(); 
    }
    void set_color_scheme(const scheme_type & val) {
    }



    bool get_show_band(int val) const {
        return default_();
    }
    void set_show_band( int idx, const bool & val) {
    }

    rectangle get_band_rect(int val) const {
        return default_();
    }


};

#define self this
string rebar:: class_name() { return GUI_STR("rebarwindow32"); }
types::int64  rebar::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = RBS_BANDBORDERS | CCS_TOP |WS_CLIPSIBLINGS|WS_CLIPCHILDREN|RBS_VARHEIGHT|CCS_NODIVIDER;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

rebar::rebar() : m_impl(new rebar::impl(this) ) {
    detail::init_property( bar_height, m_impl.get(), &impl::get_bar_height);
    detail::init_property( bg_color, m_impl.get(), &impl::get_bg_color, &impl::set_bg_color);
    detail::init_property( text_color, m_impl.get(), &impl::get_text_color, &impl::set_text_color);
    detail::init_property( row_count, m_impl.get(), &impl::get_row_count);
    detail::init_property( band, m_impl.get(), &impl::get_band, &impl::set_band);
    detail::init_property( images, m_impl.get(), &impl::get_images, &impl::set_images);
    detail::init_property( parent_wnd, m_impl.get(), &impl::set_parent_wnd);
    detail::init_property( color_scheme, m_impl.get(), &impl::get_color_scheme, &impl::set_color_scheme);
    detail::init_property( band_count, m_impl.get(), &impl::get_band_count);
    detail::init_property( show_band, m_impl.get(), &impl::get_show_band, &impl::set_show_band);
    detail::init_property( band_rect, m_impl.get(), &impl::get_band_rect);
}
rebar::~rebar() {
}









int rebar::row_height(int row_idx) const { 
    return 0;
}

void rebar:: insert_band(const types::rebar_band &band, int idx) { 
}
void rebar:: del_band(int band_idx) { 
}
void rebar:: maximize_band(int band_idx, bool to_ideal_size ) { 
}
void rebar:: minimize_band(int band_idx) { 
}
void rebar:: move_band(int old_idx, int new_idx) { 
}
void rebar:: size_to_rect(const rectangle &r) { 
}
rectangle rebar::band_borders(int band_idx) const { 
    return rectangle();
}

}}

// End of file
