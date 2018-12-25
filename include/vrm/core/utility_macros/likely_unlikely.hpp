// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>

#if defined(VRM_CORE_COMPILER_CLANG) || defined(VRM_CORE_COMPILER_GCC)

namespace vrm::core
{
    /// @brief Micro-optimization: condition likely to be true.
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr bool likely(
        const bool x) noexcept
    {
        return __builtin_expect(x, true);
    }

    /// @brief Micro-optimization: condition unlikely to be true.
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr bool unlikely(
        const bool x) noexcept
    {
        return __builtin_expect(x, false);
    }
} // namespace vrm::core

#else

namespace vrm::core
{
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr bool likely(
        const bool x) noexcept
    {
        return x;
    }

    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr bool unlikely(
        const bool x) noexcept
    {
        return x;
    }
} // namespace vrm::core

#endif
