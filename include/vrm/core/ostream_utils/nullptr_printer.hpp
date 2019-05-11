// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <cstddef>
#include <iosfwd>
#include <vrm/core/config.hpp>

namespace std
{
    VRM_CORE_FN_API auto& operator<<(ostream& o, const nullptr_t&);
}

#if defined(VRM_CORE_INLINE_LIBRARY)
#include <vrm/core/ostream_utils/nullptr_printer.cpp>
#endif
