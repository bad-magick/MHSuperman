// controls_multi_edit.hpp

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


#ifndef JT07022008_controls_multi_edit_HPP_DEFINED
#define JT07022008_controls_multi_edit_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#include "egui/controls/edit.hpp"

namespace egui { namespace ctrl {

struct multi_edit : edit, handle_events::multi_edit {
//    using handle_events:: multi_edit::events;
    multi_edit();
    ~multi_edit();
    static string class_name();
    static types::int64 default_style() ;

	void fmt_lines(bool add_soft_enters);
	int  line_length(int line_idx) const;
	string line(int line_idx) const;

    property::r<int> line_count;

	int  line_from_char(int char_idx) const;
	int  line_index(int idx) const;

	void scroll(int horiz_chars, int vert_lines);
	void scroll_vert(int lines);


private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
    copy_events<window_top> m_copy_events;
};

}}

#endif

