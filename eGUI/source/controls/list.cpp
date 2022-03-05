// list.cpp

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
#include "egui/controls/list.hpp"
#include "egui/controls/detail/get_item_ex.hpp"
#include "egui/core/win32/raw.hpp"
#include "egui/core/detail/window_manager.hpp"

namespace egui { namespace ctrl {

namespace {
    void to_win32(const types::list_item & from, detail::wrap_win32<LVITEM> & to) {
        to.set_text( from.text);
        EGUI_TO_WIN32(from, to.m_raw, state, state);
        EGUI_TO_WIN32(from, to.m_raw, image_index, iImage);
        EGUI_TO_WIN32(from, to.m_raw, indent, iIndent);
    }

    void from_win32(types::list_item & to, const detail::wrap_win32<LVITEM> & from) {
        to.text = from.m_text;
        EGUI_FROM_WIN32(to, from.m_raw, state, state);
        EGUI_FROM_WIN32(to, from.m_raw, image_index, iImage);
        EGUI_FROM_WIN32(to, from.m_raw, indent, iIndent);
    }


/*  void to_win32(const types::list_column & e, detail::wrap_win32<LVCOLUMN> & w) {
        e.set_text( w.text);
        EGUI_TO_WIN32(e, w.m_raw );
    }

    void from_win32(types::list_column & e, const detail::wrap_win32<LVCOLUMN> & w) {
        e.text = w.m_text;
        EGUI_FROM_WIN32(e, w.m_raw );
    }
*/

    const int LIST_COLUMN_FLAGS = /*LVCF_FMT | */ LVCF_IMAGE | LVCF_ORDER | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
    void to_win32(const types::list_column & e, detail::wrap_win32<LVCOLUMN> & w) {
        w.set_text( e.text);
        EGUI_TO_WIN32(e, w.m_raw, width, cx);
        EGUI_TO_WIN32(e, w.m_raw, original_index, iSubItem);
        EGUI_TO_WIN32(e, w.m_raw, cur_index, iOrder);
        EGUI_TO_WIN32(e, w.m_raw, image_index, iImage);
    }

    void from_win32(types::list_column & e, const detail::wrap_win32<LVCOLUMN> & w) {
        e.text = w.m_text;
        EGUI_FROM_WIN32(e, w.m_raw, width, cx);
        EGUI_FROM_WIN32(e, w.m_raw, original_index, iSubItem);
        EGUI_FROM_WIN32(e, w.m_raw, cur_index, iOrder);
        EGUI_FROM_WIN32(e, w.m_raw, image_index, iImage);
    }



    wnd<> find_by_hwnd( HWND h) {
        return egui::detail::window_manager::inst().create_window_from_id( h);
    }
}


struct list::impl {
    list * self;

    impl(list * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }


    typedef wnd<> wnd_type;
    typedef types::list_style::type style_type;
    typedef types::list_view::type list_view_type;
    typedef list::order_array order_array;


    color get_bg_color() const { 
        return win32::from((COLORREF)send_win32_event( self, LVM_GETBKCOLOR));
    }
    void set_bg_color(const color & val) {
        send_win32_event( self, LVM_SETBKCOLOR, 0, win32::to(val) );
    }
    color get_text_color() const { 
        return win32::from((COLORREF)send_win32_event( self, LVM_GETTEXTCOLOR));
    }
    void set_text_color(const color & val) {
        send_win32_event( self, LVM_SETTEXTCOLOR, 0, win32::to(val));
    }
    color get_text_bg_color() const { 
        return (COLORREF)send_win32_event( self, LVM_GETTEXTBKCOLOR);
    }
    void set_text_bg_color(const color & val) {
        send_win32_event( self, LVM_SETTEXTBKCOLOR, 0, win32::to(val));
    }
    temporary_image_list get_images(types::list_image::type type) const { 
        return win32::from((HIMAGELIST)send_win32_event( self, LVM_GETIMAGELIST,type));
    }
    void set_images(types::list_image::type type, const temporary_image_list & val) {
        send_win32_event( self, LVM_SETIMAGELIST, type, win32::to(val)) ;
    }
    int get_item_count() const { 
        return (int)send_win32_event( self, LVM_GETITEMCOUNT);
    }
    void set_item_count(const int & val) {
        send_win32_event( self, LVM_SETITEMCOUNT, val);
    }
    int get_first_visible() const { 
        return (int)send_win32_event( self, LVM_GETTOPINDEX);
    }
    int get_sel_count() const { 
        return (int)send_win32_event( self, LVM_GETSELECTEDCOUNT);
    }
    int get_col_count() const { 
        // it's not a problem if we do it like this - it's a few columns anyway
        int idx = 0;
        LVCOLUMN ignore = { 0 };
        ignore.mask = LVCF_FMT;
        while (idx < 1000) {
            bool has = send_win32_event( self, LVM_GETCOLUMN, idx, &ignore) != 0;
            if ( !has) 
                return idx;
            ++idx;
        }
        throw exception( GUI_STR("could not get count ???"));
    }
    order_array get_colum_orders() const { 
        order_array a;
        int count = 16;
        do {
            a.resize(count, -1);
            send_win32_event( self, LVM_GETCOLUMNORDERARRAY, count, &*a.begin() );
            count *= 2;
        } while ( *a.rbegin() != -1);

        size_t new_size = std::distance( a.begin(), std::find(a.begin(), a.end(), -1) );
        a.resize(new_size);
        return a;
    }
    void set_colum_orders(const order_array & a) {
        assert( (int)a.size() == get_col_count() );
        send_win32_event( self,  LVM_SETCOLUMNORDERARRAY, a.size(), &*a.begin() );
    }

