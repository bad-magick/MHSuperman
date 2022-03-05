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
#include "egui/core/wnd.hpp"
#include "egui/events/detail/fwd.hpp"
#include "egui/core/detail/building_egui/event_manager.hpp"

#include "egui/events/detail/convert.hpp"
#include "egui/events/window_top.hpp"

#include "egui/events/animate_ctrl.hpp"
#include "egui/events/button.hpp"
#include "egui/events/check_box.hpp"
#include "egui/events/combo_box.hpp"
#include "egui/events/date_time.hpp"
#include "egui/events/edit.hpp"
#include "egui/events/multi_edit.hpp"
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

#include <boost/foreach.hpp>

namespace egui { 

namespace detail_ { 
    void init_events() {
        static bool inited_already = false;
        if ( inited_already)
            return;
        inited_already = true;

        // init events
        using namespace egui::detail;
        window_event_coll events;
        
        // window top
        //
        { typedef handle_events::window_top::ev ev;
        window_events::creator_coll & w = events[ window_info<window_top>() ].events;
        w[WM_MOVE] = event_info<ev::move>();
        w[WM_SIZE] = event_info<ev::size>();

        w[WM_ACTIVATE ] = event_info<ev:: activate>();
        w[WM_ACTIVATEAPP ] = event_info<ev:: activate>();
        w[WM_CHILDACTIVATE ] = event_info<ev:: activate>();

        w[WM_ENABLE ] = event_info<ev:: enable>();
        w[WM_SETREDRAW ] = event_info<ev:: set_redraw>();
        w[WM_CLOSE ] = event_info<ev:: close>();
        w[WM_QUIT ] = event_info<ev:: quit>();
        w[WM_SHOWWINDOW ] = event_info<ev:: show>();
        w[WM_SETCURSOR ] = event_info<ev:: set_cursor>();
        w[WM_HELP ] = event_info<ev:: help>();
        w[WM_TIMER ] = event_info<ev:: timer>();
        w[WM_HSCROLL ] = event_info<ev:: horiz_scroll>();
        w[WM_VSCROLL ] = event_info<ev:: vert_scroll>();
        w[WM_ENTERIDLE ] = event_info<ev:: enter_idle>();
        w[WM_MOVING ] = event_info<ev:: moving>();
        w[WM_SIZING ] = event_info<ev:: sizing>();
        
        w[WM_PAINT ] = event_info<ev:: paint>();
        w[WM_SYNCPAINT ] = event_info<ev:: paint>();
        w[WM_PRINT ] = event_info<ev:: paint>();
        w[WM_PRINTCLIENT ] = event_info<ev:: paint>();
        w[WM_NCPAINT ] = event_info<ev:: paint>();
        
        w[WM_ERASEBKGND ] = event_info<ev:: erase_bg>();
        
        w[WM_KEYDOWN             ] = event_info<ev:: key_press>();
        w[WM_KEYUP               ] = event_info<ev:: key_press>();
        w[WM_SYSKEYDOWN          ] = event_info<ev:: key_press>();
        w[WM_SYSKEYUP            ] = event_info<ev:: key_press>();

        w[WM_CHAR                ] = event_info<ev:: char_>();
        w[WM_DEADCHAR            ] = event_info<ev:: char_>();
        w[WM_SYSCHAR             ] = event_info<ev:: char_>();
        w[WM_SYSDEADCHAR         ] = event_info<ev:: char_>();

        w[WM_MOUSEMOVE ] = event_info<ev:: mouse_move>();
        w[WM_NCMOUSEMOVE ] = event_info<ev:: mouse_move>();

        w[WM_LBUTTONDOWN     ] = event_info<ev:: mouse_click>();
        w[WM_LBUTTONUP       ] = event_info<ev:: mouse_click>();
        w[WM_NCLBUTTONDOWN   ] = event_info<ev:: mouse_click >();
        w[WM_NCLBUTTONUP     ] = event_info<ev:: mouse_click >();
        w[WM_RBUTTONDOWN      ] = event_info<ev:: mouse_click >();
        w[WM_RBUTTONUP        ] = event_info<ev:: mouse_click >();
        w[WM_NCRBUTTONDOWN    ] = event_info<ev:: mouse_click >();
        w[WM_NCRBUTTONUP      ] = event_info<ev:: mouse_click >();
        w[WM_MBUTTONDOWN      ] = event_info<ev:: mouse_click >();
        w[WM_MBUTTONUP        ] = event_info<ev:: mouse_click >();
        w[WM_XBUTTONDOWN      ] = event_info<ev:: mouse_click >();
        w[WM_XBUTTONUP        ] = event_info<ev:: mouse_click >();
        w[WM_NCMBUTTONDOWN    ] = event_info<ev:: mouse_click >();
        w[WM_NCMBUTTONUP      ] = event_info<ev:: mouse_click >();
        w[WM_NCXBUTTONDOWN    ] = event_info<ev:: mouse_click >();
        w[WM_NCXBUTTONUP      ] = event_info<ev:: mouse_click >();

        w[WM_LBUTTONDBLCLK    ] = event_info<ev:: mouse_double_click >();
        w[WM_NCLBUTTONDBLCLK  ] = event_info<ev:: mouse_double_click >();
        w[WM_RBUTTONDBLCLK    ] = event_info<ev:: mouse_double_click >();
        w[WM_NCRBUTTONDBLCLK  ] = event_info<ev:: mouse_double_click >();
        w[WM_MBUTTONDBLCLK    ] = event_info<ev:: mouse_double_click >();
        w[WM_XBUTTONDBLCLK    ] = event_info<ev:: mouse_double_click >();
        w[WM_NCMBUTTONDBLCLK  ] = event_info<ev:: mouse_double_click >();
        w[WM_NCXBUTTONDBLCLK  ] = event_info<ev:: mouse_double_click >();

        w[WM_SETFOCUS ] = event_info<ev:: set_focus>();
        w[WM_KILLFOCUS ] = event_info<ev:: kill_focus>();

        w[ egui::detail::g_wm_menu_command ] = event_info<ev:: menu>();
        }


        // animate_ctrl
        //
        { typedef handle_events::animate_ctrl::ev ev;
        window_events::creator_coll & w = events[ window_info<animate_ctrl>() ].notifications;
         w[ACN_START ] = event_info<ev:: start>();
         w[ACN_STOP ] = event_info<ev:: stop>();
        }

        // button
        //
        { typedef handle_events::button::ev ev;
        window_events::creator_coll & w = events[ window_info<button>() ].notifications;
        w[ BN_CLICKED] = event_info<ev:: clicked>();
        w[ BN_SETFOCUS] = event_info<ev:: focus>();
        w[ BN_KILLFOCUS] = event_info<ev:: focus>();
        }

        // check_box
        //
        { typedef handle_events::check_box::ev ev;
        window_events::creator_coll & w = events[ window_info<check_box>() ].notifications;
        }

        // combo_box
        //
        { typedef handle_events::combo_box::ev ev;
        window_events::creator_coll & w = events[ window_info<combo_box>() ].notifications;
        w[ CBN_SELCHANGE] = event_info<ev:: sel_change>();
        w[ CBN_SETFOCUS] = event_info<ev:: focus>();
        w[ CBN_KILLFOCUS] = event_info<ev:: focus>();
        w[ CBN_EDITCHANGE] = event_info<ev:: edit_change>();
        w[ CBN_EDITUPDATE] = event_info<ev:: edit_update>();
        w[ CBN_DROPDOWN] = event_info<ev:: drop_down>();
        w[ CBN_CLOSEUP] = event_info<ev:: drop_down>();
        }

        // date_time
        //
        { typedef handle_events::date_time::ev ev;
        window_events::creator_coll & w = events[ window_info<date_time>() ].notifications;
        w[ DTN_DATETIMECHANGE ] = event_info<ev:: sel_change>();
        w[ DTN_DROPDOWN ] = event_info<ev:: drop_down>();
        w[ DTN_CLOSEUP ] = event_info<ev:: drop_down>();
        w[ NM_SETFOCUS ] = event_info<ev:: focus>();
        w[ NM_KILLFOCUS ] = event_info<ev:: focus>();
        }

        // edit
        //
        { typedef handle_events::edit::ev ev;
        window_events::creator_coll & w = events[ window_info<edit>() ].notifications;
        w[ EN_SETFOCUS  ] = event_info<ev:: focus>();
        w[ EN_KILLFOCUS ] = event_info<ev:: focus>();
        w[ EN_CHANGE ] = event_info<ev:: change>();
        w[ EN_UPDATE ] = event_info<ev:: update>();
        w[ EN_MAXTEXT ] = event_info<ev:: max_text>();
        }

        // group_box
        //
        { typedef handle_events::group_box::ev ev;
        window_events::creator_coll & w = events[ window_info<group_box>() ].notifications;
        // w[ ] = event_info<ev:: >();
        }

        // label
        //
        { typedef handle_events::label::ev ev;
        window_events::creator_coll & w = events[ window_info<label>() ].notifications;
        // w[ ] = event_info<ev:: >();
        }

        // list
        //
        { typedef handle_events::list::ev ev;
        window_events::creator_coll & w = events[ window_info<list>() ].notifications;
        w[ LVN_ITEMCHANGING ] = event_info<ev:: item_changing>();
        w[ LVN_ITEMCHANGED ] = event_info<ev:: item_changed>();
        w[ LVN_COLUMNCLICK] = event_info<ev:: column_click>();
        w[ LVN_BEGINDRAG] = event_info<ev:: drag>();
        w[ LVN_BEGINRDRAG] = event_info<ev:: drag>();
        w[ LVN_ODSTATECHANGED] = event_info<ev:: state_changed>();
        w[ LVN_HOTTRACK ] = event_info<ev:: hot_track>();

        w[ NM_SETFOCUS ] = event_info<ev:: focus>();
        w[ NM_KILLFOCUS ] = event_info<ev:: focus>();

        w[ NM_CLICK ] = event_info<ev:: click>();
        w[ NM_DBLCLK ] = event_info<ev:: click >();
        w[ NM_RCLICK ] = event_info<ev:: click>();
        w[ NM_RDBLCLK ] = event_info<ev:: click >();
        }

        // list_box
        //
        { typedef handle_events::list_box::ev ev;
        window_events::creator_coll & w = events[ window_info<list_box>() ].notifications;
        w[ LBN_SELCHANGE] = event_info<ev:: sel_change>();
        w[ LBN_SELCANCEL] = event_info<ev:: sel_cancel>();
        w[ LBN_SETFOCUS] = event_info<ev:: focus>();
        w[ LBN_KILLFOCUS] = event_info<ev:: focus>();
        }

        // list_header
        //
        { typedef handle_events::list_header::ev ev;
        window_events::creator_coll & w = events[ window_info<list_header>() ].notifications;
        w[ HDN_BEGINDRAG] = event_info<ev:: drag>();
        w[ HDN_ENDDRAG] = event_info<ev:: drag>();
        w[ HDN_ITEMCHANGING] = event_info<ev:: item_changing>();
        w[ HDN_ITEMCHANGED] = event_info<ev:: item_changed>();
        w[ HDN_ITEMCLICK] = event_info<ev:: item_click>();
        w[ HDN_DIVIDERDBLCLICK] = event_info<ev:: divider_dbl_click>();

        w[ NM_RCLICK ] = event_info<ev:: right_click>();
        }

        // month_cal
        //
        { typedef handle_events::month_cal::ev ev;
        window_events::creator_coll & w = events[ window_info<month_cal>() ].notifications;
        w[ MCN_SELCHANGE] = event_info<ev:: sel_change>();
        }

        // multi_edit
        //
        { typedef handle_events::multi_edit::ev ev;
        window_events::creator_coll & w = events[ window_info<multi_edit>() ].notifications;
        // w[ ] = event_info<ev:: >();
        }

        // progress_bar
        //
        { typedef handle_events::progress_bar::ev ev;
        window_events::creator_coll & w = events[ window_info<progress_bar>() ].notifications;
        // w[ ] = event_info<ev:: >();
        }

        // radio_button
        //
        { typedef handle_events::radio_button::ev ev;
        window_events::creator_coll & w = events[ window_info<radio_button>() ].notifications;
        // w[ ] = event_info<ev:: >();
        }

        // rebar
        //
        { typedef handle_events::rebar::ev ev;
        window_events::creator_coll & w = events[ window_info<rebar>() ].notifications;
        // w[ ] = event_info<ev:: >();
        }

        // scroll_bar
        //
        { typedef handle_events::scroll_bar::ev ev;
        window_events::creator_coll & w = events[ window_info<ctrl::scroll_bar>() ].notifications;
        // w[ ] = event_info<ev:: >();
        }

        // slider
        //
        { typedef handle_events::slider::ev ev;
        window_events::creator_coll & w = events[ window_info<slider>() ].notifications;
        // w[ ] = event_info<ev:: >();
        }

        // spin_button
        //
        { typedef handle_events::spin_button::ev ev;
        window_events::creator_coll & w = events[ window_info<spin_button>() ].notifications;
        w[ UDN_DELTAPOS] = event_info<ev:: sel_change>();
        }

        // status_bar
        //
        { typedef handle_events::status_bar::ev ev;
        window_events::creator_coll & w = events[ window_info<status_bar>() ].notifications;
        w[ NM_CLICK ] = event_info<ev:: click>();
        w[ NM_DBLCLK ] = event_info<ev:: click >();
        w[ NM_RCLICK ] = event_info<ev:: click>();
        w[ NM_RDBLCLK ] = event_info<ev:: click >();
        }

        // tab
        //
        { typedef handle_events::tab::ev ev;
        window_events::creator_coll & w = events[ window_info<tab>() ].notifications;
        w[ NM_CLICK ] = event_info<ev:: click>();
        w[ NM_DBLCLK ] = event_info<ev:: click >();
        w[ NM_RCLICK ] = event_info<ev:: click>();
        w[ NM_RDBLCLK ] = event_info<ev:: click >();
        
        w[ TCN_FOCUSCHANGE] = event_info<ev:: focus_change>();
        w[ TCN_SELCHANGE] = event_info<ev:: sel_change>();
        w[ TCN_SELCHANGING] = event_info<ev:: sel_changing>();
        }

        // toolbar
        //
        { typedef handle_events::toolbar::ev ev;
        window_events::creator_coll & w = events[ window_info<toolbar>() ].notifications;
        // w[ ] = event_info<ev:: >();
        }

        // tooltip
        //
        { typedef handle_events::tooltip::ev ev;
        window_events::creator_coll & w = events[ window_info<tooltip>() ].notifications;
        // w[ ] = event_info<ev:: >();
        }

        // tree
        //
        { typedef handle_events::tree::ev ev;
        window_events::creator_coll & w = events[ window_info<tree>() ].notifications;
        w[ TVN_SINGLEEXPAND] = event_info<ev:: single_expand>();
        w[ TVN_SELCHANGING] = event_info<ev:: sel_changing>();
        w[ TVN_SELCHANGED] = event_info<ev:: sel_changed>();
        w[ TVN_ITEMEXPANDING] = event_info<ev:: item_expanding>();
        w[ TVN_ITEMEXPANDED] = event_info<ev:: item_expanded>();

        w[ NM_SETFOCUS ] = event_info<ev:: focus>();
        w[ NM_KILLFOCUS ] = event_info<ev:: focus>();

        w[ NM_CLICK ] = event_info<ev:: click>();
        w[ NM_DBLCLK ] = event_info<ev:: click >();
        w[ NM_RCLICK ] = event_info<ev:: click>();
        w[ NM_RDBLCLK ] = event_info<ev:: click >();
        }

        /*
         // xxx
        //
        { typedef handle_events::xxx::ev ev;
        window_events::creator_coll & w = events[ window_info<xxx>() ].notifications;
        // w[ ] = event_info<ev:: >();
        }
        */


        ///////////////////////////////////////////////////////////////////////////////
        // Event -> Event handler
#define ADD_EVENT(name) \
    coll[ typeid( ev:: name ) ] = event_caller<w>( &we::on_ ## name ); \
    h.push_back( member_func_as_event_handler( &w::on_  ## name , &we::on_  ## name  ) )

        egui::detail::event_call_coll coll;
        
        // window_top
        {
            typedef egui::handle_events::window_top::ev ev;
            typedef egui::window_top w;
            typedef egui::window_top::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;

            ADD_EVENT( move);
            ADD_EVENT( size);
            ADD_EVENT( activate);
            ADD_EVENT( enable);
            ADD_EVENT( set_redraw);
            ADD_EVENT( close);
            ADD_EVENT( quit);
            ADD_EVENT( show);
            ADD_EVENT( set_cursor);
            ADD_EVENT( help);
            ADD_EVENT( timer);
            ADD_EVENT( horiz_scroll);
            ADD_EVENT( vert_scroll);
            ADD_EVENT( enter_idle);
            ADD_EVENT( sizing);
            ADD_EVENT( moving);
            ADD_EVENT( paint);
            ADD_EVENT( erase_bg);
            ADD_EVENT( key_press);
            ADD_EVENT( char_);
            ADD_EVENT( set_focus);
            ADD_EVENT( kill_focus);
            ADD_EVENT( mouse_move);
            ADD_EVENT( mouse_click);
            ADD_EVENT( mouse_double_click);
        }              

        // animate_ctrl
        {
            typedef egui::handle_events::animate_ctrl::ev ev;
            typedef egui::animate_ctrl w;
            typedef egui::animate_ctrl::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;

            ADD_EVENT( start);
            ADD_EVENT( stop);
        }

        // button
        {
            typedef egui::handle_events::button::ev ev;
            typedef egui::button w;
            typedef egui::button::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            ADD_EVENT( clicked);
            ADD_EVENT( focus);
        }

        // check_box
        {
            typedef egui::handle_events::check_box::ev ev;
            typedef egui::check_box w;
            typedef egui::check_box::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
        }

        // combo_box
        {
            typedef egui::handle_events::combo_box::ev ev;
            typedef egui::combo_box w;
            typedef egui::combo_box::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            ADD_EVENT( sel_change);
            ADD_EVENT( focus);
            ADD_EVENT( edit_change);
            ADD_EVENT( edit_update);
            ADD_EVENT( drop_down);
//            ADD_EVENT( );
        }

        // date_time
        {
            typedef egui::handle_events::date_time::ev ev;
            typedef egui::date_time w;
            typedef egui::date_time::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            ADD_EVENT( sel_change);
            ADD_EVENT( drop_down);
            ADD_EVENT( focus);
        }

        // edit
        {
            typedef egui::handle_events::edit::ev ev;
            typedef egui::edit w;
            typedef egui::edit::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
            ADD_EVENT( focus);
            ADD_EVENT( change);
            ADD_EVENT( update);
            ADD_EVENT( max_text);
        }

        // group_box
        {
            typedef egui::handle_events::group_box::ev ev;
            typedef egui::group_box w;
//            typedef egui::group_box::events_type we;
            // ADD_EVENT( );
        }

        // label
        {
            typedef egui::handle_events::label::ev ev;
            typedef egui::label w;
            typedef egui::label::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
        }

        // list
        {
            typedef egui::handle_events::list::ev ev;
            typedef egui::list w;
            typedef egui::list::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
            ADD_EVENT( item_changing);
            ADD_EVENT( item_changed);
            ADD_EVENT( column_click);
            ADD_EVENT( drag);
            ADD_EVENT( state_changed);
            ADD_EVENT( hot_track);
            ADD_EVENT( click);
            ADD_EVENT( focus);
        }

        // list_box
        {
            typedef egui::handle_events::list_box::ev ev;
            typedef egui::list_box w;
            typedef egui::list_box::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
            ADD_EVENT( sel_change);
            ADD_EVENT( sel_cancel);
            ADD_EVENT( focus);
        }

        // list_header
        {
            typedef egui::handle_events::list_header::ev ev;
            typedef egui::list_header w;
            typedef egui::list_header::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
            ADD_EVENT( drag);
            ADD_EVENT( item_changing);
            ADD_EVENT( item_changed);
            ADD_EVENT( item_click);
            ADD_EVENT( divider_dbl_click);
            ADD_EVENT( right_click);
        }

        // month_cal
        {
            typedef egui::handle_events::month_cal::ev ev;
            typedef egui::month_cal w;
            typedef egui::month_cal::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
            ADD_EVENT( sel_change);
        }

        // multi_edit
        {
            typedef egui::handle_events::multi_edit::ev ev;
            typedef egui::multi_edit w;
            typedef egui::multi_edit::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
        }

        // progress_bar
        {
            typedef egui::handle_events::progress_bar::ev ev;
            typedef egui::progress_bar w;
            typedef egui::progress_bar::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
        }

        // radio_button
        {
            typedef egui::handle_events::radio_button::ev ev;
            typedef egui::radio_button w;
            typedef egui::radio_button::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
        }

        // rebar
        {
            typedef egui::handle_events::rebar::ev ev;
            typedef egui::rebar w;
            typedef egui::rebar::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
        }

        // scroll_bar
        {
            typedef egui::handle_events::scroll_bar::ev ev;
            typedef egui::ctrl::scroll_bar w;
            typedef egui::ctrl::scroll_bar::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
        }

        // slider
        {
            typedef egui::handle_events::slider::ev ev;
            typedef egui::slider w;
            typedef egui::slider::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
        }

        // spin_button
        {
            typedef egui::handle_events::spin_button::ev ev;
            typedef egui::spin_button w;
            typedef egui::spin_button::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
            ADD_EVENT( sel_change);
        }

        // status_bar
        {
            typedef egui::handle_events::status_bar::ev ev;
            typedef egui::status_bar w;
            typedef egui::status_bar::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
            ADD_EVENT( click);
        }

        // tab
        {
            typedef egui::handle_events::tab::ev ev;
            typedef egui::tab w;
            typedef egui::tab::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
            ADD_EVENT( click);
            ADD_EVENT( focus_change);
            ADD_EVENT( sel_change);
            ADD_EVENT( sel_changing);
        }

        // toolbar
        {
            typedef egui::handle_events::toolbar::ev ev;
            typedef egui::toolbar w;
            typedef egui::toolbar::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
        }

        // tooltip
        {
            typedef egui::handle_events::tooltip::ev ev;
            typedef egui::tooltip w;
            typedef egui::tooltip::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
        }

        // tree
        {
            typedef egui::handle_events::tree::ev ev;
            typedef egui::tree w;
            typedef egui::tree::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
            ADD_EVENT( single_expand);
            ADD_EVENT( sel_changing);
            ADD_EVENT( sel_changed);
            ADD_EVENT( item_expanding);
            ADD_EVENT( item_expanded);
            ADD_EVENT( click);
            ADD_EVENT( focus);
        }

        /*
        // xxx
        {
            typedef egui::handle_events::xxx::ev ev;
            typedef egui::xxx w;
            typedef egui::xxx::events_type we;
            window_events::event_handler_array & h = events[ window_info<w>() ].handlers;
            // ADD_EVENT( );
        }
        */


        egui::detail::event_manager::inst().add_call_on_event(coll);
        egui::detail::event_manager::inst().add_window_events(events);
    }
} // namespace detail_



namespace ev {








event_module_base::event_module_base() : already_inited(false) {
    // init_events should be forced by detail::initer construct
//    detail::init_events();
}

void event_module_base::add(converter_top* converter) {
    m_converters.push_back( converter_ptr(converter) );
}

/** 
    Initializes the event data - all the event's converters.

    Note:

    you can initialize your event converters in 2 ways:
    - in the constructor
    - in here (override this function)

    The advantage when doing it here is that you also know the WM_ windows message this event is for
    (while in the constructor, you don't know it yet)
*/
void event_module_base::init_event() {
}

void event_module_base::before_handle() {
    if ( already_inited)
        return;
    already_inited = true;
    init_event();
    BOOST_FOREACH(converter_ptr convert, m_converters)
    {
        convert->set_base(this);
        convert->init();
    }
}

void event_module_base::after_handle() {
    BOOST_FOREACH(converter_ptr convert, m_converters)
        convert->exit();
}


}}


// End of file
