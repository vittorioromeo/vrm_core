// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>

#if defined(VRM_CORE_COMPILER_CLANG) || defined(VRM_CORE_COMPILER_GCC)

VRM_CORE_NAMESPACE
{
    /// @brief Micro-optimization: condition likely to be true.
    VRM_CORE_ALWAYS_INLINE auto likely(bool x) noexcept
    {
        return __builtin_expect(x, true);
    }

    /// @brief Micro-optimization: condition unlikely to be true.
    VRM_CORE_ALWAYS_INLINE auto unlikely(bool x) noexcept
    {
        return __builtin_expect(x, false);
    }
}
VRM_CORE_NAMESPACE_END

#else

VRM_CORE_NAMESPACE
{
    VRM_CORE_ALWAYS_INLINE auto likely(bool x) noexcept
    {
        return x;
    }

    VRM_CORE_ALWAYS_INLINE auto unlikely(bool x) noexcept
    {
        return x;
    }
}
VRM_CORE_NAMESPACE_END

#endif
