// log.cpp

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
#include "egui/core/detail/log.hpp"
#include "egui/core/detail/util.hpp"


namespace egui {

string type_name(const std::type_info & info) {
    string name = detail::to_string<string>( info.name() );
    string::size_type scope = name.find_last_of( GUI_STR(":"));
    if ( scope != string::npos)
        name = name.substr(scope + 1);
    if ( *name.rbegin() == GUI_STR('>') )
        name = name.substr(0, name.size() - 1);

    detail::str_replace(name, GUI_STR("window_instance_t<struct "), GUI_STR(""));
    return name;
}

string type_name(const window_top & w) {
    return type_name( typeid(w) );
}

string type_name(const ev::base & e) {
    return type_name( typeid(e) );
}

egui_stream::~egui_stream() {
    *this << std::endl;
    ::OutputDebugString( str().c_str() );
}
}

// End of file
