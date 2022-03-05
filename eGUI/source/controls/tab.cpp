// tab.cpp

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
#include "egui/controls/tab.hpp"

#include "egui/controls/detail/get_item_ex.hpp"
#include "egui/core/win32/raw.hpp"

namespace egui { namespace ctrl {


struct tab::impl {
    tab * self;

    impl(tab * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    typedef types::tab_style::type style_type;



    temporary_image_list get_images() const { 
        return win32::from( (HIMAGELIST)send_win32_event( self, TCM_GETIMAGELIST) );
    }
    void set_images(const temporary_image_list & val) {
        send_win32_event( self, TCM_SETIMAGELIST, 0, win32::to(val) );
    }
    int get_count() const { 
        return (int)send_win32_event( self, TCM_GETITEMCOUNT);
    }
    int get_sel() const { 
        return (int)send_win32_event( self, TCM_GETCURSEL);
    }
    void set_sel(const int & val) {
        send_win32_event( self, TCM_SETCURSEL, val);
    }

    void set_item_padding(const size & sz) {
        send_win32_event( self,  wnd_msg(TCM_SETPADDING).l_param_lo(sz.width).l_param_hi(sz.height) );
    }

    int get_row_count() const { 
        return (int)send_win32_event( self, TCM_GETROWCOUNT);
    }
    int get_focused_item() const { 
        return (int)send_win32_event( self, TCM_GETCURFOCUS);
    }
    void set_focused_item(const int & val) {
        send_win32_event( self, TCM_SETCURFOCUS, val);
    }

    void set_min_item_width(const int & val) {
        send_win32_event( self, TCM_SETMINTABWIDTH, 0, val);
    }
    style_type get_tab_style() const { 
        return (style_type)(DWORD)send_win32_event( self, TCM_GETEXTENDEDSTYLE);
    }
    void set_tab_style(const style_type & val) {
        send_win32_event( self, TCM_SETEXTENDEDSTYLE, ~0L, val);
    }



    typedef types::tab_item tab_item;


    void set_item_size( int idx, const size & sz) {
        send_win32_event( self,  wnd_msg(TCM_SETITEMSIZE).w_param(idx).l_param_lo(sz.width).l_param_hi(sz.height) );
    }

    tab_item get_item(int val) const {
        detail::wrap_win32<TCITEM> result;
        result.m_raw.mask = TCIF_IMAGE | TCIF_PARAM | TCIF_STATE | TCIF_TEXT;
        detail::get_item_ex(result, self, TCM_GETITEM, val);

        tab_item e;
        e.text = result.m_text;
        e.image_index = result.m_raw.iImage;
        if ( result.m_raw.dwState & TCIS_BUTTONPRESSED)
            e.is_pressed = true;
        if ( result.m_raw.dwState & TCIS_HIGHLIGHTED)
            e.is_highlighted = true;
        return e;
    }
    void set_item( int idx, const tab_item & val) {
        detail::wrap_win32<TCITEM> to_set;
        to_set.m_raw.mask = TCIF_IMAGE | TCIF_PARAM | TCIF_STATE | TCIF_TEXT;
        to_set.set_text( val.text);
        to_set.m_raw.iImage = val.image_index;
        if ( val.is_pressed)
            to_set.m_raw.dwState |= TCIS_BUTTONPRESSED;
        if ( val.is_highlighted)
            to_set.m_raw.dwState |= TCIS_HIGHLIGHTED;
        to_set.m_raw.dwStateMask = TCIS_BUTTONPRESSED | TCIS_HIGHLIGHTED;
        send_win32_event( self, TCM_SETITEM, idx, &to_set.m_raw);
    }


};

#define self this
string tab:: class_name() { return GUI_STR("systabcontrol32"); }
types::int64  tab::default_style() { 
    // no tab stop - this is how we know the difference between a tab and a tab form
    types::int64 def_style = window_top::default_style() & ~types::style::tab_stop;
    types::int64 style = 0;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

tab::tab() : m_impl(new tab::impl(this) )  , m_copy_events(this) {
    egui::detail::init_property( row_count, m_impl.get(), &impl::get_row_count);

    egui::detail::init_property( min_item_width, m_impl.get(), &impl::set_min_item_width);
    egui::detail::init_property( item_padding, m_impl.get(), &impl::set_item_padding);

    egui::detail::init_property( sel, m_impl.get(), &impl::get_sel, &impl::set_sel);
    egui::detail::init_property( focused_item, m_impl.get(), &impl::get_focused_item, &impl::set_focused_item);
    egui::detail::init_property( tab_style, m_impl.get(), &impl::get_tab_style, &impl::set_tab_style);
    egui::detail::init_property( images, m_impl.get(), &impl::get_images, &impl::set_images);
    egui::detail::init_property( count, m_impl.get(), &impl::get_count);

    egui::detail::init_property( item_size, m_impl.get(), &impl::set_item_size);
    egui::detail::init_property( item, m_impl.get(), &impl::get_item, &impl::set_item);
}
tab::~tab() {
}





 

rectangle tab::item_rect(int idx) const {
    RECT r;
    send_win32_event( self, TCM_GETITEMRECT, idx, &r);
    return win32::from(r);
}

void tab:: insert_item(types::tab_item val, int idx) { 
    if ( idx == -1) idx = count;


    detail::wrap_win32<TCITEM> to_set;
    to_set.m_raw.mask = TCIF_IMAGE | TCIF_PARAM | TCIF_STATE | TCIF_TEXT;
    to_set.set_text( val.text);
    to_set.m_raw.iImage = val.image_index;
    if ( val.is_pressed)
        to_set.m_raw.dwState |= TCIS_BUTTONPRESSED;
    if ( val.is_highlighted)
        to_set.m_raw.dwState |= TCIS_HIGHLIGHTED;
    to_set.m_raw.dwStateMask = TCIS_BUTTONPRESSED | TCIS_HIGHLIGHTED;

    send_win32_event( self, TCM_INSERTITEM, idx, &to_set.m_raw);
}
void tab:: del_item(int idx) { 
    send_win32_event( self, TCM_DELETEITEM, idx);
}
void tab:: del_all_items() { 
    send_win32_event( self, TCM_DELETEALLITEMS);
}

void tab:: deselect_all(bool exclude_focus ) { 
    send_win32_event( self, TCM_DESELECTALL, exclude_focus);
}
void tab:: highlight_item(int idx, bool do_highlight ) { 
    send_win32_event( self,  wnd_msg(TCM_HIGHLIGHTITEM).w_param(idx).l_param_lo(do_highlight) );
}



}}

// End of file
