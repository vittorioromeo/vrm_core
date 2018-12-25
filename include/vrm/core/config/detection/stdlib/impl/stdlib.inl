// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/detection/stdlib/impl/stdlib.hpp>
#include <vrm/core/config/detection/stdlib/impl/stdlib_macros.hpp>

namespace vrm::core::detection
{
    inline constexpr auto current_stdlib() noexcept
    {
#if defined(VRM_CORE_STDLIB_LIBCXX)
        return stdlib::libcxx;
#elif defined(VRM_CORE_STDLIB_LIBSTDCXX)
        return stdlib::libstdcxx;
#else
        return stdlib::unknown;
#endif
    }
} // namespace vrm::core::detection
