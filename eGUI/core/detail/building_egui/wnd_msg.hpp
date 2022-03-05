#ifndef JOHN_TORJO_WIN32GUI_detail_wnd_msg
#define JOHN_TORJO_WIN32GUI_detail_wnd_msg

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// detail/wnd_msg.hpp

// Win32 GUI Generics library
//
// Copyright (C) 2004 John Torjo (john@torjo.com)
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
// To see the version you have now, read win32gui/version.txt
//
// You can find the latest version of this library at http://www.torjo.com/win32gui/

#ifndef BUILDING_EGUI
#error Donot include this in client code
#endif


namespace egui {

/*
    Allows simpler access to a Windows Message, before sending or posting it to a window.
    It's much easier to send/post a Windows Message using this, since it allows for
    easy setting of parts of the message.

 Example:
    wnd<> w = ...;
    w->send_msg( wnd_msg(EM_CHARFROMPOS).l_param_lo(pnt.x).l_param_hi(pnt.y) ); // OR
    w->send_msg( wnd_msg(EM_CHARFROMPOS).l_param(pnt.x,pnt.y) ); // OR

    Instead of
    w->send_msg( EM_CHARFROMPOS, 0, MAKELPARAM(pt.x, pt.y) );
*/
struct wnd_msg {
    wnd_msg(UINT msg) : msg(msg), wparam(0), lparam(0) {}

    template<class T>
    wnd_msg & w_param(T val) {
        wparam = (WPARAM)val;
        return *this;
    }
    wnd_msg & w_param(int lo, int hi) {
        wparam = MAKEWPARAM(lo, hi);
        return *this;
    }
    wnd_msg & w_param_lo(int lo) {
        wparam = MAKEWPARAM( lo, HIWORD(wparam) );
        return *this;
    }
    wnd_msg & w_param_hi(int hi) {
        wparam = MAKEWPARAM( LOWORD(wparam), hi );
        return *this;
    }

    template<class T>
    wnd_msg & l_param(T val) {
        lparam = (LPARAM)val;
        return *this;
    }
    wnd_msg & l_param(int lo, int hi) {
        lparam = MAKELPARAM(lo, hi);
        return *this;
    }
    wnd_msg & l_param_lo(int lo) {
        lparam = MAKELPARAM( lo, HIWORD(lparam) );
        return *this;
    }
    wnd_msg & l_param_hi(int hi) {
        lparam = MAKELPARAM( LOWORD(lparam), hi );
        return *this;
    }

    UINT msg;
    WPARAM wparam;
    LPARAM lparam;
};



}


#endif // JOHN_TORJO_WIN32GUI_detail_wnd_msg
