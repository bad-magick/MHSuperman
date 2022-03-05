// detail_get_item_ex.hpp

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


#ifndef JT07022008_detail_get_item_ex_HPP_DEFINED
#define JT07022008_detail_get_item_ex_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"

#ifndef BUILDING_EGUI
#error Donot include this in client code
#endif

namespace egui { namespace detail {

template<class type> void do_prepare_for_set(type & val, string & text, int text_size) {
    if ( !text.empty())
        val.pszText = &*text.begin();
    else
        val.pszText = GUI_STR("");
    val.cchTextMax = text_size;
};

template<class win32_raw> struct wrap_win32 {
    wrap_win32() {
        memset( &m_raw, 0, sizeof(m_raw));
    }

    void set_text(const string & txt) {
        m_text = txt;
        prepare_for_set();
    }

    // allow preparing for a SET message
    void prepare_for_set() {
        // append an ending zero if necessary. Some functions might want a null-terminated defs::string
        string::size_type text_size = m_text.size();
        if ( !m_text.empty() )
            if ( *m_text.rbegin() != 0)
                m_text.resize( m_text.size() + 1);

        do_prepare_for_set(m_raw, m_text, (int)text_size );
    }


    win32_raw m_raw;
    string m_text;
};

template<class result_type> void get_item_ex(
            result_type & result, const window_top * self, UINT msg, WPARAM wparam) {
    result.m_text.resize(256, ' ');

    string old;
do_again:
    result.m_raw.pszText = &*result.m_text.begin();
    result.m_raw.cchTextMax = (int)result.m_text.size();

    send_win32_event(self, msg, wparam, &result.m_raw);

    if ( result.m_raw.pszText != &*result.m_text.begin() )
        // the string is held elsewhere - just get it from there
        result.m_text = result.m_raw.pszText;
    else {
        // adjust the buffer...
        int idx = (int)result.m_text.find( GUI_STR('\0'));
        result.m_text.resize(idx);

        if ( old != result.m_text) {
            // not all the string was copied - try again
            old = result.m_text;
            result.m_text.resize( result.m_text.size() * 2, ' ');
            goto do_again;
        }
    }
}

}}

#endif

