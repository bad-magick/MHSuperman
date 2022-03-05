// types_icon.hpp

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


#ifndef JT07022008_types_icon_HPP_DEFINED
#define JT07022008_types_icon_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace egui { namespace types {
struct icon;

struct icon_base : resource_top {
    typedef resource_top::id_type_ptr id_type_ptr;
    typedef resource_top::id_type id_type;
    typedef resource_top::do_clone do_clone;
protected:
    icon_base(id_type_ptr p) ;
    icon_base(id_type id = 0);
    template<class other> icon_base(const other & o, const do_clone& c) : resource_top(o, c) {}
};

struct temporary_icon : resource<temporary_icon, icon, icon_base> {
    typedef resource<temporary_icon, icon, icon_base> base_type;
    temporary_icon(id_type id = 0);
    temporary_icon(const icon& src);
};

struct icon : resource<icon, temporary_icon, icon_base> {
    typedef resource<icon, temporary_icon, icon_base> base_type;

    // always copying a resource object used by clients (i.e., not temporary), will clone the original object
    icon(const icon & other) : base_type( other.clone() ) {}

    icon(int id);
    icon(int id, size desired_size);

    icon(const temporary_icon & other);
};

}}

#endif

