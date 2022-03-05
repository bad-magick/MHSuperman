// combo_box.cpp

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
#include "egui/controls/combo_box.hpp"

namespace egui { namespace ctrl {


struct combo_box::impl {
    combo_box * self;

    impl(combo_box * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    typedef combo_box::selection sel_type;

    int get_item_count() const { 
        return (int)send_win32_event( self, CB_GETCOUNT);
    }

    int get_sel() const { 
        return (int)send_win32_event( self, CB_GETCURSEL);
    }
    void set_sel(const int & val) {
        send_win32_event( self, CB_SETCURSEL,val);
    }
    int get_first_visible() const { 
        return (int)send_win32_event( self, CB_GETTOPINDEX);
    }
    void set_first_visible(const int & val) {
        send_win32_event( self, CB_SETTOPINDEX, val);
    }
    int get_horizontal_extent() const { 
        return (int)send_win32_event( self, CB_GETHORIZONTALEXTENT);
    }
    void set_horizontal_extent(const int & val) {
            send_win32_event( self, CB_SETHORIZONTALEXTENT,val);
    }

    sel_type get_edit_sel() const { 
        DWORD start,end;
        send_win32_event( self, CB_GETEDITSEL, (WPARAM)&start, &end);
        return sel_type( start, end);
    }
    void set_edit_sel(const sel_type & val) {
        send_win32_event( self,  wnd_msg(CB_SETEDITSEL).l_param_lo(val.start).l_param_hi(val.end) );
    }

    bool get_is_dropped() const { 
        return send_win32_event( self, CB_GETDROPPEDSTATE) != 0;
    }
    void set_is_dropped(const bool & val) {
        send_win32_event( self, CB_SHOWDROPDOWN, val);
    }
    void set_text_limit(const int & val) {
        send_win32_event( self, CB_LIMITTEXT, val);
    }


    string get_item_text(int val) const {
        int len = (int)send_win32_event( self, CB_GETLBTEXTLEN,val);
        string result;
        result.resize(len + 10 /*just in case*/);
        int new_size = (int)send_win32_event( self, CB_GETLBTEXT, val, &*result.begin() );
        result.resize( new_size >= 0 ? new_size : 0);
        return result;
    }


};

#define self this
string combo_box:: class_name() { return GUI_STR("combobox"); }
types::int64  combo_box::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = CBS_DROPDOWN | CBS_HASSTRINGS;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

combo_box::combo_box() : m_impl(new combo_box::impl(this) ) , m_copy_events(this)  {
    detail::init_property( item_count, m_impl.get(), &impl::get_item_count);
    detail::init_property( sel, m_impl.get(), &impl::get_sel, &impl::set_sel);
    detail::init_property( first_visible, m_impl.get(), &impl::get_first_visible, &impl::set_first_visible);
    detail::init_property( horizontal_extent, m_impl.get(), &impl::get_horizontal_extent, &impl::set_horizontal_extent);
    detail::init_property( edit_sel, m_impl.get(), &impl::get_edit_sel, &impl::set_edit_sel);
    detail::init_property( is_dropped, m_impl.get(), &impl::get_is_dropped, &impl::set_is_dropped);
    detail::init_property( text_limit, m_impl.get(), &impl::set_text_limit);

    detail::init_property( item_text, m_impl.get(), &impl::get_item_text);
}
combo_box::~combo_box() {
}
void combo_box::del_all_items() {
    send_win32_event( self, CB_RESETCONTENT);
}


void combo_box:: add_item(const string & str) { 
}
void combo_box:: add_sorted_item(const string & str) { 
    send_win32_event( self, CB_ADDSTRING, 0, str.c_str() );
}
void combo_box:: del_item(int idx) { 
    send_win32_event( self, CB_DELETESTRING, idx);
}
void combo_box:: insert_item(int idx, const string & str) { 
    send_win32_event( self, CB_INSERTSTRING, idx, str.c_str() );
}

int combo_box:: find_str(const string & str, int idx_after ) { 
    return (int)send_win32_event( self, CB_FINDSTRING, idx_after, str.c_str() );
}
int combo_box:: find_str_exact(const string & str, int idx_start ) { 
    return (int)send_win32_event( self, CB_FINDSTRINGEXACT, idx_start, str.c_str() );
}
int combo_box:: select_str(const string & str, int idx_after ) { 
    return (int)send_win32_event( self, CB_SELECTSTRING, idx_after, str.c_str() );
}

void combo_box:: clear() { 
    send_win32_event( self, WM_CLEAR);
}
void combo_box:: cut()  { 
    send_win32_event( self, WM_CUT);
}
void combo_box:: copy()  { 
    send_win32_event( self, WM_COPY);
}
void combo_box:: paste()  { 
    send_win32_event( self, WM_PASTE);
}



}}

// End of file
