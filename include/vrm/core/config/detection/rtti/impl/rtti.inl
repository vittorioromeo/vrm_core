// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/detection/rtti/impl/rtti.hpp>
#include <vrm/core/config/detection/rtti/impl/rtti_macros.hpp>

namespace vrm::core::detection
{
    [[nodiscard]] inline constexpr bool rtti() noexcept
    {
#if defined(VRM_CORE_RTTI_ENABLED)
        return true;
#else
        return false;
#endif
    }
} // namespace vrm::core::detection
