// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/casts/arithmetic.hpp>

VRM_CORE_NAMESPACE
{
    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_void_ptr(T * x) noexcept
    {
        return static_cast<void*>(x);
    }

    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_void_ptr(const T* x) noexcept
    {
        return static_cast<const void*>(x);
    }

    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto num_to_void_ptr(
        T & x) noexcept->std::enable_if_t<!std::is_pointer<T>{}, void*>
    {
        VRM_CORE_STATIC_ASSERT_NM(std::is_arithmetic<T>{});
        return reinterpret_cast<void*>(x);
    }

    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto num_to_void_ptr(const T& x) noexcept
        ->std::enable_if_t<!std::is_pointer<T>{}, const void*>
    {
        VRM_CORE_STATIC_ASSERT_NM(std::is_arithmetic<T>{});
        return reinterpret_cast<const void*>(x);
    }
}
VRM_CORE_NAMESPACE_END