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
#include ".\parse_rc.h"
#include "util/string_util.h"
#include "util/c_syntax_util.h"
#include <iomanip>

using boost::str_stream;
namespace {

    // removes the things we don't need - like comments, #includes, etc.
    void adjust_rc_body(std::string & str) {
        remove_c_comments(str);

        std::istringstream in(str);
        std::string line;
        bool inside_c_comment = false;
        typedef std::string::size_type size_type;

        int stringtable_idx = 0;
        int popup_idx = 0;
        std::string result;
        bool prepend_enter = true;
        while ( std::getline(in, line) ) {
            str_trim(line);

            // remove pre-processor lines
            if ( !line.empty() )
                if ( line[0] == '#') 
                    line.erase(); // ignore all pre-processor

            // handle old-style .RC files
            // those that use '{' or '}' instead of BEGIN/ END
            //
            // ... note: activeX controls are embodied in {}, like this:
            //CONTROL         "",IDC_PICTURECLIP1, "{27395F85-0C0C-101B-A3C9-08002B2F49FB}",WS_TABSTOP,....
            str_replace( line, "\"{", "[start-of-control]");
            str_replace( line, "}\"", "[end-of-control]");
            str_replace( line, "{", "\nBEGIN\n");
            str_replace( line, "}", "\nEND\n");
            str_replace( line, "[start-of-control]", "\"{");
            str_replace( line, "[end-of-control]", "}\"");



            // STRINGTABLE has a strange syntax - different from the rest of the statements
            // make sure all statements follow the same convention - easier to parse this way...
            if ( locase(line) == "stringtable")
                line = str_stream() << stringtable_idx++ << ' ' << line;

            // "POPUP" doesn't have an ID - provide one - so that it'll be easier for us to parse
            // and store internally ...
            { std::istringstream line_in(line);
            std::string first_word;
              line_in >> first_word;
              if ( locase(first_word) == "popup")
                  // we don't care about any "POPUP" attributes...
                  line = str_stream() << "popup \"whatever\" " << popup_idx++;
            }

            if ( !line.empty() ) {
                if ( prepend_enter)
                    result += '\n';
                // prepend space so - useful when concatenating multiple lines - we want to keep the words apart...
                result += ' ' + line;
            }

            // note: some attributes might span over multiple lines. Ignore them...
            // Example:
            // LTEXT             "sample_start Version 1.0",IDC_STATIC,49,10,119,8,
            //                   SS_NOPREFIX
            //
            // is this a broken-up line?
            prepend_enter = true;
            if ( !line.empty() ) {
                char end_of_line = *line.rbegin();
                bool is_end_of_string = end_of_line == '"' || end_of_line == '\'';
                bool is_ended_in_underscore = end_of_line == '_'; // it's simply a name, ending in underscore
                if ( ispunct(end_of_line) && !is_end_of_string && !is_ended_in_underscore)
                    prepend_enter = false;                
                // yes, another MS surprise - lines can also end in "NOT"...
                if ( line.size() > 3)
                    if ( locase(line.substr(line.size()-3)) == "not")
                        prepend_enter = false;
            }

        }
        str = result;
    }

}


bool operator<(const rc_element_key &first, const rc_element_key &second) {
    if ( first.name != second.name)
        return first.name < second.name;
    return first.type < second.type;
}


