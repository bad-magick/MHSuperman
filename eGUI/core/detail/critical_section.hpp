#ifndef JOHN_TORJO_WIN32GUI_detail_critical_section
#define JOHN_TORJO_WIN32GUI_detail_critical_section

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// detail/critical_section.hpp

// Win32 GUI Generics library
//
// Copyright (C) 2004 John Torjo (john.code@torjo.com)
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
// To see the version you have now, read win32gui/version.txt
//
// You can find the latest version of this library at http://www.torjo.com/win32gui/

#include <memory>


namespace egui { 


class critical_section {
    // you are not allowed assign another object to this
    // we are talking about Critical Sections here
    critical_section & operator = ( const critical_section & Not_Implemented);
    // CHG john.torjo, 3/14/2003 - copy-construction is disabled
    critical_section( const critical_section & From);

public:
    critical_section() ;
    ~critical_section() ;
    void Lock() ;
    void Unlock() ;

private:
    struct impl;
    mutable std::auto_ptr<impl> m_impl;
};



/*
    allows automatic Locking/ Unlocking of a Resource,
    protected by a Critical Section:
*/
class scoped_lock
{
    // not implemented - see Usage!!!
    scoped_lock operator=( scoped_lock & Not_Implemented);
    scoped_lock( const scoped_lock & Not_Implemented);

public:
    scoped_lock( critical_section & csResource) : m_csResource( csResource) {
        m_csResource.Lock();
    }
    ~scoped_lock() {
        m_csResource.Unlock();
    }

private:
    // the Critical Section for this resource
    critical_section & m_csResource;
};

}


#endif // JOHN_TORJO_WIN32GUI_detail_critical_section
