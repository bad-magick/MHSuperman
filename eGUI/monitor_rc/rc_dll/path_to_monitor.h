#pragma once

#include "rc_dll.h"

extern "C" {
RC_DLL_API void add_path_to_monitor(const char* vc_proj_path, const char* dir);
RC_DLL_API void del_path_to_monitor(const char* vc_proj_path, const char* dir);
}


void set_path_to_templates(const std::string& path);

