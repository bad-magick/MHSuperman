// label.cpp

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
#include "egui/controls/label.hpp"

namespace egui { namespace ctrl {


struct label::impl {
    label * self;

    impl(label * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }



};

#define self this
types::int64  label::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = 0;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

label::label() : m_impl(new label::impl(this) ) {
}
label::~label() {
}





}}

// End of file
