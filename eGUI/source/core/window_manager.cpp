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

#include "stdafx_core.h"
#include "egui/core/wnd.hpp"
#include "egui/core/detail/window_manager.hpp"
#include "egui/core/detail/building_egui/event_manager.hpp"
#include "egui/core/detail/handle_all_events.hpp"
#include "egui/core/detail/util.hpp"
#include <boost/foreach.hpp>
#include "egui/core/detail/log.hpp"

namespace egui { 
    
void delete_( const wnd<> & w) {
    HWND h = get_hwnd(w);
    detail::window_manager::inst().erase_window_info(h);
}
void delete_( window_base * w) {
    HWND h = get_hwnd(w);
    detail::window_manager::inst().erase_window_info(h);
}

namespace detail {




wnd<> get_window(wnd_id_type h) {
    return window_manager::inst().create_window_from_id( h);
}




// defined in commctrl.cpp
void init_common_controls() ;

namespace {
    window_base * default_hwnd_to_window( wnd_id_type h) {
        return new window_instance_t<window_base>(h);
    }
}

window_manager ::window_manager() {
    init_common_controls();
    add_create_window_from_handle_func( default_hwnd_to_window);
    // for the current thread
    register_thread_hooks();

    // add this module
    add_win32_module( ::GetModuleHandle(0) );
}

window_manager & window_manager ::inst() {
    static window_manager i;
    return i;
}

void window_manager ::add_create_window_from_handle_func(create_window_from_handle_func func) {
    scoped_lock lk(m_cs);
    m_creators.insert( m_creators.begin(), func);
}

/** 
    Creates a window from this ID, if the window isn't already created
*/
wnd<> window_manager ::create_window_from_id(wnd_id_type h) {
    if  (!h)
        return wnd<>();

    if ( ! ::IsWindow( static_cast<HWND>( const_cast<void*>( h))))
        throw exception( GUI_STR("invalid window handle") );

    scoped_lock lk(m_cs);
    wnd_coll::iterator found = m_wnds.find(h);
    if ( m_wnds.find(h) != m_wnds.end())
        return found->second;

    // add it now
    m_wnds.insert( std::make_pair(h, create_window_from_handle(h)));
    return m_wnds.find(h)->second;
}

/** 
    Returns the window corresponding to this handle, or null if there's no such window
*/
wnd<> window_manager::existing_window_from_id(wnd_id_type h) {
    scoped_lock lk(m_cs);
    wnd_coll::iterator found = m_wnds.find(h);
    if ( m_wnds.find(h) != m_wnds.end())
        return found->second;
    // not found
    return wnd<>();
}


wnd<> window_manager ::create_window_from_handle(wnd_id_type h) {
    scoped_lock lk(m_cs);
    BOOST_FOREACH(create_window_from_handle_func func, m_creators)
    {
        window_top * w = func(h);
        if ( w)
        {
            add_created_wnd(w);
            return m_wnds.find(h)->second;
        }
    }
    throw exception( GUI_STR("could not create window for handle") );
}

/** 
    adds a window that has already been created
*/
void window_manager ::add_created_wnd(window_top * w) {
    LEGUI_ << GUI_STR("*****  new ") << type_name(*w) ;

    typedef boost::shared_ptr<window_top> wnd_ptr;

    wnd<> new_wnd = wnd<>( wnd_ptr(w));
    {
    scoped_lock lk(m_cs);
    wnd_id_type h = w->id->unique;
    if ( m_wnds.find(h) != m_wnds.end())
        return; // window already added

    m_wnds.insert( std::make_pair(h, new_wnd));
    m_internal_infos[ h ] = window_internal_info();
    }

    // we subclass everything
    subclass_window( w );
    detail::event_manager::inst().add_event_handlers_for_window(w);
    w->on_initialize();
    w->on_create();

    // non intrusive handlers
    scoped_lock lk(m_cs);
    BOOST_FOREACH(non_intrusive_handler_ptr handler, m_non_intrusive_handlers)
        handler->on_new_window_create(new_wnd);
}

void window_manager::add_form( HWND h) {
    scoped_lock lk(m_cs);
    m_forms.insert(h);
}
void window_manager::del_form( HWND h) {
    scoped_lock lk(m_cs);
    m_forms.erase(h);
}
bool window_manager::is_form( HWND h) const {
    scoped_lock lk(m_cs);
    return m_forms.find(h) != m_forms.end();
}

/** returns the class name of the given window - IN LOWER CASE
 (note that Class Names are case-insensitive)
 */
string window_manager::lo_class_name(HWND h) const {
    char_ buff[1024];
    int chars = GetClassName( h, buff, 1024);
    string class_name( buff, chars);
    return lo_case(class_name);
}

window_internal_info window_manager::internal_info(HWND h) const {
    scoped_lock lk(m_cs);
    internal_info_coll::const_iterator found = m_internal_infos.find(h);
    if ( found != m_internal_infos.end())
        return found->second;
    else
        return window_internal_info();    
}

void window_manager::internal_info(HWND h, const window_internal_info & info) {
    scoped_lock lk(m_cs);
    m_internal_infos[h] = info;
}

/** 
    erases all window information we have about this window.
    this is to be called when we don't care anymore about this window (most likely when it's deleted)
*/
void window_manager::erase_window_info( HWND h) {

    window_top * w = 0;
    {
    scoped_lock lk(m_cs);
    wnd_coll::const_iterator found = m_wnds.find(h);
    if ( found == m_wnds.end())
        return; // already erased
    w = found->second.m_window;
    }
    if ( w)
    {
        bool still_alive ;
        { scoped_lock lk(w->cs);
          still_alive = w->m_still_alive;
          w->m_still_alive = false;
        }
        if ( still_alive)
            w->on_destroy();
        unsubclass_window(w);
    }

    del_form(h);
    {
    scoped_lock lk(m_cs);
    m_wnds.erase(h);
    m_internal_infos.erase(h);
    }
}

void window_manager::register_thread_hooks() {
    DWORD id = ::GetCurrentThreadId();
    thread_info thread;
    { scoped_lock lk(m_cs);
      thread = m_threads[ id ];
    }
    if ( thread.create_hook )
        return; // they've already been set for this thread

    thread.create_hook = ::SetWindowsHookEx(WH_CBT, &createdestroy_hook, 0, id);
    thread.getmsg_hook = ::SetWindowsHookEx(WH_GETMESSAGE, &get_message_hook, 0, id);

    { scoped_lock lk(m_cs);
      m_threads[ id ].create_hook = thread.create_hook;
      m_threads[ id ].getmsg_hook = thread.getmsg_hook;
    }
}
void window_manager::unregister_thread_hooks() {
    DWORD id = ::GetCurrentThreadId();
    thread_info thread;
    { scoped_lock lk(m_cs);
      thread = m_threads[ ::GetCurrentThreadId() ];
      m_threads[ id ].create_hook = 0;
      m_threads[ id ].getmsg_hook = 0;
    }

    UnhookWindowsHookEx(thread.create_hook);
    UnhookWindowsHookEx(thread.getmsg_hook);
}

thread_info window_manager::current_thread_info() const
{
    DWORD id = ::GetCurrentThreadId();
    scoped_lock lk(m_cs);
    thread_info_coll::const_iterator found = m_threads.find(id);
    if ( found != m_threads.end())
        return found->second;
    else
        return thread_info();
}


void window_manager::add_callback(void * cb) {
    scoped_lock lk(m_cs);
    m_callbacks.insert(cb);
}
void window_manager::del_callback(void * cb) {
    scoped_lock lk(m_cs);
    m_callbacks.erase(cb);
}
bool window_manager::has_callback(void * cb) const {
    scoped_lock lk(m_cs);
    return m_callbacks.find(cb) != m_callbacks.end();
}

void window_manager::add_win32_module(HINSTANCE module) {
    scoped_lock lk(m_cs);
    m_win32_modules.insert(module);
}

window_manager::win32_module_set window_manager::get_win32_modules() const {
    scoped_lock lk(m_cs);
    return m_win32_modules;
}

HINSTANCE window_manager::find_instance_having_resource(int id, const char_* resource_type) {
    typedef window_manager::win32_module_set set;
    set modules = window_manager::inst().get_win32_modules();
    BOOST_FOREACH(HINSTANCE h, modules)
        if ( ::FindResource(h, MAKEINTRESOURCE(id), resource_type) )
            return h;
    // not found anywhere, just in case...
    return 0;
}

void window_manager::add_non_intrusive_handler_ptr(non_intrusive_handler_ptr p) {
    scoped_lock lk(m_cs);
    m_non_intrusive_handlers.push_back(p);
}


}}


