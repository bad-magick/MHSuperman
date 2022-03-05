// login.h
#pragma once
#include "login_form_resource.h"
struct login :   form_resource::login {

private:
    void on_clicked(button::ev::clicked&, ok_);
};