rc_info parse_rc_file(const std::string & file_name) {
    // read the file
    std::string body;
    { std::ifstream file( file_name.c_str() );
      std::ostringstream out;
      out << file.rdbuf();
      body = out.str();
    }

    adjust_rc_body(body);

    /*
    Notes:
        we assume the .rc file is valid. We don't do any checking....

        Also, throughout the program, we assume the .rc file loads the
        IDs from one file, called "resource.h"
    */

    /*
    Usual syntax:
        identifier STATEMENT [optional-parameters]
        [optional instructions]
        BEGIN
            [instructions]
        END


    For User-defined resource.
        nameID typeID filename
        nameID typeID   {      raw-data  }

    For STRINGTABLE - there are no extra params
        Inside - very simple "id string"

    */
    rc_info res_rc;
    // we allow these extra types of resources...
    res_rc.m_others["icon"];
    res_rc.m_others["bitmap"];

    // An identifier that has children might have multiple attributes associated with it
    // These attributes come before the body. If so, we ignore all these attributes - we don't need them...
    bool waiting_for_begin = false;
    std::istringstream rc(body);
    std::string line;
    // keep the scope(s) we're in (like, inside of a DIALOG, or a MENU, etc.
    std::vector<rc_element_key> scopes;

    // ... if true, we ignore a whole block (BEGIN to END)...
    bool ignore_block = false;

    int line_idx = 0; // the index of the line - only for debugging
    while ( std::getline(rc, line) ) {
        ++line_idx;
        str_trim(line);
        if ( line.empty() ) continue; // ignore empty lines...

#ifndef NDEBUG
        OutputDebugString( (str_stream() << "(" << (int)scopes.size() << " scopes) Line " << std::setw(4) << line_idx << ": " << line << "\n").c_str());
#endif
        if ( waiting_for_begin) {
            if ( locase(line) == "begin") 
                waiting_for_begin = false; // ok - we've found it...
            continue; // read up to the begin...
        }

        if ( scopes.empty() ) {
            // not within any scope...
            // Syntax: 
            // identifier-name IDENTIFIER-TYPE [optional parameters]
            // Example: "IDD_ABOUTBOX DIALOG  22, 17, 230, 75"
            std::istringstream line_in(line);
            std::string name, type;
            line_in >> name >> type;
            type = locase(type);
            if ( type == "dialog" || type == "dialogex" || type == "menu" || type == "menuex" || type == "designinfo" || type == "accelerators") {
                waiting_for_begin = true; // complex type... could have children

                // normalize - we don't care whethere it's dialog or dialogex, etc.
                if ( type == "dialogex") type = "dialog";
                if ( type == "menuex")   type = "menu";

                // ignores the whole VC guidelines shi*
                if ( type == "designinfo") 
                    ignore_block = true;

                scopes.push_back( rc_element_key(name,type) );
            }
            else {
                rc_info::resource_coll::iterator r_res = res_rc.m_others.find( type);
                if ( r_res != res_rc.m_others.end())
                    // another type of resource - for instance, an icon
                    r_res->second.insert(name);
            }

            // add this element...
            res_rc.m_elements[ rc_element_key(name,type) ] = rc_element_value();
        }
        else if (locase(line) == "begin") 
            // this can happen only for nested structures - such as "GUIDELINES DESIGNINFO"
            scopes.push_back( rc_element_key("{INVALID_NAME}","INVALID_TYPE") );
        else if (locase(line) == "end") {
            // remove last scope...
            if ( !scopes.empty() )
                scopes.erase( scopes.end() - 1);
            if ( scopes.empty())
                ignore_block = false; // block ended...
        }
        else {
            if ( ignore_block) 
                continue; // we're ignoring this block...

            // we are within a scope
            // Syntax:
            // IDENTIFIER-TYPE text, ID [etc.] OR
            // IDENTIFIER-TYPE ID [etc.]
            str_replace(line, ",", " ");
            // watch out for text
            std::string name, type;
            std::istringstream line_in(line);
            line_in >> type;
            type = locase(type);
            bool has_text = true;
            if ( type == "combobox" || type == "edittext" || type == "listbox"
                 || type == "scrollbar" // [v1.1.5] (win32gui) v1.6.5 - solved bug when dealing with custom scroll bars
                )
                has_text = false;
            if ( has_text) {
                // this identifier contains text as well. Ignore it...
                char ch = 0;
                line_in >> ch;
                if ( ch == 'L') // could be L"...."
                    line_in >> ch;
                // ... also, ignore double quotes 
                if ( ch == '"') {
                    while ( ch == '"') {
                        std::string ignore;
                        std::getline(line_in, ignore, '"');
                        // the last character we should be reading (other than quote) should be space.
                        ch = line_in.get();
                    }
                }
                else {
                    // the text is a constant (example: 'IDS_APPLICATION')
                    std::string ignore;
                    line_in >> ignore;
                    if ( type == "menuitem") {
                        std::istringstream line_copy(line);
                        std::string word;
                        line_copy >> word >> word;
                        if ( locase(word) == "separator")
                            continue; // ignore menu separators...
                    }
                }
                    
            } // has_text

            line_in >> name;

            if ( type == "control") {
                // find out the real type...
                line_in >> type;
                type = locase(type);
                if ( !type.empty() )
                    if ( type[0] == '"' && *type.rbegin() == '"')
                        type = "control/" + type.substr(1, type.size() - 2); // ignore leading and ending quote

                // don't we love M$?
                // even though "CHECKBOX", "RADIOBUTTON" are clearly documented, they're still using "CONTROL"...
                //
                // read the control attributes...
                std::string extra;
                std::string word, delim;
                line_in >> word;
                extra += " " + word ;
                while ( line_in >> delim >> word) {
                    if ( delim != "|") break;
                    extra += " " + word;
                }
                type += locase(extra);
            }

            assert ( !name.empty() && !type.empty() ); // should have read valid info...
            // add this sub-element...
            rc_element_key child(name, type);
            // ... and the link to its parent
            res_rc.m_elements[ child ] = rc_element_value();
            res_rc.m_elements[ scopes.back() ].children.push_back( child );
            if ( type == "popup") {
                // this can have children...
                scopes.push_back(child);
                waiting_for_begin = true;
            }
        }
    } // while

    // should have processed all scopes...
    assert( scopes.empty() );

    // find dialogs and menus...
    for ( rc_info::element_coll::iterator begin = res_rc.m_elements.begin(), end = res_rc.m_elements.end(); begin != end; ++begin)
        if ( begin->first.type == "dialog" )
            res_rc.m_dialogs.insert( begin->first.name);
        else if ( begin->first.type == "menuitem")
            res_rc.m_menu_items.insert( begin->first.name);
        else if ( begin->first.type == "menu")
            res_rc.m_menus.insert( begin->first.name);

    return res_rc;
}


