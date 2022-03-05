// window_base.hpp

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


#ifndef JT07022008_window_base_HPP_DEFINED
#define JT07022008_window_base_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/core/detail/property.hpp"
#include <vector>
#include "egui/core/detail/handle_event_base.hpp"

namespace egui {

#ifdef BUILDING_EGUI
namespace detail { 
    struct window_manager; 
    struct event_manager;
}
#endif

namespace ev {
    struct new_event_base;
}

namespace types {
    /** how can a window be shown? */
    struct shown {
        enum type {
            maximize, normally, minimize
        };
    };

    /** represents the ID of a unique window */
    struct id {
        id(const void* unique) : unique(unique) {}
        const void * unique;
    };

    /** types of scroll bars */
    struct scroll_bar_type {
        enum type {
            horiz , vert, ctrl
        };
    };

    struct capture {
        enum type {
            mouse = 1, keyboard = 2
        };
    };

    struct style {
        //////////////////////////////////////////////////
        // Style

        /// a window that has a thin-line border.
        static const int64    border           = 0x00800000L; 
        /// a window that has a title bar 
        static const int64    caption          = 0x00C00000L; 
        /// a child window. A window with this style cannot have a menu bar; cannot be used with the popup style
        static const int64    child            = 0x40000000L; 
        /// a pop-up window - a popup window captures all input, and does not allow other windows to become active
        ///
        static const int64    popup            = 0x80000000L;
        /// Excludes the area occupied by child windows when drawing occurs within the parent window
        static const int64    clip_children    = 0x02000000L;  
        /// Clips child windows relative to each other; that is, when a particular child window receives a paint message, 
        /// the clip_siblings style clips all other overlapping child windows out of the region of the child window to be updated. 
        /// If clip_siblings is not specified and child windows overlap, it is possible, when drawing within the client area of a 
        /// child window, to draw within the client area of a neighboring child window
        static const int64    clip_siblings    = 0x04000000L; 
        /// if true, the window cannot receive user input
        static const int64    disabled          = 0x08000000L; 
        /// Specifies the first control of a group of controls
        static const int64    group            = 0x00020000L; 
        /// has a horizontal scroll bar.
        static const int64    horiz_scroll     = 0x00100000L; 
        /// a window that has a maximize button
        static const int64    maximize_box         = 0x00010000L; 
        /// a window that has a minimize button
        static const int64    minimize_box         = 0x00020000L; 
        /// window that has a sizing border (a thick frame) . 
        static const int64    thick_frame         = 0x00040000L; 
        /// Specifies a control that can receive the keyboard focus when the user presses the TAB key
        static const int64    tab_stop         = 0x00010000L; 
        /// window is visible
        static const int64    visible          = 0x10000000L; 
        /// a window that has a vertical scroll bar.
        static const int64    vert_scroll      = 0x00200000L;

        //////////////////////////////////////////////////
        // Extended styles

        /// Specifies that a window created with this style accepts drag-and-drop files. 
        static const int64 accept_files        = ((int64)0x00000010L << 32);
        /// Forces a top-level window onto the taskbar when the window is visible
        static const int64 app_window          = ((int64)0x00040000L << 32);
        /// Specifies that a window has a 3D look — that is << 32); a border with a sunken edge
        static const int64 client_edge         = ((int64)0x00000200L << 32);
        /// Includes a question mark in the title bar of the window. When the user clicks the question mark; the cursor changes to a question mark with a pointer. 
        static const int64 context_help        = ((int64)0x00000400L << 32);
        /// Allows the user to navigate among the child windows of the window by using the TAB key.
        static const int64 control_parent      = ((int64)0x00010000L << 32);
        /// Designates a window with a double border that may (optionally) be created with a title bar 
        static const int64 dlg_modal_frame     = ((int64)0x00000001L << 32);
        /// Places a vertical scroll bar to the left of the client area. 
        static const int64 left_scroll         = ((int64)0x00004000L << 32);
        /// Gives a window generic right-aligned properties. This depends on the window class
        static const int64 right_aligned       = ((int64)0x00001000L << 32);
        /// Creates a window with a three-dimensional border style intended to be used for items that do not accept user input
        static const int64 static_edge         = ((int64)0x00020000L << 32);
        /// Creates a tool window << 32); which is a window intended to be used as a floating toolbar. A tool window has a title bar that is shorter than a normal title bar << 32); and the window title is drawn using a smaller font. A tool window does not appear in the task bar or in the window that appears when the user presses ALT+TAB.
        static const int64 tool_window         = ((int64)0x00000080L << 32);
        /// Specifies that a window created with this style should be placed above all nontopmost windows and stay above them even when the window is deactivated
        static const int64 top_most            = ((int64)0x00000008L << 32);
        /// Specifies that a window created with this style is to be transparent. That is , any windows that are beneath the window are not obscured by the window
        static const int64 transparent         = ((int64)0x00000020L << 32);
        /// Specifies that a window has a border with a raised edge. 
        static const int64 window_edge         = ((int64)0x00000100L << 32);
    };


