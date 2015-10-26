// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <array>
#include <vrm/core/config/names.hpp>
#include <vrm/core/utility_macros.hpp>

VRM_CORE_NAMESPACE
{
#define VRM_CORE_IMPL_MAKE_ARRAY_BODY()                                \
    std::array<std::decay_t<std::common_type_t<Ts...>>, sizeof...(Ts)> \
    {                                                                  \
        {                                                              \
            FWD(xs)...                                                 \
        }                                                              \
    }

    template <typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr auto make_array(Ts && ... xs) noexcept(
        noexcept(VRM_CORE_IMPL_MAKE_ARRAY_BODY()))
    {
        return VRM_CORE_IMPL_MAKE_ARRAY_BODY();
    }
#undef VRM_CORE_IMPL_MAKE_ARRAY_BODY
}
VRM_CORE_NAMESPACE_END