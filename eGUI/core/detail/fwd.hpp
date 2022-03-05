// fwd.hpp

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


#ifndef JT07022008_fwd_HPP_DEFINED
#define JT07022008_fwd_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once

#ifndef BUILDING_EGUI
    #ifndef NDEBUG
    //debug
    #ifdef UNICODE
    #pragma comment (lib, "egui_core_dbg_u.lib" )
    #else
    #pragma comment (lib, "egui_core_dbg.lib" )
    #endif

    #else
    //release
    #ifdef UNICODE
    #pragma comment (lib, "egui_core_u.lib" )
    #else
    #pragma comment (lib, "egui_core.lib" )
    #endif
    #endif
#endif

#include <typeinfo>


#pragma warning (disable : 4250) //C4250: 'egui::window_instance_t<base>' : inherits 'egui::form::egui::form::on_initialize' via dominance
#pragma warning (disable : 4584) //  base-class 'egui::window_base' is already a base-class of 'whatever'
#pragma warning (disable : 4355) //4355: 'this' : used in base member initializer list
//#pragma warning (disable : )
#endif

#include <string>
#include <boost/shared_ptr.hpp>
#include "egui/core/detail/critical_section.hpp"

#ifndef BOOST_FUNCTION_MAX_ARGS
#  define BOOST_FUNCTION_MAX_ARGS 2
#endif
#include <boost/function.hpp>


#define FORCE_CALL_BEFORE_MAIN( name ) \
    namespace detail_ { \
        void name (); \
    namespace { \
        struct initer ## name { \
            initer ## name () { name (); } \
        } s_init ## name ; \
    }}


namespace egui {

#ifdef UNICODE
    typedef wchar_t char_;
    typedef std::wstring string;
#define GUI_STR(x) L ## x
#else
    typedef char char_;
    typedef std::string string;
#define GUI_STR(x) x
#endif

typedef const void* wnd_id_type;

// when type isn't specified
struct void_ {};

// automatic conversion to any type
struct default_ {
    template<class type> operator type() const { return type(); }
};


template<class t> struct tag {};

struct window_base;
struct window_top;
template<class window = window_top> struct wnd ;

void add_module(void* module_name);
void add_module(const char_ * module_name);
void add_module(string module_name);



struct typeinfo_holder {
    typeinfo_holder (const std::type_info & val) : m_type_info(&val) {}

    bool operator ==(const typeinfo_holder & other) const {
        return (*m_type_info == *(other.m_type_info)) != 0;
    }
    bool operator <(const typeinfo_holder & other) const {
        return m_type_info->before( *(other.m_type_info) ) != 0;
    }
    bool operator !=(const typeinfo_holder & other) const {
        return !(*this == other);
    }
private:
    const std::type_info * m_type_info;
};



namespace ev { struct base; }

}

#include "egui/core/detail/event_handler.hpp"
#include "egui/core/detail/line_related.hpp"
#include "egui/core/detail/types.hpp"

#endif