    struct scroll_info {
        scroll_info() : min_pos(0), max_pos(0), page_size(0), pos(0), track_pos(0) {}
        int min_pos;
        int max_pos;
        int page_size;
        int pos;
        int track_pos;

    };
}


/** 
    @brief Easy way to pass common args when constructing windows

    Example:

    wnd<> w = new_<form>( wnd_init("my form").rectangle(0,0,100,100));
*/
struct wnd_init {
    wnd_init() ;
    wnd_init(types::int64 style) ;
    wnd_init(const rectangle & r) ;
    wnd_init(const string & text) ;
    wnd_init(const char_ * text) ;
    wnd_init(const wnd<> & parent) ;
    wnd_init(const window_top * parent) ;

    wnd_init& style(types::int64 s) ;
    wnd_init& text(const string& t) ;
    wnd_init& rect(const rectangle & r);
    wnd_init& rect(int x, int y, int w, int h);
    wnd_init& rect(point p, size s) ;
    wnd_init& parent(const wnd<> & parent);

    void default_style(types::int64 def) const;

    bool m_style_set;
    bool m_text_set;
    bool m_rect_set;
    bool m_parent_set;

    wnd_id_type m_parent;
    mutable types::int64 m_style;
    string m_text;
    rectangle m_rect;
};


/** 
    @brief Base class for all win32gui (and your) window classes.

    Every window that exists on screen provides (at least) this functionality.
    
*/
struct window_top : handle_events::window_top {
protected:
    window_top( wnd_id_type hwnd = 0, const wnd_init & init = wnd_init() ) ;

public:
    virtual ~window_top();
    bool is_valid() const;

    virtual void on_create() {}
    virtual void on_destroy() {}
    virtual void on_initialize();

    static string class_name();
    static int form_id() { return 0; }
    static types::int64 default_style() ;

    virtual bool can_close() const;


private:
    void do_on_any_event(egui::ev::base & event_arg ) ;
public:
    virtual void on_any_event_before(egui::ev::base & /* event_arg */) ;
    virtual void on_any_event_after(egui::ev::base & /* event_arg */) ;
    
    typedef boost::function1<void, egui::ev::base& > on_any_event_func;
    void register_on_any_event_handler(on_any_event_func func);

    /** waits for a certain event to be sent to this window
        Example:

        w->wait_for( ev::destroy() );
    */
    void wait_for( const egui::ev::base & to_wait_for);

    /** 
    Sets a timer for this window. At the @c elapse millisecs, this window
    will receive the timer event, with the id set to @c event_id.
    */
    void set_timer(int event_id, unsigned elapse);
    /** 
    Kills the timer having this ID.
    */
    void kill_timer(int event_id);

    /// scrolls the window to that point
    void do_scroll(size scroll_size);

    /** 
    Brings this window to top of the Z order.
    */
    void bring_to_top();

    /** 
    Returns the child at the given point, or @c null if there's no child at that point. <br>
    The point is in client coordinates relative to your window.
    */
    wnd<> child_from_point(point pnt) const;
    /**
    Flashes the window - one time. <br>
    If invert is true, it will show the window "flashed".
    If invert is false, it will show the window normally.

    To implement flashing (multiple times), you should implement a timer,
    and repeatidly call flash.
    */
    void flash(bool invert);


