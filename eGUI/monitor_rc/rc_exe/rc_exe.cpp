// rc_exe.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "rc_exe.h"
#include "path_to_monitor.h"
using namespace egui;

string find_vc_project(fs::path path) {
    for( fs::directory_iterator b(path), e; b != e; ++b)
        if ( fs::extension( *b) == ".vcproj")
            return b->string();
    return string();
}

struct monitor : form {
    static int form_id() { return IDD_monitor; }

    void add_project(const string & path, const string & vcproj) {
        add_path_to_monitor(path.c_str(), vcproj.c_str());

        wnd<list> l = wnd_cast<list>(child_by_id(IDC_monitor_list));
        list_item it;
        it.text = path;
        l->insert_item( it, 0);
    }



    void on_create() {
        wnd<list> l = wnd_cast<list>(child_by_id(IDC_monitor_list));
        list_column col;
        col.width = 200;
        col.text = "Paths to vcproj";
        l->insert_col( col, -1);

        string path = fs::system_complete(".").string();
        string vcproj = find_vc_project(path);
        if ( !vcproj.empty())
            add_project(path, vcproj);
    }

    void on_notify(ev::notify &ev) {
        button::ev::clicked * click = dynamic_cast<button::ev::clicked*>(&ev);
        if ( !click)
            return;
        if ( click->sender == child_by_id(IDC_add)) {
            string path = child_by_id(IDC_path)->text;
            string vcproj = find_vc_project(path);
            if ( vcproj.empty())
                return; // this is not a path to a vcproj

            add_project(path, vcproj);
        }
    }
};


void egui::main(const main_args&) {
    wnd<> w = new_<monitor>();
    w->wait_for( ev::destroy() );
}