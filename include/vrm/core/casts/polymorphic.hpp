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
#include <vrm/core/type_traits/common.hpp>
#include <vrm/core/type_traits/qualifiers.hpp>
#include <vrm/core/ostream_utils/nullptr_printer.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename TDerived, typename TBase, typename TOut, typename T>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) hierarchy_cast(
            T&& ptr) noexcept
        {
            VRM_CORE_STATIC_ASSERT_NM(std::is_base_of<TBase, TDerived>{});
            VRM_CORE_ASSERT_OP(ptr, !=, nullptr);

            return static_cast<TOut>(ptr);
        }

        template <typename TDerived, typename TBase>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived_impl(
            TBase* base) noexcept
        {
            return hierarchy_cast<TDerived, TBase, // .
                copy_cv_qualifiers<TDerived, TBase>*>(base);
        }

        template <typename TBase, typename TDerived>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base_impl(
            TDerived* derived) noexcept
        {
            return hierarchy_cast<TDerived, TBase, // .
                copy_cv_qualifiers<TBase, TDerived>*>(derived);
        }
    }

    template <typename TDerived, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived(
        TBase * base) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(!std::is_polymorphic<TBase>{});
        return impl::to_derived_impl<TDerived, TBase>(base);
    }

    template <typename TBase, typename TDerived>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base(
        TDerived * derived) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(!std::is_polymorphic<TBase>{});
        return impl::to_base_impl<TBase, TDerived>(derived);
    }

    template <typename TDerived, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived(
        TBase && base) noexcept
    {
        return *to_derived<TDerived>(&base);
    }

    template <typename TBase, typename TDerived>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base(
        TDerived && derived) noexcept
    {
        return *to_base<TBase>(&derived);
    }



    template <typename TDerived, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_polymorphic_derived(
        TBase * base) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(std::is_polymorphic<TBase>{});

        decltype(auto) res(impl::to_derived_impl<TDerived, TBase>(base));
        VRM_CORE_ASSERT_OP(dynamic_cast<decltype(res)>(base), ==, base);

        return res;
    }

    template <typename TBase, typename TDerived>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_polymorphic_base(
        TDerived * derived) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(std::is_polymorphic<TBase>{});

        decltype(auto) res(impl::to_base_impl<TBase, TDerived>(derived));
        VRM_CORE_ASSERT_OP(dynamic_cast<decltype(res)>(derived), ==, derived);

        return res;
    }

    template <typename TDerived, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_polymorphic_derived(
        TBase && base) noexcept
    {
        return *to_polymorphic_derived<TDerived>(&base);
    }

    template <typename TBase, typename TDerived>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_polymorphic_base(
        TDerived && derived) noexcept
    {
        return *to_polymorphic_base<TBase>(&derived);
    }
}
VRM_CORE_NAMESPACE_END

// TODO: use `enable_if` instead of two functions?
