// radio_button.cpp

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
#include "egui/controls/radio_button.hpp"

namespace egui { namespace ctrl {


struct radio_button::impl {
    radio_button * self;

    impl(radio_button * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    bool get_checked() const { 
            return send_win32_event( self, BM_GETCHECK) == BST_CHECKED;
    }
    void set_checked(const bool & check_me) {
        // if I set this to false, don't set anything else to true
        send_win32_event( self, BM_SETCHECK, check_me ? BST_CHECKED : BST_UNCHECKED);

        // un-click the other radio button, if any...
        wnd<> prev = self->prev;
        if ( self->style & style::group )
            prev = null; 
        while ( prev) {
            if ( wnd<radio_button> rb = try_wnd_cast<radio_button>(prev) ) {
                if ( rb->checked ) {
                    send_win32_event( self, rb, BM_SETCHECK /* , 0 */);
                    return;
                }
            }
            else 
                break; // not radio button
            if ( prev->style & style::group)
                break; // v1.6.2+ - stop at first "Group" button
            
            prev = prev->prev;
        }

        wnd<> next = self->next;
        while ( next) {
            if ( next->style & style::group)
                break; // v1.6.2+ - stop at first "Group" button
            if ( wnd<radio_button> rb = try_wnd_cast<radio_button>(next) ) {
                if ( rb->checked ) {
                    send_win32_event( self, rb, BM_SETCHECK /* , 0 */);
                    return;
                }
            }
            else 
                break; // not radio button
            next = next->next;
        }


    }


};

#define self this
types::int64  radio_button::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = BS_RADIOBUTTON;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

radio_button::radio_button() : m_impl(new radio_button::impl(this) ) {
    detail::init_property( checked, m_impl.get(), &impl::get_checked, &impl::set_checked);
}
radio_button::~radio_button() {
}






}}

// End of file
