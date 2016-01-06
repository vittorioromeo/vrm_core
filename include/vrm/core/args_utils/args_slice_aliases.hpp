// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/args_utils/nth_arg.hpp>
#include <vrm/core/args_utils/args_slice.hpp>

// TODO: docs
// (mention inclusion/exclusion in ranges)

VRM_CORE_NAMESPACE
{
    template <sz_t TN, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) first_n_args(
        Ts && ... xs) noexcept
    {
        return args_slice<0, TN>(FWD(xs)...);
    }

    template <sz_t TN, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) last_n_args(
        Ts && ... xs) noexcept
    {
        constexpr auto begin_idx(sizeof...(xs)-TN);
        return args_slice<begin_idx, begin_idx + TN>(FWD(xs)...);
    }

    template <sz_t TN, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) all_args_from(
        Ts && ... xs) noexcept
    {
        return args_slice<TN, sizeof...(xs)>(FWD(xs)...);
    }

    // TODO: test
    template <sz_t TN, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) all_args_after(
        Ts && ... xs) noexcept
    {
        return all_args_from<TN + 1>(FWD(xs)...);
    }

    // TODO: test
    template <sz_t TN, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) all_args_before(
        Ts && ... xs) noexcept
    {
        return first_n_args<TN>(FWD(xs)...);
    }

    template <typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) first_arg(
        Ts && ... xs) noexcept
    {
        return std::get<0>(first_n_args<1>(FWD(xs)...));
    }

    template <typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) last_arg(
        Ts && ... xs) noexcept
    {
        return std::get<0>(last_n_args<1>(FWD(xs)...));
    }
}
VRM_CORE_NAMESPACE_END