    /**
    Forces a window to be redrawn
    */
    void do_redraw();
    /**
    Activates this window (but not if your application is in the background). 
    This window must be created by your thread.
    */
    void set_foreground();

private:
    void send_new_event(egui::ev::new_event_base& evt);
public:
    /** sends an event to this window. The event must derive from new_event<> class.
    */
    template<class event_type> void send_event(const event_type & evt) {
        (egui::ev::new_event_base & )evt; // make sure it's a custom event
        boost::shared_ptr<event_type> copy;
        if ( evt.already_sent)
            // this event has already been sent - right now, we're forwarding it
            copy = boost::dynamic_pointer_cast<event_type>( const_cast<event_type&>(evt).shared_from_this() );
        else {
            copy = boost::shared_ptr<event_type>( new event_type(evt));
            copy->already_sent = true;
        }
        send_new_event(*copy);
    }

private:
    static void register_event_handler_ptr(const std::type_info & event_type, new_event_caller_ptr caller);
    static void add_non_intrusive_handler_ptr(non_intrusive_handler_ptr p);
public:
    /** Registers an event handler for a custom event class (one that derives from new_event<>).
    */
    template<class window,class holder, class event> static void register_event_handler(event_handler<event> holder::*data) {        
        new_event_caller_ptr caller( new new_event_caller<window,holder,event>(data) );
        register_event_handler_ptr(typeid(event), caller);
    }
    /** adds a non-intrusive event handler.
    */
    template<class handler> static void add_non_intrusive_handler (const handler& h) {
        non_intrusive_handler_ptr p (new handler(h));
        add_non_intrusive_handler_ptr(p);
    }


    /// the text/caption for the current window
    property::rw< string> text;

    /// the unique ID of this window (formally known as HWND)
    property::r<types::id> id;

    /// the parent window
    property::r< wnd<> > parent;

    /// the next window in the z-order
    property::r< wnd<> > next;

    /// the previous window in the z-order
    property::r< wnd<> > prev;

    /// minimize, maximize, normally
    property::w<types::shown::type, types::shown> shown;

    /// whether it's shown or not
    property::rw<bool> visible;

    /// if true, when chaging the window's appearance, it will redraw; if false, it won't redraw until forced to
    property::w<bool> redraw;

    /// window's style
    property::rw<types::int64, types::style> style;

    /// window rectangle - always relative to parent
    property::rw<rectangle> full_rect;
    /// client rectangle - always relative to self
    property::rw<rectangle> client_rect;


    /// scroll information
    property_one_arg::rw< types::scroll_info, types::scroll_bar_type::type, types::scroll_bar_type > scroll_info;


    /// shows or hides a given scroll bar
    property_one_arg::w< bool, types::scroll_bar_type::type, types::scroll_bar_type> show_scroll;

    /// enables or disables a certain scroll bar
    property_one_arg::w< bool, types::scroll_bar_type::type, types::scroll_bar_type> enable_scroll;

    /// Returns the child that is at the top of the Z-order. 
    property::r< wnd<> > top_child_wnd;


    /// window's thread id
    property::r< types::int64> thread_id;
    /// window's proces id
    property::r< types::int64> process_id;

    /// if true, window is enabled (can receive input from the user)
    property::rw< bool> enabled;

    /// you can capture mouse and/or keyboard or release it
    property_one_arg::w<bool, types::capture::type, types::capture > capture;

    /// Returns the active window
    static property::r< wnd<> > active_wnd;
    /// Returns the window that has the keyboar focus, or null if there's no such window.
    static property::r< wnd<> > keyboard_focus_wnd;

    /* 
        to be implemented at a later time

        FIXME - font
        - icon

    */

protected:
    mutable critical_section cs;

    // creation information
    const wnd_init m_init;

private:
#ifdef BUILDING_EGUI
    friend struct detail::window_manager;
    friend struct detail::event_manager;
#endif

    // if this is false, we're been destroyed from the screen
    bool m_still_alive;

    // the window handle
    wnd_id_type m_hwnd;
    
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;

    // event handlers, if any
    typedef std::vector<on_any_event_func> on_any_event_array;
    on_any_event_array m_on_any_event;

    // if true, we're in the "wait_for" function
    bool m_is_waiting;
};


struct window_base : virtual window_top 
{
};




/** @brief just in case you want to play around with Windows HWND handles

*/
const void* raw_hwnd(const wnd<> & w);
const void* raw_hwnd(const window_top *w);

#ifdef BUILDING_EGUI
HWND get_hwnd(const wnd<> & w);
HWND get_hwnd(const window_top *w);
#endif

}

#endif

