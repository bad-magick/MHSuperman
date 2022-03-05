// types_font.hpp

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


#ifndef JT07022008_types_font_HPP_DEFINED
#define JT07022008_types_font_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace egui { namespace types {
struct font;

struct font_weight {
    enum type {
        dont_care = 0,
        thin = 100,
        extra_light = 200,
        light = 300,
        normal = 400,
        medium = 500,
        semi_bold = 600,
        bold = 700,
        extra_bold = 800,
        heavy = 900
    };
};

struct font_base : resource_top {
    typedef resource_top::id_type_ptr id_type_ptr;
    typedef resource_top::id_type id_type;
    typedef resource_top::do_clone do_clone;

    struct info_type {
        info_type(const string & name = string(), int height = 12);
        string name;
        int height;
        font_weight::type weight;
        bool italic;
        bool underline;
        bool strike_out;
        int width;
        int quality;
        int output_precision;
        int clip_precision;
        /// Specifies the angle, in tenths of degrees, between the escapement vector and the x-axis of the device. The escapement vector is parallel to the base line of a row of text. 
        int escapement;
        /// Specifies the angle, in tenths of degrees, between each character's base line and the x-axis of the device. 
        int orientation;
        int charset;
        int pitch_and_family;

        /** 
        - > 0 	Windows transforms this value into device units and matches it against the cell height of the available fonts.
        - 0 	Windows uses a default height value when it searches for a match.
        - < 0 	Windows transforms this value into device units and matches its absolute value against the character height of the available fonts.        */
        void height_in_points(int point_height);

        bool bold() const;
        void bold(bool b);
    };
protected:
    font_base(id_type_ptr p) ;
    font_base(id_type id = 0);
    template<class other> font_base(const other & o, const do_clone& c) : resource_top(o, c) {}

public:
    info_type info() const;
    void info(const info_type & inf);

private:
    void create(const info_type& font_info);
    void recreate(void * logfont);
};

struct temporary_font : resource<temporary_font, font, font_base> {
    typedef resource<temporary_font, font, font_base> base_type;
    temporary_font(id_type id = 0);
    temporary_font(const font& src);
};

struct font : resource<font, temporary_font, font_base> {
    typedef resource<font, temporary_font, font_base> base_type;

    // always copying a resource object used by clients (i.e., not temporary), will clone the original object
    font(const font & other) : base_type( other.clone() ) {}

    font(const temporary_font & other);
    font( font_base::info_type fnt_info);
};

}}

#endif

