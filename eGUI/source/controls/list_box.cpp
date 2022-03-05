// list_box.cpp

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
#include "egui/controls/list_box.hpp"

namespace egui { namespace ctrl {


struct list_box::impl {
    list_box * self;

    impl(list_box * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }



    int get_item_count() const { 
        return (int)send_win32_event( self, LB_GETCOUNT);
    }
    void set_item_count(const int & val) {
        send_win32_event( self, LB_SETCOUNT, val);
    }
    int get_sel() const { 
        return (int)send_win32_event( self, LB_GETCURSEL);
    }
    void set_sel(const int & val) {
        send_win32_event( self, LB_SETCURSEL,val);
    }
    int get_first_visible() const { 
        return (int)send_win32_event( self, LB_GETTOPINDEX);
    }
    void set_first_visible(const int & val) {
        send_win32_event( self, LB_SETTOPINDEX, val);
    }
    int get_horizontal_extent() const { 
        return (int)send_win32_event( self, LB_GETHORIZONTALEXTENT);
    }
    void set_horizontal_extent(const int & val) {
        send_win32_event( self, LB_SETHORIZONTALEXTENT,val);
    }
    int get_sel_count() const { 
        return (int)send_win32_event( self, LB_GETSELCOUNT);
    }
    int get_focused_item() const { 
        return (int)send_win32_event( self, LB_GETCARETINDEX);
    }
    void set_focused_item(const int & val) {
        send_win32_event( self, LB_SETCARETINDEX, val, true);
    }

    bool get_multi_sel(int idx) const {
        return (int)send_win32_event( self, LB_GETSEL,idx) > 0;
    }
    void set_multi_sel( int idx, const bool & val) {
        send_win32_event( self, LB_SETSEL, val, idx);
    }


};

#define self this
string list_box:: class_name() { return GUI_STR("listbox"); }
types::int64  list_box::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = 0;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

list_box::list_box() : m_impl(new list_box::impl(this) ) , m_copy_events(this)  {
    detail::init_property( sel, m_impl.get(), &impl::get_sel, &impl::set_sel);
    detail::init_property( first_visible, m_impl.get(), &impl::get_first_visible, &impl::set_first_visible);
    detail::init_property( horizontal_extent, m_impl.get(), &impl::get_horizontal_extent, &impl::set_horizontal_extent);
    detail::init_property( sel_count, m_impl.get(), &impl::get_sel_count);
    detail::init_property( focused_item, m_impl.get(), &impl::get_focused_item, &impl::set_focused_item);
    detail::init_property( item_count, m_impl.get(), &impl::get_item_count, &impl::set_item_count);
    detail::init_property( multi_sel, m_impl.get(), &impl::get_multi_sel, &impl::set_multi_sel);
}
list_box::~list_box() {
}









string list_box::item_text(int idx) const {
    int len = (int)send_win32_event( self, LB_GETTEXTLEN,idx);
    string result;
    result.resize(len + 10 /*just in case*/);
    int new_size = (int)send_win32_event( self, LB_GETTEXT, idx, &*result.begin() );
    result.resize( new_size >= 0 ? new_size : 0);
    return result;
}

void list_box::  del_all_items() { 
    send_win32_event( self, LB_RESETCONTENT);
}
void list_box::  add_item(const string & str) { 
    insert_item( -1, str);
}
void list_box::  add_sorted_item(const string & str) { 
    send_win32_event( self, LB_ADDSTRING, 0, str.c_str() );
}
void list_box::  del_item(int idx) { 
    send_win32_event( self, LB_DELETESTRING, idx);
}
void list_box::  insert_item(int idx, const string & str) { 
    send_win32_event( self, LB_INSERTSTRING, idx, str.c_str() );
}

int list_box::find_str(const string & str, int idx_after ) { 
    return (int)send_win32_event( self, LB_FINDSTRING, idx_after, str.c_str() );
}
int list_box::find_str_exact(const string & str, int idx_start ) { 
    return (int)send_win32_event( self, LB_FINDSTRINGEXACT, idx_start, str.c_str() );
}
int list_box::select_str(const string & str, int idx_after ) { 
    return (int)send_win32_event( self, LB_SELECTSTRING, idx_after, str.c_str() );
}

}}

// End of file
