// spin_button.cpp

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
#include "egui/controls/spin_button.hpp"
#include "egui/core/detail/window_manager.hpp"
#include "egui/core/win32/raw.hpp"

namespace egui { namespace ctrl {

namespace {
    wnd<> find_by_hwnd( HWND h) {
        return detail::window_manager::inst().create_window_from_id( h);
    }
}

struct spin_button::impl {
    spin_button * self;

    impl(spin_button * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    typedef spin_button::accel_array accel_array;
    typedef wnd<> wnd_type;

    accel_array get_accels() const { 
        accel_array a;
        a.resize(1);
        int count = (int)send_win32_event( self, UDM_GETACCEL, 0, &*a.begin() );
        a.resize(count);
        send_win32_event( self, UDM_GETACCEL, count, &*a.begin() );
        return a;
    }
    void set_accels(const accel_array & a) {
        send_win32_event( self,  UDM_SETACCEL, a.size(), &*a.begin() );
    }
    int get_radix_base() const { 
        return (int)send_win32_event( self, UDM_GETBASE);
    }
    void set_radix_base(const int & val) {
        send_win32_event( self, UDM_SETBASE, val);
    }

    wnd_type  get_buddy() const { 
        return find_by_hwnd( (HWND)send_win32_event( self, UDM_GETBUDDY) );
    }
    void set_buddy(const wnd_type  & val) {
        send_win32_event( self, UDM_SETBUDDY, (WPARAM)egui::raw_hwnd(val) );
    }
    int get_pos() const { 
        if ( detail::has_comctl_ver(5,80) )
            return (int)send_win32_event( self, UDM_GETPOS32);
        else
            return (int)send_win32_event( self, UDM_GETPOS);
    }
    void set_pos(const int & val) {
        if ( detail::has_comctl_ver(5,80) )
            send_win32_event( self, UDM_SETPOS32, 0, val);
        else
            send_win32_event( self, UDM_SETPOS, 0, val);
    }

    int get_min_val() const { 
        INT low,high;
        send_win32_event( self, UDM_GETRANGE32, (WPARAM)&low, &high);
        return low;
    }
    void set_min_val(const int & val) {
        range( val, get_max_val() );
    }
    int get_max_val() const { 
        INT low,high;
        send_win32_event( self, UDM_GETRANGE32, (WPARAM)&low, &high);
        return high;
    }
    void set_max_val(const int & val) {
        range( get_min_val(), val);
    }

    void range(int min_val, int max_val) {
        send_win32_event( self,  UDM_SETRANGE32, min_val, max_val);
    }

};

#define self this
string spin_button:: class_name() { return GUI_STR("msctls_updown32"); }
types::int64  spin_button::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = 0;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

spin_button::spin_button() : m_impl(new spin_button::impl(this) ) , m_copy_events(this)  {
    detail::init_property( radix_base, m_impl.get(), &impl::get_radix_base, &impl::set_radix_base);
    detail::init_property( buddy, m_impl.get(), &impl::get_buddy, &impl::set_buddy);
    detail::init_property( pos, m_impl.get(), &impl::get_pos, &impl::set_pos);
    detail::init_property( min_val, m_impl.get(), &impl::get_min_val, &impl::set_min_val);
    detail::init_property( max_val, m_impl.get(), &impl::get_max_val, &impl::set_max_val);
    detail::init_property( accels, m_impl.get(), &impl::get_accels, &impl::set_accels);
}
spin_button::~spin_button() {
}






}}

// End of file
