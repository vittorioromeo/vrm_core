// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/internal.hpp>
#include <vrm/core/assert.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename TOut, typename TIn>
        using num_convertible = std::integral_constant<bool,
            std::is_arithmetic<TOut>{} && std::is_arithmetic<TIn>() &&
                !std::is_enum<TOut>() && !std::is_enum<TIn>()>;

        template <typename TOut, typename TIn>
        using sign_compatible = std::integral_constant<bool,
            std::is_signed<TOut>{} == std::is_signed<TIn>{}>;
    }

    template <typename TOut, typename TIn>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_num(const TIn& x) noexcept
        ->std::enable_if_t<impl::num_convertible<TOut, TIn>{} &&
                               impl::sign_compatible<TOut, TIn>{},
            TOut>
    {
        return static_cast<TOut>(x);
    }

    template <typename TOut, typename TIn>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_num(const TIn& x) noexcept
        ->std::enable_if_t<impl::num_convertible<TOut, TIn>{} &&
                               !impl::sign_compatible<TOut, TIn>{},
            TOut>
    {        
        VRM_CORE_CONSTEXPR_ASSERT(x >= 0);
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

    /// @brief Converts a number to `std::size_t`.
    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_size_t(const T& x) noexcept
    {
        return to_num<::std::size_t>(x);
    }
}
VRM_CORE_NAMESPACE_END