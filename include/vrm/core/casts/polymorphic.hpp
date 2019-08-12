// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/assert.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/ostream_utils.hpp>
#include <vrm/core/type_traits.hpp>
#include <vrm/core/type_traits/common.hpp>
#include <vrm/core/type_traits/forward_like.hpp>
#include <vrm/core/type_traits/qualifiers.hpp>

namespace vrm::core
{
    namespace impl
    {
        template <typename TOut, typename T>
        VRM_CORE_ALWAYS_INLINE constexpr void assert_correct_polymorphic(
            T* ptr, std::true_type /* base class is polymorphic */) noexcept
        {
            VRM_CORE_ASSERT_OP(dynamic_cast<TOut>(ptr), ==, ptr);

            // Suppress unused warning in non-debug builds.
            (void)ptr;
        }

        template <typename TCasted, typename T>
        VRM_CORE_ALWAYS_INLINE constexpr void assert_correct_polymorphic(
            T*, std::false_type /* base class is not polymorphic */) noexcept
        {
        }

        template <typename TDerived, typename TBase, typename TOut, typename T>
        [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto)
        hierarchy_cast(T* ptr) noexcept
        {
            static_assert(std::is_base_of_v<TBase, TDerived>);
            VRM_CORE_ASSERT_OP(ptr, !=, nullptr);

            assert_correct_polymorphic<TOut>(ptr, std::is_polymorphic<TBase>{});
            return static_cast<TOut>(ptr);
        }
    } // namespace impl

    template <typename TDerived, typename TBase>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived(
        TBase* base) noexcept
    {
        using result_type = copy_cv_qualifiers<TDerived, TBase>*;
        return impl::hierarchy_cast<TDerived, TBase, result_type>(base);
    }

    template <typename TBase, typename TDerived>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base(
        TDerived* derived) noexcept
    {
        using result_type = copy_cv_qualifiers<TBase, TDerived>*;
        return impl::hierarchy_cast<TDerived, TBase, result_type>(derived);
    }

    template <typename TDerived, typename TBase>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived(
        TBase&& base) noexcept
    {
        return forward_like<decltype(base)>(*to_derived<TDerived>(&base));
    }

    template <typename TBase, typename TDerived>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base(
        TDerived&& derived) noexcept
    {
        return forward_like<decltype(derived)>(*to_base<TBase>(&derived));
    }
} // namespace vrm::core
