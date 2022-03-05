// exception.hpp

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


#ifndef JT07022008_exception_HPP_DEFINED
#define JT07022008_exception_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <stdexcept>
#include "egui/core/detail/fwd.hpp"

namespace egui {

template<class char_type> struct exception_base {
    exception_base(const string & str) {}
};
template<> struct exception_base<char> : std::runtime_error {
    exception_base(const std::string & str) : std::runtime_error(str){}
};

struct exception : exception_base<char_> {
    exception(const string & str) : exception_base<char_>(str), m_str(str) {}
    // FIXME - allow for unicode
private:
    string m_str;
};

}

#endif