    wnd_type get_header() const { 
        wnd<> w = find_by_hwnd( (HWND)send_win32_event( self, LVM_GETHEADER) );
        return w;
    }
    int get_sel() const { 
        return (int)send_win32_event( self,  wnd_msg(LVM_GETNEXTITEM).w_param(-1).l_param_lo(LVNI_ALL | LVNI_SELECTED) ); 
    }
    void set_sel(const int & idx) {
        if ( idx >= 0) {
            set_state_with_mask(idx, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
            self->ensure_visible(idx);
        }
        else {
            // no selection
            int old_sel = get_sel();
            set_state_with_mask(old_sel, 0, LVIS_SELECTED | LVIS_FOCUSED);
        }
    }

    style_type get_list_style() const { 
        return (style_type)(DWORD)send_win32_event( self, LVM_GETEXTENDEDLISTVIEWSTYLE);
    }
    void set_list_style(const style_type & val) {
        send_win32_event( self, LVM_SETEXTENDEDLISTVIEWSTYLE, ~0L, (DWORD)val);
    }
    list_view_type get_view_type() const { 
        return (list_view_type)(self->style & LVS_TYPEMASK);
    }
    void set_view_type(const list_view_type & val) {
        self->style = self->style | (val & LVS_TYPEMASK);
    }











    typedef types::list_item_state::type list_item_state_type;
    typedef types::list_column list_column;
    typedef types::list_item list_item;




    int get_state_with_mask(int idx, int mask) const {
        return (int)send_win32_event( self, LVM_GETITEMSTATE, idx, mask);
    }
    void set_state_with_mask(int idx, int state, int mask) {
        LVITEM info = { 0 };
        info.stateMask = mask;
        info.state = state;
        send_win32_event( self,  LVM_SETITEMSTATE, idx, &info);
    }


    list_item_state_type get_state(int val) const {
        return (list_item_state_type)get_state_with_mask(val, 0xFFF);
    }
    void set_state( int idx, const list_item_state_type & val) {
        set_state_with_mask(idx, val, 0xFFF);
    }

    bool get_check(int idx) const {
        UINT val = get_state_with_mask(idx, LVIS_STATEIMAGEMASK);
        bool is = (val >> 12) > 1;
        return is;
    }
    void set_check( int idx, const bool & set) {
        UINT set_val = set ? 2 : 1;
        UINT val =INDEXTOSTATEIMAGEMASK(set_val);
        set_state_with_mask( idx, val, LVIS_STATEIMAGEMASK);
    }

    list_column get_col(int idx) const {
        detail::wrap_win32<LVCOLUMN> result;
        result.m_raw.mask = LIST_COLUMN_FLAGS;
        get_item_ex(result, self, LVM_GETCOLUMN, idx);
        list_column c;
        from_win32(c, result);
        return c;
    }
    void set_col( int idx, const list_column & val) {
        detail::wrap_win32<LVCOLUMN> to_set;
        to_set.m_raw.mask = LIST_COLUMN_FLAGS;
        to_win32(val, to_set);
        send_win32_event( self, LVM_SETCOLUMN, idx, &to_set);
    }

    list_item get_item(int val) const {
        return self->sub_item(val, 0);
    }
    void set_item( int idx, const list_item & val) {
        self->sub_item(idx, 0, val);
    }


    point get_item_pos(int idx) const {
        POINT pnt;
        send_win32_event( self, LVM_GETITEMPOSITION, idx, &pnt);
        return win32::from(pnt);
    }
    void set_item_pos( int idx, const point & val) {
        send_win32_event( self, LVM_SETITEMPOSITION32, idx, &win32::to(val) );
    }


    int get_col_width(int val) const {
        return (int)send_win32_event( self, LVM_GETCOLUMNWIDTH, val);
    }
    void set_col_width( int idx, const int & val) {
        send_win32_event( self,  wnd_msg(LVM_SETCOLUMNWIDTH).w_param(idx).l_param_lo(val) ); 
    }





};

#define self this
string list:: class_name() { return GUI_STR("syslistview32"); }
types::int64  list::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = LVS_REPORT | LVS_SINGLESEL;
    types::int64 ex = WS_EX_CLIENTEDGE;

