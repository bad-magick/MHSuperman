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
#include ".\c_syntax_util.h"
#include "string_util.h"

namespace {
    // returns the same index, if this is NOT within a C-like string (that is, within quotes)
    // otherwise, returns npos
    std::string::size_type ignore_if_within_string(const std::string & str, std::string::size_type n) {
        if ( n == std::string::npos) return n;

        assert ( n < str.size() ); // should be a valid index
        bool within_quote = false;
        for ( std::string::size_type i = 0; i < n; ++i)
            if ( str[i] == '"') 
                within_quote = !within_quote;

        return within_quote ? std::string::npos : n;
    }
}

// removes C and C++ comments
void remove_c_comments(std::string & str) {
    std::istringstream in(str);
    std::string line;
    bool inside_c_comment = false;
    typedef std::string::size_type size_type;

    int stringtable_idx = 0;
    int popup_idx = 0;
    std::string result;
    while ( std::getline(in, line) ) {
        str_trim(line);
        // remove C++ comment
        size_type cpp_comment = ignore_if_within_string(line, line.find("//") );
        if ( cpp_comment != std::string::npos)
            line = line.substr(0, cpp_comment);

        // remove C comments
        size_type c_comment_start = ignore_if_within_string(line, line.find("/*"));
        size_type c_comment_end = ignore_if_within_string(line, line.find("*/") );

        if ( c_comment_start != std::string::npos && c_comment_end != std::string::npos) 
            // the comment is within a line
            line = line.substr(0, c_comment_start) + line.substr(c_comment_end+2);
        else if ( c_comment_end != std::string::npos) {
            // the end of a comment
            line = line.substr(c_comment_end+2);
            inside_c_comment = false;
        }
        else if ( c_comment_start != std::string::npos) {
            // the beginning of a comment
            inside_c_comment = true;
            line = line.substr(0, c_comment_start);
        }
        else if ( inside_c_comment)
            line.erase(); // inside C comment - the whole line is ignored

        result += line + '\n';
    }
    str = result;
}
