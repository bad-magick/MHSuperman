#pragma once
#include <time.h>

struct vc_project {
    vc_project() : last_rc_change(0), is_being_monitored(false) {}

    string vc_proj;
    string path;
    string rc_file;

    time_t last_rc_change;

    // where our templates are
    string path_to_templates;

    // if true, we're monitoring this ; otherwise, we're not
    bool is_being_monitored;
};

void update_project(vc_project & proj);
