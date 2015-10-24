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
    template <typename TDerived, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived(
        TBase & base) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_base_of<TBase, TDerived>{});
        return static_cast<TDerived&>(base);
    }

    template <typename TDerived, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived(
        TBase * base) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_base_of<TBase, TDerived>{});
        return static_cast<TDerived*>(base);
    }

    template <typename TDerived, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived(
        const TBase& base) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_base_of<TBase, TDerived>{});
        return static_cast<const TDerived&>(base);
    }

    template <typename TDerived, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived(
        const TBase* base) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_base_of<TBase, TDerived>{});
        return static_cast<const TDerived*>(base);
    }

    template <typename TBase, typename TDerived>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base(
        TDerived & derived) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_derived_of<TDerived, TBase>{});
        return static_cast<TBase&>(derived);
    }

    template <typename TBase, typename TDerived>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base(
        TDerived * derived) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_derived_of<TDerived, TBase>{});
        return static_cast<TBase*>(derived);
    }

    template <typename TBase, typename TDerived>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base(
        const TDerived& derived) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_derived_of<TDerived, TBase>{});
        return static_cast<const TBase&>(derived);
    }

    template <typename TBase, typename TDerived>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base(
        const TDerived* derived) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_derived_of<TDerived, TBase>{});
        return static_cast<const TBase*>(derived);
    }
}
VRM_CORE_NAMESPACE_END