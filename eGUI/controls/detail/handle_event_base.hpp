// controls/handle_event_base.hpp

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


#ifndef JT07022008_handle_event_base_HPP_DEFINED_controls
#define JT07022008_handle_event_base_HPP_DEFINED_controls

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#include "egui/core/detail/handle_event_base.hpp"

namespace egui { namespace handle_events {

    struct animate_ctrl {
        struct ev : window_top::ev {
            struct start;
            struct stop;
        };

        // handlers
        virtual void on_start(ev::start&) {}
        virtual void on_stop(ev::stop&) {}

        struct events_type : window_top::events_type {
            event_handler< ev::start > on_start;
            event_handler< ev::stop > on_stop;
        } events;
    };

    struct button {
        struct ev : window_top::ev {
            struct clicked;
            struct focus;

        };

        // handlers
        virtual void on_clicked(ev::clicked&) {}
        virtual void on_focus(ev::focus&) {}

        struct events_type : window_top::events_type {
            event_handler< ev::clicked > on_clicked;
            event_handler< ev::focus > on_focus;
        } events;
    };

    struct check_box {
        struct ev : button::ev {

        };

        // handlers

        struct events_type : button::events_type {
        } events;
    };

    struct combo_box {
        struct ev : window_top::ev {
            struct sel_change;
            struct focus;
            struct edit_change;
            struct edit_update;
            struct drop_down;
        };

        // handlers
        virtual void on_sel_change(ev::sel_change&) {}
        virtual void on_focus(ev::focus&) {}
        virtual void on_edit_change(ev::edit_change&) {}
        virtual void on_edit_update(ev::edit_update&) {}
        virtual void on_drop_down(ev::drop_down&) {}

        struct events_type : window_top::events_type {
            event_handler< ev::sel_change > on_sel_change;
            event_handler< ev::focus > on_focus;
            event_handler< ev::edit_change > on_edit_change;
            event_handler< ev::edit_update > on_edit_update;
            event_handler< ev::drop_down > on_drop_down;
        } events;
    };

    struct date_time {
        struct ev : window_top::ev {
            struct sel_change;
            struct drop_down;
            struct focus;
        };

        // handlers
        virtual void on_sel_change(ev::sel_change&) {}
        virtual void on_drop_down(ev::drop_down&) {}
        virtual void on_focus(ev::focus&) {}

        struct events_type : window_top::events_type {
            event_handler< ev::sel_change > on_sel_change;
            event_handler< ev::drop_down > on_drop_down;
            event_handler< ev::focus > on_focus;
        } events;
    };

    struct edit {
        struct ev : window_top::ev {
            struct focus;
            struct change;
            struct update;
            struct max_text;
        };

        // handlers
        virtual void on_focus(ev::focus&) {}
        virtual void on_change(ev::change&) {}
        virtual void on_update(ev::update&) {}
        virtual void on_max_text(ev::max_text&) {}

        struct events_type : window_top::events_type {
            event_handler< ev::focus > on_focus;
            event_handler< ev::change > on_change;
            event_handler< ev::update > on_update;
            event_handler< ev::max_text > on_max_text;
        } events;
    };

    struct group_box {
        struct ev : window_top::ev {
        };

        // handlers
    };

    struct label {
        struct ev : window_top::ev {
        };

        // handlers

    };

    struct list {
        struct ev : window_top::ev {
            struct item_changing;
            struct item_changed;
            struct column_click;
            struct drag;
            struct state_changed;
            struct hot_track;
            struct click;
            struct focus;
        };

        // handlers
        virtual void on_item_changing(ev::item_changing&) {}
        virtual void on_item_changed(ev::item_changed&) {}
        virtual void on_column_click(ev::column_click&) {}
        virtual void on_drag(ev::drag&) {}
        virtual void on_state_changed(ev::state_changed&) {}
        virtual void on_hot_track(ev::hot_track&) {}
        virtual void on_click(ev::click&) {}
        virtual void on_focus(ev::focus&) {}

        struct events_type : window_top::events_type {
            event_handler< ev::item_changing > on_item_changing;
            event_handler< ev::item_changed > on_item_changed;
            event_handler< ev::column_click > on_column_click;
            event_handler< ev::drag > on_drag;
            event_handler< ev::state_changed > on_state_changed;
            event_handler< ev::hot_track > on_hot_track;
            event_handler< ev::click > on_click;
            event_handler< ev::focus > on_focus;
        } events;
    };

    struct list_box {
        struct ev : window_top::ev {
            struct sel_change;
            struct sel_cancel;
            struct focus;
        };

