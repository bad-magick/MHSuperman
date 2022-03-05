// wnd.hpp

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


#ifndef JT07022008_wnd_HPP_DEFINED
#define JT07022008_wnd_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/shared_ptr.hpp>
#include "egui/core/detail/exception.hpp"

#include "egui/core/detail/handle_event_base.hpp"

#include "egui/core/detail/window_base.hpp"
#include "egui/core/detail/control.hpp"
#include "egui/core/detail/new_del.hpp"


namespace egui {
struct form;

namespace detail {
    struct window_manager;
    struct event_manager;

    wnd<> get_window(wnd_id_type h);

    wnd_id_type create_on_the_screen_window( create_window_base * creator, const string & class_name, const wnd_init& init, int form_id, form* );
    wnd_id_type create_on_the_screen_window( create_window_base * creator, const string & class_name, const wnd_init& init, int , void* );
}

template<class dest, class src> inline wnd<dest> try_wnd_cast(const wnd<src> & from) ;

// allow any wnd<some_type> to be converted to wnd<>
template<class window, class full_type = wnd<window_top> > struct wnd_base {
    operator full_type () const {
        const wnd<window> & w = static_cast< const wnd<window>& >(*this);
        return full_type( w.m_window_base); 
    }
};
template<> struct wnd_base<window_top, wnd<window_top> > {};

/** 
    @brief Provides @em indirect access to on-the-screen window objects.

    In case you have a wnd<> object, in order to access the C++ window object's functions,
    always use '->':

    \code
    wnd<> w = ...;
    w->some_method(...);
    bool shown = w->visible;
    w->enabled = false; // disable this window
    \endcode

*/
template<class window > struct wnd : wnd_base<window> {
    template<class other> friend struct wnd;
    template<class a, class b> friend struct wnd_base;

    /** 
        create window with new_ : 

        wnd<> w = new_<form>(some_args);
        // or
        wnd<form> w = new_(some_args);
    */
    template<
        class new_window_type,
        class p1, 
        class p2, 
        class p3, 
        class p4, 
        class p5, 
        class p6, 
        class p7, 
        class p8, 
        class p9, 
        class p10> 
    wnd(const new_t<new_window_type,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10> & args) {
        create_new_window(args, tag<new_window_type>() );
    }

private:
    template<
        class new_window_type,
        class p1, 
        class p2, 
        class p3, 
        class p4, 
        class p5, 
        class p6, 
        class p7, 
        class p8, 
        class p9, 
        class p10> 
    void create_new_window(const new_t<new_window_type,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10> & args, tag<window_base> )
    {
        // create based on 'window'
        args.init.default_style( window::default_style() );
        create_window< window_instance_t<window> , new_t<new_window_type,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10> > creator(args);
        wnd_id_type h = detail::create_on_the_screen_window( 
            &creator, window::class_name(), args.init, window::form_id(), (window*)0 );
        m_window_base = detail::get_window(h).m_window_base;
        m_window = dynamic_cast<window*>( m_window_base.get() );
    }

    template<
        class new_window_type,
        class p1, 
        class p2, 
        class p3, 
        class p4, 
        class p5, 
        class p6, 
        class p7, 
        class p8, 
        class p9, 
        class p10> 
    void create_new_window(const new_t<new_window_type,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10> & args, ... )
    {
        // create based on 'new_window_type'
        args.init.default_style( new_window_type::default_style() );
        create_window< window_instance_t<new_window_type> , new_t<new_window_type,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10> > creator(args);
        wnd_id_type h = detail::create_on_the_screen_window( 
            &creator, new_window_type::class_name(), args.init, new_window_type::form_id(), (new_window_type*)0 );
        m_window_base = detail::get_window(h).m_window_base;
        m_window = dynamic_cast<window*>( m_window_base.get() );
    }





    typedef boost::shared_ptr<window_top> wnd_ptr;
    wnd(wnd_ptr ptr) : m_window_base(ptr) {
        m_window = dynamic_cast<window*>( ptr.get() );
    }
    friend struct egui::detail::window_manager;

public:
    /** 
        default constructor - construct a null window
    */
    wnd() : m_window(0) {}

    // automatic conversion of window to wnd<>
    wnd(const window* w) {
        wnd_id_type h = w ? w->id->unique : 0;
        m_window_base = egui::detail::get_window(h).m_window_base;
        m_window = dynamic_cast<window*>( m_window_base.get() );
        if ( h)
            // we already had a pointer to this window type passed at construction
            assert(m_window);
    }

    window* operator->() {
        if ( !is_valid() )
            throw exception( GUI_STR("invalid window"));
        return m_window;
    }
    const window* operator->() const {
        if ( !is_valid() )
            throw exception( GUI_STR("invalid window"));
        return m_window;
    }

    /**
        conversion to bool. If this is non-null, it returns the equivalent of true.
        Otherwise, it returns the equivalent of false.

        You can use it in the if-assign idiom
    */
    operator bool() const { return is_valid(); }

    bool operator==(const wnd & other) const { return m_window == other.m_window; }
    bool operator!=(const wnd & other) const { return m_window != other.m_window; }
    // so that you can use wnd<> as keys in a map
    bool operator<(const wnd & other) const { return m_window < other.m_window; }

private:
    bool is_valid() const {
        if ( m_window)
            return m_window->is_valid();
        else
            return 0;
    }
private:
    // pointer to window base
    wnd_ptr m_window_base;
    // dynamic cast to the window you need
    window * m_window;

    friend struct egui::detail::event_manager;
    template<class dest, class src> friend inline wnd<dest> try_wnd_cast(const wnd<src> & from) ;

};

template<class window = window_base> struct weak_wnd {
    // FIXME
};

namespace {
    /// special null-pointer value
    wnd<> null;
}




///////////////////////////////////////////////
// Casting
template<class dest, class src> inline wnd<dest> try_wnd_cast(const wnd<src> & from) {
    const src* s = from.m_window;
    const dest* d = dynamic_cast<const dest*>(s);
    if ( d)
        return d;
    else
        return wnd<dest>();
}

template<class dest, class src> inline wnd<dest> wnd_cast(const wnd<src> & from) {
    wnd<dest> d = try_wnd_cast<dest>(from);
    if ( d)
        return d;
    else
        throw exception(GUI_STR("wnd_cast failed") );
}

}

#include "egui/core/detail/event.hpp"
#include "egui/core/detail/msg_box.hpp"
#include "egui/core/detail/form.hpp"

#ifndef BUILDING_EGUI
#include "egui/events/window_top.hpp"
#endif

#endif

