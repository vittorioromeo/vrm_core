// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/casts/arithmetic.hpp>
#include <vrm/core/type_traits/qualifiers.hpp>

VRM_CORE_NAMESPACE
{
    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_void_ptr(T * x) noexcept
    {
        return static_cast<copy_cv_qualifiers<void, T>*>(x);
    }

    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto num_to_void_ptr(T && x) noexcept
        ->std::enable_if_t<!std::is_pointer<T>{}, copy_cv_qualifiers<void, T>*>
    {
        VRM_CORE_STATIC_ASSERT_NM(std::is_arithmetic<std::decay_t<T>>{});
        return reinterpret_cast<copy_cv_qualifiers<void, T>*>(x);
    }
}
VRM_CORE_NAMESPACE_END
