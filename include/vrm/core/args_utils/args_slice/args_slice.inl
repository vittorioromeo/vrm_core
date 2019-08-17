// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/args_utils/args_slice/args_slice.hpp>
#include <vrm/core/args_utils/nth_arg.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/tuple_utils/ref_tuple.hpp>
#include <vrm/core/type_aliases/numerical.hpp>

namespace vrm::core
{
    namespace impl
    {
        template <sz_t TIBegin, sz_t... TIs, typename... Ts>
        VRM_CORE_ALWAYS_INLINE constexpr auto build_args_slice(
            std::index_sequence<TIs...>, Ts&&... xs) noexcept
        {
            return make_ref_tuple(nth_arg<TIBegin + TIs>(FWD(xs)...)...);
        }
    } // namespace impl

    template <sz_t TIBegin, sz_t TIEnd, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr auto args_slice(Ts&&... xs) noexcept
    {
        // Assert range validity.
        static_assert(TIEnd >= TIBegin);
        static_assert(sizeof...(xs) >= TIEnd - TIBegin);

        return impl::build_args_slice<TIBegin>(
            std::make_index_sequence<TIEnd - TIBegin>(), FWD(xs)...);
    }
} // namespace vrm::core
