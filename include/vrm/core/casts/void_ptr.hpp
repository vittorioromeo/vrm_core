// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/casts/arithmetic.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/type_traits/qualifiers.hpp>

namespace vrm::core
{
    template <typename T>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr auto to_void_ptr(
        T* x) noexcept
    {
        return static_cast<copy_cv_qualifiers<void, T>*>(x);
    }

    template <typename T>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr auto num_to_void_ptr(
        T&& x) noexcept
        -> std::enable_if_t<!std::is_pointer<T>{}, copy_cv_qualifiers<void, T>*>
    {
        static_assert(std::is_arithmetic_v<std::decay_t<T>>);
        return reinterpret_cast<copy_cv_qualifiers<void, T>*>(x);
    }
} // namespace vrm::core
