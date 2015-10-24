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
    template <typename T, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr T& to_derived(TBase & base) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_base_of<TBase, T>{});
        return static_cast<T&>(base);
    }

    template <typename T, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr T* to_derived(TBase * base) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_base_of<TBase, T>{});
        return static_cast<T*>(base);
    }

    template <typename T, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr const T& to_derived(
        const TBase& base) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_base_of<TBase, T>{});
        return static_cast<const T&>(base);
    }

    template <typename T, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr const T* to_derived(
        const TBase* base) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_base_of<TBase, T>{});
        return static_cast<const T*>(base);
    }
}
VRM_CORE_NAMESPACE_END