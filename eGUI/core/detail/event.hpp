// event.hpp

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


#ifndef JT07022008_event_HPP_DEFINED
#define JT07022008_event_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/enable_shared_from_this.hpp> 

namespace egui { 

namespace ev { 
    struct base ; 
    namespace converters {
        struct access_win32_data;
    }
}

namespace detail { 
    struct event_manager; 
    void set_windows_msg(ev::base& event, unsigned long wm);
    unsigned long get_windows_msg(const ev::base & event);
}

namespace ev {

typedef enum event_handled_type {
    // the event was partially handled - at least one handler was called, but more can be called 
    handled_partially,
    // the event was fully handled - no more handlers will be called
    handled_fully
};

/** base class for all events
*/
struct base {
    virtual ~base() {}

    virtual void before_handle();
    virtual void after_handle();

protected:
    base() ;
public:

    /// the window the event is for (for instance, you could get a reflected message - thus, the destination is not your window)
    wnd<> destination;

    /// the one who sent this event
    wnd<> sender;

    /// was this handled
    event_handled_type handled;

    /// if true, default Windows processing should occur as well
    /// for most events, this is set to false by default
    bool do_default_processing;

protected:
    // just in case the event needs to yield a result (useful mostly for forms)
    types::int64 result;

private:
    friend struct egui::detail::event_manager;
    friend void detail::set_windows_msg(ev::base& event, unsigned long wm);
    friend unsigned long detail::get_windows_msg(const ev::base & event);
    friend struct ::egui::ev::converters::access_win32_data;

    /** (Advanced) this is used internally - to know what WM_ windows message we're handling

    You normally don't need this - unless you want to catch some custom Win32 events 
    */
    unsigned long windows_msg;
    /** (Advanced) this is used internally - to know the WPARAM of the message we're handling

    You normally don't need this - unless you want to catch some custom Win32 events 
    */
    types::int64 wparam;
    /**  this is used internally - to know the LPARAM of the emessage we're handling

    You normally don't need this - unless you want to catch some custom Win32 events 
    */
    types::int64 lparam;
};

/** 
    if an event derives directly or indirectly from this, when it's received, it's automatically
    sent to the destination's parent as well
*/
struct reflectable : base {
};

/** 
    destroy event
*/
struct destroy : base {
    destroy( wnd<> w = wnd<>() );

    // what do destroy - if null - any window (when waiting for something to be destroyed)
    wnd<> to_destroy;
};

struct new_event_base : reflectable, boost::enable_shared_from_this<new_event_base> {
    new_event_base() : already_sent(false) {}
private:
    friend struct egui::window_top;
    // we use this to see if an event has already been sent (and at this time it's forwarded)
    bool already_sent;
};


}

template<class event_type> struct new_event : ev::new_event_base {
};

}

#endif

