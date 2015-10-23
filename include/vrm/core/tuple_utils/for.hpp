// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <vrm/core/internal.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/for_args.hpp>
#include <vrm/core/variadic_min_max.hpp>

#define VRM_CORE_IMPL_DEFINE_FORHELPER(name, body)                           \
    template <std::size_t TS, typename... TTs>                               \
    struct name                                                              \
    {                                                                        \
        template <std::size_t TI, typename TF>                               \
        VRM_CORE_ALWAYS_INLINE static std::enable_if_t<TI == TS, void> exec( \
            TF, TTs&&...) noexcept                                           \
        {                                                                    \
        }                                                                    \
                                                                             \
        template <std::size_t TI = 0, typename TF>                           \
            VRM_CORE_ALWAYS_INLINE static std::enable_if_t <                 \
            TI<TS, void> exec(TF&& f, TTs&&... ts) noexcept(noexcept(body))  \
        {                                                                    \
            body;                                                            \
            exec<TI + 1, TF>(FWD(f), FWD(ts)...);                            \
        }                                                                    \
    };

#define VRM_CORE_IMPL_TPLFOR_CALL(helper)                                   \
    ::vrm::core::impl::helper<::vrm::core::variadic_min(                    \
                                  std::tuple_size<std::decay_t<TTs>>()...), \
        TTs...>::exec(FWD(f), FWD(ts)...)

#define VRM_CORE_IMPL_DEFINE_TPLFOR_FN(name, helper)                \
    template <typename TF, typename... TTs>                         \
    VRM_CORE_ALWAYS_INLINE void name(TF&& f, TTs&&... ts) noexcept( \
        noexcept(VRM_CORE_IMPL_TPLFOR_CALL(helper)))                \
    {                                                               \
        VRM_CORE_IMPL_TPLFOR_CALL(helper);                          \
    }

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <std::size_t TI>
        struct for_tuple_data_type
        {
            static constexpr std::size_t index{TI};
        };

        VRM_CORE_IMPL_DEFINE_FORHELPER(for_tuple_helper, // .
            (FWD(f)(std::get<TI>(FWD(ts))...)))

        VRM_CORE_IMPL_DEFINE_FORHELPER(for_tuple_data_helper, // .
            (FWD(f)(for_tuple_data_type<TI>{}, std::get<TI>(FWD(ts))...)))

#undef VRM_CORE_IMPL_DEFINE_FORHELPER
    }

    /// @brief Iterates over a tuple's elements passing them to `f` one at a
    /// time.
    /// @details Can iterate over multiple tuples at once, passing the Nth
    /// element of every tuple to `f` simultaneously.
    /// If the tuples have different sizes, the minimum size will be used.
    VRM_CORE_IMPL_DEFINE_TPLFOR_FN(for_tuple, for_tuple_helper)

    /// @brief Iterates over a tuple's elements passing current iteration data
    /// and them to `f` one at a time.
    /// @details Can iterate over multiple tuples at once, passing the Nth
    /// element of every tuple to `f` simultaneously.
    /// If the tuples have different sizes, the minimum size will be used.
    VRM_CORE_IMPL_DEFINE_TPLFOR_FN(for_tuple_data, for_tuple_data_helper)
}
VRM_CORE_NAMESPACE_END

#undef VRM_CORE_IMPL_TPLFOR_CALL
#undef VRM_CORE_IMPL_DEFINE_TPLFOR_FN
