// button.cpp

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
#include "egui/controls/button.hpp"

namespace egui { namespace ctrl {


struct button::impl {
    button * self;

    impl(button * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    typedef types::button_state state_type;



    state_type get_state() const { 
        UINT raw = (UINT)send_win32_event( self, BM_GETSTATE);
        types::button_state r;
        if ( raw & BST_CHECKED)
            r.is_checked = true;
        if ( raw & BST_FOCUS)
            r.has_focus = true;
        if ( raw & BST_INDETERMINATE  )
            r.is_indeterminate = true;
        if ( raw & BST_PUSHED)
            r.is_pushed = true;

        return r;
    }
    void set_state(const state_type & val) {
        UINT raw = 0;
        if ( val.is_indeterminate)
            send_win32_event( self,  BM_SETCHECK, BST_INDETERMINATE);
        else if ( val.is_checked)
            send_win32_event( self,  BM_SETCHECK, BST_CHECKED);
        else
            send_win32_event( self,  BM_SETCHECK, 0);

        send_win32_event( self, BM_SETSTATE, val.has_focus ? true : false);
    }




};


#define self this

string button:: class_name() { return GUI_STR("button"); }
types::int64  button::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = BS_PUSHBUTTON | BS_CENTER;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}


button::button() : m_impl(new button::impl(this) ) , m_copy_events(this) {
    detail::init_property( state, m_impl.get(), &impl::get_state, &impl::set_state);
}
button::~button() {
}





void button::click() {
    send_win32_event( self, BM_CLICK);
}




}}

// End of file
