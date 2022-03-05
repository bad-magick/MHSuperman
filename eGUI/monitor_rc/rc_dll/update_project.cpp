#include "StdAfx.h"
#include "update_project.h"
#include "parse_rc/parse_rc.h"
#include "parse_rc/parse_resource_h.h"
#include "util/string_util.h"

namespace {
    /// information about the egui form's files
    struct egui_form_file {
        egui_form_file(
            const string & header, 
            const string & implementation,
            const string & form_id) : header(header), implementation_header(implementation), form_id(form_id) {}

        string header;
        string implementation_header;
        string form_id;
    };
    typedef std::vector<egui_form_file> egui_form_file_array;

    bool is_egui_form(fs::path path, string & form_id) {
        // convension:
        // all egui forms are in the type of:
        // <form>_form_resource.h 
        // and they also have a corresponding <form>_form_resource.h.hpp - which contains implementation of several functions
        string name = path.leaf();
        string::size_type pos = name.find("_form_resource.h");
        if ( pos != string::npos)
            if ( pos + strlen("_form_resource.h") == name.size() )
                if ( fs::exists(path.string() + ".hpp")) {
                    // first line syntax:
                    // "// form_id ...."
                    std::ifstream in(path.string().c_str());
                    string ignore;
                    form_id.clear();
                    in >> ignore >> form_id;
                    return !form_id.empty();
                }

        return false;
    }

    void find_egui_forms(egui_form_file_array & forms, fs::path path) {
        string form_id;
        for( fs::directory_iterator b(path), e; b != e; ++b)
            if ( is_egui_form( *b, form_id))
                forms.push_back( egui_form_file(b->string(), b->string() + ".hpp", form_id) );
            else if ( fs::is_directory(*b)) {
                // go recursively
                find_egui_forms( forms, *b);
            }
    }




    std::string resource_type_to_type(const std::string & type) {
        std::string word;
        { std::stringstream in(type);
          in >> word;
        }

        if ( word == "auto3state")              return "check_box";
        else if ( word == "autocheckbox")       return "check_box";
        else if ( word == "autoradiobutton")    return "radio_button";
        else if ( word == "checkbox")           return "check_box";
        else if ( word == "combobox")           return "combo_box";
        else if ( word == "control")            return "";
        else if ( word == "ctext")              return "label";
        else if ( word == "defpushbutton")      return "button";
        else if ( word == "edittext")           return "edit";
        else if ( word == "groupbox")           return "group_box";
        else if ( word == "icon")               return "label";
        else if ( word == "listbox")            return "list_box";
        else if ( word == "ltext")              return "label";
        else if ( word == "pushbox")            return "check_box";
        else if ( word == "pushbutton")         return "button";
        else if ( word == "radiobutton")        return "radio_button";
        else if ( word == "rtext")              return "label";
        else if ( word == "scrollbar")          return "scroll_bar";
        else if ( word == "state3")             return "check_box";

        else if ( word == "control/button")                 {
            if ( type.find("checkbox") != std::string::npos)
                return "check_box";
            else if ( type.find("radiobutton") != std::string::npos)
                return "radio_button";
            return "button";
        }
        else if ( word == "control/edit") {
            if ( type.find("es_multiline") )
                return "multi_edit";
            return "edit";
        }
        else if ( word == "control/static")                 {
            return "label";
        }
        else if ( word == "control/sysdatetimepick32")      return "date_time";
        else if ( word == "control/sysmonthcal32")          return "month_cal";
        else if ( word == "control/sysanimate32")           return "animate_ctrl";
        else if ( word == "control/msctls_progress32")      return "progress_bar";
        else if ( word == "control/msctls_trackbar32")      return "slider";
        else if ( word == "control/msctls_updown32")        return "spin_button";
        else if ( word == "control/scrollbar")              return "scroll_bar";
        else if ( word == "control/systabcontrol32")        return "tab";
        else if ( word == "control/combobox")               return "combo_box";
        else if ( word == "control/listbox")                return "list_box";
        else if ( word == "control/systreeview32")          return "tree_ctrl";
        else if ( word == "control/sysheader32")            return "header_ctrl";
        else if ( word == "control/rebarwindow32")          return "rebar";
        else if ( word == "control/toolbarwindow32")        return "toolbar";
        else if ( word == "control/msctls_statusbar32")     return "status_bar";
        else if ( word == "control/syslistview32")          return "list_ctrl";
//        else if ( word.find("control/richedit") == 0)       return "rich_edit";
        else
            return ""; // could be an activeX???
    }
    string id_to_name(string id) {
        if ( id.size() < 3) 
            return locase(id);
        if ( id[0] == 'I' && id[1] == 'D') {
            // ID*
            if ( isupper(id[2]) && id.size() > 3 && id[3] == '_')
                // ID_*
                id = id.substr(4);
            else
                // ID* (like, IDOK, IDCANCEL, etc)
                id = id.substr(2);
        }
        id = locase(id);    
        return id;
    }



