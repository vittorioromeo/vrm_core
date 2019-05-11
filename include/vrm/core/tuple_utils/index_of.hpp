// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <vrm/core/assert.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/utility_macros.hpp>

namespace vrm::core
{
    namespace impl
    {
        template <typename T, typename TT>
        struct tuple_index_of_helper;

        template <typename T, typename... Ts>
        struct tuple_index_of_helper<T, std::tuple<T, Ts...>>
            : std::integral_constant<sz_t, 0>
        {
        };

        template <typename T1, typename T2, typename... Ts>
        struct tuple_index_of_helper<T1, std::tuple<T2, Ts...>>
            : std::integral_constant<sz_t,
                  1 + tuple_index_of_helper<T1, std::tuple<Ts...>>{}>
        {
        };
    } // namespace impl

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
    VRM_CORE_ALWAYS_INLINE constexpr auto tuple_index_of(TT&) noexcept
    {
        return impl::tuple_index_of_helper<T, TT>{};
    }
} // namespace vrm::core
