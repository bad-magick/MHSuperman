// util.hpp

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


#ifndef JT07022008_util_HPP_DEFINED
#define JT07022008_util_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace egui { namespace detail {

string lo_case(const string & str);
void str_replace( string & str, const string & find, const string & replace) ;
std::wstring widen(const std::string & str);
std::string narrow(const std::wstring & str);

template<class dest> struct to_string_type {};
template<> struct to_string_type<std::wstring> {
  static const std::wstring & convert(const std::wstring& str) { return str; }
  static std::wstring convert(const std::string& str) { return widen(str); }
};

template<> struct to_string_type<std::string> {
  static const std::string & convert(const std::string& str) { return str; }
  static std::string convert(const std::wstring& str) { return narrow(str); }
};



/** 
  No matter what the source string is, we need it in the destination format.

  Example: to_string<std::wstring>("something");
*/
template<class dest, class src> inline dest to_string(const src & s) {
  return to_string_type<dest>::convert(s);
}



}}

#endif

