// template.cpp

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

#include "stdafx_events.h"
#pragma warning (disable : 4800)
#include "egui/core/wnd.hpp"
#include "egui/events/detail/fwd.hpp"
#include "egui/events/detail/convert.hpp"
#include "egui/events/window_top.hpp"

#include "egui/events/animate_ctrl.hpp"
#include "egui/events/button.hpp"
#include "egui/events/check_box.hpp"
#include "egui/events/combo_box.hpp"
#include "egui/events/date_time.hpp"
#include "egui/events/edit.hpp"
#include "egui/events/group_box.hpp"
#include "egui/events/label.hpp"
#include "egui/events/list.hpp"
#include "egui/events/list_box.hpp"
#include "egui/events/list_header.hpp"
#include "egui/events/month_cal.hpp"
#include "egui/events/progress_bar.hpp"
#include "egui/events/radio_button.hpp"
#include "egui/events/rebar.hpp"
#include "egui/events/scroll_bar.hpp"
#include "egui/events/slider.hpp"
#include "egui/events/spin_button.hpp"
#include "egui/events/status_bar.hpp"
#include "egui/events/tab.hpp"
#include "egui/events/tab_form.hpp"
#include "egui/events/toolbar.hpp"
#include "egui/events/tooltip.hpp"
#include "egui/events/tree.hpp"
#include "egui/controls/all.hpp"

