// building_library.hpp

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


#ifndef JT07022008_building_library_HPP_DEFINED
#define JT07022008_building_library_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef BUILDING_EGUI
#error Donot include this in client code
#endif

#include "egui/core/wnd.hpp"
#include <boost/bind.hpp>

#define EGUI_FROM_WIN32(e,w, p1, p2) e.p1 = w.p2
#define EGUI_TO_WIN32(e,w, p1, p2)  w.p2 = e.p1

// shorter version
#define E_TO_W(p1,p2) EGUI_TO_WIN32(egui,win32,p1,p2)
#define E_FROM_W(p1,p2) EGUI_FROM_WIN32(egui,win32,p1,p2)

namespace egui { namespace detail {

    // Property as member function (no args)

    template<class type, class impl_type, class result> void init_property(
            property_base::property_read<type> & prop, 
            impl_type * impl, result (impl_type::*func)() const ) {
        boost::function0<type> f = boost::bind( boost::mem_fn(func), impl);
        property_base::do_set_getter( prop, f );
    }

    template<class type, class impl_type, class result> void init_property(
            property_base::property_write<type> & prop, 
            impl_type * impl, void (impl_type::*func)(result) ) {
        boost::function1<void, const type& > f = boost::bind( boost::mem_fn(func), impl, _1);
        property_base::do_set_setter( prop, f );
    }

    template<class property_type, class impl_type, class result1, class result2> void init_property(
            property_type & prop, 
            impl_type * impl, 
            result1 (impl_type::*func1)() const, 
            void (impl_type::*func2)(result2)  ) {
        init_property(prop, impl, func1);
        init_property(prop, impl, func2);
    }

    // Property as global function (no args)

    template<class type, class result> void init_property(
            property_base::property_read<type> & prop, 
            result (*func)()  ) {
        boost::function0<type> f = func;
        property_base::do_set_getter( prop, f );
    }

    // Property as member function (one arg)
    template<class property_type, class impl_type, class arg, class result> void init_property(
            property_type & prop, 
            impl_type * impl, result (impl_type::*func)(arg) const ) {
        typedef typename property_type::value_type type;
        boost::function1<type,arg> f = boost::bind( boost::mem_fn(func), impl, _1);
        property_base::do_set_getter( prop, f );
    }

    template<class property_type, class impl_type, class arg1, class arg2> void init_property(
            property_type & prop, 
            impl_type * impl, void (impl_type::*func)(arg1,arg2) ) {
        typedef typename property_type::value_type type;
        boost::function2<void,arg1,const type& > f = boost::bind( boost::mem_fn(func), impl, _1, _2 );
        property_base::do_set_setter( prop, f );
    }

    template<class property_type, class impl_type, class arg1, class result1, class arg2, class arg3> void init_property(
            property_type & prop, 
            impl_type * impl, 
            result1 (impl_type::*func1)(arg1) const,
            void (impl_type::*func2)(arg2,arg3) ) {
        init_property(prop, impl, func1);
        init_property(prop, impl, func2);
    }


}}



#endif

