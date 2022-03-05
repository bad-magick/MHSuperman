// form.hpp

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


#ifndef JT07022008_form_HPP_DEFINED
#define JT07022008_form_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/core/detail/window_base.hpp"

namespace egui {

namespace types {
    struct form_style {
        static const int64 modal = 1 << 31;
    };
}

/** Represents a form
*/
struct form : window_base {
    form();
    void on_initialize();

    static string class_name();
    static types::int64 default_style() ;
protected:
    virtual void on_child_notify(ev::notify&);
public:

    /// returns the number of children
    int child_count() const ;

    /// returns the child at given index (note: pretty inefficient; you should prefer child_by_id)
    wnd<> child(int idx) const ;
    /// returns the child having this ID
    wnd<> child_by_id(int id) const ;

    /// returns the child at given index (note: pretty inefficient; you should prefer child_by_id) or null if not found
    wnd<> try_child(int idx) const ;
    /// returns the child having this ID or null if not found
    wnd<> try_child_by_id(int id) const ;

    /// adds a child control
    template<class wnd_type, class new_> void add_child( new_ args) {
        args.init.parent( this);
        wnd<wnd_type> w(args);
        w;
    }
    template<class new_> void add_child( new_ args) {
        args.init.parent( this);
        wnd<> w(args);
        w;
    }

    void end_dialog(const wnd<> & ctrl = wnd<>() );

    // FIXME this should be a property
    bool is_modal() const { return m_is_modal; }

private:
    bool m_is_modal;
};

typedef form dialog;


}

#endif