namespace egui { namespace handle_events {
using namespace converters;

////////////////////////////////////////////////////////////////////////////////////
// window

void window_top::ev:: activate::init_event() {
    do_default_processing = true;
    unsigned long msg = *access_win32_data::msg(this);
    if ( msg == WM_ACTIVATE) {
        int64 wp = *access_win32_data::wparam(this);
        int type = LOWORD(wp);
        switch(type) {
            case WA_ACTIVE: 
                access_read_only_object(is_active) = true; break;
            case WA_INACTIVE:
                break;
            case WA_CLICKACTIVE:
                access_read_only_object(is_active) = true; 
                access_read_only_object(by_mouse) = true; 
                break;
        }
    }
    if ( msg == WM_ACTIVATEAPP) {
        int64 wp = *access_win32_data::wparam(this);
        access_read_only_object(is_active) = wp != 0; 
        access_read_only_object(from_other_app) = true;
    }
    if ( msg == WM_CHILDACTIVATE) {
        access_read_only_object(is_active) = true; 
    }

}
window_top::ev:: enable::enable() {
    do_default_processing = true;
    add( convert(enabled, get_wparam() ));
}
window_top::ev:: set_redraw::set_redraw() {
    do_default_processing = true;
    add( convert(redraw_state, get_wparam() ));
}
window_top::ev:: show::show() {
    do_default_processing = true;
    add( convert(shown, get_wparam() ));
}
window_top::ev:: timer::timer() {
    do_default_processing = true;
    add( convert(id, get_wparam() ));
}
window_top::ev:: horiz_scroll::horiz_scroll() {
    do_default_processing = true;
    add( convert(scroll_pos, get_wparam(), lo() ));
    add( convert(thumb_pos, get_wparam(), hi() ));
}
window_top::ev:: vert_scroll::vert_scroll() {
    do_default_processing = true;
    add( convert(scroll_pos, get_wparam(), lo() ));
    add( convert(thumb_pos, get_wparam(), hi() ));
}

#define IF_WM(wm_msg,prefix,name) if ( msg == wm_msg) return prefix :: name;

namespace {
    struct to_paint_event : null_set {
        typedef window_top::ev::paint paint;
        static paint::type get(const unsigned long & msg) {
            IF_WM(WM_PAINT, paint, paint_);
            IF_WM(WM_SYNCPAINT, paint, sync_paint);
            IF_WM(WM_PRINT, paint, print);
            IF_WM(WM_PRINTCLIENT, paint, print_client);
            IF_WM(WM_NCPAINT, paint, nc_paint);

            return paint::paint_;
        }
    };
}

window_top::ev:: paint::paint() {
    add( convert(paint_type, get_msg(), to_paint_event() ));
    do_default_processing = true;
}

void window_top::ev::erase_bg::init_event() {
    erase_done = false;
    add( convert(dc, get_wparam()));
    add( convert(erase_done, get_l_result()));
    do_default_processing = true;
}
void window_top::ev::key_press::init_event() {
    do_default_processing = true;
    add( convert( key_code, get_wparam()));

    unsigned long msg = *access_win32_data::msg(this);
    if ( msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN)
        access_read_only_object(pressed) = true;
    if ( msg == WM_SYSKEYDOWN || msg == WM_SYSKEYUP)
        access_read_only_object(is_sys_key) = true;
}
void window_top::ev::char_::init_event() {
    do_default_processing = true;
    add( convert( char_code, get_wparam()));

    unsigned long msg = *access_win32_data::msg(this);
    switch ( msg) {
    case WM_CHAR:       access_read_only_object(char_type) = character; break;
    case WM_SYSCHAR:    access_read_only_object(char_type) = sys_char; break;
    case WM_DEADCHAR:   access_read_only_object(char_type) = dead_char; break;
    case WM_SYSDEADCHAR: access_read_only_object(char_type) = sys_dead_char; break;
    default: assert(false);
    }
}
void window_top::ev::mouse_click::init_event() {
    unsigned long msg = *access_win32_data::msg(this);

    do_default_processing = true;
    switch ( msg) {
    case WM_LBUTTONDOWN     :
    case WM_RBUTTONDOWN     :
    case WM_MBUTTONDOWN     :
    case WM_XBUTTONDOWN     :  
    case WM_NCLBUTTONDOWN   : 
    case WM_NCRBUTTONDOWN   :
    case WM_NCMBUTTONDOWN   :
    case WM_NCXBUTTONDOWN   :    
        access_read_only_object(down) = true;
        break;
    }

    switch ( msg) {
    case WM_NCLBUTTONDOWN   :   
    case WM_NCLBUTTONUP     :   
    case WM_NCRBUTTONDOWN   :   
    case WM_NCRBUTTONUP     :   
    case WM_NCMBUTTONDOWN   :   
    case WM_NCMBUTTONUP     :   
    case WM_NCXBUTTONDOWN   :        
    case WM_NCXBUTTONUP     :  
        access_read_only_object(in_non_client_area) = true;
        break;
    }

    switch ( msg) {
    case WM_LBUTTONDOWN     :
    case WM_LBUTTONUP       :
    case WM_NCLBUTTONDOWN   :   
    case WM_NCLBUTTONUP     :   
        access_read_only_object(button_type) = left; break;

    case WM_RBUTTONDOWN     :
    case WM_RBUTTONUP       :
    case WM_NCRBUTTONDOWN   :   
    case WM_NCRBUTTONUP     :   
        access_read_only_object(button_type) = right; break;

    case WM_MBUTTONDOWN     :
    case WM_MBUTTONUP       :
    case WM_XBUTTONDOWN     :  
    case WM_XBUTTONUP       :   
    case WM_NCMBUTTONDOWN   :   
    case WM_NCMBUTTONUP     :   
    case WM_NCXBUTTONDOWN   :        
    case WM_NCXBUTTONUP     :        
        access_read_only_object(button_type) = middle; break;
    }

}

window_top::ev::set_cursor::set_cursor() {
    do_default_processing = true;
}
void window_top::ev::mouse_move::init_event() {
    do_default_processing = true;
}
void window_top::ev::mouse_double_click::init_event() {
    do_default_processing = true;
    unsigned long msg = *access_win32_data::msg(this);

    switch ( msg) {
    case WM_NCLBUTTONDBLCLK :   
    case WM_NCRBUTTONDBLCLK :   
    case WM_NCMBUTTONDBLCLK :   
    case WM_NCXBUTTONDBLCLK :   
        access_read_only_object(in_non_client_area) = true;
        break;
    }

    switch ( msg) {
    case WM_LBUTTONDBLCLK   :
    case WM_NCLBUTTONDBLCLK :   
        access_read_only_object(button_type) = left; break;

    case WM_RBUTTONDBLCLK   :
    case WM_NCRBUTTONDBLCLK :   
        access_read_only_object(button_type) = right; break;

    case WM_MBUTTONDBLCLK   :
    case WM_XBUTTONDBLCLK   :   
    case WM_NCMBUTTONDBLCLK :   
    case WM_NCXBUTTONDBLCLK :        
        access_read_only_object(button_type) = middle; break;
    }
}

void window_top::ev::menu::init_event() {
    id = LOWORD( *access_win32_data::wparam(this) );
}


void window_top::ev:: move::init_event() {
    do_default_processing = true;
}
void window_top::ev:: size::init_event() {
    do_default_processing = true;
}
void window_top::ev:: close::init_event() {
    do_default_processing = true;
}
void window_top::ev:: quit::init_event() {
    do_default_processing = true;
}
void window_top::ev:: help::init_event() {
    do_default_processing = true;
}
void window_top::ev:: enter_idle::init_event() {
    do_default_processing = true;
}
void window_top::ev:: sizing::init_event() {
    do_default_processing = true;
}
void window_top::ev:: moving::init_event() {
    do_default_processing = true;
}
void window_top::ev:: set_focus::init_event() {
    do_default_processing = true;
}
void window_top::ev:: kill_focus::init_event() {
    do_default_processing = true;
}

////////////////////////////////////////////////////////////////////////////////////
// combo box

namespace {
    int wm_command_code( ::egui::ev::base * p) {
        int64 wp = *access_win32_data::wparam(p);
        return HIWORD(wp);
    }
    int wm_notify_code( ::egui::ev::base * p) {
        int64 lp = *access_win32_data::lparam(p);
        NMHDR * header = (NMHDR*)lp;
        int code = header->code;

        return code;
    }

