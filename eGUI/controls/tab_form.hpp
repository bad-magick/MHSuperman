// controls_tab_form.hpp

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


#ifndef JT07022008_controls_tab_form_HPP_DEFINED
#define JT07022008_controls_tab_form_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#include "egui/controls/tab.hpp"

namespace egui { namespace ctrl {

struct tab_form : tab, handle_events::tab_form {
//    using handle_events:: tab_form::events;
    tab_form();
    ~tab_form();
    static types::int64 default_style() ;

private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
};

}}

#endif

