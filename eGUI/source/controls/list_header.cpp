// list_header.cpp

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
#include "egui/controls/list_header.hpp"
#include "egui/controls/detail/get_item_ex.hpp"
#include "egui/core/win32/raw.hpp"

namespace egui { namespace ctrl {

namespace {
    void to_win32(const list_header_item & from, detail::wrap_win32<HDITEM> & to) {
        EGUI_TO_WIN32(from, to.m_raw, column_index, iOrder);
        EGUI_TO_WIN32(from, to.m_raw, width, cxy );
        EGUI_TO_WIN32(from, to.m_raw, image_index, iImage);
        to.set_text( from.text);
    }

    void from_win32(list_header_item & to, const detail::wrap_win32<HDITEM> & from) {
        to.text = from.m_text;
        EGUI_FROM_WIN32(to, from.m_raw, column_index, iOrder);
        EGUI_FROM_WIN32(to, from.m_raw, width, cxy );
        EGUI_FROM_WIN32(to, from.m_raw, image_index, iImage);
    }
}

struct list_header::impl {
    list_header * self;

    impl(list_header * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    typedef list_header::order_array order_array;



    int get_item_count() const { 
        return (int)send_win32_event( self, HDM_GETITEMCOUNT);
    }
    temporary_image_list get_images() const { 
        return win32::from((HIMAGELIST)send_win32_event( self, HDM_GETIMAGELIST));
    }
    void set_images(const temporary_image_list & val) {
        send_win32_event( self, HDM_SETIMAGELIST, 0, win32::to(val) );
    }
    order_array get_colum_orders() const { 
        int count = self->item_count;
        order_array a;
        a.resize(count);
        send_win32_event( self, HDM_GETORDERARRAY, count, &*a.begin() );
        return a;
    }
    void set_colum_orders(const order_array & a) {
        if ( a.size() != self->item_count )     
           throw exception( GUI_STR("list_header : col orders should match item count"));
        send_win32_event( self, HDM_SETORDERARRAY, a.size(), &*a.begin());
    }



    typedef types::list_header_item list_header_item;

    list_header_item get_item(int idx) const {
        detail::wrap_win32<HDITEM> result;
        result.m_raw.mask = HDI_FORMAT | HDI_HEIGHT | HDI_IMAGE | HDI_LPARAM | HDI_ORDER | HDI_TEXT | HDI_WIDTH;
        get_item_ex(result, self, HDM_GETITEM, idx);

        list_header_item egui;
        from_win32(egui, result);
        return egui;
    }
    void set_item( int idx, const list_header_item & val) {
        detail::wrap_win32<HDITEM> to_set;
        to_set.m_raw.mask = HDI_FORMAT | HDI_HEIGHT | HDI_IMAGE | HDI_LPARAM | HDI_ORDER | HDI_TEXT | HDI_WIDTH;
        to_win32(val, to_set);
        send_win32_event( self, HDM_SETITEM, idx, &to_set.m_raw);
    }

};

#define self this
string list_header:: class_name() { return GUI_STR("sysheader32"); }
types::int64  list_header::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = 0;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

list_header::list_header() : m_impl(new list_header::impl(this) ) , m_copy_events(this)  {
    egui::detail::init_property( images, m_impl.get(), &impl::get_images, &impl::set_images);
    egui::detail::init_property( colum_orders, m_impl.get(), &impl::get_colum_orders, &impl::set_colum_orders);
    egui::detail::init_property( item_count, m_impl.get(), &impl::get_item_count);
    egui::detail::init_property( item, m_impl.get(), &impl::get_item, &impl::set_item);
}
list_header::~list_header() {
}






void list_header:: insert_item(const types::list_header_item & val, int idx) { 
    if ( idx == -1) idx = 100000;
    detail::wrap_win32<HDITEM> to_set;
    to_set.m_raw.mask = HDI_FORMAT | HDI_HEIGHT | HDI_IMAGE | HDI_LPARAM | HDI_ORDER | HDI_TEXT | HDI_WIDTH;
    to_win32(val, to_set);

    send_win32_event( self, HDM_INSERTITEM, idx, &to_set.m_raw);
}
void list_header:: del_item(int idx) { 
    send_win32_event( self, HDM_DELETEITEM, idx);
}

}}

// End of file