    int notify_code( ::egui::ev::base * p) {
        unsigned long msg = *access_win32_data::msg(p);
        if ( msg == WM_COMMAND)
            return wm_command_code(p);
        else if ( msg == WM_NOTIFY)
            return wm_notify_code(p);
        assert(false);
        return 0;
    }

    struct l_param_ptr {
        mutable void * m_ptr ;
        l_param_ptr( ::egui::ev::base * p) {
            int64 lp = *access_win32_data::lparam(p);
            m_ptr = (void*)lp;
        }

        template<class type> operator type*() const { return static_cast<type*>(m_ptr); }
    };
}

void combo_box::ev:: focus ::init_event() {
    int code = notify_code(this);
    if ( code == CBN_SETFOCUS)
        access_read_only_object(received) = true;
}

void combo_box::ev:: drop_down ::init_event() {
    int code = notify_code(this);
    if ( code == CBN_DROPDOWN)
        access_read_only_object(dropped) = true;
}

////////////////////////////////////////////////////////////////////////////////////
// date time

void date_time::ev:: drop_down ::init_event() {
    int code = notify_code(this);
    if ( code == DTN_DROPDOWN)
        access_read_only_object(dropped) = true;
}
void date_time::ev:: focus ::init_event() {
    int code = notify_code(this);
    if ( code == NM_SETFOCUS)
        access_read_only_object(received) = true;
}

////////////////////////////////////////////////////////////////////////////////////
// edit

void edit::ev:: focus ::init_event() {
    int code = notify_code(this);
    if ( code == EN_SETFOCUS)
        access_read_only_object(received) = true;
}

////////////////////////////////////////////////////////////////////////////////////
// list

void list::ev:: item_changing ::init_event() {
    NMLISTVIEW * p = l_param_ptr(this);
    access_read_only_object( idx) = p->iItem ;
    access_read_only_object( sub_idx) = p->iSubItem ;
    access_read_only_object( old_state) = (types::list_item_state::type)p->uOldState ;
    access_read_only_object( new_state) = (types::list_item_state::type)p->uNewState ;

    add( convert(allow, get_l_result(), reverse_bool() ));
}
void list::ev:: item_changed ::init_event() {
    NMLISTVIEW * p = l_param_ptr(this);
    access_read_only_object( idx) = p->iItem ;
    access_read_only_object( sub_idx) = p->iSubItem ;
    access_read_only_object( old_state) = (types::list_item_state::type)p->uOldState ;
    access_read_only_object( new_state) = (types::list_item_state::type)p->uNewState ;
}
void list::ev:: column_click ::init_event() {
    NMLISTVIEW * p = l_param_ptr(this);
    access_read_only_object( col_idx) = p->iSubItem ;
}
void list::ev:: drag ::init_event() {
    int code = notify_code(this);
    if ( code == LVN_BEGINDRAG )
        access_read_only_object(dragged_with_left) = true;

    NMLISTVIEW * p = l_param_ptr(this);
    access_read_only_object( idx) = p->iItem ;
}
void list::ev:: state_changed ::init_event() {
    NMLVODSTATECHANGE * p = l_param_ptr(this);
    access_read_only_object( first_idx) = p->iFrom;
    access_read_only_object( last_idx) = p->iTo;
    access_read_only_object( old_state) = (types::list_item_state::type)p->uOldState ;
    access_read_only_object( new_state) = (types::list_item_state::type)p->uNewState ;
}
void list::ev:: hot_track ::init_event() {
    NMLISTVIEW * p = l_param_ptr(this);
    access_read_only_object( idx) = p->iItem ;

    access_read_only_object( idx) = p->iItem ;
    access_read_only_object( sub_idx) = p->iSubItem ;
    add( convert(allow, get_l_result(), reverse_bool() ));
}
void list::ev:: click ::init_event() {
    int code = notify_code(this);
    switch ( code) {
    case NM_CLICK:
    case NM_DBLCLK: 
        access_read_only_object(left_click) = true;
    };

    switch ( code) {
    case NM_DBLCLK: 
    case NM_RDBLCLK :
        access_read_only_object(double_click) = true;
    };
}
void list::ev:: focus ::init_event() {
    int code = notify_code(this);
    if ( code == NM_SETFOCUS)
        access_read_only_object(received) = true;
}

////////////////////////////////////////////////////////////////////////////////////
// list box

void list_box::ev:: focus ::init_event() {
    int code = notify_code(this);
    if ( code == LBN_SETFOCUS)
        access_read_only_object(received) = true;
}

////////////////////////////////////////////////////////////////////////////////////
// list header

void list_header::ev:: drag ::init_event() {
    int code = notify_code(this);
    if ( code == HDN_BEGINDRAG)
        access_read_only_object(start_of_drag) = true;

    NMHEADER * p = l_param_ptr(this);
    access_read_only_object( col_idx) = p->iItem;
    access_read_only_object( dragged_with) = (button)p->iButton;
}

void list_header::ev:: item_changing ::init_event() {
    NMHEADER * p = l_param_ptr(this);
    access_read_only_object( col_idx) = p->iItem;
    add( convert(allow, get_l_result(), reverse_bool() ));
}
void list_header::ev:: item_changed ::init_event() {
    NMHEADER * p = l_param_ptr(this);
    access_read_only_object( col_idx) = p->iItem;
}
void list_header::ev:: item_click ::init_event() {
    NMHEADER * p = l_param_ptr(this);
    access_read_only_object( col_idx) = p->iItem;
    int code = notify_code(this);
    if ( code == HDN_ITEMDBLCLICK )
        access_read_only_object(double_click) = true;
}
void list_header::ev:: divider_dbl_click ::init_event() {
    NMHEADER * p = l_param_ptr(this);
    access_read_only_object( col_idx) = p->iItem;
}

////////////////////////////////////////////////////////////////////////////////////
// month cal

void month_cal::ev:: sel_change ::init_event() {
    int code = notify_code(this);
    if ( code == MCN_SELCHANGE)
        access_read_only_object(user_made) = true;
}


////////////////////////////////////////////////////////////////////////////////////
// spin_button

void spin_button::ev:: sel_change ::init_event() {
    _NM_UPDOWN * p = l_param_ptr(this);
    access_read_only_object( current_pos) = p->iPos;
    access_read_only_object( new_pos) = p->iPos + p->iDelta;
}

////////////////////////////////////////////////////////////////////////////////////
// status bat

void status_bar::ev:: click ::init_event() {
    int code = notify_code(this);
    switch ( code) {
    case NM_CLICK:
    case NM_DBLCLK: 
        access_read_only_object(left_click) = true;
    };

    switch ( code) {
    case NM_DBLCLK: 
    case NM_RDBLCLK :
        access_read_only_object(double_click) = true;
    };

    NMMOUSE * p = l_param_ptr(this);
    access_read_only_object(idx) = (int)p->dwItemSpec;
}

////////////////////////////////////////////////////////////////////////////////////
// tab

void tab::ev:: click ::init_event() {
    int code = notify_code(this);
    switch ( code) {
    case NM_CLICK:
    case NM_DBLCLK: 
        access_read_only_object(left_click) = true;
    };

    switch ( code) {
    case NM_DBLCLK: 
    case NM_RDBLCLK :
        access_read_only_object(double_click) = true;
    };
}

////////////////////////////////////////////////////////////////////////////////////
// tree

//    int code = notify_code(this);
//    access_read_only_object( ) =


void tree::ev:: single_expand ::init_event() {
    NMTREEVIEW * p = l_param_ptr(this);
    access_read_only_object(item) = p->itemNew.hItem;
}
void tree::ev:: sel_changing ::init_event() {
    NMTREEVIEW * p = l_param_ptr(this);
    access_read_only_object(new_item) = p->itemNew.hItem;
    access_read_only_object(old_item) = p->itemOld.hItem;
    add( convert(allow, get_l_result(), reverse_bool() ));
}
void tree::ev:: sel_changed ::init_event() {
    NMTREEVIEW * p = l_param_ptr(this);
    access_read_only_object(new_item) = p->itemNew.hItem;
    access_read_only_object(old_item) = p->itemOld.hItem;
}
void tree::ev:: item_expanding ::init_event() {
    NMTREEVIEW * p = l_param_ptr(this);
    access_read_only_object(item) = p->itemNew.hItem;
    access_read_only_object(expand_type) = (types::tree_expand::type)p->action;
    add( convert(allow, get_l_result(), reverse_bool() ));
}
void tree::ev:: item_expanded ::init_event() {
    NMTREEVIEW * p = l_param_ptr(this);
    access_read_only_object(item) = p->itemNew.hItem;
    access_read_only_object(expand_type) = (types::tree_expand::type)p->action;
}
void tree::ev:: click ::init_event() {
    int code = notify_code(this);
    switch ( code) {
    case NM_CLICK:
    case NM_DBLCLK: 
        access_read_only_object(left_click) = true;
    };

    switch ( code) {
    case NM_DBLCLK: 
    case NM_RDBLCLK :
        access_read_only_object(double_click) = true;
    };
}
void tree::ev:: focus ::init_event() {
    int code = notify_code(this);
    if ( code == NM_SETFOCUS)
        access_read_only_object(received) = true;
}


////////////////////////////////////////////////////////////////////////////////////
// 

//void ::ev::  ::init_event() {
//}





}}

// End of file
