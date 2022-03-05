// date_time.cpp

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
#include "egui/controls/date_time.hpp"
#include "egui/core/detail/building_egui.hpp"
#include "egui/core/win32/raw.hpp"
#include "egui/core/detail/window_manager.hpp"

namespace egui { namespace ctrl {

namespace {
    const SYSTEMTIME invalid_time = { 0 };
}


struct date_time::impl {
    date_time * self;

    impl(date_time * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }


    std::pair<SYSTEMTIME,SYSTEMTIME> minmax_range() const {
        SYSTEMTIME minmax[2];
        DWORD res = (DWORD)send_win32_event( self,  wnd_msg(DTM_GETRANGE).l_param(&minmax) );
        if ( res & GDTR_MAX ) ;
        else minmax[1] = invalid_time;

        if ( res & GDTR_MIN) ;
        else minmax[0] = invalid_time;

        return std::make_pair( minmax[0], minmax[1]);
    }




    typedef wnd<month_cal> wnd_type;
    typedef types::temporary_font font_type;


    time_t get_sel() const { 
        SYSTEMTIME result;
        if ( send_win32_event( self, DTM_GETSYSTEMTIME, 0, (LPARAM)&result) != GDT_VALID )
            return 0;
        else
            return win32::from(result);
    }
    void set_sel(const time_t & t) {
        if ( memcmp( &t, &invalid_time, sizeof(SYSTEMTIME)) == 0)
            // invalid
            send_win32_event( self, DTM_SETSYSTEMTIME, GDT_NONE, (LPARAM)&invalid_time);
        else {
            SYSTEMTIME src = win32::to(t);
            send_win32_event( self, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&src);
        }
    }

    time_t get_min_time() const { 
        return win32::from( minmax_range().first );
    }
    void set_min_time(const time_t & t) {
        SYSTEMTIME minmax[2];
        minmax[0] = win32::to(t);
        send_win32_event( self, DTM_SETRANGE, GDTR_MIN, (LPARAM)&minmax);
    }
    time_t get_max_time() const { 
        return win32::from( minmax_range().second );
    }
    void set_max_time(const time_t & t) {
        SYSTEMTIME minmax[2];
        minmax[1] = win32::to(t);
        send_win32_event( self, DTM_SETRANGE, GDTR_MAX, (LPARAM)&minmax);
    }

    wnd_type get_month_cal_ctrl() const { 
        wnd<> w = detail::window_manager::inst().create_window_from_id( (HWND)send_win32_event( self, DTM_GETMONTHCAL) );
        return try_wnd_cast<month_cal>(w);
    }

    font_type get_font() const { 
        // win32raw
        // return (HFONT)send_win32_event( self, DTM_GETMCFONT);
        return default_(); 
    }
    void set_font(const font_type & val) {
        // win32raw
        HFONT h = 0;
        send_win32_event( self, DTM_SETMCFONT, (WPARAM)h, true);
    }




    typedef types::color color_type;
    typedef types::month_cal_color::type cal_type;


    color_type get_color(cal_type val) const {
        return win32::from( (COLORREF)send_win32_event( self, DTM_GETMCCOLOR, val) );
    }
    void set_color( cal_type idx, const color_type & val) {
        send_win32_event( self, DTM_SETMCCOLOR, idx, win32::to(val));
    }

    void set_format(const string & fmt) {
        send_win32_event( self,  wnd_msg(DTM_SETFORMAT).l_param( fmt.empty() ? 0 : fmt.c_str() ));
    }


};

#define self this
string date_time:: class_name() { return GUI_STR("sysdatetimepick32"); }
types::int64  date_time::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = 0;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

date_time::date_time() : m_impl(new date_time::impl(this) ) , m_copy_events(this)  {
    detail::init_property( format, m_impl.get(), &impl::set_format);
    detail::init_property( sel, m_impl.get(), &impl::get_sel, &impl::set_sel);
    detail::init_property( min_time, m_impl.get(), &impl::get_min_time, &impl::set_min_time);
    detail::init_property( max_time, m_impl.get(), &impl::get_max_time, &impl::set_max_time);
    detail::init_property( month_cal_ctrl, m_impl.get(), &impl::get_month_cal_ctrl);
    detail::init_property( font, m_impl.get(), &impl::get_font, &impl::set_font);

    detail::init_property( color, m_impl.get(), &impl::get_color, &impl::set_color);
}
date_time::~date_time() {
}





}}

// End of file
