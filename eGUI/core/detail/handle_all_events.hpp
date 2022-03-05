// handle_all_events.hpp

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


#ifndef JT07022008_handle_all_events_HPP_DEFINED
#define JT07022008_handle_all_events_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef BUILDING_EGUI
#error Donot include this in client code
#endif

#include "egui/core/wnd.hpp"

namespace egui { namespace detail {

void subclass_window( window_top *w );
void unsubclass_window( window_top *w );

LRESULT CALLBACK createdestroy_hook(int code, WPARAM wParam, LPARAM lParam) ;
LRESULT CALLBACK get_message_hook(int code, WPARAM wParam, LPARAM lParam) ;


}}

#endif

