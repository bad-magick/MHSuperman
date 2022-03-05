// control_base.cpp

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
#include <iostream>
#include "egui/core/detail/window_manager.hpp"
#include "egui/controls/detail/fwd.hpp"
#include "egui/controls/all.hpp"



namespace egui { 

namespace {
    
    window_top * create_control_from_handle_func(wnd_id_type h) {
#if 1
        HWND hwnd = static_cast<HWND>(const_cast<void*>(h));
        string class_name = detail::window_manager::inst().lo_class_name( hwnd);
        DWORD style = (DWORD)::GetWindowLong(hwnd, GWL_STYLE);
        DWORD ex_style = (DWORD)::GetWindowLong(hwnd, GWL_EXSTYLE);

        if ( class_name == button::class_name() )
        {
            int bs = style & 0xF;
            if ( bs == BS_CHECKBOX || bs == BS_AUTOCHECKBOX || bs == BS_3STATE || bs == BS_AUTO3STATE)
                return new window_instance_t< check_box >(h);
            if ( bs == BS_RADIOBUTTON || bs == BS_AUTORADIOBUTTON)
                return new window_instance_t< radio_button >(h);
            if ( bs == BS_GROUPBOX)
                return new window_instance_t< group_box >(h);
            return new window_instance_t< button >(h);
        }
    
        if ( class_name == edit::class_name())
        {
            if ( style & ES_MULTILINE)
                return new window_instance_t< multi_edit >(h);
            else
                return new window_instance_t< edit >(h);
        }

        if ( class_name == tab::class_name())
        {
            if ( style & types::style::tab_stop)
                return new window_instance_t< tab_form >(h);
            else
                return new window_instance_t< tab >(h);
        }

        if ( class_name == animate_ctrl::class_name())
            return new window_instance_t< animate_ctrl >(h);
        if ( class_name == combo_box::class_name())
            return new window_instance_t< combo_box >(h);
        if ( class_name == date_time::class_name())
            return new window_instance_t< date_time >(h);
        if ( class_name == label::class_name())
            return new window_instance_t< label >(h);
        if ( class_name == list::class_name())
            return new window_instance_t< list >(h);
        if ( class_name == list_box::class_name())
            return new window_instance_t< list_box >(h);
        if ( class_name == list_header::class_name())
            return new window_instance_t< list_header >(h);
        if ( class_name == month_cal::class_name())
            return new window_instance_t< month_cal >(h);
        if ( class_name == progress_bar::class_name())
            return new window_instance_t< progress_bar >(h);
        if ( class_name == rebar::class_name())
            return new window_instance_t< rebar >(h);
        if ( class_name == scroll_bar::class_name())
            return new window_instance_t< scroll_bar >(h);
        if ( class_name == slider::class_name())
            return new window_instance_t< slider >(h);
        if ( class_name == spin_button::class_name())
            return new window_instance_t< spin_button >(h);
        if ( class_name == status_bar::class_name())
            return new window_instance_t< status_bar >(h);
        if ( class_name == toolbar::class_name())
            return new window_instance_t< toolbar >(h);
        if ( class_name == tooltip::class_name())
            return new window_instance_t< tooltip >(h);
        if ( class_name == tree::class_name())
            return new window_instance_t< tree >(h);
#endif
        return 0;
    }


}

control_base::control_base() {
}
}

namespace detail_ {
    void init_ctrl_controls() {
        static bool initialized = false;
        if ( initialized)
            return;
        initialized = true;
        egui::detail::window_manager::inst().add_create_window_from_handle_func(egui::create_control_from_handle_func);
    }
}

// End of file
