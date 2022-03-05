// login.cpp
#include "stdafx.h"
#include "login.h"
#include "login_form_resource.h.hpp"

void login::on_clicked(button::ev::clicked&, ok_) {
    if ( passw->text.get() != string("secret") )
        msg_box<mb::ok>("Wrong password");
    else
        end_dialog();
}

