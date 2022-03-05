// handle_all_events.cpp

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
#include <sstream>
#include <boost/foreach.hpp>

#pragma warning (disable : 4312) // 'reinterpret_cast' : conversion from 'LONG' to 'DLGPROC' of greater size
#pragma warning (disable : 4244) // 'argument' : conversion from 'LONG_PTR' to 'LONG', possible loss of data

namespace egui { namespace detail {

namespace {
    // what's sent to the window callback on ::CreateWindowEx or ::CreateDialogParam
    struct wnd_callback : wnd_init {
        create_window_base * creator;
        string class_name;
        bool already_created;
        wnd_callback(create_window_base * creator, const string & class_name, const wnd_init & init) 
            : creator(creator), class_name(class_name), already_created(false), wnd_init(init) {}
        virtual ~wnd_callback() {}
    };
    struct form_callback : wnd_callback {
        int form_id;
        form_callback(int form_id, create_window_base * creator, const string & class_name, const wnd_init& init) : form_id(form_id), wnd_callback(creator, class_name, init) {}
     };

    int get_wm_register_internal() {
        std::basic_ostringstream<char_> msg;
        msg << GUI_STR("win32gui-wm_create-") << ::GetCurrentProcessId();
        return ::RegisterWindowMessage( msg.str().c_str());
    }
    // called so that a window will register itself with our library,
    // if it has not already done so
    //
    // this is useful ONLY if we're on top of another framework
    const int wm_register_internal = get_wm_register_internal();

    void handle_create_window_msg( HWND h, UINT msg) 
    {
        if ( msg == WM_CREATE)
            // forms NEVER receive WM_CREATE
            window_manager::inst().del_form( h);
        else if ( msg == WM_INITDIALOG)
            // forms receive WM_INITDIALOG
            window_manager::inst().add_form( h);
    }

    void handle_destroy_window_msg( HWND h, UINT msg) {
        if ( msg == WM_NCDESTROY)
        {
            // window is about to be destroyed
            window_manager::inst().del_form(h);
            window_manager::inst().erase_window_info(h);
        }
    }

    bool is_dialog( HWND h) {
        if ( window_manager::inst().is_form(h))
            return true;

        string class_name = window_manager::inst().lo_class_name(h);
        if ( class_name == GUI_STR("#32770") ) 
            return true;

        return false;
    }

    void handle_window_create(HWND h, wnd_callback * create) {
        assert(create);
        if ( window_manager::inst().has_callback(create)) {
            if ( !create->already_created) {
                create->already_created = true;
                window_manager::inst().add_created_wnd( create->creator->create(h) );
            }
        }
        else
            // this window wasn't specifically created by us
            window_manager::inst().create_window_from_id( h);
    }

    INT_PTR CALLBACK dlg_proc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        handle_create_window_msg( hwndDlg, uMsg);
        INT_PTR result = 0;
        try {
            if ( uMsg == WM_INITDIALOG)
                handle_window_create(hwndDlg, reinterpret_cast<wnd_callback*>( (void*)lParam) );

            result = event_manager::inst().handle(hwndDlg, uMsg, wParam, lParam, true);
        }
        catch(exception & ) {
        }
        catch(...) {
        }
        handle_destroy_window_msg( hwndDlg, uMsg);
        return result;
    }

    LRESULT CALLBACK wnd_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
        INT_PTR result = 0;
        handle_create_window_msg( hwnd, message);
        try {
            if ( message == WM_CREATE) {
                CREATESTRUCT * create = reinterpret_cast< CREATESTRUCT*>( (void*)lParam);
                wnd_callback* cb = static_cast<wnd_callback*>( create->lpCreateParams);
                handle_window_create(hwnd, cb);
            }
            result = event_manager::inst().handle(hwnd, message, wParam, lParam, false);
        }
        catch(exception & ) {
        }
        catch(...) {
        }
        handle_destroy_window_msg( hwnd, message);
        return result;
    }

    HINSTANCE find_instance_having_form_resource(int form_id) {
        typedef window_manager::win32_module_set set;
        set modules = window_manager::inst().get_win32_modules();
        BOOST_FOREACH(HINSTANCE h, modules)
            if ( ::FindResource(h, MAKEINTRESOURCE(form_id), RT_DIALOG) )
                return h;
        // not found anywhere, just in case...
        return ::GetModuleHandle(0);
    }

} // annonymous namespace


/** 
    creates an on-the-screen form window
*/
wnd_id_type create_on_the_screen_window( create_window_base * creator, const string & class_name, const wnd_init& init, int form_id, form* ) {
    // register hooks to catch all window creations
    window_manager::inst().register_thread_hooks();

    // create a win32 dialog
    if ( form_id > 0)
    {
        form_callback cb(form_id, creator, class_name, init);
        window_manager::inst().add_callback( &cb);
        HINSTANCE hinst = find_instance_having_form_resource(form_id);
        HWND h = 0;
        if ( init.m_style & form_style::modal) 
            ::DialogBoxParam( 
                hinst, 
                MAKEINTRESOURCE(form_id), 
                static_cast<HWND>( const_cast<void*>(init.m_parent)), 
                &dlg_proc, 
                reinterpret_cast<LPARAM>(&cb) );
        else
            h = ::CreateDialogParam( 
                hinst, 
                MAKEINTRESOURCE(form_id), 
                static_cast<HWND>( const_cast<void*>(init.m_parent)), 
                &dlg_proc, 
                reinterpret_cast<LPARAM>(&cb) );
        window_manager::inst().del_callback( &cb);
        return h;
    }
    else
        // user has not specified any form ID
        return create_on_the_screen_window(creator, GUI_STR("STATIC"), init, 0, (void*)0);
}