    return  def_style | style | (ex << 32); 
}

list::list() : m_impl(new list::impl(this) ) , m_copy_events(this)  {
    egui::detail::init_property( text_color, m_impl.get(), &impl::get_text_color, &impl::set_text_color);
    egui::detail::init_property( text_bg_color, m_impl.get(), &impl::get_text_bg_color, &impl::set_text_bg_color);
    egui::detail::init_property( images, m_impl.get(), &impl::get_images, &impl::set_images);
    egui::detail::init_property( item_count, m_impl.get(), &impl::get_item_count, &impl::set_item_count);
    egui::detail::init_property( first_visible, m_impl.get(), &impl::get_first_visible);
    egui::detail::init_property( sel_count, m_impl.get(), &impl::get_sel_count);
    egui::detail::init_property( col_count, m_impl.get(), &impl::get_col_count);
    egui::detail::init_property( colum_orders, m_impl.get(), &impl::get_colum_orders, &impl::set_colum_orders);
    egui::detail::init_property( header, m_impl.get(), &impl::get_header);
    egui::detail::init_property( sel, m_impl.get(), &impl::get_sel, &impl::set_sel);
    egui::detail::init_property( list_style, m_impl.get(), &impl::get_list_style, &impl::set_list_style);
    egui::detail::init_property( view_type, m_impl.get(), &impl::get_view_type, &impl::set_view_type);
    egui::detail::init_property( bg_color, m_impl.get(), &impl::get_bg_color, &impl::set_bg_color);

    egui::detail::init_property( state, m_impl.get(), &impl::get_state, &impl::set_state);
    egui::detail::init_property( check, m_impl.get(), &impl::get_check, &impl::set_check);
    egui::detail::init_property( col, m_impl.get(), &impl::get_col, &impl::set_col);
    egui::detail::init_property( item, m_impl.get(), &impl::get_item, &impl::set_item);
    egui::detail::init_property( item_pos, m_impl.get(), &impl::get_item_pos, &impl::set_item_pos);
    egui::detail::init_property( col_width, m_impl.get(), &impl::get_col_width, &impl::set_col_width);

}
list::~list() {
}








void list::  insert_item(const types::list_item &val, int idx){ 
    detail::wrap_win32<LVITEM> to_set;
    if ( idx == -1)
        idx = INT_MAX;
    to_set.m_raw.iItem = idx;
    to_set.m_raw.iSubItem = 0;
    to_set.m_raw.mask = LVIF_IMAGE | LVIF_INDENT | LVIF_TEXT | LVIF_STATE ;
    to_win32(val, to_set);
    send_win32_event( self, LVM_INSERTITEM, 0, &to_set.m_raw);
}
void list::  del_item(int idx){ 
    send_win32_event( self, LVM_DELETEITEM, idx);
}
void list::  del_all_items(){ 
    send_win32_event( self, LVM_DELETEALLITEMS);
}
int list::  string_width(const string & text){ 
    return (int)send_win32_event( self, LVM_GETSTRINGWIDTH, 0, text.c_str() );
}
void list::  insert_col(const types::list_column & col, int idx){ 
    detail::wrap_win32<LVCOLUMN> to_set;
    to_set.m_raw.mask = LIST_COLUMN_FLAGS; 
    to_win32(col, to_set);

    if ( idx < 0) idx = col_count; //if -1 -> at end
    send_win32_event( self, LVM_INSERTCOLUMN, idx, &to_set.m_raw);
}
void list::  del_col(int idx){ 
    send_win32_event( self, LVM_DELETECOLUMN, idx);
}

void list::  ensure_visible(int idx, bool partially_ok ){ 
    send_win32_event( self, LVM_ENSUREVISIBLE, idx, partially_ok);
}
void list::  scroll(size sz){ 
    send_win32_event( self, LVM_SCROLL, sz.width, sz.height);
}
void list::  update_item(int idx){ 
    send_win32_event( self, LVM_UPDATE, idx);
}

types::list_item list::sub_item(int idx, int sub_idx) const {
    detail::wrap_win32<LVITEM> result;
    result.m_raw.iItem = idx;
    result.m_raw.iSubItem = sub_idx;
    result.m_raw.mask = LVIF_IMAGE | LVIF_INDENT | LVIF_TEXT | LVIF_STATE ;
    detail::get_item_ex(result, self, LVM_GETITEM, 0);
    list_item i;
    from_win32(i, result);
    return i;
}
void list::sub_item(int idx, int sub_idx, const types::list_item & val) {
    detail::wrap_win32<LVITEM> to_set;
    to_set.m_raw.iItem = idx;
    to_set.m_raw.iSubItem = sub_idx;
    to_set.m_raw.mask = LVIF_IMAGE | LVIF_INDENT | LVIF_TEXT | LVIF_STATE ;
    to_win32(val, to_set);
    send_win32_event( self, LVM_SETITEM, 0, &to_set.m_raw);
}


}}

// End of file
