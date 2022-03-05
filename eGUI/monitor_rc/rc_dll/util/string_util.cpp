
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
#include "stdafx.h"
#include ".\string_util.h"
#include <ctype.h>
#include <algorithm>

/*
#include <boost/string_algo.hpp>

void replace( std::string & str, const char * find, const char * replace) {
boost::replace_range( str, boost::make_range(find, find + strlen(find)),
boost::make_range(replace, replace + strlen(replace)) );
}
*/

void str_replace( std::string & str, const std::string & find, const std::string & replace) {
    std::string::size_type pos = 0;
    while ( true) {
        std::string::size_type next = str.find( find, pos);
        if ( next == std::string::npos) break;
        str.erase( next, find.length() );
        str.insert( next, replace);
        pos = next + replace.size();
    }
}

std::string locase(const std::string & str) {
    std::string res = str;
    std::transform( res.begin(), res.end(), res.begin(), tolower);
    return res;
}

// trims leading and trailing spaces
void str_trim(std::string & str) {
    std::string::iterator begin = str.begin(), end = str.end();
    while ( begin < end)
        if ( isspace(*begin)) ++begin;
        else break;

    while ( begin < end)
        if ( isspace(end[-1]) ) --end;
        else break;

    str = std::string(begin, end);
}

/*
std::string test_str_trim(const std::string & str) {
    std::string dest = str;
    str_trim(dest);
    return dest;
}

    assert( test_str_trim(" ab ") == "ab");
    assert( test_str_trim("  ") == "");
    assert( test_str_trim("ab ") == "ab");
    assert( test_str_trim("    ab    ") == "ab");
    assert( test_str_trim("   ab") == "ab");



*/

std::string trimmed(std::string s) {
    str_trim(s);
    return s;
}


