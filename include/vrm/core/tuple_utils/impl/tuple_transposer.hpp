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
#include <vrm/core/tuple_utils/ref_tuple.hpp>
#include <vrm/core/casts/self.hpp>
#include <vrm/core/type_traits/common.hpp>
#include <vrm/core/type_traits/tuple.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <sz_t TColumnCount, sz_t TRowCount>
        struct tuple_transposer
        {
            static constexpr sz_t column_count{TColumnCount};
            static constexpr sz_t row_count{TRowCount};

            // TODO: to utils
            template <typename T0, typename T1, typename T2>
            inline static constexpr auto index_1d_from_2d(
                const T0& x, const T1& y, const T2& x_column_count) noexcept
            {
                VRM_CORE_CONSTEXPR_ASSERT(x_column_count >= 0);
                return x + y * x_column_count;
            }

            template <sz_t TVX, sz_t TVY, typename TF, typename T>
            inline static constexpr decltype(auto) get_normal(
                TF&&, T&& t) noexcept
            {
                constexpr auto idx(index_1d_from_2d(TVX, TVY, column_count));

                using nth_arg_type =
                    std::tuple_element_t<idx, std::decay_t<decltype(FWD(t))>>;

                // return self_cast<nth_arg_type>(std::get<idx>(FWD(t)));
                return std::get<idx>(FWD(t));
            }



            template <sz_t TIColumn, typename TF, typename T, sz_t... TIs>
            inline static constexpr decltype(auto)
            make_column_tuple_single_impl(
                std::index_sequence<TIs...>, TF&& f, T&& t)
            {
                return f(get_normal<TIColumn, TIs>(f, FWD(t))...);
            }

            template <typename TF, typename T, sz_t... TIs>
            inline static constexpr decltype(auto) exec_single_impl(
                std::index_sequence<TIs...>, TF&& f, T&& t)
            {
                return std::tuple_cat(make_column_tuple_single_impl<TIs>(
                    std::make_index_sequence<row_count>{}, f, FWD(t))...);
            }

            template <typename TF, typename T>
            inline static constexpr decltype(auto) exec_single(TF&& f, T&& t)
            {
                return exec_single_impl(
                    std::make_index_sequence<column_count>{}, f, FWD(t));
            }

            // TODO: test, fix columns, static assert, noexcept, inline, etc
            // TODO: transpose_args
            // TODO: transpose_types<...>
            // TODO: call_interleaved<arity>(f, args...)
            // TODO: transposed_index(...)
        };

        template <sz_t TColumnCount, sz_t TRowCount, typename TF, typename T>
        inline constexpr decltype(auto) invoke_tuple_transposer(
            TF&& f, T&& t) noexcept
        {
            return tuple_transposer<TColumnCount, TRowCount>::exec_single(
                f, FWD(t));
        }

        struct make_tuple_wrapper
        {
            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()(
                Ts&&... xs)
            {
                return std::make_tuple(FWD(xs)...);
            }
        };

        struct make_ref_tuple_wrapper
        {
            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()(
                Ts&&... xs)
            {
                return make_ref_tuple(FWD(xs)...);
            }
        };

        struct forward_as_tuple_wrapper
        {
            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()(
                Ts&&... xs)
            {
                return std::forward_as_tuple(FWD(xs)...);
            }
        };

        template <sz_t TRowCount, typename T>
        constexpr sz_t tuple_column_count{decay_tuple_size<T>() / TRowCount};

        template <sz_t TRowCount, typename TF, typename... Ts>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
            make_generic_transposed_tuple(TF&& f, Ts&&... xs) noexcept
        {
            return invoke_tuple_transposer< //.
                sizeof...(xs) / TRowCount, TRowCount>(f, f(FWD(xs)...));
        }

        template <sz_t TRowCount, typename TF, typename T>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
            to_generic_transposed_tuple(TF&& f, T&& t) noexcept
        {
            return invoke_tuple_transposer< //.
                tuple_column_count<TRowCount, T>, TRowCount>(f, FWD(t));
        }


        // TODO: improve?
        // TODO: check apply(...);
        template <typename T, sz_t... TIs>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
            tuple_ref_to_ref_tuple(T&& t, std::index_sequence<TIs...>) noexcept
        {
            return std::forward_as_tuple(std::get<TIs>(FWD(t))...);
        }


        template <typename TF, typename... TRows>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
            to_generic_transposed_tuple_from_rows(
                TF&& f, TRows&&... rows) noexcept
        {
            return f(std::tuple_cat(FWD(tuple_ref_to_ref_tuple(
                FWD(rows), make_tuple_index_sequence<decltype(rows)>{}))...));
        }
    }
}
VRM_CORE_NAMESPACE_END
