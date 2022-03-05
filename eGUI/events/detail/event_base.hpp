// event_base.hpp

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


#ifndef JT07022008_events_event_base_HPP_DEFINED
#define JT07022008_events_event_base_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace egui { namespace ev {

struct converter_top {
    converter_top() : m_base(0), m_read_only(false) {}

    virtual ~converter_top() {}
    virtual void init() {}
    virtual void exit() {}

    void set_base(base* b)      { m_base = b; }
    bool is_read_only() const   { return m_read_only; }
    void set_read_only()        { m_read_only = true; }
protected:
    base * m_base;
    bool m_read_only;
};

struct event_module_base : base {
    event_module_base() ;

    virtual void init_event();
    void before_handle();
    void after_handle();
protected:
    void add(converter_top* converter);

    typedef boost::shared_ptr<converter_top> converter_ptr;
    typedef std::vector<converter_ptr> converter_array;
    converter_array m_converters;

private:
    bool already_inited;
};


template<class type> struct read_only;
template<class type> inline type& access_read_only_object(read_only<type>& src);

template<class type> struct read_only {
    read_only() : m_val( type() ) {}

    const type & get() const { return m_val; }
    operator const type & () const { return m_val; }
    const type* operator->() const { return &m_val; }
private:
    template<class other_type> friend inline other_type& access_read_only_object(read_only<other_type>& src);
    type m_val;
};

template<class type> inline type& access_read_only_object(read_only<type>& src) {
    return src.m_val;
}


    
}}

#endif

