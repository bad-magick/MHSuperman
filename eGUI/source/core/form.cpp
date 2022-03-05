// form.cpp

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

#include "stdafx_core.h"
#include "egui/core/wnd.hpp"
#include "egui/core/detail/window_manager.hpp"
#include <boost/foreach.hpp>

namespace egui {

namespace {
    typedef std::vector<HWND> hwnd_array;
    void find_children_windows(hwnd_array & a, HWND h) {
        HWND child = ::GetWindow(h, GW_CHILD);
        while ( child) {
            a.push_back(child);
            child = ::GetWindow(child, GW_HWNDNEXT);
        }
    }

}

form::form() : m_is_modal(false) {
    hwnd_array children;
    find_children_windows(children, get_hwnd( (window_base*)this));
    BOOST_FOREACH(HWND h, children)
        detail::window_manager::inst().create_window_from_id(h);

    using namespace boost;
    events.on_notify += bind(mem_fn(&form::on_child_notify),this,_1);
}

void form::on_initialize() {
    window_base::on_initialize();

    if ( m_init.m_rect_set)
        full_rect = m_init.m_rect;

    visible = (m_init.m_style & style::visible) != 0;

    if ( m_init.m_style_set)
        style = m_init.m_style & ~form_style::modal;

    if ( m_init.m_style & form_style::modal)
        m_is_modal = true;
}

wnd<> form::try_child(int idx) const {
    HWND h = ::GetWindow( get_hwnd(this), GW_CHILD);
    while ( h) {
        if ( idx <= 0)
            return detail::window_manager::inst().create_window_from_id(h);
        --idx;
        h = ::GetWindow(h, GW_HWNDNEXT);
    }
    return wnd<>();
}
wnd<> form::try_child_by_id(int id) const {
    HWND h = ::GetDlgItem( get_hwnd(this), id);
    return detail::window_manager::inst().create_window_from_id(h);
}

int form::child_count() const {
    HWND h = ::GetWindow( get_hwnd(this), GW_CHILD);
    int count = 0;
    while ( h) {
        ++count;
        h = ::GetWindow(h, GW_HWNDNEXT);
    }
    return count;
}

wnd<> form::child_by_id(int id) const {
    wnd<> w = try_child_by_id(id);
    if ( w)
        return w;
    else
        throw exception( GUI_STR("child not found"));
}

wnd<> form::child(int idx) const {
    wnd<> w = try_child(idx);
    if ( w)
        return w;
    else
        throw exception( GUI_STR("child not found"));
}

void form::on_child_notify(ev::notify&) {
}


int msg_box(int buttons, const string & msg, wnd<> parent , string title  ) {
    if ( title.empty() && parent)
        title = parent->text;
    return ::MessageBox( get_hwnd(parent), msg.c_str(), title.c_str(), buttons);
}

void form::end_dialog(const wnd<> & ctrl) {
    if ( !m_is_modal)
        throw exception( GUI_STR("cannot call end dialog on non modal dialogs"));
    HWND h = get_hwnd(ctrl);
    int id = ::GetDlgCtrlID(h);
    ::EndDialog( get_hwnd(this), id);
}

string form::class_name() { return GUI_STR("#32770") ; }
types::int64 form::default_style() {
    types::int64 def_style = window_top::default_style();
    types::int64 style = DS_CONTROL | DS_CENTER;
    types::int64 ex = WS_EX_CONTROLPARENT;

    return  def_style | style | (ex << 32); 
}


}

// End of file
