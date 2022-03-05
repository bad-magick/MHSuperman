// tree.cpp

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
#include "egui/controls/tree.hpp"

namespace egui { namespace ctrl {


struct tree::impl {
    tree * self;

    impl(tree * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }

    typedef tree::item_id item_id;


    item_id get_root() const { 
        return default_(); 
    }
    int get_count() const { 
        return default_(); 
    }
    int get_visible_count() const { 
        return default_(); 
    }

    int get_indent() const { 
        return default_(); 
    }
    void set_indent(const int & val) {
    }
    temporary_image_list get_images() const { 
        return default_(); 
    }
    void set_images(const temporary_image_list & val) {
    }
    color get_text_color() const { 
        return default_(); 
    }
    void set_text_color(const color & val) {
    }
    color get_bg_color() const { 
        return default_(); 
    }
    void set_bg_color(const color & val) {
    }
    color get_line_color() const { 
        return default_(); 
    }
    void set_line_color(const color & val) {
    }
    color get_insertmark_color() const { 
        return default_(); 
    }
    void set_insertmark_color(const color & val) {
    }

    int get_item_height() const { 
        return default_(); 
    }
    void set_item_height(const int & val) {
    }
    int get_scroll_time() const { 
        return default_(); 
    }
    void set_scroll_time(const int & val) {
    }
    item_id get_first_visible() const { 
        return default_(); 
    }
    void set_first_visible(const item_id & val) {
    }
    item_id get_sel() const { 
        return default_(); 
    }
    void set_sel(const item_id & val) {
    }
    item_id get_drop_hilighted() const { 
        return default_(); 
    }
    void set_drop_hilighted(const item_id & val) {
    }






    typedef types::tree_item tree_item;
    typedef types::tree_state tree_state;
    typedef types::tree_check_state::type check_type;



    tree_item get_item(item_id val) const {
        return default_();
    }
    void set_item( item_id idx, const tree_item & val) {
    }


    tree_state get_state(item_id val) const {
        return default_();
    }
    void set_state( item_id idx, const tree_state & val) {
    }


    bool get_check(item_id val) const {
        return default_();
    }
    void set_check( item_id idx, const bool & val) {
    }


    check_type get_check_state(item_id val) const {
        return default_();
    }
    void set_check_state( item_id idx, const check_type & val) {
    }


};

#define self this
string tree:: class_name() { return GUI_STR("systreeview32"); }
types::int64  tree::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = 0;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

tree::tree() : m_impl(new tree::impl(this) ) , m_copy_events(this)  {
    detail::init_property( root, m_impl.get(), &impl::get_root);
    detail::init_property( count, m_impl.get(), &impl::get_count);
    detail::init_property( visible_count, m_impl.get(), &impl::get_visible_count);

    detail::init_property( indent, m_impl.get(), &impl::get_indent, &impl::set_indent);
    detail::init_property( images, m_impl.get(), &impl::get_images, &impl::set_images);
    detail::init_property( text_color, m_impl.get(), &impl::get_text_color, &impl::set_text_color);
    detail::init_property( bg_color, m_impl.get(), &impl::get_bg_color, &impl::set_bg_color);
    detail::init_property( line_color, m_impl.get(), &impl::get_line_color, &impl::set_line_color);
    detail::init_property( insertmark_color, m_impl.get(), &impl::get_insertmark_color, &impl::set_insertmark_color);
    detail::init_property( item_height, m_impl.get(), &impl::get_item_height, &impl::set_item_height);
    detail::init_property( scroll_time, m_impl.get(), &impl::get_scroll_time, &impl::set_scroll_time);
    detail::init_property( first_visible, m_impl.get(), &impl::get_first_visible, &impl::set_first_visible);
    detail::init_property( sel, m_impl.get(), &impl::get_sel, &impl::set_sel);
    detail::init_property( drop_hilighted, m_impl.get(), &impl::get_drop_hilighted, &impl::set_drop_hilighted);

    detail::init_property( item, m_impl.get(), &impl::get_item, &impl::set_item);
    detail::init_property( state, m_impl.get(), &impl::get_state, &impl::set_state);
    detail::init_property( check, m_impl.get(), &impl::get_check, &impl::set_check);
    detail::init_property( check_state, m_impl.get(), &impl::get_check_state, &impl::set_check_state);
}
tree::~tree() {
}









void tree::ensure_visible(item_id h) { 
}
int tree::children_count(item_id h) const { 
    return 0;
}
void tree::insert_item(types::tree_item it, item_id parent, item_id after ) { 
}
tree::item_id tree::add_item(item_id parent_item, const types::tree_item & info) { 
    // after last child
    return 0;
} 
tree::item_id tree::add_root_item(const types::tree_item & info) { 
    return 0;
}
void tree::del_item(item_id id) { 
}
void tree::del_all_items() { 
}

void tree::expand(item_id h, types::tree_expand::type expand ) { 
}
void tree::collapse(item_id h) { 
}

tree::item_id tree::first_child(item_id h) const { 
    return 0;
}
tree::item_id tree::next_sibling(item_id h) const { 
    return 0;
}
tree::item_id tree::prev_sibling(item_id h) const { 
    return 0;
}
tree::item_id tree::parent_item(item_id h) const { 
    return 0;
}
tree::item_id tree::next_visible(item_id h) const { 
    return 0;
}
tree::item_id tree::prev_visible(item_id h) const {
    return 0;
}
}}

// End of file
