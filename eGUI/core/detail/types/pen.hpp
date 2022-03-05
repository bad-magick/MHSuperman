// types_pen.hpp

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


#ifndef JT07022008_types_pen_HPP_DEFINED
#define JT07022008_types_pen_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace egui { namespace types {
struct pen;

struct pen_style {
    enum type {
        solid = 0,
        dash,
        dot,
        dash_dot,
        dash_dot_dot,
        null,
        inside_frame
    };
};

struct pen_base : resource_top {
    typedef resource_top::id_type_ptr id_type_ptr;
    typedef resource_top::id_type id_type;
    typedef resource_top::do_clone do_clone;
protected:
    pen_base(id_type_ptr p) ;
    pen_base(id_type id = 0);
    template<class other> pen_base(const other & o, const do_clone& c) : resource_top(o, c) {}
};

struct temporary_pen : resource<temporary_pen, pen, pen_base> {
    typedef resource<temporary_pen, pen, pen_base> base_type;
    temporary_pen(id_type id);
    temporary_pen(const pen& src);
};

struct pen : resource<pen, temporary_pen, pen_base> {
    typedef resource<pen, temporary_pen, pen_base> base_type;

    // always copying a resource object used by clients (i.e., not temporary), will clone the original object
    pen(const pen & other) : base_type( other.clone() ) {}

    pen(const temporary_pen & other);

    pen(color c, int width = 1, pen_style::type style = pen_style::solid);
};

}}

#endif

