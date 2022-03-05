// event_handler.hpp

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


#ifndef JT07022008_event_handler_HPP_DEFINED
#define JT07022008_event_handler_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <vector>

namespace egui {

/////////////////////////////////////////////////////////////
// allow calling an event handler
struct window_top;
namespace ev { struct base; }

namespace detail {
    struct func_base {
        virtual ~func_base() {}
        virtual void operator()(window_top & , egui::ev::base & event) = 0;
    };

    template<class event_type> struct event_func : func_base {
        typedef boost::function1<void,event_type&>  func;
        func m_f;
        event_func(func f) : m_f(f) {}

        virtual void operator()(window_top & , egui::ev::base & event) {
            event_type * e = dynamic_cast<event_type*>(&event);
            assert(e);
            m_f(*e);
        }
    };
}

struct event_handler_base {
    typedef boost::shared_ptr<detail::func_base> func;
    typedef std::vector<func> func_array;
    // note: there will be copying of event handlers
    // 
    // the derived class always inherits the base class event handlers
    // however, it does this by copy-ing them. If we have an event handler, for event X,
    // that is present in the base class and in the derived class, they must point to the same events!
    //
    // thus, we use a shared_ptr - to also minimize copying
    //
    // also, we need a shared_ptr since we might have something like this:
    // base->events += some_handler;
    // adding this handler should be visible in derived as well!
    typedef boost::shared_ptr<func_array> func_array_ptr;

    event_handler_base () ;
    event_handler_base(const event_handler_base & other);

    void operator()(window_top & , egui::ev::base & event) ;

protected:
    func_array_ptr m_funcs;
};


template<class event_type> struct event_handler : event_handler_base {
    typedef boost::function1<void,event_type&>  func;
    void operator +=(func f) {
        event_handler_base::func wrap( new detail::event_func<event_type>(f));
        event_handler_base::m_funcs->push_back( wrap );
    }
};



struct new_event_caller_base {
    virtual ~new_event_caller_base () {}
    virtual void call(window_top& w, egui::ev::base& evt) = 0;
};
typedef boost::shared_ptr<new_event_caller_base> new_event_caller_ptr;

template<class window, class holder, class event_type> struct new_event_caller : new_event_caller_base {
    typedef event_handler<event_type> holder::*member_data;
    member_data m_data;

    new_event_caller(member_data data) : m_data(data) {}
    virtual void call(window_top& w, egui::ev::base& evt) {
        window * real_wnd = dynamic_cast<window*>(&w);
        if ( !real_wnd)
            return;

        event_type * real_event = dynamic_cast<event_type*>(&evt);
        assert(real_event);
        holder & events = real_wnd->events;
        (events.*m_data)(*real_wnd, *real_event);
    }
};



struct non_intrusive_handler {
    virtual ~non_intrusive_handler() {}
    virtual void on_new_window_create(wnd<> w) = 0 ;
};
typedef boost::shared_ptr<non_intrusive_handler > non_intrusive_handler_ptr;


















#if 0
/* 
original version , generated a lot of code-bloat (aprox. 20Mb or more)
*/
template<class event_type> struct event_handler {
    typedef boost::function1<void,event_type&>  func;
    typedef std::vector<func> func_array;
    // note: there will be copying of event handlers
    // 
    // the derived class always inherits the base class event handlers
    // however, it does this by copy-ing them. If we have an event handler, for event X,
    // that is present in the base class and in the derived class, they must point to the same events!
    //
    // thus, we use a shared_ptr - to also minimize copying
    //
    // also, we need a shared_ptr since we might have something like this:
    // base->events += some_handler;
    // adding this handler should be visible in derived as well!
    typedef boost::shared_ptr<func_array> func_array_ptr;

    event_handler () : m_funcs(new func_array_ptr) {}

    void operator()(window_top & w, event_type& event) {
        for ( func_array::iterator b = m_funcs->begin(), e = m_funcs->end(); b != e; ++b) {
            (*b)(event);
            if ( event.handled == ev::handled_fully)
                return;
        }
    }

    void operator +=(func f) {
        m_funcs->push_back(f);
    }

    func_array_ptr m_funcs;
};
#endif

}

#endif

