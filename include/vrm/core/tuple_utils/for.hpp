// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <vrm/core/assert.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/for_args.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/type_traits/common.hpp>
#include <vrm/core/type_traits/tuple.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/variadic_min_max.hpp>

namespace vrm::core
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
            VRM_CORE_ALWAYS_INLINE static constexpr // .
                std::enable_if_t<(TI == TS), void>  // .
                exec(TF, Ts&&...)                   // .
                noexcept                            // .
            {
            }

#define VRM_CORE_IMPL_TPLFORHELPER_BODY() \
    FWD(f)(for_tuple_data_type<TI>{}, std::get<TI>(FWD(ts))...)

            template <sz_t TI = 0, typename TF>
            VRM_CORE_ALWAYS_INLINE static constexpr // .
                std::enable_if_t<(TI < TS), void>   // .
                exec(TF&& f, Ts&&... ts)            // .
                noexcept(noexcept(VRM_CORE_IMPL_TPLFORHELPER_BODY()))
            {
                VRM_CORE_IMPL_TPLFORHELPER_BODY();
                exec<TI + 1, TF>(FWD(f), FWD(ts)...);
            }

#undef VRM_CORE_IMPL_TPLFORHELPER_BODY
        };

        template <typename... Ts>
        struct for_tuple_data_helper<0, Ts...>
        {
            template <typename... TIgnore>
            VRM_CORE_ALWAYS_INLINE static constexpr // .
                void
                exec(TIgnore&&...) noexcept // .
            {
            }
        };
    } // namespace impl

    /// @brief Iterates over a tuple's elements passing current iteration data
    /// and them to `f` one at a time.
    /// @details Can iterate over multiple tuples at once, passing the Nth
    /// element of every tuple to `f` simultaneously.
    /// If the tuples have different sizes, the minimum size will be used.
    template <typename TF, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr auto for_tuple_data(TF&& f, Ts&&... ts)
        VRM_CORE_RETURNS(::vrm::core::impl::for_tuple_data_helper<
            ::vrm::core::variadic_min(decay_tuple_size<Ts>()...),
            Ts...>::exec(FWD(f), FWD(ts)...))
} // namespace vrm::core

namespace vrm::core::impl
{
    template <typename TF>
    class for_tuple_caller
    {
    private:
        TF _f;

    public:
        template <typename TFFwd>
        VRM_CORE_ALWAYS_INLINE explicit constexpr for_tuple_caller(
            TFFwd&& f) noexcept
            : _f{FWD(f)}
        {
        }

        template <typename TIgnore, typename... Ts>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        operator()(TIgnore&&, Ts&&... xs)               // .
            noexcept(noexcept((std::declval<TF>()(FWD(xs)...))))
        {
            return _f(FWD(xs)...);
        }
    };
} // namespace vrm::core::impl

namespace vrm::core
{
    /// @brief Iterates over a tuple's elements passing them to `f` one at a
    /// time.
    /// @details Can iterate over multiple tuples at once, passing the Nth
    /// element of every tuple to `f` simultaneously.
    /// If the tuples have different sizes, the minimum size will be used.
    template <typename TF, typename... Ts>
    VRM_CORE_ALWAYS_INLINE // .
        constexpr auto
        for_tuple(TF&& f, Ts&&... xs)                                      // .
        VRM_CORE_RETURNS(                                                  // .
            for_tuple_data(impl::for_tuple_caller<TF>{FWD(f)}, FWD(xs)...) // .
        )
} // namespace vrm::core

// TODO: implement using static_for?
