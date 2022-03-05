// types_resource.hpp

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


#ifndef JT07022008_types_resource_HPP_DEFINED
#define JT07022008_types_resource_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once

    #ifndef BUIDING_EGUI
    #pragma comment ( lib, "comctl32.lib")
    #endif
#endif

#include <boost/shared_ptr.hpp>

namespace egui { namespace types {

struct resource_top {
    typedef void* id_type;

    struct id_holder {
        id_type id;
        bool owns;
        id_holder(id_type id, bool owns = false) : id(id), owns(owns) {}
    };
    typedef boost::function1<void,id_holder* > destroy_func;
    typedef boost::function1<id_type,id_type> clone_func;

    virtual ~resource_top();

protected:
    typedef boost::shared_ptr<id_holder> id_type_ptr;

    resource_top(destroy_func destroyer, clone_func cloner, id_type id = 0);
    resource_top(destroy_func destroyer, clone_func cloner, id_type_ptr id ); 

    // note: the copy-constructor does this = 2 objects share the same resource
    //       functions as a pointer

    // create a clone of the original object
    struct do_clone {};
    resource_top(const resource_top & other, const do_clone&) ;

    void set_id(id_type id) ;
    void set_cloned_id(id_type_ptr id) ;
    void set_owns(bool b) ;
    
public:
    id_type_ptr clone() const ;
    operator bool() const {
        return m_id && m_id.get();
    }
    bool operator!() const {
        bool b = *this;
        return !b;
    }

    id_type id() const { return m_id->id; }
    bool owns() const { return m_id->owns; }

protected:
    // this function can destroy a resorce given an ID
    destroy_func destroy_id;
    // this funciton can clone an existing resource
    clone_func clone_id;

    id_type_ptr m_id;
};

template<class self_type, class other_type, class base> struct resource : base {
    
    typedef typename base::id_type id_type;
    typedef typename base::id_type_ptr id_type_ptr;
    typedef typename base::do_clone do_clone;

protected:
    resource(id_type id = 0) : base(id) {}

    // note: default copy-constructor is ok

    resource(const other_type & other) : base( other, do_clone() ) {
    }

    resource(id_type_ptr p) : base(p) {}

public:
    void operator=(const resource& other) {
        base::set_cloned_id( other.clone() );
    }
};

}}

#endif

