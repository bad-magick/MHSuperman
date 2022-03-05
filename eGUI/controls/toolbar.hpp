// controls_toolbar.hpp

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


#ifndef JT07022008_controls_toolbar_HPP_DEFINED
#define JT07022008_controls_toolbar_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"

namespace egui { 

namespace types {
}

namespace types {
    struct toolbar_button_state {
        enum type {
        };
    };
    struct toolbar_style {
        enum type {
            // FIXME - include extended styles as well ; example : TBSTYLE_EX_DRAWDDARROWS 
        };
    };
    struct toolbar_color_scheme {
        toolbar_color_scheme (color highlight, color shadow) : highlight(highlight), shadow(shadow) {}
        color highlight, shadow;
    };

    struct toolbar_button {
    };
}
    
namespace ctrl {

struct toolbar : control_base, handle_events::toolbar {
//    using handle_events:: toolbar::events;
    typedef types::toolbar_button button_type;
    typedef types::toolbar_button item_type;

    toolbar();
    ~toolbar();
    static string class_name();
    static types::int64 default_style() ;

/**
gets/sets the image list corresponding to this toolbar
*/
property::rw<temporary_image_list> images;

    // FIXME - this needs to be a toolbar_button class with properties like .enabled, .checked, etc

/**
gets/sets if the button having the given ID is enabled
*/
property_one_arg::rw<bool, int> button_enabled;
/**
gets/sets if the button having the given ID is checked
*/
property_one_arg::rw<bool, int> button_checked;
/**
gets/sets if the button having the given ID is pressed
*/
property_one_arg::rw<bool, int> button_pressed;
/**
gets/sets if the button having the given ID is visible
*/
property_one_arg::rw<bool, int> button_visible;
/**
gets/sets if the button having the given ID is indeterminate
*/
property_one_arg::rw<bool, int> button_indeterminate;
/**
get/set the button's state
*/
property_one_arg::rw<toolbar_button_state::type, int, toolbar_button_state> button_state;

/**
returns the number of items
*/
property::r<int> item_count;

/**
returns an item's bounding rectangle
*/
property_one_arg::r<rectangle, int> item_rect;

/**
gets/sets the buttons size
*/
property_one_arg::rw<size, int> button_size;
/**
Sets the size of the bitmapped images to be added to this control. 

The size can be set @b only before adding any bitmaps to the control. 
If an application does not explicitly set the bitmap size, the default size is 16 by 15 pixels
*/
property_one_arg::r<size, int> bitmap_size;

/// you can change the parent window 
property::w< wnd<> > parent_wnd;

/**
gets/sets the number of rows of buttons
*/
property::rw< int> row_count;
/**
gets/sets the toolbar-specific style */
property::rw<types::toolbar_style::type, types::toolbar_style> toolbar_style;

/**
returns a button's rectangle
*/
property_one_arg::r<rectangle, int> button_rect;
/**
returns the maximum number of text rows that can be displayed on a button
*/
property::r<int> text_rows;

/**
sets the min and max widths of buttons within a toolbar
*/
void button_width(int min_width, int max_width);
/**
sets the indentation for the first button.
*/
void indent(int val);
/**
sets the maximum number of text rows 
*/
void max_text_rows(int val);

/**
gets/sets the item that is "hot"
*/
property::rw<int> hot_item_sel;
/**
returns the total size of all of the visible buttons and separators in the control
*/
property::r<size> total_size;
/**
gets/sets the padding for the toolbar
*/
property::rw<size> padding;

/**
inserts an item
*/
void insert_button(const button_type & btn, int idx);
/**
deletes an item
*/
void del_button(int idx);

/**
converts an (command) ID into an index
*/
int id_to_index(int cmd_id) const;

/**
highlights/unhighlights a button
*/
property_one_arg::w<bool, int> highlight_button;
/**
moves an item
*/
void move_button(int old_idx, int new_idx);

property_one_arg::rw<types::toolbar_button, int, types::toolbar_button> button;

private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
};

}}

#endif

