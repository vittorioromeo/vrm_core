// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_traits.hpp>

VRM_CORE_NAMESPACE
{
    /// @brief Converts an enum to its underlying type.
    template <typename TIn>
    VRM_CORE_ALWAYS_INLINE constexpr auto from_enum(const TIn& x) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(std::is_enum<TIn>{});

        return static_cast<std::underlying_type_t<TIn>>(x);
    }

    /// @brief Converts an enum to a type convertible to its underlying type.
    template <typename TOut, typename TIn>
    VRM_CORE_ALWAYS_INLINE constexpr auto from_enum(const TIn& x) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(std::is_enum<TIn>{});
        VRM_CORE_STATIC_ASSERT_NM(underlying_convertible_to<TIn, TOut>{});

        return static_cast<TOut>(x);
    }

    /// @brief Converts a number to an enum.
    template <typename TOut, typename TIn>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_enum(const TIn& x) noexcept
        ->std::enable_if_t<number_convertible_to_enum<TOut, TIn>{}, TOut>
    {
        return static_cast<TOut>(x);
    }

    /// @brief Converts an enum to another enum.
    /// @details The underlying types must be convertible between each other.
    template <typename TOut, typename TIn>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_enum(const TIn& x) noexcept
        ->std::enable_if_t<are_both_enums<TOut, TIn>{}, TOut>
    {
        VRM_CORE_STATIC_ASSERT_NM(
            are_underlying_types_convertible<TOut, TIn>{});

        return static_cast<TOut>(x);
    }
}
VRM_CORE_NAMESPACE_END
