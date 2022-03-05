// convert.h
#pragma once
#include "convert_form_resource.h"
struct convert :   form_resource::convert {
    convert() : rate(1.47), updating(false) {}
private:
    
    double rate;
    bool updating;

    void on_change(edit::ev::change&, usd_);
    void on_change(edit::ev::change&, eur_);
};
