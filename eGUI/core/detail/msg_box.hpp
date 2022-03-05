// msg_box.hpp

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


#ifndef JT07022008_msg_box_HPP_DEFINED
#define JT07022008_msg_box_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace egui {

struct mb {
    enum type {
        ok = 1,
        cancel = 2,
        yes = 4,
        no = 8,
        exclamation = 1 << 4, 
        warning = 1 << 5,
        asterisk =  1 << 6,
        question = 1 << 7,
        stop = 1 << 8,
        error = 1 << 9,
        hand = 1 << 10,
        def_but_1 = 1 << 11,
        def_but_2 = 1 << 12,
        def_but_3 = 1 << 13,
        def_but_4 = 1 << 14
    };
};

template<int> struct ct_assert_if_true {};
template<> struct ct_assert_if_true<0> { typedef char value; };

// if a is true, b must be true
template<bool,bool> struct ct_assert_implies_b { typedef char value; };
template<> struct ct_assert_implies_b<0,1> {};
template<int a,int b> struct ct_assert_implies : ct_assert_implies_b<a,b> {};


template<int buttons> struct check_msg_box_buttons {
    typedef typename ct_assert_if_true<(buttons & (mb::ok | mb::yes)) == (mb::ok | mb::yes) >::value check1;
    typedef typename ct_assert_if_true<(buttons & (mb::ok | mb::no)) == (mb::ok | mb::no) >::value check2;

    // cancel needs ok
    typedef typename ct_assert_implies<buttons & mb::cancel, (buttons & (mb::ok | mb::cancel)) == (mb::ok | mb::cancel) >::value check3;
    // yes and no belong together
    typedef typename ct_assert_implies<buttons & mb::yes, (buttons & (mb::yes | mb::no)) == (mb::yes | mb::no) >::value check4;
    typedef typename ct_assert_implies<buttons & mb::no, (buttons & (mb::yes | mb::no)) == (mb::yes | mb::no) >::value check5;

};

int msg_box(int buttons, const string & msg, wnd<> parent = wnd<>(), string title = string() ) ;

template<int buttons> int msg_box(const string & msg, wnd<> parent = wnd<>(), const string & title = string() ) {
    check_msg_box_buttons<buttons> checker;
    checker;
    return msg_box(buttons, msg, parent, title);
}


}

#endif

