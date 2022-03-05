// wrap_events.hpp

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


#ifndef JT07022008_wrap_events_HPP_DEFINED
#define JT07022008_wrap_events_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/bind.hpp>

namespace egui { namespace detail {

///////////////////////////////////////////////////////////////////////////////////////////
// Uniquely identify window classes



namespace window_id {
    struct info_base : typeinfo_holder {
        info_base(const std::type_info & val) : typeinfo_holder(val) {}

        virtual bool matches_wnd(const wnd<> & w) const = 0;
    };

    template<class window_type> struct info : info_base {
        info() : info_base( typeid(window_type) ) {}

        virtual bool matches_wnd(const wnd<> & w) const {
            return try_wnd_cast<window_type>(w);
        }
    };
}

/** uniquely identify a window class */
struct window_type_info {
    template<class w> window_type_info( const tag<w> &) : m_window_info(new window_id::info<w> ) {}
    window_type_info() : m_window_info(new window_id::info<window_top> ) {}

    bool operator ==(const window_type_info & other) const {
        return *m_window_info == *other.m_window_info;
    }
    bool operator !=(const window_type_info & other) const {
        return *m_window_info != *other.m_window_info;
    }
    bool operator <(const window_type_info & other) const {
        return *m_window_info < *other.m_window_info;
    }
    
    bool matches_wnd(const wnd<> & w) const {
        return m_window_info->matches_wnd(w);
    }
private:
    boost::shared_ptr<window_id::info_base> m_window_info;
};

/** easy creation of a window type info */
template<class w> inline window_type_info window_info() { return tag<w>() ; }







/////////////////////////////////////////////////////////////
// allow calling an event handler


struct call_event_handler_base {
    virtual ~call_event_handler_base () {}
    virtual void call( window_top * w, ::egui::ev::base & event) = 0;
};
typedef boost::shared_ptr<call_event_handler_base> call_event_handler_ptr;

template<class window, class event_type> struct call_event_handler : call_event_handler_base {
    typedef event_handler<event_type> member_type;
    typedef typename window::events_type window_events_type;

    typedef member_type window_events_type::* member_data;
    member_data m_data;

    call_event_handler (member_data data) : m_data(data) {}

    virtual void call( window_top * w, ::egui::ev::base & event) {
        window * real_wnd = dynamic_cast<window*>(w);

        event_type * real_event = dynamic_cast<event_type*>(&event);
        if ( !real_event) {
            // wrong event passsed to our function!
            assert(false);
            return;
        }

        if ( real_wnd) {
            window_events_type & window_events = real_wnd->events;
            (window_events.*m_data)( *real_wnd, *real_event);
        }
        else {
            // this can be an event that's been reflected
            w->events.on_notify( *w, *real_event);
        }
    }
};

template<class window, class window_events, class event_type> inline call_event_handler_ptr event_caller( event_handler<event_type> window_events::* data) {
    return call_event_handler_ptr ( new call_event_handler<window,event_type>(data) );
}

// for an event -> it knows what event handler to call
typedef std::map< typeinfo_holder, call_event_handler_ptr> event_call_coll;



///////////////////////////////////////////////////////////////////////////////////////////
// For a window class, register its default handlers (the virtual functions)

struct add_default_event_handler_base {
    virtual ~add_default_event_handler_base () {}
    virtual void add_event_handler(window_top * w) = 0;
};
typedef boost::shared_ptr<add_default_event_handler_base> add_default_event_handler_ptr;


template<class window, class event_type> struct add_default_event_handler : add_default_event_handler_base {
    typedef event_handler<event_type> member_type;
    typedef typename window::events_type window_events_type;

    typedef member_type window_events_type::* member_data;
    typedef void (window::*window_member_func)(event_type&);

    member_data m_data;
    window_member_func m_func;

    add_default_event_handler(member_data data, window_member_func func) : m_data(data), m_func(func) {}

    virtual void add_event_handler( window_top * w) {
        window * real_wnd = dynamic_cast<window*>(w);
        if ( !real_wnd) {
            // add_default_event_handler contains wrong info!
            assert(false);
            return;
        }

        window_events_type & window_events = real_wnd->events;

        using namespace boost;
        function1<void,event_type&> wrap = bind( mem_fn(m_func), real_wnd, _1);
        (window_events.*m_data) += wrap;

    }
};


template<class window, class event_type, class window_event, class handler> 
inline add_default_event_handler_ptr member_func_as_event_handler( 
        void (window::*func)(event_type&), 
        handler window_event::* data ) {
    return add_default_event_handler_ptr ( new add_default_event_handler<window,event_type>(data, func) );
}




///////////////////////////////////////////////////////////////////////////////////////////
// Know what event to generate when a certain WM_ message occurs

struct create_event_base {
    typedef boost::shared_ptr< ::egui::ev::base > event_ptr;
    virtual ~create_event_base() {}
    virtual event_ptr create() const = 0;
};

template<class type> struct create_event : create_event_base {
    typedef create_event_base::event_ptr event_ptr;
    virtual event_ptr create() const { return event_ptr(new type); }
};

struct window_events {
    typedef boost::shared_ptr<create_event_base> creator;
    typedef std::map<long , creator> creator_coll;
    typedef std::vector<add_default_event_handler_ptr> event_handler_array;

    creator_coll events;
    creator_coll notifications;

    event_handler_array handlers;
};

template<class e> inline window_events::creator event_info() { 
    create_event_base * p = new create_event<e>;
    return window_events::creator(p) ; 
}

///////////////////////////////////////////////////////////////////////////////////////////
// keep thy events

// manages all events - for all window types
typedef std::map< window_type_info, window_events> window_event_coll;


}}

#endif

