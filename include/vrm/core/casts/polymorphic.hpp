// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_traits.hpp>
#include <vrm/core/ostream_utils.hpp>

VRM_CORE_NAMESPACE
{
    template <typename TDerived, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived(
        TBase * base) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_base_of<TBase, TDerived>{});
        VRM_CORE_ASSERT_OP(base, !=, nullptr);

        return static_cast<TDerived*>(base);
    }

    template <typename TDerived, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived(
        TBase & base) noexcept
    {
        return *to_derived<TDerived>(&base);
    }

    template <typename TDerived, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived(
        const TBase* base) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_base_of<TBase, TDerived>{});
        VRM_CORE_ASSERT_OP(base, !=, nullptr);

        return static_cast<const TDerived*>(base);
    }

    template <typename TDerived, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived(
        const TBase& base) noexcept
    {
        return *to_derived<TDerived>(&base);
    }



    template <typename TBase, typename TDerived>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base(
        TDerived * derived) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_derived_of<TDerived, TBase>{});
        VRM_CORE_ASSERT_OP(derived, !=, nullptr);

        return static_cast<TBase*>(derived);
    }

    template <typename TBase, typename TDerived>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base(
        TDerived & derived) noexcept
    {
        return *to_base<TBase>(&derived);
    }

    template <typename TBase, typename TDerived>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base(
        const TDerived* derived) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(is_same_or_derived_of<TDerived, TBase>{});
        VRM_CORE_ASSERT_OP(derived, !=, nullptr);

        return static_cast<const TBase*>(derived);
    }

    template <typename TBase, typename TDerived>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base(
        const TDerived& derived) noexcept
    {
        return *to_base<TDerived>(&derived);
    }
}
VRM_CORE_NAMESPACE_END