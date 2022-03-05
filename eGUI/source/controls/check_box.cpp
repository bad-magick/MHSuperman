// check_box.cpp

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
#include "egui/controls/check_box.hpp"

namespace egui { namespace ctrl {

struct check_box::impl {
    check_box * self;

    impl(check_box * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    typedef types::check_box_state::type state_type;

    state_type get_check_state() const { 
        return (state_type)send_win32_event( self, BM_GETCHECK); 
    }
    void set_check_state(const state_type & val) {
        send_win32_event( self, BM_SETCHECK, val);
    }
    bool get_checked() const { 
        return get_check_state() != check_box_state::unchecked;
    }
    void set_checked(const bool & val) {
        set_check_state( val ? check_box_state::checked : check_box_state::unchecked);
    }

};

#define self this
types::int64  check_box::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = BS_CHECKBOX;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

check_box::check_box() : m_impl(new check_box::impl(this) ) {
    detail::init_property( checked, m_impl.get(), &impl::get_checked, &impl::set_checked);
    detail::init_property( check_state, m_impl.get(), &impl::get_check_state, &impl::set_check_state);
}
check_box::~check_box() {
}


}}

// End of file