        // handlers
        virtual void on_sel_change(ev::sel_change&) {}
        virtual void on_sel_cancel(ev::sel_cancel&) {}
        virtual void on_focus(ev::focus&) {}

        struct events_type : window_top::events_type {
            event_handler< ev::sel_change > on_sel_change;
            event_handler< ev::sel_cancel > on_sel_cancel;
            event_handler< ev::focus > on_focus;
        } events;
    };

    struct list_header {
        struct ev : window_top::ev {
            struct drag;
            struct item_changing;
            struct item_changed;
            struct item_click;
            struct divider_dbl_click;
            struct right_click;
        };

        // handlers
        virtual void on_drag(ev::drag&) {}
        virtual void on_item_changing(ev::item_changing&) {}
        virtual void on_item_changed(ev::item_changed&) {}
        virtual void on_item_click(ev::item_click&) {}
        virtual void on_divider_dbl_click(ev::divider_dbl_click&) {}
        virtual void on_right_click(ev::right_click&) {}

        struct events_type : window_top::events_type {
            event_handler< ev::drag > on_drag;
            event_handler< ev::item_changing > on_item_changing;
            event_handler< ev::item_changed > on_item_changed;
            event_handler< ev::item_click > on_item_click;
            event_handler< ev::divider_dbl_click > on_divider_dbl_click;
            event_handler< ev::right_click > on_right_click;
        } events;
    };

    struct month_cal {
        struct ev : window_top::ev {
            struct sel_change;
        };

        // handlers
        virtual void on_sel_change(ev::sel_change&) {}

        struct events_type : window_top::events_type {
            event_handler< ev::sel_change > on_sel_change;
        } events;
    };

    struct multi_edit {
        struct ev : edit::ev {
        };

        // handlers
    };

    struct progress_bar {
        struct ev : window_top::ev {
        };

        // handlers
    };

    struct radio_button {
        struct ev : button::ev {
        };

        // handlers
    };

    struct rebar {
        struct ev : window_top::ev {
        };

        // handlers
    };

    struct scroll_bar {
        struct ev : window_top::ev {
        };

        // handlers
    };

    struct slider {
        struct ev : window_top::ev {
        };

        // handlers
    };

    struct spin_button {
        struct ev : window_top::ev {
            struct sel_change;
        };

        // handlers
        virtual void on_sel_change(ev::sel_change&) {}

        struct events_type : window_top::events_type {
            event_handler< ev::sel_change > on_sel_change;
        } events;
    };

    struct status_bar {
        struct ev : window_top::ev {
            struct click;
        };

        // handlers
        virtual void on_click(ev::click&) {}

        struct events_type : window_top::events_type {
            event_handler< ev::click > on_click;
        } events;
    };

    struct tab {
        struct ev : window_top::ev {
            struct click;
            struct focus_change;
            struct sel_change;
            struct sel_changing;

        };

        // handlers
        virtual void on_click(ev::click&) {}
        virtual void on_focus_change(ev::focus_change&) {}
        virtual void on_sel_change(ev::sel_change&) {}
        virtual void on_sel_changing(ev::sel_changing&) {}

        struct events_type : window_top::events_type {
            event_handler< ev::click > on_click;
            event_handler< ev::focus_change > on_focus_change;
            event_handler< ev::sel_change > on_sel_change;
            event_handler< ev::sel_changing > on_sel_changing;
        } events;
    };

    struct tab_form {
        struct ev : tab::ev {
        };

        // handlers

    };

    struct toolbar {
        struct ev : window_top::ev {
        };

        // handlers

    };

    struct tooltip {
        struct ev : window_top::ev {
        };

        // handlers

    };

    struct tree {
        struct ev : window_top::ev {
            struct single_expand;
            struct sel_changing;
            struct sel_changed;
            struct item_expanding;
            struct item_expanded;
            struct click;
            struct focus;
        };

        // handlers
        virtual void on_single_expand(ev::single_expand&) {}
        virtual void on_sel_changing(ev::sel_changing&) {}
        virtual void on_sel_changed(ev::sel_changed&) {}
        virtual void on_item_expanding(ev::item_expanding&) {}
        virtual void on_item_expanded(ev::item_expanded&) {}
        virtual void on_click(ev::click&) {}
        virtual void on_focus(ev::focus&) {}

        struct events_type : window_top::events_type {
            event_handler< ev::single_expand > on_single_expand;
            event_handler< ev::sel_changing > on_sel_changing;
            event_handler< ev::sel_changed > on_sel_changed;
            event_handler< ev::item_expanding > on_item_expanding;
            event_handler< ev::item_expanded > on_item_expanded;
            event_handler< ev::click > on_click;
            event_handler< ev::focus > on_focus;
        } events;
    };


}}

#endif

