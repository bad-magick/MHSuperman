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
#include <time.h>
#include "egui/core/detail/building_egui/event_manager.hpp"

namespace egui { 

namespace win32 {
    SIZE to(const size & sz) { 
        SIZE r;
        r.cx = sz.width;
        r.cy = sz.height;
        return r;
    }
    POINT to(const point & p) {
        POINT r;
        r.x = p.x;
        r.y = p.y;
        return r;
    }
    RECT to(const rectangle & rect) {
        RECT r;
        r.left = rect.start.x ;
        r.top = rect.start.y ;
        r.right = rect.start.x + rect.size.width ;
        r.bottom = rect.start.y + rect.size.height ;
        return r;
    }

    size from(const SIZE & sz) {
        return size( sz.cx, sz.cy);
    }
    point from(const POINT & p) {
        return point( p.x, p.y);
    }
    rectangle from(const RECT & r) {
        return rectangle( r.left, r.top, r.right - r.left, r.bottom - r.top);
    }

    COLORREF to(const types::color & c) {
        if ( c != color::invalid_)
            return RGB( c.red(), c.green(), c.blue());
        else
            return CLR_DEFAULT;
    }
    types::color from(const COLORREF & c) {
        if ( c != CLR_DEFAULT)
            return color( GetRValue(c), GetGValue(c), GetBValue(c) );
        else
            return color::invalid_;
    }


    void UnixTimeToFileTime(time_t t, LPFILETIME pft)
    {
        // Note that LONGLONG is a 64-bit value
        LONGLONG ll;

        ll = Int32x32To64(t, 10000000) + 116444736000000000;
        pft->dwLowDateTime = (DWORD)ll;
        pft->dwHighDateTime = (DWORD)(ll >> 32);
    }
    void UnixTimeToSystemTime(time_t t, LPSYSTEMTIME pst)
    {
        FILETIME ft;

        UnixTimeToFileTime(t, &ft);
        FileTimeToSystemTime(&ft, pst);
    }
    
    SYSTEMTIME to(const time_t & t) {
        SYSTEMTIME result;
        UnixTimeToSystemTime(t, &result);
        return result;
    }

    void ST2T(const SYSTEMTIME &st, time_t &t)
    {
        time_t now;
        time(&now);
        tm local = *localtime(&now);

        local.tm_year = st.wYear-1900;
        local.tm_mon = st.wMonth-1;
        local.tm_mday = st.wDay;
        local.tm_wday = st.wDayOfWeek;
        local.tm_hour = st.wHour;
        local.tm_min = st.wMinute;
        local.tm_sec = st.wSecond;

        t = mktime(&local);
    }

    time_t from(const SYSTEMTIME & s) {
        time_t result;
        ST2T(s, result);
        return result;
    }

    HIMAGELIST to(const image_list_base & i) { 
        return (HIMAGELIST)i.id();
    }
    HBITMAP to(const bitmap_base & b) { 
        return (HBITMAP)b.id();
    }
    HICON to(const icon_base & i) { 
        return (HICON)i.id();
    }
    HFONT to(const font_base & f) { 
        return (HFONT)f.id();
    }

    temporary_image_list from(const HIMAGELIST & h) { 
        return h;
    }

    temporary_bitmap from(const HBITMAP & h) { 
        return h;
    }

    temporary_icon from(const HICON & h) { 
        return h;
    }

    temporary_font from(const HFONT & h) { 
        return h;
    }

    UINT get_wm_msg(const ev::base & event) {
        return egui::detail::get_windows_msg(event);
    }
    WPARAM get_wparam(const ev::base & event) {
        return detail::event_manager::inst().get_wparam(event);
    }
    LPARAM get_lparam(const ev::base & event) {
        return detail::event_manager::inst().get_lparam(event);
    }


}
    
namespace types {

color::color(int r, int g, int b) : m_rgb(RGB(r,g,b)) {}


const int color::red() const       { return GetRValue(m_rgb); }
const int color::green() const     { return GetGValue(m_rgb); }
const int color::blue() const      { return GetBValue(m_rgb); }

color & color::red(int val) {
    m_rgb = RGB( val, green(), blue() );
    return *this;
}
color & color::green(int val) {
    m_rgb = RGB( red(), val, blue() );
    return *this;
}
color & color::blue(int val) {
    m_rgb = RGB( red(), green(), val );
    return *this;
}

color color::invalid_color() {
    color c;
    c.m_rgb = CLR_DEFAULT;
    return c;
}

color color::invalid_ = invalid_color();



/** 

Assumes the point is relative to 'from', and transforms it into 'to'.

In order to convert from screen coordinates:
pnt.convert(0, some_wnd);

In order to convert TO screen coordinates:
pnt.convert(some_wnd,0);

*/
point point::convert(const wnd<> & from, const wnd<> & to) const {
    HWND h_from = get_hwnd(from);
    HWND h_to = get_hwnd(to);
    POINT p = win32::to(*this);
    ::MapWindowPoints(h_from, h_to, &p, 1);
    return win32::from(p);
}
bool point::is_in_rect(const rectangle & r) const {
    return r.contains_point(*this);
}



/** 
Assumes the rectangle is relative to 'from', and transforms it into 'to'.

In order to convert from screen coordinates:
pnt.convert(0, some_wnd);

In order to convert TO screen coordinates:
pnt.convert(some_wnd,0);

*/
rectangle rectangle::convert(const wnd<> & from, const wnd<> & to) const {
    HWND h_from = get_hwnd(from);
    HWND h_to = get_hwnd(to);
    RECT r = win32::to(*this);
    ::MapWindowPoints(h_from, h_to, (POINT*)&r, 2);
    return win32::from(r);
}
/** 
Returns true if this rectangle contains the given point
*/
bool rectangle::contains_point(const point & p) const {
    return ::PtInRect( &win32::to(*this), win32::to(p) ) != 0;
}

rectangle rectangle::intersect(const rectangle& other) const {
    RECT r;
    if ( ::IntersectRect( &r, &win32::to(*this), &win32::to(other) ) ) 
        return win32::from(r);
    else 
        return invalid_rect;
} 

rectangle rectangle::merge(const rectangle& other) const {
    RECT r;
    if ( ::UnionRect( &r, &win32::to(*this), &win32::to(other)) ) return win32::from(r);
    else return invalid_rect;
}

rectangle rectangle::inflate(const size_type& sz, int direction ) const {
    rectangle r = *this;
    if ( direction & inflate_to_right) r.size.width += sz.width;
    if ( direction & inflate_to_left) r.start.x -= sz.width;

    if ( direction & inflate_to_bottom) r.size.height += sz.height;
    if ( direction & inflate_to_top) r.start.y -= sz.height;
    return r;
}

void rectangle::offset(int x, int y) {
	start.x += x;
	start.y += y;
}




}}

// End of file


