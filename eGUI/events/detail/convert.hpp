// convert.hpp

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


#ifndef JT07022008_events_convert_HPP_DEFINED
#define JT07022008_events_convert_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/events/detail/fwd.hpp"

namespace egui { namespace ev { namespace converters {

template<class type> struct converter_base : converter_top {
    /* @param val - the variable we're to initialize on init (from the win32 event), and update its place on teh win32 event on exit
    */
    converter_base(type & val) : m_val(val) {}

    void init() {
        init_type(m_val);
    }
    void exit() {
        exit_type(m_val);
    }

    virtual void init_type(type& val) {}
    virtual void exit_type(type& val) {}

private:
    type & m_val;
};

/////////////////////////////////////////////////////////////
// do conversion

struct null_set {
    template<class type, class other> static void set(type & dest, const other& src ) {}
};

struct identity {
    template<class type> static const type & get(const type & val) { return val; }
    template<class type, class other> static void set(type & dest, const other& src ) { dest = (type)src; }
};

struct reverse_bool {
    template<class type> static bool get(const type & val) { return val; }
    template<class type> static void set(type & dest, bool src ) { dest = !src; }
};

struct lo {
    typedef types::int64 int64;

    static int64 get(const int64 & val) { 
        return LOWORD(val); 
    }
    template<class type> static void set(int64 & dest, const type & src ) { 
        dest = MAKEWPARAM( HIWORD(dest), src); 
    }
};

struct hi {
    typedef types::int64 int64;

    static int64 get(const int64 & val) { 
        return HIWORD(val); 
    }
    template<class type> static void set(int64 & dest, const type & src ) { 
        dest = MAKEWPARAM( src, LOWORD(dest)); 
    }
};

/////////////////////////////////////////////////////////////
// reinterpret as

struct access_win32_data {
    static types::int64 *wparam( ::egui::ev::base * p) {
        return &(p->wparam);
    }
    static types::int64 *lparam( ::egui::ev::base * p) {
        return &(p->lparam);
    }
    static types::int64 *l_result( ::egui::ev::base * p) {
        return &(p->result);
    }
    static unsigned long * msg( ::egui::ev::base * p) {
        return &(p->windows_msg);
    }
};

struct wp {}; // wparam
struct lp {}; // lparam

template<class param = lp> struct as_pointer {
    static void * convert( ::egui::ev::base * p) {
        return access_win32_data::lparam(p);
    }
};

template<> struct as_pointer<wp> {
    static void * convert( ::egui::ev::base * p) {
        return access_win32_data::wparam(p);
    }
};

struct get_wparam {
    static int64 * convert( ::egui::ev::base * p) {
        return access_win32_data::wparam(p);
    }
};


struct get_lparam {
    static int64 * convert( ::egui::ev::base * p) {
        return access_win32_data::lparam(p);
    }
};

struct get_msg {
    static unsigned long * convert( ::egui::ev::base * p) {
        return access_win32_data::msg(p);
    }
};

struct get_l_result {
    static int64 * convert( ::egui::ev::base * p) {
        return access_win32_data::l_result(p);
    }
};

/////////////////////////////////////////////////////////////

// convert(this, as_pointer<wparam>(), &NMLISTM::iImage)
template<class type, class as_pointer, class reinterpret_as, class member_type, class do_conversion = identity > struct convert_pointer_to_member : converter_base<type> {
    typedef member_type reinterpret_as::* member_data;
    member_data m_data;

    convert_pointer_to_member(member_data data, type & val) : converter_base<type>(val), m_data(data) {}

    virtual void init_type(type& val) {
        reinterpret_as * p = static_cast< reinterpret_as * >( as_pointer::convert(converter_top::m_base) );
        val = (type)do_conversion::get( p->*m_data );
    }

    virtual void exit_type(type& val) {
        reinterpret_as * p = static_cast< reinterpret_as * >( as_pointer::convert(converter_top::m_base) );
        do_conversion::set( p->*m_data, val) ;
    }

};

// convert(this, get_wparam(), lo)
// convert(this, get_wparam(), hi)
template<class type, class reinterpret_as, class do_conversion = identity> struct simple_convert : converter_base<type> {
    simple_convert(type & val): converter_base<type>(val) {}

    virtual void init_type(type& val) {
        val = (type)do_conversion::get( *reinterpret_as::convert(converter_top::m_base) );
    }

    virtual void exit_type(type& val) {
        do_conversion::set( *reinterpret_as::convert(converter_top::m_base), val) ;
    }
};


// convert(this, get_wparam())
template<class type, class reinterpret_as>
inline converter_top * convert(type & val, const reinterpret_as&) {
    return new simple_convert<type,reinterpret_as>( val);
}

template<class type, class reinterpret_as>
inline converter_top* convert(egui::ev::read_only<type> & ro_val, const reinterpret_as&) {
    type & val = access_read_only_object(ro_val);
    converter_top* p = new simple_convert<type,reinterpret_as>( val);
    p->set_read_only();
    return p;
}


// convert(this, get_wparam(), lo)
template<class type, class reinterpret_as, class do_conversion>
inline converter_top * convert(type & val, const reinterpret_as&, const do_conversion&) {
    return new simple_convert<type,reinterpret_as,do_conversion>( val);
}

template<class type, class reinterpret_as, class do_conversion>
inline converter_top * convert(egui::ev::read_only<type> & ro_val, const reinterpret_as&, const do_conversion&) {
    type & val = access_read_only_object(ro_val);
    converter_top* p = new simple_convert<type,reinterpret_as,do_conversion>( val);
    p->set_read_only();
    return p;
}



}}}

#endif

