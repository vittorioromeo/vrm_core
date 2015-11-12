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

VRM_CORE_NAMESPACE
{
    template <sz_t TColumnCount, sz_t TRowCount>
    struct tuple_transposer
    {
        // static constexpr sz_t
        // columns{variadic_min(std::tuple_size<TTs>{}...)};
        // static constexpr sz_t rows{sizeof...(TTs)};

        static constexpr sz_t columns{TColumnCount};
        static constexpr sz_t rows{TRowCount};
        /*
                template <sz_t TI, typename TF, typename... TTuples>
                auto make_column_tuple_impl(TF&& f, TTuples&&... ts)
                {
                    VRM_CORE_STATIC_ASSERT_NM(TI < columns);
                    return f(std::get<TI>(FWD(ts))...);
                }

                template <typename TF, typename... TTuples, sz_t... TIs>
                auto exec_impl(std::index_sequence<TIs...>, TF&& f, TTuples&&...
           ts)
                {
                    return std::tuple_cat(
                        make_column_tuple_impl<TIs>(f, FWD(ts)...)...);
                }

                template <typename TF, typename... TTuples>
                auto exec(TF&& f, TTuples&&... ts)
                {
                    return exec_impl(
                        std::make_index_sequence<columns>{}, f, FWD(ts)...);
                }
        */

        // TODO: to utils
        template <typename T0, typename T1, typename T2>
        inline static constexpr auto index_1d_from_2d(
            const T0& x, const T1& y, const T2& column_count) noexcept
        {
            VRM_CORE_CONSTEXPR_ASSERT(column_count >= 0);
            return x + y * column_count;
        }

        template <std::size_t TVX, std::size_t TVY, typename T>
        inline static constexpr decltype(auto) get_normal(
            T&& t) noexcept
        {
            constexpr auto idx(index_1d_from_2d(TVX, TVY, columns));
            return std::get<idx>(FWD(t));
        }



        template <sz_t TIColumn, typename TF, typename T, sz_t... TIs>
        inline static constexpr auto make_column_tuple_single_impl(
            std::index_sequence<TIs...>, TF&& f, T&& t)
        {
            return f(get_normal<TIColumn, TIs>(FWD(t))...);
        }

        template <typename TF, typename T, sz_t... TIs>
        inline static constexpr auto exec_single_impl(
            std::index_sequence<TIs...>, TF&& f, T&& t)
        {
            return std::tuple_cat(make_column_tuple_single_impl<TIs>(
                std::make_index_sequence<rows>{}, f, FWD(t))...);
        }

        template <typename TF, typename T>
        inline static constexpr auto exec_single(TF&& f, T&& t)
        {
            return exec_single_impl(
                std::make_index_sequence<columns>{}, f, FWD(t));
        }

        // TODO: test, fix columns, static assert, noexcept, inline, etc
        // TODO: transpose_args
        // TODO: transpose_types<...>
        // TODO: call_interleaved<arity>(f, args...)
    };

    template <sz_t TRowSize, typename T>
    auto make_transposed_tuple(T && t)
    {
        // TODO: decay_tuple_size

        return tuple_transposer<std::tuple_size<std::decay_t<T>>{} / TRowSize, TRowSize>::
            exec_single(
                [&](auto&&... xs)
                {
                    return std::make_tuple(FWD(xs)...);
                },
                FWD(t));
    }

    template <typename... TRows>
    auto make_transposed_tuple_from_row_tuples(TRows && ... rows)
    {
    }

    template <typename... TRows>
    auto make_transposed_ref_tuple_from_row_tuples(TRows && ... rows)
    {
    }

    template <typename... TRows>
    auto forward_as_transposed_tuple_from_row_tuples(TRows && ... rows)
    {
    }
}
VRM_CORE_NAMESPACE_END
