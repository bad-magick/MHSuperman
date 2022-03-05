// edit.cpp

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
#include "egui/controls/edit.hpp"

namespace egui { namespace ctrl {


struct edit::impl {
    edit * self;

    impl(edit * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }



    typedef edit::selection sel_type;

    int get_first_visible_line() const { 
		return (int)send_win32_event( self, EM_GETFIRSTVISIBLELINE);
    }

    char_ get_password_char() const { 
		return (char_)send_win32_event( self, EM_GETPASSWORDCHAR);
    }
    void set_password_char(const char_ & val) {
		send_win32_event( self, EM_SETPASSWORDCHAR, val);
    }
    bool get_read_only() const { 
		return (::GetWindowLong(raw_hwnd(), GWL_STYLE) & ES_READONLY) != 0;
    }
    void set_read_only(const bool & val) {
		send_win32_event( self, EM_SETREADONLY, val);
    }
    bool get_can_undo() const { 
        return send_win32_event( self, EM_CANUNDO) != 0;
    }

    int get_max_chars() const { 
    	return (int)send_win32_event( self, EM_GETLIMITTEXT);
    }
    void set_max_chars(const int & limit) {
    	send_win32_event( self,  wnd_msg(EM_LIMITTEXT).w_param(limit) );
    }
    sel_type get_sel() const { 
	    DWORD start, end;
	    send_win32_event( self,  EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
	    return sel_type(start,end);
    }
    void set_sel(const sel_type & val) {
    	send_win32_event( self,  EM_SETSEL, val.start, val.end);
    }

};
string edit:: class_name() { return GUI_STR("edit"); }
types::int64  edit::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = 0;
    types::int64 ex = WS_EX_CLIENTEDGE;

    return  def_style | style | (ex << 32); 
}

edit::edit() : m_impl(new edit::impl(this) ) , m_copy_events(this)  {
    detail::init_property( password_char, m_impl.get(), &impl::get_password_char, &impl::set_password_char);
    detail::init_property( read_only, m_impl.get(), &impl::get_read_only, &impl::set_read_only);
    detail::init_property( can_undo, m_impl.get(), &impl::get_can_undo);
    detail::init_property( max_chars, m_impl.get(), &impl::get_max_chars, &impl::set_max_chars);
    detail::init_property( sel, m_impl.get(), &impl::get_sel, &impl::set_sel);
    detail::init_property( first_visible_line, m_impl.get(), &impl::get_first_visible_line);
}
edit::~edit() {
}






#define self this

int  edit:: char_from_pos(const point& pnt) const {
	DWORD res = (DWORD)send_win32_event( self,  wnd_msg(EM_CHARFROMPOS).l_param(pnt.x,pnt.y) );
	return LOWORD(res);
}
int  edit:: line_from_pos(const point& pnt) const {
	DWORD res = (DWORD)send_win32_event( self,  wnd_msg(EM_CHARFROMPOS).l_param(pnt.x,pnt.y) );
	return HIWORD(res);
}
point edit:: pos_from_char(int char_idx) const {
	DWORD res = (DWORD)send_win32_event( self, EM_POSFROMCHAR, char_idx);
	return point( LOWORD(res), HIWORD(res) );
}

void edit:: replace_sel(const string &str, bool allow_undo ) { 
	send_win32_event( self,  EM_REPLACESEL, allow_undo, (LPARAM)str.c_str() );
}
void edit:: scroll_caret() { 
	send_win32_event( self,  EM_SCROLLCARET);
}
void edit:: scroll_horiz(int chars) { 
	send_win32_event( self, EM_LINESCROLL, chars);		
}


void edit:: empty_undo_buffer() { 
	send_win32_event( self,  EM_EMPTYUNDOBUFFER);
}
void edit:: undo() { 
	send_win32_event( self, EM_UNDO);
}
void edit:: clear() { 
	send_win32_event( self, WM_CLEAR);
}
void edit:: cut() { 
	send_win32_event( self, WM_CUT);
}
void edit:: copy() { 
	send_win32_event( self, WM_COPY);
}
void edit:: paste() { 
	send_win32_event( self, WM_PASTE);
}



}}

// End of file