    struct control {
        string name;
        string type;
        string id;
    };

    /// information about what an egui form should contain
    struct egui_form_info {
        egui_form_info() : file("","","") {}
        egui_form_file file;

        typedef std::set<std::string> string_set;
        string_set control_types;

        typedef std::vector<control> control_array;
        control_array controls;
    };

    typedef std::vector<string> event_array;
    typedef std::map<string, event_array > event_coll;

    void load_events(event_coll & events, fs::path path) {
        std::ifstream in(path.string().c_str());
        std::string line;
        while ( std::getline(in, line)) {
            line = trimmed(line);
            if ( line.empty())
                continue;
            // each line:
            // <ctrl> <event1> <event2> ...
            std::istringstream line_in(line);
            string word;
            line_in >> word;
            event_array & ctrl_events = events[word];
            while ( line_in >> word)
                ctrl_events.push_back(word);
        }
    }

    string adjust_ctrl_id(const string & id) {
        // these are defined in windows.h
        if ( id == "IDOK") return "1";
        if ( id == "IDCANCEL") return "2";
        if ( id == "IDABORT") return "3";
        if ( id == "IDRETRY") return "4";
        if ( id == "IDIGNORE") return "5";
        if ( id == "IDYES") return "6";
        if ( id == "IDNO") return "7";
        if ( id == "IDCLOSE") return "8";
        if ( id == "IDHELP") return "9";
        if ( id == "IDTRYAGAIN") return "10";
        if ( id == "IDCONTINUE") return "11";
        if ( id == "IDTIMEOUT") return "32000";
        //if ( id == "") return "";

        return id;
    }

    void fill_egui_form_info(const rc_info & rc, const egui_form_file & form, egui_form_info & info) {
        info = egui_form_info();
        info.file = form;

        // resolve IDs
        rc_element_value rc_value = rc.m_elements.find( rc_element_key(form.form_id,"dialog") )->second;
        typedef rc_element_value::children_array array;
        for(array::const_iterator b = rc_value.children.begin(), e = rc_value.children.end() ; b != e; ++b) {
            if ( b->name == "IDC_STATIC")
                continue;
            if ( b->type.empty())
                continue;
            if ( b->name.empty())
                continue;
            if ( isdigit(b->name[0]))
                continue; // resource through fixed number

            control ctrl;
            ctrl.id = b->name;
            ctrl.type = resource_type_to_type(b->type);
            if ( ctrl.type.empty())
                continue;
            ctrl.name = id_to_name( ctrl.id);
            ctrl.id = adjust_ctrl_id(ctrl.id);
            info.controls.push_back(ctrl);
        }

        BOOST_FOREACH(const control & ctrl, info.controls)
            info.control_types.insert( ctrl.type);
    }

