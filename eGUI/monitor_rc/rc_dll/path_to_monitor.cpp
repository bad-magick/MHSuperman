#include "StdAfx.h"
#include "path_to_monitor.h"
#include "rc_monitor.h"

namespace {
    boost::shared_ptr<rc_monitor> monitor;
    string path_to_templates;
}

extern "C" {

RC_DLL_API void add_path_to_monitor(const char* vc_proj_path, const char* dir) {
    try {
        if ( !monitor)
            monitor = boost::shared_ptr<rc_monitor>(new rc_monitor);
        monitor->set_path_to_templates(path_to_templates);
        monitor->add_project(dir, vc_proj_path);
    }
    catch(...) {}
}
RC_DLL_API void del_path_to_monitor(const char* vc_proj_path, const char* dir) {
    try {
        if ( !monitor)
            return;
        monitor->del_project(dir, vc_proj_path);
    }
    catch(...) {}
}

}


void set_path_to_templates(const string& path) {
    path_to_templates = path;
}
