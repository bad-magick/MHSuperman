// controls_edit.hpp

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


#ifndef JT07022008_controls_edit_HPP_DEFINED
#define JT07022008_controls_edit_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"
#ifndef BUILDING_EGUI
#include "egui/events/edit.hpp"
#endif

namespace egui { namespace ctrl {

struct edit : control_base, handle_events::edit {
    using handle_events:: edit::events;
    using handle_events:: edit::events_type;
    typedef handle_events::edit::ev ev;

    edit();
    ~edit();
    static string class_name();
    static types::int64 default_style() ;

	/** returns the zero-based index of the uppermost visible line in a multiline edit control */
    property::r<int> first_visible_line;

	/** retrns the character at the given position (position is in client coordinates) */
    int  char_from_pos(const point& pt) const;
	/** returns the line from the given position (position is in client coordinates) */
    int  line_from_pos(const point& pt) const;	
	/** returns the client area coordinates of a specified character (given its index) in an edit control */
    point pos_from_char(int char_idx) const;

	/** get/set the password character - in case this is a password edit control */
    property::rw<char_> password_char;

	/** replaces the selected text */
    void replace_sel(const string &str, bool allow_undo = true);
	/** scrolls to where the caret is */
    void scroll_caret();
	/** scrolls horizontally */
    void scroll_horiz(int chars);

	/** get/set if the edit is read-only */
    property::rw<bool> read_only;

	/** returns true if you can undo */
    property::r<bool> can_undo;

	/** empties the undo buffer */
    void empty_undo_buffer();
    void undo();
    void clear();
    void cut();
    void copy();
    void paste();

/** get/set the max. number of chars this edit control can hold */
property::rw<int> max_chars;

struct selection {
    int start, end;
    selection(int start = 0, int end = 0) : start(start), end(end) {}
};
/** get/set the current text selection
*/
property::rw<selection> sel;


private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
    copy_events<window_top> m_copy_events;
};

}}

#endif

