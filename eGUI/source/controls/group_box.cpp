// group_box.cpp

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
#include "egui/controls/group_box.hpp"

namespace egui { namespace ctrl {


struct group_box::impl {
    group_box * self;

    impl(group_box * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }



};

#define self this

types::int64  group_box::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = WS_GROUP | BS_GROUPBOX;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

group_box::group_box() : m_impl(new group_box::impl(this) ) {
}
group_box::~group_box() {
}





}}

// End of file
