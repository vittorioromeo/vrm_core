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
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/tuple_utils/transpose.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename TF, typename TT, sz_t... TIs>
        VRM_CORE_ALWAYS_INLINE decltype(auto) apply_helper(
            TF&& f, TT&& t, std::index_sequence<TIs...>) // .
            noexcept(noexcept(FWD(f)(std::get<TIs>(FWD(t))...)))
        {
            // The `apply_helper` function calls `f` once, expanding the
            // contents of the `t` tuple as the function parameters.
            return FWD(f)(std::get<TIs>(FWD(t))...);
        }
    }

    template <typename TF, typename TT>
    VRM_CORE_ALWAYS_INLINE decltype(auto) apply(TF && f, TT && t) // .
        noexcept(noexcept(impl::apply_helper(
            FWD(f), FWD(t), make_tuple_index_sequence<TT>{})))
    {
        // `apply_helper` requires an index sequence that goes from `0` to
        // the number of tuple items.

        return impl::apply_helper(
            FWD(f), FWD(t), make_tuple_index_sequence<TT>{});
    }


    template <typename TF, typename... TTs>
    VRM_CORE_ALWAYS_INLINE decltype(auto) apply_all_sequential(
        TF && f, TTs && ... ts) // .
    {
        return apply(FWD(f), std::tuple_cat(FWD(ts)...));
    }

    template <typename TF, typename... TTs>
    VRM_CORE_ALWAYS_INLINE decltype(auto) apply_all_interleaved(
        TF && f, TTs && ... ts) // .
    {
        // TODO:
        // implement for_tuple(...) in terms of this and for_args<columns>
    }
}
VRM_CORE_NAMESPACE_END
