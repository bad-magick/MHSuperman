// form_event.hpp

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


#ifndef JT07022008_form_event_HPP_DEFINED
#define JT07022008_form_event_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace egui {

template<class form> struct form_func_base {
    virtual ~form_func_base() {}
    virtual void call(ev::base &) = 0;
};

template<class form, class event, class sender> struct form_func : form_func_base<form> {
    typedef void (form::*func)(event&, sender);

    form * self;
    func f;

    form_func(form * self, func f) : self(self), f(f) {}
    virtual void call(ev::base & evt) {
        event * real_evt = dynamic_cast<event*>(&evt);
        assert(real_evt);
        sender ignore;
        (self->*f)(*real_evt, ignore);
    }
};

}

#endif

