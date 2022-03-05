
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
#ifndef STRING_UTIL_H
#define STRING_UTIL_H


void str_replace( std::string & str, const std::string & find, const std::string & replace);
std::string locase(const std::string & str);

void str_trim(std::string & str);
std::string trimmed(std::string s);

#endif