// FIXME this might not be sufficient. There are other places where adjust_id_name is used alone (no type!!!)
void adjust_id_name_and_type(std::string&  name, std::string& type) {
    if ( name.find("_typeis_") != std::string::npos) {
        std::string::size_type idx = name.find("_typeis_");
        type = name.substr(idx + strlen("_typeis_"));
        str_replace(type, "__", "::"); // namespace
        name = name.substr(0, idx);
    }
    adjust_id_name(name);
}


namespace {
    void remove_prefix(const std::string &prefix, std::string & dest) {
        if (dest.find(prefix) == 0)
            dest = dest.substr( prefix.size() );
    }

    void resolve_predefined_name(std::string & name) {
        if ( name == "IDOK") name = "ok";
        else if ( name == "IDCANCEL") name = "cancel";
        else if ( name == "IDABORT") name = "abort";
        else if ( name == "IDRETRY") name = "retry";
        else if ( name == "IDIGNORE") name = "ignore";
        else if ( name == "IDYES") name = "yes";
        else if ( name == "IDNO") name = "no";
        else if ( name == "IDCLOSE") name = "close";
        else if ( name == "IDHELP") name = "help";
        else if ( name == "IDTRYAGAIN") name = "try_again";
        else if ( name == "IDCONTINUE") name = "continue";
        else if ( name == "IDTIMEOUT") name = "timeout";
    }

    // distant future - when implementing "Smart .RC Editor", we'll want to allow for dialog-dependent IDs
    void adjust_internal_name(std::string & name) {
        if ( name.find("_win32gui_internal_") != std::string::npos )
            name = name.substr( 0, name.find("_win32gui_internal_") );
    }
}

// adjusts the name of this ID 
void adjust_id_name(std::string & name) {
    remove_prefix("ID_", name);
    remove_prefix("IDC_", name);
    remove_prefix("IDR_", name);
    remove_prefix("IDI_", name);
    remove_prefix("IDA_", name);
    remove_prefix("IDS_", name);
    remove_prefix("IDB_", name);
    remove_prefix("IDD_", name);
    remove_prefix("IDH_", name);
    remove_prefix("IDV_", name);
    remove_prefix("IDM_", name);
    resolve_predefined_name(name);
    name = locase(name);
    adjust_internal_name(name);
}


