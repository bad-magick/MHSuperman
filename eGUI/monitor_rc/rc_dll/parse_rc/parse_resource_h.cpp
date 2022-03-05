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
#include ".\parse_resource_h.h"
#include "util/c_syntax_util.h"
#include "util/string_util.h"


resource_h_info parse_resource_h_file(const std::string & file_name) {
    // read the file
    std::string body;
    { std::ifstream file( file_name.c_str() );
      std::ostringstream out;
      out << file.rdbuf();
      body = out.str();
    }
    remove_c_comments( body);

    std::istringstream resource_h(body);
    std::string line;

    resource_h_info res_info;
    while ( std::getline(resource_h, line) ) {
        str_trim(line);
        std::istringstream line_in(line);
        std::string command;
        line_in >> command;
        if ( command == "#define") {
            // it's an ID...
            std::string name, value;
            line_in >> name;
            // the rest of the line is the value
            std::getline(line_in, value);
            str_trim( value); 

            res_info.m_name_to_value[name] = value;
            res_info.m_value_to_name[value] = name;
        }
    }

    return res_info;
}

bool operator==(const resource_h_info & a, const resource_h_info & b) {
    return a.m_name_to_value == b.m_name_to_value &&
        a.m_value_to_name == b.m_value_to_name;
}

namespace {
    void add_corresp(name_to_value_coll & name_to_value, value_to_name_coll & value_to_name, const std::string & name, const std::string & value) {
        name_to_value[name] = value;
        value_to_name[value] = name;

    }
}

resource_h_info ::resource_h_info () {
    add_corresp(m_name_to_value, m_value_to_name, "IDOK" , "1");
    add_corresp(m_name_to_value, m_value_to_name, "IDCANCEL" , "2");
    add_corresp(m_name_to_value, m_value_to_name, "IDABORT" , "3");
    add_corresp(m_name_to_value, m_value_to_name, "IDRETRY" , "4");
    add_corresp(m_name_to_value, m_value_to_name, "IDIGNORE" , "5");
    add_corresp(m_name_to_value, m_value_to_name, "IDYES" , "6");
    add_corresp(m_name_to_value, m_value_to_name, "IDNO" , "7");
    add_corresp(m_name_to_value, m_value_to_name, "IDCLOSE" , "8");
    add_corresp(m_name_to_value, m_value_to_name, "IDHELP" , "9");
    add_corresp(m_name_to_value, m_value_to_name, "IDTRYAGAIN" , "10");
    add_corresp(m_name_to_value, m_value_to_name, "IDCONTINUE" , "11");
    add_corresp(m_name_to_value, m_value_to_name, "IDTIMEOUT" , "32000");
}


