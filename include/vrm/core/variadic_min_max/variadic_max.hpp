// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>

namespace vrm::core
{
    template <typename T>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) variadic_max(
        T&& a) noexcept
    {
        return FWD(a);
    }

    template <typename T0, typename T1, typename... Ts>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) variadic_max(
        T0&& a, T1&& b, Ts&&... xs) noexcept
    {
        if constexpr(sizeof...(Ts) == 0)
        {
            return a < b ? FWD(b) : FWD(a);
        }
        else
        {
            return variadic_max(FWD(a), variadic_max(FWD(b), FWD(xs)...));
        }
    }
} // namespace vrm::core
