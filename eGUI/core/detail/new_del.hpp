// new_del.hpp

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


#ifndef JT07022008_new_del_HPP_DEFINED
#define JT07022008_new_del_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/core/detail/fwd.hpp"

namespace egui {

template<class new_window_type = window_base, class p1 = void_, class p2 = void_, class p3 = void_, class p4 = void_, class p5 = void_, class p6 = void_, class p7 = void_, class p8 = void_, class p9 = void_, class p10 = void_> struct new_t {

    new_t(
            const wnd_init & init = wnd_init() ,
            const p1 & a1 = p1(),
            const p2 & a2 = p2(),
            const p3 & a3 = p3(),
            const p4 & a4 = p4(),
            const p5 & a5 = p5(),
            const p6 & a6 = p6(),
            const p7 & a7 = p7(),
            const p8 & a8 = p8(),
            const p9 & a9 = p9(),
            const p10 & a10 = p10() ) 
        : init(init)
        , v1(a1)
        , v2(a2)
        , v3(a3)
        , v4(a4)
        , v5(a5)
        , v6(a6)
        , v7(a7)
        , v8(a8)
        , v9(a9)
        , v10(a10)
    {}



    wnd_init init;
    p1 v1;
    p2 v2;
    p3 v3;
    p4 v4;
    p5 v5;
    p6 v6;
    p7 v7;
    p8 v8;
    p9 v9;
    p10 v10;
};

/* The following need to compile:

    new_(5);
    new_( L"title", 5);

    new_<form>(5);
    new_<form>( L"title", 5);
    new_<form>( rectangle(0,0,10,10), 5);
    new_<form>( wnd_init().rect(0,0,10,10).text(L"tt"), 5);
    new_<form>();
    new_( wnd_init().rect(0,0,50,50), 10);
    new_( wnd_init().rect(0,0,50,50), 10, 2.4);
    new_( wnd_init().rect(0,0,50,50), 10, (wchar_t*)L"dummy");
    new_( L"title", 10, (wchar_t*)L"dummy");
    new_( rectangle(0,0,10,10), 10, (wchar_t*)L"dummy");
    new_( L"tt", 10, (wchar_t*)L"dummy");
    new_( L"tt", 10, (wchar_t*)L"dummy", 3.2);

    new_<form>( wnd_init().rect(0,0,50,50), 10, 2.4);
    new_<form>( wnd_init().rect(0,0,50,50), 10, (wchar_t*)L"dummy");
    new_<form>( L"title", 10, (wchar_t*)L"dummy");
    new_<form>( rectangle(0,0,10,10), 10, (wchar_t*)L"dummy");
    new_<form>( L"tt", 10, (wchar_t*)L"dummy");
    new_<form>( L"tt", 10, (wchar_t*)L"dummy", 3.2);


    Hopefully, something like this should compile as well:
    new_( wnd_init().rect(0,0,50,50), 10, L"dummy");

    However, VC treates L"dummy" as const wchart[6]. On top of that, it makes p2 = const wchart[6] and generates
    a compile time error "cannot specify explicit initializer for arrays". No matter what I do, I still can't initialize it.

    I guess one solution is to have a wrapper class, like wrap<p1> v1; wrap<p2> v2; etc. 
    and for c-like strings, internally hold std strings
*/

/** 
new_[<type>]([args]);

Caches the arguments to be passed at construction, when constructing a window.

The type of the window to create is found in one of 2 ways:

@code
// [1] the type of window to create is 'form', passed as template argument to new_
wnd<> w = new_<form>("My Form");

// [2] the type of window to create is 'label', passed as template argument to the result
wnd<label> w = new_("My Label");
@endcode

The @c args are optional, and we allow up to 10 arguments. If you pass arguments, the first argument @b must be @em convertible to wnd_init.
In other words, wnd_init contains the most common initialization arguments that are needed at creation of a window:
- its style, 
- its text (caption), 
- its rectangle and 
- its parent.

Thus, the first argument must be of any of the following types:
- wnd_init
- int64 (which means, it contains the window's style)
- string (which means, it contains the window's caption)
- rectangle (which mean, it contains the window's rectangle)
- wnd<> (which means, it contains the window's parent)

The remaining arguments are passed to the window at construction

@code
struct font_label : label {
    font_label(string font, int size) ;
    ...
};

// construct a label with a font
//
// Arg 1    : wnd_init 
// Args 2,3 : pass to font_label's constructor
wnd <> w = new_<font_label>("My Label", "Tahoma", 12);
@endcode

*/
inline new_t<> new_() { return new_t<>(); }

inline new_t<window_base> new_(const wnd_init & init) { return new_t<window_base>( init); }
template<class p1> inline new_t<window_base,p1> new_(const wnd_init & init, const p1 & a1) { return new_t<window_base,p1>( init, a1); }
template<class p1, class p2> inline new_t<window_base,p1,p2> new_(const wnd_init & init, const p1 & a1, const p2 & a2) { return new_t<window_base,p1,p2>(init, a1,a2); }
template<class p1, class p2, class p3> inline new_t<window_base,p1,p2,p3> new_(const wnd_init & init, const p1 & a1, const p2 & a2, const p3 & a3) { return new_t<window_base,p1,p2,p3>(init, a1,a2,a3); }

template<class new_wnd_type> inline new_t<new_wnd_type> new_() { return new_t<new_wnd_type>( ); }

template<class new_wnd_type> inline new_t<new_wnd_type> new_(const wnd_init & init) { return new_t<new_wnd_type>( init); }
template<class new_wnd_type, class p1> inline new_t<new_wnd_type,p1> new_(const wnd_init & init, const p1 & a1) { return new_t<new_wnd_type,p1>( init, a1); }
template<class new_wnd_type, class p1, class p2> inline new_t<new_wnd_type,p1,p2> new_(const wnd_init & init, const p1 & a1, const p2 & a2) { return new_t<new_wnd_type,p1,p2>(init, a1,a2); }
template<class new_wnd_type, class p1, class p2, class p3> inline new_t<new_wnd_type,p1,p2,p3> new_(const wnd_init & init, const p1 & a1, const p2 & a2, const p3 & a3) { return new_t<new_wnd_type,p1,p2,p3>(init, a1,a2,a3); }

// FIXME - up to 10 args



void delete_( const wnd<> & w); 
void delete_( window_base * w);

/** 
    Every time a window is created, it will be an instance of this class
*/
template<class base> struct window_instance_t : base, virtual window_top {

    window_instance_t(wnd_id_type hwnd) : window_top(hwnd) {}

    template<class type> window_instance_t(wnd_id_type hwnd, const new_t<type> & args) 
        : window_top(hwnd,args.init) {}

    template<class type, class p1> window_instance_t(wnd_id_type hwnd, const new_t<type,p1> & args) 
        : window_top(hwnd,args.init), base(args.v1) {}
    template<class type, class p1, class p2> window_instance_t(wnd_id_type hwnd, const new_t<type,p1,p2> & args) 
        : window_top(hwnd,args.init), base(args.v1, args.v2) {}
    template<class type, class p1, class p2, class p3> window_instance_t(wnd_id_type hwnd, const new_t<type,p1,p2,p3> & args) 
        : window_top(hwnd,args.init), base(args.v1, args.v2, args.v3) {}
    template<class type, class p1, class p2, class p3, class p4> window_instance_t(wnd_id_type hwnd, const new_t<type,p1,p2,p3,p4> & args) 
        : window_top(hwnd,args.init), base(args.v1, args.v2, args.v3, args.v4) {}
    template<class type, class p1, class p2, class p3, class p4, class p5> window_instance_t(wnd_id_type hwnd, const new_t<type,p1,p2,p3,p4,p5> & args) 
        : window_top(hwnd,args.init), base(args.v1, args.v2, args.v3, args.v4, args.v5) {}

};

struct create_window_base {
    virtual ~create_window_base() {}
    virtual window_top * create(wnd_id_type h) = 0;
};

template<class window, class param> struct create_window : create_window_base {
    param p;
    create_window(const param& p) : p(p) {}

    virtual window_top * create(wnd_id_type h) { 
        window_top * w = new window(h, p); 
        return w;
    }

};


}

#endif

