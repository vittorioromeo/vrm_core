// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <cstddef>
#include <ostream>
#include <vrm/core/config.hpp>

namespace std
{
    auto& operator<<(std::ostream& o, const std::nullptr_t&);
}

#if defined(VRM_CORE_INLINE_LIBRARY)
#include <vrm/core/ostream_utils/nullptr_printer.cpp>
#endif