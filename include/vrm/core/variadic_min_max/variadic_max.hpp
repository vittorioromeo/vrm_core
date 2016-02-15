// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>

VRM_CORE_NAMESPACE
{
    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto variadic_max(T a) noexcept
    {
        return a;
    }

    template <typename T0, typename T1>
    VRM_CORE_ALWAYS_INLINE constexpr auto variadic_max(T0 a, T1 b) noexcept
    {
        return a < b ? b : a;
    }

    template <typename T0, typename T1, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr auto variadic_max(
        T0 a, T1 b, Ts... xs) noexcept
    {
        return variadic_max(a, variadic_max(b, xs...));
    }
}
VRM_CORE_NAMESPACE_END
