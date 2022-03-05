#include "StdAfx.h"
#include "rc_monitor.h"
#include <boost/foreach.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <sys/types.h> 
#include <sys/stat.h>


rc_monitor::rc_monitor(void)
{
    using namespace boost;

    // at this time, we monitor at most 10 projects
    m_projects.resize(10);
    m_sleep_ms = 350;
    for ( int idx = 0; idx < (int)m_projects.size(); ++idx)
        thread t( bind( mem_fn( &rc_monitor::monitor_project), this, idx));

}

rc_monitor::~rc_monitor(void)
{
}

string find_rc_file(fs::path path) {
    for( fs::directory_iterator b(path), e; b != e; ++b)
        if ( fs::extension( *b) == ".rc")
            return b->string();
        else if ( fs::is_directory(*b)) {
            // search recursively
            string rc = find_rc_file( *b);
            if ( !rc.empty())
                return rc;
        }
    return string();
}


void rc_monitor::add_project(const std::string & vc_proj_path, const std::string & dir) {
    string rc_file = find_rc_file(dir);
    if ( rc_file.empty())
        return; // the project doesn't have resources

    // just in case we were already monitoring it
    del_project(vc_proj_path, dir);

    scoped_lock lk(cs);
    BOOST_FOREACH(vc_project & vc, m_projects)
        if ( !vc.is_being_monitored) {
            vc.is_being_monitored = true;
            vc.vc_proj = vc_proj_path;
            vc.path = dir;
            vc.rc_file = rc_file;
            return;
        }
}

void rc_monitor::del_project(const std::string & vc_proj_path, const std::string & dir) {
    scoped_lock lk(cs);
    BOOST_FOREACH(vc_project & vc, m_projects)
        if ( vc.vc_proj == vc_proj_path && vc.path == dir) 
            vc.is_being_monitored = false;
}

void rc_monitor::monitor_project(int idx) {
    while ( true ) {
        ::SleepEx( m_sleep_ms, true);
        vc_project proj;
        { scoped_lock lk(cs);
          proj = m_projects[idx];
        }
        if ( !proj.is_being_monitored)
            continue; // we're not monitoring anything

        struct _stat rc_info;
        _stat( proj.rc_file.c_str(), &rc_info);
        if ( rc_info.st_mtime > proj.last_rc_change) {
            update_project(proj);
            proj.last_rc_change = rc_info.st_mtime;
        }

        // update our info
        { scoped_lock lk(cs);
          if ( !m_projects[idx].is_being_monitored)
              // while we were updating the project, it just got canceled on us
              continue;
          m_projects[idx] = proj;
        }
    }
}

void rc_monitor::set_path_to_templates(const string& path) {
    scoped_lock lk(cs);
    BOOST_FOREACH(vc_project & vc, m_projects)
        vc.path_to_templates = path;
}
