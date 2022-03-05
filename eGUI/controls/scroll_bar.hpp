// controls_scroll_bar.hpp

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


#ifndef JT07022008_controls_scroll_bar_HPP_DEFINED
#define JT07022008_controls_scroll_bar_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"

namespace egui { namespace ctrl {


struct scroll_bar : control_base, handle_events::scroll_bar {
//    using handle_events:: scroll_bar::events;
    scroll_bar();
    ~scroll_bar();
    static string class_name();
    static types::int64 default_style() ;

/// get/set scroll information
property::rw<types::scroll_info> scroll_info;
/// enable/disable itself
property::w<bool> enable;
/// show/hide itself
property::w<bool> show;

private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
};

}}

#endif