/** 
    creates an on-the-screen control window
*/
wnd_id_type create_on_the_screen_window( create_window_base * creator, const string & class_name, const wnd_init& init, int , void* ) {
    // register hooks to catch all window creations
    window_manager::inst().register_thread_hooks();

    wnd_callback cb(creator, class_name, init);
    window_manager::inst().add_callback( &cb);
    rectangle r(0,0,100,100);
    if ( init.m_rect_set)
        r = init.m_rect;

    DWORD s = (DWORD)(init.m_style & 0xFFFFFFFF);
    DWORD e = (DWORD)(init.m_style >> 32);

    HWND h = ::CreateWindowEx(
        e,
        class_name.c_str(),
        init.m_text.c_str() ,
        s,
        r.start.x,
        r.start.y,
        r.size.width,
        r.size.height,
        static_cast<HWND>( const_cast<void*>(init.m_parent)) ,
        0,
        0,
        &cb
        );
    window_manager::inst().del_callback( &cb);
    return h;
}


LRESULT CALLBACK createdestroy_hook(int code, WPARAM wParam, LPARAM lParam) {
    HWND wnd_to_register = 0;
    // note: we don't create/destroy the C++ object right here. It could be too early!
    //
    // For example, the programmer might have created an object manually, like, create_wnd<my_edit>(...)
    // If we were to register the window here, we would create the wrong C++ object (in this case, we would
    // have created an 'edit')

    // note: since we caught this event, we're gonna post to the same window (this way we know we'll
    // catch this event also!)
    if ( code == HCBT_CREATEWND) {
        wnd_to_register = reinterpret_cast<HWND>(wParam);

        // in case it's a window to be created by us, do it so (check the lpCreateParams to see if it' our window)
        CBT_CREATEWND * create_wnd = reinterpret_cast<CBT_CREATEWND*>(lParam);
        wnd_callback * callback = static_cast<wnd_callback*> ( create_wnd->lpcs->lpCreateParams);
        if ( callback)
            handle_window_create(wnd_to_register, callback);
        // just in case we somehow miss creating the window 
        ::PostMessage(wnd_to_register, wm_register_internal, true, reinterpret_cast<LPARAM>(wnd_to_register) );
    }
    else if ( code == HCBT_DESTROYWND) {
        wnd_to_register = reinterpret_cast<HWND>(wParam);
        // note: posting to the same window will most likely fail - since by the time it would get
        //       the message, it would already be destroyed ;)
        ::PostMessage(0, wm_register_internal, false, reinterpret_cast<LPARAM>(wnd_to_register) );
    }
    return CallNextHookEx( window_manager::inst().current_thread_info().create_hook , code, wParam, lParam);
}

LRESULT CALLBACK get_message_hook(int code, WPARAM wParam, LPARAM lParam) {
    MSG * msg = reinterpret_cast<MSG*>(lParam);
    if ( msg->message == wm_register_internal) {
        bool create = msg->wParam != 0;
        HWND h = reinterpret_cast<HWND>(msg->lParam);
        if ( create)
            // create this window
            window_manager::inst().create_window_from_id( h);
        else
            window_manager::inst().erase_window_info( h);
    }
    return CallNextHookEx( window_manager::inst().current_thread_info().getmsg_hook, code, wParam, lParam);
}







void subclass_window( window_top *w )
{
    if ( w->process_id != ::GetCurrentProcessId() )
        throw exception( GUI_STR("cannot subclass a window created by another process"));

    window_manager::inst().register_thread_hooks();

    HWND h = get_hwnd(w);
    window_internal_info info;
    bool is_dlg = is_dialog(h) || dynamic_cast<form*>(w);
    if ( is_dlg) {
        DLGPROC old = reinterpret_cast<DLGPROC>( ::GetWindowLongPtr(h, DWLP_DLGPROC));
        if ( old == &dlg_proc)
            return; // we've already subclassed this

        info.old_dlg_proc = old;
        window_manager::inst().internal_info(h, info);
        ::SetWindowLongPtr(h, DWLP_DLGPROC, reinterpret_cast<LONG_PTR>(&dlg_proc));
    }
    else {
        WNDPROC old = reinterpret_cast<WNDPROC>( ::GetWindowLongPtr(h, GWLP_WNDPROC));
        if ( old == &wnd_proc)
            return; // we've already subclassed this

        info.old_wnd_proc = old;
        window_manager::inst().internal_info(h, info);
        ::SetWindowLongPtr(h, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&wnd_proc) );
    }
}

void unsubclass_window( window_top *w )
{
    HWND h = get_hwnd(w);
    window_internal_info info = window_manager::inst().internal_info(h);
    if ( info.old_dlg_proc) 
        ::SetWindowLongPtr(h, DWLP_DLGPROC, reinterpret_cast<LONG_PTR>(info.old_dlg_proc));

    if ( info.old_wnd_proc)
        ::SetWindowLongPtr(h, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(info.old_wnd_proc) );

}


}}


