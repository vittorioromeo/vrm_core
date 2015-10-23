// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <vrm/core/internal.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/utility_macros.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename T, typename TT>
        struct tuple_index_of_helper;

        template <typename T, typename... Ts>
        struct tuple_index_of_helper<T, std::tuple<T, Ts...>>
            : std::integral_constant<std::size_t, 0>
        {
        };

        template <typename T1, typename T2, typename... Ts>
        struct tuple_index_of_helper<T1, std::tuple<T2, Ts...>>
            : std::integral_constant<std::size_t,
                  1 + tuple_index_of_helper<T1, std::tuple<Ts...>>{}>
        {
        };
    }

    /// @brief Returns the index of the first occurrence of the type `T` in a
    /// tuple.
    template <typename T, typename TT>
    VRM_CORE_ALWAYS_INLINE constexpr auto tuple_index_of() noexcept
    {
        return impl::tuple_index_of_helper<T, TT>{};
    }

    /// @brief Returns the index of the first occurrence of the type `T` in a
    /// tuple. Deduces type.
    template <typename T, typename TT>
    VRM_CORE_ALWAYS_INLINE constexpr auto tuple_index_of(TT&)noexcept
    {
        return impl::tuple_index_of_helper<T, TT>{};
    }
}
VRM_CORE_NAMESPACE_END