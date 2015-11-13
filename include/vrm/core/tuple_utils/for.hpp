// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/type_traits/common.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/for_args.hpp>
#include <vrm/core/variadic_min_max.hpp>

#define VRM_CORE_IMPL_TPLFORHELPER_BODY() \
    FWD(f)(for_tuple_data_type<TI>{}, std::get<TI>(FWD(ts))...)

#define VRM_CORE_IMPL_TPLFOR_CALL()                                          \
    ::vrm::core::impl::for_tuple_data_helper<::vrm::core::variadic_min(      \
                                                 decay_tuple_size<Ts>()...), \
        Ts...>::exec(FWD(f), FWD(ts)...)

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <sz_t TI>
        struct for_tuple_data_type
        {
            static constexpr sz_t index{TI};
        };

        template <sz_t TS, typename... Ts>
        struct for_tuple_data_helper
        {
            template <sz_t TI, typename TF>
            VRM_CORE_ALWAYS_INLINE static std::enable_if_t<TI == TS, void> exec(
                TF, Ts&&...) noexcept
            {
            }

            template <sz_t TI = 0, typename TF>
                VRM_CORE_ALWAYS_INLINE static std::enable_if_t <
                TI<TS, void> exec(TF&& f, Ts&&... ts) noexcept(
                    noexcept(VRM_CORE_IMPL_TPLFORHELPER_BODY()))
            {
                VRM_CORE_IMPL_TPLFORHELPER_BODY();
                exec<TI + 1, TF>(FWD(f), FWD(ts)...);
            }
        };
    }

    /// @brief Iterates over a tuple's elements passing current iteration data
    /// and them to `f` one at a time.
    /// @details Can iterate over multiple tuples at once, passing the Nth
    /// element of every tuple to `f` simultaneously.
    /// If the tuples have different sizes, the minimum size will be used.
    template <typename TF, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr void for_tuple_data(
        TF && f, Ts && ... ts) noexcept(noexcept(VRM_CORE_IMPL_TPLFOR_CALL()))
    {
        VRM_CORE_IMPL_TPLFOR_CALL();
    }

    /// @brief Iterates over a tuple's elements passing them to `f` one at a
    /// time.
    /// @details Can iterate over multiple tuples at once, passing the Nth
    /// element of every tuple to `f` simultaneously.
    /// If the tuples have different sizes, the minimum size will be used.
    template <typename TF, typename... Ts>
    VRM_CORE_ALWAYS_INLINE                              // .
        constexpr void for_tuple(TF && f, Ts && ... xs) // .
    //     noexcept(noexcept(for_args_data<TArity>(
    //       impl::ignore_first_arg<decltype(f)>{f}, FWD(xs)...)))
    {
        for_tuple_data(
            [&f](auto, auto&&... rest)
            {
                f(FWD(rest)...);
            },
            FWD(xs)...);
    }
}
VRM_CORE_NAMESPACE_END

#undef VRM_CORE_IMPL_TPLFOR_CALL
#undef VRM_CORE_IMPL_DEFINE_TPLFOR_FN

// TODO: implement using static_for? noexcept?
