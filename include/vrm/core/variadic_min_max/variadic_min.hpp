// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>

VRM_CORE_NAMESPACE
{
    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr T variadic_min(T a) noexcept
    {
        return a;
    }

    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr T variadic_min(T a, T b) noexcept
    {
        return a < b ? a : b;
    }

    template <typename T, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr T variadic_min(T a, T b, Ts... xs) noexcept
    {
        return variadic_min<T>(a, variadic_min<T>(b, xs...));
    }
}
VRM_CORE_NAMESPACE_END
