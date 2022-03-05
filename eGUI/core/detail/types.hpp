// types.hpp

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


#ifndef JT07022008_types_HPP_DEFINED
#define JT07022008_types_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/cstdint.hpp>
#include "egui/core/detail/types/resource.hpp"
#include "egui/core/detail/types/bitmap.hpp"
#include "egui/core/detail/types/brush.hpp"
#include "egui/core/detail/types/font.hpp"
#include "egui/core/detail/types/icon.hpp"
#include "egui/core/detail/types/pen.hpp"
#include "egui/core/detail/types/image_list.hpp"

namespace egui { namespace types {

    typedef boost::int64_t int64;

}

using namespace types;

}

#endif

