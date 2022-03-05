// month_cal.cpp

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
#include "egui/controls/month_cal.hpp"
#include "egui/core/win32/raw.hpp"

namespace egui { namespace ctrl {

namespace {
    const SYSTEMTIME invalid_time = { 0 };
}


struct month_cal::impl {
    month_cal * self;

    impl(month_cal * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    typedef month_cal::selection sel_type;

    time_t get_sel() const { 
        SYSTEMTIME t = { 0 };
        if ( send_win32_event( self, MCM_GETCURSEL, (LPARAM)&t) != 0 )
            return win32::from(t) ;
        else
            return 0;
    }
    void set_sel(const time_t & t) {
        if ( memcmp( &t, &invalid_time, sizeof(SYSTEMTIME)) == 0)
            // invalid
            send_win32_event( self, MCM_SETCURSEL, 0, (LPARAM)&invalid_time);
        else {
            SYSTEMTIME src = win32::to(t);
            send_win32_event( self, MCM_SETCURSEL, 0, (LPARAM)&src);
        }
    }

    int get_first_day_of_week() const { 
        DWORD res = (DWORD)send_win32_event( self, MCM_GETFIRSTDAYOFWEEK);
        return LOWORD(res);
    }
    void set_first_day_of_week(const int & val) {
        send_win32_event( self, MCM_SETFIRSTDAYOFWEEK, 0, val);
    }
    bool get_uses_locale() const { 
        DWORD res = (DWORD)send_win32_event( self, MCM_GETFIRSTDAYOFWEEK);
        return HIWORD(res) == 0;
    }

    int get_max_sel_count() const { 
        return (int)send_win32_event( self, MCM_GETMAXSELCOUNT);
    }
    void set_max_sel_count(const int & val) {
        send_win32_event( self, MCM_SETMAXSELCOUNT, val);
    }

    int get_month_delta() const { 
        return (int)send_win32_event( self, MCM_GETMONTHDELTA);
    }
    void set_month_delta(const int & val) {
        send_win32_event( self,  MCM_SETMONTHDELTA, val);
    }

    std::pair<SYSTEMTIME,SYSTEMTIME> minmax_range() const {
        SYSTEMTIME minmax[2], invalid = { 0 };
        DWORD res = (DWORD)send_win32_event( self,  wnd_msg(MCM_GETRANGE).l_param(&minmax) );
        if ( res & GDTR_MAX ) ;
        else minmax[1] = invalid;

        if ( res & GDTR_MIN) ;
        else minmax[0] = invalid;

        return std::make_pair( minmax[0], minmax[1]);
    }


    time_t get_min_time() const { 
        return win32::from(minmax_range().first);
    }
    void set_min_time(const time_t & t) {
        SYSTEMTIME minmax[2];
        minmax[0] = win32::to(t);
        send_win32_event( self, MCM_SETRANGE, GDTR_MIN, (LPARAM)&minmax);
    }
    time_t get_max_time() const { 
        return win32::from(minmax_range().second);
    }
    void set_max_time(const time_t & t) {
        SYSTEMTIME minmax[2];
        minmax[1] = win32::to(t);
        send_win32_event( self, MCM_SETRANGE, GDTR_MAX, (LPARAM)&minmax);
    }

    sel_type get_sel_range  () const { 
        SYSTEMTIME rng[2];
        send_win32_event( self, MCM_GETSELRANGE, 0, (LPARAM)&rng);
        return sel_type( win32::from(rng[0]), win32::from(rng[1]));
    }
    void set_sel_range(const sel_type & val) {
        SYSTEMTIME rng[2];
        rng[0] = win32::to(val.start);
        rng[1] = win32::to(val.end);
        send_win32_event( self, MCM_SETSELRANGE, 0, (LPARAM)&rng);
    }
    time_t get_today() const { 
        SYSTEMTIME t;
        send_win32_event( self, MCM_GETTODAY, 0, (LPARAM)&t);
        return win32::from(t);
    }
    void set_today(const time_t & val) {
        if ( val > 0)
            send_win32_event( self, MCM_SETTODAY, 0, (LPARAM)&val);
        else
            send_win32_event( self, MCM_SETTODAY, 0);
    }

    
    
    
    typedef types::color color_type;
    typedef types::month_cal_color::type cal_type;

    color_type get_color(cal_type val) const {
        return win32::from( (COLORREF)send_win32_event( self, MCM_GETCOLOR, val) );
    }
    void set_color( cal_type idx, const color_type & val) {
        send_win32_event( self, MCM_SETCOLOR, idx, win32::to(val));
    }


};

#define self this
string month_cal:: class_name() { return GUI_STR("sysmonthcal32"); }
types::int64  month_cal::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = 0;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

month_cal::month_cal() : m_impl(new month_cal::impl(this) ) , m_copy_events(this)  {
    detail::init_property( first_day_of_week, m_impl.get(), &impl::get_first_day_of_week, &impl::set_first_day_of_week);
    detail::init_property( uses_locale, m_impl.get(), &impl::get_uses_locale);
    detail::init_property( max_sel_count, m_impl.get(), &impl::get_max_sel_count, &impl::set_max_sel_count);
    detail::init_property( month_delta, m_impl.get(), &impl::get_month_delta, &impl::set_month_delta);
    detail::init_property( min_time, m_impl.get(), &impl::get_min_time, &impl::set_min_time);
    detail::init_property( max_time, m_impl.get(), &impl::get_max_time, &impl::set_max_time);
    detail::init_property( sel_range, m_impl.get(), &impl::get_sel_range, &impl::set_sel_range);
    detail::init_property( today, m_impl.get(), &impl::get_today, &impl::set_today);
    detail::init_property( sel, m_impl.get(), &impl::get_sel, &impl::set_sel);
    detail::init_property( color, m_impl.get(), &impl::get_color, &impl::set_color);
}
month_cal::~month_cal() {
}





}}

// End of file
