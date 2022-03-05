#pragma once

#include "update_project.h"


/** 
    monitors .rc files
*/
class rc_monitor
{
public:
    rc_monitor(void);
    ~rc_monitor(void);

    void add_project(const std::string & vc_proj_path, const std::string & dir);
    void del_project(const std::string & vc_proj_path, const std::string & dir);

    void set_path_to_templates(const string& path);
private:
    void monitor_project(int idx);
private:
    critical_section cs;

    typedef std::vector<vc_project> vc_project_array;
    vc_project_array m_projects;


    // how much should we sleep in between monitoring
    int m_sleep_ms;
};
