// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/assert.hpp>
#include <vrm/core/casts/arithmetic.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/type_traits.hpp>

namespace vrm::core
{
    /// @brief Converts an enum to a type convertible to its underlying type.
    template <typename TOut, typename TIn>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr auto from_enum(
        const TIn& x) noexcept
    {
        static_assert(std::is_enum_v<TIn>);
        static_assert(underlying_convertible_to<TIn, TOut>{});

        return to_num<TOut>(static_cast<std::underlying_type_t<TIn>>(x));
    }

    /// @brief Converts an enum to its underlying type.
    template <typename TIn>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr auto from_enum(
        const TIn& x) noexcept
    {
        return from_enum<std::underlying_type_t<TIn>, TIn>(x);
    }

    /// @brief Converts a number to an enum.
    template <typename TOut, typename TIn>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr auto to_enum(
        const TIn& x) noexcept
        -> std::enable_if_t<number_convertible_to_enum<TOut, TIn>{}, TOut>
    {
        return static_cast<TOut>(to_num<std::underlying_type_t<TOut>>(x));
    }

    /// @brief Converts an enum to another enum.
    /// @details The underlying types must be convertible between each other.
    template <typename TOut, typename TIn>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr auto to_enum(
        const TIn& x) noexcept
        -> std::enable_if_t<are_both_enums<TOut, TIn>{}, TOut>
    {
        static_assert(are_underlying_types_convertible<TOut, TIn>{});

        return to_enum<TOut>(from_enum(x));
    }
} // namespace vrm::core
