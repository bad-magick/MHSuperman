// controls_rebar.hpp

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


#ifndef JT07022008_controls_rebar_HPP_DEFINED
#define JT07022008_controls_rebar_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "egui/controls/detail/fwd.hpp"

namespace egui { 
    
namespace types {
    struct rebar_band {

    };

    struct rebar_color_scheme {
        rebar_color_scheme (color highlight = color(), color shadow = color()) : highlight(highlight), shadow(shadow) {}
        color highlight, shadow;
    };
}

namespace ctrl {

struct rebar : control_base, handle_events::rebar {
//    using handle_events::rebar ::events;
    typedef rebar_band item_type;
    typedef rebar_band band_type;

    rebar();
    ~rebar();
    static string class_name();
    static types::int64 default_style() ;

/** 
Retrieves the band borders of a given band (left border, right border, etc.)
*/
rectangle band_borders(int band_idx) const;

/** 
retrieves the number of bands this rebar has
*/
property::r<int> band_count;
/** 
returns the height of the rebar
*/
property::r<int> bar_height;

/** 
gets/sets the background color of the rebar
*/
property::rw<color> bg_color;
/** 
gets/sets the text color
*/
property::rw<color> text_color;

/** 
returns the bounding rectangle for a given band 
*/
property_one_arg::r<rectangle, int> band_rect;
/** 
returns the number of rows in a rebar (note that a row can contain multiple bars)
*/
property::r<int> row_count;
/** 
returns the height (in pixels) of a row in a rebar (note that a row can contain multiple bars)
*/
int row_height(int row_idx) const;

void insert_band(const types::rebar_band &band, int idx);
/** 
deletes a band from the rebar
*/
void del_band(int band_idx);

property::rw<types::rebar_band> band;

/** 
maximizes a band, so that it'll show everything it contains
*/
void maximize_band(int band_idx, bool to_ideal_size = true);
/** 
minimizes a band
*/
void minimize_band(int band_idx);
/** 
moves a band
*/
void move_band(int old_idx, int new_idx);

/** 
gest/sets the rebar's image list

Note:
usually you don't need this, since you sit one or more toolbars on a rebar.
*/
property::rw<temporary_image_list> images;

/// you can change the parent window 
property::w< wnd<> > parent_wnd;

/** 
shows or hides a given band
*/
property_one_arg::rw<bool, int> show_band;

/** 
tries to find the best layout of the bands for the given rectangle.

The bands will be arranged and wrapped as necessary to fit the rectangle.
*/
void size_to_rect(const rectangle &r);

/** 
gets/sets the color scheme (highlight color and shadow color) of the rebar
*/
property::rw<types::rebar_color_scheme> color_scheme;


private:
    struct impl;
    friend struct impl;
    boost::shared_ptr<impl> m_impl;
};


}}

#endif

