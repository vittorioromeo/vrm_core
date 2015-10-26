// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/detection/debug/debug_macros.hpp>
#include <vrm/core/config/detection/debug/debug.hpp>

VRM_CORE_NAMESPACE
{
    namespace detection
    {
        inline constexpr auto debug() noexcept
        {
#if defined(VRM_CORE_DEBUG)
            return true;
#else
            return false;
#endif
        }
    }
}
VRM_CORE_NAMESPACE_END