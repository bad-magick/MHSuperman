// controls_checkbox.hpp

// Easy GUI Library
//
// Copyright (C) 2008 John Torjo (see http://torjo.com/contact/ for email)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.
//
// You can find the latest version of this library at http://www.torjo.com/egui/


#ifndef JT07022008_controls_checkbox_HPP_DEFINED
#define JT07022008_controls_checkbox_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#include "egui/controls/button.hpp"

namespace egui { 

namespace types {
    struct check_box_state {
        enum type {
            checked = 1, 
            unchecked = 0, 
            // intemediate (it's not checked and it's not unchecked)
            intermediate = 2
        };
    };
}

namespace ctrl {

struct check_box : button {

    check_box();
    ~check_box();
    static types::int64 default_style() ;

/** 
get/set the state of a checkbox
*/
property::rw<types::check_box_state::type, types::check_box_state> check_state;
/// get/set whether it's checked
property::rw<bool> checked;

private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
};

}}

#endif

