// types_image_list.hpp

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


#ifndef JT07022008_types_image_list_HPP_DEFINED
#define JT07022008_types_image_list_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace egui { namespace types {
struct image_list;

struct image_list_base : resource_top {
    typedef resource_top::id_type_ptr id_type_ptr;
    typedef resource_top::id_type id_type;
    typedef resource_top::do_clone do_clone;
protected:
    image_list_base(id_type_ptr p) ;
    image_list_base(id_type id = 0);
    template<class other> image_list_base(const other & o, const do_clone& c) : resource_top(o, c) {}

public:
    void add_image(const temporary_bitmap & bmp);
    void add_image(const temporary_bitmap & bmp, const temporary_bitmap & mask);
    void add_image(const temporary_bitmap & bmp, color mask); 

    void copy(int from_idx, int to_idx);
    void swap(int src_idx, int dest_idx);
};

struct temporary_image_list : resource<temporary_image_list, image_list, image_list_base> {
    typedef resource<temporary_image_list, image_list, image_list_base> base_type;
    temporary_image_list(id_type id = 0);
    temporary_image_list(const image_list& src);
};

struct image_list : resource<image_list, temporary_image_list, image_list_base> {
    typedef resource<image_list, temporary_image_list, image_list_base> base_type;

    // always copying a resource object used by clients (i.e., not temporary), will clone the original object
    image_list(const image_list & other) : base_type( other.clone() ) {}

    image_list(const temporary_image_list & other);

    image_list(int cx, int cy, int initial_count = 10, int grow_by = 5) ;
    image_list(int id, int cx, int grow = 5, color c = color::invalid_ );
    image_list(const string & file_name, int cx, int grow = 5, color c = color::invalid_ );



};

}}

#endif

