// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/args_utils/nth_arg.hpp>
#include <vrm/core/args_utils/args_slice.hpp>

VRM_CORE_NAMESPACE
{
    template <std::size_t TN, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) first_n_args(
        Ts && ... xs) noexcept
    {
        return args_slice<0, TN>(FWD(xs)...);
    }

    template <std::size_t TN, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) last_n_args(
        Ts && ... xs) noexcept
    {
        return args_slice<sizeof...(xs)-TN, sizeof...(xs)>(FWD(xs)...);
    }
}
VRM_CORE_NAMESPACE_END