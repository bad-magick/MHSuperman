// toolbar.cpp

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
#include "egui/controls/toolbar.hpp"

namespace egui { namespace ctrl {


struct toolbar::impl {
    toolbar * self;

    impl(toolbar * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    typedef wnd<> wnd_type;
    typedef types::toolbar_style::type style_type;


    temporary_image_list get_images() const { 
        return default_(); 
    }
    void set_images(const temporary_image_list & val) {
    }
    int get_item_count() const { 
        return default_(); 
    }
    void set_parent_wnd(const wnd_type  & val) {
    }

    int get_row_count() const { 
        return default_(); 
    }
    void set_row_count(const int & val) {
    }
    style_type get_toolbar_style() const { 
        return default_(); 
    }
    void set_toolbar_style(const style_type & val) {
    }
    int get_text_rows() const { 
        return default_(); 
    }

    int get_hot_item_sel() const { 
        return default_(); 
    }
    void set_hot_item_sel(const int & val) {
    }
    size get_total_size() const { 
        return default_(); 
    }
    size get_padding() const { 
        return default_(); 
    }
    void set_padding(const size & val) {
    }



    typedef toolbar_button_state::type state_type;
    typedef types::toolbar_button toolbar_button;


    bool get_button_enabled(int val) const {
        return default_();
    }
    void set_button_enabled( int idx, const bool & val) {
    }

    bool get_button_checked(int val) const {
        return default_();
    }
    void set_button_checked( int idx, const bool & val) {
    }

    bool get_button_pressed(int val) const {
        return default_();
    }
    void set_button_pressed( int idx, const bool & val) {
    }

    bool get_button_visible(int val) const {
        return default_();
    }
    void set_button_visible( int idx, const bool & val) {
    }

    bool get_button_indeterminate(int val) const {
        return default_();
    }
    void set_button_indeterminate( int idx, const bool & val) {
    }

    state_type get_button_state(int val) const {
        return default_();
    }
    void set_button_state( int idx, const state_type & val) {
    }


    size get_button_size(int val) const {
        return default_();
    }
    void set_button_size( int idx, const size & val) {
    }

    toolbar_button get_button(int val) const {
        return default_();
    }
    void set_button( int idx, const toolbar_button & val) {
    }


    rectangle get_item_rect(int val) const {
        return default_();
    }

    size get_bitmap_size(int val) const {
        return default_();
    }

    rectangle get_button_rect(int val) const {
        return default_();
    }


    void set_highlight_button( int idx, const bool & val) {
    }



};

#define self this
string toolbar:: class_name() { return GUI_STR("toolbarwindow32"); }
types::int64  toolbar::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = WS_CHILD | TBSTYLE_TRANSPARENT | CCS_NORESIZE | CCS_NODIVIDER | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

toolbar::toolbar() : m_impl(new toolbar::impl(this) ) {
    detail::init_property( item_count, m_impl.get(), &impl::get_item_count);
    detail::init_property( text_rows, m_impl.get(), &impl::get_text_rows);

    detail::init_property( parent_wnd, m_impl.get(), &impl::set_parent_wnd);

    detail::init_property( row_count, m_impl.get(), &impl::get_row_count, &impl::set_row_count);
    detail::init_property( toolbar_style, m_impl.get(), &impl::get_toolbar_style, &impl::set_toolbar_style);
    detail::init_property( hot_item_sel, m_impl.get(), &impl::get_hot_item_sel, &impl::set_hot_item_sel);
    detail::init_property( total_size, m_impl.get(), &impl::get_total_size);
    detail::init_property( padding, m_impl.get(), &impl::get_padding, &impl::set_padding);
    detail::init_property( images, m_impl.get(), &impl::get_images, &impl::set_images);
    detail::init_property( button_enabled, m_impl.get(), &impl::get_button_enabled, &impl::set_button_enabled);
    detail::init_property( button_checked, m_impl.get(), &impl::get_button_checked, &impl::set_button_checked);
    detail::init_property( button_pressed, m_impl.get(), &impl::get_button_pressed, &impl::set_button_pressed);
    detail::init_property( button_visible, m_impl.get(), &impl::get_button_visible, &impl::set_button_visible);
    detail::init_property( button_indeterminate, m_impl.get(), &impl::get_button_indeterminate, &impl::set_button_indeterminate);
    detail::init_property( button_state, m_impl.get(), &impl::get_button_state, &impl::set_button_state);
    detail::init_property( button_size, m_impl.get(), &impl::get_button_size, &impl::set_button_size);
    detail::init_property( button, m_impl.get(), &impl::get_button, &impl::set_button);

    detail::init_property( item_rect, m_impl.get(), &impl::get_item_rect);
    detail::init_property( bitmap_size, m_impl.get(), &impl::get_bitmap_size);
    detail::init_property( button_rect, m_impl.get(), &impl::get_button_rect);
    detail::init_property( highlight_button, m_impl.get(), &impl::set_highlight_button);
}
toolbar::~toolbar() {
}






void toolbar:: button_width(int min_width, int max_width) { 
}
void toolbar:: indent(int val) { 
}
void toolbar:: max_text_rows(int val) { 
}
void toolbar:: insert_button(const button_type & btn, int idx) { 
}
void toolbar:: del_button(int idx) { 
}

int toolbar::id_to_index(int cmd_id) const { 
    return 0;
}

void toolbar:: move_button(int old_idx, int new_idx) { 
}


}}

// End of file
