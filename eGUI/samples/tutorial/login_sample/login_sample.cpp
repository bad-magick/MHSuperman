// login_sample.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "login.h"

using namespace egui;
void egui::main(const main_args&) {
    wnd<login>( new_( wnd_init().style(form_style::modal) ));
}

