// multi_edit.cpp

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
#include "egui/controls/multi_edit.hpp"

namespace egui { namespace ctrl {


struct multi_edit::impl {
    multi_edit * self;

    impl(multi_edit * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    int get_line_count() const { 
		return (int)send_win32_event( self, EM_GETLINECOUNT);
    }


};

#define self this
types::int64  multi_edit::default_style() { 
    types::int64 def_style = edit::default_style();
    types::int64 style = ES_MULTILINE;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

multi_edit::multi_edit() : m_impl(new multi_edit::impl(this) ) , m_copy_events(this)  {
    detail::init_property( line_count, m_impl.get(), &impl::get_line_count);
}
multi_edit::~multi_edit() {
}





void multi_edit::fmt_lines(bool add_soft_enters) { 
	send_win32_event( self,  wnd_msg(EM_FMTLINES).w_param(add_soft_enters) );
}
int  multi_edit::line_length(int line_idx) const { 
	int char_idx = (int)send_win32_event( self,  wnd_msg(EM_LINEINDEX).w_param(line_idx) );
	return (int)send_win32_event( self,  wnd_msg(EM_LINELENGTH).w_param(char_idx) ); 
}
string multi_edit::line(int line_idx) const { 
	int chars = line_length(line_idx);
	string str;
	str.resize(chars + sizeof(WORD) );
	*(WORD*)(&*str.begin()) = chars;
	chars = (int)send_win32_event( self, wnd_msg(EM_GETLINE).w_param(line_idx).l_param(&*str.begin()) );
	str.resize(chars);
	return str;
}

int  multi_edit::line_from_char(int char_idx) const { 
	return (int)send_win32_event( self, EM_LINEFROMCHAR, char_idx);
}
int  multi_edit::line_index(int idx) const { 
	return (int)send_win32_event( self,  wnd_msg(EM_LINEINDEX).w_param(idx) );
}

void multi_edit::scroll(int horiz_chars, int vert_lines) { 
		send_win32_event( self, EM_LINESCROLL, horiz_chars, vert_lines);		
}
void multi_edit::scroll_vert(int lines) { 
		scroll(0, lines);
}


}}

// End of file
