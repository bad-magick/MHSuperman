//////////////////////////////////////////////////////////////////////
// str_stream.h
#ifndef BOOST_STR_STREAM__HPP_JT_2003MAR04
#define BOOST_STR_STREAM__HPP_JT_2003MAR04

//  Copyright John Torjo 2003-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <sstream>
#include <iosfwd>

namespace boost {

namespace stream_detail {
    template< class char_type, class char_traits> struct as_c_str_res {
        typedef std::basic_string<char_type,char_traits> str_type;
        as_c_str_res( const str_type & str) { m_str = str; }
        operator const char_type*() const { return m_str.c_str(); }
    private:
        str_type m_str;
    };
}


// basic_str_stream - allow stream usage, and then conversion to string
template< class char_type, class char_traits = std::char_traits<char_type> > class basic_str_stream
{
    typedef std::basic_stringstream< char_type, char_traits> stringstream_type;
    typedef std::basic_string< char_type, char_traits> string_type;
    typedef stream_detail::as_c_str_res<char_type,char_traits> c_like_str_type;
public:
    // default construction
    basic_str_stream()
    {}

    // allow to_string like usage
    template< class type> basic_str_stream( const type & value) {
        *this << value;
    }

    stringstream_type & underlying_stream() const    { return m_out; }

    // implicit conversion
    operator string_type() const    { return m_out.str(); }

    // explicit conversion to string
    string_type str() const         { return m_out.str(); }
    // explicit conversion to C-like string
    c_like_str_type c_str() const   { return c_like_str_type( m_out.str() ); }
private:
    mutable stringstream_type m_out;

#ifndef NDEBUG
public:
    void recalculate_string() const
    { m_string = m_out.str(); }
private:
    mutable string_type m_string;
#endif
}; // class basic_str_stream

typedef basic_str_stream< char> str_stream;
typedef basic_str_stream< wchar_t> wstr_stream;

template< class char_type, class char_traits, class type>
inline const basic_str_stream< char_type, char_traits> & operator<< ( 
        const basic_str_stream< char_type, char_traits> & out, 
        const type & value)
{
    out.underlying_stream() << value;
#ifndef NDEBUG
    out.recalculate_string();
#endif
    return out;
}


// allow function IO manipulators
template< class char_type, class char_traits>
inline const basic_str_stream< char_type, char_traits> & operator<< ( 
        const basic_str_stream< char_type, char_traits> & out, 
        std::ios_base & (*func)( std::ios_base&) )
{
    func( out.underlying_stream());
    return out;
}

template< class char_type, class char_traits>
inline const basic_str_stream< char_type, char_traits> & operator<< ( 
        const basic_str_stream< char_type, char_traits> & out, 
        std::basic_ios< char_type, char_traits> & (*func)( std::basic_ios< char_type, char_traits> &) )
{
    func( out.underlying_stream());
    return out;
}

template< class char_type, class char_traits>
inline const basic_str_stream< char_type, char_traits> & operator<< ( 
        const basic_str_stream< char_type, char_traits> & out, 
        std::basic_ostream< char_type, char_traits> & (*func)( std::basic_ostream< char_type, char_traits> &) )
{
    func( out.underlying_stream());
    return out;
}


} // namespace boost

#endif
// End of file
