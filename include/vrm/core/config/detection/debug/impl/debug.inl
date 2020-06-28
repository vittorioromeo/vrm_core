// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/detection/debug/impl/debug.hpp>
#include <vrm/core/config/detection/debug/impl/debug_macros.hpp>

namespace vrm::core::detection
{
    [[nodiscard]] inline constexpr bool debug() noexcept
    {
#if defined(VRM_CORE_DEBUG)
        return true;
#else
        return false;
#endif
    }
} // namespace vrm::core::detection
