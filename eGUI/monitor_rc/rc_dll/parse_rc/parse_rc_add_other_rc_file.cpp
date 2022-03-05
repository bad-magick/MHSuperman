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

#include "StdAfx.h"
#include ".\parse_rc_add_other_rc_file.h"
#include "util/string_util.h"
#include <assert.h>

/** 
    Parses this .rc file, and makes sure it also includes our internal .rc2 file
*/
void parse_rc_add_other_rc_file(const std::string & file_name) {
    const std::string TEXTINCLUDE_LINE = "\"#include \"\"win32gui_res/win32gui.rc2\"\"\\r\\n\"";
    const std::string INCLUDE_LINE = "#include \"win32gui_res/win32gui.rc2\"";

    const std::string INCLUDE_LINE_PREFIX = "#ifndef APSTUDIO_INVOKED\n";
    const std::string INCLUDE_LINE_SUFFIX = "\n#endif";
    // for MSVC - we need to add our #include within the "3 TEXTINCLUDE" line, or otherwise
    // it will be overwritten

    std::string textinclude_str;

    bool textinclude_line_already_exists = false;
    bool include_line_already_exists = false;

    bool inside_3_textinclude = false;
    std::ostringstream out;
    {
    std::ifstream in(file_name.c_str());
    std::string line;
    while ( std::getline(in, line) ) {
        if ( !inside_3_textinclude)
            out << line << std::endl;

        std::string original_line = line;
        line = locase(line);
        str_trim(line);

        if ( inside_3_textinclude) {
            if ( line == TEXTINCLUDE_LINE)
                textinclude_line_already_exists = true;
            textinclude_str += original_line + "\n";
        }

        if ( line == "3 textinclude")
            inside_3_textinclude = true;

        if ( line == "end") {
            if ( inside_3_textinclude) {
                // write our TEXTINCLUDE line, if necessary
                if ( textinclude_line_already_exists)
                    ; // already there
                else {
                    // we're including it now - as the first line in this block
                    std::istringstream textinclude_in(textinclude_str);
                    std::string ignore;
                    // first line is "BEGIN"
                    std::getline(textinclude_in, ignore);
                    assert(locase(ignore) == "begin");
                    std::ostringstream textinclude_out;
                    textinclude_out << "BEGIN\n" << TEXTINCLUDE_LINE << "\n" << textinclude_in.rdbuf() << "\n";
                    out << textinclude_out.str();
                }
            }
            inside_3_textinclude = false;
        }

        if ( line == INCLUDE_LINE)
            include_line_already_exists = true;
    }

    if ( include_line_already_exists)
        ; // we already have the include line...
    else
        out << "\n" << INCLUDE_LINE_PREFIX << INCLUDE_LINE << INCLUDE_LINE_SUFFIX << std::endl;
    } // close the file

    if ( textinclude_line_already_exists && include_line_already_exists)
        ; // nothing to do - the include lines already exist
    else {
        // rewrite the new file...
        std::ofstream new_file(file_name.c_str());
        new_file << out.str();
    }
}
