// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/variadic_min_max.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/type_traits/common.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/tuple_utils/ref_tuple.hpp>
#include <vrm/core/casts/self.hpp>
#include <vrm/core/tuple_utils/impl/tuple_transposer.hpp>

VRM_CORE_NAMESPACE
{
    template <sz_t TRowCount, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        make_transposed_tuple(Ts && ... xs) noexcept
    {
        return impl::make_generic_transposed_tuple<TRowCount>( // .
            impl::make_tuple_wrapper{}, FWD(xs)...);
    }

    template <sz_t TRowCount, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        make_transposed_ref_tuple(Ts && ... xs) noexcept
    {
        return impl::make_generic_transposed_tuple<TRowCount>( // .
            impl::make_ref_tuple_wrapper{}, FWD(xs)...);
    }


    template <sz_t TRowCount, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        forward_as_transposed_tuple(Ts && ... xs) noexcept
    {
        return impl::make_generic_transposed_tuple<TRowCount>( // .
            impl::forward_as_tuple_wrapper{}, FWD(xs)...);
    }



    template <sz_t TRowCount, typename T>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        to_transposed_tuple(T && t) noexcept
    {
        return impl::to_generic_transposed_tuple<TRowCount>( // .
            impl::make_tuple_wrapper{}, FWD(t));
    }

    template <sz_t TRowCount, typename T>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        to_transposed_ref_tuple(T && t) noexcept
    {
        return impl::to_generic_transposed_tuple<TRowCount>( // .
            impl::make_ref_tuple_wrapper{}, FWD(t));
    }

    template <sz_t TRowCount, typename T>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        to_forwarded_transposed_tuple(T && t) noexcept
    {
        return impl::to_generic_transposed_tuple<TRowCount>( // .
            impl::forward_as_tuple_wrapper{}, FWD(t));
    }

    template <typename... TRows>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        to_transposed_tuple_from_rows(TRows && ... rows)
    {
        return impl::to_generic_transposed_tuple_from_rows(
            [](auto&& t) -> decltype(auto)
            {
                return to_transposed_tuple<sizeof...(TRows)>(FWD(t));
            },
            FWD(rows)...);
    }

    template <typename... TRows>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        to_transposed_ref_tuple_from_rows(TRows && ... rows)
    {
        return impl::to_generic_transposed_tuple_from_rows(
            [](auto&& t) -> decltype(auto)
            {
                return to_transposed_ref_tuple<sizeof...(TRows)>(FWD(t));
            },
            FWD(rows)...);
    }

    template <typename... TRows>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        to_forwarded_transposed_tuple_from_rows(TRows && ... rows)
    {
        return impl::to_generic_transposed_tuple_from_rows(
            [](auto&& t) -> decltype(auto)
            {
                return to_forwarded_transposed_tuple<sizeof...(TRows)>(FWD(t));
            },
            FWD(rows)...);
    }
}
VRM_CORE_NAMESPACE_END

// TODO: noexcept(...
