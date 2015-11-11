// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/utility_macros.hpp>

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

        // We use `std::decay_t` here to get rid of the reference.
        template <typename TT>
        using get_indices =
            std::make_index_sequence<std::tuple_size<std::decay_t<TT>>{}>;
    }

    template <typename TF, typename TT>
    VRM_CORE_ALWAYS_INLINE decltype(auto) apply(TF && f, TT && t) // .
        noexcept(noexcept(
            impl::apply_helper(FWD(f), FWD(t), impl::get_indices<TT>{})))
    {
        // `apply_helper` requires an index sequence that goes from `0` to
        // the number of tuple items.

        // We can build that using `std::make_index_sequence` and
        // `std::tuple_size`.

        return impl::apply_helper(FWD(f), FWD(t), impl::get_indices<TT>{});
    }

    template <typename... TTs>
    struct tuple_transposer
    {
        static constexpr sz_t columns{variadic_min(std::tuple_size<TTs>{}...)};

        static constexpr sz_t rows{sizeof...(TTs)};

        template <sz_t TI>
        auto make_column_tuple(TTs&&... ts)
        {
            VRM_CORE_STATIC_ASSERT_NM(TI < columns);
            return std::forward_as_tuple(std::get<TI>(FWD(ts))...);
        }

        template <sz_t... TIs>
        auto exec_impl(TTs&&... ts)
        {
            return std::tuple_cat(make_column_tuple<TIs>(FWD(ts)...)...);
        }

        auto exec(TTs&&... ts)
        {
            return exec_impl(std::make_index_sequence<columns>(FWD(ts)...));
        }

        // TODO: test, fix columns, static assert, noexcept, inline, etc
        // TODO: transpose_args
        // TODO: call_interleaved<arity>(f, args...)
    };

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
