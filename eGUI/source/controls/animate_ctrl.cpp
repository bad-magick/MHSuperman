// animate_ctrl.cpp

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
#include "egui/controls/animate_ctrl.hpp"

namespace egui { namespace ctrl {


struct animate_ctrl::impl {
    animate_ctrl * self;

    impl(animate_ctrl * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }



};
string animate_ctrl:: class_name() { return GUI_STR("SysAnimate32"); }
types::int64 animate_ctrl ::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = 0;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

animate_ctrl::animate_ctrl() : m_impl(new animate_ctrl::impl(this) ), m_copy_events(this) {
}
animate_ctrl::~animate_ctrl() {
}

#define self this

void animate_ctrl::open(int avi_id) { 
    send_win32_event( self, ACM_OPEN, 0, MAKEINTRESOURCE(avi_id) );
}
void animate_ctrl::open(const string & file_name) { 
    send_win32_event( self, ACM_OPEN, 0, file_name.c_str() );
}

void animate_ctrl::play(unsigned from, unsigned to, unsigned rep ) { 
    send_win32_event( self,  wnd_msg(ACM_PLAY).w_param(rep).l_param_lo(from).l_param_hi(to) );
}

void animate_ctrl::stop() { 
    send_win32_event( self, ACM_STOP);
}
void animate_ctrl::close() { 
    send_win32_event( self, ACM_OPEN, 0 );
}
void animate_ctrl::seek(unsigned to) { 
    play(to, to, 0);
}


}}

// End of file
