// tooltip.cpp

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
#include "egui/controls/tooltip.hpp"

namespace egui { 
    
namespace types {

/** 
creates a tooltip area consisting of a full window
*/
tooltip_area::tooltip_area (const wnd<> & w) : rect(invalid_rect) {
    compute_from_handle( raw_hwnd(w) );
}    
/** 
creates a tooltip area consisting of a full window
*/
tooltip_area::tooltip_area(const window_top * w) : rect(invalid_rect) {
    compute_from_handle( raw_hwnd(w) );
}

/** 
(advanced) <br>
creates a tooltip area consisting of a full window

You specify both the parent, and the control window (they can even be the same).

@param parent - the window that will receive notifications
@param w - the window you're creating an area for
*/
tooltip_area::tooltip_area(const wnd<> & parent, const wnd<> & w) : rect(invalid_rect) {
    hwnd = raw_hwnd(parent);
    id = const_cast<void*>( raw_hwnd(w) );
}

// 
/**
    (advanced) <br>
    Specify a rectangular area within the given window

    @param w - the window (also, this window will receive notifications)
    @param id - unique ID (application-identifier for this tool). 
    @param r - the rectangle (within w), that the tooltip control will monitor

    @remarks
    Note that for id, I'm using an unsigned short, to make sure it first within a void*

*/
tooltip_area::tooltip_area(const wnd<> & w, unsigned short id_, const rectangle & r) : rect(r) {
    hwnd = raw_hwnd(w);
    id = (void*)(id_);
}
void tooltip_area::compute_from_handle(wnd_id_type h) {
    hwnd = ::GetParent( static_cast<HWND>( const_cast<void*>(h) ) );
    id = const_cast<void*>(hwnd);
}


}

namespace ctrl {


struct tooltip::impl {
    tooltip * self;

    impl(tooltip * self) : self(self) {
    }

    HWND raw_hwnd() const {
        return get_hwnd(self);
    }


    int get_tool_count() const { 
        return default_(); 
    }
    void set_active(const bool & val) {
    }

    int get_initial_delay_time() const { 
        return default_(); 
    }
    void set_initial_delay_time(const int & val) {
    }
    int get_popup_delay_time() const { 
        return default_(); 
    }
    void set_popup_delay_time(const int & val) {
    }
    int get_reshow_delay_time() const { 
        return default_(); 
    }
    void set_reshow_delay_time(const int & val) {
    }

    rectangle get_margins() const { 
        return default_(); 
    }
    void set_margins(const rectangle & val) {
    }
    int get_max_width() const { 
        return default_(); 
    }
    void set_max_width(const int & val) {
    }
    color get_bg_color() const { 
        return default_(); 
    }
    void set_bg_color(const color & val) {
    }
    color get_text_color() const { 
        return default_(); 
    }
    void set_text_color(const color & val) {
    }




    typedef types::size size_type;
    typedef tooltip::area area;


    string get_tip_text(area val) const {
        return default_();
    }
    void set_tip_text( area idx, const string & val) {
    }

    rectangle get_rect(area val) const {
        return default_();
    }
    void set_rect( area idx, const rectangle & val) {
    }


    size_type get_size(area val) const {
        return default_();
    }

};

#define self this
string tooltip:: class_name() { return GUI_STR("tooltips_class32"); }
types::int64  tooltip::default_style() { 
    types::int64 def_style = window_top::default_style();
    types::int64 style = WS_POPUP | TTS_ALWAYSTIP;
    types::int64 ex = 0;

    return  def_style | style | (ex << 32); 
}

tooltip::tooltip() : m_impl(new tooltip::impl(this) ) {
    detail::init_property( initial_delay_time, m_impl.get(), &impl::get_initial_delay_time, &impl::set_initial_delay_time);
    detail::init_property( popup_delay_time, m_impl.get(), &impl::get_popup_delay_time, &impl::set_popup_delay_time);
    detail::init_property( reshow_delay_time, m_impl.get(), &impl::get_reshow_delay_time, &impl::set_reshow_delay_time);
    detail::init_property( margins, m_impl.get(), &impl::get_margins, &impl::set_margins);
    detail::init_property( max_width, m_impl.get(), &impl::get_max_width, &impl::set_max_width);
    detail::init_property( bg_color, m_impl.get(), &impl::get_bg_color, &impl::set_bg_color);
    detail::init_property( text_color, m_impl.get(), &impl::get_text_color, &impl::set_text_color);
    detail::init_property( tool_count, m_impl.get(), &impl::get_tool_count);
    detail::init_property( tip_text, m_impl.get(), &impl::get_tip_text, &impl::set_tip_text);
    detail::init_property( rect, m_impl.get(), &impl::get_rect, &impl::set_rect);
    detail::init_property( size, m_impl.get(), &impl::get_size);
    detail::init_property( active, m_impl.get(), &impl::set_active);
}
tooltip::~tooltip() {
}





void tooltip::pop() { 
}
void tooltip::add_tool( area h) { 
}
void tooltip::del_tool( area h) { 
}

void tooltip::relay_event(const egui::ev::base & event) { 
    // MSG msg;
}

void tooltip::title(const string & str, types::tooltip_title::type t ) { 
}
void tooltip::update() { 
}


}}

// End of file
