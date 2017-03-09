// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <type_traits>
#include <vrm/core/assert.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/tuple_utils/transpose.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/type_traits/tuple.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/variadic_min_max.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename TF, typename TT, sz_t... TIs>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) apply_helper(
            TF&& f, TT&& t, std::index_sequence<TIs...>) // .
        // noexcept(noexcept(FWD(f)(std::get<TIs>(FWD(t))...)))
        {
            // The `apply_helper` function calls `f` once, expanding the
            // contents of the `t` tuple as the function parameters.
            return FWD(f)(std::get<TIs>(FWD(t))...);
        }
    }

    template <typename TF, typename TT>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) apply(TF && f, TT && t) // .
    // noexcept(noexcept(impl::apply_helper( FWD(f), FWD(t),
    // make_tuple_index_sequence<TT>{})))
    {
        // `apply_helper` requires an index sequence that goes from `0` to
        // the number of tuple items.

        return impl::apply_helper(
            FWD(f), FWD(t), make_tuple_index_sequence<TT>{});
    }

    // TODO: move to another file
    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        tuple_ref_to_ref_tuple(T && t) noexcept
    {
        return vrm::core::apply(
            [](auto&&... xs) { return std::forward_as_tuple(FWD(xs)...); },
            FWD(t));

        // return std::forward_as_tuple(std::get<TIs>(FWD(t))...);
    }
    template <typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        tuple_cat_as_ref(Ts && ... ts) noexcept
    {
        return std::tuple_cat(tuple_ref_to_ref_tuple(FWD(ts))...);
    }

    template <sz_t TColumnCount, typename TF, typename TT>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) apply_interleaved(
        TF && f, TT && t) // .
    {
        // TODO: test

        constexpr sz_t row_count{decay_tuple_size<TT>() / TColumnCount};
        return vrm::core::apply(
            FWD(f), to_forwarded_transposed_tuple<row_count>(FWD(t)));
    }

    template <typename TF, typename... TTs>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) apply_all_sequential(
        TF && f, TTs && ... ts) // .
    {
        return vrm::core::apply(FWD(f), tuple_cat_as_ref(FWD(ts)...));
    }

    template <sz_t TColumnCount, typename TF, typename... TTs>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) apply_all_interleaved(
        TF && f, TTs && ... ts) // .
    {
        return apply_interleaved<TColumnCount>(
            FWD(f), tuple_cat_as_ref(FWD(ts)...));
    }

    template <typename TF, typename... TTs>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) multi_apply(
        TF && f, TTs && ... ts) // TODO: noexcept
    {
        // TODO: replace with multi-index-generation
        return vrm::core::apply(FWD(f), std::tuple_cat(FWD(ts)...));
    }
}
VRM_CORE_NAMESPACE_END

// TODO: noexcept(...
