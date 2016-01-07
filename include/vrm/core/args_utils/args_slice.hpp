// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/args_utils/nth_arg.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <sz_t TIBegin, sz_t... TIs, typename... Ts>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) build_args_slice(
            std::index_sequence<TIs...>, Ts&&... xs) noexcept
        {
            return make_ref_tuple(nth_arg<TIBegin + TIs>(FWD(xs)...)...);
        }
    }

    template <sz_t TIBegin, sz_t TIEnd, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) args_slice(
        Ts && ... xs) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(TIEnd >= TIBegin);
        VRM_CORE_STATIC_ASSERT_NM(sizeof...(xs) >= TIEnd - TIBegin);

        return impl::build_args_slice<TIBegin>(
            std::make_index_sequence<TIEnd - TIBegin>(), FWD(xs)...);
    }
}
VRM_CORE_NAMESPACE_END

// TODO: docs
