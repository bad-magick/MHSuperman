// types_brush.hpp

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


#ifndef JT07022008_types_brush_HPP_DEFINED
#define JT07022008_types_brush_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace egui { namespace types {
struct brush;
struct temporary_brush ;

struct brush_style {
    enum type {
        solid = 0,
        null,
        hollow = null,
        hatched,
        pattern,
        indexed,
        dib_pattern,
        dib_pattern_pt,
        pattern_8x8,
        dib_pattern_8x8,
        mono_pattern
    };
};

struct sys_color {
    enum type {
    scroll_bar         = 0
    , background        
    , active_caption     
    , inactive_caption   
    , menu              
    , window            
    , window_frame       
    , menu_text          
    , window_text        
    , caption_text       
    , active_border      
    , inactive_border    
    , app_workspace      
    , highlight         
    , highlight_text     
    , button_face           
    , button_shadow         
    , gray_text          
    , button_text           
    , inactive_caption_text 
    , button_highlight      
    , _3d_dark_shadow 
    , _3d_light    
    , info_text   
    , info_bk     
    , hot_light          = 26
    , gradient_active_caption 
    , gradient_inactive_caption
    , menu_hilight       
    , menu_bar           
    };
};


struct brush_base : resource_top {
    typedef resource_top::id_type_ptr id_type_ptr;
    typedef resource_top::id_type id_type;
    typedef resource_top::do_clone do_clone;
protected:
    brush_base(id_type_ptr p) ;
    brush_base(id_type id = 0);
    template<class other> brush_base(const other & o, const do_clone& c) : resource_top(o, c) {}
public:

    types::color color() const ;
	void color(types::color cr) ;

    brush_style::type style() const;
    void style(brush_style::type s);

    static temporary_brush sys_color_brush(sys_color::type idx) ;
};

struct temporary_brush : resource<temporary_brush, brush, brush_base> {
    typedef resource<temporary_brush, brush, brush_base> base_type;
    temporary_brush(id_type id);
    temporary_brush(const brush& src);
};

struct brush : resource<brush, temporary_brush, brush_base> {
    typedef resource<brush, temporary_brush, brush_base> base_type;

    // always copying a resource object used by clients (i.e., not temporary), will clone the original object
    brush(const brush & other) : base_type( other.clone() ) {}

    brush(const temporary_brush & other);

    static temporary_brush solid_brush(types::color c);
};

}}

#endif

