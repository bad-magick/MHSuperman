// convert.cpp
#include "stdafx.h"
#include "convert.h"
#include "convert_form_resource.h.hpp"
#include <sstream>
#include <iomanip>
namespace {
    double to_double(const string& str) {
        std::istringstream in(str);
        double result = 0;
        in >> result;
        return result;
    }

    string to_string(double d) {
        std::ostringstream out;
        out << std::setprecision(2) << std::fixed << d;
        return out.str();
    }
}

void convert::on_change(edit::ev::change&, usd_) {
    if ( updating) return;
    updating = true;
    eur->text = to_string( to_double(usd->text) / rate);
    updating = false;
}
void convert::on_change(edit::ev::change&, eur_) { 
    if ( updating) return;
    updating = true;
    usd->text = to_string( to_double(eur->text) * rate);
    updating = false;
}
