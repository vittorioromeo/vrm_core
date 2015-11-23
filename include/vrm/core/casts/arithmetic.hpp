// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <cfenv>
#include <limits>
#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/type_traits.hpp>
#include <vrm/core/casts/impl/overflow_check.hpp>

VRM_CORE_NAMESPACE
{
    template <typename TOut, typename TIn>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_num(const TIn& x) noexcept
    {
        static_assert(are_both_numbers<TOut, TIn>{},
            "`to_num` only works on numerical types.");

        VRM_CORE_CONSTEXPR_ASSERT((!impl::will_overflow<TOut, TIn>(x)));

        return static_cast<TOut>(x);
    }

    /// @brief Converts a number to `int`.
    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_int(const T& x) noexcept
    {
        return to_num<int>(x);
    }

    /// @brief Converts a number to `float`.
    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_float(const T& x) noexcept
    {
        return to_num<float>(x);
    }

    /// @brief Converts a number to `double`.
    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_double(const T& x) noexcept
    {
        return to_num<double>(x);
    }

    /// @brief Converts a number to `sz_t`.
    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_sz_t(const T& x) noexcept
    {
        return to_num<sz_t>(x);
    }
}
VRM_CORE_NAMESPACE_END
