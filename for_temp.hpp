// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/for_args.hpp>
#include <vrm/core/variadic_min_max.hpp>
#include <vrm/core/type_traits/size_t_constant.hpp>

#define VRM_CORE_IMPL_TPLFOR_DATAEXEC_BODY()                      \
    for_args(                                                     \
        [&](auto i)                                               \
        {                                                         \
            f(for_tuple_data_type<i>{}, std::get<i>(FWD(ts))...); \
        },                                                        \
        size_t_constant<TIs>{}...)

#define VRM_CORE_IMPL_TPLFOR_CALL()                                        \
    ::vrm::core::impl::for_tuple_data_helper<                              \
        ::vrm::core::variadic_min(std::tuple_size<std::decay_t<Ts>>()...), \
        Ts...>::exec(FWD(f), FWD(ts)...)

namespace vrm::core
{
    namespace impl
    {
        template <typename... Ts>
        constexpr std::size_t min_tuple_size{
            variadic_min(std::tuple_size<std::decay_t<Ts>>()...)};

        template <typename... Ts>
        VRM_CORE_ALWAYS_INLINE constexpr auto make_min_tuple_size_seq() noexcept
        {
            return std::make_index_sequence<min_tuple_size<Ts...>>();
        }

        template <std::size_t TI>
        struct for_tuple_data_type
        {
            static constexpr std::size_t index{TI};
        };

        template <std::size_t... TIs, typename TF, typename... Ts>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) for_tuple_data_exec(
            std::index_sequence<TIs...>, TF&& f, Ts&&... ts) // noexcept(
        // noexcept(VRM_CORE_IMPL_TPLFORHELPER_BODY()))
        {
            // VRM_CORE_IMPL_TPLFORHELPER_BODY();
            return for_args(
                [&](auto i)
                {
                    f(for_tuple_data_type<i>{}, std::get<i>(FWD(ts))...);
                },
                size_t_constant<TIs>{}...);
        }
    }

    /// @brief Iterates over a tuple's elements passing current iteration
    /// data
    /// and them to `f` one at a time.
    /// @details Can iterate over multiple tuples at once, passing the Nth
    /// element of every tuple to `f` simultaneously.
    /// If the tuples have different sizes, the minimum size will be used.
    template <typename TF, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) for_tuple_data(TF && f,
        Ts && ... ts) // noexcept(noexcept(VRM_CORE_IMPL_TPLFOR_CALL()))
    {
        // VRM_CORE_IMPL_TPLFOR_CALL();

        return impl::for_tuple_data_exec(
            impl::make_min_tuple_size_seq<Ts...>(), FWD(f), FWD(ts)...);
    }

    /// @brief Iterates over a tuple's elements passing them to `f` one at a
    /// time.
    /// @details Can iterate over multiple tuples at once, passing the Nth
    /// element of every tuple to `f` simultaneously.
    /// If the tuples have different sizes, the minimum size will be used.
    template <typename TF, typename... Ts>
    VRM_CORE_ALWAYS_INLINE                                        // .
        constexpr decltype(auto) for_tuple(TF && f, Ts && ... xs) // .
    //     noexcept(noexcept(for_args_data<TArity>(
    //       impl::ignore_first_arg<decltype(f)>{f}, FWD(xs)...)))
    {
        return for_tuple_data(
            [&f](auto, auto&&... rest)
            {
                f(FWD(rest)...);
            },
            FWD(xs)...);
    }
}

#undef VRM_CORE_IMPL_TPLFOR_CALL
#undef VRM_CORE_IMPL_DEFINE_TPLFOR_FN