    void create_form_header(const egui_form_info & info, const event_coll & events, const string & file_template, string & text) {
        string includes;
        BOOST_FOREACH(string type, info.control_types)
            includes += "\n#include <egui/controls/" + type + ".hpp>";

        string ctrl_classes;
        BOOST_FOREACH(const control & ctrl, info.controls)
            ctrl_classes += "\nstruct " + ctrl.name + "_ {};";

        string notifications;
        BOOST_FOREACH(const control & ctrl, info.controls) {
            event_coll::const_iterator found = events.find( ctrl.type);
            if ( found != events.end()) 
                BOOST_FOREACH(const string & evt, found->second) 
                    notifications += "\nvirtual void on_" + evt + "(" + ctrl.type + "::ev::" + evt + "&, " + ctrl.name + "_) {}";
        }

        string declarations;
        BOOST_FOREACH(const control & ctrl, info.controls) 
            declarations += "\nwnd<" + ctrl.type + "> " + ctrl.name + ";";

        string form_name;
        form_name = fs::path(info.file.header).leaf();
        str_replace(form_name, "_form_resource.h", "");

        text = file_template;
        str_replace(text, "$control_includes$", includes);
        str_replace(text, "$form$", form_name );
        str_replace(text, "$form_id$", info.file.form_id );
        str_replace(text, "$control_classes$", ctrl_classes);
        str_replace(text, "$notifications$", notifications);
        str_replace(text, "$control_declarations$", declarations);
    }
    void create_form_impl_header(const egui_form_info & info, const event_coll & events, const string & file_template, string & text) {
        string form_name;
        form_name = fs::path(info.file.header).leaf();
        str_replace(form_name, "_form_resource.h", "");

        string ctrl_mappings;
        BOOST_FOREACH(const control & ctrl, info.controls) 
            ctrl_mappings += "\n" + ctrl.name + " = wnd_cast<" + ctrl.type + ">( child_by_id(" + ctrl.id + "));";

        string event_mappings;
        BOOST_FOREACH(const control & ctrl, info.controls) {
            event_mappings += "\n{ type_to_event_coll & notif = m_notifications[ " + ctrl.name + "];" ;
            event_coll::const_iterator found = events.find( ctrl.type);
            if ( found != events.end()) 
                BOOST_FOREACH(const string & evt, found->second) {
                   event_mappings += "\n  { egui::form_func<" + form_name + "," + ctrl.type + "::ev::" + evt + "," + ctrl.name + "_>::func f = &" + form_name + "::on_" + evt + ";";
                   event_mappings += "\n    egui::form_func<" + form_name + "," + ctrl.type + "::ev::" + evt + "," + ctrl.name 
                       + "_> * func = new egui::form_func<" + form_name + "," + ctrl.type + "::ev::" + evt + "," + ctrl.name + "_>(this,f); \n";
                   event_mappings += "\n    notif[ typeid(" + ctrl.type + "::ev::" + evt + ") ] = form_func_ptr(func); }";
                }
            event_mappings += "} \n";
        }

        text = file_template;
        str_replace(text, "$form$", form_name );
        str_replace(text, "$form_id$", info.file.form_id );
        str_replace(text, "$control_mappings$", ctrl_mappings);
        str_replace(text, "$event_mappings$", event_mappings);
    }

    void load_file(string & templ, fs::path path) {
        std::ifstream in( path.string().c_str());
        std::ostringstream out;
        in >> out.rdbuf();
        templ = out.str();
    }
}

void update_project(vc_project & proj) {
    egui_form_file_array forms;
    find_egui_forms(forms, proj.path);

    if ( forms.empty())
        // no eGUI forms yet
        return;

    event_coll events ;
    load_events( events, fs::path(proj.path_to_templates) / "events.egui.hpp");
    rc_info rc = parse_rc_file( proj.rc_file);

    string header_template, impl_template;
    load_file(header_template, fs::path(proj.path_to_templates) / "form.egui.hpp");
    load_file(impl_template, fs::path(proj.path_to_templates) / "form_impl.egui.hpp");

    BOOST_FOREACH(const egui_form_file & form, forms) {
        egui_form_info info;
        fill_egui_form_info(rc, form, info);

        string header_text, impl_text;
        create_form_header(info, events, header_template, header_text);
        create_form_impl_header(info, events, impl_template, impl_text);

        string old_header_text, old_impl_text;
        load_file(old_header_text, form.header);
        load_file(old_impl_text, form.implementation_header);

        if ( header_text != old_header_text) {
            std::ofstream out( form.header.c_str());
            out << header_text;
        }
        if ( impl_text != old_impl_text) {
            std::ofstream out( form.implementation_header.c_str());
            out << impl_text;
        }
    }
}


