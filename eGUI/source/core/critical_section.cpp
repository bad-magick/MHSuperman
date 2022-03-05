// critical_section.cpp

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

#include "stdafx_core.h"
#include "egui/core/detail/critical_section.hpp"


namespace egui {

struct critical_section::impl {
    CRITICAL_SECTION cs;
};

critical_section::critical_section() : m_impl(new impl) {
    InitializeCriticalSection( &(m_impl->cs) );
}

critical_section::~critical_section() {
    DeleteCriticalSection( &(m_impl->cs) );
}

void critical_section::Lock() {
    EnterCriticalSection( &(m_impl->cs) );
}

void critical_section::Unlock() {
    LeaveCriticalSection( &(m_impl->cs) );
}


}


