// window_manager.hpp

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


#ifndef JT07022008_window_manager_HPP_DEFINED
#define JT07022008_window_manager_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef BUILDING_EGUI
#error Donot include this in client code
#endif

#include "egui/core/wnd.hpp"
#include <vector>
#include <map>
#include <set>

namespace egui { namespace detail {

typedef boost::function1< window_top * , wnd_id_type> create_window_from_handle_func;

struct window_internal_info {
    window_internal_info() : old_wnd_proc(0), old_dlg_proc(0) {}

    WNDPROC old_wnd_proc;
    DLGPROC old_dlg_proc;
};

struct thread_info {
    thread_info() : create_hook(0), getmsg_hook(0) {}
    HHOOK create_hook;
    HHOOK getmsg_hook;
};

struct window_manager {

    static window_manager & inst() ;
protected:
    window_manager() ;
    window_manager(const window_manager&);


public:
    void add_create_window_from_handle_func(create_window_from_handle_func func) ;

    wnd<> create_window_from_id(wnd_id_type h);
    wnd<> existing_window_from_id(wnd_id_type h);
    void add_created_wnd(window_top * w);

    void add_form( HWND h);
    void del_form( HWND h);
    bool is_form( HWND h) const;

    string lo_class_name(HWND h) const;
    
    window_internal_info internal_info(HWND h) const;
    void internal_info(HWND h, const window_internal_info & info) ;

    void erase_window_info( HWND h);

    void register_thread_hooks();
    void unregister_thread_hooks();

    thread_info current_thread_info() const;

    void add_callback(void * cb);
    void del_callback(void * cb);
    bool has_callback(void * cb) const;

    typedef std::set<HINSTANCE> win32_module_set;
    void add_win32_module(HINSTANCE module);
    win32_module_set get_win32_modules() const;

    HINSTANCE find_instance_having_resource(int id, const char_* resource_type) ;

    void add_non_intrusive_handler_ptr(non_intrusive_handler_ptr p);

private:
    wnd<> create_window_from_handle(wnd_id_type h);

private:
    mutable critical_section m_cs;

    typedef std::map< wnd_id_type, wnd<> > wnd_coll;
    // the C++ window objects
    wnd_coll m_wnds;

    // internal information for the C++ windows
    typedef std::map< wnd_id_type, window_internal_info> internal_info_coll;
    internal_info_coll m_internal_infos;

    // when we ask for a window corresponding to an HWND, and that window doesn't yet exist,
    // we invoke the creators - until one creator actually creates the window
    typedef std::vector<create_window_from_handle_func> creator_array;
    creator_array m_creators;

    // these are the handles of the windows we know are dialogs (forms)
    std::set<HWND> m_forms;

    typedef std::map<DWORD, thread_info> thread_info_coll;
    thread_info_coll m_threads;

    typedef std::set<void*> callback_set;
    callback_set m_callbacks;

    typedef std::set<HINSTANCE> win32_module_set;
    win32_module_set m_win32_modules;

    typedef std::vector<non_intrusive_handler_ptr> non_intrusive_handler_ptr_array;
    non_intrusive_handler_ptr_array m_non_intrusive_handlers;
};


bool has_comctl_ver(UINT major, UINT minor) ;

}}

#endif

