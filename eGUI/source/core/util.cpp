// util.cpp

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
#include "egui/core/detail/util.hpp"
#include <algorithm>

namespace egui { namespace detail {

string lo_case(const string & str) {
    string result;
    result.resize( str.size());
    std::transform( str.begin(), str.end(), result.begin(), tolower);
    return result;
}

void str_replace( string & str, const string & find, const string & replace) {
    size_t pos = 0;
    while ( true) {
        size_t next = str.find( find, pos);
        if ( next == string::npos) 
            break;
        str.erase( next, find.length() );
        str.insert( next, replace);
        pos = next + replace.size();
    }
}

std::string narrow(const std::wstring & str)
{
  std::string result;
  result.assign( str.begin(), str.end());
  return result;
}
std::wstring widen(const std::string & str)
{
  std::wstring result;
  result.assign( str.begin(), str.end());
  return result;
}



}}



