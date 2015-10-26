// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/names.hpp>

VRM_CORE_NAMESPACE
{
    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr T variadic_max(T a) noexcept
    {
        return a;
    }

    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr T variadic_max(T a, T b) noexcept
    {
        return a < b ? b : a;
    }

    template <typename T, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr T variadic_max(T a, T b, Ts... xs) noexcept
    {
        return variadic_max<T>(a, variadic_max<T>(b, xs...));
    }
}
VRM_CORE_NAMESPACE_END