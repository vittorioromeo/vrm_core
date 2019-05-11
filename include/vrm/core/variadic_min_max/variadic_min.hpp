// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros/fwd.hpp>

namespace vrm::core
{
    template <typename T>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) variadic_min(
        T&& a) noexcept
    {
        return FWD(a);
    }

    template <typename T0, typename T1, typename... Ts>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) variadic_min(
        T0&& a, T1&& b, Ts&&... xs) noexcept
    {
        if constexpr(sizeof...(Ts) == 0)
        {
            return a < b ? FWD(a) : FWD(b);
        }
        else
        {
            return variadic_min(FWD(a), variadic_min(FWD(b), FWD(xs)...));
        }
    }
} // namespace vrm::core
