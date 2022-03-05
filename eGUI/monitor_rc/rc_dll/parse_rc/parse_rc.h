
#ifndef PARSE_RC_HPP
#define PARSE_RC_HPP

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



struct rc_element_key {
    rc_element_key(const std::string & name, const std::string & type) : name(name), type(type) {}

    // the name of this element
    std::string name;
    // the type of this element. Note that the same name might appear for different types
    // (for instance, we might have an ID_user_name as an edit box, but also an ID_user_name
    //  as a string resource)
    //
    // note: the type is in lower-case (types are case-insensitive)
    std::string type;
};

bool operator<(const rc_element_key &first, const rc_element_key &second);



/*
    Represents a single element from an .rc file
*/
struct rc_element_value {
    typedef std::vector<rc_element_key> children_array;
    children_array children;
};




/*
    Represents information from an .RC file

    It knows control-to-dialog references as well
    (that is, which controls are sitted on which dialogs)
*/
struct rc_info {


    // for an element, information about it and its children
    typedef std::map<rc_element_key, rc_element_value> element_coll;
    element_coll m_elements;

    typedef std::set<std::string> set;
    // the dialogs defined for this resource
    set m_dialogs;

    // the menu items defined for this resource
    set m_menu_items;

    // the menus defined for this resource
    set m_menus;

    // other types of resources
    typedef std::map<std::string,set> resource_coll;
    resource_coll m_others;
};


rc_info parse_rc_file(const std::string & file_name);

void adjust_id_name_and_type(std::string&  name, std::string& type) ;
void adjust_id_name(std::string & name);



#endif
