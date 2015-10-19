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
    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto from_enum(const T& x) noexcept
    {
        return static_cast<std::underlying_type_t<T>>(x);
    }

    template <typename TOut, typename TIn>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_enum(const TIn& x) noexcept
        ->std::enable_if_t<
            std::is_enum<TOut>() && !std::is_enum<TIn>() &&
                std::is_convertible<std::underlying_type_t<TOut>, TIn>{},
            TOut>
    {
        return static_cast<TOut>(x);
    }

    template <typename TOut, typename TIn>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_enum(const TIn& x) noexcept
        ->std::enable_if_t<std::is_enum<TOut>() && std::is_enum<TIn>(), TOut>
    {
        VRM_CORE_STATIC_ASSERT_NM(
            std::is_convertible<std::underlying_type_t<TOut>,
                std::underlying_type_t<TIn>>{});

        return static_cast<TOut>(x);
    }
}
VRM_CORE_NAMESPACE_END